#if defined(OMNI_UT_MISC) || defined(OMNI_UTUA)

#define UT_NAME consts
#define UT_DESC "const's unit test"
#include <utdefs/unit_test.hpp>

#define CONST_OUT(v) omni::out << OMNI_DEF2STR(v) << " = " << v << std::endl

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() {}

        void base_test()
        {   
            CONST_OUT(omni::consts::size::binary::string::full::B);
            CONST_OUT(omni::consts::size::binary::string::full::KB);
            CONST_OUT(omni::consts::size::binary::string::full::MB);
            CONST_OUT(omni::consts::size::binary::string::full::GB);
            CONST_OUT(omni::consts::size::binary::string::full::TB);
            CONST_OUT(omni::consts::size::binary::string::full::PB);
            CONST_OUT(omni::consts::size::binary::string::full::EB);
            CONST_OUT(omni::consts::size::binary::string::full::ZB);
            CONST_OUT(omni::consts::size::binary::string::full::YB);
            CONST_OUT(omni::consts::size::binary::string::B);
            CONST_OUT(omni::consts::size::binary::string::KB);
            CONST_OUT(omni::consts::size::binary::string::MB);
            CONST_OUT(omni::consts::size::binary::string::GB);
            CONST_OUT(omni::consts::size::binary::string::TB);
            CONST_OUT(omni::consts::size::binary::string::PB);
            CONST_OUT(omni::consts::size::binary::string::EB);
            CONST_OUT(omni::consts::size::binary::string::ZB);
            CONST_OUT(omni::consts::size::binary::string::YB);
            CONST_OUT(omni::consts::size::binary::KB);
            CONST_OUT(omni::consts::size::binary::MB);
            CONST_OUT(omni::consts::size::binary::GB);
            CONST_OUT(omni::consts::size::decimal::string::full::B);
            CONST_OUT(omni::consts::size::decimal::string::full::KB);
            CONST_OUT(omni::consts::size::decimal::string::full::MB);
            CONST_OUT(omni::consts::size::decimal::string::full::GB);
            CONST_OUT(omni::consts::size::decimal::string::full::TB);
            CONST_OUT(omni::consts::size::decimal::string::full::PB);
            CONST_OUT(omni::consts::size::decimal::string::full::EB);
            CONST_OUT(omni::consts::size::decimal::string::full::ZB);
            CONST_OUT(omni::consts::size::decimal::string::full::YB);
            CONST_OUT(omni::consts::size::decimal::string::B);
            CONST_OUT(omni::consts::size::decimal::string::KB);
            CONST_OUT(omni::consts::size::decimal::string::MB);
            CONST_OUT(omni::consts::size::decimal::string::GB);
            CONST_OUT(omni::consts::size::decimal::string::TB);
            CONST_OUT(omni::consts::size::decimal::string::PB);
            CONST_OUT(omni::consts::size::decimal::string::EB);
            CONST_OUT(omni::consts::size::decimal::string::ZB);
            CONST_OUT(omni::consts::size::decimal::string::YB);
            CONST_OUT(omni::consts::size::decimal::KB);
            CONST_OUT(omni::consts::size::decimal::MB);
            CONST_OUT(omni::consts::size::decimal::GB);
            CONST_OUT(omni::consts::err::DELEGATE_NOT_FOUND);
            CONST_OUT(omni::consts::err::ERR_GET_TIME);
            CONST_OUT(omni::consts::err::ERR_MEM_ALLOC);
            CONST_OUT(omni::consts::err::ERR_OPEN_PARENT_PROC);
            CONST_OUT(omni::consts::err::ERR_RET_PRI_CLASS);
            CONST_OUT(omni::consts::err::ERR_SET_PRIORITY);
            CONST_OUT(omni::consts::err::FILE_NOT_FOUND);
            CONST_OUT(omni::consts::err::FILE_NOT_ACCESSIBLE);
            CONST_OUT(omni::consts::err::GENERAL_EXCEPTION);
            CONST_OUT(omni::consts::err::INDEX_OOR);
            CONST_OUT(omni::consts::err::INVALID_BASE);
            CONST_OUT(omni::consts::err::INVALID_CHAR);
            CONST_OUT(omni::consts::err::INVALID_CAST);
            CONST_OUT(omni::consts::err::INVALID_DELEGATE);
            CONST_OUT(omni::consts::err::INVALID_DELEGATE_FUNC_PTR);
            CONST_OUT(omni::consts::err::INVALID_OPTION);
            CONST_OUT(omni::consts::err::INVALID_SETTING);
            CONST_OUT(omni::consts::err::INVALID_SEEK_DIR);
            CONST_OUT(omni::consts::err::INVALID_THREAD_HANDLE);
            CONST_OUT(omni::consts::err::INVALID_THREAD_PRIORITY);
            CONST_OUT(omni::consts::err::INVALID_THREAD_START_TYPE);
            CONST_OUT(omni::consts::err::INVALID_SIZE);
            CONST_OUT(omni::consts::err::PATH_NOT_ACCESSIBLE);
            CONST_OUT(omni::consts::err::SET_PRI_UNSUPPORTED);
            CONST_OUT(omni::consts::err::STRING_COUNT_GT0);
            CONST_OUT(omni::consts::err::STRING_INVALID_BINARY_FORMAT);
            CONST_OUT(omni::consts::err::STRING_INVALID_BINARY_STR_SZ);
            CONST_OUT(omni::consts::err::STRING_NOT_NUMERIC);
            CONST_OUT(omni::consts::err::SUCCESS);
            CONST_OUT(omni::consts::err::UNKNOWN);
            CONST_OUT(omni::consts::misc::COMMA);
            CONST_OUT(omni::consts::misc::MINUS);
            CONST_OUT(omni::consts::misc::NCHAR);
            CONST_OUT(omni::consts::misc::PERIOD);
            CONST_OUT(omni::consts::misc::PLUS);
            CONST_OUT(OMNI_NO_DELEGATE_STR);
            
            
            omni::sync::thread_priority tp = omni::sync::thread_priority::HIGHEST; CONST_OUT(tp);
            tp = omni::sync::thread_priority::IDLE; CONST_OUT(tp);
            tp = omni::sync::thread_priority::LOWEST; CONST_OUT(tp);
            tp = omni::sync::thread_priority::BELOW_NORMAL; CONST_OUT(tp); 
            tp = omni::sync::thread_priority::NORMAL; CONST_OUT(tp);
            tp = omni::sync::thread_priority::ABOVE_NORMAL; CONST_OUT(tp);
            tp = omni::sync::thread_priority::HIGHEST; CONST_OUT(tp);
            tp = omni::sync::thread_priority::REAL_TIME; CONST_OUT(tp);
            
            omni::sync::thread_start_type st = omni::sync::thread_start_type::USER; CONST_OUT(st);
            st = omni::sync::thread_start_type::NOW; CONST_OUT(st);
            
            omni::sync::thread_state ts = omni::sync::thread_state::UNSTARTED; CONST_OUT(ts);
            ts = omni::sync::thread_state::START_REQUESTED; CONST_OUT(ts);
            ts = omni::sync::thread_state::RUNNING; CONST_OUT(ts);
            ts = omni::sync::thread_state::COMPLETED; CONST_OUT(ts);
            ts = omni::sync::thread_state::STOP_REQUESTED; CONST_OUT(ts);
            ts = omni::sync::thread_state::STOPPED; CONST_OUT(ts);
            ts = omni::sync::thread_state::ABORT_REQUESTED; CONST_OUT(ts);
            ts = omni::sync::thread_state::ABORTED; CONST_OUT(ts);
            
            omni::sync::thread_option ot = omni::sync::thread_option::ALLOW_THREAD_REUSE; CONST_OUT(ot);
            ot = omni::sync::thread_option::AUTO_JOIN; CONST_OUT(ot);
            ot = omni::sync::thread_option::STACK_SIZE; CONST_OUT(ot);
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_MISC
