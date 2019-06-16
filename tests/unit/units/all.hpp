#if defined(OMNI_UT_ALL)

#define UT_NAME all
#define UT_DESC "Displays sizeof info for the various classes"
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        typedef omni::delegate1<void, int> omni_delegate1;
        typedef omni::event1<void, int> omni_event1;

        UT_CLASS_CTOR() {}
        
        UT_CLASS_DTOR() {}

        void base_test() { this->info_test(); }
        
        void info_test()
        {
            // std types
            print_info(bool);
            print_info(int);
            print_info(unsigned int);
            print_info(std::size_t);
            print_info(long);
            print_info(unsigned long int);
            print_info(char*);
            
            // omni 'types' ('primitive' objects)
            print_info(omni::callback);
            print_info(omni::action);
            print_info(omni_delegate1);
            print_info(omni_event1);
            print_info(omni::object);
            print_info(omni::property<int>);
            print_info(omni::property<omni::object>);
            print_info(omni::generic_ptr);
            print_info(omni::generic_ptr_safe);
            print_info(omni::smart_ptr<int>);
            print_info(omni::smart_ptr_safe<int>);
            print_info(omni::exception);
            print_info(omni::char_t);
            print_info(omni::string_t);
            print_info(omni::sstream_t);
            print_info(omni::chrono::tick_t);
            print_info(omni::chrono::freq_t);
            print_info(omni::sync::mutex_t);
            print_info(omni::sync::semaphore_t);
            print_info(omni::sync::spin_lock_t);
            print_info(omni::sync::cond_t);
            print_info(omni::sync::thread_t);
            print_info(omni::sync::thread_handle_t);
            print_info(omni::sync::thread_fnptr_t);
            print_info(omni::sync::thread_priority);
            print_info(omni::sync::thread_start_type);
            print_info(omni::sync::thread_state);
            print_info(omni::sync::thread_option);
            print_info(omni::sync::thread_flags);
            print_info(omni::sync::thread_start);
            print_info(omni::sync::parameterized_thread_start);
            
            // omni 'classes' ('complex' objects)
            print_info(omni::application::argparser);
            print_info(omni::stopwatch);
            print_info(omni::util::version);
            print_info(omni::sync::auto_lock<omni::sync::binary_semaphore>);
            print_info(omni::sync::auto_lock<omni::sync::mutex>);
            print_info(omni::sync::auto_lock<omni::sync::mutex_t>);
            print_info(omni::sync::auto_lock<omni::sync::basic_lock>);
            print_info(omni::sync::auto_lock<omni::sync::spin_lock>);
            print_info(omni::sync::scoped_lock<omni::sync::binary_semaphore>);
            print_info(omni::sync::scoped_lock<omni::sync::mutex>);
            print_info(omni::sync::scoped_lock<omni::sync::mutex_t>);
            print_info(omni::sync::scoped_lock<omni::sync::basic_lock>);
            print_info(omni::sync::scoped_lock<omni::sync::spin_lock>);
            print_info(omni::sync::binary_semaphore);
            print_info(omni::sync::mutex);
            print_info(omni::sync::basic_lock);
            print_info(omni::sync::runnable);
            print_info(omni::sync::runnable_thread);
            print_info(omni::sync::semaphore);
            print_info(omni::sync::basic_thread);
            print_info(omni::sync::thread);
            print_info(omni::sync::threadpool);
            print_info(omni::sync::threadpool_task);
            print_info(omni::sync::spin_lock);
            print_info(omni::sync::spin_wait);
            print_info(omni::sync::safe_spin_wait);
            print_info(omni::sync::conditional);
            print_info(omni::chrono::timespan);
            print_info(omni::chrono::unsigned_timespan);
            print_info(omni::chrono::async_timer);
            print_info(omni::chrono::sync_timer);
            print_info(omni::chrono::queue_timer);
            print_info(omni::chrono::drop_timer);
            print_info(omni::geometry::point_t);
            print_info(omni::geometry::point64_t);
            print_info(omni::geometry::pointF_t);
            print_info(omni::geometry::raw_point_t);
            print_info(omni::geometry::raw_point64_t);
            print_info(omni::geometry::raw_pointF_t);
            print_info(omni::geometry::point_3d_t);
            print_info(omni::geometry::point64_3d_t);
            print_info(omni::geometry::pointF_3d_t);
            print_info(omni::geometry::raw_point_3d_t);
            print_info(omni::geometry::raw_point64_3d_t);
            print_info(omni::geometry::raw_pointF_3d_t);
            print_info(omni::geometry::size_t);
            print_info(omni::geometry::size64_t);
            print_info(omni::geometry::sizeF_t);
            print_info(omni::geometry::raw_size_t);
            print_info(omni::geometry::raw_size64_t);
            print_info(omni::geometry::raw_sizeF_t);
            print_info(omni::geometry::rectangle_t);
            print_info(omni::geometry::rectangle64_t);
            print_info(omni::geometry::rectangleF_t);
            print_info(omni::geometry::raw_rectangle_t);
            print_info(omni::geometry::raw_rectangle64_t);
            print_info(omni::geometry::raw_rectangleF_t);
            print_info(omni::drawing::color_t);
            print_info(omni::drawing::color64_t);
            print_info(omni::net::socket);

            // exceptions
            print_info(omni::exception);
            print_info(omni::exceptions::string_exception);
            print_info(omni::exceptions::stopwatch_exception);
            print_info(omni::exceptions::thread_exception);
            print_info(omni::exceptions::threadpool_exception);
            print_info(omni::exceptions::mutex_system_exception);
            print_info(omni::exceptions::semaphore_system_exception);

            // constants (static memory)
            std::cout << "constant static memory consumed: " <<
                    sizeof(omni::chrono::DAYS_PER_YEAR) +
                    sizeof(omni::chrono::DAYS_PER_4_YEARS) +
                    sizeof(omni::chrono::DAYS_PER_100_YEARS) +
                    sizeof(omni::chrono::DAYS_PER_400_YEARS) +
                    sizeof(omni::chrono::DAYS_TO_1601AD) +
                    sizeof(omni::chrono::DAYS_TO_1899AD) +
                    sizeof(omni::chrono::DAYS_TO_10000AD) +
                    sizeof(omni::chrono::TICKS_TO_10000AD) +
                    sizeof(omni::chrono::MILLISECONDS_TO_10000AD) +
                    sizeof(omni::chrono::FILE_TIME_OFFSET) +
                    sizeof(omni::chrono::DOUBLE_DATE_OFFSET) +
                    sizeof(omni::chrono::OA_DATE_MIN_AS_TICKS) +
                    sizeof(omni::chrono::OA_DATE_MIN_AS_DOUBLE) +
                    sizeof(omni::chrono::OA_DATE_MAX_AS_DOUBLE) +
                    sizeof(omni::chrono::DAYS_TO_MONTH_365) +
                    sizeof(omni::chrono::DAYS_TO_MONTH_366) +

                    sizeof(omni::chrono::TICKS_PER_NANOSECOND) +
                    sizeof(omni::chrono::TICKS_PER_MICROSECOND) +
                    sizeof(omni::chrono::TICKS_PER_MILLISECOND) +
                    sizeof(omni::chrono::TICKS_PER_TENTH_SECOND) +
                    sizeof(omni::chrono::TICKS_PER_SECOND) +
                    sizeof(omni::chrono::TICKS_PER_MINUTE) +
                    sizeof(omni::chrono::TICKS_PER_HOUR) +
                    sizeof(omni::chrono::TICKS_PER_DAY) +
                    sizeof(omni::chrono::NANOSECONDS_PER_MICROSECOND) +
                    sizeof(omni::chrono::NANOSECONDS_PER_MILLISECOND) +
                    sizeof(omni::chrono::NANOSECONDS_PER_SECOND) +
                    sizeof(omni::chrono::NANOSECONDS_PER_MINUTE) +
                    sizeof(omni::chrono::NANOSECONDS_PER_HOUR) +
                    sizeof(omni::chrono::NANOSECONDS_PER_DAY) +
                    sizeof(omni::chrono::MICROSECONDS_PER_NANOSECOND) +
                    sizeof(omni::chrono::MICROSECONDS_PER_MILLISECOND) +
                    sizeof(omni::chrono::MICROSECONDS_PER_SECOND) +
                    sizeof(omni::chrono::MICROSECONDS_PER_MINUTE) +
                    sizeof(omni::chrono::MICROSECONDS_PER_HOUR) +
                    sizeof(omni::chrono::MICROSECONDS_PER_DAY) +
                    sizeof(omni::chrono::MILLISECONDS_PER_NANOSECOND) +
                    sizeof(omni::chrono::MILLISECONDS_PER_MICROSECOND) +
                    sizeof(omni::chrono::MILLISECONDS_PER_SECOND) +
                    sizeof(omni::chrono::MILLISECONDS_PER_MINUTE) +
                    sizeof(omni::chrono::MILLISECONDS_PER_HOUR) +
                    sizeof(omni::chrono::MILLISECONDS_PER_DAY) +
                    sizeof(omni::chrono::SECONDS_PER_NANOSECOND) +
                    sizeof(omni::chrono::SECONDS_PER_MICROSECOND) +
                    sizeof(omni::chrono::SECONDS_PER_MILLISECOND) +
                    sizeof(omni::chrono::SECONDS_PER_MINUTE) +
                    sizeof(omni::chrono::SECONDS_PER_HOUR) +
                    sizeof(omni::chrono::SECONDS_PER_DAY) +
                    sizeof(omni::chrono::MINUTES_PER_NANOSECOND) +
                    sizeof(omni::chrono::MINUTES_PER_MICROSECOND) +
                    sizeof(omni::chrono::MINUTES_PER_MILLISECOND) +
                    sizeof(omni::chrono::MINUTES_PER_SECOND) +
                    sizeof(omni::chrono::MINUTES_PER_HOUR) +
                    sizeof(omni::chrono::MINUTES_PER_DAY) +
                    sizeof(omni::chrono::NANOSECONDS_PER_TICK) +
                    sizeof(omni::chrono::MICROSECONDS_PER_TICK) +
                    sizeof(omni::chrono::MILLISECONDS_PER_TICK) +
                    sizeof(omni::chrono::SECONDS_PER_TICK) +
                    sizeof(omni::chrono::MINUTES_PER_TICK) +
                    sizeof(omni::chrono::HOURS_PER_TICK) +
                    sizeof(omni::chrono::DAYS_PER_TICK) +

                    sizeof(omni::consts::size::binary::KB) +
                    sizeof(omni::consts::size::binary::MB) +
                    sizeof(omni::consts::size::binary::GB) +
                    sizeof(omni::consts::size::decimal::KB) +
                    sizeof(omni::consts::size::decimal::MB) +
                    sizeof(omni::consts::size::decimal::GB) +
                    
                    // char
                    std::strlen(omni::cconsts::err::DELEGATE_NOT_FOUND) +
                    std::strlen(omni::cconsts::err::ERR_GET_TIME) +
                    std::strlen(omni::cconsts::err::ERR_MEM_ALLOC) +
                    std::strlen(omni::cconsts::err::ERR_OPEN_PARENT_PROC) +
                    std::strlen(omni::cconsts::err::ERR_RET_PRI_CLASS) +
                    std::strlen(omni::cconsts::err::ERR_SET_PRIORITY) +
                    std::strlen(omni::cconsts::err::FILE_NOT_FOUND) +
                    std::strlen(omni::cconsts::err::FILE_NOT_ACCESSIBLE) +
                    std::strlen(omni::cconsts::err::GENERAL_EXCEPTION) +
                    std::strlen(omni::cconsts::err::INDEX_OOR) +
                    std::strlen(omni::cconsts::err::INVALID_BASE) +
                    std::strlen(omni::cconsts::err::INVALID_CHAR) +
                    std::strlen(omni::cconsts::err::INVALID_CAST) +
                    std::strlen(omni::cconsts::err::INVALID_DELEGATE) +
                    std::strlen(omni::cconsts::err::INVALID_DELEGATE_FUNC_PTR) +
                    std::strlen(omni::cconsts::err::INVALID_OPTION) +
                    std::strlen(omni::cconsts::err::INVALID_SETTING) +
                    std::strlen(omni::cconsts::err::INVALID_SEEK_DIR) +
                    std::strlen(omni::cconsts::err::INVALID_THREAD_HANDLE) +
                    std::strlen(omni::cconsts::err::INVALID_THREAD_PRIORITY) +
                    std::strlen(omni::cconsts::err::INVALID_THREAD_START_TYPE) +
                    std::strlen(omni::cconsts::err::INVALID_SIZE) +
                    std::strlen(omni::cconsts::err::PATH_NOT_ACCESSIBLE) +
                    std::strlen(omni::cconsts::err::SET_PRI_UNSUPPORTED) +
                    std::strlen(omni::cconsts::err::STRING_COUNT_GT0) +
                    std::strlen(omni::cconsts::err::STRING_INVALID_BINARY_FORMAT) +
                    std::strlen(omni::cconsts::err::STRING_INVALID_BINARY_STR_SZ) +
                    std::strlen(omni::cconsts::err::STRING_NOT_NUMERIC) +
                    std::strlen(omni::cconsts::err::SUCCESS) +
                    std::strlen(omni::cconsts::err::UNKNOWN) +
                    sizeof(omni::cconsts::misc::COMMA) +
                    sizeof(omni::cconsts::misc::MINUS) +
                    sizeof(omni::cconsts::misc::NCHAR) +
                    sizeof(omni::cconsts::misc::PERIOD) +
                    sizeof(omni::cconsts::misc::PLUS) +
                    std::strlen(omni::cconsts::size::binary::string::full::B) +
                    std::strlen(omni::cconsts::size::binary::string::full::KB) +
                    std::strlen(omni::cconsts::size::binary::string::full::MB) +
                    std::strlen(omni::cconsts::size::binary::string::full::GB) +
                    std::strlen(omni::cconsts::size::binary::string::full::TB) +
                    std::strlen(omni::cconsts::size::binary::string::full::PB) +
                    std::strlen(omni::cconsts::size::binary::string::full::EB) +
                    std::strlen(omni::cconsts::size::binary::string::full::ZB) +
                    std::strlen(omni::cconsts::size::binary::string::full::YB) +
                    std::strlen(omni::cconsts::size::binary::string::B) +
                    std::strlen(omni::cconsts::size::binary::string::KB) +
                    std::strlen(omni::cconsts::size::binary::string::MB) +
                    std::strlen(omni::cconsts::size::binary::string::GB) +
                    std::strlen(omni::cconsts::size::binary::string::TB) +
                    std::strlen(omni::cconsts::size::binary::string::PB) +
                    std::strlen(omni::cconsts::size::binary::string::EB) +
                    std::strlen(omni::cconsts::size::binary::string::ZB) +
                    std::strlen(omni::cconsts::size::binary::string::YB) +
                    std::strlen(omni::cconsts::size::decimal::string::full::B) +
                    std::strlen(omni::cconsts::size::decimal::string::full::KB) +
                    std::strlen(omni::cconsts::size::decimal::string::full::MB) +
                    std::strlen(omni::cconsts::size::decimal::string::full::GB) +
                    std::strlen(omni::cconsts::size::decimal::string::full::TB) +
                    std::strlen(omni::cconsts::size::decimal::string::full::PB) +
                    std::strlen(omni::cconsts::size::decimal::string::full::EB) +
                    std::strlen(omni::cconsts::size::decimal::string::full::ZB) +
                    std::strlen(omni::cconsts::size::decimal::string::full::YB) +
                    std::strlen(omni::cconsts::size::decimal::string::B) +
                    std::strlen(omni::cconsts::size::decimal::string::KB) +
                    std::strlen(omni::cconsts::size::decimal::string::MB) +
                    std::strlen(omni::cconsts::size::decimal::string::GB) +
                    std::strlen(omni::cconsts::size::decimal::string::TB) +
                    std::strlen(omni::cconsts::size::decimal::string::PB) +
                    std::strlen(omni::cconsts::size::decimal::string::EB) +
                    std::strlen(omni::cconsts::size::decimal::string::ZB) +
                    std::strlen(omni::cconsts::size::decimal::string::YB) +

                    // wchar_t
                    std::wcslen(omni::wconsts::err::DELEGATE_NOT_FOUND) +
                    std::wcslen(omni::wconsts::err::ERR_GET_TIME) +
                    std::wcslen(omni::wconsts::err::ERR_MEM_ALLOC) +
                    std::wcslen(omni::wconsts::err::ERR_OPEN_PARENT_PROC) +
                    std::wcslen(omni::wconsts::err::ERR_RET_PRI_CLASS) +
                    std::wcslen(omni::wconsts::err::ERR_SET_PRIORITY) +
                    std::wcslen(omni::wconsts::err::FILE_NOT_FOUND) +
                    std::wcslen(omni::wconsts::err::FILE_NOT_ACCESSIBLE) +
                    std::wcslen(omni::wconsts::err::GENERAL_EXCEPTION) +
                    std::wcslen(omni::wconsts::err::INDEX_OOR) +
                    std::wcslen(omni::wconsts::err::INVALID_BASE) +
                    std::wcslen(omni::wconsts::err::INVALID_CHAR) +
                    std::wcslen(omni::wconsts::err::INVALID_CAST) +
                    std::wcslen(omni::wconsts::err::INVALID_DELEGATE) +
                    std::wcslen(omni::wconsts::err::INVALID_DELEGATE_FUNC_PTR) +
                    std::wcslen(omni::wconsts::err::INVALID_OPTION) +
                    std::wcslen(omni::wconsts::err::INVALID_SETTING) +
                    std::wcslen(omni::wconsts::err::INVALID_SEEK_DIR) +
                    std::wcslen(omni::wconsts::err::INVALID_THREAD_HANDLE) +
                    std::wcslen(omni::wconsts::err::INVALID_THREAD_PRIORITY) +
                    std::wcslen(omni::wconsts::err::INVALID_THREAD_START_TYPE) +
                    std::wcslen(omni::wconsts::err::INVALID_SIZE) +
                    std::wcslen(omni::wconsts::err::PATH_NOT_ACCESSIBLE) +
                    std::wcslen(omni::wconsts::err::SET_PRI_UNSUPPORTED) +
                    std::wcslen(omni::wconsts::err::STRING_COUNT_GT0) +
                    std::wcslen(omni::wconsts::err::STRING_INVALID_BINARY_FORMAT) +
                    std::wcslen(omni::wconsts::err::STRING_INVALID_BINARY_STR_SZ) +
                    std::wcslen(omni::wconsts::err::STRING_NOT_NUMERIC) +
                    std::wcslen(omni::wconsts::err::SUCCESS) +
                    std::wcslen(omni::wconsts::err::UNKNOWN) +
                    sizeof(omni::wconsts::misc::COMMA) +
                    sizeof(omni::wconsts::misc::MINUS) +
                    sizeof(omni::wconsts::misc::NCHAR) +
                    sizeof(omni::wconsts::misc::PERIOD) +
                    sizeof(omni::wconsts::misc::PLUS) +
                    std::wcslen(omni::wconsts::size::binary::string::full::B) +
                    std::wcslen(omni::wconsts::size::binary::string::full::KB) +
                    std::wcslen(omni::wconsts::size::binary::string::full::MB) +
                    std::wcslen(omni::wconsts::size::binary::string::full::GB) +
                    std::wcslen(omni::wconsts::size::binary::string::full::TB) +
                    std::wcslen(omni::wconsts::size::binary::string::full::PB) +
                    std::wcslen(omni::wconsts::size::binary::string::full::EB) +
                    std::wcslen(omni::wconsts::size::binary::string::full::ZB) +
                    std::wcslen(omni::wconsts::size::binary::string::full::YB) +
                    std::wcslen(omni::wconsts::size::binary::string::B) +
                    std::wcslen(omni::wconsts::size::binary::string::KB) +
                    std::wcslen(omni::wconsts::size::binary::string::MB) +
                    std::wcslen(omni::wconsts::size::binary::string::GB) +
                    std::wcslen(omni::wconsts::size::binary::string::TB) +
                    std::wcslen(omni::wconsts::size::binary::string::PB) +
                    std::wcslen(omni::wconsts::size::binary::string::EB) +
                    std::wcslen(omni::wconsts::size::binary::string::ZB) +
                    std::wcslen(omni::wconsts::size::binary::string::YB) +
                    std::wcslen(omni::wconsts::size::decimal::string::full::B) +
                    std::wcslen(omni::wconsts::size::decimal::string::full::KB) +
                    std::wcslen(omni::wconsts::size::decimal::string::full::MB) +
                    std::wcslen(omni::wconsts::size::decimal::string::full::GB) +
                    std::wcslen(omni::wconsts::size::decimal::string::full::TB) +
                    std::wcslen(omni::wconsts::size::decimal::string::full::PB) +
                    std::wcslen(omni::wconsts::size::decimal::string::full::EB) +
                    std::wcslen(omni::wconsts::size::decimal::string::full::ZB) +
                    std::wcslen(omni::wconsts::size::decimal::string::full::YB) +
                    std::wcslen(omni::wconsts::size::decimal::string::B) +
                    std::wcslen(omni::wconsts::size::decimal::string::KB) +
                    std::wcslen(omni::wconsts::size::decimal::string::MB) +
                    std::wcslen(omni::wconsts::size::decimal::string::GB) +
                    std::wcslen(omni::wconsts::size::decimal::string::TB) +
                    std::wcslen(omni::wconsts::size::decimal::string::PB) +
                    std::wcslen(omni::wconsts::size::decimal::string::EB) +
                    std::wcslen(omni::wconsts::size::decimal::string::ZB) +
                    std::wcslen(omni::wconsts::size::decimal::string::YB) +
                    #if defined(OMNI_UNICODE)
                        std::wcslen(omni::environment::NEW_LINE)
                    #else
                        std::strlen(omni::environment::NEW_LINE)
                    #endif
            << std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_ALL
