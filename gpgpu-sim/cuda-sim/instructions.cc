// Copyright (c) 2009-2011, Tor M. Aamodt, Wilson W.L. Fung, Ali Bakhoda,
// Jimmy Kwa, George L. Yuan
// The University of British Columbia
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
// Redistributions in binary form must reproduce the above copyright notice, this
// list of conditions and the following disclaimer in the documentation and/or
// other materials provided with the distribution.
// Neither the name of The University of British Columbia nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <stdarg.h>
#include <iostream>
#include <GL/gl.h>
#include <vector>

#include "instructions.h"
#include "instructions_extra.h"
#include "ptx_ir.h"
#include "opcodes.h"
#include "ptx_sim.h"
#include "ptx.tab.h"
#include <stdlib.h>
#include <math.h>
#include <fenv.h>
#include "cuda-math.h"
#include "../stream_manager.h"
#include "../abstract_hardware_model.h"
#include "ptx_loader.h"
#include "cuda_device_printf.h"
#include "../gpgpu-sim/gpu-sim.h"
#include "../gpgpu-sim/shader.h"
#include "gpu/gpgpu-sim/cuda_gpu.hh"

unsigned ptx_instruction::g_num_ptx_inst_uid=0;

const char *g_opcode_string[NUM_OPCODES] = {
#define OP_DEF(OP,FUNC,STR,DST,CLASSIFICATION) STR,
#include "opcodes.def"
#undef OP_DEF
};

void inst_not_implemented( const ptx_instruction * pI ) ;
//ptx_reg_t srcOperandModifiers(ptx_reg_t opData, operand_info opInfo, operand_info dstInfo, unsigned type, ptx_thread_info *thread);

void sign_extend( ptx_reg_t &data, unsigned src_size, const operand_info &dst );

void writeVertexResultData(const operand_info &dst, const ptx_reg_t &data, unsigned type, ptx_thread_info *thread, const ptx_instruction *pI ){
    unsigned uniqueThreadId = thread->get_uid_in_kernel();
    unsigned attribIndex = dst.get_addr_offset();
    unsigned resAttribID;
    switch(dst.get_int()){//&0xFFFF){
        case VERTEX_POSITION:  resAttribID = VERT_RESULT_HPOS;break;
        case VERTEX_COLOR0:    resAttribID = VERT_RESULT_COL0;break;
        case VERTEX_COLOR1:    resAttribID = VERT_RESULT_COL1;break;
        case VERTEX_TEXCOORD0: resAttribID = VERT_RESULT_TEX0;break;
        case VERTEX_TEXCOORD1: resAttribID = VERT_RESULT_TEX1;break;
        case VERTEX_TEXCOORD2: resAttribID = VERT_RESULT_TEX2;break;
        case VERTEX_TEXCOORD3: resAttribID = VERT_RESULT_TEX3;break;
        case VERTEX_TEXCOORD4: resAttribID = VERT_RESULT_TEX4;break;
        case VERTEX_TEXCOORD5: resAttribID = VERT_RESULT_TEX5;break;
        case VERTEX_TEXCOORD6: resAttribID = VERT_RESULT_TEX6;break;
        case VERTEX_TEXCOORD7: resAttribID = VERT_RESULT_TEX7;break;
        default: printf("Undefined vertex result register \n"); abort();
    }
    writeVertexResult(uniqueThreadId,resAttribID,attribIndex,data.f32);
}

float readFragmentInputData(ptx_thread_info *thread,int builtin_id, unsigned dim_mod){
    unsigned uniqueThreadId = thread->get_uid_in_kernel();
    unsigned attribIndex = dim_mod;
    unsigned attribID;
    void* stream = thread->get_kernel_info()->get_stream();
    //std::cout<<"stream id is "<<thread->get_kernel_info()->get_stream()->get_uid()<<std::endl;
    
    switch(builtin_id){
        case FRAGMENT_POSITION:  attribID=FRAG_ATTRIB_WPOS; break;
        case FRAGMENT_TEXCOORD0: attribID=FRAG_ATTRIB_TEX0; break;
        case FRAGMENT_TEXCOORD1: attribID=FRAG_ATTRIB_TEX1; break;
        case FRAGMENT_TEXCOORD2: attribID=FRAG_ATTRIB_TEX2; break;
        case FRAGMENT_TEXCOORD3: attribID=FRAG_ATTRIB_TEX3; break;
        case FRAGMENT_TEXCOORD4: attribID=FRAG_ATTRIB_TEX4; break;
        case FRAGMENT_TEXCOORD5: attribID=FRAG_ATTRIB_TEX5; break;
        case FRAGMENT_TEXCOORD6: attribID=FRAG_ATTRIB_TEX6; break;
        case FRAGMENT_TEXCOORD7: attribID=FRAG_ATTRIB_TEX7; break;
        default: printf("Undefined fragment input register \n"); abort();
    }
    return readFragmentAttribs(uniqueThreadId, attribID, attribIndex, stream);
}

int readFragmentInputDataInt(ptx_thread_info *thread,int builtin_id, unsigned dim_mod){
    unsigned uniqueThreadId = thread->get_uid_in_kernel();
    unsigned attribIndex = dim_mod;
    unsigned attribID;
    void* stream = thread->get_kernel_info()->get_stream();
    assert(builtin_id == FRAGMENT_ACTIVE); // the only one for now
    attribID = FRAG_ACTIVE;
    return readFragmentAttribsInt(uniqueThreadId, attribID, attribIndex, stream);
}

int readVertexInputDataInt(ptx_thread_info *thread,int builtin_id, unsigned dim_mod){
    unsigned uniqueThreadId = thread->get_uid_in_kernel();
    unsigned attribIndex = dim_mod;
    unsigned attribID;
    void* stream = thread->get_kernel_info()->get_stream();
    assert(builtin_id == VERTEX_ACTIVE); // the only one for now
    attribID = VERT_ACTIVE;
    return readVertexAttribsInt(uniqueThreadId, attribID, attribIndex, stream);
}

unsigned readBufferWidth(){
    return readMESABufferWidth();
}

void ptx_thread_info::set_reg( const symbol *reg, const ptx_reg_t &value ) 
{
   assert( reg != NULL );
   if( reg->name() == "_" ) return;
   assert( !m_regs.empty() );
   assert( reg->uid() > 0 );
   m_regs.back()[ reg ] = value;
   if (m_enable_debug_trace ) 
      m_debug_trace_regs_modified.back()[ reg ] = value;
   m_last_set_operand_value = value;
}

ptx_reg_t ptx_thread_info::get_reg( const symbol *reg )
{
   static bool unfound_register_warned = false;
   assert( reg != NULL );
   assert( !m_regs.empty() );
   reg_map_t::iterator regs_iter = m_regs.back().find(reg);
   if (regs_iter == m_regs.back().end()) {
      assert( reg->type()->get_key().is_reg() );
      const std::string &name = reg->name();
      unsigned call_uid = m_callstack.back().m_call_uid;
      ptx_reg_t uninit_reg;
      uninit_reg.u32 = 0x0;
      set_reg(reg, uninit_reg); // give it a value since we are going to warn the user anyway
      std::string file_loc = get_location();
      if( !unfound_register_warned ) {
          printf("GPGPU-Sim PTX: WARNING (%s) ** reading undefined register \'%s\' (cuid:%u). Setting to 0X00000000. This is okay if you are simulating the native ISA"
        		  "\n",
                 file_loc.c_str(), name.c_str(), call_uid );
          unfound_register_warned = true;
      }
      regs_iter = m_regs.back().find(reg);
   }
   if (m_enable_debug_trace ) 
      m_debug_trace_regs_read.back()[ reg ] = regs_iter->second;
   return regs_iter->second;
}

ptx_reg_t ptx_thread_info::get_operand_value( const operand_info &op, operand_info dstInfo, unsigned opType, ptx_thread_info *thread, int derefFlag )
{
   ptx_reg_t result;


   if(op.get_double_operand_type() == 0) {
      if(((opType != BB128_TYPE) && (opType != BB64_TYPE) && (opType != FF64_TYPE)) || (op.get_addr_space() != undefined_space)) {
         if ( op.is_reg() ) {
            result = get_reg( op.get_symbol() );
         } else if ( op.is_builtin()) {
             //start here
             bool isFloat; float floatValue;
             unsigned unsignedValue = get_builtin( op.get_int(), op.get_addr_offset(),isFloat,floatValue);
             if(isFloat)
                 result.f32=floatValue;
             else result.u32 = unsignedValue;
         } else  if(op.is_immediate_address()){
    		 result.u64 = op.get_addr_offset();
    	 } else if ( op.is_memory_operand() ) {
            // a few options here...
            const symbol *sym = op.get_symbol();
            const type_info *type = sym->type();
            const type_info_key &info = type->get_key();

            if ( info.is_reg() ) {
               const symbol *name = op.get_symbol();
               result.u64 = get_reg(name).u64 + op.get_addr_offset(); 
            } else if ( info.is_param_kernel() ) {
               result.u64 = sym->get_address() + op.get_addr_offset();
            } else if ( info.is_param_local() ) {
               result.u64 = sym->get_address() + op.get_addr_offset();
            } else if ( info.is_global() ) {
               assert( op.get_addr_offset() == 0 );
               result.u64 = sym->get_address();
            } else if ( info.is_local() ) {
               result.u64 = sym->get_address() + op.get_addr_offset();
            } else if ( info.is_const() ) {
               result.u64 = sym->get_address() + op.get_addr_offset();
            } else if ( op.is_shared() ) {
               result.u64 = op.get_symbol()->get_address() + op.get_addr_offset();
            } else {
               const char *name = op.name().c_str();
               printf("GPGPU-Sim PTX: ERROR ** get_operand_value : unknown memory operand type for %s\n", name );
               abort();
            }

         } else if ( op.is_literal() ) {
            result = op.get_literal_value();
         } else if ( op.is_label() ) {
            result.u64 = op.get_symbol()->get_address();
         } else if ( op.is_shared() ) {
            result.u64 = op.get_symbol()->get_address();
         } else if ( op.is_const() ) {
            result.u64 = op.get_symbol()->get_address();
         } else if ( op.is_global() ) {
            result.u64 = op.get_symbol()->get_address();
         } else if ( op.is_local() ) {
            result.u64 = op.get_symbol()->get_address();
         } else {
            const char *name = op.name().c_str();
            printf("GPGPU-Sim PTX: ERROR ** get_operand_value : unknown operand type for %s\n", name );
            assert(0);
         }

         if(op.get_operand_lohi() == 1) 
              result.u64 = result.u64 & 0xFFFF;
         else if(op.get_operand_lohi() == 2) 
              result.u64 = (result.u64>>16) & 0xFFFF;
      } else if (opType == BB128_TYPE) {
          // b128
          result.u128.lowest = get_reg( op.vec_symbol(0) ).u32;
          result.u128.low = get_reg( op.vec_symbol(1) ).u32;
          result.u128.high = get_reg( op.vec_symbol(2) ).u32;
          result.u128.highest = get_reg( op.vec_symbol(3) ).u32;
      } else {
          // bb64 or ff64
          result.bits.ls = get_reg( op.vec_symbol(0) ).u32;
          result.bits.ms = get_reg( op.vec_symbol(1) ).u32;
      }
   } else if (op.get_double_operand_type() == 1) {
      ptx_reg_t firstHalf, secondHalf;
      firstHalf.u64 = get_reg( op.vec_symbol(0) ).u64;
      secondHalf.u64 = get_reg( op.vec_symbol(1) ).u64;
      if(op.get_operand_lohi() == 1)
           secondHalf.u64 = secondHalf.u64 & 0xFFFF;
      else if(op.get_operand_lohi() == 2)
           secondHalf.u64 = (secondHalf.u64>>16) & 0xFFFF;
      result.u64 = firstHalf.u64 + secondHalf.u64;
   } else if (op.get_double_operand_type() == 2) {
      // s[reg1 += reg2]
      // reg1 is incremented after value is returned: the value returned is s[reg1]
      ptx_reg_t firstHalf, secondHalf;
      firstHalf.u64 = get_reg(op.vec_symbol(0)).u64;
      secondHalf.u64 = get_reg(op.vec_symbol(1)).u64;
      if(op.get_operand_lohi() == 1)
           secondHalf.u64 = secondHalf.u64 & 0xFFFF;
      else if(op.get_operand_lohi() == 2)
           secondHalf.u64 = (secondHalf.u64>>16) & 0xFFFF;
      result.u64 = firstHalf.u64;
      firstHalf.u64 = firstHalf.u64 + secondHalf.u64;
      set_reg(op.vec_symbol(0),firstHalf);
   } else if (op.get_double_operand_type() == 3) {
      // s[reg += immediate]
      // reg is incremented after value is returned: the value returned is s[reg]
      ptx_reg_t firstHalf;
      firstHalf.u64 = get_reg(op.get_symbol()).u64;
      result.u64 = firstHalf.u64;
      firstHalf.u64 = firstHalf.u64 + op.get_addr_offset();
      set_reg(op.get_symbol(),firstHalf);
   }

   ptx_reg_t finalResult;
   finalResult.u64=0;

   // @TODO: Joel: This code should only be executed when simulating PTXPlus,
   //        and it should be explored later
   if((op.get_addr_space() == global_space)&&(derefFlag)) {
       printf("GPGPU-Sim PTX: DON'T ACCESS MEMORY (GLOBAL) FOR OPERANDS!\n");
       assert(0);
   } else if((op.get_addr_space() == shared_space)&&(derefFlag)) {
       printf("GPGPU-Sim PTX: DON'T ACCESS MEMORY (SHARED) FOR OPERANDS!\n");
       assert(0);
   } else if((op.get_addr_space() == const_space)&&(derefFlag)) {
       printf("GPGPU-Sim PTX: DON'T ACCESS MEMORY (CONST) FOR OPERANDS!\n");
       assert(0);
   } else if((op.get_addr_space() == local_space)&&(derefFlag)) {
       printf("GPGPU-Sim PTX: DON'T ACCESS MEMORY (LOCAL) FOR OPERANDS!\n");
       assert(0);
   } else {
       finalResult = result;
   }

   if((op.get_operand_neg() == true)&&(derefFlag)) {
      switch( opType ) {
      // Default to f32 for now, need to add support for others
      case S8_TYPE:
      case U8_TYPE:
      case B8_TYPE:
         finalResult.s8 = -finalResult.s8;
         break;
      case S16_TYPE:
      case U16_TYPE:
      case B16_TYPE:
         finalResult.s16 = -finalResult.s16;
         break;
      case S32_TYPE:
      case U32_TYPE:
      case B32_TYPE:
         finalResult.s32 = -finalResult.s32;
         break;
      case S64_TYPE:
      case U64_TYPE:
      case B64_TYPE:
         finalResult.s64 = -finalResult.s64;
         break;
      case F16_TYPE:
         finalResult.f16 = -finalResult.f16;
         break;
      case F32_TYPE:
         finalResult.f32 = -finalResult.f32;
         break;
      case F64_TYPE:
      case FF64_TYPE:
         finalResult.f64 = -finalResult.f64;
         break;
      default:
         assert(0); break;
      }

   }

   return finalResult;

}

unsigned get_operand_nbits( const operand_info &op )
{
   if ( op.is_reg() ) {
      const symbol *sym = op.get_symbol();
      const type_info *typ = sym->type();
      type_info_key t = typ->get_key();
      switch( t.scalar_type() ) {
      case PRED_TYPE:
         return 1;
      case B8_TYPE: case S8_TYPE: case U8_TYPE:
         return 8;
      case S16_TYPE: case U16_TYPE: case F16_TYPE: case B16_TYPE:
         return 16;
      case S32_TYPE: case U32_TYPE: case F32_TYPE: case B32_TYPE:
         return 32;
      case S64_TYPE: case U64_TYPE: case F64_TYPE: case B64_TYPE:
         return 64;
      default:
         printf("ERROR: unknown register type\n");
         fflush(stdout);
         abort(); break;
      }
   } else {
      printf("ERROR: Need to implement get_operand_nbits() for currently unsupported operand_info type\n");
      fflush(stdout);
      abort();
   }

   return 0;
}

void ptx_thread_info::get_vector_operand_values( const operand_info &op, ptx_reg_t* ptx_regs, unsigned num_elements )
{
   assert( op.is_vector() );
   assert( num_elements <= 4 ); // max 4 elements in a vector

   for (int idx = num_elements - 1; idx >= 0; --idx) {
      const symbol *sym = NULL;
      sym = op.vec_symbol(idx);
      if( strcmp(sym->name().c_str(),"_") != 0) {
         reg_map_t::iterator reg_iter = m_regs.back().find(sym);
         assert( reg_iter != m_regs.back().end() );
         ptx_regs[idx] = reg_iter->second;
      }
   }
}

void sign_extend( ptx_reg_t &data, unsigned src_size, const operand_info &dst )
{
   if( !dst.is_reg() )
      return;
   unsigned dst_size = get_operand_nbits( dst );
   if( src_size >= dst_size )
      return;
   // src_size < dst_size
   unsigned long long mask = 1;
   mask <<= (src_size-1);
   if( (mask & data.u64) == 0 ) {
      // no need to sign extend
      return;
   }
   // need to sign extend
   mask = 1;
   mask <<= dst_size-src_size;
   mask -= 1;
   mask <<= src_size;
   data.u64 |= mask;
}

  void ptx_thread_info::set_operand_value( const operand_info &dst, const ptx_reg_t &data, unsigned type, ptx_thread_info *thread, const ptx_instruction *pI, int overflow, int carry )
{
    thread->set_operand_value( dst, data, type, thread, pI );

    if (dst.get_double_operand_type() == -2)
    {
        ptx_reg_t predValue;
        
        const symbol *sym = dst.vec_symbol(0);
        predValue.u64 = (m_regs.back()[ sym ].u64) & ~(0x0C);
        predValue.u64 |= ((overflow & 0x01)<<3);
        predValue.u64 |= ((carry & 0x01)<<2);

        set_reg(sym,predValue);
    }
    else if (dst.get_double_operand_type() == 0)
    {
        //intentionally do nothing
    }
    else
    {
        printf("Unexpected double destination\n");
        assert(0);
    }

}

