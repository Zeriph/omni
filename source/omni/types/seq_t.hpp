/*
 * Copyright (c) 2017, Zeriph Enterprises
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Neither the name of Zeriph, Zeriph Enterprises, LLC, nor the names
 *   of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
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
#if !defined(OMNI_SEQ_T_HPP)
#define OMNI_SEQ_T_HPP 1
/*
    The default container type used throughout the Omni framework.
    This is to allow a user of this code to change the STL container type used
    in portions of this code without actually touching the code. This is in case
    a user wishes to use the Omni framework in an environment that only has support
    for one of the STL sequence containers (only support for list, not vector or 
    deque for example)
    
    Note that this does not preclude one from using a different container for their
    needs in different areas of code. This macro is merely here to allow the user
    finer control over how the framework operates.
    
    DEV_NOTE: We didn't typedef because we are dealing with templated types, we merely
    want to allow the user to choose the underlying container type without having to
    reimplement a lot of extra code (i.e. typedef'ing and wrapping in another template).
    Hence the names with _T postfix, to indicate that it is renamed
    type, NOT a typedef'd type (which would indicate specific implementation)
*/

#if defined(OMNI_SEQCONT_TYPE)
    #if OMNI_SEQCONT_TYPE == "list"
        #define OMNI_SEQ_H <list>
        #define OMNI_SEQ_T std::list
    #elif OMNI_SEQCONT_TYPE == "vector"
        #define OMNI_SEQ_H <vector>
        #define OMNI_SEQ_T std::vector
    #endif
#endif // OMNI_SEQCONT_TYPE
// default type of std::deque
#if !defined(OMNI_SEQ_H)
    #define OMNI_SEQ_H <deque>
#endif
#if !defined(OMNI_SEQ_T)
    #define OMNI_SEQ_T std::deque
#endif
#include OMNI_SEQ_H
#include <algorithm>
#include <iterator> 

#endif // OMNI_SEQ_T_HPP
