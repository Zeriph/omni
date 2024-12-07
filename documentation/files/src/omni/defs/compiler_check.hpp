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
#if !defined(OMNI_COMPILER_CHECK_HPP)
#define OMNI_COMPILER_CHECK_HPP 1

/*
    DEV_NOTE: unlike some of the other "macro" check files, this one will include
    the compiler being used, the language detected (e.g. C++03/11/etc.), as well
    as any POSIX versions and standard libraries used (e.g. GnuLibC vs Bionic Libc)
*/

/*
    DEV_NOTE: As of the inclusion of this file, there are no areas of Omni that
    utilize compiler specific code and as a rule-of-thumb for Omni, we try
    to avoid compiler specific code to be as cross-system compatible as
    possible. However, that does not preclude one from using compiler-specific code
    if it makes sense to enable certain optimizations in the source.
    
    Please note that just because a specific macro is defined below, does not
    mean the library has been tested to work in that environment. OMNI_COMPILER_ORACLE_PRO_C
    will be defined, for instance, if the __SUNPRO_CC macro is defined (usually by
    the compiler), but this does not mean we have been able to test/build the
    library in a direct (or even emulated) using a Sun Pro*C compiler.
    
    That being said, the purpose of this file is to give helper macros for
    possible compiler compilation detection, keyword being possible. Should
    a need ever arise to force the Omni library to build for a separate compiler
    (e.g. building an ARM version on an Intel compiler), one can define the
    OMNI_COMPILER_CHECK_IGNORE preprocessor define and specify which ever compiler
    via one of the below defines.

    DEV_NOTE: These macro's do not determine the actual compiler used,
    instead these are merely guesses based on common compilation defines to
    determine what compiler the library is being compiled for.

    DEV_NOTE: We are not including the C compilers, only C++ since this is a 
    C++ only library and cannot compile with any C-only compilers
*/ 

#if defined(OMNI_COMPILER_CHECK_IGNORE)
    /* Define here or as part of build. */
#else
    // https://sourceforge.net/p/predef/wiki/Compilers/

    // ARM Compiler
    #if defined(__CC_ARM) || defined(__ARMCC_VERSION)
        #define OMNI_COMPILER_ARM
    #endif
    // Borland C++
    #if defined(__BORLANDC__) || defined(__CODEGEARC__)
        #define OMNI_COMPILER_BORLAND
    #endif
    //Clang
    #if defined(__clang__)
        #define OMNI_COMPILER_CLANG
    #endif
    // Comeau C++
    #if defined(__COMO__)
        #define OMNI_COMPILER_COMEAU
    #endif
    // Compaq C/C++
    #if defined(__DECC) || defined(__DECC_VER) || defined(__DECCXX) || defined(__DECCXX_VER) || defined(__VAXC) || defined(VAXC)
        #define OMNI_COMPILER_COMPAQ
    #endif
    // Diab C/C++
    #if defined(__DCC__)
        #define OMNI_COMPILER_DIAB
    #endif
    // Digital Mars
    #if defined(__DMC__)
        #define OMNI_COMPILER_DIGITAL_MARS
    #endif
    // Dignus Systems/C++
    #if defined(__SYSC__)
        #define OMNI_COMPILER_DIGNUS
    #endif
    // DJGPP
    #if defined(__DJGPP__) || defined(__GO32__)
        #define OMNI_COMPILER_DJGPP
    #endif
    // EDG C++ Frontend
    #if defined(__EDG__)
        #define OMNI_COMPILER_EDG
    #endif
    // EKOPath
    #if defined(__PATHCC__)
        #define OMNI_COMPILER_EKOPATH
    #endif
    // Fujitsu C++
    #if defined(__FCC_VERSION)
        #define OMNI_COMPILER_FUJITSU
    #endif
    // GCC C/C++
    #if defined(__GNUC__)
        #define OMNI_COMPILER_GCC
    #endif
    // Green Hill C/C++
    #if defined(__ghs__)
        #define OMNI_COMPILER_GREEN_HILL
    #endif
    // HP aC++
    #if defined(__HP_aCC)
        #define OMNI_COMPILER_HP
    #endif
    // IAR C/C++
    #if defined(__IAR_SYSTEMS_ICC__)
        #define OMNI_COMPILER_IAR
    #endif
    // IBM XL
    #if defined(__ibmxl__) || defined(__xlC__)
        #define OMNI_COMPILER_IBM
    #endif
    // IBM z/OS XL C/C++
    #if defined(__IBMC__) || defined(__IBMCPP__)
        #define OMNI_COMPILER_IBM_ZOS
    #endif
    // Intel C/C++
    #if defined(__INTEL_COMPILER) || defined(__ICC) || defined(__ECC) || defined(__ICL)
        #define OMNI_COMPILER_INTEL
    #endif
    // KAI C++
    #if defined(__KCC)
        #define OMNI_COMPILER_KAI
    #endif
    // LLVM
    #if defined(__llvm__)
        #define OMNI_COMPILER_LLVM
    #endif
    // MetaWare High C/C++
    #if defined(__HIGHC__)
        #define OMNI_COMPILER_METAWARE
    #endif
    // Microsoft Visual C++
    #if defined(_MSC_VER)
        #define OMNI_COMPILER_MSVC
    #endif
    // MinGW/MinGW-64
    #if defined(__MINGW32__) || defined(__MINGW64__)
        #define OMNI_COMPILER_MINGW
    #endif
    // MPW C++
    #if defined(__MRC__) || defined(MPW_C) || defined(MPW_CPLUS)
        #define OMNI_COMPILER_MPW
    #endif
    // Open64
    #if defined(__OPEN64__) || defined(__OPENCC__)
        #define OMNI_COMPILER_OPEN64
    #endif
    // Oracle Solaris Studio
    #if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
        #define OMNI_COMPILER_ORACLE_SOLARIS_STUDIO
    #endif
    // Palm C/C++
    #if defined(_PACC_VER)
        #define OMNI_COMPILER_PALM
    #endif
    // Portland Group C/C++
    #if defined(__PGI)
        #define OMNI_COMPILER_PORTLAND
    #endif
    // Renesas C/C++
    #if defined(__RENESAS__) || defined(__HITACHI__)
        #define OMNI_COMPILER_RENESAS
    #endif
    // Symantec C++
    #if defined(__SC__)
        #define OMNI_COMPILER_SYMANTEC
    #endif
    // TenDRA C/C++
    #if defined(__TenDRA__)
        #define OMNI_COMPILER_TENDRA
    #endif
    // Texas Instruments C/C++ Compiler
    #if defined(__TI_COMPILER_VERSION__) || defined(_TMS320C6X)
        #define OMNI_COMPILER_TEXAS_INSTRUMENTS
    #endif
    // Turbo C/C++
    #if defined(__TURBOC__)
        #define OMNI_COMPILER_TURBO_C
    #endif
    // Ultimate C/C++
    #if defined(_UCC)
        #define OMNI_COMPILER_ULTIMATE_CPP
    #endif
    // Watcom C++
    #if defined(__WATCOMC__)
        #define OMNI_COMPILER_WATCOM
    #endif
    // Zortech C++
    #if defined(__ZTC__)
        #define OMNI_COMPILER_ZORTECH
    #endif
