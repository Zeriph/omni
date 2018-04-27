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
#if !defined(OMNI_FSTREAM_T_HPP)
#define OMNI_FSTREAM_T_HPP 1
#include <omni/defs/global.hpp>
#include <fstream>

#if defined(OMNI_UNICODE)
    #define OMNI_OFSTREAM_T std::wofstream
    #define OMNI_IFSTREAM_T std::wifstream
    #define OMNI_FSTREAM_T std::wfstream
#else
    #define OMNI_OFSTREAM_T std::ofstream
    #define OMNI_IFSTREAM_T std::ifstream
    #define OMNI_FSTREAM_T std::fstream
#endif

namespace omni {
    /**
     * Defines the underlying std::ofstream type;
     * if OMNI_UNICODE is defined the underlying stream will be a wide stream type
     */
    typedef OMNI_OFSTREAM_T ofstream_t;
    /**
     * Defines the underlying std::ifstream type;
     * if OMNI_UNICODE is defined the underlying stream will be a wide stream type
     */
    typedef OMNI_IFSTREAM_T ifstream_t;
    /**
     * Defines the underlying std::fstream type;
     * if OMNI_UNICODE is defined the underlying stream will be a wide stream type
     */
    typedef OMNI_FSTREAM_T fstream_t;
}

#endif // OMNI_FSTREAM_T_HPP
