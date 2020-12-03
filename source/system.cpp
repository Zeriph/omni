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
#include <omni/system.hpp>
#include <iostream>
#include <string>
#if !defined(OMNI_WIN_API)
    #if defined(OMNI_OS_WIN)
        #include <direct.h> // _getcwd
    #else
        #include <sys/param.h>
        #include <unistd.h>
    #endif
    #if defined(OMNI_OS_BSD)
        #include <sys/sysctl.h>
    #endif
    #if defined(OMNI_NON_PORTABLE)
        #if defined(OMNI_OS_APPLE)
            #include <mach-o/dyld.h>
            #include <limits.h>
        #elif defined(OMNI_OS_FREEBSD)
            #include <sys/sysctl.h>
        #endif
    #endif
#endif
#include <csignal>
#include <cerrno>
#include <signal.h>
#include <errno.h>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <omni/defs/consts.hpp>

bool omni::system::is_big_endian()
{
    unsigned short test = 0x0001;
    return ((*(reinterpret_cast<char*>(&test))) == 0x00);
}

int32_t omni::system::last_error()
{
    return OMNI_GLE;
}

std::string omni::system::last_error_str()
{
    return omni::system::error_str(OMNI_GLE);
}

#if defined(OMNI_NON_PORTABLE)

omni::system::architecture_type omni::system::architecture()
{
    #if defined(OMNI_ARCH_DEC_ALPHA)
        // DEC-Alpha
        return omni::system::architecture_type::DEC_ALPHA;
    #endif
    #if defined(OMNI_ARCH_AMD64)
        // AMD64
        return omni::system::architecture_type::AMD64;
    #endif
    #if defined(OMNI_ARCH_ARM)
        // ARM
        return omni::system::architecture_type::ARM;
    #endif
    #if defined(OMNI_ARCH_ARM64)
        //ARM64
        return omni::system::architecture_type::ARM64;
    #endif
    #if defined(OMNI_ARCH_BLACKFIN)
        // Blackfin
        return omni::system::architecture_type::BLACKFIN;
    #endif
    #if defined(OMNI_ARCH_CONVEX)
        // Convex
        return omni::system::architecture_type::CONVEX;
    #endif
    #if defined(OMNI_ARCH_EPIPHANY)
        // Epiphany
        return omni::system::architecture_type::EPIPHANY;
    #endif
    #if defined(OMNI_ARCH_HPPA_RISC)
        // HP/PA RISC
        return omni::system::architecture_type::HPPA_RISC;
    #endif
    #if defined(OMNI_ARCH_INTEL_X86)
        // Intel x86
        return omni::system::architecture_type::INTEL_X86;
    #endif
    #if defined(OMNI_ARCH_INTEL_IA64)
        // Intel Itanium (IA-64)
        return omni::system::architecture_type::INTEL_IA64;
    #endif
    #if defined(OMNI_ARCH_MOTOROLA_68K)
        // Motorola 68k
        return omni::system::architecture_type::MOTOROLA_68K;
    #endif
    #if defined(OMNI_ARCH_MIPS)
        // MIPS
        return omni::system::architecture_type::MIPS;
    #endif
    #if defined(OMNI_ARCH_POWER_PC)
        // PowerPC
        return omni::system::architecture_type::POWER_PC;
    #endif
    #if defined(OMNI_ARCH_PYRAMID_9810)
        // Pyramid 9810
        return omni::system::architecture_type::PYRAMID_9810;
    #endif
    #if defined(OMNI_ARCH_RS600)
        // RS/6000
        return omni::system::architecture_type::RS600;
    #endif
    #if defined(OMNI_ARCH_SPARC)
        // SPARC
        return omni::system::architecture_type::SPARC;
    #endif
    #if defined(OMNI_ARCH_SUPER_H)
        // SuperH
        return omni::system::architecture_type::SUPER_H;
    #endif
    #if defined(OMNI_ARCH_SYSTEM_Z)
        // SystemZ
        return omni::system::architecture_type::SYSTEM_Z;
    #endif
    #if defined(OMNI_ARCH_TMS320)
        // TMS320
        return omni::system::architecture_type::TMS320;
    #endif
    #if defined(OMNI_ARCH_TMS470)
        // TMS470
        return omni::system::architecture_type::TMS470;
    #endif
}