void ptx_thread_info::set_operand_value( const operand_info &dst, const ptx_reg_t &data, unsigned type, ptx_thread_info *thread, const ptx_instruction *pI )
{
   ptx_reg_t dstData;
   size_t size;
   int t;

   type_info_key::type_decode(type,size,t);

   /*complete this section for other cases*/
   if(dst.get_addr_space() == undefined_space)
   {
      if(dst.is_builtin()){
          writeVertexResultData(dst, data, type, thread, pI );
          return;
      }
      ptx_reg_t setValue;
      setValue.u64 = data.u64;

      // Double destination in set instruction ($p0|$p1) - second is negation of first
      if (dst.get_double_operand_type() == -1)
      {
          ptx_reg_t setValue2;
          const symbol *name1 = dst.vec_symbol(0);
          const symbol *name2 = dst.vec_symbol(1);

          if ( (type==F16_TYPE)||(type==F32_TYPE)||(type==F64_TYPE)||(type==FF64_TYPE) ) {
             setValue2.f32 = (setValue.u64==0)?1.0f:0.0f;
          } else {
             setValue2.u32 = (setValue.u64==0)?0xFFFFFFFF:0;
          }

          set_reg(name1,setValue);
          set_reg(name2,setValue2);
      }

      // Double destination in cvt,shr,mul,etc. instruction ($p0|$r4) - second register operand receives data, first predicate operand
      // is set as $p0=($r4!=0)
      // Also for Double destination in set instruction ($p0/$r1)
      else if ((dst.get_double_operand_type() == -2)||(dst.get_double_operand_type() == -3))
      {
          ptx_reg_t predValue;
          const symbol *predName = dst.vec_symbol(0);
          const symbol *regName = dst.vec_symbol(1);
          predValue.u64 = 0;

          switch ( type ) {
          case S8_TYPE:
              if((setValue.s8 & 0x7F) == 0)
                  predValue.u64 |= 1;
              break;
          case S16_TYPE:
              if((setValue.s16 & 0x7FFF) == 0)
                  predValue.u64 |= 1;
              break;
          case S32_TYPE:
              if((setValue.s32 & 0x7FFFFFFF) == 0)
                  predValue.u64 |= 1;
              break;
          case S64_TYPE:
              if((setValue.s64 & 0x7FFFFFFFFFFFFFFF) == 0)
                  predValue.u64 |= 1;
              break;
          case U8_TYPE:
          case B8_TYPE:
              if(setValue.u8 == 0)
                  predValue.u64 |= 1;
              break;
          case U16_TYPE:
          case B16_TYPE:
              if(setValue.u16 == 0)
                  predValue.u64 |= 1;
              break;
          case U32_TYPE:
          case B32_TYPE:
              if(setValue.u32 == 0)
                  predValue.u64 |= 1;
              break;
          case U64_TYPE:
          case B64_TYPE:
              if(setValue.u64 == 0)
                  predValue.u64 |= 1;
              break;
          case F16_TYPE:
              if(setValue.f16 == 0)
                  predValue.u64 |= 1;
              break;
          case F32_TYPE:
              if(setValue.f32 == 0)
                  predValue.u64 |= 1;
              break;
          case F64_TYPE:
          case FF64_TYPE:
              if(setValue.f64 == 0)
                  predValue.u64 |= 1;
              break;
          default: assert(0); break;
          }


          if ( (type==S8_TYPE)||(type==S16_TYPE)||(type==S32_TYPE)||(type==S64_TYPE)||
               (type==U8_TYPE)||(type==U16_TYPE)||(type==U32_TYPE)||(type==U64_TYPE)||
               (type==B8_TYPE)||(type==B16_TYPE)||(type==B32_TYPE)||(type==B64_TYPE)) {
              if((setValue.u32 & (1<<(size-1))) != 0)
                  predValue.u64 |= 1<<1;
          }
          if ( type==F32_TYPE ) {
              if(setValue.f32 < 0)
                  predValue.u64 |= 1<<1;
          }

          if(dst.get_operand_lohi() == 1)
          {
              setValue.u64 = ((m_regs.back()[ regName ].u64) & (~(0xFFFF))) + (data.u64 & 0xFFFF);
          }
          else if(dst.get_operand_lohi() == 2)
          {
              setValue.u64 = ((m_regs.back()[ regName ].u64) & (~(0xFFFF0000))) + ((data.u64<<16) & 0xFFFF0000);
          }

          set_reg(predName,predValue);
          set_reg(regName,setValue);
      }
      else if (type == BB128_TYPE)
      {
          //b128 stuff here.
          ptx_reg_t setValue2, setValue3, setValue4;
          setValue.u64 = 0;
          setValue2.u64 = 0;
          setValue3.u64 = 0;
          setValue4.u64 = 0;
          setValue.u32 = data.u128.lowest;
          setValue2.u32 = data.u128.low;
          setValue3.u32 = data.u128.high;
          setValue4.u32 = data.u128.highest;

          const symbol *name1, *name2, *name3, *name4 = NULL;

          name1 = dst.vec_symbol(0);
          name2 = dst.vec_symbol(1);
          name3 = dst.vec_symbol(2);
          name4 = dst.vec_symbol(3);

          set_reg(name1,setValue);
          set_reg(name2,setValue2);
          set_reg(name3,setValue3);
          set_reg(name4,setValue4);
      }
      else if (type == BB64_TYPE || type == FF64_TYPE)
      {
          //ptxplus version of storing 64 bit values to registers stores to two adjacent registers
          ptx_reg_t setValue2;
          setValue.u32 = 0;
          setValue2.u32 = 0;

          setValue.u32 = data.bits.ls;
          setValue2.u32 = data.bits.ms;

          const symbol *name1, *name2 = NULL;

          name1 = dst.vec_symbol(0);
          name2 = dst.vec_symbol(1);

          set_reg(name1,setValue);
          set_reg(name2,setValue2);
      }
      else
      {
          if(dst.get_operand_lohi() == 1)
          {
              setValue.u64 = ((m_regs.back()[ dst.get_symbol() ].u64) & (~(0xFFFF))) + (data.u64 & 0xFFFF);
          }
          else if(dst.get_operand_lohi() == 2)
          {
              setValue.u64 = ((m_regs.back()[ dst.get_symbol() ].u64) & (~(0xFFFF0000))) + ((data.u64<<16) & 0xFFFF0000);
          }
          set_reg(dst.get_symbol(),setValue);
      }
   }

   // @TODO: Joel: These should only be executed with PTXPlus simulation, and
   //        this support should be explored later
   // global memory - g[4], g[$r0]
   else if(dst.get_addr_space() == global_space)
   {
       printf("GPGPU-Sim PTX: DON'T ACCESS MEMORY (GLOBAL) FOR SETTING OPERANDS!\n");
       assert(0);
   }

   // shared memory - s[4], s[$r0]
   else if(dst.get_addr_space() == shared_space)
   {
       printf("GPGPU-Sim PTX: DON'T ACCESS MEMORY (SHARED) FOR SETTING OPERANDS!\n");
       assert(0);
   }

   // local memory - l0[4], l0[$r0]
   else if(dst.get_addr_space() == local_space)
   {
       printf("GPGPU-Sim PTX: DON'T ACCESS MEMORY (LOCAL) FOR SETTING OPERANDS!\n");
       assert(0);
   }

   else
   {
       printf("Destination stores to unknown location.");
       assert(0);
   }


}

void ptx_thread_info::set_vector_operand_values( const operand_info &dst, 
                                                 const ptx_reg_t &data1, 
                                                 const ptx_reg_t &data2, 
                                                 const ptx_reg_t &data3, 
                                                 const ptx_reg_t &data4 )
{
   unsigned num_elements = dst.get_vect_nelem(); 
   if (num_elements > 0) {
       set_reg(dst.vec_symbol(0), data1);
       if (num_elements > 1) {
           set_reg(dst.vec_symbol(1), data2);
           if (num_elements > 2) {
              set_reg(dst.vec_symbol(2), data3);
              if (num_elements > 3) {
                 set_reg(dst.vec_symbol(3), data4);
              }
           }
       }
   }

   m_last_set_operand_value = data1;
}

#define my_abs(a) (((a)<0)?(-a):(a))

#define MY_MAX_I(a,b) (a > b) ? a : b
#define MY_MAX_F(a,b) isNaN(a) ? b : isNaN(b) ? a : (a > b) ? a : b

#define MY_MIN_I(a,b) (a < b) ? a : b
#define MY_MIN_F(a,b) isNaN(a) ? b : isNaN(b) ? a : (a < b) ? a : b

#define MY_INC_I(a,b) (a >= b) ? 0 : a+1
#define MY_DEC_I(a,b) ((a == 0) || (a > b)) ? b : a-1

#define MY_CAS_I(a,b,c) (a == b) ? c : a

#define MY_EXCH(a,b) b

void abs_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t a, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);


   switch ( i_type ) {
   case S16_TYPE: d.s16 = my_abs(a.s16); break;
   case S32_TYPE: d.s32 = my_abs(a.s32); break;
   case S64_TYPE: d.s64 = my_abs(a.s64); break;
   case U16_TYPE: d.s16 = my_abs(a.u16); break;
   case U32_TYPE: d.s32 = my_abs(a.u32); break;
   case U64_TYPE: d.s64 = my_abs(a.u64); break;
   case F32_TYPE: d.f32 = my_abs(a.f32); break;
   case F64_TYPE: case FF64_TYPE: d.f64 = my_abs(a.f64); break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0);
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void addp_impl( const ptx_instruction *pI, ptx_thread_info *thread )
{
   //PTXPlus add instruction with carry (carry is kept in a predicate) register
   ptx_reg_t src1_data, src2_data, src3_data, data;
   int overflow = 0;
   int carry = 0;

   const operand_info &dst  = pI->dst();  //get operand info of sources and destination
   const operand_info &src1 = pI->src1(); //use them to determine that they are of type 'register'
   const operand_info &src2 = pI->src2();
   const operand_info &src3 = pI->src3();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);
   src3_data = thread->get_operand_value(src3, dst, i_type, thread, 1);

   unsigned rounding_mode = pI->rounding_mode();
   int orig_rm = fegetround();
   switch ( rounding_mode ) {
   case RN_OPTION: break;
   case RZ_OPTION: fesetround( FE_TOWARDZERO ); break;
   default: assert(0); break;
   }

   //performs addition. Sets carry and overflow if needed.
   //src3_data.pred&0x4 is the carry flag
   switch ( i_type ) {
   case S8_TYPE:
      data.s64 = (src1_data.s64 & 0x0000000FF) + (src2_data.s64 & 0x0000000FF) + (src3_data.pred & 0x4);
      if(((src1_data.s64 & 0x80)-(src2_data.s64 & 0x80)) == 0) {overflow=((src1_data.s64 & 0x80)-(data.s64 & 0x80))==0?0:1; }
      carry = (data.u64 & 0x000000100)>>8;
      break;
   case S16_TYPE:
      data.s64 = (src1_data.s64 & 0x00000FFFF) + (src2_data.s64 & 0x00000FFFF) + (src3_data.pred & 0x4);
      if(((src1_data.s64 & 0x8000)-(src2_data.s64 & 0x8000)) == 0) {overflow=((src1_data.s64 & 0x8000)-(data.s64 & 0x8000))==0?0:1; }
      carry = (data.u64 & 0x000010000)>>16;
      break;
   case S32_TYPE:
      data.s64 = (src1_data.s64 & 0x0FFFFFFFF) + (src2_data.s64 & 0x0FFFFFFFF) + (src3_data.pred & 0x4);
      if(((src1_data.s64 & 0x80000000)-(src2_data.s64 & 0x80000000)) == 0) {overflow=((src1_data.s64 & 0x80000000)-(data.s64 & 0x80000000))==0?0:1; }
      carry = (data.u64 & 0x100000000)>>32;
      break;
   case S64_TYPE:
      data.s64 = src1_data.s64 + src2_data.s64 + (src3_data.pred & 0x4);
      break;
   case U8_TYPE:
      data.u64 = (src1_data.u64 & 0xFF) + (src2_data.u64 & 0xFF) + (src3_data.pred & 0x4);
      carry = (data.u64 & 0x100)>>8;
      break;
   case U16_TYPE:
      data.u64 = (src1_data.u64 & 0xFFFF) + (src2_data.u64 & 0xFFFF) + (src3_data.pred & 0x4);
      carry = (data.u64 & 0x10000)>>16;
      break;
   case U32_TYPE:
      data.u64 = (src1_data.u64 & 0xFFFFFFFF) + (src2_data.u64 & 0xFFFFFFFF) + (src3_data.pred & 0x4);
      carry = (data.u64 & 0x100000000)>>32;
      break;
   case U64_TYPE:
      data.s64 = src1_data.s64 + src2_data.s64 + (src3_data.pred & 0x4);
      break;
   case F16_TYPE: assert(0); break;
   case F32_TYPE: data.f32 = src1_data.f32 + src2_data.f32; break;
   case F64_TYPE: case FF64_TYPE: data.f64 = src1_data.f64 + src2_data.f64; break;
   default: assert(0); break;
   }
   fesetround( orig_rm );

   thread->set_operand_value(dst, data, i_type, thread, pI, overflow, carry  );
}

void add_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t src1_data, src2_data, data;
   int overflow = 0;
   int carry = 0;

   const operand_info &dst  = pI->dst();  //get operand info of sources and destination 
   const operand_info &src1 = pI->src1(); //use them to determine that they are of type 'register'
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);

   unsigned rounding_mode = pI->rounding_mode();
   int orig_rm = fegetround();
   switch ( rounding_mode ) {
   case RN_OPTION: break;
   case RZ_OPTION: fesetround( FE_TOWARDZERO ); break;
   default: assert(0); break;
   }

   //performs addition. Sets carry and overflow if needed.
   switch ( i_type ) {
   case S8_TYPE:
      data.s64 = (src1_data.s64 & 0x0000000FF) + (src2_data.s64 & 0x0000000FF);
      if(((src1_data.s64 & 0x80)-(src2_data.s64 & 0x80)) == 0) {overflow=((src1_data.s64 & 0x80)-(data.s64 & 0x80))==0?0:1; }
      carry = (data.u64 & 0x000000100)>>8;
      break;
   case S16_TYPE:
      data.s64 = (src1_data.s64 & 0x00000FFFF) + (src2_data.s64 & 0x00000FFFF);
      if(((src1_data.s64 & 0x8000)-(src2_data.s64 & 0x8000)) == 0) {overflow=((src1_data.s64 & 0x8000)-(data.s64 & 0x8000))==0?0:1; }
      carry = (data.u64 & 0x000010000)>>16;
      break;
   case S32_TYPE:
      data.s64 = (src1_data.s64 & 0x0FFFFFFFF) + (src2_data.s64 & 0x0FFFFFFFF);
      if(((src1_data.s64 & 0x80000000)-(src2_data.s64 & 0x80000000)) == 0) {overflow=((src1_data.s64 & 0x80000000)-(data.s64 & 0x80000000))==0?0:1; }
      carry = (data.u64 & 0x100000000)>>32;
      break;
   case S64_TYPE:
      data.s64 = src1_data.s64 + src2_data.s64;
      break;
   case U8_TYPE:
      data.u64 = (src1_data.u64 & 0xFF) + (src2_data.u64 & 0xFF);
      carry = (data.u64 & 0x100)>>8;
      break;
   case U16_TYPE:
      data.u64 = (src1_data.u64 & 0xFFFF) + (src2_data.u64 & 0xFFFF);
      carry = (data.u64 & 0x10000)>>16;
      break;
   case U32_TYPE:
      data.u64 = (src1_data.u64 & 0xFFFFFFFF) + (src2_data.u64 & 0xFFFFFFFF);
      carry = (data.u64 & 0x100000000)>>32;
      break;
   case U64_TYPE:
      data.u64 = src1_data.u64 + src2_data.u64;
      break;
   case F16_TYPE: assert(0); break;
   case F32_TYPE: data.f32 = src1_data.f32 + src2_data.f32; break;
   case F64_TYPE: case FF64_TYPE: data.f64 = src1_data.f64 + src2_data.f64; break;
   default: assert(0); break;
   }
   fesetround( orig_rm );

   thread->set_operand_value(dst, data, i_type, thread, pI, overflow, carry  );
}

void addc_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }

void and_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t src1_data, src2_data, data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);


   //the way ptxplus handles predicates: 1 = false and 0 = true
   if(i_type == PRED_TYPE)
      data.pred = ~(~(src1_data.pred) & ~(src2_data.pred));
   else
      data.u64 = src1_data.u64 & src2_data.u64;

   thread->set_operand_value(dst,data, i_type, thread, pI);
}

void andn_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t src1_data, src2_data, data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);

   switch ( i_type ) {
   case B16_TYPE:  src2_data.u16  = ~src2_data.u16; break;
   case B32_TYPE:  src2_data.u32  = ~src2_data.u32; break;
   case B64_TYPE:  src2_data.u64  = ~src2_data.u64; break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0); 
      break;
   }

   data.u64 = src1_data.u64 & src2_data.u64;

   thread->set_operand_value(dst,data, i_type, thread, pI);
}

void atom_callback( const inst_t* inst, ptx_thread_info* thread)
{
   const ptx_instruction *pI = dynamic_cast<const ptx_instruction*>(inst);

   // "Decode" the output type
   unsigned to_type = pI->get_type();
   size_t size;
   int t;
   type_info_key::type_decode(to_type, size, t);

   // Set up operand variables
   ptx_reg_t data;        // d
   ptx_reg_t src1_data;   // a
   ptx_reg_t src2_data;   // b
   ptx_reg_t op_result;   // temp variable to hold operation result

   bool data_ready = false;

   // Get operand info of sources and destination
   const operand_info &dst  = pI->dst();     // d
   const operand_info &src1 = pI->src1();    // a
   const operand_info &src2 = pI->src2();    // b

   // Get operand values
   src1_data = thread->get_operand_value(src1, src1, to_type, thread, 1);        // a
   if (dst.get_symbol()->type()){
      src2_data = thread->get_operand_value(src2, dst, to_type, thread, 1);      // b
   } else {
	   //This is the case whent he first argument (dest) is '_'
      src2_data = thread->get_operand_value(src2, src1, to_type, thread, 1);     // b
   }

   // Check state space
   addr_t effective_address = src1_data.u64;  
   memory_space_t space = pI->get_space();
   if (space == undefined_space) {
      // generic space - determine space via address
      if( whichspace(effective_address) == global_space ) {
         effective_address = generic_to_global(effective_address);
         space = global_space;
      } else if( whichspace(effective_address) == shared_space ) {
         unsigned smid = thread->get_hw_sid();
         effective_address = generic_to_shared(smid,effective_address);
         space = shared_space;
      } else {
         abort();
      }
   } 
   assert( space == global_space || space == shared_space );

   memory_space *mem = NULL;
   if(space == global_space)
       panic("gem5-gpu: Global atomics shouldn't call atom_callback!\n");
   else if(space == shared_space)
       mem = thread->m_shared_mem;
   else
       abort();

   // Copy value pointed to in operand 'a' into register 'd'
   // (i.e. copy src1_data to dst)
   mem->read(effective_address,size/8,&data.s64);
   if (dst.get_symbol()->type()){
	   thread->set_operand_value(dst, data, to_type, thread, pI);                         // Write value into register 'd'
   }

   // Get the atomic operation to be performed
   unsigned m_atomic_spec = pI->get_atomic();

   switch ( m_atomic_spec ) {
   // AND
   case ATOMIC_AND:
      {

         switch ( to_type ) {
         case B32_TYPE:
         case U32_TYPE:
            op_result.u32 = data.u32 & src2_data.u32;
            data_ready = true;
            break;
         case S32_TYPE:
            op_result.s32 = data.s32 & src2_data.s32;
            data_ready = true;
            break;
         default:
            printf("Execution error: type mismatch (%x) with instruction\natom.AND only accepts b32\n", to_type);
            assert(0);
            break;
         }

         break;
      }
      // OR
   case ATOMIC_OR:
      {

         switch ( to_type ) {
         case B32_TYPE:
         case U32_TYPE:
            op_result.u32 = data.u32 | src2_data.u32;
            data_ready = true;
            break;
         case S32_TYPE:
            op_result.s32 = data.s32 | src2_data.s32;
            data_ready = true;
            break;
         default:
            printf("Execution error: type mismatch (%x) with instruction\natom.OR only accepts b32\n", to_type);
            assert(0);
            break;
         }

         break;
      }
      // XOR
   case ATOMIC_XOR:
      {

         switch ( to_type ) {
         case B32_TYPE:
         case U32_TYPE:
            op_result.u32 = data.u32 ^ src2_data.u32;
            data_ready = true;
            break;
         case S32_TYPE:
            op_result.s32 = data.s32 ^ src2_data.s32;
            data_ready = true;
            break;
         default:
            printf("Execution error: type mismatch (%x) with instruction\natom.XOR only accepts b32\n", to_type);
            assert(0);
            break;
         }

         break;
      }
      // CAS
   case ATOMIC_CAS:
      {

         ptx_reg_t src3_data;
         const operand_info &src3 = pI->src3();
         src3_data = thread->get_operand_value(src3, dst, to_type, thread, 1);

         switch ( to_type ) {
         case B32_TYPE:
         case U32_TYPE:
            op_result.u32 = MY_CAS_I(data.u32, src2_data.u32, src3_data.u32);
            data_ready = true;
            break;
         case B64_TYPE:
         case U64_TYPE:
            op_result.u64 = MY_CAS_I(data.u64, src2_data.u64, src3_data.u64);
            data_ready = true;
            break;
         case S32_TYPE:
            op_result.s32 = MY_CAS_I(data.s32, src2_data.s32, src3_data.s32);
            data_ready = true;
            break;
         default:
            printf("Execution error: type mismatch (%x) with instruction\natom.CAS only accepts b32 and b64\n", to_type);
            assert(0);
            break;
         }

         break;
      }
      // EXCH
   case ATOMIC_EXCH:
      {
         switch ( to_type ) {
         case B32_TYPE:
         case U32_TYPE:
            op_result.u32 = MY_EXCH(data.u32, src2_data.u32);
            data_ready = true;
            break;
         case B64_TYPE:
         case U64_TYPE:
            op_result.u64 = MY_EXCH(data.u64, src2_data.u64);
            data_ready = true;
            break;
         case S32_TYPE:
            op_result.s32 = MY_EXCH(data.s32, src2_data.s32);
            data_ready = true;
            break;
         default:
            printf("Execution error: type mismatch (%x) with instruction\natom.EXCH only accepts b32\n", to_type);
            assert(0);
            break;
         }

         break;
      }
      // ADD
   case ATOMIC_ADD:
      {

         switch ( to_type ) {
         case U32_TYPE:
            op_result.u32 = data.u32 + src2_data.u32;
            data_ready = true;
            break;
         case S32_TYPE:
            op_result.s32 = data.s32 + src2_data.s32;
            data_ready = true;
            break;
         case U64_TYPE: 
            op_result.u64 = data.u64 + src2_data.u64; 
            data_ready = true; 
            break; 
         case F32_TYPE: 
            op_result.f32 = data.f32 + src2_data.f32; 
            data_ready = true; 
            break; 
         default:
            printf("Execution error: type mismatch with instruction\natom.ADD only accepts u32, s32, u64, and f32\n");
            assert(0);
            break;
         }

         break;
      }
      // INC
   case ATOMIC_INC:
      {
         switch ( to_type ) {
         case U32_TYPE: 
            op_result.u32 = MY_INC_I(data.u32, src2_data.u32);
            data_ready = true;
            break;
         default:
            printf("Execution error: type mismatch with instruction\natom.INC only accepts u32 and s32\n");
            assert(0);
            break;
         }

         break;
      }
      // DEC
   case ATOMIC_DEC:
      {
         switch ( to_type ) {
         case U32_TYPE: 
            op_result.u32 = MY_DEC_I(data.u32, src2_data.u32);
            data_ready = true;
            break;
         default:
            printf("Execution error: type mismatch with instruction\natom.DEC only accepts u32 and s32\n");
            assert(0);
            break;
         }

         break;
      }
      // MIN
   case ATOMIC_MIN:
      {
         switch ( to_type ) {
         case U32_TYPE: 
            op_result.u32 = MY_MIN_I(data.u32, src2_data.u32);
            data_ready = true;
            break;
         case S32_TYPE:
            op_result.s32 = MY_MIN_I(data.s32, src2_data.s32);
            data_ready = true;
            break;
         default:
            printf("Execution error: type mismatch with instruction\natom.MIN only accepts u32 and s32\n");
            assert(0);
            break;
         }

         break;
      }
      // MAX
   case ATOMIC_MAX:
      {
         switch ( to_type ) {
         case U32_TYPE:
            op_result.u32 = MY_MAX_I(data.u32, src2_data.u32);
            data_ready = true;
            break;
         case S32_TYPE:
            op_result.s32 = MY_MAX_I(data.s32, src2_data.s32);
            data_ready = true;
            break;
         default:
            printf("Execution error: type mismatch with instruction\natom.MAX only accepts u32 and s32\n");
            assert(0);
            break;
         }

         break;
      }
      // DEFAULT
   default:
      {
         assert(0);
         break;
      }
   }

   // Write operation result into  memory
   // (i.e. copy src1_data to dst)
   if ( data_ready ) {
      mem->write(effective_address,size/8,&op_result.s64,thread,pI);
   } else {
      printf("Execution error: data_ready not set\n");
      assert(0);
   }
}