#endif // OMNI_COMPILER_CHECK_IGNORE

/*
    DEV_NOTE: There are areas of the Omni library that can utilize C++11 or higher,
    but to enable those you must specify the OMNI_ENABLE_CXX flag on compilation.
    
    To that, the purpose of this file is to give helper macros for possible language
    detection, keyword being possible. Should a need ever arise to force the Omni
    library to build for a separate language (e.g. building explicitly for C++11 with
    C++20), one can define the OMNI_LANGUAGE_CHECK_IGNORE preprocessor define and
    specify which ever compiler via one of the below defines.

    DEV_NOTE: These macro's do not determine the actual language used, instead these
    are merely guesses based on common compilation defines to determine what language
    the library is being compiled for.

    DEV_NOTE: we're not checking C versions since this is a C++ library.

    DEV_NOTE: some of these macros might be irrelevant since this library can't compile
    on some C++98 compilers.
*/ 

#if defined(OMNI_LANGUAGE_CHECK_IGNORE)
    /* Define here or as part of build. */
#else
    // http://sourceforge.net/p/predef/wiki/Home/

    #if defined(__embedded_cplusplus)
        #define OMNI_LANGUAGE_CPP_EMBEDDED
    #endif

    #if defined(__cplusplus_cli)
        #define OMNI_LANGUAGE_CPP_CLI
    #endif

    #if defined(__cplusplus)
        #if (__cplusplus >= 199711L)
            #define OMNI_LANGUAGE_CPP_98
            // DEV_NOTE: C++03 apparently didn't get a specific version number, despite being an official (and big) update
            #define OMNI_LANGUAGE_CPP_03
            // DEV_NOTE: we'll default to the 03 version
            #define OMNI_LANGUAGE_CPP_VERSION 03
        #endif
        #if (__cplusplus >= 201103L)
            #define OMNI_LANGUAGE_CPP_11
            #undef OMNI_LANGUAGE_CPP_VERSION
            #define OMNI_LANGUAGE_CPP_VERSION 11
        #endif
        #if (__cplusplus >= 201402L)
            #define OMNI_LANGUAGE_CPP_14
            #undef OMNI_LANGUAGE_CPP_VERSION
            #define OMNI_LANGUAGE_CPP_VERSION 14
        #endif
        #if (__cplusplus >= 201703L)
            #define OMNI_LANGUAGE_CPP_17
            #undef OMNI_LANGUAGE_CPP_VERSION
            #define OMNI_LANGUAGE_CPP_VERSION 17
        #endif
        #if (__cplusplus >= 202002L)
            #define OMNI_LANGUAGE_CPP_20
            #undef OMNI_LANGUAGE_CPP_VERSION
            #define OMNI_LANGUAGE_CPP_VERSION 20
        #endif
        #if (__cplusplus >= 202302L)
            #define OMNI_LANGUAGE_CPP_23
            #undef OMNI_LANGUAGE_CPP_VERSION
            #define OMNI_LANGUAGE_CPP_VERSION 23
        #endif

        #if defined(OMNI_NO_LANGUAGE_CPP_VERSION)
            #undef OMNI_LANGUAGE_CPP_VERSION
        #endif
    #endif

    #if defined(_POSIX_VERSION)
        #if (_POSIX_VERSION >= 198808L)
            #define OMNI_LANGUAGE_POSIX_88
        #endif
        #if (_POSIX_VERSION >= 199009L)
            #define OMNI_LANGUAGE_POSIX_90
        #endif
        #if (_POSIX_VERSION >= 199309L)
            #define OMNI_LANGUAGE_POSIX_93
        #endif
        #if (_POSIX_VERSION >= 199506L)
            #define OMNI_LANGUAGE_POSIX_96
        #endif
        #if (_POSIX_VERSION >= 200112L)
            #define OMNI_LANGUAGE_POSIX_01
        #endif
        #if (_POSIX_VERSION >= 200809L)
            #define OMNI_LANGUAGE_POSIX_08
        #endif
    #endif

    #if defined(_POSIX2_C_VERSION)
        #define OMNI_LANGUAGE_POSIX_2C
    #endif

    #if defined(_XOPEN_VERSION)
        #if (_XOPEN_VERSION >= 3)
            #define OMNI_LANGUAGE_XOPEN_3
            #define OMNI_LANGUAGE_XOPEN_89
        #endif
        #if (_XOPEN_VERSION >= 4)
            #define OMNI_LANGUAGE_XOPEN_4
            #define OMNI_LANGUAGE_XOPEN_92
            #if defined(_XOPEN_UNIX)
                #define OMNI_LANGUAGE_XOPEN_UNIX
                #define OMNI_LANGUAGE_XOPEN_UNIX95
            #endif
        #endif
        #if (_XOPEN_VERSION >= 500)
            #define OMNI_LANGUAGE_XOPEN_500
            #define OMNI_LANGUAGE_XOPEN_UNIX98
        #endif
        #if (_XOPEN_VERSION >= 600)
            #define OMNI_LANGUAGE_XOPEN_600
            #define OMNI_LANGUAGE_XOPEN_UNIX03
        #endif
        #if (_XOPEN_VERSION >= 700)
            #define OMNI_LANGUAGE_XOPEN_700
        #endif
    #endif

    #if defined(__LSB_VERSION__)
        #define OMNI_LANGUAGE_LINUX_STANDARDS_BASE
    #endif