omni::string_t omni::system::cwd()
{
    omni::char_t* p = new omni::char_t[FILENAME_MAX]();
    #if defined(OMNI_WIN_API)
        bool ret = (::GetCurrentDirectory(FILENAME_MAX, p) != 0);
    #else
        char* tp = new char[FILENAME_MAX]();
        #if defined(OMNI_OS_WIN)
            bool ret = (::_getcwd(tp, FILENAME_MAX) != 0);
        #else
            bool ret = (::getcwd(tp, FILENAME_MAX) != 0);
        #endif
        if (ret) {
            tp[FILENAME_MAX - 1] = '\0';
            #if defined(OMNI_UNICODE)
                std::mbstowcs(p, tp, FILENAME_MAX);
            #else
                std::memcpy(p, tp, FILENAME_MAX);
            #endif
        }
        delete[] tp;
    #endif
    if (!ret) {
        delete[] p;
        OMNI_DBGE(OMNI_PATH_NOT_ACCESSIBLE_STR << ": " << OMNI_GLE)
        return omni::string_t();
    }
    omni::string_t sret(p);
    delete[] p;
    return sret;
}

std::string omni::system::error_str(int code)
{
    #if defined(OMNI_WIN_API)//defined(OMNI_OS_WIN)
        OMNI_CHAR_T *serr = new OMNI_CHAR_T[65535];
        // not a direct system message, must use IGNORE_INSERTS
        DWORD ret = ::FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            code,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            serr,
            65535,
            NULL
        );
        if (ret != 0) {
            omni::string_t werr(serr); // make copy
            delete[] serr;
            serr = OMNI_NULL;
            return omni::string::to_string(werr);
        }
        delete[] serr;
        serr = OMNI_NULL;
        return std::string("Unknown error ").append(omni::string::util::to_string(code));
    #else
        return std::strerror(code);
    #endif
}

omni::string_t omni::system::path()
{
    omni::char_t* p = new omni::char_t[FILENAME_MAX]();
    #if !defined(OMNI_OS_WIN)
        char* tp = new char[FILENAME_MAX]();
    #endif
    #if defined(OMNI_OS_WIN) // windows
        // DEV_NOTE: ifdef OMNI_WIN_API not applicable here
        bool ret = (::GetModuleFileName(0, p, FILENAME_MAX) != 0);
    #elif defined(OMNI_OS_APPLE) // apple
        uint32_t cb = FILENAME_MAX;
        bool ret = (::_NSGetExecutablePath(tp, &cb) == 0);
    #elif defined(OMNI_OS_SOLARIS) // solaris/sun
        bool ret = (std::strncpy(tp, ::getexecname(), FILENAME_MAX) != 0);
    #elif defined(OMNI_OS_BSD) // bsd
        #if defined(OMNI_OS_FREEBSD) // freebsd
            int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 };
            std::size_t cb = FILENAME_MAX;
            bool ret = (::sysctl(mib, 4, tp, &cb, NULL, 0) == 0);
        #else // other bsd with procfs            
            #if !defined(OMNI_NO_PROC_SYS)
                bool ret = (::readlink("/proc/curproc/file", tp, (FILENAME_MAX - 1)) != -1);
                if (!ret) {
                    std::memset(tp, 0, FILENAME_MAX);
                    char* e = std::getenv("_");
                    ret = (e ? (std::strncpy(tp, e, FILENAME_MAX) != 0) : false);
                }
            #else
                std::memset(tp, 0, FILENAME_MAX);
                char* e = std::getenv("_");
                bool ret = (e ? (std::strncpy(tp, e, FILENAME_MAX) != 0) : false);
            #endif
        #endif
    #else // *nix
        #if !defined(OMNI_NO_PROC_SYS)
            bool ret = (::readlink("/proc/self/exe", tp, (FILENAME_MAX - 1)) != -1);
            if (!ret) {
                std::memset(tp, 0, FILENAME_MAX);
                char* e = std::getenv("_");
                ret = (e ? (std::strncpy(tp, e, FILENAME_MAX) != 0) : false);
            }
        #else
            std::memset(tp, 0, FILENAME_MAX);
            char* e = std::getenv("_");
            bool ret = (e ? (std::strncpy(tp, e, FILENAME_MAX) != 0) : false);
        #endif
    #endif
    #if !defined(OMNI_OS_WIN)
        if (ret) {
            #if defined(OMNI_UNICODE)
                ret = (std::mbstowcs(p, tp, FILENAME_MAX) != 0);
            #else
                ret = (std::strncpy(&p[0], tp, FILENAME_MAX) != 0);
            #endif
        }
        delete[] tp;
    #endif
    if (!ret) {
        delete[] p;
        OMNI_DBGE(OMNI_PATH_NOT_ACCESSIBLE_STR << ": " << OMNI_GLE)
        return omni::string_t();
    }
    omni::string_t sret(p);
    delete[] p;
    return sret;
}