// atom_impl will now result in a callback being called in mem_ctrl_pop (gpu-sim.c)
void atom_impl( const ptx_instruction *pI, ptx_thread_info *thread )
{   
   // SYNTAX
   // atom.space.operation.type d, a, b[, c]; (now read in callback)

   // obtain memory space of the operation 
   memory_space_t space = pI->get_space(); 

   // get the memory address
   const operand_info &src1 = pI->src1();
   // const operand_info &dst  = pI->dst();  // not needed for effective address calculation 
   unsigned i_type = pI->get_type();
   ptx_reg_t src1_data;
   src1_data = thread->get_operand_value(src1, src1, i_type, thread, 1);
   addr_t effective_address = src1_data.u64; 

   addr_t effective_address_final; 

   // handle generic memory space by converting it to global 
   if ( space == undefined_space ) {
      if( whichspace(effective_address) == global_space ) {
         effective_address_final = generic_to_global(effective_address);
         space = global_space;
      } else if( whichspace(effective_address) == shared_space ) {
         unsigned smid = thread->get_hw_sid();
         effective_address_final = generic_to_shared(smid,effective_address);
         space = shared_space;
      } else {
         abort();
      }
   } else {
      assert( space == global_space || space == shared_space );
      effective_address_final = effective_address; 
   }

   // Check state space
   assert( space == global_space || space == shared_space );

   thread->m_last_effective_address.set(effective_address_final);
   thread->m_last_memory_space = space;
   thread->m_last_dram_callback.function = atom_callback;
   thread->m_last_dram_callback.instruction = pI; 
}

void bar_sync_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   const operand_info &dst  = pI->dst();
   ptx_reg_t b = thread->get_operand_value(dst, dst, U32_TYPE, thread, 1);
   assert( b.u32 == 0 ); // support for bar.sync a{,b}; where a != 0 not yet implemented
}

void bfe_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void bfi_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void bfind_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }

void bra_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   const operand_info &target  = pI->dst();
   ptx_reg_t target_pc = thread->get_operand_value(target, target, U32_TYPE, thread, 1);

   thread->m_branch_taken = true;
   thread->set_npc(target_pc);
}

void brx_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   const operand_info &target  = pI->dst();
   ptx_reg_t target_pc = thread->get_operand_value(target, target, U32_TYPE, thread, 1);

   thread->m_branch_taken = true;
   thread->set_npc(target_pc);
}

void break_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   const operand_info &target  = thread->pop_breakaddr();
   ptx_reg_t target_pc = thread->get_operand_value(target, target, U32_TYPE, thread, 1);

   thread->m_branch_taken = true;
   thread->set_npc(target_pc);
}

void breakaddr_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   const operand_info &target  = pI->dst();
   thread->push_breakaddr(target);
   assert(pI->has_pred() == false); // pdom analysis cannot handle if this instruction is predicated 
}

void brev_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void brkpt_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }

void call_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   static unsigned call_uid_next = 1;
    
   const operand_info &target  = pI->func_addr();
   assert( target.is_function_address() );
   const symbol *func_addr = target.get_symbol();
   const function_info *target_func = func_addr->get_pc();

   // check that number of args and return match function requirements
   if( pI->has_return() ^ target_func->has_return() ) {
      printf("GPGPU-Sim PTX: Execution error - mismatch in number of return values between\n"
             "               call instruction and function declaration\n");
      abort(); 
   }
   unsigned n_return = target_func->has_return();
   unsigned n_args = target_func->num_args();
   unsigned n_operands = pI->get_num_operands();

   if( n_operands != (n_return+1+n_args) ) {
      printf("GPGPU-Sim PTX: Execution error - mismatch in number of arguements between\n"
             "               call instruction and function declaration\n");
      abort(); 
   }

   // handle intrinsic functions
   std::string fname = target_func->get_name();
   if( fname == "vprintf" ) {
      gpgpusim_cuda_vprintf(pI, thread, target_func);
      return;
   } 

   // read source arguements into register specified in declaration of function
   arg_buffer_list_t arg_values;
   copy_args_into_buffer_list(pI, thread, target_func, arg_values);

   // record local for return value (we only support a single return value)
   const symbol *return_var_src = NULL;
   const symbol *return_var_dst = NULL;
   if( target_func->has_return() ) {
      return_var_dst = pI->dst().get_symbol();
      return_var_src = target_func->get_return_var();
   }

   gpgpu_sim *gpu = thread->get_gpu();
   unsigned callee_pc=0, callee_rpc=0;
   if( gpu->simd_model() == POST_DOMINATOR ) {
      thread->get_core()->get_pdom_stack_top_info(thread->get_hw_wid(),&callee_pc,&callee_rpc);
      assert( callee_pc == thread->get_pc() );
   }

   thread->callstack_push(callee_pc + pI->inst_size(), callee_rpc, return_var_src, return_var_dst, call_uid_next++);

   copy_buffer_list_into_frame(thread, arg_values);

   thread->set_npc(target_func);
}

//Ptxplus version of call instruction. Jumps to a label not a different Kernel.
void callp_impl( const ptx_instruction *pI, ptx_thread_info *thread )
{
   
   static unsigned call_uid_next = 1;

   const operand_info &target  = pI->dst();
   ptx_reg_t target_pc = thread->get_operand_value(target, target, U32_TYPE, thread, 1);

   const symbol *return_var_src = NULL;
   const symbol *return_var_dst = NULL;

   gpgpu_sim *gpu = thread->get_gpu();
   unsigned callee_pc=0, callee_rpc=0;
   if( gpu->simd_model() == POST_DOMINATOR ) {
      thread->get_core()->get_pdom_stack_top_info(thread->get_hw_wid(),&callee_pc,&callee_rpc);
      assert( callee_pc == thread->get_pc() );
   } 

   thread->callstack_push_plus(callee_pc + pI->inst_size(), callee_rpc, return_var_src, return_var_dst, call_uid_next++);
   thread->set_npc(target_pc);
}

void clz_impl( const ptx_instruction *pI, ptx_thread_info *thread )
{
   ptx_reg_t a, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);

   int max = 0;
   unsigned long long mask = 0;
   d.u64 = 0;

   switch ( i_type ) {
   case B32_TYPE:
      max = 32;
      mask = 0x80000000;
      break;
   case B64_TYPE:
      max = 64;
      mask = 0x8000000000000000;
      break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0);
      break;
   }

   while ((d.u32 < max) && ((a.u64&mask) == 0) ) {
      d.u32++;
      a.u64 = a.u64 << 1;
   }

   thread->set_operand_value(dst,d, B32_TYPE, thread, pI);
}

void cnot_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t a, b, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);

   switch ( i_type ) {
   case PRED_TYPE: d.pred = ((a.pred & 0x0001) == 0)?1:0; break;
   case B16_TYPE:  d.u16  = (a.u16  == 0)?1:0; break;
   case B32_TYPE:  d.u32  = (a.u32  == 0)?1:0; break;
   case B64_TYPE:  d.u64  = (a.u64  == 0)?1:0; break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0);
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void cos_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ptx_reg_t a, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);


   switch ( i_type ) {
   case F32_TYPE: 
      d.f32 = cos(a.f32);
      break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0); 
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

ptx_reg_t chop( ptx_reg_t x, unsigned from_width, unsigned to_width, int to_sign, int rounding_mode, int saturation_mode )
{
   switch ( to_width ) {
   case 8:  x.mask_and(0,0xFF);  break;
   case 16: x.mask_and(0,0xFFFF);      break;
   case 32: x.mask_and(0,0xFFFFFFFF);  break;
   case 64: break;
   default: assert(0); break;
   }
   return x;
}

ptx_reg_t sext( ptx_reg_t x, unsigned from_width, unsigned to_width, int to_sign, int rounding_mode, int saturation_mode )
{
   x=chop(x,0,from_width,0,rounding_mode,saturation_mode);
   switch ( from_width ) {
   case 8: if ( x.get_bit(7) ) x.mask_or(0xFFFFFFFF,0xFFFFFF00);break;
   case 16:if ( x.get_bit(15) ) x.mask_or(0xFFFFFFFF,0xFFFF0000);break;
   case 32: if ( x.get_bit(31) ) x.mask_or(0xFFFFFFFF,0x00000000);break;
   case 64: break;
   default: assert(0); break;
   }
   return x;
}

// sign extend depending on the destination register size - hack to get SobelFilter working in CUDA 4.2
ptx_reg_t sexd( ptx_reg_t x, unsigned from_width, unsigned to_width, int to_sign, int rounding_mode, int saturation_mode )
{
   x=chop(x,0,from_width,0,rounding_mode,saturation_mode);
   switch ( to_width ) {
   case 8: if ( x.get_bit(7) ) x.mask_or(0xFFFFFFFF,0xFFFFFF00);break;
   case 16:if ( x.get_bit(15) ) x.mask_or(0xFFFFFFFF,0xFFFF0000);break;
   case 32: if ( x.get_bit(31) ) x.mask_or(0xFFFFFFFF,0x00000000);break;
   case 64: break;
   default: assert(0);
   }
   return x;
}

ptx_reg_t zext( ptx_reg_t x, unsigned from_width, unsigned to_width, int to_sign, int rounding_mode, int saturation_mode )
{
   return chop(x,0,from_width,0,rounding_mode,saturation_mode);
}

int saturatei(int a, int max, int min) 
{
   if (a > max) a = max;
   else if (a < min) a = min;
   return a;
}

unsigned int saturatei(unsigned int a, unsigned int max) 
{
   if (a > max) a = max;
   return a;
}

ptx_reg_t f2x( ptx_reg_t x, unsigned from_width, unsigned to_width, int to_sign, int rounding_mode, int saturation_mode )
{
   assert( from_width == 32); 

   enum cuda_math::cudaRoundMode mode = cuda_math::cudaRoundZero;
   switch (rounding_mode) {
   case RZI_OPTION: mode = cuda_math::cudaRoundZero;    break;
   case RNI_OPTION: mode = cuda_math::cudaRoundNearest; break;
   case RMI_OPTION: mode = cuda_math::cudaRoundMinInf;  break;
   case RPI_OPTION: mode = cuda_math::cudaRoundPosInf;  break;
   default: break; 
   }

   ptx_reg_t y;
   if ( to_sign == 1 ) { // convert to 64-bit number first?
      int tmp = cuda_math::float2int(x.f32, mode);
      if ((x.u32 & 0x7f800000) == 0)
         tmp = 0; // round denorm. FP to 0
      if (saturation_mode && to_width < 32) {
         tmp = saturatei(tmp, (1<<to_width) - 1, -(1<<to_width));
      }
      switch ( to_width ) {
      case 8:  y.s8  = (char)tmp; break;
      case 16: y.s16 = (short)tmp; break;
      case 32: y.s32 = (int)tmp; break;
      case 64: y.s64 = (long long)tmp; break;
      default: assert(0); break;
      }
   } else if ( to_sign == 0 ) {
      unsigned int tmp = cuda_math::float2uint(x.f32, mode);
      if ((x.u32 & 0x7f800000) == 0)
         tmp = 0; // round denorm. FP to 0
      if (saturation_mode && to_width < 32) {
         tmp = saturatei(tmp, (1<<to_width) - 1);
      }
      switch ( to_width ) {
      case 8:  y.u8  = (unsigned char)tmp; break;
      case 16: y.u16 = (unsigned short)tmp; break;
      case 32: y.u32 = (unsigned int)tmp; break;
      case 64: y.u64 = (unsigned long long)tmp; break;
      default: assert(0); break;
      }
   } else {
      switch ( to_width ) {
      case 16: assert(0); break;
      case 32: assert(0); break; // handled by f2f
      case 64: 
         y.f64 = x.f32; 
         break;
      default: assert(0); break;
      }
   }
   return y;
}

double saturated2i (double a, double max, double min) {
   if (a > max) a = max;
   else if (a < min) a = min;
   return a;
}

ptx_reg_t d2x( ptx_reg_t x, unsigned from_width, unsigned to_width, int to_sign, int rounding_mode, int saturation_mode )
{
   assert( from_width == 64); 

   double tmp;
   switch (rounding_mode) {
   case RZI_OPTION: tmp = trunc(x.f64);     break;
   case RNI_OPTION: tmp = nearbyint(x.f64); break;
   case RMI_OPTION: tmp = floor(x.f64);     break;
   case RPI_OPTION: tmp = ceil(x.f64);      break;
   default: tmp = x.f64; break; 
   }

   ptx_reg_t y;
   if ( to_sign == 1 ) {
      tmp = saturated2i(tmp, ((1<<(to_width - 1)) - 1), (1<<(to_width - 1)) );
      switch ( to_width ) {
      case 8:  y.s8  = (char)tmp; break;
      case 16: y.s16 = (short)tmp; break;
      case 32: y.s32 = (int)tmp; break;
      case 64: y.s64 = (long long)tmp; break;
      default: assert(0); break;
      }
   } else if ( to_sign == 0 ) {
      tmp = saturated2i(tmp, ((1<<(to_width - 1)) - 1), 0);
      switch ( to_width ) {
      case 8:  y.u8  = (unsigned char)tmp; break;
      case 16: y.u16 = (unsigned short)tmp; break;
      case 32: y.u32 = (unsigned int)tmp; break;
      case 64: y.u64 = (unsigned long long)tmp; break;
      default: assert(0); break;
      }
   } else {
      switch ( to_width ) {
      case 16: assert(0); break;
      case 32:
         y.f32 = x.f64;  
         break;
      case 64: 
         y.f64 = x.f64; // should be handled by d2d
         break;
      default: assert(0); break;
      }
   }
   return y;
}

ptx_reg_t s2f( ptx_reg_t x, unsigned from_width, unsigned to_width, int to_sign, int rounding_mode, int saturation_mode )
{
   ptx_reg_t y;

   if (from_width < 64) { // 32-bit conversion
      y = sext(x,from_width,32,0,rounding_mode,saturation_mode);

      switch ( to_width ) {
      case 16: assert(0); break;
      case 32: 
         switch (rounding_mode) {
         case RZ_OPTION: y.f32 = cuda_math::__int2float_rz(y.s32); break;
         case RN_OPTION: y.f32 = cuda_math::__int2float_rn(y.s32); break;
         case RM_OPTION: y.f32 = cuda_math::__int2float_rd(y.s32); break;
         case RP_OPTION: y.f32 = cuda_math::__int2float_ru(y.s32); break;
         default: break; 
         }
         break;
      case 64: y.f64 = y.s32; break; // no rounding needed
      default: assert(0); break;
      }
   } else {
      switch ( to_width ) {
      case 16: assert(0); break;
      case 32: 
         switch (rounding_mode) {
         case RZ_OPTION: y.f32 = cuda_math::__ll2float_rz(y.s64); break; 
         case RN_OPTION: y.f32 = cuda_math::__ll2float_rn(y.s64); break;
         case RM_OPTION: y.f32 = cuda_math::__ll2float_rd(y.s64); break; 
         case RP_OPTION: y.f32 = cuda_math::__ll2float_ru(y.s64); break;
         default: break; 
         }
         break;
      case 64: y.f64 = y.s64; break; // no internal implementation found
      default: assert(0); break;
      }
   }

   // saturating an integer to 1 or 0?
   return y;
}

