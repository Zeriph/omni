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
#include <omni/chrono/date_time.hpp>

#if defined(OMNI_SAFE_DATETIME)
    #define OMNI_SAFE_DTTMMTX_FW ,m_mtx()
    #define OMNI_DTTM_ALOCK_FW    omni::sync::scoped_lock<omni::sync::basic_lock> uuid12345(&this->m_mtx);
    #define OMNI_DTTM_OLOCK_FW(o) omni::sync::scoped_lock<omni::sync::basic_lock> uuid54321(&o.m_mtx);
    #define OMNI_DTTM_MLOCK_FW    this->m_mtx.lock();
    #define OMNI_DTTM_ULOCK_FW    this->m_mtx.unlock();
#else
    #define OMNI_SAFE_DTTMMTX_FW
    #define OMNI_DTTM_ALOCK_FW
    #define OMNI_DTTM_OLOCK_FW(o)
    #define OMNI_DTTM_MLOCK_FW
    #define OMNI_DTTM_ULOCK_FW
#endif

// These are local defines
#define OMNI_MAX_MILLIS_FW static_cast<int64_t>(OMNI_MILLISECONDS_TO_10000AD)
#define OMNI_MAX_TICKS_FW OMNI_TICKS_TO_10000AD
#define OMNI_TS_NULL_OFF_FW omni::chrono::time_span::min_value()

#define OMNI_DATE_DATA_HXX_FW
#include <omni/xx/date_data.hxx>
#undef OMNI_DATE_DATA_HXX_FW

// --- start private ctors ---

// not 'user' accessable as it's used to construct empty (min) DT objects
omni::chrono::date_time::date_time() :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint64_t ticks, const std::string& non_op) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(ticks)
    OMNI_SAFE_DTTMMTX_FW
{
    OMNI_UNUSED(non_op);
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(bool is_ambiguous_dst, const omni::chrono::date_time_kind& kind, uint64_t ticks, const std::string& non_op) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    OMNI_UNUSED(non_op);
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range())
    }
    if (kind != omni::chrono::date_time_kind::LOCAL) {
        OMNI_ERR_FW("Invalid enum specified for private constructor", omni::exceptions::invalid_enum())
    }
    this->m_date = (ticks | (is_ambiguous_dst ? OMNI_KIND_LOCAL_AMBIGUOUS_DST_FW : OMNI_KIND_LOCAL_FW));
    OMNI_D5_FW("created");
}

// --- end private ctors ---

omni::chrono::date_time::date_time(const omni::chrono::date_time& cp) :
    OMNI_CPCTOR_FW(cp)
    m_date(cp._date_value())
    OMNI_SAFE_DTTMMTX_FW
{
    OMNI_D5_FW("copied");
}

omni::chrono::date_time::date_time(uint64_t ticks) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range("Invalid tick count specified"))
    }
    this->m_date = ticks;
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint64_t ticks, const omni::chrono::date_time_kind& kind) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range("Invalid tick count specified"))
    }
    if (!omni::chrono::date_time_kind::is_valid(static_cast<int32_t>(kind.value()))) {
        OMNI_ERR_FW("Invalid date kind specified", omni::exceptions::invalid_enum("Invalid date kind specified"))
    }
    this->m_date = (ticks | (static_cast<uint64_t>(kind.value()) << OMNI_KIND_SHIFT_FW));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    this->m_date = static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    this->m_date = static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
                   static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, const omni::chrono::date_time_kind& kind) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (!omni::chrono::date_time_kind::is_valid(static_cast<int32_t>(kind.value()))) {
        OMNI_ERR_FW("Invalid date kind specified", omni::exceptions::invalid_enum("Invalid date kind specified"))
    }
    this->m_date =
    (
        (
            static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
            static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second))
        ) // ticks
        | // OR'd
        ( // with kind
            static_cast<uint64_t>(kind.value()) << OMNI_KIND_SHIFT_FW
        )
    );
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (millisecond >= OMNI_MILLISECONDS_PER_SECOND) {
        OMNI_ERR_FW("Invalid milliseconds specified", omni::exceptions::invalid_range("Invalid milliseconds specified"))
    }
    uint64_t ticks = (
        static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
        static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second))
    ) + (millisecond * OMNI_TICKS_PER_MILLISECOND);
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range("Invalid milliseconds specified"))
    }
    this->m_date = ticks;
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond, const omni::chrono::date_time_kind& kind) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (millisecond >= OMNI_MILLISECONDS_PER_SECOND) {
        OMNI_ERR_FW("Invalid milliseconds specified", omni::exceptions::invalid_range("Invalid milliseconds specified"))
    }
    if (!omni::chrono::date_time_kind::is_valid(static_cast<int32_t>(kind.value()))) {
        OMNI_ERR_FW("Invalid date kind specified", omni::exceptions::invalid_enum("Invalid milliseconds specified"))
    }
    uint64_t ticks = (
        static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
        static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second))
    ) + (millisecond * OMNI_TICKS_PER_MILLISECOND);
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range("Invalid tick count specified"))
    }
    this->m_date = (ticks | (static_cast<uint64_t>(kind.value()) << OMNI_KIND_SHIFT_FW));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::~date_time()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

omni::chrono::date_time omni::chrono::date_time::add(const omni::chrono::time_span& value)
{
    return this->add_ticks(value.ticks());
}

