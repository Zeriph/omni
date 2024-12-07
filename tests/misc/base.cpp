#include <omnilib>
#include <vector>

#define printl(v) std::cout << v << std::endl
#define tp(fmt, val, exp) std::cout << fmt << " = " << val << " | exp: " << exp << std::endl

int main(int argc, const char* argv[])
{
    /*
    OMNI_CONSTEXT_FW const double  TICKS_PER_NANOSECOND OMNI_EXT_ASSN_FW(0.01);
    OMNI_CONSTEXT_FW const int64_t TICKS_PER_MICROSECOND OMNI_EXT_ASSN_FW(10);
    OMNI_CONSTEXT_FW const int64_t TICKS_PER_MILLISECOND OMNI_EXT_ASSN_FW(10000);
    OMNI_CONSTEXT_FW const int64_t TICKS_PER_TENTH_SECOND OMNI_EXT_ASSN_FW(1000000); // TICKS_PER_MILLISECOND * 100);
    OMNI_CONSTEXT_FW const int64_t TICKS_PER_SECOND OMNI_EXT_ASSN_FW(10000000);
    OMNI_CONSTEXT_FW const int64_t TICKS_PER_MINUTE OMNI_EXT_ASSN_FW(600000000);
    OMNI_CONSTEXT_FW const int64_t TICKS_PER_HOUR OMNI_EXT_ASSN_FW(36000000000);
    OMNI_CONSTEXT_FW const int64_t TICKS_PER_DAY OMNI_EXT_ASSN_FW(864000000000);
    
    t = ticks
    span_t d = static_cast<span_t>(std::abs(static_cast<double>(t)) / omni::chrono::TICKS_PER_DAY);
    span_t h = static_cast<span_t>(std::abs(static_cast<double>(t)) / omni::chrono::TICKS_PER_HOUR) % 24;
    span_t m = static_cast<span_t>(std::abs(static_cast<double>(t)) / omni::chrono::TICKS_PER_MINUTE) % 60;
    span_t s = static_cast<span_t>(std::abs(static_cast<double>(t)) / omni::chrono::TICKS_PER_SECOND) % 60;
    span_t ms = static_cast<span_t>(std::abs(static_cast<double>(t)) / omni::chrono::TICKS_PER_MILLISECOND) % 1000;
    // d.hh:mm:ss.ms
    if (t < 0) { ss << "-"; }
    ss << d << ".";
    if (h < 10) { ss << "0"; }
    ss << h << ":";
    if (m < 10) { ss << "0"; }
    ss << m << ":";
    if (s < 10) { ss << "0"; }
    ss << s << "." << ms;



    
    */
    int64_t ticks = 1000000;
    omni::chrono::uspan_t s1(ticks);
    omni::chrono::span_t s2(-ticks);
    omni::chrono::uspan_t s3(365, 24, 60, 60, 1001);
    omni::chrono::span_t s4(3, 3, 3);

    printl("ticks = " << ticks);
    printl("-ticks = " << (-ticks));

    printl("d.hh:mm:ss.ms");
    tp("s1(1000000)", s1, "0.00:00:00.100");
    tp("s2(-1000000)", s2, "-0.00:00:00.100");
    tp("s3(365, 24, 60, 60, 1001)", s3, "366.01:01:01.01");
    tp("s4(3, 3, 3)", s4, "0.03:03:03.00");

    return 0;
}
