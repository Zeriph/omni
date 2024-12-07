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
#if !defined(OMNI_CHRONO_T_HPP)
#define OMNI_CHRONO_T_HPP 1
#include <omni/types/tick_t.hpp>

namespace omni {
    namespace chrono {
        class monotonic
        {
            public:
                inline static double elapsed_us(omni::chrono::tick_t init, omni::chrono::tick_t end)
                {
                    #if defined(OMNI_OS_APPLE)
                        return (static_cast<double>((end - init)) * static_cast<double>(m_freq.numer)) /
                                static_cast<double>(m_freq.denom * 1000);
                    #else
                        #if defined(OMNI_OS_WIN)
                            #if defined(OMNI_WIN_MONO_TICK_QPC)
                                return (static_cast<double>(((end.QuadPart - init.QuadPart) * 1000000)) / 
                                        static_cast<double>(m_freq.QuadPart));
                            #else
                                return static_cast<double>(end - init);
                            #endif
                        #else
                            return (static_cast<double>(end.tv_nsec - init.tv_nsec) / 1000) + 
                                    static_cast<double>((end.tv_sec - init.tv_sec) * 1000000);
                        #endif
                    #endif
                }
                
                inline static double elapsed_ms(omni::chrono::tick_t init, omni::chrono::tick_t end)
                {
                    return (omni::chrono::monotonic::elapsed_us(init, end) / 1000);
                }
                
                inline static double elapsed_s(omni::chrono::tick_t init, omni::chrono::tick_t end)
                {
                    return (omni::chrono::monotonic::elapsed_us(init, end) / 1000000);
                }
                
                inline static double elapsed_us(omni::chrono::tick_t init)
                {
                    return omni::chrono::monotonic::elapsed_us(init, omni::chrono::monotonic::tick());
                }
                
                inline static double elapsed_ms(omni::chrono::tick_t init)
                {
                    return omni::chrono::monotonic::elapsed_ms(init, omni::chrono::monotonic::tick());
                }
                
                inline static double elapsed_s(omni::chrono::tick_t init)
                {
                    return omni::chrono::monotonic::elapsed_s(init, omni::chrono::monotonic::tick());
                }
                inline static omni::chrono::freq_t frequency()
                {
                    return omni::chrono::monotonic::m_freq;
                }
                
                inline static bool initialize()
                {
                    #if defined(OMNI_OS_WIN)
                        #if defined(OMNI_WIN_MONO_TICK_QPC)
                            if (m_freq.LowPart == 0) {
                                ::QueryPerformanceFrequency(&m_freq);
                            }
                        #endif
                    #elif defined(OMNI_OS_APPLE)
                        if (m_freq.denom == 0) {
                            if (::mach_timebase_info(&m_freq) != KERN_SUCCESS) {
                                #if defined(OMNI_THROW) || defined(OMNI_TERMINATE)
                                    OMNI_ERRV_FW("An error occurred getting the clock resolution: ", std::strerror(errno), omni::exceptions::clock_exception())
                                #else
                                    OMNI_DBGEV("An error occurred getting the clock resolution: ", std::strerror(errno))
                                #endif
                                return false;
                            }
                        }
                    #else
                        if (m_freq.tv_nsec == 0) {
                            // CLOCK_MONOTONIC by default but can be configured for CLOCK_REALTIME where applicable (like QNX)
                            if (::clock_getres(OMNI_CLOCK_GETRES_CID_FW, &m_freq) != 0) {
                                #if defined(OMNI_THROW) || defined(OMNI_TERMINATE)
                                    OMNI_ERRV_FW("An error occurred getting the clock resolution: ", std::strerror(errno), omni::exceptions::clock_exception())
                                #else
                                    OMNI_DBGEV("An error occurred getting the clock resolution: ", std::strerror(errno))
                                #endif
                                return false;
                            }
                        }
                    #endif
                    return true;
                }

                inline static bool initialized()
                {
                    #if defined(OMNI_OS_WIN)
                        #if defined(OMNI_WIN_MONO_TICK_QPC)
                            return (m_freq.LowPart != 0);
                        #else
                            return true;
                        #endif
                    #elif defined(OMNI_OS_APPLE)
                        return (m_freq.denom != 0);
                    #else
                        return (m_freq.tv_nsec != 0);
                    #endif
                }

