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
#if !defined(OMNI_NULL_DEF_HPP)
#define OMNI_NULL_DEF_HPP 1

/*
    As the NULL macro is implementation defined and not all compilers will support
    the nullptr keyword, the default for null pointer values is to zeroize them, that is,
    the preferred way to initialize pointer types to the null value is to set them to the 0
    address over setting to NULL or nullptr. Example:

    int* val = 0;       <- preferred way
    int* val = NULL;    <- OK, but NULL could be anything, so not really safe
    int* val = nullptr; <- OK and expresses intent better, but not all compilers support this

    We do not want to overuse macros through the library, but in this scenario, it is also
    preferable to avoid being able to do something like this:

    static const int nullptr = 0;
    int* val = &nullptr;

    &nullptr is not allowed in C++11 and additional checks would need to be in place to avoid this in
    C++11 compilers and not in previous editions; as well int* val = nullptr could have an implicit cast
    since you are referencing a named variable (nullptr), this is not the case in C++11 with the nullptr keyword. 

    So to avoid all of this, we will give the user the option to choose (or define) their null pointer
    value. Defining OMNI_NULL_PTR sets the C++11 nullptr keyword while OMNI_NULL_MACRO will use the
    implementation defined NULL macro, and if nothing, the default is to use 0. While the macro name
    OMNI_NULL is more verbose than 0/NULL/nullptr, it does express the intent better than just plain 0.
*/
#if defined(OMNI_NULL_PTR) && defined(OMNI_NULL_MACRO)
    #error "Can not define OMNI_NULL_PTR and OMNI_NULL_MACRO together"
#endif
#if (defined(OMNI_NULL_PTR) || defined(OMNI_NULL_MACRO)) && defined(OMNI_NULL)
    #error "Can not define OMNI_NULL as well as OMNI_NULL_PTR or OMNI_NULL_MACRO"
#endif
#if defined(OMNI_NULL_PTR)
    #define OMNI_NULL nullptr
#endif
#if defined(OMNI_NULL_MACRO)
    #define OMNI_NULL NULL
#endif
#if !defined(OMNI_NULL)
    #define OMNI_NULL 0
#endif

#endif // OMNI_NULL_DEF_HPP
