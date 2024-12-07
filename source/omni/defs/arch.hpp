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
#if !defined(OMNI_ARCH_HPP)
#define OMNI_ARCH_HPP 1

/*
    DEV_NOTE: As of the inclusion of this file, there are no areas of Omni that
    utilize architecture specific code and as a rule-of-thumb for Omni, we try
    to avoid architecture specific code to be as cross-system compatible as
    possible. However, that does not preclude one from using arch-specific code
    if it makes sense to enable certain optimizations in the source.
    
    Please note that just because a specific macro is defined below, does not
    mean the library has been tested to work in that environment. OMNI_ARCH_PPC
    will be defined, for instance, if the __powerpc macro is defined (usually by
    the compiler), but this does not mean we have been able to test/build the
    library in a direct (or even emulated) PowerPPC environment.
    
    That being said, the purpose of this file is to give helper macros for
    possible architecture compilation detection, keyword being possible. Should
    a need ever arise to force the Omni library to build for a separate architecture
    (e.g. building an ARM version on an Intel processor), one can define the
    OMNI_ARCH_IGNORE preprocessor define and specify which ever architecture
    via one of the below defines.

    DEV_NOTE: These macro's do not determine the bit-width of the architecture,
    instead these are merely guesses based on common compilation defines to
    determine what architecture the library is being compiled for.
*/ 

#if defined(OMNI_ARCH_IGNORE)
    /* Define here or as part of build. */
