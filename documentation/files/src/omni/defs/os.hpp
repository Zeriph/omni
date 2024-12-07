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
#if !defined(OMNI_OS_HPP)
#define OMNI_OS_HPP 1

/*
    DEV_NOTE: Most areas of the Omni library only ever need to see if we
    are in a Windows based build or *nix/POSIX based environment. In some 
    areas we do need to check for other OSs, for example, stopwatch needs
    Apple detection on top of *nix/Win and the non portable code for
    application (see application.cpp) heavily relies on this.
    
    Please note that just because a specific macro is defined below, does not
    mean the library has been tested to work in that environment. OMNI_OS_OS400
    will be defined, for instance, if the __OS400__ macro is defined (usually by
    the compiler/system libs), but this does not mean we have been able to test/build
    the library in a direct (or even emulated) IBM OS/400 environment.
    
    That being said, the purpose of this file is to give helper macros for
    possible OS detection, keyword being possible. Should a need ever arise
    to force the Omni library to build for a separate platform (building
    a POSIX compliant program under Cygwin/MinGW for instance), one can
    define the OMNI_OS_IGNORE preprocessor define and specify which ever
    platform they wish.
*/ 

#if defined(OMNI_OS_IGNORE)
    /*
    Define here or as part of build. Values used by the omni library:
    
    OMNI_OS_WIN
    OMNI_OS_APPLE
    OMNI_OS_LINUX
    OMNI_OS_OPENBSD
    OMNI_OS_FREEBSD
    OMNI_OS_SOLARIS
    OMNI_OS_BSD
    
    */
