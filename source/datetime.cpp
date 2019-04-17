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
#include <omni/chrono/datetime.hpp>

#if defined(OMNI_SAFE_DATETIME)
    #define OMNI_SAFE_DTTMMTX_FW m_mtx(),
    #define OMNI_DTTM_ALOCK_FW    omni::sync::scoped_lock<omni::sync::basic_lock> mlock(&this->m_mtx);
    #define OMNI_DTTM_MLOCK_FW    this->m_mtx.lock();
    #define OMNI_DTTM_ULOCK_FW    this->m_mtx.unlock();
#else
    #define OMNI_SAFE_DTTMMTX_FW
    #define OMNI_DTTM_ALOCK_FW
    #define OMNI_DTTM_MLOCK_FW
    #define OMNI_DTTM_ULOCK_FW
#endif

/*
// TODO: these are in the C# source, do these _need_ to be const or can the be hash-define'd for the framework??
const int32_t omni::chrono::datetime::DATE_PART_YEAR = 0;
const int32_t omni::chrono::datetime::DATE_PART_DAY_OF_YEAR = 1;
const int32_t omni::chrono::datetime::DATE_PART_MONTH = 2;
const int32_t omni::chrono::datetime::DATE_PART_DAY = 3;
const uint64_t omni::chrono::datetime::TICKS_MASK = 0X3FFFFFFFFFFFFFFF;
const uint64_t omni::chrono::datetime::FLAGS_MASK = 0XC000000000000000;
const uint64_t omni::chrono::datetime::LOCAL_MASK = 0X8000000000000000;
const int64_t omni::chrono::datetime::TICKS_CEILING = 0X4000000000000000;
const uint64_t omni::chrono::datetime::KIND_UNSPECIFIED = 0X0000000000000000;
const uint64_t omni::chrono::datetime::KIND_UTC = 0X4000000000000000;
const uint64_t omni::chrono::datetime::KIND_LOCAL = 0X8000000000000000;
const uint64_t omni::chrono::datetime::KIND_LOCAL_AMBIGUOUS_DST = 0XC000000000000000;
const int32_t omni::chrono::datetime::KIND_SHIFT = 62;


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
public DateTime(int year, int month, int day, Calendar calendar) 
    : this(year, month, day, 0, 0, 0, calendar) {
}

// Constructs a DateTime from a given year, month, day, hour,
// minute, and second.
//
public DateTime(int year, int month, int day, int hour, int minute, int second) {
    this.dateData = (UInt64)(DateToTicks(year, month, day) + TimeToTicks(hour, minute, second));
}

public DateTime(int year, int month, int day, int hour, int minute, int second, DateTimeKind kind) {
    if (kind < DateTimeKind.Unspecified || kind > DateTimeKind.Local) {
        throw new ArgumentException(Environment.GetResourceString("Argument_InvalidDateTimeKind"), "kind");
    }
    Contract.EndContractBlock();
    Int64 ticks = DateToTicks(year, month, day) + TimeToTicks(hour, minute, second);
    this.dateData = ((UInt64)ticks | ((UInt64)kind << KindShift));
}

// Constructs a DateTime from a given year, month, day, hour,
// minute, and second for the specified calendar.
//
public DateTime(int year, int month, int day, int hour, int minute, int second, Calendar calendar) {
    if (calendar == null)
        throw new ArgumentNullException("calendar");
    Contract.EndContractBlock();
    this.dateData = (UInt64)calendar.ToDateTime(year, month, day, hour, minute, second, 0).Ticks;
}
    
// Constructs a DateTime from a given year, month, day, hour,
// minute, and second.
//
public DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond) {
    if (millisecond < 0 || millisecond >= MillisPerSecond) {
        throw new ArgumentOutOfRangeException("millisecond", Environment.GetResourceString("ArgumentOutOfRange_Range", 0, MillisPerSecond - 1));
    }
    Contract.EndContractBlock();
    Int64 ticks = DateToTicks(year, month, day) + TimeToTicks(hour, minute, second);
    ticks += millisecond * TicksPerMillisecond;
    if (ticks < MinTicks || ticks > MaxTicks)
        throw new ArgumentException(Environment.GetResourceString("Arg_DateTimeRange"));
    this.dateData = (UInt64)ticks;
}

public DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, DateTimeKind kind) {
    if (millisecond < 0 || millisecond >= MillisPerSecond) {
        throw new ArgumentOutOfRangeException("millisecond", Environment.GetResourceString("ArgumentOutOfRange_Range", 0, MillisPerSecond - 1));
    }
    if (kind < DateTimeKind.Unspecified || kind > DateTimeKind.Local) {
        throw new ArgumentException(Environment.GetResourceString("Argument_InvalidDateTimeKind"), "kind");
    }
    Contract.EndContractBlock();
    Int64 ticks = DateToTicks(year, month, day) + TimeToTicks(hour, minute, second);
    ticks += millisecond * TicksPerMillisecond;
    if (ticks < MinTicks || ticks > MaxTicks)
        throw new ArgumentException(Environment.GetResourceString("Arg_DateTimeRange"));
    this.dateData = ((UInt64)ticks | ((UInt64)kind << KindShift));
}

// Constructs a DateTime from a given year, month, day, hour,
// minute, and second for the specified calendar.
//
public DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, Calendar calendar) {
    if (calendar == null)
        throw new ArgumentNullException("calendar");
    if (millisecond < 0 || millisecond >= MillisPerSecond) {
        throw new ArgumentOutOfRangeException("millisecond", Environment.GetResourceString("ArgumentOutOfRange_Range", 0, MillisPerSecond - 1));
    }
    Contract.EndContractBlock();
    Int64 ticks = calendar.ToDateTime(year, month, day, hour, minute, second, 0).Ticks;
    ticks += millisecond * TicksPerMillisecond;
    if (ticks < MinTicks || ticks > MaxTicks)
        throw new ArgumentException(Environment.GetResourceString("Arg_DateTimeRange"));
    this.dateData = (UInt64)ticks;
}

public DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, Calendar calendar, DateTimeKind kind) {
    if (calendar == null)
        throw new ArgumentNullException("calendar");
    if (millisecond < 0 || millisecond >= MillisPerSecond) {
        throw new ArgumentOutOfRangeException("millisecond", Environment.GetResourceString("ArgumentOutOfRange_Range", 0, MillisPerSecond - 1));
    }            
    if (kind < DateTimeKind.Unspecified || kind > DateTimeKind.Local) {
        throw new ArgumentException(Environment.GetResourceString("Argument_InvalidDateTimeKind"), "kind");
    }
    Contract.EndContractBlock();
    Int64 ticks = calendar.ToDateTime(year, month, day, hour, minute, second, 0).Ticks;
    ticks += millisecond * TicksPerMillisecond;
    if (ticks < MinTicks || ticks > MaxTicks)
        throw new ArgumentException(Environment.GetResourceString("Arg_DateTimeRange"));
    this.dateData = ((UInt64)ticks | ((UInt64)kind << KindShift));
}
*/
