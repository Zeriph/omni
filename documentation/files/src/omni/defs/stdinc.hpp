/*
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
#if !defined(OMNI_STDINC_HPP)
#define OMNI_STDINC_HPP 1

/*
    This file is simply a helper header to include some of the STL for easy
    access. It should be noted that even if you define something like OMNI_NO_STD_CLIMITS,
    if a specific TU needs that header, it will still include it in there, just not
    globally in here.
*/

#if !defined(OMNI_NO_STDINC)
    #if !defined(OMNI_NO_STD_VECTOR)
        #include <vector>
    #endif
    #if !defined(OMNI_NO_STD_MAP)
        #include <map>
    #endif
    #if !defined(OMNI_NO_STD_ALGORITHM)
        #include <algorithm>
    #endif
    #if !defined(OMNI_NO_STD_ITERATOR)
        #include <iterator>
    #endif
    #if !defined(OMNI_NO_STD_CLIMITS)
        #include <climits>
    #endif
    #if !defined(OMNI_NO_STD_DEQUE)
        #include <deque>
    #endif
    #if !defined(OMNI_NO_STD_LIST)
        #include <list>
    #endif
    #if !defined(OMNI_NO_STD_SET)
        #include <set>
    #endif
    #if !defined(OMNI_NO_STD_BITSET)
        #include <bitset>
    #endif
    #if !defined(OMNI_NO_STD_MEMORY)
        #include <memory>
    #endif
#endif

#endif // OMNI_STDINC_HPP
