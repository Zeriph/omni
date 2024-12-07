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
            M_LIST_ADD(now, "test the functionality in omni::chrono::date_time::now");
            M_LIST_ADD(utc_now, "test the functionality in omni::chrono::date_time::now and utc_now");
            M_LIST_ADD(util_funcs, "test the utility functions in omni::chrono::date_time");
            M_LIST_ADD(cs_comp, "compares the output from the C# datetime to omni");
            M_LIST_ADD(parse_test, "tests the parsing functions");
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
            double double_value = 0.5;
            uint32_t uint32_t_months = 5;
            int64_t int64_t_value = 100;
            int16_t int16_t_value = 255;
            omni::chrono::date_time chrono_date_time_value(temp_val);
            omni::chrono::date_time chrono_date_time_other(500000);
            std::string std_string_format = "MM/dd/yyyy HH:mm:ss AM";
            std::wstring std_wstring_format = L"MM/dd/yyyy HH:mm:ss AM";;
            omni::chrono::date_time chrono_date_time_d2(7588181);
            omni::chrono::time_span chrono_time_span_t(1000);
            omni::chrono::date_time chrono_date_time_ap(1001001);
            uint16_t uint16_t_year = 20;
            uint8_t uint8_t_month = 10;
            int64_t int64_t_date_data = 10000;
            int64_t int64_t_file_time = 1000000;
            double double_d = 3.14159;
            std::string std_string_s = "10/31/2020 10:42:37 AM";
            omni::chrono::date_time date_time_value(505005);
            omni::chrono::date_time_kind chrono_date_time_kind_kind;
            omni::chrono::date_time chrono_date_time_result(omni::chrono::date_time::min_value());
            omni::chrono::date_time_styles chrono_date_time_styles_style;
            //omni::chrono::date_time current = omni::chrono::date_time::now();

            test("omni::chrono::date_time::now", omni::chrono::date_time::now(), "?");
            
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

        void now()
        {
            double offset = omni::chrono::date_time::offset_from_utc();
            std::cout << "offset in seconds from UTC = " << offset << std::endl << std::endl;

            omni::chrono::date_time now = omni::chrono::date_time::now();
            this->date_info_print(now, "now");

            omni::chrono::date_time today = omni::chrono::date_time::today();
            this->date_info_print(today, "today");
        }

        void utc_now()
        {
            double offset = omni::chrono::date_time::offset_from_utc();
            std::cout << "offset in seconds from UTC = " << offset << std::endl << std::endl;

            omni::chrono::date_time now = omni::chrono::date_time::now();
            this->date_info_print(now, "now");

            omni::chrono::date_time now_to_utc = now.to_utc();
            this->date_info_print(now_to_utc, "now_to_utc");

            omni::chrono::date_time utc = omni::chrono::date_time::utc_now();
            this->date_info_print(utc, "utc");

            // TODO: causes crash
            // omni::chrono::date_time today = omni::chrono::date_time::today();
            // this->date_info_print(today, "today");
            
            omni::chrono::date_time cst = omni::chrono::date_time::from_offset(utc, omni::chrono::span_t(-5, 0, 0));
            this->date_info_print(cst, "cst");

            omni::chrono::date_time utc5 = omni::chrono::date_time::from_offset(utc, omni::chrono::span_t(5, 0, 0));
            this->date_info_print(utc5, "utc+5");

            omni::chrono::date_time utc24 = omni::chrono::date_time::from_offset(utc, omni::chrono::span_t(24, 0, 0));
            this->date_info_print(utc24, "utc+24");

            omni::chrono::date_time dst5 = omni::chrono::date_time::from_offset(utc, omni::chrono::span_t(-5, 0, 0), omni::chrono::date_time_kind::LOCAL_DST);
            this->date_info_print(dst5, "dst-5");

            omni::chrono::date_time dst_5 = omni::chrono::date_time::from_offset(utc, omni::chrono::span_t(5, 0, 0), omni::chrono::date_time_kind::LOCAL_DST);
            this->date_info_print(dst_5, "dst+5");
            
            
            /*
                omni::chrono::date_time add(const omni::chrono::time_span& value);
                omni::chrono::date_time add_days(double value);
                omni::chrono::date_time add_hours(double value);
                omni::chrono::date_time add_milliseconds(double value);
                omni::chrono::date_time add_minutes(double value);
                omni::chrono::date_time add_months(int32_t months);
                omni::chrono::date_time add_seconds(double value);
                omni::chrono::date_time add_ticks(int64_t value);
                omni::chrono::date_time add_years(int16_t value);
                omni::chrono::time_span subtract(const omni::chrono::date_time& value) const;
                omni::chrono::date_time subtract(const omni::chrono::time_span& value) const;
                
                omni::chrono::date_time add(const omni::chrono::time_span& value);
                omni::chrono::date_time add_days(double value);
                omni::chrono::date_time add_hours(double value);
                omni::chrono::date_time add_milliseconds(double value);
                omni::chrono::date_time add_minutes(double value);
                omni::chrono::date_time add_months(int32_t months);
                omni::chrono::date_time add_seconds(double value);
                omni::chrono::date_time add_ticks(int64_t value);
                omni::chrono::date_time add_years(int16_t value);
                --bool is_dst() const;
                --inline bool is_daylight_saving_time() const { return this->is_dst(); }
                --int64_t to_binary() const;
                omni::chrono::date_time date() const;
                --uint8_t day() const;
                --omni::chrono::day_of_week day_of_week() const;
                --uint16_t day_of_year() const;
                int32_t hash_code() const;
                --uint8_t hour() const;
                --omni::chrono::date_time_kind kind() const;
                --uint16_t millisecond() const;
                --uint8_t minute() const;
                --uint8_t month() const;
                --uint8_t second() const;
                --uint64_t ticks() const;
                --omni::chrono::time_span time_of_day() const;
                --uint16_t year() const;
                omni::chrono::time_span subtract(const omni::chrono::date_time& value) const;
                omni::chrono::date_time subtract(const omni::chrono::time_span& value) const;
                --double to_oa_date() const;
                --uint64_t to_file_time() const;
                --uint64_t to_file_time_utc() const;
                omni::chrono::date_time to_local_time() const;
                std::string to_long_date_string() const;
                std::wstring to_long_date_wstring() const;
                std::string to_long_time_string() const;
                std::wstring to_long_time_wstring() const;
                std::string to_short_date_string() const;
                std::wstring to_short_date_wstring() const;
                std::string to_short_time_string() const;
                std::wstring to_short_time_wstring() const;
                std::string to_string(const std::string& format) const;
                std::wstring to_wstring(const std::wstring& format) const;
                omni::chrono::date_time to_universal_time() const;
                omni::sequence::string_t get_date_time_formats() const;
                omni::sequence::string_t get_date_time_formats(char format) const;
                void swap(omni::chrono::date_time& other);
                omni::string_t to_string_t() const;
                std::string to_string() const;
                std::wstring to_wstring() const;
                omni::chrono::date_time& operator=(const omni::chrono::date_time& ap);
                omni::chrono::date_time operator+(const omni::chrono::time_span& t);
                omni::chrono::date_time operator-(const omni::chrono::time_span& t);
                omni::chrono::date_time& operator+=(const omni::chrono::time_span& t);
                omni::chrono::date_time& operator-=(const omni::chrono::time_span& t);
                omni::chrono::time_span operator+(const omni::chrono::date_time& d2);
                omni::chrono::time_span operator-(const omni::chrono::date_time& d2);

                bool operator==(const omni::chrono::date_time& d2) const;
                bool operator!=(const omni::chrono::date_time& d2) const;
                bool operator<(const omni::chrono::date_time& d2) const;
                bool operator<=(const omni::chrono::date_time& d2) const;
                bool operator>(const omni::chrono::date_time& d2) const;
                bool operator>=(const omni::chrono::date_time& d2) const;
            */
        }

        void util_funcs()
        {
            // omni::chrono::date_time::days_in_month
            test("omni::chrono::date_time::days_in_month(1984, 1)", omni::chrono::date_time::days_in_month(1984, 1), "31");
            test("omni::chrono::date_time::days_in_month(1984, 2)", omni::chrono::date_time::days_in_month(1984, 2), "29");
            test("omni::chrono::date_time::days_in_month(2001, 2)", omni::chrono::date_time::days_in_month(2001, 2), "28");
            test("omni::chrono::date_time::days_in_month(2025, 2)", omni::chrono::date_time::days_in_month(2025, 2), "28");

            // omni::chrono::date_time::is_leap_year
            test("omni::chrono::date_time::is_leap_year(1983)", omni::chrono::date_time::is_leap_year(1983), "false");
            test("omni::chrono::date_time::is_leap_year(1984)", omni::chrono::date_time::is_leap_year(1984), "true");
            test("omni::chrono::date_time::is_leap_year(2003)", omni::chrono::date_time::is_leap_year(2003), "false");
            test("omni::chrono::date_time::is_leap_year(2024)", omni::chrono::date_time::is_leap_year(2024), "true");

            /*
                now.is_dst = no
                now.to_binary = -8585021862188565760
                now.kind = LOCAL
                now.year = 2023
                now.month = 11
                now.day = 7
                now.day_of_week = TUESDAY
                now.day_of_year = 311
                now.hour = 23
                now.minute = 17
                now.second = 46
                now.millisecond = 621
                now.ticks = 638349958666210048
                now.time_of_day = 0.23:17:46.621
                now.to_oa_date = 45238
                now.to_file_time = 133438942666210048
                now.to_file_time_utc = 133438942666210048
                now.to_string = ''
            */
            // omni::chrono::date_time::from_binary
            omni::chrono::date_time fb = omni::chrono::date_time::from_binary(-8585021767939111438);
            this->date_info_print(fb, "from_binary");

            // omni::chrono::date_time::from_file_time
            omni::chrono::date_time fft = omni::chrono::date_time::from_file_time(133439036915664370);
            this->date_info_print(fft, "from_file_time");

            // omni::chrono::date_time::from_file_time_utc
            omni::chrono::date_time fftutc = omni::chrono::date_time::from_file_time_utc(133439036915664370);
            this->date_info_print(fftutc, "from_file_time_utc");

            // omni::chrono::date_time::from_oa_date
            omni::chrono::date_time fod = omni::chrono::date_time::from_oa_date(45238.0797634954);
            this->date_info_print(fod, "from_oa_date");

            //this->date_info_print(omni::chrono::date_time::min_value(), "min_value");
            //this->date_info_print(omni::chrono::date_time::max_value(), "max_value");

            /*
                from_binary.is_dst = no
                from_binary.to_binary = -8585024468893268352
                from_binary.kind = LOCAL
                from_binary.year = 2023
                from_binary.month = 11
                from_binary.day = 5
                from_binary.day_of_week = SUNDAY
                from_binary.day_of_year = 309
                from_binary.hour = 4
                from_binary.minute = 53
                from_binary.second = 16
                from_binary.millisecond = 150
                from_binary.ticks = 638347567961507456
                from_binary.time_of_day = 0.04:53:16.150
                from_binary.to_oa_date = 45235.2
                from_binary.to_file_time = 133436551961507456
                from_binary.to_file_time_utc = 133436551961507456
                from_binary.to_string = ''

                from_file_time.is_dst = no
                from_file_time.to_binary = -8468579516893268352
                from_file_time.kind = LOCAL
                from_file_time.year = 2392
                from_file_time.month = 11
                from_file_time.day = 4
                from_file_time.day_of_week = WEDNESDAY
                from_file_time.day_of_year = 309
                from_file_time.hour = 10
                from_file_time.minute = 53
                from_file_time.second = 16
                from_file_time.millisecond = 150
                from_file_time.ticks = 754792519961507456
                from_file_time.time_of_day = 0.10:53:16.150
                from_file_time.to_oa_date = 180009
                from_file_time.to_file_time = 249881503961507456
                from_file_time.to_file_time_utc = 249881503961507456
                from_file_time.to_string = ''

                from_file_time_utc.is_dst = no
                from_file_time_utc.to_binary = -8468579084893268352
                from_file_time_utc.kind = UTC
                from_file_time_utc.year = 2392
                from_file_time_utc.month = 11
                from_file_time_utc.day = 4
                from_file_time_utc.day_of_week = WEDNESDAY
                from_file_time_utc.day_of_year = 309
                from_file_time_utc.hour = 16
                from_file_time_utc.minute = 53
                from_file_time_utc.second = 16
                from_file_time_utc.millisecond = 150
                from_file_time_utc.ticks = 754792735961507456
                from_file_time_utc.time_of_day = 0.16:53:16.150
                from_file_time_utc.to_oa_date = 180010
                from_file_time_utc.to_file_time = 249881503961507456
                from_file_time_utc.to_file_time_utc = 249881503961507456
                from_file_time_utc.to_string = ''

                from_oa_date.is_dst = no
                from_oa_date.to_binary = 638347824000000000
                from_oa_date.kind = UNSPECIFIED
                from_oa_date.year = 2023
                from_oa_date.month = 11
                from_oa_date.day = 5
                from_oa_date.day_of_week = SUNDAY
                from_oa_date.day_of_year = 309
                from_oa_date.hour = 12
                from_oa_date.minute = 0
                from_oa_date.second = 0
                from_oa_date.millisecond = 0
                from_oa_date.ticks = 638347824000000000
                from_oa_date.time_of_day = 0.12:00:00.0
                from_oa_date.to_oa_date = 45235.5
                from_oa_date.to_file_time = 133436808000000000
                from_oa_date.to_file_time_utc = 133436592000000000
                from_oa_date.to_string = ''

            */
        }

        void cs_comp()
        {
            omni::chrono::date_time dt = omni::chrono::date_time::from_file_time(133439036915664370);

            const std::string formats[] = { "d", "D", "f", "F", "g", "G", "m", "o", "r", "s", "t", "T", "u", "U", "y", "Y" };
            for (size_t i; i < 16; ++i) {
                try {
                    std::cout << formats[i] << " = " << dt.to_string(formats[i]) << std::endl;
                } catch (std::exception& ex) {
                    std::cout << "Error parsing format " << formats[i] << ": " << ex.what() << std::endl;
                } catch (...) {
                    std::cout << "Unknown error parsing format " << formats[i] << std::endl;
                }
            }
            
            this->date_info_print(dt, "from_file_time");

            /*
            foreach (String s in dt.GetDateTimeFormats()) {
                System.Console.WriteLine(s);
            }
            */
        }

        void parse_test()
        {
            omni::chrono::date_time out = omni::chrono::date_time::now();
            if (omni::chrono::date_time::try_parse("10/31/2020 10:42:58 AM", out)) {
                date_info_print(out, "parsed");
            } else {
                printl("Could not parse the date: " << "10/31/2020 10:42:58 AM");
            }

            /*
                date_try_parse("10/31/2024 10:31 AM", n);
                date_try_parse("2/16/2008 12:15:12 PM", n);
                date_try_parse("16/02/2008 12:15:12", n); // <- reverse mm/dd
                date_try_parse("08/18/2018 07:22:16", n);
                date_try_parse("08/18/2018", n);
                date_try_parse("8/2018", n);
                date_try_parse("8/18", n);
                date_try_parse("07:22:16", n);
                date_try_parse("7 PM", n);
                date_try_parse("2018-08-18T07:22:16.0000000Z", n);
                date_try_parse("2018-08-18T07:22:16.0000000-07:00", n);
                date_try_parse("08/18/2018 07:22:16 -5:00", n);
                date_try_parse("2008-05-01T07:34:42-5:00", n);
                date_try_parse("2008-05-01 7:34:42Z", n);
                date_try_parse("2008-09-15T09:30:41.7752486-07:00", n);
                date_try_parse("2008-09-15T09:30:41.7752486Z", n);
                date_try_parse("2008-09-15T09:30:41.7752486", n);
                date_try_parse("2008-09-15T09:30:41.7752486-04:00", n);
                date_try_parse("Saturday November 9, 2024 10:31 AM", n);
                date_try_parse("Sat, 9 Nov 2024 10:31:59 AM", n);
                date_try_parse("Mon, 15 Sep 2008 09:30:41 GMT", n);
                date_try_parse("Thu, 01 May 2008 07:34:42 GMT", n);
                date_try_parse("Sat, 18 Aug 2018 07:22:16 GMT", n);
                date_try_parse_exact("20241031 22:31", "yyyyMMdd HH:mm", n);
                date_try_parse_exact("061830RJAN12", "yyHHmmRMMMdd", n);
            */
        }
    
    private:
        void date_info_print(const omni::chrono::date_time& dt, const char* v)
        {
            std::cout << v << ".is_dst = " << (dt.is_dst() ? "yes" : "no") << std::endl
                      << v << ".to_binary = " << dt.to_binary() << std::endl
                      << v << ".hash_code = " << dt.hash_code() << std::endl
                      << v << ".kind = " << dt.kind() << std::endl
                      << v << ".year = " << dt.year() << std::endl
                      << v << ".month = " << static_cast<uint32_t>(dt.month()) << std::endl
                      << v << ".day = " << static_cast<uint32_t>(dt.day()) << std::endl
                      << v << ".day_of_week = " << dt.day_of_week() << std::endl
                      << v << ".day_of_year = " << dt.day_of_year() << std::endl
                      << v << ".hour = " << static_cast<uint32_t>(dt.hour()) << std::endl
                      << v << ".minute = " << static_cast<uint32_t>(dt.minute()) << std::endl
                      << v << ".second = " << static_cast<uint32_t>(dt.second()) << std::endl
                      << v << ".millisecond = " << dt.millisecond() << std::endl
                      << v << ".ticks = " << dt.ticks() << std::endl
                      << v << ".time_of_day = " << dt.time_of_day() << std::endl
                      << v << ".to_oa_date = " << dt.to_oa_date() << std::endl
                      << v << ".to_file_time = " << dt.to_file_time() << std::endl
                      << v << ".to_file_time_utc = " << dt.to_file_time_utc() << std::endl
                      << v << ".to_string = '" << dt.to_string() << "'" << std::endl;
            std::cout << std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_DATE_TIME
