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
#if !defined(OMNI_VER_HPP)
#define OMNI_VER_HPP 1
#if !defined(OMNI_NO_FW_VER)
#include <omni/defs/helper.hpp>

#define OMNI_FW_VER_MAJ 0 // Major revision
#define OMNI_FW_VER_MIN 8 // Minor revision
#define OMNI_FW_VER_SUB 1 // Sub revision

#if defined(OMNI_FW_VER_USE_TIME)
    #define OMNI_FW_TS_FW OMNI_DATE " " OMNI_TIME
    #define OMNI_FW_VER_STR OMNI_DEF2STR(OMNI_FW_VER_MAJ) "." OMNI_DEF2STR(OMNI_FW_VER_MIN) "." OMNI_DEF2STR(OMNI_FW_VER_SUB) " (" OMNI_FW_TS_FW ")"
#else
    #define OMNI_FW_VER_STR OMNI_DEF2STR(OMNI_FW_VER_MAJ) "." OMNI_DEF2STR(OMNI_FW_VER_MIN) "." OMNI_DEF2STR(OMNI_FW_VER_SUB)
#endif
    
#endif // !OMNI_NO_FW_VER
#endif // OMNI_VER_HPP
