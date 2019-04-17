#if !defined(OMNI_UT_TESTS)
#define OMNI_UT_TESTS

#if defined(OMNI_UT_ALL) || defined(OMNI_UT_FULL)
    #if defined(OMNI_UT_ALL) && defined(OMNI_UT_FULL)
        #error Cannot specify to test all and full
    #endif
    #include "units/all.hpp"
    #include "units/full.hpp"
    #define OMNI_UTUA // use all tests
#endif

// test includes
#include "units/application.hpp"
#include "units/argparser.hpp"
#include "units/basic_lock.hpp"
#include "units/basic_thread.hpp"
#include "units/binary_semaphore.hpp"
#include "units/bits.hpp"
#include "units/chrono.hpp"
#include "units/color.hpp"
#include "units/conditional.hpp"
#include "units/datetime.hpp"
#include "units/delegate.hpp"
#include "units/environment.hpp"
#include "units/exceptions.hpp"
#include "units/geometry.hpp"
#include "units/io.hpp"
// #include "units/fswatcher.hpp" // incomplete
#include "units/generic_ptr.hpp"
#include "units/math.hpp"
#include "units/misc.hpp"
#include "units/mutex.hpp"
#include "units/object.hpp"
#include "units/property.hpp"
#include "units/runnable.hpp"
#include "units/semaphore.hpp"
#include "units/smart_ptr.hpp"
// #include "units/socket.hpp" // incomplete
// #include "units/tcp.hpp" // incomplete
// #include "units/udp.hpp" // incomplete
#include "units/spin.hpp"
#include "units/stopwatch.hpp"
#include "units/string.hpp"
#include "units/system.hpp"
#include "units/timer.hpp"
#include "units/timespan.hpp"
#include "units/thread.hpp"
#include "units/threadpool.hpp"
#include "units/version.hpp"

#if defined(OMNI_UTUA)
    #undef OMNI_UTUA
#endif

#endif // OMNI_UT_TESTS