ptx_reg_t u2f( ptx_reg_t x, unsigned from_width, unsigned to_width, int to_sign, int rounding_mode, int saturation_mode )
{
   ptx_reg_t y;

   if (from_width < 64) { // 32-bit conversion
      y = zext(x,from_width,32,0,rounding_mode,saturation_mode);

      switch ( to_width ) {
      case 16: assert(0); break;
      case 32: 
         switch (rounding_mode) {
         case RZ_OPTION: y.f32 = cuda_math::__uint2float_rz(y.u32); break;
         case RN_OPTION: y.f32 = cuda_math::__uint2float_rn(y.u32); break;
         case RM_OPTION: y.f32 = cuda_math::__uint2float_rd(y.u32); break;
         case RP_OPTION: y.f32 = cuda_math::__uint2float_ru(y.u32); break;
         default: break; 
         }
         break;
      case 64: y.f64 = y.u32; break; // no rounding needed
      default: assert(0); break;
      }
   } else {
      switch ( to_width ) {
      case 16: assert(0); break;
      case 32: 
         switch (rounding_mode) {
         case RZ_OPTION: y.f32 = cuda_math::__ull2float_rn(y.u64); break; 
         case RN_OPTION: y.f32 = cuda_math::__ull2float_rn(y.u64); break;
         case RM_OPTION: y.f32 = cuda_math::__ull2float_rn(y.u64); break; 
         case RP_OPTION: y.f32 = cuda_math::__ull2float_rn(y.u64); break; 
         default: break; 
         }
         break;
      case 64: y.f64 = y.u64; break; // no internal implementation found
      default: assert(0); break;
      }
   }

   // saturating an integer to 1 or 0?
   return y;
}

ptx_reg_t f2f( ptx_reg_t x, unsigned from_width, unsigned to_width, int to_sign, int rounding_mode, int saturation_mode )
{
   ptx_reg_t y;
   switch ( rounding_mode ) {
   case RZI_OPTION: 
      y.f32 = truncf(x.f32); 
      break;          
   case RNI_OPTION: 
#if CUDART_VERSION >= 3000
      y.f32 = nearbyintf(x.f32); 
#else
      y.f32 = cuda_math::__internal_nearbyintf(x.f32); 
#endif
      break;          
   case RMI_OPTION: 
      if ((x.u32 & 0x7f800000) == 0) {
         y.u32 = x.u32 & 0x80000000; // round denorm. FP to 0, keeping sign
      } else {
         y.f32 = floorf(x.f32); 
      }
      break;          
   case RPI_OPTION: 
      if ((x.u32 & 0x7f800000) == 0) {
         y.u32 = x.u32 & 0x80000000; // round denorm. FP to 0, keeping sign
      } else {
         y.f32 = ceilf(x.f32); 
      }
      break;          
   default: 
      if ((x.u32 & 0x7f800000) == 0) {
         y.u32 = x.u32 & 0x80000000; // round denorm. FP to 0, keeping sign
      } else {
         y.f32 = x.f32;
      }
      break; 
   }
#if CUDART_VERSION >= 3000
   if (isnanf(y.f32)) 
#else
   if (cuda_math::__cuda___isnanf(y.f32)) 
#endif
   {
      y.u32 = 0x7fffffff;
   } else if (saturation_mode) {
      y.f32 = cuda_math::__saturatef(y.f32);
   }

   return y;
}

ptx_reg_t d2d( ptx_reg_t x, unsigned from_width, unsigned to_width, int to_sign, int rounding_mode, int saturation_mode )
{
   ptx_reg_t y;
   switch ( rounding_mode ) {
   case RZI_OPTION: 
      y.f64 = trunc(x.f64); 
      break;          
   case RNI_OPTION: 
#if CUDART_VERSION >= 3000
      y.f64 = nearbyint(x.f64); 
#else
      y.f64 = cuda_math::__internal_nearbyintf(x.f64); 
#endif
      break;          
   case RMI_OPTION: 
      y.f64 = floor(x.f64); 
      break;          
   case RPI_OPTION: 
      y.f64 = ceil(x.f64); 
      break;          
   default: 
      y.f64 = x.f64;
      break; 
   }
   if (isnan(y.f64)) {
      y.u64 = 0xfff8000000000000ull;
   } else if (saturation_mode) {
      y.f64 = cuda_math::__saturatef(y.f64); 
   }
   return y;
}

ptx_reg_t (*g_cvt_fn[11][11])( ptx_reg_t x, unsigned from_width, unsigned to_width, int to_sign, 
                               int rounding_mode, int saturation_mode ) = {
   { NULL, sext, sext, sext, NULL, sext, sext, sext, s2f, s2f, s2f}, 
   { chop, NULL, sext, sext, chop, NULL, sext, sext, s2f, s2f, s2f}, 
   { chop, sexd, NULL, sext, chop, chop, NULL, sext, s2f, s2f, s2f}, 
   { chop, chop, chop, NULL, chop, chop, chop, NULL, s2f, s2f, s2f}, 
   { NULL, zext, zext, zext, NULL, zext, zext, zext, u2f, u2f, u2f}, 
   { chop, NULL, zext, zext, chop, NULL, zext, zext, u2f, u2f, u2f}, 
   { chop, chop, NULL, zext, chop, chop, NULL, zext, u2f, u2f, u2f}, 
   { chop, chop, chop, NULL, chop, chop, chop, NULL, u2f, u2f, u2f}, 
   { f2x , f2x , f2x , f2x , f2x , f2x , f2x , f2x , NULL,f2x, f2x}, 
   { f2x , f2x , f2x , f2x , f2x , f2x , f2x , f2x , f2x, f2f, f2x},
   { d2x , d2x , d2x , d2x , d2x , d2x , d2x , d2x , d2x, d2x, d2d} 
};

void ptx_round(ptx_reg_t& data, int rounding_mode, int type)
{
   if (rounding_mode == RN_OPTION) {
      return;
   }
   switch ( rounding_mode ) {
   case RZI_OPTION: 
      switch ( type ) {
      case S8_TYPE:
      case S16_TYPE:
      case S32_TYPE:
      case S64_TYPE:
      case U8_TYPE:
      case U16_TYPE:
      case U32_TYPE:
      case U64_TYPE:
         printf("Trying to round an integer??\n"); assert(0); break;
      case F16_TYPE: assert(0); break;
      case F32_TYPE:
         data.f32 = truncf(data.f32); 
         break;          
      case F64_TYPE:
      case FF64_TYPE:
         if (data.f64 < 0) data.f64 = ceil(data.f64); //negative
         else data.f64 = floor(data.f64); //positive
         break; 
      default: assert(0); break;
      }
      break;
   case RNI_OPTION: 
      switch ( type ) {
      case S8_TYPE:
      case S16_TYPE:
      case S32_TYPE:
      case S64_TYPE:
      case U8_TYPE:
      case U16_TYPE:
      case U32_TYPE:
      case U64_TYPE:
         printf("Trying to round an integer??\n"); assert(0); break;
      case F16_TYPE: assert(0); break;
      case F32_TYPE: 
#if CUDART_VERSION >= 3000
         data.f32 = nearbyintf(data.f32); 
#else
         data.f32 = cuda_math::__cuda_nearbyintf(data.f32); 
#endif
         break;          
      case F64_TYPE: case FF64_TYPE: data.f64 = round(data.f64); break; 
      default: assert(0); break;
      }
      break;
   case RMI_OPTION: 
      switch ( type ) {
      case S8_TYPE:
      case S16_TYPE:
      case S32_TYPE:
      case S64_TYPE:
      case U8_TYPE:
      case U16_TYPE:
      case U32_TYPE:
      case U64_TYPE:
         printf("Trying to round an integer??\n"); assert(0); break;
      case F16_TYPE: assert(0); break;
      case F32_TYPE: 
         data.f32 = floorf(data.f32); 
         break;          
      case F64_TYPE: case FF64_TYPE: data.f64 = floor(data.f64); break; 
      default: assert(0); break;
      }
      break;
   case RPI_OPTION: 
      switch ( type ) {
      case S8_TYPE:
      case S16_TYPE:
      case S32_TYPE:
      case S64_TYPE:
      case U8_TYPE:
      case U16_TYPE:
      case U32_TYPE:
      case U64_TYPE:
         printf("Trying to round an integer??\n"); assert(0); break;
      case F16_TYPE: assert(0); break;
      case F32_TYPE: data.f32 = ceilf(data.f32); break;          
      case F64_TYPE: case FF64_TYPE: data.f64 = ceil(data.f64); break; 
      default: assert(0); break;
      }
      break;
   default:  break; 
   }

   if (type == F32_TYPE) {
#if CUDART_VERSION >= 3000
      if (isnanf(data.f32)) 
#else
      if (cuda_math::__cuda___isnanf(data.f32)) 
#endif
      {
         data.u32 = 0x7fffffff;
      }
   }
   if ((type == F64_TYPE)||(type == FF64_TYPE)) {
      if (isnan(data.f64)) {
         data.u64 = 0xfff8000000000000ull;
      }
   }
}

void ptx_saturate(ptx_reg_t& data, int saturation_mode, int type)
{
   if (!saturation_mode) {
      return;
   }
   switch ( type ) {
   case S8_TYPE:
   case S16_TYPE:
   case S32_TYPE:
   case S64_TYPE:
   case U8_TYPE:
   case U16_TYPE:
   case U32_TYPE:
   case U64_TYPE:
      printf("Trying to clamp an integer to 1??\n"); assert(0); break;
   case F16_TYPE: assert(0); break;
   case F32_TYPE:
      if (data.f32 > 1.0f) data.f32 = 1.0f; //negative
      if (data.f32 < 0.0f) data.f32 = 0.0f; //positive
      break;          
   case F64_TYPE:
   case FF64_TYPE:
      if (data.f64 > 1.0f) data.f64 = 1.0f; //negative
      if (data.f64 < 0.0f) data.f64 = 0.0f; //positive
      break; 
   default: assert(0); break;
   }

}

void cvt_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   unsigned to_type = pI->get_type();
   unsigned from_type = pI->get_type2();
   unsigned rounding_mode = pI->rounding_mode();
   unsigned saturation_mode = pI->saturation_mode();

   if ( to_type == F16_TYPE || from_type == F16_TYPE )
      abort();

   int to_sign, from_sign;
   size_t from_width, to_width;
   unsigned src_fmt = type_info_key::type_decode(from_type, from_width, from_sign);
   unsigned dst_fmt = type_info_key::type_decode(to_type, to_width, to_sign);

   ptx_reg_t data = thread->get_operand_value(src1, dst, from_type, thread, 1);

   if(pI->is_neg()){

   switch( from_type ) {
      // Default to f32 for now, need to add support for others
      case S8_TYPE:
      case U8_TYPE:
      case B8_TYPE:
         data.s8 = -data.s8;
         break;
      case S16_TYPE:
      case U16_TYPE:
      case B16_TYPE:
         data.s16 = -data.s16;
         break;
      case S32_TYPE:
      case U32_TYPE:
      case B32_TYPE:
         data.s32 = -data.s32;
         break;
      case S64_TYPE:
      case U64_TYPE:
      case B64_TYPE:
         data.s64 = -data.s64;
         break;
      case F16_TYPE:
         data.f16 = -data.f16;
         break;
      case F32_TYPE:
         data.f32 = -data.f32;
         break;
      case F64_TYPE:
      case FF64_TYPE:
         data.f64 = -data.f64;
         break;
      default:
         assert(0); break;
      }

   }


   if ( g_cvt_fn[src_fmt][dst_fmt] != NULL ) {
      ptx_reg_t result = g_cvt_fn[src_fmt][dst_fmt](data,from_width,to_width,to_sign, rounding_mode, saturation_mode);
      data = result;
   }

   thread->set_operand_value(dst, data, to_type, thread, pI );
}

void cvta_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   memory_space_t space = pI->get_space();
   bool to_non_generic = pI->is_to();

   unsigned i_type = pI->get_type();
   ptx_reg_t from_addr = thread->get_operand_value(src1,dst,i_type,thread,1);
   addr_t from_addr_hw = (addr_t)from_addr.u64;
   addr_t to_addr_hw = 0;
   unsigned smid = thread->get_hw_sid();
   unsigned hwtid = thread->get_hw_tid();

   if( to_non_generic ) {
      switch( space.get_type() ) {
      case shared_space: to_addr_hw = generic_to_shared( smid, from_addr_hw ); break;
      case local_space:  to_addr_hw = generic_to_local( smid, hwtid, from_addr_hw ); break;
      case global_space: to_addr_hw = generic_to_global(from_addr_hw ); break;
      default: abort(); break;
      }
   } else {
      switch( space.get_type() ) {
      case shared_space: to_addr_hw = shared_to_generic( smid, from_addr_hw ); break;
      case local_space:  to_addr_hw =  local_to_generic( smid, hwtid, from_addr_hw )
                                      + thread->get_local_mem_stack_pointer(); break; // add stack ptr here so that it can be passed as a pointer at function call 
      case global_space: to_addr_hw = global_to_generic( from_addr_hw ); break;
      default: abort(); break;
      }
   }
   
   ptx_reg_t to_addr;
   to_addr.u64 = to_addr_hw;
   thread->set_reg(dst.get_symbol(),to_addr);
}

void div_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();

   ptx_reg_t src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   ptx_reg_t src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);


   switch ( i_type ) {
   case S8_TYPE:
      data.s8  = src1_data.s8  / src2_data.s8 ; break;
   case S16_TYPE:
      data.s16 = src1_data.s16 / src2_data.s16; break;
   case S32_TYPE:
      data.s32 = src1_data.s32 / src2_data.s32; break;
   case S64_TYPE: 
      data.s64 = src1_data.s64 / src2_data.s64; break;
   case U8_TYPE:
      data.u8  = src1_data.u8  / src2_data.u8 ; break;
   case U16_TYPE:
      data.u16 = src1_data.u16 / src2_data.u16; break;
   case U32_TYPE:
      data.u32 = src1_data.u32 / src2_data.u32; break;
   case U64_TYPE: 
      data.u64 = src1_data.u64 / src2_data.u64; break;
   case B8_TYPE:
      data.u8  = src1_data.u8  / src2_data.u8 ; break;
   case B16_TYPE:
      data.u16 = src1_data.u16 / src2_data.u16; break;
   case B32_TYPE:
      data.u32 = src1_data.u32 / src2_data.u32; break;
   case B64_TYPE:
      data.u64 = src1_data.u64 / src2_data.u64; break;
   case F16_TYPE: assert(0); break;
   case F32_TYPE: data.f32 = src1_data.f32 / src2_data.f32; break;
   case F64_TYPE: case FF64_TYPE: data.f64 = src1_data.f64 / src2_data.f64; break;
   default: assert(0); break;
   }
   thread->set_operand_value(dst,data, i_type, thread,pI);
}

void ex2_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t src1_data, src2_data, data;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();

   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);


   switch ( i_type ) {
   case F32_TYPE: 
      data.f32 = cuda_math::__powf(2.0, src1_data.f32);
      break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0); 
      break;
   }
   
   thread->set_operand_value(dst,data, i_type, thread,pI);
}

void exit_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   thread->set_done();
   thread->exitCore();
   thread->registerExit();
   checkGraphicsThreadExit((void*) thread->get_kernel_info(),thread->get_uid_in_kernel());
}

void mad_def( const ptx_instruction *pI, ptx_thread_info *thread, bool use_carry = false );

void fma_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   mad_def(pI,thread);
}

void isspacep_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
    printf("GPGPU-Sim PTX: UNTESTED INSTRUCTION: ISSPACEP\n");
    assert(0);
//   ptx_reg_t a;
//   bool t=false;
//
//   const operand_info &dst  = pI->dst();
//   const operand_info &src1 = pI->src1();
//   memory_space_t space = pI->get_space();
//
//   a = thread->get_reg(src1.get_symbol());
//   addr_t addr = (addr_t)a.u64;
//   unsigned smid = thread->get_hw_sid();
//   unsigned hwtid = thread->get_hw_tid();
//
//   switch( space.get_type() ) {
//   case shared_space: t = isspace_shared( smid, addr );
//   case local_space:  t = isspace_local( smid, hwtid, addr );
//   case global_space: t = isspace_global( addr );
//   default: abort();
//   }
//
//   ptx_reg_t p;
//   p.pred = t?1:0;
//
//   thread->set_reg(dst.get_symbol(),p);
}

void decode_space( memory_space_t &space, ptx_thread_info *thread, const operand_info &op, memory_space *&mem, addr_t &addr)
{
   unsigned smid = thread->get_hw_sid();
   unsigned hwtid = thread->get_hw_tid();

   if( space == param_space_unclassified ) {
      // need to op to determine whether it refers to a kernel param or local param
      const symbol *s = op.get_symbol();
      const type_info *t = s->type();
      type_info_key ti = t->get_key();
      if( ti.is_param_kernel() )
         space = param_space_kernel;
      else if( ti.is_param_local() ) {
         space = param_space_local;
      } else {
         printf("GPGPU-Sim PTX: ERROR ** cannot resolve .param space for '%s'\n", s->name().c_str() );
         abort(); 
      }
   }
   switch ( space.get_type() ) {
   case global_space: mem = thread->get_global_memory(); break;
   case param_space_local:
   case local_space:
      mem = thread->get_global_memory();
      addr += thread->get_local_mem_stack_pointer();
      break; 
   case tex_space:    mem = thread->get_tex_memory(); break; 
   case surf_space:   mem = thread->get_surf_memory(); break; 
   case param_space_kernel:  mem = thread->get_param_memory(); break;
   case shared_space:  mem = thread->m_shared_mem; break; 
   case const_space:  mem = thread->get_global_memory(); break;
   case generic_space:
      if( thread->get_ptx_version().ver() >= 2.0 ) {
         // convert generic address to memory space address
         space = whichspace(addr);
         switch ( space.get_type() ) {
         case global_space: mem = thread->get_global_memory(); addr = generic_to_global(addr); break;
         case local_space:  mem = thread->get_global_memory(); addr = generic_to_local(smid,hwtid,addr); break; 
         case shared_space: mem = thread->m_shared_mem; addr = generic_to_shared(smid,addr); break; 
         default: abort();
         }
      } else {
         abort();
      }
      break;
   case param_space_unclassified:
   case undefined_space:
   default:
      abort(); break;
   }
}

void ld_exec( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   const operand_info &dst = pI->dst();
   const operand_info &src1 = pI->src1();
   
//   printf("ld inst\n");
//   if(src1.get_type() == symbolic_t || src1.get_type() == reg_t || src1.get_type() == address_t 
//           || src1.get_type() == memory_t || src1.get_type() == label_t ){
//       printf("src %s\n", src1.name().c_str());
//   }
//   if(dst.get_type() == symbolic_t || dst.get_type() == reg_t || dst.get_type() == address_t 
//           || dst.get_type() == memory_t || dst.get_type() == label_t ){
//       printf("dst %s\n", dst.name().c_str());
//   }

   unsigned type = pI->get_type();

   ptx_reg_t src1_data = thread->get_operand_value(src1, dst, type, thread, 1);
   ptx_reg_t data;
   memory_space_t space = pI->get_space();
   unsigned vector_spec = pI->get_vector();

   memory_space *mem = NULL;
   addr_t addr = src1_data.u64;

   decode_space(space,thread,src1,mem,addr);

   thread->get_gpu()->gem5CudaGPU->getCudaCore(thread->get_hw_sid())->record_ld(space);

   if (space.get_type() != global_space &&
       space.get_type() != const_space &&
       space.get_type() != local_space) {
       size_t size;
       int t;
       data.u64=0;
       type_info_key::type_decode(type,size,t);
       // Note here that when using gem5 memories, this read function will not
       // return the data that will be set in the operand. Instead, when the read
       // completes, it will write the operands a second time with the correct data
       if (!vector_spec) {
          mem->read(addr,size/8,&data.s64,thread,pI);
          // Before, we did a functional read here.
          if( type == S16_TYPE || type == S32_TYPE )
             sign_extend(data,size,dst);
          thread->set_operand_value(dst,data, type, thread, pI);
       } else {
          ptx_reg_t data1, data2, data3, data4;
          mem->read(addr,size/8,&data1.s64,thread,pI);
          mem->read(addr+size/8,size/8,&data2.s64,thread,pI);
          if (vector_spec != V2_TYPE) { //either V3 or V4
             mem->read(addr+2*size/8,size/8,&data3.s64,thread,pI);
             if (vector_spec != V3_TYPE) { //v4
                mem->read(addr+3*size/8,size/8,&data4.s64,thread,pI);
                thread->set_vector_operand_values(dst,data1,data2,data3,data4);
             } else //v3
                thread->set_vector_operand_values(dst,data1,data2,data3,data3);
          } else //v2
             thread->set_vector_operand_values(dst,data1,data2,data2,data2);
       }
   }
   thread->m_last_effective_address.set(addr);
   thread->m_last_memory_space = space; 
//   printf("ld addr=%x \n", addr);
}