omni::chrono::date_time omni::chrono::date_time::add_days(double value)
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, OMNI_MILLISECONDS_PER_DAY);
}

omni::chrono::date_time omni::chrono::date_time::add_hours(double value)
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, OMNI_MILLISECONDS_PER_HOUR);
}

omni::chrono::date_time omni::chrono::date_time::add_milliseconds(double value)
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, 1);
}

omni::chrono::date_time omni::chrono::date_time::add_minutes(double value)
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, OMNI_MILLISECONDS_PER_MINUTE);
}

omni::chrono::date_time omni::chrono::date_time::add_months(int32_t months)
{
    OMNI_DTTM_ALOCK_FW
    if ((months < -120000) || (months > 120000)) {
        OMNI_ERR_RETV_FW("Invalid months specified", omni::exceptions::invalid_range("Invalid months specified"), omni::chrono::date_time())
    }
    int64_t y = omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_YEAR_FW);
    int64_t m = omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_MONTH_FW);
    int64_t d = omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_DAY_FW);
    int64_t i = m - 1 + months;
    if (i >= 0) {
        m = i % 12 + 1;
        y = y + i / 12;
    } else {
        m = 12 + (i + 1) % 12;
        y = y + (i - 11) / 12;
    }
    if (y < 1 || y > 9999) {
        OMNI_ERR_RETV_FW("Invalid months specified", omni::exceptions::invalid_range("Invalid months specified"), omni::chrono::date_time())
    }
    int days = omni::chrono::date_time::days_in_month(y, m);
    if (d > days) {
        d = days;
    }
    return omni::chrono::date_time(
        static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(y, m, d) + (this->_ticks() % OMNI_TICKS_PER_DAY))
        | this->_internal_kind()
    );
}

omni::chrono::date_time omni::chrono::date_time::add_seconds(double value)
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, OMNI_MILLISECONDS_PER_SECOND);
}

omni::chrono::date_time omni::chrono::date_time::add_ticks(int64_t value)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    if ((value > (OMNI_MAX_TICKS_FW - ticks)) || (value < (-ticks)) ) {
        OMNI_ERR_RETV_FW("Invalid ticks specified", omni::exceptions::invalid_range("Invalid ticks specified"), omni::chrono::date_time())
    }
    return omni::chrono::date_time(static_cast<uint64_t>(ticks + value) | this->_internal_kind());
}

omni::chrono::date_time omni::chrono::date_time::add_years(int16_t value)
{
    if ((value < -10000) || (value > 10000)) {
        OMNI_ERR_RETV_FW("Invalid years specified", omni::exceptions::invalid_range(), omni::chrono::date_time())
    }
    return this->add_months(value * 12);
}

bool omni::chrono::date_time::is_dst() const
{
    OMNI_DTTM_ALOCK_FW
    if (this->_kind() == omni::chrono::date_time_kind::UTC) {
        return false;
    }
    // TOOD: more TimeZoneInfo that needs to be implemented
    //return TimeZoneInfo.Local.IsDaylightSavingTime(this, TimeZoneInfoOptions.NoThrowOnInvalidTime);
    return false;
}

int64_t omni::chrono::date_time::to_binary() const
{
    if (this->kind() == omni::chrono::date_time_kind::UTC) {
        /*
            Local times need to be adjusted as you move from one time zone to another, 
            just as they are when serializing in text. As such the format for local times
            changes to store the ticks of the UTC time, but with flags that look like a 
            local date.
        
            To match serialization in text we need to be able to handle cases where
            the UTC value would be out of range. Unused parts of the ticks range are
            used for this, so that values just past max value are stored just past the
            end of the maximum range, and values just below minimum value are stored
            at the end of the ticks area, just below 2^62.
        */

        // TODO: = TimeZoneInfo.GetLocalUtcOffset(this, TimeZoneInfoOptions.NoThrowOnInvalidTime);
        omni::chrono::time_span offset;
        int64_t ticks = this->_ticks();
        int64_t stored = ticks - offset.ticks();
        if (stored < 0) {
            stored = OMNI_TICKS_CEILING_FW + stored;
        }
        return stored | static_cast<int64_t>(OMNI_LOCAL_MASK_FW);
    }
    return static_cast<int64_t>(this->m_date);
}

omni::chrono::date_time omni::chrono::date_time::date() const
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    return omni::chrono::date_time(static_cast<uint64_t>(ticks - ticks % OMNI_TICKS_PER_DAY) | this->_internal_kind());
}

// Returns the day-of-month part of this DateTime. The returned value is an integer between 1 and 31.
uint8_t omni::chrono::date_time::day() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_DAY_FW);
}

omni::chrono::day_of_week omni::chrono::date_time::day_of_week() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::day_of_week(
        static_cast<omni::chrono::day_of_week::enum_t>((this->_ticks() / OMNI_TICKS_PER_DAY + 1) % 7)
    );
}

uint16_t omni::chrono::date_time::day_of_year() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_DAY_OF_YEAR_FW);
}

int32_t omni::chrono::date_time::hash_code() const
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    return static_cast<int32_t>(ticks) ^ static_cast<int32_t>(ticks >> 32);
}

uint8_t omni::chrono::date_time::hour() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint8_t>((this->_ticks() / OMNI_TICKS_PER_HOUR) % 24);
}

omni::chrono::date_time_kind omni::chrono::date_time::kind() const
{
    OMNI_DTTM_ALOCK_FW
    return this->_kind();
}