uint64_t omni::system::processors()
{
    //may return 0 when not able to detect
    // if C++11, return std::thread::hardware_concurrency();
    #if defined(OMNI_OS_WIN) // windows
        // DEV_NOTE: ifdef OMNI_WIN_API not applicable here
        SYSTEM_INFO si;
        ::GetSystemInfo(&si);
        return static_cast<uint64_t>(si.dwNumberOfProcessors);
    #elif defined(OMNI_OS_HPUX) // HPUX
        // DEV_NOTE: untested (no access to HPUX system)
        return static_cast<uint64_t>(::mpctl(MPC_GETNUMSPUS, NULL, NULL));
    #elif defined(OMNI_OS_IRIX) // IRIX
        // DEV_NOTE: untested (no access to Irix system)
        return static_cast<uint64_t>(::sysconf(_SC_NPROC_ONLN));
    #elif defined(OMNI_OS_BSD) // bsd
        int mib[4];
        int ret = 0;
        std::size_t len = sizeof(ret);
        /* set the mib for hw.ncpu */
        mib[0] = CTL_HW;
        mib[1] = HW_NCPU;
        /* get the number of CPUs from the system */
        ::sysctl(mib, 2, &ret, &len, NULL, 0);
        if (ret < 1) {
            mib[1] = HW_NCPU;
            ::sysctl(mib, 2, &ret, &len, NULL, 0);
            if (ret < 0) { ret = 0; }
        }
        return static_cast<uint64_t>(ret);
    #else // *nix
        return static_cast<uint64_t>(::sysconf(_SC_NPROCESSORS_ONLN));
    #endif
}

std::string omni::system::signal_str(int sig)
{
    /* DEV_NOTE: we do not "redefine" any of the signal names in the
    omni namespace as it would be redundant and unnecessarily verbose */
    #if defined(OMNI_WIN_API)
    switch (sig) {
        case CTRL_C_EVENT:        // signal when CTRL+C received
            return "CTRL_C_EVENT: CTRL+C received";
        case CTRL_BREAK_EVENT:    // signal when CTRL+BREAK received
            return "CTRL_BREAK_EVENT: CTRL+BREAK received";
        case CTRL_CLOSE_EVENT:    // signal when console window being closed
            return "CTRL_CLOSE_EVENT: console window closing";
        case CTRL_LOGOFF_EVENT:   // signal when user being logged off
            return "CTRL_C_EVENT: user logging off";
        case CTRL_SHUTDOWN_EVENT: // signal when system is shutting down
            return "CTRL_C_EVENT: system shutting down";
        default: break; // other/unknown signal
    }
    #endif
    switch (sig) {
        // SIGINT is caught by the console handler in windows
        case SIGINT:  // signal interrupt: typically occurs when user interrupts the program (like when pressing CTRL+C)
            return "SIGINT: signal interrupt";
        case SIGABRT: // signal abort: abnormal termination
            return "SIGABRT: abort/abnormal termination";
        case SIGFPE:  // signal floating point exception: occurs on erroneous arithmetic operations (like division by 0)
            return "SIGFPE: floating point exception";
        case SIGILL:  // signal illegal instruction: typically occurs with code corruption
            return "SIGILL: illegal instruction";
        case SIGSEGV: // signal segmentation violation: typically occurs when the program tries to read/write invalid memory
            return "SIGSEGV: segmentation violation";
        case SIGTERM: // signal terminate: termination request sent to the program
            return "SIGTERM: terminate";
        default: break; // other/unknown signal
    }
    return std::string("Other/Unknown: ").append(omni::string::util::lexical_cast<std::string, int>(sig));
}

#endif