void ld_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ld_exec(pI,thread);
}
void ldu_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ld_exec(pI,thread);
}

void lg2_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t a, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();

   a = thread->get_operand_value(src1, dst, i_type, thread, 1);


   switch ( i_type ) {
   case F32_TYPE: 
      d.f32 = log(a.f32)/log(2);
      break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0);
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void mad24_impl( const ptx_instruction *pI, ptx_thread_info *thread )
{
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();
   const operand_info &src3 = pI->src3();
   ptx_reg_t d, t;

   unsigned i_type = pI->get_type();
   ptx_reg_t a = thread->get_operand_value(src1, dst, i_type, thread, 1);
   ptx_reg_t b = thread->get_operand_value(src2, dst, i_type, thread, 1);
   ptx_reg_t c = thread->get_operand_value(src3, dst, i_type, thread, 1);

   unsigned sat_mode = pI->saturation_mode();

   assert( !pI->is_wide() );

   switch ( i_type ) {
   case S32_TYPE: 
      t.s64 = a.s32 * b.s32;
      if ( pI->is_hi() ) {
         d.s64 = (t.s64>>16) + c.s32;
         if ( sat_mode ) {
            if ( d.s64 > (int)0x7FFFFFFF )
               d.s64 = (int)0x7FFFFFFF;
            else if ( d.s64 < (int)0x80000000 )
               d.s64 = (int)0x80000000;
         }
      } else if ( pI->is_lo() ) d.s64 = t.s32 + c.s32;
      else assert(0);
      break;
   case U32_TYPE: 
      t.u64 = a.u32 * b.u32;
      if ( pI->is_hi() ) d.u64 = (t.u64>>16) + c.u32;
      else if ( pI->is_lo() ) d.u64 = t.u32 + c.u32;
      else assert(0);
      break;
   default: 
      assert(0);
      break;
   }

   thread->set_operand_value(dst, d, i_type, thread, pI);
}

void mad_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   mad_def(pI, thread, false);
}

void madp_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   mad_def(pI, thread, true);
}

void mad_def( const ptx_instruction *pI, ptx_thread_info *thread, bool use_carry ) 
{ 
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();
   const operand_info &src3 = pI->src3();
   ptx_reg_t d, t;

   int carry=0;
   int overflow=0;

   unsigned i_type = pI->get_type();
   ptx_reg_t a = thread->get_operand_value(src1, dst, i_type, thread, 1);
   ptx_reg_t b = thread->get_operand_value(src2, dst, i_type, thread, 1);
   ptx_reg_t c = thread->get_operand_value(src3, dst, i_type, thread, 1);

   // take the carry bit, it should be the 4th operand 
   ptx_reg_t carry_bit; 
   carry_bit.u64 = 0;
   if (use_carry) {
      const operand_info &carry = pI->operand_lookup(4);
      carry_bit = thread->get_operand_value(carry, dst, PRED_TYPE, thread, 0);
      carry_bit.pred &= 0x4;
      carry_bit.pred >>=2;
   }

   unsigned rounding_mode = pI->rounding_mode();

   switch ( i_type ) {
   case S16_TYPE: 
      t.s32 = a.s16 * b.s16;
      if ( pI->is_wide() ) d.s32 = t.s32 + c.s32 + carry_bit.pred;
      else if ( pI->is_hi() ) d.s16 = (t.s32>>16) + c.s16 + carry_bit.pred;
      else if ( pI->is_lo() ) d.s16 = t.s16 + c.s16 + carry_bit.pred;
      else assert(0);
      carry = ((long long int)(t.s32 + c.s32 + carry_bit.pred)&0x100000000)>>32;
      break;
   case S32_TYPE: 
      t.s64 = a.s32 * b.s32;
      if ( pI->is_wide() ) d.s64 = t.s64 + c.s64 + carry_bit.pred;
      else if ( pI->is_hi() ) d.s32 = (t.s64>>32) + c.s32 + carry_bit.pred;
      else if ( pI->is_lo() ) d.s32 = t.s32 + c.s32 + carry_bit.pred;
      else assert(0);
      break;
   case S64_TYPE: 
      t.s64 = a.s64 * b.s64;
      assert( !pI->is_wide() );
      assert( !pI->is_hi() );
      assert( use_carry == false); 
      if ( pI->is_lo() ) d.s64 = t.s64 + c.s64 + carry_bit.pred;
      else assert(0);
      break;
   case U16_TYPE: 
      t.u32 = a.u16 * b.u16;
      if ( pI->is_wide() ) d.u32 = t.u32 + c.u32 + carry_bit.pred;
      else if ( pI->is_hi() ) d.u16 = (t.u32 + c.u16 + carry_bit.pred)>>16;
      else if ( pI->is_lo() ) d.u16 = t.u16 + c.u16 + carry_bit.pred;
      else assert(0);
      carry = ((long long int)((long long int)t.u32 + c.u32 + carry_bit.pred)&0x100000000)>>32;
      break;
   case U32_TYPE: 
      t.u64 = a.u32 * b.u32;
      if ( pI->is_wide() ) d.u64 = t.u64 + c.u64 + carry_bit.pred;
      else if ( pI->is_hi() ) d.u32 = (t.u64 + c.u32 + carry_bit.pred)>>32;
      else if ( pI->is_lo() ) d.u32 = t.u32 + c.u32 + carry_bit.pred;
      else assert(0);
      break;
   case U64_TYPE: 
      t.u64 = a.u64 * b.u64;
      assert( !pI->is_wide() );
      assert( !pI->is_hi() );
      assert( use_carry == false); 
      if ( pI->is_lo() ) d.u64 = t.u64 + c.u64 + carry_bit.pred;
      else assert(0);
      break;
   case F16_TYPE: 
      assert(0); 
      break;
   case F32_TYPE: {
         assert( use_carry == false); 
         int orig_rm = fegetround();
         switch ( rounding_mode ) {
         case RN_OPTION: break;
         case RZ_OPTION: fesetround( FE_TOWARDZERO ); break;
         default: assert(0); break;
         }
         d.f32 = a.f32 * b.f32 + c.f32;
         if ( pI->saturation_mode() ) {
            if ( d.f32 < 0 ) d.f32 = 0;
            else if ( d.f32 > 1.0f ) d.f32 = 1.0f;
         }
         fesetround( orig_rm );
         break;
      }  
   case F64_TYPE: case FF64_TYPE: {
         assert( use_carry == false); 
         int orig_rm = fegetround();
         switch ( rounding_mode ) {
         case RN_OPTION: break;
         case RZ_OPTION: fesetround( FE_TOWARDZERO ); break;
         default: assert(0); break;
         }
         d.f64 = a.f64 * b.f64 + c.f64;
         if ( pI->saturation_mode() ) {
            if ( d.f64 < 0 ) d.f64 = 0;
            else if ( d.f64 > 1.0f ) d.f64 = 1.0;
         }
         fesetround( orig_rm );
         break;
      }
   default: 
      assert(0);
      break;
   }
   thread->set_operand_value(dst, d, i_type, thread, pI, overflow, carry);
}

bool isNaN(float x)
{
   return isnan(x);
}

bool isNaN(double x)
{
   return isnan(x);
}

void max_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t a, b, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);
   b = thread->get_operand_value(src2, dst, i_type, thread, 1);


   switch ( i_type ) {
   case U16_TYPE: d.u16 = MY_MAX_I(a.u16,b.u16); break;
   case U32_TYPE: d.u32 = MY_MAX_I(a.u32,b.u32); break;
   case U64_TYPE: d.u64 = MY_MAX_I(a.u64,b.u64); break;
   case S16_TYPE: d.s16 = MY_MAX_I(a.s16,b.s16); break;
   case S32_TYPE: d.s32 = MY_MAX_I(a.s32,b.s32); break;
   case S64_TYPE: d.s64 = MY_MAX_I(a.s64,b.s64); break;
   case F32_TYPE: d.f32 = MY_MAX_F(a.f32,b.f32); break;
   case F64_TYPE: case FF64_TYPE: d.f64 = MY_MAX_F(a.f64,b.f64); break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0); 
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void membar_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   // handled by timing simulator 
}

void min_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t a, b, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);
   b = thread->get_operand_value(src2, dst, i_type, thread, 1);


   switch ( i_type ) {
   case U16_TYPE: d.u16 = MY_MIN_I(a.u16,b.u16); break;
   case U32_TYPE: d.u32 = MY_MIN_I(a.u32,b.u32); break;
   case U64_TYPE: d.u64 = MY_MIN_I(a.u64,b.u64); break;
   case S16_TYPE: d.s16 = MY_MIN_I(a.s16,b.s16); break;
   case S32_TYPE: d.s32 = MY_MIN_I(a.s32,b.s32); break;
   case S64_TYPE: d.s64 = MY_MIN_I(a.s64,b.s64); break;
   case F32_TYPE: d.f32 = MY_MIN_F(a.f32,b.f32); break;
   case F64_TYPE: case FF64_TYPE: d.f64 = MY_MIN_F(a.f64,b.f64); break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0);
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void mov_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ptx_reg_t data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   
   
//   printf("mov inst\n");
//   if(src1.get_type() == symbolic_t || src1.get_type() == reg_t || src1.get_type() == address_t 
//           || src1.get_type() == memory_t || src1.get_type() == label_t ){
//       printf("src %s\n", src1.name().c_str());
//   }
//   if(dst.get_type() == symbolic_t || dst.get_type() == reg_t || dst.get_type() == address_t 
//           || dst.get_type() == memory_t || dst.get_type() == label_t ){
//       printf("dst %s\n", dst.name().c_str());
//   }
   
   unsigned i_type = pI->get_type();

   if( (src1.is_vector() || dst.is_vector()) && (i_type != BB64_TYPE) && (i_type != BB128_TYPE) && (i_type != FF64_TYPE) ) {
      assert(!pI->saturation_mode());
      // pack or unpack operation
      unsigned nbits_to_move = 0;
      ptx_reg_t tmp_bits;

      switch( pI->get_type() ) {
      case B16_TYPE: nbits_to_move = 16; break;
      case B32_TYPE: nbits_to_move = 32; break;
      case B64_TYPE: nbits_to_move = 64; break;
      default: printf("Execution error: mov pack/unpack with unsupported type qualifier\n"); assert(0); break;
      }

      if( src1.is_vector() ) {
         unsigned nelem = src1.get_vect_nelem();
         ptx_reg_t v[4];
         thread->get_vector_operand_values(src1, v, nelem );

         unsigned bits_per_src_elem = nbits_to_move / nelem;
         for( unsigned i=0; i < nelem; i++ ) {
            switch(bits_per_src_elem) {
            case 8:   tmp_bits.u64 |= ((unsigned long long)(v[i].u8)  << (8*i));  break;
            case 16:  tmp_bits.u64 |= ((unsigned long long)(v[i].u16) << (16*i)); break;
            case 32:  tmp_bits.u64 |= ((unsigned long long)(v[i].u32) << (32*i)); break;
            default: printf("Execution error: mov pack/unpack with unsupported source/dst size ratio (src)\n"); assert(0); break;
            }
         }
      } else {
         data = thread->get_operand_value(src1, dst, i_type, thread, 1);

         switch( pI->get_type() ) {
         case B16_TYPE: tmp_bits.u16 = data.u16; break;
         case B32_TYPE: tmp_bits.u32 = data.u32; break;
         case B64_TYPE: tmp_bits.u64 = data.u64; break;
         default: assert(0); break;
         }
      }

      if( dst.is_vector() ) {
         unsigned nelem = dst.get_vect_nelem();
         ptx_reg_t v[4];
         unsigned bits_per_dst_elem = nbits_to_move / nelem;
         for( unsigned i=0; i < nelem; i++ ) {
            switch(bits_per_dst_elem) {
            case 8:  v[i].u8  = (tmp_bits.u64 >> (8*i)) & ((unsigned long long) 0xFF); break;
            case 16: v[i].u16 = (tmp_bits.u64 >> (16*i)) & ((unsigned long long) 0xFFFF); break;
            case 32: v[i].u32 = (tmp_bits.u64 >> (32*i)) & ((unsigned long long) 0xFFFFFFFF); break;
            default:
               printf("Execution error: mov pack/unpack with unsupported source/dst size ratio (dst)\n");
               assert(0);
               break;
            }
         }
         thread->set_vector_operand_values(dst,v[0],v[1],v[2],v[3]);
      } else {
         thread->set_operand_value(dst,tmp_bits, i_type, thread, pI);
      }
   } else if (i_type == PRED_TYPE and src1.is_literal() == true) {
      // in ptx, literal input translate to predicate as 0 = false and 1 = true 
      // we have adopted the opposite to simplify implementation of zero flags in ptxplus 
      data = thread->get_operand_value(src1, dst, i_type, thread, 1);

      ptx_reg_t finaldata; 
      finaldata.pred = (data.u32 == 0)? 1 : 0;  // setting zero-flag in predicate 
      thread->set_operand_value(dst, finaldata, i_type, thread, pI);
   } else {

     data = thread->get_operand_value(src1, dst, i_type, thread, 1);
     
      if (i_type == F32_TYPE and pI->saturation_mode()) {
            if (data.f32 < 0) data.f32 = 0;
            else if (data.f32 > 1.0f) data.f32 = 1.0f;
        } else if (i_type == F64_TYPE and pI->saturation_mode()) {
            if (data.f64 < 0) data.f64 = 0;
            else if (data.f64 > 1.0f) data.f64 = 1.0f;
        } else assert(!pI->saturation_mode());

     thread->set_operand_value(dst, data, i_type, thread, pI);
   }
   
//   printf("mov data.f32 = %f\n", data.f32);
}

void mul24_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ptx_reg_t src1_data, src2_data, data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);


   //src1_data = srcOperandModifiers(src1_data, src1, dst, i_type, thread);
   //src2_data = srcOperandModifiers(src2_data, src2, dst, i_type, thread);

   src1_data.mask_and(0,0x00FFFFFF);
   src2_data.mask_and(0,0x00FFFFFF);

   switch ( i_type ) {
   case S32_TYPE: 
      if( src1_data.get_bit(23) ) 
         src1_data.mask_or(0xFFFFFFFF,0xFF000000);
      if( src2_data.get_bit(23) ) 
         src2_data.mask_or(0xFFFFFFFF,0xFF000000);
      data.s64 = src1_data.s64 * src2_data.s64;
      break;
   case U32_TYPE:
      data.u64 = src1_data.u64 * src2_data.u64;
      break;
   default:
      printf("GPGPU-Sim PTX: Execution error - type mismatch with instruction\n");
      assert(0);
      break;
   }

   if ( pI->is_hi() ) {
      data.u64 = data.u64 >> 16;
      data.mask_and(0,0xFFFFFFFF);
   } else if (pI->is_lo()) {
      data.mask_and(0,0xFFFFFFFF);
   }

   thread->set_operand_value(dst, data, i_type, thread, pI);
}

void mul_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ptx_reg_t data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();
   
   ptx_reg_t d, t;

   unsigned i_type = pI->get_type();
   ptx_reg_t a = thread->get_operand_value(src1, dst, i_type, thread, 1);
   ptx_reg_t b = thread->get_operand_value(src2, dst, i_type, thread, 1);
   
//   printf("mul inst\n");
//   if(src1.get_type() == symbolic_t || src1.get_type() == reg_t || src1.get_type() == address_t 
//           || src1.get_type() == memory_t || src1.get_type() == label_t ){
//       printf("src1 %s, val.f32=%f\n", src1.name().c_str(), a.f32);
//   }
//   if(src2.get_type() == symbolic_t || src2.get_type() == reg_t || src2.get_type() == address_t 
//           || src2.get_type() == memory_t || src2.get_type() == label_t ){
//       printf("src2 %s, val.f32=%f\n", src2.name().c_str(), b.f32);
//   }
//   
//   if(dst.get_type() == symbolic_t || dst.get_type() == reg_t || dst.get_type() == address_t 
//           || dst.get_type() == memory_t || dst.get_type() == label_t ){
//       printf("dst %s\n", dst.name().c_str());
//   }
   
   
   

   unsigned rounding_mode = pI->rounding_mode();

   switch ( i_type ) {
   case S16_TYPE: 
      t.s32 = ((int)a.s16) * ((int)b.s16);
      if ( pI->is_wide() ) d.s32 = t.s32;
      else if ( pI->is_hi() ) d.s16 = (t.s32>>16);
      else if ( pI->is_lo() ) d.s16 = t.s16;
      else assert(0);
      break;
   case S32_TYPE: 
      t.s64 = ((long long)a.s32) * ((long long)b.s32);
      if ( pI->is_wide() ) d.s64 = t.s64;
      else if ( pI->is_hi() ) d.s32 = (t.s64>>32);
      else if ( pI->is_lo() ) d.s32 = t.s32;
      else assert(0);
      break;
   case S64_TYPE: 
      t.s64 = a.s64 * b.s64;
      assert( !pI->is_wide() );
      assert( !pI->is_hi() );
      if ( pI->is_lo() ) d.s64 = t.s64;
      else assert(0);
      break;
   case U16_TYPE: 
      t.u32 = ((unsigned)a.u16) * ((unsigned)b.u16);
      if ( pI->is_wide() ) d.u32 = t.u32;
      else if ( pI->is_lo() ) d.u16 = t.u16;
      else if ( pI->is_hi() ) d.u16 = (t.u32>>16);
      else assert(0);
      break;
   case U32_TYPE: 
      t.u64 = ((unsigned long long)a.u32) * ((unsigned long long)b.u32);
      if ( pI->is_wide() ) d.u64 = t.u64;
      else if ( pI->is_lo() ) d.u32 = t.u32;
      else if ( pI->is_hi() ) d.u32 = (t.u64>>32);
      else assert(0);
      break;
   case U64_TYPE: 
      t.u64 = a.u64 * b.u64;
      assert( !pI->is_wide() );
      assert( !pI->is_hi() );
      if ( pI->is_lo() ) d.u64 = t.u64;
      else assert(0);
      break;
   case F16_TYPE: 
      assert(0); 
      break;
   case F32_TYPE: {
         int orig_rm = fegetround();
         switch ( rounding_mode ) {
         case RN_OPTION: break;
         case RZ_OPTION: fesetround( FE_TOWARDZERO ); break;
         default: assert(0); break;
         }

         d.f32 = a.f32 * b.f32;

         if ( pI->saturation_mode() ) {
            if ( d.f32 < 0 ) d.f32 = 0;
            else if ( d.f32 > 1.0f ) d.f32 = 1.0f;
         }
         fesetround( orig_rm );
         break;
      }  
   case F64_TYPE: case FF64_TYPE:{
         int orig_rm = fegetround();
         switch ( rounding_mode ) {
         case RN_OPTION: break;
         case RZ_OPTION: fesetround( FE_TOWARDZERO ); break;
         default: assert(0); break;
         }
         d.f64 = a.f64 * b.f64;
         if ( pI->saturation_mode() ) {
            if ( d.f64 < 0 ) d.f64 = 0;
            else if ( d.f64 > 1.0f ) d.f64 = 1.0;
         }
         fesetround( orig_rm );
         break;
      }
   default: 
      assert(0); 
      break;
   }
   
//   printf("mul data.f32 = %f\n", d.f32);

   thread->set_operand_value(dst, d, i_type, thread, pI);
}