uint16_t omni::chrono::date_time::millisecond() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>((this->_ticks()/ OMNI_TICKS_PER_MILLISECOND) % 1000); 
}

uint8_t omni::chrono::date_time::minute() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>((this->_ticks()/ OMNI_TICKS_PER_MINUTE) % 60); 
}

uint8_t omni::chrono::date_time::month() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_MONTH_FW);
}

uint8_t omni::chrono::date_time::second() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>((this->_ticks()/ OMNI_TICKS_PER_SECOND) % 60); 
}

uint64_t omni::chrono::date_time::ticks() const
{
    OMNI_DTTM_ALOCK_FW
    return this->_ticks();
}

omni::chrono::time_span omni::chrono::date_time::time_of_day() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::time_span(this->_ticks() % OMNI_TICKS_PER_DAY); 
}

uint16_t omni::chrono::date_time::year() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_YEAR_FW);
}

omni::chrono::time_span omni::chrono::date_time::subtract(const omni::chrono::date_time& value) const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::time_span(this->_ticks() - value._ticks());
}

omni::chrono::date_time omni::chrono::date_time::subtract(const omni::chrono::time_span& value) const
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();            
    int64_t vticks = value.ticks();
    if ((ticks < vticks) || ((ticks - OMNI_MAX_TICKS_FW) > vticks)) {
        OMNI_ERR_RETV_FW("Invalid time span specified", omni::exceptions::invalid_range("Invalid time span specified"), omni::chrono::date_time())
    }
    return omni::chrono::date_time(static_cast<uint64_t>(ticks - vticks) | this->_internal_kind());
}

double omni::chrono::date_time::to_oa_date() const
{
    OMNI_DTTM_ALOCK_FW
    return this->_ticks_to_oa_date(this->_ticks());
}

uint64_t omni::chrono::date_time::to_file_time() const
{
    // Treats the input as local if it is not specified
    return this->to_universal_time().to_file_time_utc();
}

uint64_t omni::chrono::date_time::to_file_time_utc() const
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = (
        ((this->_internal_kind() & OMNI_LOCAL_MASK_FW) != 0) ?
        this->to_universal_time()._ticks() :
        this->_ticks()
    ) - OMNI_FILE_TIME_OFFSET;
    if (ticks < 0) {
        OMNI_ERR_RETV_FW("Invalid file time specified", omni::exceptions::invalid_range(), 0)
    }
    return ticks;
}

omni::chrono::date_time omni::chrono::date_time::to_local_time() const
{
    OMNI_DTTM_ALOCK_FW
    return this->_to_local_time(false);
}

std::string omni::chrono::date_time::to_long_date_string() const
{
    OMNI_DTTM_ALOCK_FW
    return date_time_format::format(*this, "D");
}

std::wstring omni::chrono::date_time::to_long_date_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(date_time_format::format(*this, "D"));
}

std::string omni::chrono::date_time::to_long_time_string() const
{
    OMNI_DTTM_ALOCK_FW
    return date_time_format::format(*this, "T");
}

std::wstring omni::chrono::date_time::to_long_time_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(date_time_format::format(*this, "T"));
}

std::string omni::chrono::date_time::to_short_date_string() const
{
    OMNI_DTTM_ALOCK_FW
    return date_time_format::format(*this, "d");
}

std::wstring omni::chrono::date_time::to_short_date_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(date_time_format::format(*this, "d"));
}

std::string omni::chrono::date_time::to_short_time_string() const
{
    OMNI_DTTM_ALOCK_FW
    return date_time_format::format(*this, "t");
}

std::wstring omni::chrono::date_time::to_short_time_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(date_time_format::format(*this, "t"));
}

std::string omni::chrono::date_time::to_string(const std::string& format) const
{
    OMNI_DTTM_ALOCK_FW
    return date_time_format::format(*this, format);
}

std::wstring omni::chrono::date_time::to_wstring(const std::wstring& format) const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(date_time_format::format(*this, omni::string_util::to_string(format)));
}

omni::chrono::date_time omni::chrono::date_time::to_universal_time() const
{
    if (this->kind() == omni::chrono::date_time_kind::UTC) {
        return omni::chrono::date_time(*this);
    }
    OMNI_DTTM_ALOCK_FW
    // TODO: finish this
    //return TimeZoneInfo.ConvertTimeToUtc(this, TimeZoneInfoOptions.NoThrowOnInvalidTime);
    return omni::chrono::date_time(*this);
}

omni::sequence::string_t omni::chrono::date_time::get_date_time_formats() const
{
    OMNI_DTTM_ALOCK_FW
    // TODO: finish
    // return (GetDateTimeFormats(CultureInfo.CurrentCulture));
    return omni::sequence::string_t();
}

omni::sequence::string_t omni::chrono::date_time::get_date_time_formats(char format) const
{
    OMNI_DTTM_ALOCK_FW
    // TODO: finish
    // return (GetDateTimeFormats(format, CultureInfo.CurrentCulture));
    return omni::sequence::string_t();
}

void omni::chrono::date_time::swap(omni::chrono::date_time& other)
{
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(other)
    OMNI_XOR_SWAP(this->m_date, other.m_date);
}

omni::string_t omni::chrono::date_time::to_string_t() const
{
    #if defined(OMNI_UNICODE)
        return this->to_wstring();
    #else
        return this->to_string();
    #endif
}

std::string omni::chrono::date_time::to_string() const
{
    return this->to_string(std::string());
}

