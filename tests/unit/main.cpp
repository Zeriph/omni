#if !defined(OMNI_NO_UT_MAIN)
#include <omnilib>
#include "tests.hpp"

#define print_fw_info() omni::out << "Omni C++ cross platform library (v" << OMNI_FW_VER_STR << ") unit test" << std::endl
#define invalid_unit(fval) omni::out << "Invalid unit specified: " << fval << std::endl
#define invalid_test(tval) omni::out << "Invalid test specified: " << tval.c_str() << std::endl
#define print_unit(i, itr) omni::out << ((i<9) ? "0" : "") << (i+1) << " - " << itr->name() << " - " << itr->description() << std::endl
#define print_test(t, uti) omni::out << ((t<9) ? "0" : "") << (t+1) << " - " << ((uti.name.size() != 0) ? uti.name : OMNI_STRW("null")) << " - " << ((uti.desc.size() != 0) ? uti.desc : OMNI_STRW("null")) << std::endl

omni::ut omni::ut::current_test;

void application_exit() { printv("exiting on signal ", omni::system::signal_str(omni::application::last_signal()).c_str()); }
void application_terminated() { printl("application termination requested"); }
void application_signal(int sig) { printv("signal received: ", omni::system::signal_str(sig).c_str()); }
void application_startup() { printl("unit_test: application_startup"); }
void application_shutdown() { printl("unit_test: application_shutdown"); }

void ut_run()
{
    if (omni::ut::current_test.funcptr) {
        omni::out << std::endl << "Start unit test: " << omni::ut::current_test.name << std::endl;
        omni::stopwatch sw;
        sw.start();
        omni::ut::current_test.funcptr();
        sw.stop();
        omni::out << std::endl << "Test complete, run time: " << sw << std::endl;
    } else {
        printl("Invalid test address, exiting");
        omni::application::exit();
    }
}

void print_usage()
{
    omni::out << "usage: [unit] [test][list]" << std::endl
              << "unit      The unit name/number to test. If [unit] is the only argument" << std::endl
              << "          on the command line, a list of tests for the unit will display" << std::endl
              << "test      The specific unit test name/number of the unit" << std::endl
              << "list      Lists the tests; if specified after [unit], will display" << std::endl
              << "          the tests associated with the specific [unit]" << std::endl;
}

void print_units()
{
    printl("Current units to test:");
    std::size_t idx = 0;
    unit_map::iterator itr = units.begin();
    for (; itr != units.end(); ++itr, ++idx) {
        print_unit(idx, itr->second);
    }
}

void print_tests(omni::ut_base* unit)
{
    printv("Current tests for unit: ", unit->name());
    test_map::const_iterator itr = unit->tests().begin();
    for (; itr != unit->tests().end(); ++itr) {
        print_test(itr->first, itr->second);
    }
}

void usage()
{
    print_usage();
    printl("");
    print_units();
}

omni::ut parse_args(const omni::application::argparser& args)
{
    if (args.argc() > 1) {
        if (args.contains("-?") || args.contains("help")) { print_usage(); }
        else if (args[1] == OMNI_STRW("list")) { print_units(); }
        else {
            omni::string_t fval = omni::string::util::to_string_t(args[1]);
            unit_map::const_iterator ufind = units.begin();
            if (omni::string::util::is_numeric(fval)) {
                std::size_t idx = omni::string::util::to_type<std::size_t>(fval);
                for (--idx; idx > 0; --idx, ++ufind) { }
            } else {
                ufind = units.find(fval);
            }
            if (ufind == units.end()) { invalid_unit(fval); print_units(); }
            else {
                if (args.argc() < 3 || args[2] == OMNI_STRW("list")) { print_tests(ufind->second); }
                else {
                    if (omni::string::util::is_numeric(args[2])) {
                        int idx = omni::string::type_cast<int>(args[2]);
                        test_map::const_iterator tfind = ufind->second->tests().find((idx - 1));
                        if (tfind != ufind->second->tests().end()) {
                            return tfind->second;
                        }
                    } else {
                        test_map::const_iterator tfind = ufind->second->tests().begin();
                        while (tfind != ufind->second->tests().end()) {
                            if (args[2] == tfind->second.name) {
                                return tfind->second;
                            }
                            ++tfind;
                        }
                    }
                    invalid_test(args[2]);
                    print_tests(ufind->second);
                }
            }
        }
    } else { print_usage(); }
    return omni::ut();
}

void init(int argc, const char** argv)
{
    print_fw_info();
    omni::application::terminate_handler::attach(&application_terminated);
    omni::application::exit_handler::attach(&application_exit);
    omni::application::startup_handler::attach(&application_startup);
    omni::application::shutdown_handler::attach(&application_shutdown);
    omni::application::signal_handler::attach(&application_signal);
    omni::application::set_args(argc, argv);
}

int main(int argc, const char* argv[])
{
    init(argc, argv);
    omni::ut::current_test = parse_args(omni::application::args());
    return (omni::ut::current_test.funcptr ? 
            omni::application::run(&ut_run) : 0);
}
#endif