void neg_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t src1_data, src2_data, data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned to_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, to_type, thread, 1);


   switch ( to_type ) {
   case S8_TYPE:
   case S16_TYPE:
   case S32_TYPE:
   case S64_TYPE: 
      data.s64 = 0 - src1_data.s64; break; // seems buggy, but not (just ignore higher bits)
   case U8_TYPE:
   case U16_TYPE:
   case U32_TYPE:
   case U64_TYPE: 
      assert(0); break;
   case F16_TYPE: assert(0); break;
   case F32_TYPE: data.f32 = 0.0f - src1_data.f32; break;
   case F64_TYPE: case FF64_TYPE: data.f64 = 0.0f - src1_data.f64; break;
   default: assert(0); break;
   }

   thread->set_operand_value(dst,data, to_type, thread, pI);
}

//nandn bitwise negates second operand then bitwise nands with the first operand
void nandn_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ptx_reg_t src1_data, src2_data, data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);


   //the way ptxplus handles predicates: 1 = false and 0 = true
   if(i_type == PRED_TYPE)
      data.pred = (~src1_data.pred & src2_data.pred);
   else
      data.u64 = ~(src1_data.u64 & ~src2_data.u64);

   thread->set_operand_value(dst,data, i_type, thread, pI);

}

//norn bitwise negates first operand then bitwise ands with the second operand
void norn_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ptx_reg_t src1_data, src2_data, data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);


   //the way ptxplus handles predicates: 1 = false and 0 = true
   if(i_type == PRED_TYPE)
      data.pred = ~(src1_data.pred & ~(src2_data.pred));
   else
      data.u64 = ~(src1_data.u64) & src2_data.u64;

   thread->set_operand_value(dst,data, i_type, thread, pI);

}

void not_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ptx_reg_t a, b, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);


   switch ( i_type ) {
   case PRED_TYPE: d.pred = (~(a.pred) & 0x000F); break;
   case B16_TYPE:  d.u16  = ~a.u16; break;
   case B32_TYPE:  d.u32  = ~a.u32; break;
   case B64_TYPE:  d.u64  = ~a.u64; break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0); 
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void or_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t src1_data, src2_data, data;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);

   //the way ptxplus handles predicates: 1 = false and 0 = true
   if(i_type == PRED_TYPE)
      data.pred = ~(~(src1_data.pred) | ~(src2_data.pred));
   else
      data.u64 = src1_data.u64 | src2_data.u64;

   thread->set_operand_value(dst,data, i_type, thread, pI);
}

void orn_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t src1_data, src2_data, data;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);

   //the way ptxplus handles predicates: 1 = false and 0 = true
   if(i_type == PRED_TYPE)
      data.pred = ~(~(src1_data.pred) | (src2_data.pred));
   else
      data.u64 = src1_data.u64 | ~src2_data.u64;

   thread->set_operand_value(dst,data, i_type, thread, pI);
}

void pmevent_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void popc_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t src_data, data;
   const operand_info &dst  = pI->dst();
   const operand_info &src = pI->src1();

   unsigned i_type = pI->get_type();
   src_data = thread->get_operand_value(src, dst, i_type, thread, 1);

   switch ( i_type ) {
   case B32_TYPE: {
      std::bitset<32> mask(src_data.u32); 
      data.u32 = mask.count(); 
      } break;
   case B64_TYPE: {
      std::bitset<64> mask(src_data.u64); 
      data.u32 = mask.count();
      } break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0); 
      break;
   }

   thread->set_operand_value(dst,data, i_type, thread, pI);
}
void prefetch_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void prefetchu_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void prmt_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }

void rcp_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t src1_data, src2_data, data;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);


   switch ( i_type ) {
   case F32_TYPE: 
      data.f32 = 1.0f / src1_data.f32;
      break;
   case F64_TYPE:
   case FF64_TYPE:
      data.f64 = 1.0f / src1_data.f64;
      break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0); 
      break;
   }

   thread->set_operand_value(dst,data, i_type, thread, pI);
}

void red_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }

void rem_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t src1_data, src2_data, data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);

   data.u64 = src1_data.u64 % src2_data.u64;

   thread->set_operand_value(dst,data, i_type, thread, pI);
}

void ret_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   bool empty = thread->callstack_pop();
   if( empty ) {
   thread->set_done();
   thread->exitCore();
   thread->registerExit();
   }
}

//Ptxplus version of ret instruction.
void retp_impl( const ptx_instruction *pI, ptx_thread_info *thread )
{
   bool empty = thread->callstack_pop_plus();
   if( empty ) {
   thread->set_done();
   thread->exitCore();
   thread->registerExit();
   }
}

void rsqrt_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t a, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);


   switch ( i_type ) {
   case F32_TYPE:
      if ( a.f32 < 0 ) {
         d.u64 = 0;
         d.u64 = 0x7fc00000; // NaN
      } else if ( a.f32 == 0 ) {
         d.u64 = 0;
         d.u32 = 0x7f800000; // Inf
      } else
         d.f32 = cuda_math::__internal_accurate_fdividef(1.0f, sqrtf(a.f32));
      break;
   case F64_TYPE: 
   case FF64_TYPE:
      if ( a.f32 < 0 ) {
         d.u64 = 0;
	      d.u32 = 0x7fc00000; // NaN
         float x = d.f32; 
         d.f64 = (double)x;
      } else if ( a.f32 == 0 ) {
         d.u64 = 0;
	      d.u32 = 0x7f800000; // Inf
         float x = d.f32; 
         d.f64 = (double)x;
      } else
         d.f64 = 1.0 / sqrt(a.f64); 
      break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0);
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

#define SAD(d,a,b,c) d = c + ((a<b) ? (b-a) : (a-b))

void sad_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t a, b, c, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();
   const operand_info &src3 = pI->src3();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);
   b = thread->get_operand_value(src2, dst, i_type, thread, 1);
   c = thread->get_operand_value(src3, dst, i_type, thread, 1);


   switch ( i_type ) {
   case U16_TYPE: SAD(d.u16,a.u16,b.u16,c.u16); break;
   case U32_TYPE: SAD(d.u32,a.u32,b.u32,c.u32); break;
   case U64_TYPE: SAD(d.u64,a.u64,b.u64,c.u64); break;
   case S16_TYPE: SAD(d.s16,a.s16,b.s16,c.s16); break;
   case S32_TYPE: SAD(d.s32,a.s32,b.s32,c.s32); break;
   case S64_TYPE: SAD(d.s64,a.s64,b.s64,c.s64); break;
   case F32_TYPE: SAD(d.f32,a.f32,b.f32,c.f32); break;
   case F64_TYPE: case FF64_TYPE: SAD(d.f64,a.f64,b.f64,c.f64); break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0); 
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void selp_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();
   const operand_info &src3 = pI->src3();

   ptx_reg_t a, b, c, d;

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);
   b = thread->get_operand_value(src2, dst, i_type, thread, 1);
   c = thread->get_operand_value(src3, dst, i_type, thread, 1);

   //predicate value was changed so the lowest bit being set means the zero flag is set.
   //As a result, the value of c.pred must be inverted to get proper behavior
   d = (!(c.pred & 0x0001))?a:b;

   thread->set_operand_value(dst,d, PRED_TYPE, thread, pI);
}

bool isFloat(int type) 
{
   switch ( type ) {
   case F16_TYPE:
   case F32_TYPE:
   case F64_TYPE:
   case FF64_TYPE:
      return true;
   default:
      return false;
   }
}

bool CmpOp( int type, ptx_reg_t a, ptx_reg_t b, unsigned cmpop )
{
   bool t = false;

   switch ( type ) {
   case B16_TYPE: 
      switch (cmpop) {
      case EQ_OPTION: t = (a.u16 == b.u16); break;
      case NE_OPTION: t = (a.u16 != b.u16); break;
      default:
         assert(0); break;
      } break;

   case B32_TYPE: 
      switch (cmpop) {
      case EQ_OPTION: t = (a.u32 == b.u32); break;
      case NE_OPTION: t = (a.u32 != b.u32); break;
      default:
         assert(0); break;
      } break;
   case B64_TYPE:
      switch (cmpop) {
      case EQ_OPTION: t = (a.u64 == b.u64); break;
      case NE_OPTION: t = (a.u64 != b.u64); break;
      default:
         assert(0); break;
      }
      break;
   case S8_TYPE: 
   case S16_TYPE:
      switch (cmpop) {
      case EQ_OPTION: t = (a.s16 == b.s16); break;
      case NE_OPTION: t = (a.s16 != b.s16); break;
      case LT_OPTION: t = (a.s16 < b.s16); break;
      case LE_OPTION: t = (a.s16 <= b.s16); break;
      case GT_OPTION: t = (a.s16 > b.s16); break;
      case GE_OPTION: t = (a.s16 >= b.s16); break;
      default:
         assert(0); break;
      }
      break;
   case S32_TYPE: 
      switch (cmpop) {
      case EQ_OPTION: t = (a.s32 == b.s32); break;
      case NE_OPTION: t = (a.s32 != b.s32); break;
      case LT_OPTION: t = (a.s32 < b.s32); break;
      case LE_OPTION: t = (a.s32 <= b.s32); break;
      case GT_OPTION: t = (a.s32 > b.s32); break;
      case GE_OPTION: t = (a.s32 >= b.s32); break;
      default:
         assert(0); break;
      }
      break;
   case S64_TYPE:
      switch (cmpop) {
      case EQ_OPTION: t = (a.s64 == b.s64); break;
      case NE_OPTION: t = (a.s64 != b.s64); break;
      case LT_OPTION: t = (a.s64 < b.s64); break;
      case LE_OPTION: t = (a.s64 <= b.s64); break;
      case GT_OPTION: t = (a.s64 > b.s64); break;
      case GE_OPTION: t = (a.s64 >= b.s64); break;
      default:
         assert(0); break;
      }
      break;
   case U8_TYPE: 
   case U16_TYPE: 
      switch (cmpop) {
      case EQ_OPTION: t = (a.u16 == b.u16); break;
      case NE_OPTION: t = (a.u16 != b.u16); break;
      case LT_OPTION: t = (a.u16 < b.u16); break;
      case LE_OPTION: t = (a.u16 <= b.u16); break;
      case GT_OPTION: t = (a.u16 > b.u16); break;
      case GE_OPTION: t = (a.u16 >= b.u16); break;
      case LO_OPTION: t = (a.u16 < b.u16); break;
      case LS_OPTION: t = (a.u16 <= b.u16); break;
      case HI_OPTION: t = (a.u16 > b.u16); break;
      case HS_OPTION: t = (a.u16 >= b.u16); break;
      default:
         assert(0); break;
      }
      break;
   case U32_TYPE: 
      switch (cmpop) {
      case EQ_OPTION: t = (a.u32 == b.u32); break;
      case NE_OPTION: t = (a.u32 != b.u32); break;
      case LT_OPTION: t = (a.u32 < b.u32); break;
      case LE_OPTION: t = (a.u32 <= b.u32); break;
      case GT_OPTION: t = (a.u32 > b.u32); break;
      case GE_OPTION: t = (a.u32 >= b.u32); break;
      case LO_OPTION: t = (a.u32 < b.u32); break;
      case LS_OPTION: t = (a.u32 <= b.u32); break;
      case HI_OPTION: t = (a.u32 > b.u32); break;
      case HS_OPTION: t = (a.u32 >= b.u32); break;
      default:
         assert(0); break;
      }
      break;
   case U64_TYPE:
      switch (cmpop) {
      case EQ_OPTION: t = (a.u64 == b.u64); break;
      case NE_OPTION: t = (a.u64 != b.u64); break;
      case LT_OPTION: t = (a.u64 < b.u64); break;
      case LE_OPTION: t = (a.u64 <= b.u64); break;
      case GT_OPTION: t = (a.u64 > b.u64); break;
      case GE_OPTION: t = (a.u64 >= b.u64); break;
      case LO_OPTION: t = (a.u64 < b.u64); break;
      case LS_OPTION: t = (a.u64 <= b.u64); break;
      case HI_OPTION: t = (a.u64 > b.u64); break;
      case HS_OPTION: t = (a.u64 >= b.u64); break;
      default:
         assert(0); break;
      }
      break;
   case F16_TYPE: assert(0); break;
   case F32_TYPE: 
      switch (cmpop) {
      case EQ_OPTION: t = (a.f32 == b.f32) && !isNaN(a.f32) && !isNaN(b.f32); break;
      case NE_OPTION: t = (a.f32 != b.f32) && !isNaN(a.f32) && !isNaN(b.f32); break;
      case LT_OPTION: t = (a.f32 < b.f32 ) && !isNaN(a.f32) && !isNaN(b.f32); break;
      case LE_OPTION: t = (a.f32 <= b.f32) && !isNaN(a.f32) && !isNaN(b.f32); break;
      case GT_OPTION: t = (a.f32 > b.f32 ) && !isNaN(a.f32) && !isNaN(b.f32); break;
      case GE_OPTION: t = (a.f32 >= b.f32) && !isNaN(a.f32) && !isNaN(b.f32); break;
      case EQU_OPTION: t = (a.f32 == b.f32) || isNaN(a.f32) || isNaN(b.f32); break;
      case NEU_OPTION: t = (a.f32 != b.f32) || isNaN(a.f32) || isNaN(b.f32); break;
      case LTU_OPTION: t = (a.f32 < b.f32 ) || isNaN(a.f32) || isNaN(b.f32); break;
      case LEU_OPTION: t = (a.f32 <= b.f32) || isNaN(a.f32) || isNaN(b.f32); break;
      case GTU_OPTION: t = (a.f32 > b.f32 ) || isNaN(a.f32) || isNaN(b.f32); break;
      case GEU_OPTION: t = (a.f32 >= b.f32) || isNaN(a.f32) || isNaN(b.f32); break;
      case NUM_OPTION: t = !isNaN(a.f32) && !isNaN(b.f32); break;
      case NAN_OPTION: t = isNaN(a.f32) || isNaN(b.f32); break;
      default:
         assert(0); break;
      }
      break;
   case F64_TYPE: 
   case FF64_TYPE:
      switch (cmpop) {
      case EQ_OPTION: t = (a.f64 == b.f64) && !isNaN(a.f64) && !isNaN(b.f64); break;
      case NE_OPTION: t = (a.f64 != b.f64) && !isNaN(a.f64) && !isNaN(b.f64); break;
      case LT_OPTION: t = (a.f64 < b.f64 ) && !isNaN(a.f64) && !isNaN(b.f64); break;
      case LE_OPTION: t = (a.f64 <= b.f64) && !isNaN(a.f64) && !isNaN(b.f64); break;
      case GT_OPTION: t = (a.f64 > b.f64 ) && !isNaN(a.f64) && !isNaN(b.f64); break;
      case GE_OPTION: t = (a.f64 >= b.f64) && !isNaN(a.f64) && !isNaN(b.f64); break;
      case EQU_OPTION: t = (a.f64 == b.f64) || isNaN(a.f64) || isNaN(b.f64); break;
      case NEU_OPTION: t = (a.f64 != b.f64) || isNaN(a.f64) || isNaN(b.f64); break;
      case LTU_OPTION: t = (a.f64 < b.f64 ) || isNaN(a.f64) || isNaN(b.f64); break;
      case LEU_OPTION: t = (a.f64 <= b.f64) || isNaN(a.f64) || isNaN(b.f64); break;
      case GTU_OPTION: t = (a.f64 > b.f64 ) || isNaN(a.f64) || isNaN(b.f64); break;
      case GEU_OPTION: t = (a.f64 >= b.f64) || isNaN(a.f64) || isNaN(b.f64); break;
      case NUM_OPTION: t = !isNaN(a.f64) && !isNaN(b.f64); break;
      case NAN_OPTION: t = isNaN(a.f64) || isNaN(b.f64); break;
      default:
         assert(0); break;
      }
      break;
   default: assert(0); break;
   }

   return t;
}

void setp_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ptx_reg_t a, b;

   int t=0;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   assert( pI->get_num_operands() < 4 ); // or need to deal with "c" operand / boolOp

   unsigned type = pI->get_type();
   unsigned cmpop = pI->get_cmpop();
   a = thread->get_operand_value(src1, dst, type, thread, 1);
   b = thread->get_operand_value(src2, dst, type, thread, 1);

   t = CmpOp(type,a,b,cmpop);

   ptx_reg_t data;

   //the way ptxplus handles the zero flag, 1 = false and 0 = true
   data.pred = (t==0); //inverting predicate since ptxplus uses "1" for a set zero flag

   thread->set_operand_value(dst,data, PRED_TYPE, thread, pI);
}

void set_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t a, b;

   int t=0;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   assert( pI->get_num_operands() < 4 ); // or need to deal with "c" operand / boolOp

   unsigned src_type = pI->get_type2();
   unsigned cmpop = pI->get_cmpop();

   a = thread->get_operand_value(src1, dst, src_type, thread, 1);
   b = thread->get_operand_value(src2, dst, src_type, thread, 1);

   // Take abs of first operand if needed
   if(pI->is_abs()) {
      switch ( src_type ) {
      case S16_TYPE: a.s16 = my_abs(a.s16); break;
      case S32_TYPE: a.s32 = my_abs(a.s32); break;
      case S64_TYPE: a.s64 = my_abs(a.s64); break;
      case U16_TYPE: a.u16 = a.u16; break;
      case U32_TYPE: a.u32 = my_abs(a.u32); break;
      case U64_TYPE: a.u64 = my_abs(a.u64); break;
      case F32_TYPE: a.f32 = my_abs(a.f32); break;
      case F64_TYPE: case FF64_TYPE: a.f64 = my_abs(a.f64); break;
      default:
         printf("Execution error: type mismatch with instruction\n");
         assert(0);
         break;
      }
   }

   t = CmpOp(src_type,a,b,cmpop);

   ptx_reg_t data;
   if ( isFloat(pI->get_type()) ) {
      data.f32 = (t!=0)?1.0f:0.0f;
   } else {
      data.u32 = (t!=0)?0xFFFFFFFF:0;
   }

   thread->set_operand_value(dst, data, pI->get_type(), thread, pI);

}

void shl_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ptx_reg_t a, b, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);
   b = thread->get_operand_value(src2, dst, i_type, thread, 1);

   switch ( i_type ) {
   case B16_TYPE:
   case U16_TYPE:
      if ( b.u16 >= 16 )
         d.u16 = 0;
      else
         d.u16 = (unsigned short) ((a.u16 << b.u16) & 0xFFFF); 
      break;
   case B32_TYPE: 
   case U32_TYPE: 
      if ( b.u32 >= 32 )
         d.u32 = 0;
      else
         d.u32 = (unsigned) ((a.u32 << b.u32) & 0xFFFFFFFF); 
      break;
   case B64_TYPE: 
   case U64_TYPE: 
      if ( b.u32 >= 64 )
         d.u64 = 0;
      else
         d.u64 = (a.u64 << b.u64); 
      break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0); 
      break;
   }

   thread->set_operand_value(dst, d, i_type, thread, pI);
}

