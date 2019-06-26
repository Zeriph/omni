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
#if !defined(OMNI_DATETIME_HPP)
#define OMNI_DATETIME_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/date_t.hpp>
#include <omni/ostream.hpp>
#if defined(OMNI_SAFE_DATETIME)
    #include <omni/sync/basic_lock.hpp>
    #include <omni/sync/scoped_lock.hpp>
#endif

// TODO: implement, verify and document

namespace omni {
    namespace chrono {
        /** Undocumented: not finished */
        class datetime
        {
            public:
                datetime();
                datetime(const omni::chrono::datetime& cp);

                /*
                // Constructs a DateTime from a tick count. The ticks
                // argument specifies the date as the number of 100-nanosecond intervals
                // that have elapsed since 1/1/0001 12:00am.
                //
                public DateTime(long ticks) {
                    if (ticks < MinTicks || ticks > MaxTicks)
                        throw new ArgumentOutOfRangeException("ticks", Environment.GetResourceString("ArgumentOutOfRange_DateTimeBadTicks"));
                    Contract.EndContractBlock();
                    dateData = (UInt64)ticks;               
                }

                private DateTime(UInt64 dateData) {
                    this.dateData = dateData;
                }        

                public DateTime(long ticks, DateTimeKind kind) {
                    if (ticks < MinTicks || ticks > MaxTicks) {
                        throw new ArgumentOutOfRangeException("ticks", Environment.GetResourceString("ArgumentOutOfRange_DateTimeBadTicks"));
                    }
                    if (kind < DateTimeKind.Unspecified || kind > DateTimeKind.Local) {
                        throw new ArgumentException(Environment.GetResourceString("Argument_InvalidDateTimeKind"), "kind");
                    }
                    Contract.EndContractBlock();
                    this.dateData = ((UInt64)ticks | ((UInt64)kind << KindShift));
                }

                internal DateTime(long ticks, DateTimeKind kind, Boolean isAmbiguousDst) {
                    if (ticks < MinTicks || ticks > MaxTicks) {
                        throw new ArgumentOutOfRangeException("ticks", Environment.GetResourceString("ArgumentOutOfRange_DateTimeBadTicks"));
                    }
                    Contract.Requires(kind == DateTimeKind.Local, "Internal Constructor is for local times only");
                    Contract.EndContractBlock();
                    dateData = ((UInt64)ticks | (isAmbiguousDst ? KindLocalAmbiguousDst : KindLocal));
                }        
                                            
                // Constructs a DateTime from a given year, month, and day. The
                // time-of-day of the resulting DateTime is always midnight.
                //
                public DateTime(int year, int month, int day) {
                    this.dateData = (UInt64) DateToTicks(year, month, day);
                }

                // Constructs a DateTime from a given year, month, and day for
                // the specified calendar. The
                // time-of-day of the resulting DateTime is always midnight.
                //
                public DateTime(int year, int month, int day, Calendar calendar);
                public DateTime(int year, int month, int day, int hour, int minute, int second);
                public DateTime(int year, int month, int day, int hour, int minute, int second, DateTimeKind kind);
                public DateTime(int year, int month, int day, int hour, int minute, int second, Calendar calendar);
                public DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);
                public DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, DateTimeKind kind);
                public DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, Calendar calendar);
                public DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, Calendar calendar, DateTimeKind kind);
                */


                ~datetime();
                void swap(omni::chrono::datetime& other);
                omni::string_t to_string_t() const;
                std::string to_string() const;
                std::wstring to_wstring() const;
                omni::chrono::datetime& operator=(const omni::chrono::datetime& ap);
                bool operator==(const omni::chrono::datetime& o) const;
                bool operator!=(const omni::chrono::datetime& o) const;
                
                operator std::string() const;
                operator std::wstring() const;

                static datetime MIN_VALUE()
                {
                    return datetime(); //0, omni::chrono::date_time_kind::UNSPECIFIED);
                }
                static datetime MAX_VALUE()
                {
                    return datetime(); // omni::chrono::TICKS_TO_10000AD, omni::chrono::date_time_kind::UNSPECIFIED);
                }
                
                OMNI_MEMBERS_FW(omni::chrono::datetime) // disposing,name,type(),hash()
                OMNI_OSTREAM_FW(omni::chrono::datetime)
                
            private:
                uint64_t m_date;
                #if defined(OMNI_SAFE_DATETIME)
                    mutable omni::sync::basic_lock m_mtx;
                #endif
        };
        
        omni::chrono::datetime now();
    } // namespace chrono
} // namespace omni

namespace std {
    inline void swap(omni::chrono::datetime& o1, omni::chrono::datetime& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_TIME_HPP