#endif // OMNI_LANGUAGE_CHECK_IGNORE

/*
    DEV_NOTE: As of the inclusion of this file, there are no areas of Omni that
    utilize C-lib specific code and as a rule-of-thumb for Omni, we try
    to avoid C-lib specific code to be as cross-system compatible as
    possible. However, that does not preclude one from using lib-specific code
    if it makes sense to enable certain optimizations in the source.
    
    Please note that just because a specific macro is defined below, does not
    mean the library has been tested to work in that environment. OMNI_STD_LIB_BIONIC
    will be defined, for instance, if the __BIONIC__ macro is defined (usually by
    the compiler), but this does not mean we have been able to test/build the
    library in a direct (or even emulated) environment using the Bionic C lib.
    
    That being said, the purpose of this file is to give helper macros for
    possible compiler compilation detection, keyword being possible. Since

    DEV_NOTE: These macro's do not determine the actual libraries used,
    instead these are merely guesses based on common compilation defines to
    determine what libraries might be used.

    DEV_NOTE: There's no "ignore" flag for this since these are just
    helper macros and not used (nor will be used) in Omni.
*/ 

#if defined(__BIONIC__)
    #define OMNI_STD_LIB_BIONIC
#endif
#if defined(__GNU_LIBRARY__) || defined(__GLIBC__)
    #define OMNI_STD_LIB_GNUC
#endif
#if defined(__KLIBC__)
    #define OMNI_STD_LIB_KLIB
#endif
#if defined(__UCLIBC__)
    #define OMNI_STD_LIB_UC
#endif
#if defined(__CRTL_VER)
    #define OMNI_STD_LIB_VMS
#endif
#if defined(__LIBREL__) || defined(__TARGET_LIB__)
    #define OMNI_STD_LIB_ZOS
#endif
#if defined(_CPPLIB_VER)
    #define OMNI_STD_LIB_DINKUMWARE
#endif
#if defined(__GLIBCPP__) || defined(__GLIBCXX__)
    #define OMNI_STD_LIB_GNUCPP
#endif
#if defined(__INTEL_CXXLIB_ICC)
    #define OMNI_STD_LIB_INTEL
#endif
#if defined(_LIBCPP_VERSION) || _LIBCPP_ABI_VERSION
    #define OMNI_STD_LIB_CPP
#endif
#if defined(_MFC_VER)
    #define OMNI_STD_LIB_MS_MFC
#endif

#endif // OMNI_COMPILER_CHECK_HPP
