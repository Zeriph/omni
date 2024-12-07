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

/* DEV_NOTE: this file is not intended to be used directly by any user code!

 i.e. do not #include <omni/xxx_impl.hxx> and do not compile this source directly.
 this file is included directly in other source.
*/

// so as not to accidentally build this file with the source
// these macros are defined in chrono
#if !defined(OMNI_IO_PATH_COMBINE_FW)
    #error "invalid preprocessor directive detected"
#endif

namespace omni {
    namespace io {
        
        // TODO: there's GOT to be a better way to do this

        namespace cpath {
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27, const std::string& p28)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); p.push_back(p28); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27, const std::string& p28, const std::string& p29)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); p.push_back(p28); p.push_back(p29); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27, const std::string& p28, const std::string& p29, const std::string& p30)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); p.push_back(p28); p.push_back(p29); p.push_back(p30); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27, const std::string& p28, const std::string& p29, const std::string& p30, const std::string& p31)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); p.push_back(p28); p.push_back(p29); p.push_back(p30); 
                p.push_back(p31); 
                return omni::io::cpath::combine(p);
            }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27, const std::string& p28, const std::string& p29, const std::string& p30, const std::string& p31, const std::string& p32)
            {
                omni::sequence::std_string_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); p.push_back(p28); p.push_back(p29); p.push_back(p30); 
                p.push_back(p31); p.push_back(p32); 
                return omni::io::cpath::combine(p);
            }
        }
        namespace wpath {
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27, const std::wstring& p28)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); p.push_back(p28); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27, const std::wstring& p28, const std::wstring& p29)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); p.push_back(p28); p.push_back(p29); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27, const std::wstring& p28, const std::wstring& p29, const std::wstring& p30)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); p.push_back(p28); p.push_back(p29); p.push_back(p30); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27, const std::wstring& p28, const std::wstring& p29, const std::wstring& p30, const std::wstring& p31)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); p.push_back(p28); p.push_back(p29); p.push_back(p30); 
                p.push_back(p31); 
                return omni::io::wpath::combine(p);
            }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27, const std::wstring& p28, const std::wstring& p29, const std::wstring& p30, const std::wstring& p31, const std::wstring& p32)
            {
                omni::sequence::std_wstring_t p;
                p.push_back(p1); p.push_back(p2); p.push_back(p3); p.push_back(p4); p.push_back(p5); 
                p.push_back(p6); p.push_back(p7); p.push_back(p8); p.push_back(p9); p.push_back(p10); 
                p.push_back(p11); p.push_back(p12); p.push_back(p13); p.push_back(p14); p.push_back(p15); 
                p.push_back(p16); p.push_back(p17); p.push_back(p18); p.push_back(p19); p.push_back(p20); 
                p.push_back(p21); p.push_back(p22); p.push_back(p23); p.push_back(p24); p.push_back(p25); 
                p.push_back(p26); p.push_back(p27); p.push_back(p28); p.push_back(p29); p.push_back(p30); 
                p.push_back(p31); p.push_back(p32); 
                return omni::io::wpath::combine(p);
            }
        }
        namespace path {
            // std::string 
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3) { return omni::io::cpath::combine(p1, p2, p3); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4) { return omni::io::cpath::combine(p1, p2, p3, p4); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5) { return omni::io::cpath::combine(p1, p2, p3, p4, p5); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27, const std::string& p28) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27, const std::string& p28, const std::string& p29) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27, const std::string& p28, const std::string& p29, const std::string& p30) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27, const std::string& p28, const std::string& p29, const std::string& p30, const std::string& p31) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31); }
            inline std::string combine(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& p5, const std::string& p6, const std::string& p7, const std::string& p8, const std::string& p9, const std::string& p10, const std::string& p11, const std::string& p12, const std::string& p13, const std::string& p14, const std::string& p15, const std::string& p16, const std::string& p17, const std::string& p18, const std::string& p19, const std::string& p20, const std::string& p21, const std::string& p22, const std::string& p23, const std::string& p24, const std::string& p25, const std::string& p26, const std::string& p27, const std::string& p28, const std::string& p29, const std::string& p30, const std::string& p31, const std::string& p32) { return omni::io::cpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32); }

            // std::wstring 
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3) { return omni::io::wpath::combine(p1, p2, p3); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4) { return omni::io::wpath::combine(p1, p2, p3, p4); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5) { return omni::io::wpath::combine(p1, p2, p3, p4, p5); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27, const std::wstring& p28) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27, const std::wstring& p28, const std::wstring& p29) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27, const std::wstring& p28, const std::wstring& p29, const std::wstring& p30) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27, const std::wstring& p28, const std::wstring& p29, const std::wstring& p30, const std::wstring& p31) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31); }
            inline std::wstring combine(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3, const std::wstring& p4, const std::wstring& p5, const std::wstring& p6, const std::wstring& p7, const std::wstring& p8, const std::wstring& p9, const std::wstring& p10, const std::wstring& p11, const std::wstring& p12, const std::wstring& p13, const std::wstring& p14, const std::wstring& p15, const std::wstring& p16, const std::wstring& p17, const std::wstring& p18, const std::wstring& p19, const std::wstring& p20, const std::wstring& p21, const std::wstring& p22, const std::wstring& p23, const std::wstring& p24, const std::wstring& p25, const std::wstring& p26, const std::wstring& p27, const std::wstring& p28, const std::wstring& p29, const std::wstring& p30, const std::wstring& p31, const std::wstring& p32) { return omni::io::wpath::combine(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32); }
        }
    }
}

#undef OMNI_IO_PATH_COMBINE_FW