#else
    // http://sourceforge.net/p/predef/wiki/Home/

    // Windows
    #if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || \
        defined(__WINDOWS__) || defined(__WIN64__) || defined(_MSC_VER) || defined(MSDOS) || \
        defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
        #define OMNI_OS_WIN
    #endif

    // Apple/macOS
    #if defined(macintosh) || defined(Macintosh) || ((defined(__APPLE__) || defined(__APPLE_CC__)) && defined(__MACH__))
        #define OMNI_OS_APPLE
        #include <AvailabilityMacros.h>
        #if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_7
            #define OMNI_OS_MACOS
        #else
            // older mac's
            #define OMNI_OS_APPLE_MAC
        #endif
    #endif

    // Apple/iPhone/TV/Watch/iOS/Simulator
    #if defined(__APPLE__)
        #if !defined(OMNI_OS_APPLE)
            #define OMNI_OS_APPLE
        #endif
        #include <TargetConditionals.h>
        #if defined(TARGET_OS_OSX)
            // DEV_NOTE: this would essentially be an alias to OMNI_OS_MACOS
            #define OMNI_OS_APPLE_OSX
        #endif
        #if defined(TARGET_OS_IPHONE)
            #define OMNI_OS_APPLE_IPHONE
        #endif
        #if defined(TARGET_OS_IOS)
            #define OMNI_OS_APPLE_IOS
        #endif
        #if defined(TARGET_OS_MACCATALYST)
            #define OMNI_OS_APPLE_MACCATALYST
        #endif
        #if defined(TARGET_OS_TV)
            #define OMNI_OS_APPLE_TV
        #endif
        #if defined(TARGET_OS_WATCH)
            #define OMNI_OS_APPLE_WATCH
        #endif
        #if defined(TARGET_OS_VISION)
            #define OMNI_OS_APPLE_VISION
        #endif
        #if defined(TARGET_OS_BRIDGE)
            #define OMNI_OS_APPLE_BRIDGE
        #endif
        #if defined(TARGET_OS_SIMULATOR)
            #define OMNI_OS_APPLE_SIM
        #endif
    #endif
    
    // UNIX Environment
    #if defined(__unix__) || defined(__unix)
        #define OMNI_OS_UNIX
    #endif

    // BSD Environment
    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || \
        defined(__DragonFly__) || defined(_SYSTYPE_BSD) || defined(__MidnightBSD__) || defined(__MidnightBSD_kernel__)
        #define OMNI_OS_BSD
    #endif

    // Linux kernel
    #if defined(__linux__) || defined(linux) || defined(__linux)
        #define OMNI_OS_LINUX
    #endif

    // -- OS specific defines --
    
    // AIX
    #if defined(_AIX) || defined(__TOS_AIX__)
        #define OMNI_OS_AIX
    #endif
    // Android
    #if defined(__ANDROID__) || defined(__ANDROID_API__)
        #define OMNI_OS_ANDROID
        #if defined(__ANDROID_API__)
            #define OMNI_OS_ANDROID_VERSION __ANDROID_API__
        #endif
    #endif
    // Amdahl UTS
    #if defined(UTS)
        #define OMNI_OS_UTS
    #endif
    // AmigaOS
    #if defined(AMIGA) || defined(__amigaos__)
        #define OMNI_OS_AMIGA
    #endif
    // Apollo AEGIS
    #if defined(aegis)
        #define OMNI_OS_AEGIS
    #endif
    // Apollo Domain/OS
    #if defined(apollo)
        #define OMNI_OS_APPOLO
    #endif
    // BeOS
    #if defined(__BEOS__)
        #define OMNI_OS_BEOS
    #endif
    // Blue Gene
    #if defined(__bg__) || defined(__bgq__) || defined(__THW_BLUEGENE__) || defined(__TOS_BGQ__)
        #define OMNI_OS_BLUEGENE
    #endif
    // BSD/OS
    #if defined(__bsdi__)
        #define OMNI_OS_BSDI
    #endif
    // Cygwin
    #if defined(__CYGWIN__)
        #define OMNI_OS_CYGWIN
    #endif
    // ConvexOS
    #if defined(__convex__)
        #define OMNI_OS_CONVEX
    #endif
    // DG/UX
    #if defined(DGUX) || defined(__DGUX__) || defined(__dgux__)
        #define OMNI_OS_DGUX
    #endif
    // DYNIX/ptx
    #if defined(_SEQUENT_) || defined(sequent)
        #define OMNI_OS_DYNIX
    #endif
    // DragonFly
    #if defined(__DragonFly__)
        #define OMNI_OS_DRAGONFLYBSD
    #endif
    // eCos
    #if defined(__ECOS)
        #define OMNI_OS_ECOS
    #endif
    // EMX Environment
    #if defined(__EMX__)
        #define OMNI_OS_EMX
    #endif
    // FreeBSD
    #if defined(__FreeBSD__)
        #define OMNI_OS_FREEBSD
    #endif
    // GNU aka GNU/Hurd
    #if defined(__GNU__) || defined(__gnu_hurd__)
        #define OMNI_OS_GNU_HURD
    #endif
    // GNU/kFreeBSD
    #if defined(__FreeBSD_kernel__) && defined(__GLIBC__)
        #define OMNI_OS_GNU_FREEBSD
    #endif
    // GNU/Linux
    #if defined(__gnu_linux__)
        #define OMNI_OS_GNU_LINUX
    #endif
    // HI-UX MPP
    #if defined(__hiuxmpp)
        #define OMNI_OS_HIUXMPP
    #endif
    // HP-UX
    #if defined(_hpux) || defined(hpux) || defined(__hpux)
        #define OMNI_OS_HPUX
    #endif
    // IBM OS/400
    #if defined(__OS400__)
        #define OMNI_OS_OS400
    #endif
    // INTEGRITY
    #if defined(__INTEGRITY)
        #define OMNI_OS_INTEGRITY
    #endif
    // Interix Environment
    #if defined(__INTERIX)
        #define OMNI_OS_INTERIX
    #endif
    // IRIX
    #if defined(sgi) || defined(__sgi)
        #define OMNI_OS_IRIX
    #endif
    // LynxOS
    #if defined(__Lynx__)
        #define OMNI_OS_LYNXOS
    #endif
    // Microware OS-9
    #if defined(__OS9000) || defined(_OSK)
        #define OMNI_OS_MICROWARE_OS9
    #endif
    // MSYS/MinGW32 Environment
    #if defined(__MINGW32__)
        #define OMNI_OS_MINGW
    #endif
    // MINIX
    #if defined(__minix)
        #define OMNI_OS_MINIX
    #endif
    // MorphOS
    #if defined(__MORPHOS__)
        #define OMNI_OS_MORPHOS
    #endif
    // MPE/iX
    #if defined(mpeix) || defined(__mpexl)
        #define OMNI_OS_MPEIX
    #endif
    // MSDOS
    #if defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
        #define OMNI_OS_MSDOS
    #endif
    // NetBSD
    #if defined(__NetBSD__)
        #define OMNI_OS_NETBSD
    #endif
    // NonStop
    #if defined(__TANDEM)
        #define OMNI_OS_NONSTOP
    #endif
    // Nucleus RTOS
    #if defined(__nucleus__)
        #define OMNI_OS_NUCLEUS
    #endif
    // OpenBSD
    #if defined(__OpenBSD__)
        #define OMNI_OS_OPENBSD
    #endif
    // OS/2
    #if defined(OS2) || defined(_OS2) || defined(__OS2__) || defined(__TOS_OS2__)
        #define OMNI_OS_OS2
    #endif
    // Palm OS
    #if defined(__palmos__)
        #define OMNI_OS_PALMOS
    #endif
    // Pyramid DC/OSx
    #if defined(pyr)
        #define OMNI_OS_PYRAMID
    #endif
    // Plan 9
    #if defined(EPLAN9)
        #define OMNI_OS_PLAN9
    #endif
    // QNX
    #if defined(__QNX__) || defined(__QNXNTO__)
        #define OMNI_OS_QNX
    #endif
    // Reliant UNIX
    #if defined(sinux)
        #define OMNI_OS_RELIANT_UNIX
    #endif
    // SCO OpenServer
    #if defined(M_I386) || defined(M_XENIX) || defined(_SCO_DS)
        #define OMNI_OS_SCO_OPENSERVER
    #endif
    // Stratus VOS
    #if defined(__VOS__)
        #define OMNI_OS_VOS
    #endif
    // Solaris
    #if defined(sun) || defined(__sun)
        #define OMNI_OS_SOLARIS
    #endif
    // SVR4 Environment
    #if defined(__sysv__) || defined(__SVR4) || defined(__svr4__) || defined(_SYSTYPE_SVR4)
        #define OMNI_OS_SVR
    #endif
    // SunOS
    #if defined(OMNI_OS_SOLARIS)
        // Use the SVR4 macros to distinguish between Solaris and SunOS.
        #if !defined(__SVR4) && !defined(__svr4__)
            #define OMNI_OS_SUNOS
        #endif
    #endif
    // Syllable
    #if defined(__SYLLABLE__)
        #define OMNI_OS_SYLLABLE
    #endif
    // Symbian OS
    #if defined(__SYMBIAN32__)
        #define OMNI_OS_SYMBIAN
    #endif
    // Tru64 (OSF/1)
    #if defined(__osf__) || defined(__osf)
        #define OMNI_OS_OSF1
    #endif
    // Ultrix
    #if defined(ultrix) || defined(__ultrix) || defined(__ultrix__) || (defined(unix) && defined(vax))
        #define OMNI_OS_ULTRIX
    #endif
    // UNICOS
    #if defined(_UNICOS)
        #define OMNI_OS_UNICOS
    #endif
    // UNICOS/mp
    #if defined(_CRAY) || defined(__crayx1)
        #define OMNI_OS_CRAY
    #endif
    // UnixWare
    #if defined(sco) || defined(_UNIXWARE7)
        #define OMNI_OS_UNIXWARE
    #endif
    // U/Win Environment
    #if defined(_UWIN)
        #define OMNI_OS_UWIN
    #endif
    // VMS
    #if defined(__VMS) || defined(VMS)
        #define OMNI_OS_VMS
    #endif
    // VxWorks
    #if defined(__VXWORKS__) || defined(__vxworks)
        #define OMNI_OS_VXWORKS
    #endif
    // Windows CE
    #if defined(_WIN32_WCE) || defined(WIN32_PLATFORM_HPC2000) || defined(WIN32_PLATFORM_HPCPRO) || \
        defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
        #define OMNI_OS_WINCE
    #endif
    // Wind/U Environment
    #if defined(_WINDU_SOURCE)
        #define OMNI_OS_WINDU
    #endif
    // z/OS
    #if defined(__MVS__) || defined(__HOS_MVS__) || defined(__TOS_MVS__)
        #define OMNI_OS_ZOS
    #endif
    // XBox One
    #if defined(_XBOX_ONE)
        #define OMNI_OS_XBOX_ONE
    #endif
    // PS4
    #if defined(__ORBIS__)
        #define OMNI_OS_PLAYSTATION_4
    #endif
    // Emscripten
    #if defined(EMSCRIPTEN) || defined(__EMSCRIPTEN__)
        #define OMNI_OS_EMSCRIPTEN
    #endif
    // Fuchsia
    #if defined(__Fuchsia__)
        #define OMNI_OS_FUCHSIA
    #endif
    // HAIKU
    #if defined(__HAIKU__)
        #define OMNI_OS_HAIKU
    #endif
    // MidnightBSD
    #if defined(__MidnightBSD__) || defined(__MidnightBSD_kernel__)
        #define OMNI_OS_MIDNIGHT_BSD
    #endif
    // native_client
    #if defined(__native_client__)
        #define OMNI_OS_NATIVE_CLIENT
    #endif

    // check for any invalid combo's
    #if defined(OMNI_OS_CYGWIN) || defined(OMNI_OS_MINGW)
        #if defined(OMNI_OS_WIN)
            #warning "OMNI_OS_WIN in Cygwin environment" 
        #endif
    #endif

