#if defined(OMNI_UTUA) || defined(OMNI_UT_SPAN)

#define UT_NAME span
#define UT_ROOT_NS chrono
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(span, "test the functionality in omni::chrono::span");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::chrono::span_t);
            print_info(omni::chrono::span<int8_t>);
            print_info(omni::chrono::span<int16_t>);
            print_info(omni::chrono::span<int32_t>);
            print_info(omni::chrono::span<int64_t>);            
        }
        
        void base_test()
        {
            span(); printl("");
        }

        void span()
        {
            typedef int64_t TickType;
            omni::chrono::span<TickType> temp_val;
            //                                    d,  h,  m,  s, ticks
            omni::chrono::span<TickType> cspano(365, 24, 60, 60, 1000); // = 1 year, 1 day, 1 hour, 1m, 1s
            TickType TickType_ticks = 1000000;
            omni::chrono::span_t span_t_val(3, 3, 3);
            double double_value = 3.14159;
            TickType span_t_value = 100000;
            TickType span_t_hours = 12;
            TickType span_t_minutes = 32;
            TickType span_t_seconds = 50;
            std::string std_string_s = "3.05:32:42.123";
            omni::chrono::span<TickType> cspan_res;
            
            // span ~~  omni::chrono::span::span()
            // span ~~  omni::chrono::span::span(const omni::chrono::span<TickType>& cp)
            // span ~~  omni::chrono::span::span(span_t ticks)
            // span ~~  omni::chrono::span::span(span_t hours, span_t minutes, span_t seconds)
            // span ~~  omni::chrono::span::span(span_t days, span_t hours, span_t minutes, span_t seconds)
            // span ~~  omni::chrono::span::span(span_t days, span_t hours, span_t minutes, span_t seconds, span_t milliseconds)
            // span ~~  omni::chrono::span::span()
            
            // add ~~ omni::chrono::span<TickType>& omni::chrono::span::add(const omni::chrono::span<TickType>& other)
            test("temp_val.add(cspano)", temp_val.add(cspano), "366.01:01:01.0");
            
            // add ~~ omni::chrono::span<TickType>& omni::chrono::span::add(TickType ticks)
            test("temp_val.add(TickType_ticks)", temp_val.add(TickType_ticks), "366.01:01:01.100");
            
            // can_negate ~~ bool omni::chrono::span::can_negate()
            test("temp_val.can_negate()", (temp_val.can_negate() ? "true" : "false"), "true");
            
            // days ~~ span_t omni::chrono::span::days()
            test("temp_val.days()", temp_val.days(), "366");
            
            // duration ~~ omni::chrono::span<TickType> omni::chrono::span::duration()
            test("temp_val.duration()", temp_val.duration(), "366.01:01:01.100");
            
            // hash_code ~~ uint64_t omni::chrono::span::hash_code()
            test("temp_val.hash_code()", temp_val.hash_code(), "316260611070307");
            
            // hours ~~ span_t omni::chrono::span::hours()
            test("temp_val.hours()", temp_val.hours(), "1");
            
            // milliseconds ~~ span_t omni::chrono::span::milliseconds()
            test("temp_val.milliseconds()", temp_val.milliseconds(), "100");
            
            // minutes ~~ span_t omni::chrono::span::minutes()
            test("temp_val.minutes()", temp_val.minutes(), "1");
            
            // negate ~~ omni::chrono::span<TickType> omni::chrono::span::negate()
            test("temp_val.negate()", temp_val.negate(), "-366.01:01:01.100");
            
            // seconds ~~ span_t omni::chrono::span::seconds()
            test("temp_val.seconds()", temp_val.seconds(), "1");
            
            // subtract ~~ omni::chrono::span<TickType>& omni::chrono::span::subtract(const omni::chrono::span<TickType>& other)
            test("temp_val.subtract(cspano)", temp_val.subtract(cspano), "0.00:00:00.100");
            
            // subtract ~~ omni::chrono::span<TickType>& omni::chrono::span::subtract(TickType ticks)
            test("temp_val.subtract(TickType_ticks)", temp_val.subtract(TickType_ticks), "0.00:00:00.0");
            
            // swap ~~ void omni::chrono::span::swap(omni::chrono::span<TickType>& o)
            temp_val.swap(cspano);
            test("temp_val.swap(cspano)", temp_val, "366.01:01:01.0");
            
            // ticks ~~ span_t omni::chrono::span::ticks()
            test("temp_val.ticks()", temp_val.ticks(), "316260610000000");
            
            // to_string ~~ std::string omni::chrono::span::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "366.01:01:01.0");
            
            // to_string_t ~~ omni::string_t omni::chrono::span::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "366.01:01:01.0");
            
            // to_wstring ~~ std::wstring omni::chrono::span::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "366.01:01:01.0");
            
            // total_days ~~ double omni::chrono::span::total_days()
            test("temp_val.total_days()", temp_val.total_days(), "366.042");
            
            // total_hours ~~ double omni::chrono::span::total_hours()
            test("temp_val.total_hours()", temp_val.total_hours(), "8785.02");
            
            // total_milliseconds ~~ double omni::chrono::span::total_milliseconds()
            test("temp_val.total_milliseconds()", temp_val.total_milliseconds(), "3.16261e+10");
            
            // total_minutes ~~ double omni::chrono::span::total_minutes()
            test("temp_val.total_minutes()", temp_val.total_minutes(), "527101");
            
            // total_seconds ~~ double omni::chrono::span::total_seconds()
            test("temp_val.total_seconds()", temp_val.total_seconds(), "3.16261e+07");
            
            // operator std::string ~~  omni::chrono::span::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "366.01:01:01.0");
            
            // operator std::wstring ~~  omni::chrono::span::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "366.01:01:01.0");
            
            // operator!= ~~ bool omni::chrono::span::operator!=(const omni::chrono::span<TickType>& other)
            test("(temp_val != cspano)", ((temp_val != cspano) ? "true" : "false"), "true");
            
            // operator!= ~~ bool omni::chrono::span::operator!=(span_t val)
            test("(temp_val != span_t_val)", ((temp_val != span_t_val) ? "true" : "false"), "true");
            
            // operator+ ~~ omni::chrono::span<TickType> omni::chrono::span::operator+(const omni::chrono::span<TickType>& other)
            test("(temp_val + cspano)", (temp_val + cspano), "366.01:01:01.0");
            
            // operator+ ~~ omni::chrono::span<TickType> omni::chrono::span::operator+(span_t val)
            test("(temp_val + span_t_val)", (temp_val + span_t_val), "366.04:04:04.0");
            
            // operator+ ~~ omni::chrono::span<TickType>& omni::chrono::span::operator+()
            test("(temp_val + omni::chrono::span<TickType>(10000))", (temp_val + omni::chrono::span<TickType>(10000)), "366.01:01:01.1");
            
            // operator+= ~~ omni::chrono::span<TickType>& omni::chrono::span::operator+=(const omni::chrono::span<TickType>& other)
            test("(temp_val += cspano)", (temp_val += cspano), "366.01:01:01.0");
            
            // operator+= ~~ omni::chrono::span<TickType>& omni::chrono::span::operator+=(span_t val)
            test("(temp_val += span_t_val)", (temp_val += span_t_val), "366.04:04:04.0");
            
            // operator- ~~ omni::chrono::span<TickType> omni::chrono::span::operator-(const omni::chrono::span<TickType>& other)
            test("(temp_val - cspano)", (temp_val - cspano), "366.04:04:04.0");
            
            // operator- ~~ omni::chrono::span<TickType> omni::chrono::span::operator-(span_t val)
            test("(temp_val - span_t_val)", (temp_val - span_t_val), "366.01:01:01.0");
            
            // operator- ~~ omni::chrono::span<TickType> omni::chrono::span::operator-()
            test("(temp_val - omni::chrono::span<TickType>(10000))", (temp_val - omni::chrono::span<TickType>(10000)), "366.04:04:03.999");
            
            // operator-= ~~ omni::chrono::span<TickType>& omni::chrono::span::operator-=(const omni::chrono::span<TickType>& other)
            test("(temp_val -= cspano)", (temp_val -= cspano), "366.04:04:04.0");
            
            // operator-= ~~ omni::chrono::span<TickType>& omni::chrono::span::operator-=(span_t val)
            test("(temp_val -= span_t_val)", (temp_val -= span_t_val), "366.01:01:01.0");
            
            // operator< ~~ bool omni::chrono::span::operator<(const omni::chrono::span<TickType>& other)
            test("(temp_val < cspano)", ((temp_val < cspano) ? "true" : "false"), "false");
            
            // operator< ~~ bool omni::chrono::span::operator<(span_t val)
            test("(temp_val < span_t_val)", ((temp_val < span_t_val) ? "true" : "false"), "false");
            
            // operator<= ~~ bool omni::chrono::span::operator<=(const omni::chrono::span<TickType>& other)
            test("(temp_val <= cspano)", ((temp_val <= cspano) ? "true" : "false"), "false");
            
            // operator<= ~~ bool omni::chrono::span::operator<=(span_t val)
            test("(temp_val <= span_t_val)", ((temp_val <= span_t_val) ? "true" : "false"), "false");
            
            // operator= ~~ omni::chrono::span<TickType>& omni::chrono::span::operator=(const omni::chrono::span<TickType>& other)
            test("(temp_val = cspano)", (temp_val = cspano), "0.00:00:00.0");
            
            // operator= ~~ omni::chrono::span<TickType>& omni::chrono::span::operator=(span_t val)
            test("(temp_val = span_t_val)", (temp_val = span_t_val), "0.03:03:03.0");
            
            // operator== ~~ bool omni::chrono::span::operator==(const omni::chrono::span<TickType>& other)
            test("(temp_val == cspano)", ((temp_val == cspano) ? "true" : "false"), "false");
            
            // operator== ~~ bool omni::chrono::span::operator==(span_t val)
            test("(temp_val == span_t_val)", ((temp_val == span_t_val) ? "true" : "false"), "true");
            
            // operator> ~~ bool omni::chrono::span::operator>(const omni::chrono::span<TickType>& other)
            test("(temp_val > cspano)", ((temp_val > cspano) ? "true" : "false"), "true");
            
            // operator> ~~ bool omni::chrono::span::operator>(span_t val)
            test("(temp_val > span_t_val)", ((temp_val > span_t_val) ? "true" : "false"), "false");
            
            // operator>= ~~ bool omni::chrono::span::operator>=(const omni::chrono::span<TickType>& other)
            test("(temp_val >= cspano)", ((temp_val >= cspano) ? "true" : "false"), "true");
            
            // operator>= ~~ bool omni::chrono::span::operator>=(span_t val)
            test("(temp_val >= span_t_val)", ((temp_val >= span_t_val) ? "true" : "false"), "true");
            
            // from_days ~~ static inline omni::chrono::span<TickType> omni::chrono::span::from_days(double value)
            test("omni::chrono::span<TickType>::from_days(double_value)", omni::chrono::span<TickType>::from_days(double_value), "3.03:23:53.376");
            
            // from_hours ~~ static inline omni::chrono::span<TickType> omni::chrono::span::from_hours(double value)
            test("omni::chrono::span<TickType>::from_hours(double_value)", omni::chrono::span<TickType>::from_hours(double_value), "0.03:08:29.724");
            
            // from_microseconds ~~ static inline omni::chrono::span<TickType> omni::chrono::span::from_microseconds(span_t value)
            test("omni::chrono::span<TickType>::from_microseconds(span_t_value)", omni::chrono::span<TickType>::from_microseconds(span_t_value), "0.00:00:00.100");
            
            // from_milliseconds ~~ static inline omni::chrono::span<TickType> omni::chrono::span::from_milliseconds(double value)
            test("omni::chrono::span<TickType>::from_milliseconds(double_value)", omni::chrono::span<TickType>::from_milliseconds(double_value), "0.00:00:00.3");
            
            // from_minutes ~~ static inline omni::chrono::span<TickType> omni::chrono::span::from_minutes(double value)
            test("omni::chrono::span<TickType>::from_minutes(double_value)", omni::chrono::span<TickType>::from_minutes(double_value), "0.00:03:08.495");
            
            // from_nanoseconds ~~ static inline omni::chrono::span<TickType> omni::chrono::span::from_nanoseconds(span_t value)
            test("omni::chrono::span<TickType>::from_nanoseconds(span_t_value)", omni::chrono::span<TickType>::from_nanoseconds(span_t_value), "0.00:00:00.0");
            
            // from_seconds ~~ static inline omni::chrono::span<TickType> omni::chrono::span::from_seconds(double value)
            test("omni::chrono::span<TickType>::from_seconds(double_value)", omni::chrono::span<TickType>::from_seconds(double_value), "0.00:00:03.142");
            
            // from_ticks ~~ static inline omni::chrono::span<TickType> omni::chrono::span::from_ticks(span_t value)
            test("omni::chrono::span<TickType>::from_ticks(span_t_value)", omni::chrono::span<TickType>::from_ticks(span_t_value), "0.00:00:00.10");
            
            // from_time ~~ static inline omni::chrono::span<TickType> omni::chrono::span::from_time(span_t hours, span_t minutes, span_t seconds)
            test("omni::chrono::span<TickType>::from_time(span_t_hours, span_t_minutes, span_t_seconds)", omni::chrono::span<TickType>::from_time(span_t_hours, span_t_minutes, span_t_seconds), "0.12:32:50.0");
            
            // max_milliseconds ~~ static inline span_t omni::chrono::span::max_milliseconds()
            test("omni::chrono::span<TickType>::max_milliseconds()", omni::chrono::span<TickType>::max_milliseconds(), "922337203685477");
            
            // max_seconds ~~ static inline span_t omni::chrono::span::max_seconds()
            test("omni::chrono::span<TickType>::max_seconds()", omni::chrono::span<TickType>::max_seconds(), "922337203685");
            
            // max_value ~~ static inline omni::chrono::span<TickType> omni::chrono::span::max_value()
            test("omni::chrono::span<TickType>::max_value()", omni::chrono::span<TickType>::max_value(), "10675199.02:48:05.477");
            
            // min_milliseconds ~~ static inline span_t omni::chrono::span::min_milliseconds()
            test("omni::chrono::span<TickType>::min_milliseconds()", omni::chrono::span<TickType>::min_milliseconds(), "-922337203685477");
            
            // min_seconds ~~ static inline span_t omni::chrono::span::min_seconds()
            test("omni::chrono::span<TickType>::min_seconds()", omni::chrono::span<TickType>::min_seconds(), "-922337203685");
            
            // min_value ~~ static inline omni::chrono::span<TickType> omni::chrono::span::min_value()
            test("omni::chrono::span<TickType>::min_value()", omni::chrono::span<TickType>::min_value(), "-10675199.02:48:05.477");
            
            // parse ~~ static omni::chrono::span<TickType> omni::chrono::span::parse(const std::string& s)
            try {
                test("omni::chrono::span<TickType>::parse(std_string_s)", omni::chrono::span<TickType>::parse(std_string_s), std_string_s);
            } catch (const std::exception& ex) {
                printl("Error: " << ex.what());
            } catch (...) {
                printl("Unknown error parsing time span string");
            }
            
            // try_parse ~~ static bool omni::chrono::span::try_parse(const std::string& s, omni::chrono::span<TickType>& result)
            test("omni::chrono::span<TickType>::try_parse(std_string_s, cspan_res)", (omni::chrono::span<TickType>::try_parse(std_string_s, cspan_res) ? "true" : "false"), "true");
            
            // zero ~~ static inline omni::chrono::span<TickType> omni::chrono::span::zero()
            test("omni::chrono::span<TickType>::zero()", omni::chrono::span<TickType>::zero(), "0.00:00:00.0");

            try {
                omni::chrono::span<uint64_t> max = omni::chrono::span<uint64_t>::max_value();
                printl("max = " << max);
                printl("testing overflow");
                max.add(100);
                printl("max = " << max);
            } catch (const std::exception& ex) {
                printl("Error: " << ex.what());
            } catch (...) {
                printl("Unknown error trying overflow");
            }
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_SPAN
