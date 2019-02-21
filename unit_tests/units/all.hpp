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
            print_info(omni::chrono::time);
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
            print_info(omni::drawing::color);

            // exceptions
            print_info(omni::exception);
            print_info(omni::exceptions::string_exception);
            print_info(omni::exceptions::stopwatch_exception);
            print_info(omni::exceptions::thread_exception);
            print_info(omni::exceptions::threadpool_exception);
            print_info(omni::exceptions::mutex_system_exception);
            print_info(omni::exceptions::semaphore_system_exception);
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_ALL