std::wstring omni::chrono::date_time::to_wstring() const
{
    return this->to_wstring(std::wstring());
}

omni::chrono::date_time& omni::chrono::date_time::operator=(const omni::chrono::date_time& ap)
{

    if (this != &ap) {
        OMNI_DTTM_ALOCK_FW
        OMNI_DTTM_OLOCK_FW(ap)
        OMNI_ASSIGN_FW(ap)
        this->m_date = ap.m_date;
    }
    return *this;
}

omni::chrono::date_time omni::chrono::date_time::operator+(const omni::chrono::time_span& t)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = t.ticks();
    if ((vticks > (OMNI_MAX_TICKS_FW - ticks)) || (vticks < (0 - ticks))) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range("Invalid OLE date specified"), *this)
    }
    return omni::chrono::date_time(static_cast<uint64_t>(ticks + vticks) | this->_internal_kind());
}

omni::chrono::date_time omni::chrono::date_time::operator-(const omni::chrono::time_span& t)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = t.ticks();
    if ((ticks < vticks) || ((ticks - OMNI_MAX_TICKS_FW) > vticks)) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range("Invalid OLE date specified"), *this)
    }
    return omni::chrono::date_time(static_cast<uint64_t>(ticks - vticks) | this->_internal_kind());
}

omni::chrono::date_time& omni::chrono::date_time::operator+=(const omni::chrono::time_span& t)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = t.ticks();
    if ((vticks > (OMNI_MAX_TICKS_FW - ticks)) || (vticks < (0 - ticks))) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range("Invalid OLE date specified"), *this)
    }
    this->m_date = (static_cast<uint64_t>(ticks + vticks) | this->_internal_kind());
    return *this;
}

omni::chrono::date_time& omni::chrono::date_time::operator-=(const omni::chrono::time_span& t)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = t.ticks();
    if ((ticks < vticks) || ((ticks - OMNI_MAX_TICKS_FW) > vticks)) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range(), *this)
    }
    this->m_date = (static_cast<uint64_t>(ticks - vticks) | this->_internal_kind());
    return *this;
}

omni::chrono::time_span omni::chrono::date_time::operator-(const omni::chrono::date_time& d2)
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::time_span(this->_ticks() - d2.ticks());
}

omni::chrono::time_span omni::chrono::date_time::operator+(const omni::chrono::date_time& d2)
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::time_span(this->_ticks() + d2.ticks());
}

