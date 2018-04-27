/*
 * This file is part of the Omni C++ framework.
 * 
 * Copyright (c), Zeriph Enterprises
 * All rights reserved.
 * 
 * Contributor(s):
 * Zechariah Perez, omni (at) zeriph (dot) com
 * 
 * THIS SOFTWARE IS PROVIDED BY ZERIPH AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ZERIPH AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(OMNI_DELEGATES_HPP)
#define OMNI_DELEGATES_HPP 1

#include <omni/delegate/0.hpp>
#include <omni/delegate/1.hpp>
#include <omni/delegate/2.hpp>
#include <omni/delegate/3.hpp>
#include <omni/delegate/4.hpp>
#include <omni/delegate/5.hpp>
#include <omni/delegate/6.hpp>
#include <omni/delegate/7.hpp>
#include <omni/delegate/8.hpp>
#include <omni/delegate/9.hpp>
#include <omni/delegate/10.hpp>
#include <omni/delegate/11.hpp>
#include <omni/delegate/12.hpp>
#include <omni/delegate/13.hpp>
#include <omni/delegate/14.hpp>
#include <omni/delegate/15.hpp>
#include <omni/delegate/16.hpp>

#define OMNI_DEL0_FW(a) omni::delegate<a>
#define OMNI_DEL1_FW(a,b) omni::delegate1<a,b>
#define OMNI_DEL2_FW(a,b,c) omni::delegate2<a,b,c>
#define OMNI_DEL3_FW(a,b,c,d) omni::delegate3<a,b,c,d>
#define OMNI_DEL4_FW(a,b,c,d,e) omni::delegate4<a,b,c,d,e>
#define OMNI_DEL5_FW(a,b,c,d,e,f) omni::delegate5<a,b,c,d,e,f>
#define OMNI_DEL6_FW(a,b,c,d,e,f,g) omni::delegate6<a,b,c,d,e,f,g>
#define OMNI_DEL7_FW(a,b,c,d,e,f,g,h) omni::delegate7<a,b,c,d,e,f,g,h>
#define OMNI_DEL8_FW(a,b,c,d,e,f,g,h,i) omni::delegate8<a,b,c,d,e,f,g,h,i>
#define OMNI_DEL9_FW(a,b,c,d,e,f,g,h,i,j) omni::delegate9<a,b,c,d,e,f,g,h,i,j>
#define OMNI_DEL10_FW(a,b,c,d,e,f,g,h,i,j,k) omni::delegate10<a,b,c,d,e,f,g,h,i,j,k>
#define OMNI_DEL11_FW(a,b,c,d,e,f,g,h,i,j,k,l) omni::delegate11<a,b,c,d,e,f,g,h,i,j,k,l>
#define OMNI_DEL12_FW(a,b,c,d,e,f,g,h,i,j,k,l,m) omni::delegate12<a,b,c,d,e,f,g,h,i,j,k,l,m>
#define OMNI_DEL13_FW(a,b,c,d,e,f,g,h,i,j,k,l,m,n) omni::delegate13<a,b,c,d,e,f,g,h,i,j,k,l,m,n>
#define OMNI_DEL14_FW(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o) omni::delegate14<a,b,c,d,e,f,g,h,i,j,k,l,m,n,o>
#define OMNI_DEL15_FW(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) omni::delegate15<a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p>
#define OMNI_DEL16_FW(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q) omni::delegate16<a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q>

// DEV_NOTE: this is here for MS compilers and how they expand macro variables and the __VA_ARGS__
#define OMNI_EXPAND_FW(x) x

#define OMNI_DELEGATE_GET_MACRO_FW(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,NAME,...) OMNI_EXPAND_FW( NAME )
#define OMNI_DELEGATE_DEF_FW(...) OMNI_EXPAND_FW( OMNI_DELEGATE_GET_MACRO_FW(__VA_ARGS__, OMNI_DEL16_FW, OMNI_DEL15_FW, OMNI_DEL14_FW, OMNI_DEL13_FW, OMNI_DEL12_FW, OMNI_DEL11_FW, OMNI_DEL10_FW, OMNI_DEL9_FW, OMNI_DEL8_FW, OMNI_DEL7_FW, OMNI_DEL6_FW, OMNI_DEL5_FW, OMNI_DEL4_FW, OMNI_DEL3_FW, OMNI_DEL2_FW, OMNI_DEL1_FW, OMNI_DEL0_FW) )OMNI_EXPAND_FW( (__VA_ARGS__) )

#define OMNI_DELEGATE_GET_BIND_MACRO_FW(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,Class,Function,Obj,NAME,...) OMNI_EXPAND_FW( NAME )
#define OMNI_DELEGATE_BIND_DEF_FW(...) OMNI_EXPAND_FW( OMNI_DELEGATE_GET_BIND_MACRO_FW(__VA_ARGS__, OMNI_BIND16, OMNI_BIND15, OMNI_BIND14, OMNI_BIND13, OMNI_BIND12, OMNI_BIND11, OMNI_BIND10, OMNI_BIND9, OMNI_BIND8, OMNI_BIND7, OMNI_BIND6, OMNI_BIND5, OMNI_BIND4, OMNI_BIND3, OMNI_BIND2, OMNI_BIND1, OMNI_BIND0) )OMNI_EXPAND_FW( (__VA_ARGS__ ) )
#define OMNI_DELEGATE_BIND_CONST_DEF_FW(...) OMNI_EXPAND_FW( OMNI_DELEGATE_GET_BIND_MACRO_FW(__VA_ARGS__, OMNI_BIND16_CONST, OMNI_BIND15_CONST, OMNI_BIND14_CONST, OMNI_BIND13_CONST, OMNI_BIND12_CONST, OMNI_BIND11_CONST, OMNI_BIND10_CONST, OMNI_BIND9_CONST, OMNI_BIND8_CONST, OMNI_BIND7_CONST, OMNI_BIND6_CONST, OMNI_BIND5_CONST, OMNI_BIND4_CONST, OMNI_BIND3_CONST, OMNI_BIND2_CONST, OMNI_BIND1_CONST, OMNI_BIND0_CONST) )OMNI_EXPAND_FW( (__VA_ARGS__) )

#define OMNI_DELEGATE(...) OMNI_EXPAND_FW( OMNI_DELEGATE_DEF_FW(__VA_ARGS__) )
#define omni_delegate(...) OMNI_EXPAND_FW( OMNI_DELEGATE_DEF_FW(__VA_ARGS__) )

#define OMNI_BIND(...) OMNI_EXPAND_FW( OMNI_DELEGATE_BIND_DEF_FW(__VA_ARGS__) )
#define omni_bind(...) OMNI_EXPAND_FW( OMNI_DELEGATE_BIND_DEF_FW(__VA_ARGS__) )

#define OMNI_BIND_CONST(...) OMNI_EXPAND_FW( OMNI_DELEGATE_BIND_CONST_DEF_FW(__VA_ARGS__) )
#define omni_bind_const(...) OMNI_EXPAND_FW( OMNI_DELEGATE_BIND_CONST_DEF_FW(__VA_ARGS__) )

#endif // OMNI_DELEGATES_HPP

