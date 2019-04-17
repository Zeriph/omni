#include <omnilib>

typedef omni_sequence_t<omni::string_t> list_t;

static std::string old_lic_cont;
static std::string new_lic_cont;
static omni::string_t out_dir;
static omni::string_t omni_dir;

static bool print_usage()
{
    omni::out << "USAGE:" << std::endl << 
        omni::application::args()[0] << std::endl <<
        " -old 'path'    old license file path" << std::endl <<
        " -new 'path'    new license file path" << std::endl <<
        " -omni 'path'   omni code directory" << std::endl <<
        " -out 'path'    output code directory" << std::endl;
    return false;
}

static bool parse_args()
{
    omni::application::argparser& args = omni::application::args();
    if (args.contains("-?") || args.contains("--help") || args.contains("-h")) {
        return print_usage();
    }
    std::string old_lic_file = omni::string::util::to_string(args["-old"]);
    std::string new_lic_file = omni::string::util::to_string(args["-new"]);
    omni_dir = args["-omni"];
    out_dir = args["-out"];
    if (!omni::io::file::exists(old_lic_file) || !omni::io::file::exists(new_lic_file)) {
        omni::out << "Both license files must be specified and exists." << std::endl;
        return false;
    }
    if (!omni::io::directory::exists(omni_dir)) {
        omni::out << "Omni directory does not exists: " << omni_dir << std::endl;
        return false;
    }
    if (!out_dir.empty() && !omni::io::directory::exists(out_dir)) {
        omni::out << "Creating directory '" << out_dir << "' ...";
        if (!omni::io::directory::create(out_dir)) {
            omni::out << "failed." << std::endl;
            return false;
        }
        omni::out << "done." << std::endl;
    }
    old_lic_cont = omni::io::file::get_contents(old_lic_file);
    new_lic_cont = omni::io::file::get_contents(new_lic_file);
    if (old_lic_cont.empty() || new_lic_cont.empty()) {
        omni::out << "License contents must not be empty." << std::endl;
        return false;
    }
    return true;
}

static void app_main()
{
    if (parse_args()) {
        list_t files = omni::io::directory::get_all_files(omni_dir);
        omni::out << "Found " << files.size() << " files." << std::endl;
        std::string contents, fname;
        bool to_stdout = out_dir.empty();
        for (list_t::iterator file = files.begin(); file != files.end(); ++file) {
            contents  = omni::io::file::get_contents(*file);
            fname = omni::io::path::combine(out_dir, (*file).substr(omni_dir.length()));
            if ((contents.length() <= old_lic_cont.length()) ||
                (contents.substr(0, old_lic_cont.length()) != old_lic_cont))
            {
                omni::out << "Copying non-licensed file: " << *file << std::endl;
                uint64_t w = omni::io::file::write(fname, contents);
                continue;
            }
            contents = new_lic_cont + contents.substr(old_lic_cont.length());
            if (!omni::io::directory::create(omni::io::path::get_parent_name(fname), true)) {
                omni::out << "Could not create directory: " << omni::io::path::get_parent_name(fname) << std::endl;
                continue;
            }
            omni::out << fname << ": ";
            if (to_stdout) {
                omni::out << std::endl << contents;
            } else {
                uint64_t w = omni::io::file::write(fname, contents);
                if (w == contents.length()) {
                    omni::out << "SUCCESS!";
                } else {
                    omni::out << "FAILURE, wrote " << w << " bytes, expected " << contents.length();
                }
            }
            omni::out << std::endl;
        }
    }
}

int main(int argc, const char* argv[])
{
    return omni::application::run(argc, argv, &app_main, true);
}