#endif // OMNI_OS_IGNORE

#if !defined(OMNI_OS_STR) && !defined(OMNI_NO_OS_STR)
    #if defined(OMNI_OS_WIN)
        #define OMNI_OS_STR "Windows"
    #elif defined(OMNI_OS_APPLE)
        #if defined(OMNI_OS_APPLE_OSX) || defined(OMNI_OS_MACOS)
            #define OMNI_OS_STR "Apple OSX"
        #elif defined(OMNI_OS_APPLE_IPHONE)
            #define OMNI_OS_STR "Apple iPhone"
        #elif defined(OMNI_OS_APPLE_IOS)
            #define OMNI_OS_STR "Apple iOS"
        #elif defined(OMNI_OS_APPLE_TV)
            #define OMNI_OS_STR "Apple TV"
        #elif defined(OMNI_OS_APPLE_WATCH)
            #define OMNI_OS_STR "Apple Watch"
        #elif defined(OMNI_OS_APPLE_VISON)
            #define OMNI_OS_STR "Apple Vision"
        #else
            #define OMNI_OS_STR "Apple"
        #endif
    #elif defined(OMNI_OS_ANDROID)
        #define OMNI_OS_STR "Android"
    #elif defined(OMNI_OS_OPENBSD)
        #define OMNI_OS_STR "OpenBSD"
    #elif defined(OMNI_OS_FREEBSD)
        #define OMNI_OS_STR "FreeBSD"
    #elif defined(OMNI_OS_SOLARIS)
        #define OMNI_OS_STR "Solaris"
    #elif defined(OMNI_OS_LINUX)
        #define OMNI_OS_STR "Linux"
    #else
        #define OMNI_OS_STR "Other OS"
    #endif
#endif

#endif // OMNI_OS_HPP