                inline static omni::chrono::tick_t tick()
                {
                    #if !defined(OMNI_NO_CHRONO_AUTO_INIT_TICK)
                        omni::chrono::monotonic::initialize();
                    #endif
                    #if defined(OMNI_OS_WIN)
                        #if defined(OMNI_WIN_MONO_TICK_QPC)
                            omni::chrono::tick_t tmp;
                            if (::QueryPerformanceCounter(&tmp) == 0) {
                                std::memset(&tmp, 0, sizeof(omni::chrono::tick_t));
                                OMNI_ERR_FW("An error occurred getting the clock time", omni::exceptions::clock_exception())
                            }
                            return tmp;
                        #else
                            return
                            #if defined(OMNI_WIN_API)
                                #if defined(OMNI_WIN_MONO_TICK_COUNT)
                                    ::GetTickCount()
                                #else
                                    ::GetTickCount64()
                                #endif
                            #else
                                std::clock()
                            #endif
                            ;
                        #endif
                    #elif defined(OMNI_OS_APPLE)
                        return ::mach_absolute_time();
                    #else
                        omni::chrono::tick_t tmp;
                        if (::clock_gettime(CLOCK_MONOTONIC, &tmp) != 0) {
                            #if defined(OMNI_THROW) || defined(OMNI_TERMINATE)
                                OMNI_ERRV_FW("An error occurred getting the clock time: ", std::strerror(errno), omni::exceptions::clock_exception())
                            #else
                                OMNI_DBGEV("An error occurred getting the clock time: ", std::strerror(errno))
                                std::memset(&tmp, 0, sizeof(omni::chrono::tick_t));
                            #endif
                        }
                        return tmp;
                    #endif
                }
                
            private:
                monotonic(); // = delete;
                monotonic(const monotonic& cp); // = delete;
                monotonic& operator=(const monotonic& cp); // = delete;
                
                static omni::chrono::freq_t m_freq;
        };
        
        inline bool equal(const omni::chrono::tick_t& t1, const omni::chrono::tick_t& t2)
        {
            /* this is an inline bool so as not to inadvertently override the equality operator, the user
            has to expressly call the function instead of an implicit function call made by compiler where
            a call to t1 == t2 is made */
            return
            #if defined(OMNI_OS_APPLE)
                (t1 == t2)
            #elif defined(OMNI_OS_WIN)
                #if defined(OMNI_WIN_MONO_TICK_QPC)
                    (t1.QuadPart == t2.QuadPart)
                #else
                    (t1 == t2)
                #endif
            #else
                (t1.tv_sec == t2.tv_sec && t1.tv_nsec == t2.tv_nsec)
            #endif
            ;
        }
        
        // for double precision use omni::chrono::monotonic::elapsed_us
        inline uint64_t elapsed_us(omni::chrono::tick_t init, omni::chrono::tick_t end)
        {
            return static_cast<uint64_t>(omni::chrono::monotonic::elapsed_us(init, end));
        }
        
        // for double precision use omni::chrono::monotonic::elapsed_us
        inline uint64_t elapsed_us(omni::chrono::tick_t init)
        {
            return static_cast<uint64_t>(omni::chrono::monotonic::elapsed_us(init));
        }
        
        // for double precision use omni::chrono::monotonic::elapsed_ms
        inline uint64_t elapsed_ms(omni::chrono::tick_t init, omni::chrono::tick_t end)
        {
            return static_cast<uint64_t>(omni::chrono::monotonic::elapsed_ms(init, end));
        }
        
        // for double precision use omni::chrono::monotonic::elapsed_ms
        inline uint64_t elapsed_ms(omni::chrono::tick_t init)
        {
            return static_cast<uint64_t>(omni::chrono::monotonic::elapsed_ms(init));
        }
        
        // for double precision use omni::chrono::monotonic::elapsed_s
        inline uint64_t elapsed_s(omni::chrono::tick_t init, omni::chrono::tick_t end)
        {
            return static_cast<uint64_t>(omni::chrono::monotonic::elapsed_s(init, end));
        }
        
        // for double precision use omni::chrono::monotonic::elapsed_s
        inline uint64_t elapsed_s(omni::chrono::tick_t init)
        {
            return static_cast<uint64_t>(omni::chrono::monotonic::elapsed_s(init));
        }

        inline omni::chrono::tick_t monotonic_tick()
        {
            return omni::chrono::monotonic::tick();
        }
    }
}

#endif // OMNI_CHRONO_T_HPP