#else
    // http://sourceforge.net/p/predef/wiki/Home/

    // DEC-Alpha
    #if defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA) || \
        defined(__alpha_ev1__) || defined(__alpha_ev2__) || defined(__alpha_ev3__) || \
        defined(__alpha_ev4__) || defined(__alpha_ev5__) || defined(__alpha_ev6__) || \
        defined(__alpha_ev7__) || defined(__alpha_ev8__) || defined(__alpha_ev9__)
        #define OMNI_ARCH_DEC_ALPHA
    #endif

    // AMD64
    #if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
        #define OMNI_ARCH_AMD64
    #endif

    // ARM
    #if defined(__arm__) || defined(__thumb__) || defined(_ARM) || defined(_M_ARMT) || \
        defined(__arm) || defined(_M_ARM) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB) || \
        /* ARM 2 */   defined(__ARM_ARCH_2__) || \
        /* ARM 3 */   defined(__ARM_ARCH_3__) ||  defined(__ARM_ARCH_3M__) || \
        /* ARM 4T */  defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T) || \
        /* ARM 5 */   defined(__ARM_ARCH_5__) || defined(__ARM_ARCH_5E__) || \
        /* ARM 5T */  defined(__ARM_ARCH_5T__) || defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_5TEJ__) || \
        /* ARM 6 */   defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || \
        /* ARM 6T2 */ defined(__ARM_ARCH_6T2__) || \
        /* ARM 7 */   defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        #define OMNI_ARCH_ARM
    #endif
    
    // ARM64
    #if defined(__aarch64__)
        #define OMNI_ARCH_ARM64
    #endif
    
    // Blackfin
    #if defined(__bfin) || defined(__BFIN__) || defined(__ADSPBLACKFIN__)
        #define OMNI_ARCH_BLACKFIN
    #endif

    // Convex
    #if defined(__convex__) || defined(__convex_c1__) || defined(__convex_c2__) || \
        defined(__convex_c32__) || defined(__convex_c34__) || defined(__convex_c38__)
        #define OMNI_ARCH_CONVEX
    #endif

    // Epiphany
    #if defined(__epiphany__)
        #define OMNI_ARCH_EPIPHANY
    #endif

    // Elbrus
    #if defined(__e2k__)
        #define OMNI_ARCH_ELBRUS
    #endif

    // HP/PA RISC
    #if defined(__hppa__) || defined(__HPPA__) || defined(__hppa) || \
        /* PA RISC 1.0 */ defined(_PA_RISC1_0) || \
        /* PA RISC 1.1 */ defined(_PA_RISC1_1) || defined(__HPPA11__) || defined(__PA7100__) || \
        /* PA RISC 2.0 */ defined(_PA_RISC2_0) || defined(__RISC2_0__) || defined(__HPPA20__) || defined(__PA8000__)
        #define OMNI_ARCH_HPPA_RISC
    #endif

    // Intel x80
    #if defined(__8080__) || defined(__8085__) || defined(__Z80) || defined(__Z180)
        #define OMNI_ARCH_INTEL_X80
    #endif

    // Intel x86
    #if defined(i386) || defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || \
        defined(__IA32__) || defined(_M_I86) || defined(_M_IX86) || defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) || \
        defined(__I86__) || defined(__INTEL__) || defined(__386)
        #define OMNI_ARCH_INTEL_X86
    #endif

    // Intel Itanium (IA-64)
    #if defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(_M_IA64) || \
        defined(_M_IA64) || defined(_M_IA64) || defined(__itanium__)
        #define OMNI_ARCH_INTEL_IA64
    #endif

    // LoongArch
    #if defined(__loongarch__)
        #define OMNI_ARCH_LOONGARCH
    #endif

    // Motorola 68k
    #if defined(__m68k__) || defined(M68000) || defined(__MC68K__) || \
        /* 68000 */ defined(__mc68000__) || defined(__MC68000__) || \
        /* 68010 */ defined(__mc68010__) || \
        /* 68020 */ defined(__mc68020__) || defined(__MC68020__) || \
        /* 68030 */ defined(__mc68030__) || defined(__MC68030__) || \
        /* 68040 */ defined(__mc68040__) || \
        /* 68060 */ defined(__mc68060__)
        #define OMNI_ARCH_MOTOROLA_68K
    #endif

    // MIPS
    #if defined(__mips__) || defined(mips) || defined(_MIPS_ISA) || defined(_R3000) || defined(_R4000) || defined(_R5900) || \
        defined(__mips) || defined(__MIPS__) || defined(_MIPS_ISA_MIPS1) || defined(_MIPS_ISA_MIPS2) || defined(__MIPS_ISA2__) || \
        defined(_R4000) || defined(_MIPS_ISA_MIPS3) || defined(__MIPS_ISA3__) || defined(_MIPS_ISA_MIPS4) || \
        defined(__MIPS_ISA4__) || defined(__MIPS_ISA4__)
        #define OMNI_ARCH_MIPS
    #endif

    // NEC SX-Aurora TSUBASA
    #if defined(__ve__) || defined(__ve) || defined(__NEC__)
        #define OMNI_ARCH_NEC
    #endif

    // PNaCl
    #if defined(__pnacl__)
        #define OMNI_ARCH_PNACL
    #endif

    // PowerPC
    #if defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || \
        defined(__ppc__) || defined(__ppc64__) || defined(__PPC__) || defined(__PPC64__) || defined(_ARCH_PPC) || \
        defined(_ARCH_PPC64) || defined(_M_PPC) || defined(__PPCGECKO__) || defined(__PPCBROADWAY__) || \
        defined(_XENON) || defined(__ppc) || defined(_ARCH_440) || defined(_ARCH_450) || defined(__ppc601__) || \
        defined(_ARCH_601) || defined(__ppc603__) || defined(_ARCH_603) || defined(__ppc604__) || defined(_ARCH_604)
        #define OMNI_ARCH_POWER_PC
    #endif

    // Pyramid 9810
    #if defined(pyr)
        #define OMNI_ARCH_PYRAMID_9810
    #endif

    // RISC-V
    #if defined(__riscv) || defined(__riscv_xlen)
        #define OMNI_ARCH_RISC_V
        #if defined(__riscv_xlen)
            #if (__riscv_xlen == 32)
                #define OMNI_ARCH_RISC_V32
            #elif (__riscv_xlen == 64)
                #define OMNI_ARCH_RISC_V64
            #endif
        #endif
    #endif

    // RS/6000
    #if defined(__THW_RS6000) || defined(_IBMR2) || defined(_POWER) || defined(_ARCH_PWR) || \
        defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || defined(_ARCH_PWR4)
        #define OMNI_ARCH_RS6000
    #endif

    // SPARC
    #if defined(__sparc__) || defined(__sparc) || defined(__sparc_v8__) || defined(__sparc_v9__) || defined(__sparcv8) || defined(__sparcv9)
        #define OMNI_ARCH_SPARC
    #endif

    // SuperH
    #if defined(__sh__) || defined(__sh1__) || defined(__sh2__) || defined(__sh3__) || defined(__SH3__) || defined(__SH4__) || defined(__SH5__)
        #define OMNI_ARCH_SUPER_H
    #endif

    // SystemZ
    #if defined(__370__) || defined(__THW_370__) || defined(__s390__) || defined(__s390x__) || defined(__zarch__) || defined(__SYSC_ZARCH__)
        #define OMNI_ARCH_SYSTEM_Z
    #endif

    // TMS320
    #if defined(_TMS320C2XX) || defined(__TMS320C2000__) || defined(_TMS320C5X) || defined(__TMS320C55X__) || \
        defined(_TMS320C6X) || defined(__TMS320C6X__) || defined(_TMS320C28X) || defined(_TMS320C5XX) || \
        defined(__TMS320C55X__) || defined(_TMS320C6200) || defined(_TMS320C6400) || defined(_TMS320C6400_PLUS) || \
        defined(_TMS320C6600) || defined(_TMS320C6700) || defined(_TMS320C6700_PLUS) || defined(_TMS320C6740)
        #define OMNI_ARCH_TMS320
    #endif

    // TMS470
    #if defined(__TMS470__)
        #define OMNI_ARCH_TMS470
    #endif

#endif // OMNI_ARCH_IGNORE

#endif // OMNI_ARCH_HPP
