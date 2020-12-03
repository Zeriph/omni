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
#if !defined(OMNI_SEQ_T_HPP)
#define OMNI_SEQ_T_HPP 1
/*
    The default container type used throughout the Omni library.
    This is to allow a user of this code to change the STL container type used
    in portions of this code without actually touching the code. This is in case
    a user wishes to use the Omni library in an environment that only has support
    for one of the STL sequence containers (only support for list, not vector or 
    deque for example)
    
    Note that this does not preclude one from using a different container for their
    needs in different areas of code. This macro is merely here to allow the user
    finer control over how the library operates.
    
    DEV_NOTE: We did not typedef because we are dealing with templated types, we merely
    want to allow the user to choose the underlying container type without having to
    re-implement a lot of extra code (i.e. typedef-ing and wrapping in another template).
    Hence the names with _T postfix, to indicate that it is renamed
    type, NOT a typedefd type (which would indicate specific implementation)
*/

#if defined(OMNI_SEQUENCE_CONTAINER_TYPE)
    #define OMNI_SEQ_H_FW <OMNI_SEQUENCE_CONTAINER_TYPE>
    #define OMNI_SEQ_T_FW std::OMNI_SEQUENCE_CONTAINER_TYPE
#endif

// default type of std::deque
#if !defined(OMNI_SEQ_H_FW)
    #define OMNI_SEQ_H_FW <deque>
#endif
#if !defined(OMNI_SEQ_T_FW)
    #define OMNI_SEQ_T_FW std::deque
#endif

#include OMNI_SEQ_H_FW
#include <algorithm>
#include <iterator>

#define OMNI_SEQUENCE_T OMNI_SEQ_T_FW
#define OMNI_SEQ_T OMNI_SEQ_T_FW
#define omni_sequence_t OMNI_SEQ_T_FW
#define omni_seq_t OMNI_SEQ_T_FW

#define omni_foreach(t, n, v) for (omni_seq_t<t>::iterator n = v.begin(); n != v.end(); ++n)
#define omni_foreach_const(t, n, v) for (omni_seq_t<t>::const_iterator n = v.begin(); n != v.end(); ++n)
#define omni_foreach_c(t, n, v) omni_foreach_const(t, n, v)

#define std_foreach(t, n, v) for (t::iterator n = v.begin(); n != v.end(); ++n)
#define std_foreach_const(t, n, v) for (t::const_iterator n = v.begin(); n != v.end(); ++n)
#define std_foreach_c(t, n, v) std_foreach_const(t, n, v)

namespace omni {
    namespace sequence {
        template < template < class, class > class std_seq_t, class T, class std_allocator_t >
        inline bool equal(const std_seq_t<T, std_allocator_t >& a, const std_seq_t<T, std_allocator_t >& b)
        {
            if (a.size() != b.size()) {
                return false;
            }
            return std::equal(a.begin(), a.end(), b.begin());
        }
        template < template < class, class > class std_seq_t, class T, class std_allocator_t >
        inline bool equals(const std_seq_t<T, std_allocator_t >& a, const std_seq_t<T, std_allocator_t >& b)
        {
            if (a.size() != b.size()) {
                return false;
            }
            return std::equal(a.begin(), a.end(), b.begin());
        }

        template < template < class, class > class std_seq_t, class T >
        inline bool equal(const std_seq_t<T, std::allocator<T> >& a, const std_seq_t<T, std::allocator<T> >& b)
        {
            if (a.size() != b.size()) {
                return false;
            }
            return std::equal(a.begin(), a.end(), b.begin());
        }
        template < template < class, class > class std_seq_t, class T >
        inline bool equals(const std_seq_t<T, std::allocator<T> >& a, const std_seq_t<T, std::allocator<T> >& b)
        {
            if (a.size() != b.size()) {
                return false;
            }
            return std::equal(a.begin(), a.end(), b.begin());
        }

        template < class InputIterator >
        inline bool equal(InputIterator start1, InputIterator end1, InputIterator start2, InputIterator end2)
        {
            while ((start1 != end1) && (start2 != end2)) {
                if (*start1 != *start2) {
                    return false;
                }
                ++start1;
                ++start2;
            }
            return (start1 == end1) && (start2 == end2);
        }
        template < class InputIterator >
        inline bool equals(InputIterator start1, InputIterator end1, InputIterator start2, InputIterator end2)
        {
            while ((start1 != end1) && (start2 != end2)) {
                if (*start1 != *start2) {
                    return false;
                }
                ++start1;
                ++start2;
            }
            return (start1 == end1) && (start2 == end2);
        }

        template < template < class, class > class std_seq_t, class T, class std_allocator_t, class InputIterator >
        void add_range(std_seq_t<T, std_allocator_t >& array, InputIterator start, InputIterator end)
        {
            while (start != end) {
                array.push_back(start);
                ++start;
            }
        }

        template < template < class, class > class std_seq_t, class T, class InputIterator >
        void add_range(std_seq_t<T, std::allocator<T> >& array, InputIterator start, InputIterator end)
        {
            while (start != end) {
                array.push_back(*start);
                ++start;
            }
        }

        template < template < class, class > class std_seq_t, class T, class std_allocator_t >
        void add_range(std_seq_t<T, std_allocator_t >& array1, const std_seq_t<T, std_allocator_t >& array2)
        {
            for (std::size_t i = 0; i < array2.size(); ++i) {
                array1.push_back(array2[i]);
            }
        }

        template < template < class, class > class std_seq_t, class T >
        void add_range(std_seq_t<T, std::allocator<T> >& array1, const std_seq_t<T, std::allocator<T> >& array2)
        {
            for (std::size_t i = 0; i < array2.size(); ++i) {
                array1.push_back(array2[i]);
            }
        }
    }
}

#endif // OMNI_SEQ_T_HPP
