#if defined(OMNI_UTUA) || defined(OMNI_UT_DATE_TIME)

#define UT_NAME date_time
#define UT_ROOT_NS chrono
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(date_time, "test the functionality in omni::chrono::date_time");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::chrono::date_time);
        }
        
        void base_test()
        {
            date_time(); printl("");
        }

        void date_time()
        {
            typedef double T;
            omni::chrono::date_time temp_val(1000);
            omni::chrono::time_span chrono_time_span_value;
            double double_value;
            uint32_t uint32_t_months;
            int64_t int64_t_value;
            int16_t int16_t_value;
            omni::chrono::date_time chrono_date_time_value(temp_val);
            omni::chrono::date_time chrono_date_time_other(500000);
            std::string std_string_format;
            std::wstring std_wstring_format;
            omni::chrono::date_time chrono_date_time_d2(7588181);
            omni::chrono::time_span chrono_time_span_t(1000);
            omni::chrono::date_time chrono_date_time_ap(1001001);
            uint16_t uint16_t_year = 20;
            uint8_t uint8_t_month = 10;
            int64_t int64_t_date_data = 10000;
            int64_t int64_t_file_time = 1000000;
            double double_d = 3.14159;
            std::string std_string_s;
            omni::chrono::date_time date_time_value(505005);
            omni::chrono::date_time_kind chrono_date_time_kind_kind;
            omni::chrono::date_time chrono_date_time_result(omni::chrono::date_time::min_value());
            omni::chrono::date_time_styles chrono_date_time_styles_style;
            
            // date_time ~~  omni::chrono::date_time::date_time(const omni::chrono::date_time& cp)
            // date_time ~~  omni::chrono::date_time::date_time(int64_t ticks)
            // date_time ~~  omni::chrono::date_time::date_time(int64_t ticks, const omni::chrono::date_time_kind& kind)
            // date_time ~~  omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day)
            // date_time ~~  omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
            // date_time ~~  omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, const omni::chrono::date_time_kind& kind)
            // date_time ~~  omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond)
            // date_time ~~  omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond, const omni::chrono::date_time_kind& kind)
            // date_time ~~ omni::sequence::string_t omni::chrono::date_time::date_time()
            // date_time ~~ omni::sequence::string_t omni::chrono::date_time::date_time(char format)
            
            // add ~~ omni::chrono::date_time omni::chrono::date_time::add(const omni::chrono::time_span& value)
            test("temp_val.add(chrono_time_span_value)", temp_val.add(chrono_time_span_value), "?");
            
            // add_days ~~ omni::chrono::date_time omni::chrono::date_time::add_days(double value)
            test("temp_val.add_days(double_value)", temp_val.add_days(double_value), "?");
            
            // add_hours ~~ omni::chrono::date_time omni::chrono::date_time::add_hours(double value)
            test("temp_val.add_hours(double_value)", temp_val.add_hours(double_value), "?");
            
            // add_milliseconds ~~ omni::chrono::date_time omni::chrono::date_time::add_milliseconds(double value)
            test("temp_val.add_milliseconds(double_value)", temp_val.add_milliseconds(double_value), "?");
            
            // add_minutes ~~ omni::chrono::date_time omni::chrono::date_time::add_minutes(double value)
            test("temp_val.add_minutes(double_value)", temp_val.add_minutes(double_value), "?");
            
            // add_months ~~ omni::chrono::date_time omni::chrono::date_time::add_months(uint32_t months)
            test("temp_val.add_months(uint32_t_months)", temp_val.add_months(uint32_t_months), "?");
            
            // add_seconds ~~ omni::chrono::date_time omni::chrono::date_time::add_seconds(double value)
            test("temp_val.add_seconds(double_value)", temp_val.add_seconds(double_value), "?");
            
            // add_ticks ~~ omni::chrono::date_time omni::chrono::date_time::add_ticks(int64_t value)
            test("temp_val.add_ticks(int64_t_value)", temp_val.add_ticks(int64_t_value), "?");
            
            // add_years ~~ omni::chrono::date_time omni::chrono::date_time::add_years(int16_t value)
            test("temp_val.add_years(int16_t_value)", temp_val.add_years(int16_t_value), "?");
            
            // date ~~ omni::chrono::date_time omni::chrono::date_time::date()
            test("temp_val.date()", temp_val.date(), "?");
            
            // day ~~ uint8_t omni::chrono::date_time::day()
            test("temp_val.day()", temp_val.day(), "?");
            
            // day_of_week ~~ omni::chrono::day_of_week omni::chrono::date_time::day_of_week()
            test("temp_val.day_of_week()", temp_val.day_of_week(), "?");
            
            // day_of_year ~~ uint16_t omni::chrono::date_time::day_of_year()
            test("temp_val.day_of_year()", temp_val.day_of_year(), "?");
            
            // hash_code ~~ int32_t omni::chrono::date_time::hash_code()
            test("temp_val.hash_code()", temp_val.hash_code(), "?");
            
            // hour ~~ uint8_t omni::chrono::date_time::hour()
            test("temp_val.hour()", temp_val.hour(), "?");
            
            // is_daylight_saving_time ~~ inline bool omni::chrono::date_time::is_daylight_saving_time()
            test("temp_val.is_daylight_saving_time()", (temp_val.is_daylight_saving_time() ? "true" : "false"), "?");
            
            // is_dst ~~ bool omni::chrono::date_time::is_dst()
            test("temp_val.is_dst()", (temp_val.is_dst() ? "true" : "false"), "?");
            
            // kind ~~ omni::chrono::date_time_kind omni::chrono::date_time::kind()
            test("temp_val.kind()", temp_val.kind(), "?");
            
            // millisecond ~~ uint16_t omni::chrono::date_time::millisecond()
            test("temp_val.millisecond()", temp_val.millisecond(), "?");
            
            // minute ~~ uint8_t omni::chrono::date_time::minute()
            test("temp_val.minute()", temp_val.minute(), "?");
            
            // month ~~ uint8_t omni::chrono::date_time::month()
            test("temp_val.month()", temp_val.month(), "?");
            
            // second ~~ uint8_t omni::chrono::date_time::second()
            test("temp_val.second()", temp_val.second(), "?");
            
            // subtract ~~ omni::chrono::time_span omni::chrono::date_time::subtract(const omni::chrono::date_time& value)
            test("temp_val.subtract(chrono_date_time_value)", temp_val.subtract(chrono_date_time_value), "?");
            
            // subtract ~~ omni::chrono::date_time omni::chrono::date_time::subtract(const omni::chrono::time_span& value)
            test("temp_val.subtract(chrono_time_span_value)", temp_val.subtract(chrono_time_span_value), "?");
            
            // swap ~~ void omni::chrono::date_time::swap(omni::chrono::date_time& other)
            temp_val.swap(chrono_date_time_other);
            test("temp_val.swap(chrono_date_time_other)", temp_val, "?");
            
            // ticks ~~ uint64_t omni::chrono::date_time::ticks()
            test("temp_val.ticks()", temp_val.ticks(), "?");
            
            // time_of_day ~~ omni::chrono::time_span omni::chrono::date_time::time_of_day()
            test("temp_val.time_of_day()", temp_val.time_of_day(), "?");
            
            // to_binary ~~ int64_t omni::chrono::date_time::to_binary()
            test("temp_val.to_binary()", temp_val.to_binary(), "?");
            
            // to_file_time ~~ uint64_t omni::chrono::date_time::to_file_time()
            test("temp_val.to_file_time()", temp_val.to_file_time(), "?");
            
            // to_file_time_utc ~~ uint64_t omni::chrono::date_time::to_file_time_utc()
            test("temp_val.to_file_time_utc()", temp_val.to_file_time_utc(), "?");
            
            // to_local_time ~~ omni::chrono::date_time omni::chrono::date_time::to_local_time()
            test("temp_val.to_local_time()", temp_val.to_local_time(), "?");
            
            // to_long_date_string ~~ std::string omni::chrono::date_time::to_long_date_string()
            test("temp_val.to_long_date_string()", temp_val.to_long_date_string(), "?");
            
            // to_long_date_wstring ~~ std::wstring omni::chrono::date_time::to_long_date_wstring()
            test("temp_val.to_long_date_wstring()", temp_val.to_long_date_wstring(), "?");
            
            // to_long_time_string ~~ std::string omni::chrono::date_time::to_long_time_string()
            test("temp_val.to_long_time_string()", temp_val.to_long_time_string(), "?");
            
            // to_long_time_wstring ~~ std::wstring omni::chrono::date_time::to_long_time_wstring()
            test("temp_val.to_long_time_wstring()", temp_val.to_long_time_wstring(), "?");
            
            // to_oa_date ~~ double omni::chrono::date_time::to_oa_date()
            test("temp_val.to_oa_date()", temp_val.to_oa_date(), "?");
            
            // to_short_date_string ~~ std::string omni::chrono::date_time::to_short_date_string()
            test("temp_val.to_short_date_string()", temp_val.to_short_date_string(), "?");
            
            // to_short_date_wstring ~~ std::wstring omni::chrono::date_time::to_short_date_wstring()
            test("temp_val.to_short_date_wstring()", temp_val.to_short_date_wstring(), "?");
            
            // to_short_time_string ~~ std::string omni::chrono::date_time::to_short_time_string()
            test("temp_val.to_short_time_string()", temp_val.to_short_time_string(), "?");
            
            // to_short_time_wstring ~~ std::wstring omni::chrono::date_time::to_short_time_wstring()
            test("temp_val.to_short_time_wstring()", temp_val.to_short_time_wstring(), "?");
            
            // to_string ~~ std::string omni::chrono::date_time::to_string(const std::string& format)
            test("temp_val.to_string(std_string_format)", temp_val.to_string(std_string_format), "?");
            
            // to_string ~~ std::string omni::chrono::date_time::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "?");
            
            // to_string_t ~~ omni::string_t omni::chrono::date_time::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "?");
            
            // to_universal_time ~~ omni::chrono::date_time omni::chrono::date_time::to_universal_time()
            test("temp_val.to_universal_time()", temp_val.to_universal_time(), "?");
            
            // to_wstring ~~ std::wstring omni::chrono::date_time::to_wstring(const std::wstring& format)
            test("temp_val.to_wstring(std_wstring_format)", temp_val.to_wstring(std_wstring_format), "?");
            
            // to_wstring ~~ std::wstring omni::chrono::date_time::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "?");
            
            // year ~~ uint16_t omni::chrono::date_time::year()
            test("temp_val.year()", temp_val.year(), "?");
            
            // operator std::string ~~  omni::chrono::date_time::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "?");
            
            // operator std::wstring ~~  omni::chrono::date_time::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "?");
            
            // operator!= ~~ bool omni::chrono::date_time::operator!=(const omni::chrono::date_time& d2)
            test("(temp_val != chrono_date_time_d2)", ((temp_val != chrono_date_time_d2) ? "true" : "false"), "?");
            
            // operator+ ~~ omni::chrono::date_time omni::chrono::date_time::operator+(const omni::chrono::time_span& t)
            test("(temp_val + chrono_time_span_t)", (temp_val + chrono_time_span_t), "?");
            
            // operator+ ~~ omni::chrono::time_span omni::chrono::date_time::operator+(const omni::chrono::date_time& d2)
            test("(temp_val + chrono_date_time_d2)", (temp_val + chrono_date_time_d2), "?");
            
            // operator+= ~~ omni::chrono::date_time& omni::chrono::date_time::operator+=(const omni::chrono::time_span& t)
            test("(temp_val += chrono_time_span_t)", (temp_val += chrono_time_span_t), "?");
            
            // operator- ~~ omni::chrono::date_time omni::chrono::date_time::operator-(const omni::chrono::time_span& t)
            test("(temp_val - chrono_time_span_t)", (temp_val - chrono_time_span_t), "?");
            
            // operator- ~~ omni::chrono::time_span omni::chrono::date_time::operator-(const omni::chrono::date_time& d2)
            test("(temp_val - chrono_date_time_d2)", (temp_val - chrono_date_time_d2), "?");
            
            // operator-= ~~ omni::chrono::date_time& omni::chrono::date_time::operator-=(const omni::chrono::time_span& t)
            test("(temp_val -= chrono_time_span_t)", (temp_val -= chrono_time_span_t), "?");
            
            // operator< ~~ bool omni::chrono::date_time::operator<(const omni::chrono::date_time& d2)
            test("(temp_val < chrono_date_time_d2)", ((temp_val < chrono_date_time_d2) ? "true" : "false"), "?");
            
            // operator<= ~~ bool omni::chrono::date_time::operator<=(const omni::chrono::date_time& d2)
            test("(temp_val <= chrono_date_time_d2)", ((temp_val <= chrono_date_time_d2) ? "true" : "false"), "?");
            
            // operator= ~~ omni::chrono::date_time& omni::chrono::date_time::operator=(const omni::chrono::date_time& ap)
            test("(temp_val = chrono_date_time_ap)", (temp_val = chrono_date_time_ap), "?");
            
            // operator== ~~ bool omni::chrono::date_time::operator==(const omni::chrono::date_time& d2)
            test("(temp_val == chrono_date_time_d2)", ((temp_val == chrono_date_time_d2) ? "true" : "false"), "?");
            
            // operator> ~~ bool omni::chrono::date_time::operator>(const omni::chrono::date_time& d2)
            test("(temp_val > chrono_date_time_d2)", ((temp_val > chrono_date_time_d2) ? "true" : "false"), "?");
            
            // operator>= ~~ bool omni::chrono::date_time::operator>=(const omni::chrono::date_time& d2)
            test("(temp_val >= chrono_date_time_d2)", ((temp_val >= chrono_date_time_d2) ? "true" : "false"), "?");
            
            // days_in_month ~~ static uint16_t omni::chrono::date_time::days_in_month(uint16_t year, uint8_t month)
            test("omni::chrono::date_time::days_in_month(uint16_t_year, uint8_t_month)", omni::chrono::date_time::days_in_month(uint16_t_year, uint8_t_month), "?");
            
            // from_binary ~~ static omni::chrono::date_time omni::chrono::date_time::from_binary(int64_t date_data)
            test("omni::chrono::date_time::from_binary(int64_t_date_data)", omni::chrono::date_time::from_binary(int64_t_date_data), "?");
            
            // from_file_time ~~ static omni::chrono::date_time omni::chrono::date_time::from_file_time(int64_t file_time)
            test("omni::chrono::date_time::from_file_time(int64_t_file_time)", omni::chrono::date_time::from_file_time(int64_t_file_time), "?");
            
            // from_file_time_utc ~~ static omni::chrono::date_time omni::chrono::date_time::from_file_time_utc(int64_t file_time)
            test("omni::chrono::date_time::from_file_time_utc(int64_t_file_time)", omni::chrono::date_time::from_file_time_utc(int64_t_file_time), "?");
            
            // from_oa_date ~~ static omni::chrono::date_time omni::chrono::date_time::from_oa_date(double d)
            test("omni::chrono::date_time::from_oa_date(double_d)", omni::chrono::date_time::from_oa_date(double_d), "?");
            
            // is_leap_year ~~ static bool omni::chrono::date_time::is_leap_year(uint16_t year)
            test("omni::chrono::date_time::is_leap_year(uint16_t_year)", (omni::chrono::date_time::is_leap_year(uint16_t_year) ? "true" : "false"), "?");
            
            // max_value ~~ static inline date_time omni::chrono::date_time::max_value()
            test("omni::chrono::date_time::max_value()", omni::chrono::date_time::max_value(), "?");
            
            // min_value ~~ static inline date_time omni::chrono::date_time::min_value()
            test("omni::chrono::date_time::min_value()", omni::chrono::date_time::min_value(), "?");
            
            // now ~~ static omni::chrono::date_time omni::chrono::date_time::now()
            test("omni::chrono::date_time::now()", omni::chrono::date_time::now(), "?");
            
            // parse ~~ static omni::chrono::date_time omni::chrono::date_time::parse(const std::string& s)
            test("omni::chrono::date_time::parse(std_string_s)", omni::chrono::date_time::parse(std_string_s), "?");
            
            // parse_exact ~~ static omni::chrono::date_time omni::chrono::date_time::parse_exact(const std::string& s, const std::string& format)
            test("omni::chrono::date_time::parse_exact(std_string_s, std_string_format)", omni::chrono::date_time::parse_exact(std_string_s, std_string_format), "?");
            
            // specify_kind ~~ static omni::chrono::date_time omni::chrono::date_time::specify_kind(const date_time& value, const omni::chrono::date_time_kind& kind)
            test("omni::chrono::date_time::specify_kind(date_time_value, chrono_date_time_kind_kind)", omni::chrono::date_time::specify_kind(date_time_value, chrono_date_time_kind_kind), "?");
            
            // today ~~ static omni::chrono::date_time omni::chrono::date_time::today()
            test("omni::chrono::date_time::today()", omni::chrono::date_time::today(), "?");
            
            // try_parse ~~ static bool omni::chrono::date_time::try_parse(const std::string& s, omni::chrono::date_time& result)
            test("omni::chrono::date_time::try_parse(std_string_s, chrono_date_time_result)", (omni::chrono::date_time::try_parse(std_string_s, chrono_date_time_result) ? "true" : "false"), "?");
            
            // try_parse_exact ~~ static bool omni::chrono::date_time::try_parse_exact(const std::string& s, const std::string& format, const omni::chrono::date_time_styles& style, omni::chrono::date_time& result)
            test("omni::chrono::date_time::try_parse_exact(std_string_s, std_string_format, chrono_date_time_styles_style, chrono_date_time_result)", (omni::chrono::date_time::try_parse_exact(std_string_s, std_string_format, chrono_date_time_styles_style, chrono_date_time_result) ? "true" : "false"), "?");
            
            // utc_now ~~ static omni::chrono::date_time omni::chrono::date_time::utc_now()
            test("omni::chrono::date_time::utc_now()", omni::chrono::date_time::utc_now(), "?");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_DATE_TIME