bool omni::chrono::date_time::operator==(const omni::chrono::date_time& d2) const
{
    if (this == &d2) { return true; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(d2)
    return (
        this->m_date == d2.m_date
    )
    OMNI_EQUAL_FW(d2);
}

bool omni::chrono::date_time::operator!=(const omni::chrono::date_time& d2) const
{
    return !(*this == d2);
}

bool omni::chrono::date_time::operator<(const omni::chrono::date_time& d2) const
{
    if (this == &d2) { return false; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(d2)
    return (this->m_date < d2.m_date);
}

bool omni::chrono::date_time::operator<=(const omni::chrono::date_time& d2) const
{
    if (this == &d2) { return true; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(d2)
    return (this->m_date <= d2.m_date);
}

bool omni::chrono::date_time::operator>(const omni::chrono::date_time& d2) const
{
    if (this == &d2) { return false; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(d2)
    return (this->m_date > d2.m_date);
}

bool omni::chrono::date_time::operator>=(const omni::chrono::date_time& d2) const
{
    if (this == &d2) { return true; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(d2)
    return (this->m_date >= d2.m_date);
}

// -- start private methods --

omni::chrono::date_time omni::chrono::date_time::_add(double value, int64_t scale)
{
    int64_t millis = static_cast<uint64_t>((value * scale) + ((value >= 0.0) ? 0.5 : -0.5));
    if ((millis <= -OMNI_MAX_MILLIS_FW) || (millis >= OMNI_MAX_MILLIS_FW)) {
        OMNI_ERR_RETV_FW("Invalid value/scale specified", omni::exceptions::invalid_range("Invalid value/scale specified"), omni::chrono::date_time())
    }
    return this->add_ticks(millis * OMNI_TICKS_PER_MILLISECOND);
}

omni::chrono::date_time_kind omni::chrono::date_time::_kind() const
{
    switch (this->_internal_kind()) {
        case OMNI_KIND_UNSPECIFIED_FW:
            return omni::chrono::date_time_kind::UNSPECIFIED;
        case OMNI_KIND_UTC_FW:
            return omni::chrono::date_time_kind::UTC;
        default: break;
    }
    return omni::chrono::date_time_kind::LOCAL;                    
}

int64_t omni::chrono::date_time::_to_binary_raw() const
{
    return static_cast<int64_t>(this->m_date);
}

int64_t omni::chrono::date_time::_get_date_part(uint8_t part) const
{
    #if defined(OMNI_NO_CONSTS)
        const int32_t DT365[] = OMNI_DAYS_TO_MONTH_365;
        const int32_t DT366[] = OMNI_DAYS_TO_MONTH_366;
    #endif
    const int32_t* days = OMNI_NULL;
    int64_t n, y400, y100, y4, y1, m;
    int64_t ticks = this->_ticks();
    // n = number of days since 1/1/0001
    n = (ticks / OMNI_TICKS_PER_DAY);
    // y400 = number of whole 400-year periods since 1/1/0001
    y400 = n / OMNI_DAYS_PER_400_YEARS;
    // n = day number within 400-year period
    n -= y400 * OMNI_DAYS_PER_400_YEARS;
    // y100 = number of whole 100-year periods within 400-year period
    y100 = n / OMNI_DAYS_PER_100_YEARS;
    // Last 100-year period has an extra day, so decrement result if 4
    if (y100 == 4) { y100 = 3; }
    // n = day number within 100-year period
    n -= y100 * OMNI_DAYS_PER_100_YEARS;
    // y4 = number of whole 4-year periods within 100-year period
    y4 = n / OMNI_DAYS_PER_4_YEARS;
    // n = day number within 4-year period
    n -= y4 * OMNI_DAYS_PER_4_YEARS;
    // y1 = number of whole years within 4-year period
    y1 = n / OMNI_DAYS_PER_YEAR;
    // Last year has an extra day, so decrement result if 4
    if (y1 == 4) y1 = 3;
    // If year was requested, compute and return it
    if (part == OMNI_DATE_PART_YEAR_FW) {
        return y400 * 400 + y100 * 100 + y4 * 4 + y1 + 1;
    }
    // n = day number within year
    n -= y1 * OMNI_DAYS_PER_YEAR;
    // If day-of-year was requested, return it
    if (part == OMNI_DATE_PART_YEAR_FW) {
        return n + 1;
    }
    // Leap year calculation looks different from IsLeapYear since y1, y4,
    // and y100 are relative to year 1, not year 0
    m = (n >> 5) + 1;

    // All months have less than 32 days, so n >> 5 is a good conservative
    // estimate for the month
    // m = 1-based month number
    if ((y1 == 3) && (y4 != 24 || y100 == 3)) {
        #if defined(OMNI_NO_CONSTS)
            days = &DT366[0];
        #else
            days = &omni::chrono::DAYS_TO_MONTH_366[0];
        #endif
    } else {
        #if defined(OMNI_NO_CONSTS)
            days = &DT365[0];
        #else
            days = &omni::chrono::DAYS_TO_MONTH_365[0];
        #endif
    }

    while (n >= days[m]) {
        m++;
    }
    // If month was requested, return it
    if (part == OMNI_DATE_PART_MONTH_FW) {
        return m;
    }
    // Return 1-based day-of-month
    return n - days[m - 1] + 1;
}

bool omni::chrono::date_time::_is_ambiguous_daylight_saving_time() const
{
    OMNI_DTTM_ALOCK_FW
    return (this->_internal_kind() == OMNI_KIND_LOCAL_AMBIGUOUS_DST_FW);
}

omni::chrono::date_time omni::chrono::date_time::_to_local_time(bool throw_on_overflow) const
{
    //OMNI_DTTM_ALOCK_FW
    
    if (this->kind() == omni::chrono::date_time_kind::LOCAL) {
        return omni::chrono::date_time(*this);
    }
    bool isDaylightSavings = false;
    bool isAmbiguousLocalDst = false;
    int64_t offset = 0; // TODO: finish -> TimeZoneInfo.GetUtcOffsetFromUtc(this, TimeZoneInfo.Local, out isDaylightSavings, out isAmbiguousLocalDst).Ticks;
    int64_t tick = this->_ticks() + offset;
    if (tick > OMNI_MAX_TICKS_FW) {
        if (throw_on_overflow) {
            OMNI_ERR_RETV_FW("Invalid ticks for local time", omni::exceptions::invalid_range(), omni::chrono::date_time())
        } else {
            return omni::chrono::date_time(OMNI_MAX_TICKS_FW, omni::chrono::date_time_kind::LOCAL);
        }
    }
    if (tick < 0) {
        if (throw_on_overflow) {
            OMNI_ERR_RETV_FW("Invalid local time", omni::exceptions::invalid_range(), omni::chrono::date_time())
        } else {
            return omni::chrono::date_time(0, omni::chrono::date_time_kind::LOCAL);
        }
    }
    return omni::chrono::date_time(isAmbiguousLocalDst, omni::chrono::date_time_kind::LOCAL, static_cast<uint64_t>(tick), std::string(""));
}

// -- start static methods --

uint16_t omni::chrono::date_time::days_in_month(uint16_t year, uint8_t month)
{
    if ((month < 1) || (month > 12)) {
        OMNI_ERR_RETV_FW("Invalid month specified", omni::exceptions::invalid_range("Invalid month specified"), omni::chrono::date_time())
    }
    #if defined(OMNI_NO_CONSTS)
        if (omni::chrono::is_leap_year(year)) {
            // check the year argument
            const int32_t d366[] = OMNI_DAYS_TO_MONTH_366;
            return d366[month] - d366[month - 1];
        }
        const int32_t d365[] = OMNI_DAYS_TO_MONTH_365;
        return d365[month] - d365[month - 1];
    #else
        if (omni::chrono::is_leap_year(year)) {
            // check the year argument
            return omni::chrono::DAYS_TO_MONTH_366[month] - omni::chrono::DAYS_TO_MONTH_366[month - 1];
        }
        return omni::chrono::DAYS_TO_MONTH_365[month] - omni::chrono::DAYS_TO_MONTH_365[month - 1];
    #endif
}

omni::chrono::date_time omni::chrono::date_time::from_binary(int64_t date_data)
{
    if ((date_data & static_cast<int64_t>(OMNI_LOCAL_MASK_FW)) != 0) {
        /*
            Local times need to be adjusted as you move from one time zone to another, 
            just as they are when serializing in text. As such the format for local times
            changes to store the ticks of the UTC time, but with flags that look like a 
            local date.
        */
        bool ambig_dst = false;
        int64_t offset = 0;
        int64_t ticks = (date_data & static_cast<int64_t>(OMNI_TICKS_MASK_FW));
        // Negative ticks are stored in the top part of the range and should be converted back into a negative number
        if (ticks > OMNI_TICKS_CEILING_FW - OMNI_TICKS_PER_DAY) {
            ticks = ticks - OMNI_TICKS_CEILING_FW;
        }
        // Convert the ticks back to local. If the UTC ticks are out of range, we need to default to
        // the UTC offset from MinValue and MaxValue to be consistent with Parse. 
        

        // TODO: need to work on TimeZoneInfo
        /*
        if (ticks < 0) {
            offset = TimeZoneInfo.GetLocalUtcOffset(omni::chrono::date_time::min_value(), TimeZoneInfoOptions.NoThrowOnInvalidTime).Ticks;
        } else if (ticks > OMNI_MAX_TICKS_FW) {
            offset = TimeZoneInfo.GetLocalUtcOffset(omni::chrono::date_time::max_value(), TimeZoneInfoOptions.NoThrowOnInvalidTime).Ticks;
        } else {                    
            // Because the ticks conversion between UTC and local is lossy, we need to capture whether the 
            // time is in a repeated hour so that it can be passed to the DateTime constructor.
            omni::chrono::date_time utcDt(ticks, omni::chrono::date_time_kind::UTC);
            bool isDaylightSavings = false;
            offset = TimeZoneInfo.GetUtcOffsetFromUtc(utcDt, TimeZoneInfo.Local, out isDaylightSavings, out ambig_dst).Ticks;
        }
        */

        ticks += offset;
        // Another behaviour of parsing is to cause small times to wrap around, so that they can be used
        // to compare times of day
        if (ticks < 0) {
            ticks += OMNI_TICKS_PER_DAY;
        }                
        if (ticks < 0 || ticks > OMNI_MAX_TICKS_FW) {
            OMNI_ERR_RETV_FW("Invalid binary tick count specified", omni::exceptions::invalid_range(), omni::chrono::date_time())
        }
        return omni::chrono::date_time(ambig_dst, omni::chrono::date_time_kind::LOCAL, static_cast<uint64_t>(ticks), std::string(""));
    }
    return omni::chrono::date_time::_from_binary_raw(date_data);
}

omni::chrono::date_time omni::chrono::date_time::from_file_time(int64_t file_time)
{
    return omni::chrono::date_time::from_file_time_utc(file_time).to_local_time();
}

omni::chrono::date_time omni::chrono::date_time::from_file_time_utc(int64_t file_time)
{
    if ((file_time < 0) || (file_time > (OMNI_MAX_TICKS_FW - OMNI_FILE_TIME_OFFSET))) {
        OMNI_ERR_RETV_FW("Invalid file time specified", omni::exceptions::invalid_range("Invalid file time specified"), omni::chrono::date_time())
    }
    // This is the ticks in Universal time for this file_time.
    int64_t uticks = file_time + OMNI_FILE_TIME_OFFSET;            
    return omni::chrono::date_time(static_cast<uint64_t>(uticks), omni::chrono::date_time_kind::UTC);
}

omni::chrono::date_time omni::chrono::date_time::from_oa_date(double d)
{
    return omni::chrono::date_time(omni::chrono::date_time::_double_date_to_ticks(d), omni::chrono::date_time_kind::UNSPECIFIED);
}

omni::chrono::date_time omni::chrono::date_time::specify_kind(const omni::chrono::date_time& value, const omni::chrono::date_time_kind& kind)
{
    return omni::chrono::date_time(value._ticks(), kind);
}

omni::chrono::date_time omni::chrono::date_time::now()
{
    omni::chrono::date_time utc = omni::chrono::date_time::utc_now();
    bool isAmbiguousLocalDst = false;
    int64_t offset = 0; // TODO: finish -> TimeZoneInfo.GetDateTimeNowUtcOffsetFromUtc(utc, out isAmbiguousLocalDst).Ticks;
    int64_t tick = utc.ticks() + offset;
    if (tick > OMNI_MAX_TICKS_FW) {
        return omni::chrono::date_time(OMNI_MAX_TICKS_FW, omni::chrono::date_time_kind::LOCAL);
    }
    if (tick < 0) {
        return omni::chrono::date_time(0, omni::chrono::date_time_kind::LOCAL);
    }
    return omni::chrono::date_time(isAmbiguousLocalDst, omni::chrono::date_time_kind::LOCAL, static_cast<uint64_t>(tick), std::string(""));
}

omni::chrono::date_time omni::chrono::date_time::utc_now()
{
    // following code is tuned for speed. Don't change it without running benchmark.
    int64_t ticks = 0;
    #if defined(OMNI_OS_WIN)
        FILETIME ft;
        ::GetSystemTimeAsFileTime(&ft);
        ULARGE_INTEGER tm;
        tm.LowPart = ft.dwLowDateTime;
        tm.HighPart = ft.dwHighDateTime;
        //ticks = static_cast<int64_t>(ft);
        ticks = static_cast<int64_t>(tm.QuadPart);
        /*
            DEV_NOTE: this is from the .NET source, but mathematically doesn't make sense ...

            if (CompatibilitySwitches.IsAppEarlierThanWindowsPhone8) {
                // Windows Phone 7.0/7.1 return the ticks up to millisecond, not up to the 100th nanosecond.

                long ticksms = ticks / TicksPerMillisecond; <- here .. ticksms now == (ticks / TicksPerMillisecond)
                ticks = ticksms * TicksPerMillisecond;      <- so right here, doing ticks = ticksms * TicksPerMillisecond
            }

            that code is like saying this:
            
            ticks = (ticks / TicksPerMillisecond) * TicksPerMillisecond;
            
            and since the multiplication cancels out the division, it's
            just doing this:

            ticks = ticks;

            huh?? Is this some fdiv asm sort of thing?
        */
        ticks += OMNI_FILE_TIME_OFFSET;
    #else
        #if defined(OMNI_OS_APPLE)
            struct timeval tv;
            if (::gettimeofday(&tv, NULL) != 0) {
                OMNI_ERRV_RETV_FW("An error occurred getting the clock time: ", errno, omni::exceptions::clock_exception(errno), false)
            }
            ticks = (tv.tv_sec * OMNI_TICKS_PER_SECOND) + (tv.tv_usec * OMNI_TICKS_PER_MICROSECOND);
        #else
            struct timespec tm;
            if (::clock_gettime(CLOCK_REALTIME, &tm) != 0) {
                OMNI_ERRV_RETV_FW("An error occurred getting the clock time: ", errno, omni::exceptions::clock_exception(errno), false)
            }
            ticks = (tm.tv_sec * OMNI_TICKS_PER_SECOND) + (tm.tv_nsec * OMNI_TICKS_PER_NANOSECOND);
        #endif
        ticks += OMNI_FILE_TIME_OFFSET;
    #endif
    return omni::chrono::date_time((static_cast<uint64_t>(ticks) | OMNI_KIND_UTC_FW), std::string(""));
}

omni::chrono::date_time omni::chrono::date_time::today()
{
    return omni::chrono::date_time::now().date();
}

bool omni::chrono::date_time::is_leap_year(uint16_t year)
{
    if ((year < 1) || (year > 9999)) {
        OMNI_ERR_RETV_FW("Invalid year specified", omni::exceptions::invalid_range("Invalid year specified"), false)
    }
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

omni::chrono::date_time omni::chrono::date_time::parse(const std::string& s)
{
    return date_time_format::DateTimeParse::Parse(s,
        date_time_format::DateTimeFormatInfo::CurrentInfo,
        omni::chrono::date_time_styles::NONE);
}

/*
    Constructs a DateTime from a string. The string must specify a
    date and optionally a time in a culture-specific or universal format.
    Leading and trailing whitespace characters are allowed.
*/
omni::chrono::date_time omni::chrono::date_time::parse_exact(const std::string& s, const std::string& format)
{
    date_time_format::DateTimeFormatInfo dtfi(date_time_format::DateTimeFormatInfo::GetInstance(/*provider*/));
    return date_time_format::DateTimeParse::ParseExact(s, format,
        dtfi,
        omni::chrono::date_time_styles::NONE);
}

bool omni::chrono::date_time::try_parse(const std::string& s, omni::chrono::date_time& result)
{
    return date_time_format::DateTimeParse::TryParse(s,
        date_time_format::DateTimeFormatInfo::CurrentInfo,
        omni::chrono::date_time_styles::NONE, result);
}

bool omni::chrono::date_time::try_parse_exact(const std::string& s, const std::string& format, const omni::chrono::date_time_styles& style, omni::chrono::date_time& result)
{
    date_time_format::DateTimeFormatInfo dtfi(date_time_format::DateTimeFormatInfo::GetInstance(/*provider*/));
    return date_time_format::DateTimeParse::TryParseExact(s, format, dtfi, style, result);
}

// -- start private static methods --

int64_t omni::chrono::date_time::_date_to_ticks(uint16_t year, uint8_t month, uint8_t day)
{
    if ((year >= 1) && (year <= 9999) && (month >= 1) && (month <= 12)) {
        #if defined(OMNI_NO_CONSTS)
            const int32_t d365[] = OMNI_DAYS_TO_MONTH_365;
            const int32_t d366[] = OMNI_DAYS_TO_MONTH_366;
            const int32_t* days = omni::chrono::is_leap_year(year) ? &d365[0]: &d366[0];
        #else
            const int32_t* days = omni::chrono::is_leap_year(year) ?
                                &omni::chrono::DAYS_TO_MONTH_365[0]:
                                &omni::chrono::DAYS_TO_MONTH_366[0];
        #endif

        if ((day >= 1) && (day <= (days[month] - days[month - 1]))) {
            int32_t y = year - 1;
            return ((y * 365) + (y / 4) - (y / 100) + (y / 400) + days[month - 1] + day - 1) * OMNI_TICKS_PER_DAY;
        }
    }
    OMNI_ERR_RETV_FW("Invalid year/month/day specified", omni::exceptions::invalid_range(), 0)
}

int64_t omni::chrono::date_time::_time_to_ticks(uint8_t hour, uint8_t minute, uint8_t second)
{
    //omni::chrono::time_span.TimeToTicks is a family access function which does no error checking, so
    //we need to put some error checking out here.
    if ((hour >= 0) && (hour < 24) && (minute >= 0) && (minute < 60) && (second >=0) && (second < 60)) {
        return omni::chrono::time_span::from_time(hour, minute, second).ticks();
    }
    OMNI_ERR_RETV_FW("Invalid hour/minute/second specified", omni::exceptions::invalid_range(), 0)
}

int64_t omni::chrono::date_time::_double_date_to_ticks(double value)
{
    // DEV_NOTE: the comments are from the .NET source .. thanks to you whomever you were
    // The check done this way will take care of NaN
    if (!(value < OMNI_OA_DATE_MAX_AS_DOUBLE) || !(value > OMNI_OA_DATE_MIN_AS_DOUBLE)) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range(), 0)
    }
    // Conversion to long will not cause an overflow here, as at this point the "value" is in between OADateMinAsDouble and OADateMaxAsDouble
    int64_t millis = static_cast<int64_t>(value * OMNI_MILLISECONDS_PER_DAY + (value >= 0? 0.5: -0.5));
    // The interesting thing here is when you have a value like 12.5 it all positive 12 days and 12 hours from 01/01/1899
    // However if you a value of -12.25 it is minus 12 days but still positive 6 hours, almost as though you meant -11.75 all negative
    // This line below fixes up the millis in the negative case
    if (millis < 0) {
        millis -= (millis % OMNI_MILLISECONDS_PER_DAY) * 2;
    }
    millis += OMNI_DOUBLE_DATE_OFFSET / OMNI_TICKS_PER_MILLISECOND;
    if (millis < 0 || millis >= OMNI_MAX_MILLIS_FW) {
        OMNI_ERR_RETV_FW("Invalid OLE milliseconds specified", omni::exceptions::invalid_range(), 0)
    }
    return millis * OMNI_TICKS_PER_MILLISECOND;
}

omni::chrono::date_time omni::chrono::date_time::_from_binary_raw(int64_t date_data)
{
    int64_t ticks = (date_data & static_cast<int64_t>(OMNI_TICKS_MASK_FW));
    if ((ticks < 0) || (ticks > OMNI_MAX_TICKS_FW)) {
        OMNI_ERR_RETV_FW("Invalid binary tick value", omni::exceptions::invalid_range("Invalid binary tick value"), omni::chrono::date_time())
    }
    return omni::chrono::date_time(static_cast<uint64_t>(date_data));
}

double omni::chrono::date_time::_ticks_to_oa_date(int64_t value)
{
    // DEV_NOTE: the notes are from the .NET source code
    if (value == 0) {
        return 0.0;  // Returns OleAut's zero'ed date value.
    }
    if (value < OMNI_TICKS_PER_DAY) { // This is a fix for VB. They want the default day to be 1/1/0001 rather then 12/30/1899.
        value += OMNI_DOUBLE_DATE_OFFSET; // We could have moved this fix down but we would like to keep the bounds check.
    }
    if (value < OMNI_OA_DATE_MIN_AS_TICKS) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range(), 0)
    }
    // Currently, our max date == OA's max date (12/31/9999), so we don't 
    // need an overflow check in that direction.
    int64_t ms = (value  - OMNI_DOUBLE_DATE_OFFSET) / OMNI_TICKS_PER_MILLISECOND;
    if (ms < 0) {
        int64_t frac = ms % OMNI_MILLISECONDS_PER_DAY;
        if (frac != 0) {
            ms -= (OMNI_MILLISECONDS_PER_DAY + frac) * 2;
        }
    }
    return static_cast<double>(ms) / OMNI_MILLISECONDS_PER_DAY;
}

bool omni::chrono::date_time::_try_create(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond, omni::chrono::date_time& result)
{
    result = omni::chrono::date_time::min_value();
    if (year < 1 || year > 9999 || month < 1 || month > 12) {
        return false;
    }
    if (omni::chrono::date_time::is_leap_year(year)) {
        #if defined(OMNI_NO_CONSTS)
            const int32_t d366[] = OMNI_DAYS_TO_MONTH_366;
            if (day < 1 || day > d366[month] - d366[month - 1]) {
                return false;
            }
        #else
            if (day < 1 || day > omni::chrono::DAYS_TO_MONTH_366[month] - omni::chrono::DAYS_TO_MONTH_366[month - 1]) {
                return false;
            }
        #endif
    } else {
        #if defined(OMNI_NO_CONSTS)
            const int32_t d365[] = OMNI_DAYS_TO_MONTH_365;
            if (day < 1 || day > d365[month] - d365[month - 1]) {
                return false;
            }
        #else
            if (day < 1 || day > omni::chrono::DAYS_TO_MONTH_365[month] - omni::chrono::DAYS_TO_MONTH_365[month - 1]) {
                return false;
            }
        #endif
    }            
    if (hour < 0 || hour >= 24 || minute < 0 || minute >= 60 || second < 0 || second >= 60) {
        return false;
    }                
    if (millisecond < 0 || millisecond >= OMNI_MILLISECONDS_PER_SECOND) {
        return false;
    }
    int64_t ticks = omni::chrono::date_time::_date_to_ticks(year, month, day) + omni::chrono::date_time::_time_to_ticks(hour, minute, second);
    
    ticks += millisecond * OMNI_TICKS_PER_MILLISECOND;
    if (ticks < 0 || ticks > OMNI_MAX_TICKS_FW) {
        return false;
    }
    result = omni::chrono::date_time(ticks, omni::chrono::date_time_kind::UNSPECIFIED);
    return true;
}