void shr_impl( const ptx_instruction *pI, ptx_thread_info *thread )
{
   ptx_reg_t a, b, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);
   b = thread->get_operand_value(src2, dst, i_type, thread, 1);


   switch ( i_type ) {
   case U16_TYPE:
   case B16_TYPE: 
      if ( b.u16 < 16 )
         d.u16 = (unsigned short) ((a.u16 >> b.u16) & 0xFFFF);
      else
         d.u16 = 0;
      break;
   case U32_TYPE:
   case B32_TYPE: 
      if ( b.u32 < 32 )
         d.u32 = (unsigned) ((a.u32 >> b.u32) & 0xFFFFFFFF);
      else
         d.u32 = 0;
      break;
   case U64_TYPE:
   case B64_TYPE: 
      if ( b.u32 < 64 )
         d.u64 = (a.u64 >> b.u64);
      else
         d.u64 = 0;
      break;
   case S16_TYPE: 
      if ( b.u16 < 16 )
         d.s64 = (a.s16 >> b.s16);
      else {
         if ( a.s16 < 0 ) {
            d.s64 = -1;
         } else {
            d.s64 = 0;
         }
      }
      break;
   case S32_TYPE: 
      if ( b.u32 < 32 )
         d.s64 = (a.s32 >> b.s32);
      else {
         if ( a.s32 < 0 ) {
            d.s64 = -1;
         } else {
            d.s64 = 0;
         }
      }
      break;
   case S64_TYPE: 
      if ( b.u64 < 64 )
         d.s64 = (a.s64 >> b.u64);
      else {
         if ( a.s64 < 0 ) {
            if ( b.s32 < 0 ) {
               d.u64 = -1;
               d.s32 = 0;
            } else {
               d.s64 = -1;
            }
         } else {
            d.s64 = 0;
         }
      }
      break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0); 
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void sin_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ptx_reg_t a, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);


   switch ( i_type ) {
   case F32_TYPE: 
      d.f32 = sin(a.f32);
      break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0); 
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void slct_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();
   const operand_info &src3 = pI->src3();

   ptx_reg_t a, b, c, d;

   unsigned i_type = pI->get_type();
   unsigned c_type = pI->get_type2();
   bool t = false;
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);
   b = thread->get_operand_value(src2, dst, i_type, thread, 1);
   c = thread->get_operand_value(src3, dst, c_type, thread, 1);

   switch ( c_type ) {
   case S32_TYPE: t = c.s32 >= 0; break;
   case F32_TYPE: t = c.f32 >= 0; break;
   default: assert(0); break;
   }

   switch ( i_type ) {
   case B16_TYPE:
   case S16_TYPE:
   case U16_TYPE: d.u16 = t?a.u16:b.u16; break;
   case F32_TYPE:
   case B32_TYPE:
   case S32_TYPE:
   case U32_TYPE: d.u32 = t?a.u32:b.u32; break;
   case F64_TYPE:
   case FF64_TYPE:
   case B64_TYPE:
   case S64_TYPE:
   case U64_TYPE: d.u64 = t?a.u64:b.u64; break;
   default: assert(0); break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void sqrt_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t a, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);


   switch ( i_type ) {
   case F32_TYPE: 
      if ( a.f32 < 0 )
         d.f32 = nanf("");
      else
         d.f32 = sqrt(a.f32); break;
   case F64_TYPE: 
   case FF64_TYPE:
      if ( a.f64 < 0 )
         d.f64 = nan("");
      else
         d.f64 = sqrt(a.f64); break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0);
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void ssy_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   //printf("Execution Warning: unimplemented ssy instruction is treated as a nop\n");
   // TODO: add implementation
}

void sub_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   ptx_reg_t data;
   int overflow = 0;
   int carry = 0;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   ptx_reg_t src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   ptx_reg_t src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);

   //performs addition. Sets carry and overflow if needed.
   //the constant is added in during subtraction so the carry bit is set properly.
   switch ( i_type ) {
   case S8_TYPE:
      data.s64 = (src1_data.s64 & 0xFF) - (src2_data.s64 & 0xFF) + 0x100;
      if(((src1_data.s64 & 0x80)-(src2_data.s64 & 0x80)) != 0) {overflow=((src1_data.s64 & 0x80)-(data.s64 & 0x80))==0?0:1; }
      carry = (data.s32 & 0x100)>>8;
      break;
   case S16_TYPE:
      data.s64 = (src1_data.s64 & 0xFFFF) - (src2_data.s64 & 0xFFFF) + 0x10000;
      if(((src1_data.s64 & 0x8000)-(src2_data.s64 & 0x8000)) != 0) {overflow=((src1_data.s64 & 0x8000)-(data.s64 & 0x8000))==0?0:1; }
      carry = (data.s32 & 0x10000)>>16;
      break;
   case S32_TYPE:
      data.s64 = (src1_data.s64 & 0xFFFFFFFF) - (src2_data.s64 & 0xFFFFFFFF) + 0x100000000;
      if(((src1_data.s64 & 0x80000000)-(src2_data.s64 & 0x80000000)) != 0) {overflow=((src1_data.s64 & 0x80000000)-(data.s64 & 0x80000000))==0?0:1; }
      carry = ((data.u64)>>32) & 0x0001;
      break;
   case S64_TYPE: 
      data.s64 = src1_data.s64 - src2_data.s64; break;
   case B8_TYPE:
   case U8_TYPE:
      data.u64 = (src1_data.u64 & 0xFF) - (src2_data.u64 & 0xFF) + 0x100;
      carry = (data.u64 & 0x100)>>8;
      break;
   case B16_TYPE:
   case U16_TYPE:
      data.u64 = (src1_data.u64 & 0xFFFF) - (src2_data.u64 & 0xFFFF) + 0x10000;
      carry = (data.u64 & 0x10000)>>16;
      break;
   case B32_TYPE:
   case U32_TYPE:
      data.u64 = (src1_data.u64 & 0xFFFFFFFF) - (src2_data.u64 & 0xFFFFFFFF) + 0x100000000;
      carry = (data.u64 & 0x100000000)>>32;
      break;
   case B64_TYPE:
   case U64_TYPE: 
      data.u64 = src1_data.u64 - src2_data.u64; break;
   case F16_TYPE: assert(0); break;
   case F32_TYPE: data.f32 = src1_data.f32 - src2_data.f32; break;
   case F64_TYPE: case FF64_TYPE: data.f64 = src1_data.f64 - src2_data.f64; break;
   default: assert(0); break;
   }

   thread->set_operand_value(dst,data, i_type, thread, pI, overflow, carry);
}

void nop_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   // Do nothing
}

void subc_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void suld_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void sured_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void sust_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void suq_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }

ptx_reg_t* ptx_tex_regs = NULL;

union intfloat {
   int a;
   float b;
};

float reduce_precision( float x, unsigned bits )
{
   intfloat tmp;
   tmp.b = x;
   int v = tmp.a;
   int man = v & ((1<<23)-1);
   int mask =  ((1<<bits)-1) << (23-bits);
   int nv = (v & ((-1)-((1<<23)-1))) | (mask&man);
   tmp.a = nv;
   float result = tmp.b;
   return result;
}

unsigned wrap( unsigned x, unsigned y, unsigned mx, unsigned my, size_t elem_size )
{
   unsigned nx = (mx+x)%mx;
   unsigned ny = (my+y)%my;
   return nx + mx*ny;
}

unsigned clamp( unsigned x, unsigned y, unsigned mx, unsigned my, size_t elem_size )
{
   unsigned nx = x;
   while (nx >= mx) nx -= elem_size;
   unsigned ny = (y >= my)? my - 1 : y;
   return nx + mx*ny;
}

float textureNormalizeElementSigned(int element, int bits)
{
   if (bits) {
      int maxN = (1 << bits) - 1; 
      // removing upper bits 
      element &= maxN;
      // normalizing the number to [-1.0,1.0]
      maxN >>= 1;
      float output = (float) element / maxN;  
      if (output < -1.0f) output = -1.0f; 
      return output; 
   } else {
      return 0.0f; 
   }
}

float textureNormalizeElementUnsigned(unsigned int element, int bits)
{
   if (bits) {
      unsigned int maxN = (1 << bits) - 1; 
      // removing upper bits and normalizing the number to [0.0,1.0]
      return (float)(element & maxN) / maxN;  
   } else {
      return 0.0f; 
   }
}

void textureNormalizeOutput( const struct cudaChannelFormatDesc& desc, ptx_reg_t& datax, ptx_reg_t& datay, ptx_reg_t& dataz, ptx_reg_t& dataw ) 
{
   if (desc.f == cudaChannelFormatKindSigned) {
      datax.f32 = textureNormalizeElementSigned( datax.s32, desc.x ); 
      datay.f32 = textureNormalizeElementSigned( datay.s32, desc.y ); 
      dataz.f32 = textureNormalizeElementSigned( dataz.s32, desc.z ); 
      dataw.f32 = textureNormalizeElementSigned( dataw.s32, desc.w ); 
   } else if (desc.f == cudaChannelFormatKindUnsigned) {
      datax.f32 = textureNormalizeElementUnsigned( datax.u32, desc.x ); 
      datay.f32 = textureNormalizeElementUnsigned( datay.u32, desc.y ); 
      dataz.f32 = textureNormalizeElementUnsigned( dataz.u32, desc.z ); 
      dataw.f32 = textureNormalizeElementUnsigned( dataw.u32, desc.w ); 
   } else {
      assert(0 && "Undefined texture read mode: cudaReadModeNormalizedFloat expect integer elements"); 
   }
}

struct samplePointLocation{
    void set(int i, int j, float pfactor){
        x = i;
        y = j;
        factor = pfactor;
    }
    int x,y; //z not used here, 3d textures are supported
    float factor;
};

//function that apply addressing mode to coord given the dimension size for the coord is dimSize
float applyTexAddressingMode(float coord, cudaTextureAddressMode addressingMode, unsigned int dimSize){
    assert(addressingMode==cudaAddressModeClamp or addressingMode==cudaAddressModeWrap);
    
    if(addressingMode==cudaAddressModeClamp){
        coord = (coord > (dimSize - 1))? (dimSize - 1) : coord;
        coord = (coord < 0)? 0 : coord;
    } else if (addressingMode==cudaAddressModeWrap){
        coord = fmod(coord,dimSize);
        coord = (coord>=0)? coord : coord + dimSize;
    } else assert(0);
    return coord;
}

std::vector<samplePointLocation> getSamplingPoints(float x, float y, unsigned dimension, cudaTextureFilterMode filterMode){
    std::vector<samplePointLocation> samplingPoints;
    //filter mode is point
    if (filterMode == cudaFilterModePoint) {
        samplePointLocation sp;
        int i = floor(x);
        int j = floor(y);
        if(dimension==GEOM_MODIFIER_1D) sp.set(i,0,1);
        else if(dimension==GEOM_MODIFIER_2D) sp.set(i,j,1);
        else {
            printf("Dimensions identifier is either not supported or incorrect\n");
            assert(0);
        }
        samplingPoints.push_back(sp);
    } else if (filterMode == cudaFilterModeLinear){
        //as specified in the cuda manual in texture fetching section
        float xb = x < 0.5? x: x - 0.5;
        float yb = y < 0.5? y: y - 0.5;
        float a = xb - floor(xb);
        float b = yb - floor(yb);
        int i = floor(xb);
        int j = floor(yb);
        //case filter mode is linear
        if(dimension==GEOM_MODIFIER_1D){
            samplePointLocation sp0, sp1;
            sp0.set(i,0,1-a);
            sp1.set(i+1,0,a);
            samplingPoints.push_back(sp0);
            samplingPoints.push_back(sp1);
        } else if(dimension==GEOM_MODIFIER_2D){
            samplePointLocation sp0, sp1, sp2, sp3;
            sp0.set(i,j,(1-a)*(1-b));
            sp1.set(i+1,j,a*(1-b));
            sp2.set(i,j+1,(1-a)*b);
            sp3.set(i+1,j+1,a*b);
            samplingPoints.push_back(sp0);
            samplingPoints.push_back(sp1);
            samplingPoints.push_back(sp2);
            samplingPoints.push_back(sp3);
        } else {
            printf("Dimensions identifier is either not supported or incorrect\n");
            assert(0);
        }
    }
    return samplingPoints;
}

void getTexelData(ptx_thread_info *thread, addr_t offset, ptx_reg_t * data, float factor,
        unsigned type, unsigned size, void* texel_data) {
    memory_space * tex_mem = thread->get_tex_memory();
    ptx_reg_t tempData;
    switch (type) {
        case U8_TYPE:
        case U16_TYPE:
        case U32_TYPE:
        case B8_TYPE:
        case B16_TYPE:
        case B32_TYPE:
        case S8_TYPE:
        case S16_TYPE:
        case S32_TYPE:
            memcpy(&tempData.u32,texel_data+offset,size);
            //tex_mem->read(texel_data+offset, size, &tempData.u32, thread, NULL);
            data->u32 += factor * tempData.u32;
            break;
        case B64_TYPE:
        case U64_TYPE:
        case S64_TYPE:
            memcpy(&tempData.u64,texel_data+offset,size);//need to be rechecked as original code uses 8
            //tex_mem->read(texel_data+offset, size, &tempData.u64, thread, NULL);
            data->u64 += factor * tempData.u64;
            break;
        case F16_TYPE: assert(0);
            break;
        case F32_TYPE:
            memcpy(&tempData.f32,texel_data+offset,size);
            //tex_mem->read(texel_data+offset, size, &tempData.f32, NULL, NULL);
            data->f32 += factor * tempData.f32;
            break;
        case F64_TYPE:
        case FF64_TYPE:
            memcpy(&tempData.f64,texel_data+offset,size);
            //tex_mem->read(texel_data+offset, size, &tempData.f64, NULL, NULL);
            data->f64 += factor * tempData.f64;
            break;
        default: assert(0);
            break;
    }
}

//functional texture read uses a temporary fix, the writebacks should use gem5 memory to verify correctness 
void tex_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   unsigned dimension = pI->dimension();
   const operand_info &dst = pI->dst(); //the registers to which fetched texel will be placed
   const operand_info &src1 = pI->src1(); //the name of the texture
   const operand_info &src2 = pI->src2(); //the vector registers containing coordinates of the texel to be fetched

   std::string textureName = src1.name();
   unsigned to_type = pI->get_type();
   unsigned coords_type = pI->get_type2();
   fflush(stdout);
   
   if (!ptx_tex_regs) ptx_tex_regs = new ptx_reg_t[4];
   unsigned nelem = src2.get_vect_nelem();
   thread->get_vector_operand_values(src2, ptx_tex_regs, nelem); //ptx_reg should be 4 entry vector type...coordinates into texture
   thread->get_gpu()->gem5CudaGPU->getCudaCore(thread->get_hw_sid())->record_ld(tex_space);

   gpgpu_sim *gpu = thread->get_gpu();
   const struct textureReference* texref = gpu->get_texref(textureName);
   const struct cudaArray* cuArray = gpu->get_texarray(texref); 
   
   //check that our texels align with texture line size as we assume this when we retrieve and then writeback texels data
    unsigned const texelSize= (cuArray->desc.x + cuArray->desc.y + cuArray->desc.z +cuArray->desc.w)/8;
    assert(texelSize %thread->get_gpu()->get_config().get_texcache_linesize());
   
   //assume always 2D f32 input
   //access array with src2 coordinates
   float x_f32=0;
   float y_f32=0;
   unsigned int texture_width = cuArray->width;
   unsigned int texture_height = cuArray->height;
   new_addr_type tex_array_base = (new_addr_type) cuArray->devPtr;
   //------------------------------------------
   
   switch ( coords_type ) {
       case S32_TYPE:
           x_f32 = ptx_tex_regs[0].s32; 
           y_f32 = ptx_tex_regs[1].s32; 
       case F32_TYPE: 
           x_f32 = reduce_precision(ptx_tex_regs[0].f32,16);
           y_f32 = reduce_precision(ptx_tex_regs[1].f32,15);
   }
   //3D is not supported now
   assert(dimension!=GEOM_MODIFIER_3D); 
   
   //channels should be a multiple of byte in size
   assert(!(cuArray->desc.x%8) and !(cuArray->desc.y%8) and !(cuArray->desc.z%8) and !(cuArray->desc.w%8));
      
   if(texref->normalized){
       x_f32*= texture_width;
       y_f32*= texture_height;
   } else {
       //only valid with normalized mode the wrap and the mirror as well which is not supported here anyway
       assert(texref->addressMode[0]!=cudaAddressModeWrap);
       assert(texref->addressMode[1]!=cudaAddressModeWrap);
   }
   
   //clamping or wrapping each dimension we support, namely x and y
   x_f32 = applyTexAddressingMode(x_f32,texref->addressMode[0],texture_width);
   y_f32 = applyTexAddressingMode(y_f32,texref->addressMode[1],texture_height);
   
   std::vector<samplePointLocation> samplingPoints;   
   samplingPoints = getSamplingPoints(x_f32, y_f32, dimension, texref->filterMode);
   
   //bytes per texture texel
   unsigned texelBytes = (cuArray->desc.w+cuArray->desc.x+cuArray->desc.y+cuArray->desc.z)/8;
   unsigned textureWidthBytes = texture_width * texelBytes;
   
    //registers to save return data
    ptx_reg_t dataX, dataY, dataZ, dataW;
    //initializing all possible data to zero as we will add the numbers based on the factors in the loop using
    //function getTexelData(...)
    dataX.u32 =0; dataX.u64=0; dataX.f32=0; dataX.f64=0;
    dataY.u32 =0; dataY.u64=0; dataY.f32=0; dataY.f64=0;
    dataZ.u32 =0; dataZ.u64=0; dataZ.f32=0; dataZ.f64=0;
    dataW.u32 =0; dataW.u64=0; dataW.f32=0; dataW.f64=0; 
   
   for(int point=0;point<samplingPoints.size();point++){
       new_addr_type reqTexAddr= samplingPoints[point].y * textureWidthBytes; //counting for the y, in case of 1D always y=0
       reqTexAddr+=samplingPoints[point].x * texelBytes; //the address of the texture 
       //samplePointInfo_t spa(reqTexAddr,samplingPoints[point].factor, texelSize); 
       //requetedTexelAddresses.push_back(spa);
       //printf("fetching texel address = %x\n", tex_array_base+reqTexAddr);
       thread->m_last_effective_address.set(tex_array_base+reqTexAddr, point);
       
       float factor = samplingPoints[point].factor;
       void* texelDataAddr = cuArray->texData+reqTexAddr;
       //new_addr_type texelDataAddr = ((new_addr_type)cuArray->texData)+reqTexAddr;
       
       new_addr_type offset =0;
        if(cuArray->desc.x){
            getTexelData(thread, offset,&dataX, factor, to_type,
                    cuArray->desc.x/8, texelDataAddr);
            offset+= cuArray->desc.x/8;
        }
        if(cuArray->desc.y){
            getTexelData(thread, offset,&dataY, factor, to_type,
                    cuArray->desc.y/8, texelDataAddr);
            offset+= cuArray->desc.y/8;
        }
        if(cuArray->desc.z){
            getTexelData(thread, offset,&dataZ, factor, to_type,
                    cuArray->desc.z/8, texelDataAddr);
            offset+= cuArray->desc.z/8;
        }
        if(cuArray->desc.w){
            getTexelData(thread, offset,&dataW, factor, to_type,
                    cuArray->desc.w/8, texelDataAddr);
            offset+= cuArray->desc.w/8;
        }
   }
   
    const struct textureReferenceAttr* texAttr = gpu->get_texattr(texref);
    if (texAttr->m_readmode == cudaReadModeNormalizedFloat) {
        textureNormalizeOutput(cuArray->desc, dataX, dataY, dataZ, dataW);
    } else {
        assert(texAttr->m_readmode == cudaReadModeElementType);
    }
    
    thread->set_vector_operand_values(dst,dataX,dataY,dataZ,dataW);
    thread->m_last_memory_space = tex_space; 
    
}



void txq_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void trap_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void vabsdiff_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void vadd_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void vmad_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void vmax_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void vmin_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void vset_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void vshl_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void vshr_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }
void vsub_impl( const ptx_instruction *pI, ptx_thread_info *thread ) { inst_not_implemented(pI); }

void vote_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   static bool first_in_warp = true;
   static bool and_all;
   static bool or_all;
   static unsigned int ballot_result;
   static std::list<ptx_thread_info*> threads_in_warp;
   static unsigned last_tid;

   if( first_in_warp ) {
      first_in_warp = false;
      threads_in_warp.clear();
      and_all = true;
      or_all = false;
      ballot_result = 0;
      int offset=31;
      while( (offset>=0) && !pI->active(offset) ) 
         offset--;
      assert( offset >= 0 );
      last_tid = (thread->get_hw_tid() - (thread->get_hw_tid()%pI->warp_size())) + offset;
   }

   ptx_reg_t src1_data;
   const operand_info &src1 = pI->src1();
   src1_data = thread->get_operand_value(src1, pI->dst(), PRED_TYPE, thread, 1);

   //predicate value was changed so the lowest bit being set means the zero flag is set.
   //As a result, the value of src1_data.pred must be inverted to get proper behavior
   bool pred_value = !(src1_data.pred & 0x0001);
   bool invert = src1.is_neg_pred();

   threads_in_warp.push_back(thread);
   and_all &= (invert ^ pred_value);
   or_all |= (invert ^ pred_value);

   // vote.ballot
   if (invert ^ pred_value) {
      int lane_id = thread->get_hw_tid() % pI->warp_size(); 
      ballot_result |= (1 << lane_id); 
   }

   if( thread->get_hw_tid() == last_tid ) {
      if (pI->vote_mode() == ptx_instruction::vote_ballot) {
         ptx_reg_t data = ballot_result; 
         for( std::list<ptx_thread_info*>::iterator t=threads_in_warp.begin(); t!=threads_in_warp.end(); ++t ) {
            const operand_info &dst = pI->dst();
            (*t)->set_operand_value(dst,data, pI->get_type(), (*t), pI);
         }
      } else {
         bool pred_value = false; 

         switch( pI->vote_mode() ) {
         case ptx_instruction::vote_any: pred_value = or_all; break;
         case ptx_instruction::vote_all: pred_value = and_all; break;
         case ptx_instruction::vote_uni: pred_value = (or_all ^ and_all); break;
         default:
            abort();
         }
         ptx_reg_t data;
         data.pred = pred_value?0:1; //the way ptxplus handles the zero flag, 1 = false and 0 = true

         for( std::list<ptx_thread_info*>::iterator t=threads_in_warp.begin(); t!=threads_in_warp.end(); ++t ) {
            const operand_info &dst = pI->dst();
            (*t)->set_operand_value(dst,data, PRED_TYPE, (*t), pI);
         }
      }
      first_in_warp = true;
   }
}

void xor_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t src1_data, src2_data, data;

   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();
   const operand_info &src2 = pI->src2();

   unsigned i_type = pI->get_type();
   src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
   src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);

   //the way ptxplus handles predicates: 1 = false and 0 = true
   if(i_type == PRED_TYPE)
      data.pred = ~(~(src1_data.pred) ^ ~(src2_data.pred));
   else
      data.u64 = src1_data.u64 ^ src2_data.u64;

   thread->set_operand_value(dst,data, i_type, thread, pI);
}

void inst_not_implemented( const ptx_instruction * pI ) 
{
   printf("GPGPU-Sim PTX: ERROR (%s:%u) instruction \"%s\" not (yet) implemented\n",
          pI->source_file(), 
          pI->source_line(), 
          pI->get_opcode_cstr() );
   abort();
}

//ptx_reg_t srcOperandModifiers(ptx_reg_t opData, operand_info opInfo, operand_info dstInfo, unsigned type, ptx_thread_info *thread)
//{
//   ptx_reg_t result;
//   memory_space *mem = NULL;
//   size_t size;
//   int t;
//   result.u64=0;
//
//   //complete other cases for reading from memory, such as reading from other const memory
//   if(opInfo.get_addr_space() == global_space)
//   {
//       mem = thread->get_global_memory();
//       type_info_key::type_decode(type,size,t);
//       mem->read(opData.u32,size/8,&result.u64);
//       if( type == S16_TYPE || type == S32_TYPE )
//         sign_extend(result,size,dstInfo);
//   }
//   else if(opInfo.get_addr_space() == shared_space)
//   {
//       mem = thread->m_shared_mem;
//       type_info_key::type_decode(type,size,t);
//       mem->read(opData.u32,size/8,&result.u64);
//
//       if( type == S16_TYPE || type == S32_TYPE )
//         sign_extend(result,size,dstInfo);
//
//   }
//   else if(opInfo.get_addr_space() == const_space)
//   {
//       mem = thread->get_global_memory();
//       type_info_key::type_decode(type,size,t);
//
//       mem->read((opData.u32 + opInfo.get_const_mem_offset()),size/8,&result.u64);
//
//       if( type == S16_TYPE || type == S32_TYPE )
//         sign_extend(result,size,dstInfo);
//   }
//   else
//   {
//       result = opData;
//   }
//
//   if(opInfo.get_operand_lohi() == 1)
//   {
//       result.u64 = result.u64 & 0xFFFF;
//   }
//   else if(opInfo.get_operand_lohi() == 2)
//   {
//        result.u64 = (result.u64>>16) & 0xFFFF;
//   }
//
//   if(opInfo.get_operand_neg() == true) {
//      result.f32 = -result.f32;
//   }
//
//   return result;
//}

void getNormilizedRGBA(C_DATA_TYPE color, float * r, float * g, float * b, float * a){
    unsigned char ac = (color>>24)%256;
    unsigned char rc = (color>>16)%256;
    unsigned char gc = (color>>8 )%256;
    unsigned char bc = (color>>0 )%256; 
    *a = ((float)ac)/255.0;
    *r = ((float)rc)/255.0;
    *g = ((float)gc)/255.0;
    *b = ((float)bc)/255.0;
}


float getBlendFactor(GLenum blendMode, float srcColor, float dstColor,
                        float blendColor, float srcAlpha, float dstAlpha, float blendAlpha){
    float blendFactor;
    switch(blendMode){
        case GL_ZERO: blendFactor=0.0; break;
        case GL_ONE: blendFactor= 1.0; break;
        case GL_DST_COLOR: blendFactor = dstColor; break;
        case GL_ONE_MINUS_DST_COLOR: blendFactor = 1.0 - dstColor; break;
        case GL_SRC_ALPHA: blendFactor = srcAlpha; break;
        case GL_ONE_MINUS_SRC_ALPHA: blendFactor = 1.0 - srcAlpha; break;
        case GL_DST_ALPHA: blendFactor = dstAlpha; break;
        case GL_ONE_MINUS_DST_ALPHA: blendFactor = 1.0 - dstAlpha; break;
        case GL_SRC_ALPHA_SATURATE: 
            if(srcAlpha < (1.0 - dstAlpha))
                blendFactor = srcAlpha;
            else 
                blendFactor = 1.0 - dstAlpha;
            break;
        case GL_CONSTANT_COLOR: blendFactor = blendColor; break;
        case GL_ONE_MINUS_CONSTANT_COLOR: blendFactor = 1.0 - blendColor; break;
        case GL_CONSTANT_ALPHA: blendFactor = blendAlpha; break;
        case GL_ONE_MINUS_CONSTANT_ALPHA:  blendFactor = 1.0 - blendAlpha; break;
        case GL_SRC_COLOR: blendFactor = srcColor; break;
        case GL_ONE_MINUS_SRC_COLOR: blendFactor = 1.0 - srcColor; break;
        default: printf("gpgpusim: Unknown blending mode %u\n",blendMode);
        assert(0);
    }
    return blendFactor;
}

C_DATA_TYPE blend(float as, float rs, float bs, float gs, float ad, float rd, float bd, float gd){
    //now we only support one type of blending
    GLenum blend_src_rgb, blend_dst_rgb, blend_src_alpha, blend_dst_alpha, eqnRGB, eqnAlpha;
    float blendColor[4]; 
    float ar,rr,gr,br;
    getBlendingMode(&blend_src_rgb,&blend_dst_rgb,&blend_src_alpha,&blend_dst_alpha,&eqnRGB, &eqnAlpha, blendColor);
    
    float rsFactor = getBlendFactor(blend_src_rgb,rs, rd, blendColor[RCOMP], as, ad, blendColor[ACOMP]);
    float rdFactor = getBlendFactor(blend_dst_rgb,rs, rd, blendColor[RCOMP], as, ad, blendColor[ACOMP]);
    
    float gsFactor = getBlendFactor(blend_src_rgb,gs, gd, blendColor[GCOMP], as, ad, blendColor[ACOMP]);
    float gdFactor = getBlendFactor(blend_dst_rgb,gs, gd, blendColor[GCOMP], as, ad, blendColor[ACOMP]);
    
    float bsFactor = getBlendFactor(blend_src_rgb,bs, bd, blendColor[BCOMP], as, ad, blendColor[ACOMP]);
    float bdFactor = getBlendFactor(blend_dst_rgb,bs, bd, blendColor[BCOMP], as, ad, blendColor[ACOMP]);
    
    float asFactor = getBlendFactor(blend_src_alpha,as, ad, blendColor[ACOMP], as, ad, blendColor[ACOMP]);
    float adFactor = getBlendFactor(blend_dst_alpha,as, ad, blendColor[ACOMP], as, ad, blendColor[ACOMP]);
    
    switch(eqnRGB){
        case GL_FUNC_ADD: 
            rr = rs * rsFactor + rd * rdFactor;
            gr = gs * gsFactor + gd * gdFactor;
            br = bs * bsFactor + bd * bdFactor;
            break;
        case GL_FUNC_SUBTRACT: 
            rr = rs * rsFactor - rd * rdFactor;
            gr = gs * gsFactor - gd * gdFactor;
            br = bs * bsFactor - bd * bdFactor;
            break;
        case GL_FUNC_REVERSE_SUBTRACT:
            rr = rd * rdFactor - rs * rsFactor;
            gr = gd * gdFactor - gs * gsFactor;
            br = bd * bdFactor - bs * bsFactor;
            break;
        default: 
            printf("gpgpusim: Unknown RGB blending function mode %d\n",eqnRGB); 
            assert(0);
    }
    
    switch(eqnAlpha){
        case GL_FUNC_ADD:
            ar = as * asFactor + ad * adFactor; break;
        case GL_FUNC_SUBTRACT:
            ar = as * asFactor - ad * adFactor; break;
        case GL_FUNC_REVERSE_SUBTRACT:
            ar = ad * adFactor - as * asFactor; break;
        default: 
            printf("gpgpusim: Unknown alpha blending function mode %d\n",eqnRGB); 
            assert(0);
    }
        
    C_DATA_TYPE car = ar*255.0;
    C_DATA_TYPE crr = rr*255.0;
    C_DATA_TYPE cgr = gr*255.0;
    C_DATA_TYPE cbr = br*255.0;
    C_DATA_TYPE result;
    cbr = cbr;
    cgr = cgr<<8;
    crr = crr<<16;
    car = car<<24;
    result = cbr + cgr + crr + car;
    return result;
}

C_DATA_TYPE blendU32(C_DATA_TYPE color_src, C_DATA_TYPE color_dst){
    float as, rs, bs, gs, ad, rd, bd, gd;
    getNormilizedRGBA(color_src,&rs,&gs,&bs,&as);
    getNormilizedRGBA(color_dst,&rd,&gd,&bd,&ad);
    return blend(as,rs,bs,gs,ad,rd,bd,gd);
}

C_DATA_TYPE get_final_color_result(zrop_callback_t::zrop_input_t color, new_addr_type addr) {
    extern gpgpu_sim *g_the_gpu;

    if (isBlendingEnabled()) {
        assert(!isDepthTestEnabled());
        float as, rs, gs, bs;
        getNormilizedRGBA(color, &rs, &gs, &bs, &as);
        C_DATA_TYPE dest;
        g_the_gpu->get_global_memory()->read(addr, C_DATA_SIZE, &dest);
        float rd, bd, ad, gd;
        getNormilizedRGBA(dest, &rd, &gd, &bd, &ad);
        C_DATA_TYPE resultColor = blend(as, rs, bs, gs, ad, rd, bd, gd);
        return resultColor;
    }
    
    return color;
}

//bool z_st_callback(const class inst_t* instruction,class ptx_thread_info* thread, zrop_callback_t::zrop_input_t depth, zrop_callback_t::zrop_input_t color, new_addr_type addr)
//{
//    const ptx_instruction *pI = dynamic_cast<const ptx_instruction*>(instruction);
//    Z_DATA_TYPE storedDepth = globalZBuffer.readZValue(addr);
//    bool write = depth Z_IS_CLOSER_THAN storedDepth;
//    extern gpgpu_sim *g_the_gpu;
//    
//    if(isBlendingEnabled()){
//        assert(!isDepthTestEnabled());
//        g_the_gpu->get_global_memory()->write(addr,C_DATA_SIZE,&color,thread,pI);
//        return true;
//    }
//    
//    if(!isDepthTestEnabled()){
//        g_the_gpu->get_global_memory()->write(addr,C_DATA_SIZE,&color,thread,pI);
//        return true;
//    }
//    
//    if(write){
//        //write to the z memory
//        globalZBuffer.writeZValue(depth,addr,thread,instruction);
//        //z call back can be called by fetches that does not correspond to real threads so we use g_the_gpu, when this always used with real threads
//        //then we can use thread->getGlobalMemory
//        g_the_gpu->get_global_memory()->write(addr,C_DATA_SIZE,&color,thread,pI);
//    }
//    return write;
//}
//
////zwrite operation implementation, if the write operation is to a z allocated location 
////then the write operation will be done using callbacks from the z-unit
//void z_st( const ptx_instruction *pI, ptx_thread_info *thread ) 
//{
//   const operand_info &dst = pI->dst();
//   const operand_info &src1 = pI->src1();
//   unsigned type = pI->get_type();
//   ptx_reg_t addr_reg = thread->get_operand_value(dst, dst, type, thread, 1);
//   memory_space_t space = pI->get_space();
//   unsigned vector_spec = pI->get_vector();
//
//   addr_t addr = addr_reg.u32;
//   assert(space.get_type()==global_space);
//   assert(vector_spec==V2_TYPE); //should be vector instruction with 2 values depth and color
//   
//   size_t size;
//   int t;
//   type_info_key::type_decode(type,size,t);
//   assert(size==32);
//   ptx_reg_t* ptx_regs = new ptx_reg_t[2]; 
//   thread->get_vector_operand_values(src1, ptx_regs, 2); 
//   thread->m_last_memory_space = space;
//   thread->m_last_effective_address.set(addr);
//   
//   C_DATA_TYPE final_color = get_final_color_result(ptx_regs[0].u32,addr);
//   
//   if(isDepthTestEnabled() || isBlendingEnabled()){
//       thread->m_last_zrop_callback.function = z_st_callback;
//       thread->m_last_zrop_callback.instruction = pI; 
//       thread->m_last_zrop_callback.color = final_color;
//       thread->m_last_zrop_callback.depth = ptx_regs[1].u32;
//       thread->m_last_zrop_callback.address = addr;
//   } 
//   else z_st_callback(pI, thread, ptx_regs[1].u32, final_color, addr);
//
//   delete [] ptx_regs;
//}

void st_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   const operand_info &dst = pI->dst();
   const operand_info &src1 = pI->src1(); //may be scalar or vector of regs
   unsigned type = pI->get_type();
   ptx_reg_t addr_reg = thread->get_operand_value(dst, dst, type, thread, 1);
   ptx_reg_t data;
   memory_space_t space = pI->get_space();
   unsigned vector_spec = pI->get_vector();

   memory_space *mem = NULL;
   addr_t addr = addr_reg.u64;
//   //calling the z_st if the address is in the z buffer, should be done as separate instruction later
//   if(globalZBuffer.isInZBuffers(addr)){
//       z_st(pI,thread);
//       return;
//   }
   decode_space(space,thread,dst,mem,addr);
   thread->get_gpu()->gem5CudaGPU->getCudaCore(thread->get_hw_sid())->record_st(space);

   if (space.get_type() != global_space &&
       space.get_type() != const_space &&
       space.get_type() != local_space) {
   size_t size;
   int t;
   type_info_key::type_decode(type,size,t);

   if (!vector_spec) {
      data = thread->get_operand_value(src1, dst, type, thread, 1);
      mem->write(addr,size/8,&data.s64,thread,pI);
   } else {
      if (vector_spec == V2_TYPE) {
         ptx_reg_t* ptx_regs = new ptx_reg_t[2]; 
         thread->get_vector_operand_values(src1, ptx_regs, 2); 
         mem->write(addr,size/8,&ptx_regs[0].s64,thread,pI);
         mem->write(addr+size/8,size/8,&ptx_regs[1].s64,thread,pI);
         delete [] ptx_regs;
      }
      if (vector_spec == V3_TYPE) {
         ptx_reg_t* ptx_regs = new ptx_reg_t[3]; 
         thread->get_vector_operand_values(src1, ptx_regs, 3); 
         mem->write(addr,size/8,&ptx_regs[0].s64,thread,pI);
         mem->write(addr+size/8,size/8,&ptx_regs[1].s64,thread,pI);
         mem->write(addr+2*size/8,size/8,&ptx_regs[2].s64,thread,pI);
         delete [] ptx_regs;
      }
      if (vector_spec == V4_TYPE) {
         ptx_reg_t* ptx_regs = new ptx_reg_t[4]; 
         thread->get_vector_operand_values(src1, ptx_regs, 4); 
         mem->write(addr,size/8,&ptx_regs[0].s64,thread,pI);
         mem->write(addr+size/8,size/8,&ptx_regs[1].s64,thread,pI);
         mem->write(addr+2*size/8,size/8,&ptx_regs[2].s64,thread,pI);
         mem->write(addr+3*size/8,size/8,&ptx_regs[3].s64,thread,pI);
         delete [] ptx_regs;
      }
   }
   }
   //printf("writing result to addres %x\n", addr);
   thread->m_last_effective_address.set(addr);
   thread->m_last_memory_space = space; 
}

void frc_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{ 
   ptx_reg_t a, d;
   const operand_info &dst  = pI->dst();
   const operand_info &src1 = pI->src1();

   unsigned i_type = pI->get_type();
   a = thread->get_operand_value(src1, dst, i_type, thread, 1);


   switch ( i_type ) {
   case F32_TYPE: d.f32 = floor(a.f32); break;
   case F64_TYPE: case FF64_TYPE: d.f64 = floor(a.f64); break;
   default:
      printf("Execution error: type mismatch with instruction\n");
      assert(0);
      break;
   }

   thread->set_operand_value(dst,d, i_type, thread, pI);
}

void blend_impl(const ptx_instruction *pI, ptx_thread_info *thread) {
    ptx_reg_t src1_data, src2_data, data;

    const operand_info &dst = pI->dst();
    const operand_info &src1 = pI->src1();
    const operand_info &src2 = pI->src2();

    unsigned i_type = pI->get_type();
    assert(i_type == U32_TYPE); //what we use for blending for now
    
    src1_data = thread->get_operand_value(src1, dst, i_type, thread, 1);
    src2_data = thread->get_operand_value(src2, dst, i_type, thread, 1);
    
    data.u32 = blendU32(src1_data.u32,src2_data.u32);

    thread->set_operand_value(dst, data, i_type, thread, pI);
}

void printf_impl( const ptx_instruction *pI, ptx_thread_info *thread ) 
{
   const operand_info &dst  = pI->dst();  
   const operand_info &src1 = pI->src1();
   unsigned i_type = pI->get_type();
   ptx_reg_t number = thread->get_operand_value(dst, dst, i_type, thread, 1);
   ptx_reg_t value = thread->get_operand_value(src1, dst, i_type, thread, 1);
   unsigned uniqueThreadId = thread->get_uid_in_kernel();

   switch( i_type ) {
      case S8_TYPE:
      case S16_TYPE:
      case S32_TYPE:
      case S64_TYPE:
      case U8_TYPE:
      case U16_TYPE:
      case U32_TYPE:
      case B8_TYPE:
      case B16_TYPE:
      case B32_TYPE:
      case U64_TYPE:
      case B64_TYPE:
         printf("GPGPU-Sim PTX: printf(%d, tid=%d) ==> (0x%llx = %d)\n", number.u32, uniqueThreadId, value.u64, value.u64);
         break;
      case F16_TYPE:
      case F32_TYPE:
      case F64_TYPE:
      case FF64_TYPE:
         printf("GPGPU-Sim PTX: printf(%d, tid=%d) ==> %f\n", number.u32, uniqueThreadId, value.f64);
         break;
      default:
         assert(0); break;
      }
}
