#include "docugen.hpp"
#include "inc/Program.hpp"

#define read_line(v) std::getline(std::cin, v);

static List<OmniDocuGen::MacroOp> _checkedMacros;
static List<OmniDocuGen::CodeGen::ptr_t> _checkedFiles;
static List<OmniDocuGen::MemberTypeInformation::ptr_t> _checkedMembers;
static List<OmniDocuGen::FrameworkExample> _checkExamples;

class UtInfo {
    public:
        UtInfo() : Name(), RootNS(), IsNS(false), Empty(true), Member() {}
        UtInfo(const UtInfo& cp) : Name(cp.Name), RootNS(cp.RootNS), IsNS(cp.IsNS), Empty(cp.Empty), Member(cp.Member) {}
        explicit UtInfo(const std::string& nm) : Name(nm), RootNS(), IsNS(false), Empty(false), Member() {}
        UtInfo(const std::string& nm, OmniDocuGen::MemberTypeInformation::ptr_t& mti) : Name(nm), RootNS(), IsNS(false), Empty(false), Member(mti) {}
        UtInfo(const std::string& nm, const std::string& rns) : Name(nm), RootNS(rns), IsNS(false), Empty(false), Member() {}
        UtInfo(const std::string& nm, const std::string& rns, OmniDocuGen::MemberTypeInformation::ptr_t& mti) : Name(nm), RootNS(rns), IsNS(false), Empty(false), Member(mti) {}
        UtInfo(const std::string& nm, const std::string& rns, bool isns) : Name(nm), RootNS(rns), IsNS(isns), Empty(false), Member() {}
        UtInfo(const std::string& nm, const std::string& rns, bool isns, OmniDocuGen::MemberTypeInformation::ptr_t& mti) :
            Name(nm), RootNS(rns), IsNS(isns), Empty(false), Member(mti)
        {
            if (mti->Parent->CodeType == OmniDocuGen::Types::CodeStructureType::Namespace) {
                this->RootNS = mti->Parent->Name;
            }
        }
        ~UtInfo() {}

        UtInfo& operator=(const UtInfo& cp)
        {
            this->Name = cp.Name;
            this->RootNS = cp.RootNS;
            this->IsNS = cp.IsNS;
            this->Empty = cp.Empty;
            this->Member = cp.Member;
            return *this;
        }

        std::string Name;
        std::string RootNS;
        bool IsNS;
        bool Empty;
        OmniDocuGen::MemberTypeInformation::ptr_t Member;
};

static void FullUsage()
{
    pl(
        "MODE: -full -> Runs the full build sequence based on specified options." << std::endl <<
        "OPTIONS:" << std::endl <<
            "-maxmacrothreads   Max number of macro threads" << std::endl <<
            "-maxmtithreads     Max number of MTI threads" << std::endl <<
            "-maxsyntaxthreads  Max number of syntax threads" << std::endl <<
            "-maxpool           Max number of thread pool threads" << std::endl <<
            "" << std::endl <<
            "Build/generation options:" << std::endl <<
            "-doclasses     Sepcifies to generate all class help (docs/classes/*.html)" << std::endl <<
            "-doclassindex  Sepcifies to generate docs/classes/index.html" << std::endl <<
            "-dosyntax      Sepcifies to generate docs/htmlsrc/*.html (syntax highlighting)" << std::endl <<
            "-doexamples    Sepcifies to generate the library examples (docs/examples/*)" << std::endl <<
            "-domacros      Sepcifies to generate docs/options/*.html (macro/options help)" << std::endl <<
            "-doapi         Sepcifies to generate docs/api.html" << std::endl <<
            "-dofilesview   Sepcifies to generate files/index.html (shows the source)" << std::endl <<
            "-dobuild       Sepcifies to generate the build scripts and solution files" << std::endl <<
            "-dohash        Sepcifies to generate the hashes for the zip files generated" << std::endl <<
            "-dojs          Sepcifies to generate the JavaScript search.js file" << std::endl <<
            "" << std::endl <<
            "-doall         Perform all of the above generation and build actions" << std::endl <<
            "" << std::endl <<
            "The following options cannot be combined with all of the above options:" << std::endl <<
            "-src           Sepcifies library source file(s) to use as input for generation" << std::endl <<
            "               of HTML syntax highlighted files (docs/htmlsrc/*.cpp.html)" << std::endl <<
            "               (can be specified multiple times for multiple inputs)" << std::endl <<
            "-mac           Sepcifies macro(s) to use as input for generation" << std::endl <<
            "               of the OMNI_MACRO option html with linked references" << std::endl <<
            "               (can be specified multiple times for multiple inputs)" << std::endl <<
            "-mti           Sepcifies an Omni class member full path to use as input for" << std::endl <<
            "               generation of that class members MTI html file, for example:" << std::endl <<
            "               'omni::application::signal_handler::attach' will generate the" << std::endl <<
            "               class help file omni-application-signal_handler-attach.html" << std::endl <<
            "               (can be specified multiple times for multiple inputs)" << std::endl <<
            "-ex            Sepcifies an Omni example directory name to use as input for" << std::endl <<
            "               example html generation." << std::endl <<
            "               (can be specified multiple times for multiple inputs)" << std::endl <<
            "" << std::endl <<
            "If you specify -src, -mac, or -mti, you can only specify -doclassindex, -doapi," << std::endl <<
            " -dofilesview, -dobuild, -dohash, and -dojs." << std::endl <<
            "" << std::endl
    );
}

static void Usage()
{
    pl("Omni Code Document Parser/Generator" << std::endl);
    pl("USAGE:" << std::endl << 
        omni::application::args()[0] << " (-settings [file]) [mode] (mode options)" << std::endl <<
            "-settings [file]       If this flag and file are specified, the specified file" << std::endl <<
            "                       will be used over the default settings file." << std::endl <<
            "                       NOTE: you can override any of the settings in the loaded" << std::endl <<
            "                       file by passing settings tag name as a command line option." << std::endl <<
            "                       (e.g. -SourceDirectory \"/code/source/omni\")" << std::endl <<
            "-singlethread          If this flag is enabled, the program will run in single" << std::endl <<
            "                       threaded mode for modes that generate member info." << std::endl <<
            "-profile               If this flag is enabled, the program will run in profile" << std::endl <<
            "                       mode which does not write any files to the disk." << std::endl <<
            "-tree                  Specifies to output the text tree of the nodes." << std::endl <<
            "                       This mode is only valid for parser and normal modes." << std::endl <<
            "-v                     Each time this flag is specified will increase the" << std::endl <<
            "                       verbosity of the output." << std::endl <<
            "-silent                Surpress normal status update output no matter the verbosity." << std::endl <<
            "-debug                 Specifying this will increase the verbosity to the max." << std::endl <<
            "" << std::endl <<
        "[mode] is one of the following:" << std::endl <<
            "-full      Specifies running the full parser/generator." << std::endl <<
            "-parser    Specifies running the Omni class parser." << std::endl <<
            "-ut        Specifies running the Omni unit test class parser/creator." << std::endl <<
            "-macro     Specifies running the Omni macro editor." << std::endl <<
            "-api       Specifies running the Omni system API editor." << std::endl <<
            "-html      Specifies running the code syntax HTML highlighter with optional Omni" << std::endl <<
            "           references." << std::endl <<
            "-lic       Specifies running the license replacer." << std::endl <<
            "" << std::endl <<
            "The following are the mode options, or flags, that can be specified with each" << std::endl <<
            "mode specified on the command line; pay attention as each mode has specific" << std::endl <<
            "flags and additional options to specify and utilize." << std::endl <<
            "" << std::endl);
    FullUsage();
    pl(
        "MODE: -parser -> Runs the class parser only." << std::endl <<
        "OPTIONS:" << std::endl <<
            "-in [file]     Specifies the specific Omni file to read and parse, otherwise" << std::endl <<
            "               the entire library will be parsed." << std::endl <<
            "-mti [path]    View the member type information for the full path specified." << std::endl <<
            "               The full path is the full namespace path, e.g. omni::event" << std::endl <<
            "" << std::endl <<
        "MODE: -ut -> Runs the unit test class parser/creator." << std::endl <<
        "OPTIONS:" << std::endl <<
            "-in [file]     Specifies the specific Omni file to read and parse, otherwise" << std::endl <<
            "               the entire library will be parsed." << std::endl <<
            "-mti [path]    View the member type information for the full path specified." << std::endl <<
            "               The full path is the full namespace path, e.g. omni::event" << std::endl <<
            "-noinfo        If specified, the info_test function will not be generated." << std::endl <<
            "-new           Enables 'create' mode in which you can create or overwrite unit tests." << std::endl <<
            "-spilt         If -new is specified, this will put each class/struct in a different" << std::endl <<
            "               unit test file instead of splitting into unit test functions within" << std::endl <<
            "               the same unit test file." << std::endl <<
            "-overwrite     If -new is specified, this will overwrite the unit test if that" << std::endl <<
            "               test already exists." << std::endl <<
            "-name [name]   If -new is specified, this flag specifies the unit test name to use for UT_NAME." << std::endl <<
            "               This overrides the auto-discovered value for the unit test." << std::endl <<
            "               Note: This value is not valid with the -spilt flag." << std::endl <<
            "-desc [data]   If -new is specified, this flag will specify a test description" << std::endl <<
            "               for the UT_DESC macro in the unit test header." << std::endl <<
            "-rootns [ns]   If -new is specified, this flag specifies the root namespace to use for UT_ROOT_NS." << std::endl <<
            "               This overrides the auto-discovered value for the root namespace." << std::endl <<
            "               Note: This value is not valid with the -spilt flag." << std::endl <<
            "-isns          If -new is specified, this flag specifies this unit test is a namespace" << std::endl <<
            "               (Sets UT_ISNS to true). This overrides the auto-discovered value for the unit test." << std::endl <<
            "               Note: This value is not valid with the -spilt flag." << std::endl <<
            "-print         If -new is specified, this will output the unit test file to the console" << std::endl <<
            "               instead of the actual unit test output file. Note: -overwrite is ignored." << std::endl <<
            "-comment       If -new is specified, this will enclose the output within the 'base_test'" << std::endl <<
            "               in a multi-line comment block. This can be used in conjuction with the" << std::endl <<
            "               -print option. Note: -overwrite is ignored." << std::endl <<
            "" << std::endl <<
            "NOTE: the unit test parser/creator is simplistic in its generation of the unit tests." << std::endl <<
            "It is intended to speed up creation of unit test files and the code generated is not" << std::endl <<
            "fully compilable without slight modification. Enabling the -comment flag will comment" << std::endl <<
            "out the block of code to make the test file compilable." << std::endl <<
            "" << std::endl <<
        "MODE: -macro -> Create and view OMNI_ macro options" << std::endl <<
        "OPTIONS:" << std::endl <<
            "-scan          This options lets you scan the Omni source for new and old macros" << std::endl <<
            "               and choose what to do with them afterwards, like exporting the" << std::endl <<
            "               new macros found, or removing any of the old/stale macros that" << std::endl <<
            "               are no longer referenced in the source, but still have XML files." << std::endl <<
            "               This option does not have any additional flags, so specifying any" << std::endl <<
            "               other flags, like -new, -overwrite, or -name will be ignored." << std::endl <<
            "-new           Enables 'create' mode in which you can create or overwrite macros." << std::endl <<
            "-overwrite     If -new is specified, this will overwrite the macro file if that" << std::endl <<
            "               macro already exists." << std::endl <<
            "-name [name]   If -new is _not_ enabled, this will specify to display the name" << std::endl <<
            "               of the macro in view mode." << std::endl <<
            "               If -new _is_ enabled, this will specify the name of the macro to" << std::endl <<
            "               create or edit (if -overwrite is enabled)." << std::endl <<
            "-brief [txt]   If -new is _not_ enabled, this will specify to display the @brief" << std::endl <<
            "               of the macro in view mode." << std::endl <<
            "               If -new _is_ enabled, this will specify the @brief of the macro" << std::endl <<
            "               being created or edited (if -overwrite is enabled)." << std::endl <<
            "-is_helper [true/false]" << std::endl <<
            "               If -new _is_ enabled, this will specify the IsHelper of the macro" << std::endl <<
            "               being created or edited (if -overwrite is enabled)." << std::endl <<
            "-is_constant [true/false]" << std::endl <<
            "               If -new _is_ enabled, this will specify the IsConstant of the" << std::endl <<
            "               macro being created or edited (if -overwrite is enabled)." << std::endl <<
            "-is_fwhelp [true/false]" << std::endl <<
            "               If -new _is_ enabled, this will specify the IsFWHelp of the macro" << std::endl <<
            "               being created or edited (if -overwrite is enabled)." << std::endl <<
            "-noask         If specified will use the default values for any new macro's" << std::endl <<
            "               where any command line arguments are not specifed." << std::endl <<
            "-details       If -new is _not_ enabled, this will specify to display the longer" << std::endl <<
            "               details of each macro options (can include lots of code)." << std::endl <<
            "-extra         If -new is _not_ enabled, this will specify to display the extra" << std::endl <<
            "               info of the macro option (like if it's a helper, etc.)." << std::endl <<
            "" << std::endl <<
        "MODE: -api -> Create and view system API's used by Omni" << std::endl <<
        "OPTIONS:" << std::endl <<
            "-new           Enables 'create' mode in which you can create or overwrite API's" << std::endl <<
            "-overwrite     If -new is specified, this will overwrite the api file if that" << std::endl <<
            "               api already exists." << std::endl <<
            "-name [name]   If -new is _not_ enabled, this will display the file name" << std::endl <<
            "               of the API in view mode; the parameter is ignored." << std::endl <<
            "               If -new _is_ enabled, this will specify the name of the api to" << std::endl <<
            "               create or edit (if -overwrite is enabled)." << std::endl <<
            "-link [www]    If -new is _not_ enabled, this will specify to display the link" << std::endl <<
            "               of the API in view mode; the parameter is ignored." << std::endl <<
            "               If -new _is_ enabled, this will specify the link of the api to" << std::endl <<
            "               create or edit (if -overwrite is enabled)." << std::endl <<
            "-type [type]   If -new _is_ enabled, this will specify the type of the api to" << std::endl <<
            "               create or edit (if -overwrite is enabled)." << std::endl <<
            "               The type specified must be one of the following:" << std::endl <<
            "               'Windows', 'Apple', 'Linux', 'Unix', 'POSIX', or 'STD'" << std::endl <<
            "-sort          Specifies to sort by type instead of by name when viewing the API's." << std::endl <<
            "-scan          Specifies scanning for system API's not already accounted for." << std::endl <<
            "" << std::endl <<
        "MODE: -html -> HTML syntax highlighter" << std::endl <<
        "OPTIONS:" << std::endl <<
            "-inchref [.]   Specifies the relative path of the 'include' HTML path for use" << std::endl <<
            "               when creating a deeper nested HTML example/code file, example:" << std::endl <<
            "               -inchref \"../../\"" << std::endl <<
            "-dochref [.]   Specifies the relative path of the 'docugen' HTML path for use" << std::endl <<
            "               when creating a deeper nested HTML example/code file, example:" << std::endl <<
            "               -dochref \"../../\"" << std::endl <<
            "-css           Enabling this flag will generate the CSS style tags needed in the" << std::endl <<
            "               HTML, otherwise it is assumed the HTML generated will be placed" << std::endl <<
            "               relative to the content/main.css." << std::endl <<
            "-checkbox      Enabling this flag to include the 'show/hide example' input"  << std::endl <<
            "               checkbox, label and relevent CSS (if -css is specified)" << std::endl <<
            "-genclasses    Enabling this flag will generate the class tree and highlight all" << std::endl <<
            "               Omni library classes, SysAPI's and MacroOp's." << std::endl <<
            "-in [file]     Specifies the file to read and highlight, otherwise text will be" << std::endl <<
            "               read from the console via stdin." << std::endl <<
            "-out [file]    Specifies the file to write the highlighted text to, otherwise" << std::endl <<
            "               the output will be written to stdout." << std::endl <<
            "" << std::endl <<
        "MODE: -lic -> License replacer mode" << std::endl <<
        "OPTIONS:" << std::endl <<
            "-stdout        Specifies that the code should be written to stdout and not" << std::endl <<
            "               the file." << std::endl <<
            "-out [path]    Specifies the output directory to copy the new files to. If not" << std::endl <<
            "               specified, then the TempZipDirectory settings path is used." << std::endl <<
            "-old [file]    Specifies the old license file containing the old license to" << std::endl <<
            "               remove. If not specified, the LicenseFile settings value is used." << std::endl <<
            "-new [file]    Specifies the new license file containing the new license to add." << std::endl <<
            "-replace       Specifies to replace the old license file with the new file" << std::endl <<
            "               after replacing the license in the source." << std::endl <<
            "" << std::endl
    );
}

static std::string _GetMtiName(OmniDocuGen::MemberTypeInformation::ptr_t& mti)
{
    std::string ret;
    if (mti->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Public) {
        if (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Namespace) {
            foreach (OmniDocuGen::MemberTypeInformation::ptr_t, member, mti->Members) {
                std::string tmp = _GetMtiName(*member);
                if (!tmp.empty()) {
                    if (ret.empty()) {
                        ret += tmp;
                    } else {
                        ret += " and " + tmp;
                    }
                }
            }
            if (ret.empty()) {
                ret = mti->FullPath;
            }
        } else {
            if ((mti->CodeType == OmniDocuGen::Types::CodeStructureType::Class) ||
                (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Struct))
            {
                ret = mti->FullPath;
            }
        }
    }
    return ret;
}

static List<UtInfo> _GetMtiUnitName(OmniDocuGen::MemberTypeInformation::ptr_t& mti)
{
    List<UtInfo> ret;
    if (mti->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Public) {
        if (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Namespace) {
            foreach (OmniDocuGen::MemberTypeInformation::ptr_t, member, mti->Members) {
                List<UtInfo> tmp = _GetMtiUnitName(*member);
                foreach (UtInfo, ut, tmp) {
                    ret.push_back(*ut);
                }
            }
            if (ret.size() == 0) {
                ret.push_back(UtInfo(mti->Name, "", true, mti));
            }
        } else {
            if ((mti->CodeType == OmniDocuGen::Types::CodeStructureType::Class) ||
                (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Struct))
            {
                if (mti->Parent->CodeType == OmniDocuGen::Types::CodeStructureType::Namespace) {
                    ret.push_back(UtInfo(mti->Name, mti->Parent->Name, mti));
                } else {
                    ret.push_back(UtInfo(mti->Name, mti));
                }
            }
        }
    }
    return ret;
}

static std::string _GetVariableName(OmniDocuGen::ParameterInformation::ptr_t p)
{
    std::string ret = omni::string::replace(p->ParamType, "const ", "");
    ret = omni::string::replace(ret, "&", "");
    ret = omni::string::replace(ret, ">", "");
    ret = omni::string::replace(ret, "<", "");
    ret = omni::string::replace_all(ret, "::", "_");
    ret = omni::string::replace_all(ret, ",", "");
    ret = omni::string::replace_all(ret, " ", "");
    ret = omni::string::replace(ret, "omni_", "");

    return ret + "_" + p->Name;
}

static std::string _GetTemplate(const std::string& tp)
{
    std::string ret = omni::string::replace(tp, "template ", "");
    ret = omni::string::replace(ret, "<", "");
    ret = omni::string::replace(ret, ">", "");
    ret = omni::string::replace_all(ret, "class ", "");
    ret = omni::string::replace_all(ret, "typename ", "");
    ret = omni::string::replace_all(ret, "std::size_t ", "");
    ret = omni::string::replace_all(ret, "size_t ", "");
    ret = omni::string::replace_all(ret, " ", "");
    ret = omni::string::replace_all(ret, "[", "");
    ret = omni::string::replace_all(ret, "]", "");
    return "<" + omni::string::trim(ret) + ">";
}

static std::string _PrintMemberInfo(OmniDocuGen::MemberTypeInformation::ptr_t& mti)
{
    if (
        (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Dtor) ||
        (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Typedef) ||
        (mti->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Private) ||
        (mti->Name == "hash") || (mti->Name == "name") || (mti->Name == "type") || (mti->Name == "disposing") ||
        (omni::string::contains(mti->Signature, "friend std::ostream") || omni::string::contains(mti->Signature, "friend std::wostream"))
    )
    { return ""; }

    std::string rv = omni::string::trim(omni::string::replace(mti->Signature, mti->ReturnType, ""));
    std::string parms, tmp, ret;
    std::string sig = "// " + mti->Name + " ~~ " + mti->Signature + "\n";

    if (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Ctor) {
        ret = sig;
        if (mti->IsOverloaded()) {
            foreach (OmniDocuGen::MemberTypeInformation::ptr_t, oload, mti->Overloads) {
                if ((*oload)->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Private) { continue; }
                ret += "// " + (*oload)->Name + " ~~ " + (*oload)->Signature + "\n";
            }
        }
        return ret + "\n";
    }

    if ((mti->Parent) && (!mti->IsStatic) && (
        (mti->Parent->CodeType == OmniDocuGen::Types::CodeStructureType::Class) ||
        (mti->Parent->CodeType == OmniDocuGen::Types::CodeStructureType::Struct)))
    {
        switch (mti->CodeType) {
            case OmniDocuGen::Types::CodeStructureType::Operator:
                tmp = omni::string::trim(
                    omni::string::replace(mti->Name, "operator", "") // get the operator name
                );
                if (!omni::char_util::is_alpha(tmp[0])) {
                    /*
                        It's likely a binary/arith operator, e.g.

                        +    -    *    /    =    <    >    +=   -=   *=   /=   <<   >>
                        <<=  >>=  ==   !=   <=   >=   ++   --   %    &    ^    !    |
                        ~    &=   ^=   |=   &&   ||   %=   []

                        operator!=
                        operator+
                        operator+=
                        operator-
                    */
                    if ((tmp == "--") || (tmp == "++")) {
                        if (mti->Parameters.size() > 0) {
                            rv = "(" + tmp + "temp_val)";
                        } else {
                            rv = "(temp_val" + tmp + ")";
                        }
                    } else {
                        if (mti->Parameters.size() > 0) {
                            rv = "(temp_val " + tmp + " " + _GetVariableName(mti->Parameters[0]) + ")";
                        } else {
                            // this shouldn't happen
                            rv = "(temp_val " + tmp + " " + mti->Parent->FullPath + ")";
                        }
                    }
                } else {
                    /*
                        It's likely a type operator:

                        operator omni::math::dimensional
                        operator std::string
                        operator std::wstring
                    */
                    if (mti->ReturnType != "bool") {
                        rv = "(static_cast< " + tmp + " >(temp_val))";
                    } else {
                        // this shouldn't happen
                        rv = "(temp_val " + tmp + " " + mti->Parent->FullPath + ")";
                    }
                }
                break;
            default:
                rv = "temp_val." + mti->Name;
                break;
        }
    } else if (mti->IsStatic) {
        if (mti->IsTemplated()) {
            rv = mti->FullPath + _GetTemplate(mti->Template);
        } else {
            if ((mti->Parent) && (mti->Parent->IsTemplated())) {
                rv = mti->Parent->FullPath + _GetTemplate(mti->Parent->Template) +
                     omni::string::replace(mti->FullPath, mti->Parent->FullPath, "");
            } else {
                rv = mti->FullPath;
            }
        }
    }
    if ((mti->Parameters.size() > 0) && (mti->CodeType != OmniDocuGen::Types::CodeStructureType::Operator)) {
        foreach (OmniDocuGen::ParameterInformation::ptr_t, p, mti->Parameters) {
            parms += _GetVariableName(*p);
            if ((p+1) != mti->Parameters.end()) {
                parms += ", ";
            }
        }
    }
    if ((mti->CodeType != OmniDocuGen::Types::CodeStructureType::Member) &&
        (mti->CodeType != OmniDocuGen::Types::CodeStructureType::Operator))
    {
        rv += "(" + parms + ")";
    }
    rv = omni::string::trim(omni::string::replace(omni::string::replace(rv, "inline ", ""), "static ", ""));
    
    ret = "";
    if (mti->ReturnType == "void") {
        ret = rv + ";\ntest(\"" + rv + "\", temp_val, \"?\");\n\n";
    } else if (mti->ReturnType == "bool") {
        ret = "test(\"" + rv + "\", (" + rv + " ? \"true\" : \"false\"), \"?\");\n\n";
    } else {
        ret = "test(\"" + rv + "\", " + rv + ", \"?\");\n\n";
    }

    if (mti->IsOverloaded()) {
        ret = sig + ret;
        foreach (OmniDocuGen::MemberTypeInformation::ptr_t, oload, mti->Overloads) {
            if ((*oload)->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Private) { continue; }
            if ((*oload)->IsStatic) { continue; }
            ret += _PrintMemberInfo(*oload);
        }
    } else {
        ret = sig + ret;
    }
    return ret;
}

static std::string _PrintMtiStaticInfo(OmniDocuGen::MemberTypeInformation::ptr_t& mti)
{
    std::string ret;
    if (mti->IsOverloaded()) {
        if (mti->IsStatic) {
            ret += _PrintMemberInfo(mti);
        }
        foreach (OmniDocuGen::MemberTypeInformation::ptr_t, oload, mti->Overloads) {
            if ((*oload)->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Private) { continue; }
            if ((*oload)->IsStatic) {
                ret += _PrintMemberInfo(*oload);
            }
        }
    } else {
        foreach (OmniDocuGen::MemberTypeInformation::ptr_t, mem, mti->Members) {
            if ((*mem)->IsStatic) {
                ret += _PrintMemberInfo(*mem);
            } else {
                ret += _PrintMtiStaticInfo(*mem);
            }
        }
    }
    return ret;
}

static std::string _PrintMtiTestSignatureInfo(OmniDocuGen::MemberTypeInformation::ptr_t& mti)
{
    std::string ret;
    if (mti->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Public) {
        if (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Namespace) {
            foreach (OmniDocuGen::MemberTypeInformation::ptr_t, member, mti->Members) {
                if ((*member)->IsStatic) { continue; }
                ret += _PrintMtiTestSignatureInfo(*member);
            }
            ret += _PrintMtiStaticInfo(mti);
        } else {
            if ((mti->CodeType == OmniDocuGen::Types::CodeStructureType::Class) ||
                (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Struct))
            {
                ret = "";// mti->FullPath + " temp_val;\n\n";
                foreach (OmniDocuGen::MemberTypeInformation::ptr_t, member, mti->Members) {
                    if ((*member)->IsStatic) { continue; }
                    ret += _PrintMemberInfo(*member);
                }
                ret += _PrintMtiStaticInfo(mti);
            } else {
                ret = _PrintMemberInfo(mti);
            }
        }
    }
    return ret + "\n";
}

static List<std::string> _GetMemberParams(OmniDocuGen::MemberTypeInformation::ptr_t& mti)
{
    List<std::string> ret;
    if (
        (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Ctor) ||
        (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Dtor) ||
        (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Typedef) ||
        (mti->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Private) ||
        (mti->Name == "hash") || (mti->Name == "name") || (mti->Name == "type") || (mti->Name == "disposing") ||
        (omni::string::contains(mti->Signature, "friend std::ostream") || omni::string::contains(mti->Signature, "friend std::wostream"))
    )
    { return ret; }

    if ((mti->CodeType == OmniDocuGen::Types::CodeStructureType::Operator) &&
        (mti->Parameters.size() > 0) &&
        ((mti->Name == "operator--") || (mti->Name == "operator++")))
    {
        // ignore operator--(int dummy) and operator++(int dummy)
    } else {
        std::string tmp;
        foreach (OmniDocuGen::ParameterInformation::ptr_t, p, mti->Parameters) {
            tmp = omni::string::replace((*p)->ParamType, "const ", "");
            tmp = omni::string::trim(omni::string::replace_all(tmp, "&", ""));
            tmp = tmp + " " + _GetVariableName(*p);
            ret.push_back(tmp);
        }
    }
    
    if (mti->IsOverloaded()) {
        foreach (OmniDocuGen::MemberTypeInformation::ptr_t, oload, mti->Overloads) {
            if ((*oload)->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Private) { continue; }
            if ((*oload)->IsStatic) { continue; }
            List<std::string> tmp2 = _GetMemberParams(*oload);
            foreach (std::string, tval, tmp2) {
                ret.push_back(*tval);
            }
        }
    }
    return ret;
}

static List<std::string> _GetParamStaticInfo(OmniDocuGen::MemberTypeInformation::ptr_t& mti)
{
    List<std::string> ret;
    if (mti->IsOverloaded()) {
        if (mti->IsStatic) {
            List<std::string> tmp = _GetMemberParams(mti);
            foreach (std::string, tval, tmp) {
                ret.push_back(*tval);
            }
        }
        foreach (OmniDocuGen::MemberTypeInformation::ptr_t, oload, mti->Overloads) {
            if ((*oload)->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Private) { continue; }
            if ((*oload)->IsStatic) {
                List<std::string> tmp = _GetMemberParams(*oload);
                foreach (std::string, tval, tmp) {
                    ret.push_back(*tval);
                }
            }
        }
    } else {
        foreach (OmniDocuGen::MemberTypeInformation::ptr_t, mem, mti->Members) {
            if ((*mem)->IsStatic) {
                List<std::string> tmp = _GetMemberParams(*mem);
                foreach (std::string, tval, tmp) {
                    ret.push_back(*tval);
                }
            } else {
                List<std::string> tmp = _GetParamStaticInfo(*mem);
                foreach (std::string, tval, tmp) {
                    ret.push_back(*tval);
                }
            }
        }
    }
    return ret;
}

static List<std::string> _GetMtiList(OmniDocuGen::MemberTypeInformation::ptr_t& mti)
{
    List<std::string> ret;
    if (mti->ScopeAccessType == OmniDocuGen::Types::CodeScopeAcessType::Public) {
        if (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Namespace) {
            foreach (OmniDocuGen::MemberTypeInformation::ptr_t, member, mti->Members) {
                if ((*member)->IsStatic) { continue; }
                List<std::string> tmp = _GetMtiList(*member);
                foreach (std::string, tval, tmp) {
                    ret.push_back(*tval);
                }
            }
            List<std::string> tmp2 = _GetParamStaticInfo(mti);
            foreach (std::string, tval, tmp2) {
                ret.push_back(*tval);
            }
        } else {
            if ((mti->CodeType == OmniDocuGen::Types::CodeStructureType::Class) ||
                (mti->CodeType == OmniDocuGen::Types::CodeStructureType::Struct))
            {
                if (mti->IsTemplated()) {
                    ret.push_back((mti->FullPath + _GetTemplate(mti->Template) + " temp_val"));
                } else {
                    ret.push_back((mti->FullPath + " temp_val"));
                }
                foreach (OmniDocuGen::MemberTypeInformation::ptr_t, member, mti->Members) {
                    if ((*member)->IsStatic) { continue; }
                    List<std::string> tmp = _GetMemberParams(*member);
                    foreach (std::string, tval, tmp) {
                        ret.push_back(*tval);
                    }
                }
                List<std::string> tmp2 = _GetParamStaticInfo(mti);
                foreach (std::string, tval, tmp2) {
                    ret.push_back(*tval);
                }
            } else {
                ret = _GetMemberParams(mti);
            }
        }
    }
    return ret;
}

static std::string _GetMtiParamData(OmniDocuGen::MemberTypeInformation::ptr_t& mti)
{
    std::string ret;
    List<std::string> list = _GetMtiList(mti);
    std::map<std::string, uint32_t> vals;
    foreach (std::string, tval, list) {
        if (vals[*tval] == 0) {
            ret += *tval + ";\n";
        }
        vals[*tval] += 1;
    }
    return "typedef double T;\n" + ret + "\n";
}

static List<std::string> _MacroScanSourceFile(const std::string& f)
{
    up(2, "Scanning {0}", f);
    List<std::string> ret;
    std::string ext = omni::io::path::get_extension(f);
    if ((ext != ".hpp") && (ext != ".cpp") && (ext != ".cxx") && (ext != ".hxx")) {
        return ret;
    }

    std::string code = omni::io::file::get_contents(f);
    if (OmniDocuGen::Program::StopReq || code.empty()) { return ret; }
    if (omni::string::contains(code, "OMNI_")) {
        List<std::string> ops;
        std::string finds = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
        std::string newop;
        bool do_add = true;
        size_t beg, end, len, s, e;
        beg = code.find("OMNI_");
        while (beg != std::string::npos) {
            end = code.find_first_not_of(finds, beg);
            len = end - beg;
            newop = code.substr(beg, len);
            do_add = true;
            s = code.rfind("/*", beg);
            if (s != std::string::npos) {
                e = OmniDocuGen::Util::IndexOfCompliment(code, s, "/*", "*/");
                if (((s < beg) && (e > beg)) && ((s < end) && (e > end))) {
                    // it's in a comment, so skip it
                    do_add = false;
                }
            }
            if (do_add) {
                up(5, "FOUND {0}", newop);
                ops.push_back(newop);
            }
            code.replace(beg, len, " ");
            beg = code.find("OMNI_", beg);
        }
        if (OmniDocuGen::Program::StopReq) { return ret; }
        if (ops.size() > 1) {
            std::string ot;
            foreach (std::string, op, ops) {
                if (OmniDocuGen::Program::StopReq) { return ret; }
                if (!omni::string::contains(*op, "OMNI_")) { continue; }
                ot = omni::string::trim(*op);
                if (omni::string::ends_with(ot, "_HPP") || omni::string::ends_with(ot, "_FW") || ot == "OMNI_") { continue; }
                if (omni::string::starts_with(ot, "OMNI_BIND") && (ot != "OMNI_BIND") && (ot != "OMNI_BIND_CONST")) {
                    if (omni::string::is_numeric(ot.substr(9, 1))) { continue; }
                }
                if (OmniDocuGen::Program::StopReq) { return ret; }
                if (has_not(ret, ot)) {
                    ret.push_back(ot);
                }
            }
        }
    }
    return ret;
}

static void _ParseCheckedFiles(void_t p)
{
    OMNI_UNUSED(p);
    omni::stopwatch ssw;
    try {
        up("Parsing {0} syntax files", omni::string::to_string(_checkedFiles.size()));
        ssw.start();
        OmniDocuGen::DocuGen::GenerateHtmlSyntaxFiles(_checkedFiles);
        ssw.stop();
        up("syntax generation: {0} ms", omni::string::to_string(ssw.elapsed_ms()));
        up((OmniDocuGen::Program::StopReq ? "stop requested" : "parse thread complete"));
    } catch (const std::exception& ex) {
        OmniDocuGen::Program::AddError(ex, "Error in generator thread");
    }
}

static void _ParseCheckedMacros(void_t p)
{
    OMNI_UNUSED(p);
    omni::stopwatch ssw;
    try {
        up("Parsing {0} macro files", omni::string::to_string(_checkedMacros.size()));
        ssw.start();
        OmniDocuGen::DocuGen::GenerateMacroOptions(_checkedMacros);
        ssw.stop();
        up("Macro generation: {0} ms", omni::string::to_string(ssw.elapsed_ms()));
        up((OmniDocuGen::Program::StopReq ? "stop requested" : "parse thread complete"));
    } catch (const std::exception& ex) {
        OmniDocuGen::Program::AddError(ex, "Error in generator thread");
    }
}

static void _ParseCheckedMembers(void_t p)
{
    OMNI_UNUSED(p);
    omni::stopwatch ssw;
    try {
        up("parsing {0} class members", omni::string::to_string(_checkedMembers.size()));
        ssw.start();
        OmniDocuGen::DocuGen::GenerateClassFiles(_checkedMembers, false);
        ssw.stop();
        up("member generation: {0} ms", omni::string::to_string(ssw.elapsed_ms()));
        up((OmniDocuGen::Program::StopReq ? "stop requested" : "parse thread complete"));
    } catch (const std::exception& ex) {
        OmniDocuGen::Program::AddError(ex, "Error in generator thread");
    }
}

static void _ParseCheckedExamples(void_t p)
{
    OMNI_UNUSED(p);
    omni::stopwatch ssw;
    up("parsing {0} class members", omni::string::to_string(_checkExamples.size()));
    foreach (OmniDocuGen::FrameworkExample, ex, _checkExamples) {
        if (OmniDocuGen::Program::StopReq) { return; }
        try {
            std::string fname = omni::io::path::combine(OmniDocuGen::DocuGen::Examples, (ex->HtmlFile));
            if (!OmniDocuGen::Util::WriteFile(fname, ex->ToHTML())) {
                OmniDocuGen::Program::AddError(OmniDocuGen::Util::Format("Could not write example file {0}", fname));
            }
        } catch (const std::exception& ex) {
            OmniDocuGen::Program::AddError(ex, "Error in generator thread");
        }
    }
    OmniDocuGen::DocuGen::GenerateExampleIndexHtml(false);
}

static void Full()
{
    up("Running Omni Document Generator");
    if (omni::io::directory::exists(OmniDocuGen::Program::Settings.SourceDirectory)) {
        omni::application::argparser& args = omni::application::args();
        omni::seq::string_t cfiles, cmacs, cmems, cexes;
        bool specific = false;
        omni::stopwatch sw;
        
        if (args.contains("-doall")) {
            OmniDocuGen::DocuGen::DoAPI = true;
            OmniDocuGen::DocuGen::DoBuildFiles = true;
            OmniDocuGen::DocuGen::DoClasses = true;
            OmniDocuGen::DocuGen::DoClassIndex = true;
            OmniDocuGen::DocuGen::DoExamples = true;
            OmniDocuGen::DocuGen::DoFilesView = true;
            OmniDocuGen::DocuGen::DoMacroOptions = true;
            OmniDocuGen::DocuGen::DoSyntax = true;
            OmniDocuGen::DocuGen::DoHashZipFiles = true;
            OmniDocuGen::DocuGen::DoJs = true;
        } else {
            OmniDocuGen::DocuGen::DoAPI = args.contains("-doapi");
            OmniDocuGen::DocuGen::DoBuildFiles = args.contains("-dobuild");
            OmniDocuGen::DocuGen::DoClasses = args.contains("-doclasses");
            OmniDocuGen::DocuGen::DoClassIndex = args.contains("-doclassindex");
            OmniDocuGen::DocuGen::DoExamples = args.contains("-doexamples");
            OmniDocuGen::DocuGen::DoFilesView = args.contains("-dofilesview");
            OmniDocuGen::DocuGen::DoMacroOptions = args.contains("-domacros");
            OmniDocuGen::DocuGen::DoSyntax = args.contains("-dosyntax");
            OmniDocuGen::DocuGen::DoHashZipFiles = args.contains("-dohash");
            OmniDocuGen::DocuGen::DoJs = args.contains("-dojs");
        }
        if (args.contains("-src")) { cfiles = args.get_switches("-src"); }
        if (args.contains("-mac")) { cmacs = args.get_switches("-mac"); }
        if (args.contains("-mti")) { cmems = args.get_switches("-mti"); }
        if (args.contains("-ex")) { cexes = args.get_switches("-ex"); }
        specific = ((cfiles.size() > 0) || (cmacs.size() > 0) || (cmems.size() > 0) || (cexes.size() > 0));
        if (!OmniDocuGen::DocuGen::DoAPI && !OmniDocuGen::DocuGen::DoBuildFiles && !OmniDocuGen::DocuGen::DoClasses &&
            !OmniDocuGen::DocuGen::DoClassIndex && !OmniDocuGen::DocuGen::DoExamples && !OmniDocuGen::DocuGen::DoFilesView &&
            !OmniDocuGen::DocuGen::DoMacroOptions && !OmniDocuGen::DocuGen::DoSyntax && !OmniDocuGen::DocuGen::DoHashZipFiles &&
            !OmniDocuGen::DocuGen::DoJs && !specific)
        {
            up("No options specified for full mode.");
            FullUsage();
            return;
        }
        if (OmniDocuGen::DocuGen::ParseNeeded()) {
            bool isFile = (OmniDocuGen::DocuGen::DoFilesView && cfiles.size() > 0);
            bool isMac = (OmniDocuGen::DocuGen::DoMacroOptions && cmacs.size() > 0);
            bool isMem = (OmniDocuGen::DocuGen::DoClasses && cmems.size() > 0);
            bool isEx = (OmniDocuGen::DocuGen::DoExamples && cexes.size() > 0);
            bool isfw = !(isFile || isMac || isMem || isEx);
            if (!isfw) {
                pl("The following items are selected for specific generation:");
                if (isFile) { pl(cfiles.size() << " HTML syntax file(s)"); }
                if (isMac) { pl(cmacs.size() << " macro help file(s)"); }
                if (isMem) { pl(cmems.size() << " class member help file(s)"); }
                if (isEx) { pl(cexes.size() << " class member help file(s)"); }

                pl("There are also library build options specified. What would you like to do?");
                pl("");
                pl("1.) Continue with the above selected.");
                pl("2.) Build the library with the specified options.");
                pl("3.) Quit.");
                pl("");
                pv("Choose [1, 2, 3]: ");
                std::string ans;
                read_line(ans);
                if (ans.size() > 0) {
                    char op = omni::string::to_lower(ans)[0];
                    switch (op) {
                        case '1': specific = true; break;
                        case '2': specific = false; break;
                        case '3': default: return; // quit
                    }
                }
            }
        }
        if (specific || OmniDocuGen::DocuGen::ParseNeeded()) {
            sw.start();
            OmniDocuGen::DocuGen::StartSource((specific ? OmniDocuGen::Types::SourceGenType::Normal : OmniDocuGen::Types::SourceGenType::BuildToo));
            sw.stop();
            up("Found {0} top level members with {1} total members in {2}s ({3}ms)",
                omni::string::to_string(OmniDocuGen::DocuGen::AllMti->GetNodeCount(false)),
                omni::string::to_string(OmniDocuGen::DocuGen::AllMti->GetNodeCount(true)),
                omni::string::to_string(omni::math::round((static_cast<double>(sw.elapsed_ms())/1000), 3)),
                omni::string::to_string(sw.elapsed_ms())
            );

            omni_foreach (std::string, val, cfiles) {
                OmniDocuGen::CodeGen::ptr_t gen(new OmniDocuGen::CodeGen(*val));
                up(1, "Using source {0}", gen->SourceFile);
                _checkedFiles.push_back(gen);
            }
            omni_foreach (std::string, val, cmacs) {
                foreach (OmniDocuGen::MacroOp, op, OmniDocuGen::DocuGen::Macros) {
                    if (op->Name == omni::string::to_upper(*val)) {
                        up(1, "Using macro {0}", op->Name);
                        _checkedMacros.push_back(*op);
                        break;
                    }
                }
            }
            omni_foreach (std::string, val, cmems) {
                OmniDocuGen::MemberTypeInformation::ptr_t mti = OmniDocuGen::DocuGen::AllMti->Find(*val);
                if (mti && (mti->FullPath == *val)) {
                    up(1, "Using file ", mti->FullPath);
                    _checkedMembers.push_back(mti);
                }
            }
            omni_foreach (std::string, val, cexes) {
                std::string en = omni::io::path::combine(OmniDocuGen::Program::Settings.ExampleDirectory, *val);
                if (omni::io::directory::exists(en)) {
                    OmniDocuGen::FrameworkExample ex(en);
                    up(1, "Using example ", ex.Name);
                    _checkExamples.push_back(ex);
                } else {
                    up("Could not find example directory '{0}'", en);
                }
            }
        }
        if (specific) {
            List<omni_task_t> tasks;
            sw.start();
            if (_checkedFiles.size() > 0) { tasks.push_back(_ParseCheckedFiles); }
            if (_checkedMacros.size() > 0) { tasks.push_back(_ParseCheckedMacros); }
            if (_checkedMembers.size() > 0) { tasks.push_back(_ParseCheckedMembers); }
            if (_checkExamples.size() > 0) { tasks.push_back(_ParseCheckedExamples); }
            // generate the class tree and classes/index.html
            if (OmniDocuGen::DocuGen::DoClassIndex) {
                OmniDocuGen::DocuGen::CheckClassDir();
                tasks.push_back(OmniDocuGen::DocuGen::_DoClassIndex);
            }
            // generate the sysapi/index.html
            if (OmniDocuGen::DocuGen::DoAPI) { tasks.push_back(OmniDocuGen::DocuGen::_DoAPI); }
            // generate the docs/htmlsrc/index.html...
            if (OmniDocuGen::DocuGen::DoFilesView) { tasks.push_back(OmniDocuGen::DocuGen::_DoFilesView); }

            if (OmniDocuGen::Program::SingleThreaded) {
                foreach (omni_task_t, task, tasks) {
                    (*task)(void_t());
                }
            } else {
                foreach (omni_task_t, task, tasks) {
                    OmniDocuGen::Program::Tasks.queue(*task);
                }
                OmniDocuGen::Program::Tasks.wait_active_queue();
                // should be clear by this point, but just in case
                OmniDocuGen::Program::Tasks.clear_queue();
            }

            OmniDocuGen::DocuGen::CheckGenerateBuildJsHash();

            sw.stop();
            up("Total time to complete: {0}s ({1}ms)",
                omni::string::to_string(omni::math::round((static_cast<double>(sw.elapsed_ms())/1000), 3)),
                omni::string::to_string(sw.elapsed_ms())
            );
        } else {
            OmniDocuGen::DocuGen::StartBuild();
        }
        OmniDocuGen::Program::SetGenerationProgress(OmniDocuGen::Types::GenerationStatus::MainComplete);
    } else {
        up("The source directory does not exist: {0}", OmniDocuGen::Program::Settings.SourceDirectory);
    }
}

static void MacroGen()
{
    /*
        The macro's referenced in the documentation are stored in an XML based
        file format from the OmniDocuGen::Program::Settings.MacroDirectory.

        Each file has the following format:

        <?xml version="1.0"?>
        <MacroOp xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">
          <Name></Name>
          <Brief></Brief>
          <Considerations></Considerations>
          <Description></Description>
          <Notes></Notes>
          <PlatformSpecific></PlatformSpecific>
          <Synopsis></Synopsis>
          <IsHelper>false</IsHelper>
          <IsConstant>false</IsConstant>
          <IsFWHelp>false</IsFWHelp>
        </MacroOp>

        The command line macro editor/generator's purpose will be to view
        and create the XML files _only_ since 'editing' the files can
        be done easier by simply using a command line text editor or a
        GUI text editor (like VS Code, or TextEdit in Mac, LeafPad in *nix, or
        even simply Notepad in Windows). Another way to 'edit' the file
        would be to use this tool to create a "new" macro file, and pass
        the -overwrite flag which will overwrite that macro file if it
        exists.
    */
    omni::application::argparser& args = omni::application::args();
    pl("Running Omni MACRO viewer/creator mode");
    if (args.contains("-new")) {
        // create mode
        bool usedef = args.contains("-noask");
        bool ow = args.contains("-overwrite");
        std::string name = args["-name"];
        std::string brief = args["-brief"];
        std::string helper = (args.contains("-is_helper") ? "T" : "");
        std::string constant = (args.contains("-is_constant") ? "T" : "");
        std::string fwhelp = (args.contains("-is_fwhelp") ? "T" : "");
        if (usedef) {
            if (brief.empty()) { brief = "A library macro/option"; }
            if (helper.empty()) { helper = "F"; }
            if (constant.empty()) { constant = "F"; }
            if (fwhelp.empty()) { fwhelp = "F"; }
        }
        // These won't be "created" as they can allow for a larger text input;
        // so we create and then alert.
        // <Considerations></Considerations> <Description></Description> <Notes></Notes>
        // <PlatformSpecific></PlatformSpecific> <Synopsis></Synopsis>
        if (name.empty()) {
            pv("Enter the macro name (e.g. OMNI_BIND): ");
            read_line(name);
            name = omni::string::to_upper(name);
        }
        if (brief.empty()) {
            pv("Enter the macro @Brief (e.g. A helper macro for binding to the omni::delegate): ");
            read_line(brief);
        }
        if (helper.empty()) {
            pv("Is this macro a helper macro? (T/F): ");
            read_line(helper);
        }
        if (constant.empty()) {
            pv("Is this macro a constant macro? (T/F): ");
            read_line(constant);
        }
        if (fwhelp.empty()) {
            pv("Is this macro a library helper macro? (T/F): ");
            read_line(fwhelp);
        }
        bool is_helper = ((helper.size() > 0) && (omni::string::to_lower(helper)[0] == 't')) ? true : false;
        bool is_constant = ((constant.size() > 0) && (omni::string::to_lower(constant)[0] == 't')) ? true : false;
        bool is_fwhelp = ((fwhelp.size() > 0) && (omni::string::to_lower(fwhelp)[0] == 't')) ? true : false;
        name = omni::string::to_upper(name);
        OmniDocuGen::MacroOp op(name, brief, is_helper, is_constant, is_fwhelp);
        if (!op.Exists() || ow) {
            pl("Creating macro '" << op << "'");
            if (op.Save()) {
                pl("Created macro '" << op << "' at '" << op.FileName() << "'");
                pl("Be sure to edit the XML file for the following: Considerations, Description, Notes, PlatformSpecific and Synopsis");
            }
        } else if (op.Exists() && !ow) {
            pl("Macro '" << op << "' already exists and -overwrite was not specified.");
        } else {
            pl("Unknown condition met!??");
        }
    } else if (args.contains("-scan")) {
        // scan mode to scan for new macros
        typedef std::map<std::string, uint8_t> op_map;
        List<std::string> newops;
        op_map macros, oldops, rems;
        std::string ans;
        omni::stopwatch swtot, sw;
        swtot.start();
        OmniDocuGen::DocuGen::LoadMacros(OmniDocuGen::Program::Settings.MacroDirectory);
        foreach (OmniDocuGen::MacroOp, mo, OmniDocuGen::DocuGen::Macros) { 
            macros[mo->Name] = 1;
            oldops[mo->Name] = 1;
        }
        omni::seq::std_string_t src;
        omni::io::directory::get_all_files(OmniDocuGen::Program::Settings.SourceDirectory, src);
        pl("Scanning " << src.size() << " source files from " << OmniDocuGen::Program::Settings.SourceDirectory);
        sw.start();
        omni_foreach (std::string, s, src) {
            if (OmniDocuGen::Program::StopReq) { break; }
            List<std::string> scans = _MacroScanSourceFile(*s);
            foreach (std::string, op, scans) {
                if (macros[*op] != 1) {
                    newops.push_back(*op);
                    macros[*op] = 1;
                } else {
                    rems[*op] = 1;
                }
            }
        }
        sw.stop();
        swtot.stop();
        std_foreach(op_map, op, rems) {
            oldops.erase(op->first);
        }
        std::cout << std::endl;
        up(2, "Total time: {0}ms", omni::string::to_string(swtot.elapsed_ms()));
        pl("Scanned " << src.size() << " files in " << sw.elapsed_ms() << "ms, found " << macros.size() << " macros with " << newops.size() << " new and " << oldops.size() << " old");
        
        if (newops.size() > 0) {
            pl("Macro's not currently accounted for:");
            foreach (std::string, op, newops) {
                pl(*op);
            }
            pl("");
        }
        if (oldops.size() > 0) {
            pl("Macro's no longer in use:");
            std_foreach (op_map, op, oldops) {
                pl(op->first << ": " << omni::io::path::combine(OmniDocuGen::Program::Settings.MacroDirectory, omni::string::to_lower(op->first)) << ".xml");
            }
            pl("");
        }
    } else {
        // default view mode
        bool f = args.contains("-name");
        bool b = args.contains("-brief");
        bool d = args.contains("-details");
        bool e = args.contains("-extra");
        OmniDocuGen::DocuGen::LoadMacros(OmniDocuGen::Program::Settings.MacroDirectory);
        foreach (OmniDocuGen::MacroOp, m, OmniDocuGen::DocuGen::Macros) {
            // ToFullString(bool view_file, bool view_brief, bool view_deets, bool view_is)
            pv(m->ToFullString(f, b, d, e));
        }
        pl("Total: " << OmniDocuGen::DocuGen::Macros.size());
    }
}

static void SysAPI()
{
    /*
        The system API's referenced in the documentation are stored in an XML based
        file format from the OmniDocuGen::Program::Settings.SystemAPIDirectory.

        Each file has the following format:

        <?xml version="1.0"?>
        <SysAPI xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">
        <Name>{NAME_OF_API}</Name>
        <Link>{CODE_REFERENCE_WEB_LINK}</Link>
        <SysType>{The OmniDocuGen::Types::SystemType, one of the following [Windows, Apple, Linux, Unix, POSIX, STD]}</SysType>
        </SysAPI>

        The command line API editor/generator's purpose will be to view
        and create the XML files _only_ since 'editing' the files can
        be done easier by simply using a command line text editor or a
        GUI text editor (like VS Code, TextEdit in Mac, or LeafPad in *nix, or
        even simply Notepad in Windows). Another way to 'edit' the file
        would be to use this tool to create a "new" API file, and pass
        the -overwrite flag which will overwrite that API file if it
        exists.
    */
    omni::application::argparser& args = omni::application::args();
    pl("Running Omni System API viewer/creator mode");
    if (args.contains("-scan")) {
        OmniDocuGen::DocuGen::LoadSystemAPI(OmniDocuGen::Program::Settings.SystemAPIDirectory);
        size_t apisz = OmniDocuGen::DocuGen::SysAPIs.size();
        omni::seq::std_string_t sources;
        omni::io::directory::get_all_files(OmniDocuGen::Program::Settings.SourceDirectory, sources);
        List<std::string> found;
        omni_foreach (std::string, src, sources) {
            up(1, "Searching in {0}", *src);
            std::string code = omni::io::file::get_contents(*src);
            foreach (OmniDocuGen::SysAPI, api, OmniDocuGen::DocuGen::SysAPIs) {
                if ((api->SysType == OmniDocuGen::Types::SystemType::STD) && omni::string::contains(code, api->Name)) {
                    code = omni::string::replace_all(code, api->Name, " ");
                }
            }
            while (omni::string::contains(code, "std::")) {
                std::string std;
                size_t s = code.find("std::");
                size_t e = s + 5;
                for (;(omni::char_util::is_alpha_num(code[e]) || code[e] == '_' || code[e] == ':'); ++e);
                std = code.substr(s, e-s);
                if (std::find(found.begin(), found.end(), std) == found.end()) {
                    up(1, "Found {0}", std);
                    found.push_back(std);
                }
                code = omni::string::replace_all(code, std, "");
            }
        }
        pl("Found " << found.size() << " additional 'std' API's:");
        foreach (std::string, api, found) {
            pl(*api);
        }
        pl("");
    } else if (args.contains("-new")) {
        // create mode
        bool ow = args.contains("-overwrite");
        std::string name = args["-name"];
        std::string link = args["-link"];
        std::string sys = args["-type"];
        OmniDocuGen::Types::SystemType type;
        if (name.empty()) {
            pv("Enter the API function name (e.g. ftruncate, CreateThread, std::ceil ..): ");
            std::cin >> name;
        }
        if (link.empty()) {
            pv("Enter the API reference link (e.g. https://linux.die.net/man/3/ftruncate): ");
            std::cin >> link;
        }
        if (sys.empty()) {
            pv("Enter the API system of 'Windows', 'Apple', 'Linux', 'Unix', 'POSIX', or 'STD': ");
            std::cin >> sys;
        }
        if (OmniDocuGen::Types::SystemType::try_parse(sys, type)) {
            OmniDocuGen::SysAPI api(name, link, type);
            if (!api.Exists() || ow) {
                pl("Creating system API '" << api << "'");
                if (api.Save()) {
                    pl("Created system API '" << api << "' at '" << api.FileName() << "'");
                }
            } else if (api.Exists() && !ow) {
                pl("System API '" << api << "' already exists and -overwrite was not specified.");
            } else {
                pl("Unknown condition met!??");
            }
        } else {
            pl("Unknown system type specified '" << sys << "'; must be one of the following:");
            pl("Windows, Apple, Linux, Unix, POSIX, STD");
        }
    } else {
        // default view mode
        bool f = args.contains("-name");
        bool l = args.contains("-link");
        OmniDocuGen::DocuGen::LoadSystemAPI(OmniDocuGen::Program::Settings.SystemAPIDirectory);
        foreach (OmniDocuGen::SysAPI, s, OmniDocuGen::DocuGen::SysAPIs) {
            pl(s->ToFullString(f, l));
        }
        pl("Total: " << OmniDocuGen::DocuGen::SysAPIs.size());
    }
}

static void LicenseReplacer()
{
    omni::application::argparser& args = omni::application::args();
    std::string old_lic_cont;
    std::string new_lic_cont;
    size_t tot = 0;
    std::string omni_dir = OmniDocuGen::Program::Settings.SourceDirectory;
    std::string out_dir = args["-out"];
    std::string old_lic_file = args["-old"];
    std::string new_lic_file = args["-new"];
    bool to_stdout = args.contains("-stdout");
    bool do_replace = args.contains("-replace");
    if (out_dir.empty()) {
        out_dir = omni::io::path::combine(OmniDocuGen::Program::Settings.TempZipDirectory, "src_licrep");
    }
    if (old_lic_file.empty()) {
        old_lic_file = OmniDocuGen::Program::Settings.LicenseFile;
    }
    pl("Running Omni license replacer mode");
    if (!omni::io::file::exists(old_lic_file) || !omni::io::file::exists(new_lic_file)) {
        pl("Both license files must exists.");
        return;
    }
    if (!omni::io::directory::exists(omni_dir)) {
        pl("Omni directory does not exists: " << omni_dir);
        return;
    }
    if (!out_dir.empty() && !omni::io::directory::exists(out_dir)) {
        pv("Creating directory '" << out_dir << "' ...");
        if (!omni::io::directory::create(out_dir, true)) {
            pl("failed.");
            return;
        }
        pl("done.");
    }
    pl(
        "Using old file '" << old_lic_file << "', new file '" << new_lic_file <<
        "', output path '" << out_dir << "'" << (to_stdout ? ", printing to standard out" : "")
    );
    old_lic_cont = omni::string::trim(omni::io::file::get_contents(old_lic_file));
    new_lic_cont = omni::string::trim(omni::io::file::get_contents(new_lic_file));
    if (old_lic_cont.empty() || new_lic_cont.empty()) {
        pl("License contents must not be empty.");
        return;
    }
    if (old_lic_cont == new_lic_cont) {
        pl("New license and old license are the same.");
        return;
    }
    omni::seq::std_string_t files;
    omni::io::directory::get_all_files(omni_dir, files);
    pl("Found " << files.size() << " files.");
    std::string contents;
    std::string fname;
    omni_foreach(std::string, file, files) {
        fname = omni::io::path::combine(out_dir, (*file).substr(omni_dir.length()));
        if (!to_stdout && !omni::io::directory::create(omni::io::path::get_parent_name(fname), true)) {
            pl("Could not create directory: " << omni::io::path::get_parent_name(fname));
            continue;
        }
        contents = omni::io::file::get_contents(*file);
        if ((contents.length() <= old_lic_cont.length()) ||
            (contents.substr(0, old_lic_cont.length()) != old_lic_cont))
        {
            pv(*file << " non-licensed");
            if (!to_stdout) {
                pv(", copying...");
                uint64_t w = (OmniDocuGen::Program::Profile ? contents.length() : omni::io::file::write(fname, contents));
                if (w == contents.length()) {
                    pl("SUCCESS!");
                    ++tot;
                } else {
                    pl("FAILURE, wrote " << w << " bytes, expected " << contents.length());
                }
            } else {
                pl(", continuing...");
                ++tot;
            }
            continue;
        }

        pv(fname << ": ");
        contents = new_lic_cont + contents.substr(old_lic_cont.length());
        if (to_stdout) {
            pv(std::endl << contents);
            ++tot;
        } else {
            uint64_t w = (OmniDocuGen::Program::Profile ? contents.length() : omni::io::file::write(fname, contents));
            if (w == contents.length()) {
                pl("SUCCESS!");
                ++tot;
            } else {
                pl("FAILURE, wrote " << w << " bytes, expected " << contents.length());
            }
        }
    }
    pl(std::endl << "Analyzed " << tot << " files.");
    if (do_replace) {
        pv("Replacing '" << old_lic_file << "' content with '" << new_lic_file << "' content...");
        size_t w = (OmniDocuGen::Program::Profile ? new_lic_cont.length() : omni::io::file::write(old_lic_file, new_lic_cont));
        if (w == new_lic_cont.size()) {
            pl("SUCCESS.");
        } else {
            pl("fail.");
        }
    }
}

static void CodeToHtml()
{
    pl("Running HTML code highlighter mode");
    omni::application::argparser& args = omni::application::args();
    std::string code;
    std::string inchref = args["-inchref"];
    std::string dochref = args["-dochref"];
    bool gencss = args.contains("-css");
    bool genbox = args.contains("-checkbox");
    bool genclasses = args.contains("-genclasses");
    std::string ifile = args["-in"];
    std::string ofile = args["-out"];
    if (ifile.empty()) {
        std::stringstream ssc;
        pl("Enter your code (press EOL [CTRL+D] to stop):");
        for (std::string line; std::getline(std::cin, line);) {
            if (OmniDocuGen::Program::StopReq) { return; }
            ssc << line << std::endl;
        }
        code = ssc.str();
        pl(std::endl);
    } else {
        if (omni::io::file::exists(ifile)) {
            code = omni::io::file::get_contents(ifile);
        } else {
            pl("Input file '" << ifile << "' not found.");
            return;
        }
    }
    std::string html;
    if (gencss) {
        html = "<style type=\"text/css\">" OMNI_EOL_N
        "a:link, a:visited { color: #2E93D6; text-decoration: none; }" OMNI_EOL_N
        "a:hover { color: #34B2E9; text-decoration: underline; }" OMNI_EOL_N
        "pre, code, .code { font-size: 12px; }" OMNI_EOL_N
        "code, .code { white-space: nowrap; }" OMNI_EOL_N
        "sup, sub { font-size: 0.75em; }" OMNI_EOL_N
        "sup > code, sub > code, sup > .code, sub > .code { font-size: inherit; }" OMNI_EOL_N
        "code > sup, code > sub, .code > sup, .code > sub { font-size: 0.8em; }" OMNI_EOL_N
        "pre, code, .code, div.sntx > input+label { font-family: Consolas, Courier, Arial, Tahoma, serif; }" OMNI_EOL_N
        "div.sntx { color: #CACACA; background-color: #272727; border: 1px solid #CACACA; padding: 0.25em; overflow: hidden; margin: 1em 0 1em 0; box-shadow: 0 0 4px #999999; }" OMNI_EOL_N
        "div.sntx > pre { margin: 0.5em 0 0 0; overflow: auto; }" OMNI_EOL_N;
        if (genbox) {
            html += "div.sntx > input { cursor: pointer; position: absolute; right: 1.75em; visibility: hidden; }" OMNI_EOL_N
            "div.sntx > input+label { font-size: 12px; padding-left: 1.3em; cursor: pointer; background: url(data:image/gif;base64,R0lGODlhDAAMAPcAAAAAAAAAMwAAZgAAmQAAzAAA/wAzAAAzMwAzZgAzmQAzzAAz/wBmAABmMwBmZgBmmQBmzABm/wCZAACZMwCZZgCZmQCZzACZ/wDMAADMMwDMZgDMmQDMzADM/wD/AAD/MwD/ZgD/mQD/zAD//zMAADMAMzMAZjMAmTMAzDMA/zMzADMzMzMzZjMzmTMzzDMz/zNmADNmMzNmZjNmmTNmzDNm/zOZADOZMzOZZjOZmTOZzDOZ/zPMADPMMzPMZjPMmTPMzDPM/zP/ADP/MzP/ZjP/mTP/zDP//2YAAGYAM2YAZmYAmWYAzGYA/2YzAGYzM2YzZmYzmWYzzGYz/2ZmAGZmM2ZmZmZmmWZmzGZm/2aZAGaZM2aZZmaZmWaZzGaZ/2bMAGbMM2bMZmbMmWbMzGbM/2b/AGb/M2b/Zmb/mWb/zGb//5kAAJkAM5kAZpkAmZkAzJkA/5kzAJkzM5kzZpkzmZkzzJkz/5lmAJlmM5lmZplmmZlmzJlm/5mZAJmZM5mZZpmZmZmZzJmZ/5nMAJnMM5nMZpnMmZnMzJnM/5n/AJn/M5n/Zpn/mZn/zJn//8wAAMwAM8wAZswAmcwAzMwA/8wzAMwzM8wzZswzmcwzzMwz/8xmAMxmM8xmZsxmmcxmzMxm/8yZAMyZM8yZZsyZmcyZzMyZ/8zMAMzMM8zMZszMmczMzMzM/8z/AMz/M8z/Zsz/mcz/zMz///8AAP8AM/8AZv8Amf8AzP8A//8zAP8zM/8zZv8zmf8zzP8z//9mAP9mM/9mZv9mmf9mzP9m//+ZAP+ZM/+ZZv+Zmf+ZzP+Z///MAP/MM//MZv/Mmf/MzP/M////AP//M///Zv//mf//zP///6ysqp2dm6Ghn6OjoaSkoqampMbGxcjIx8zMy7e3tpWVlMzMzcvLzL+/wD4+PywsLC8vLzExMTQ0NDg4OEhISG1tbXt7e4mJiaioqLCwsLS0tLu7u8PDw8rKys3Nzc7Ozs/Pz9DQ0NLS0tTU1Nzc3OHh4eLi4gAAACH5BAEAAP8ALAAAAAAMAAwAAAg5AK0IHEhw4L+DCBMKTHgt4b+FCK9ZUTgxYsWDC69p3NjwYUWBEg1CPCiRIsOLHh2iHOkQY8GXVgICADs=) 0 0.1em no-repeat; }" OMNI_EOL_N
            "div.sntx > input:checked+label { background: url(data:image/gif;base64,R0lGODlhDAAMAPcAAAAAAAAAMwAAZgAAmQAAzAAA/wAzAAAzMwAzZgAzmQAzzAAz/wBmAABmMwBmZgBmmQBmzABm/wCZAACZMwCZZgCZmQCZzACZ/wDMAADMMwDMZgDMmQDMzADM/wD/AAD/MwD/ZgD/mQD/zAD//zMAADMAMzMAZjMAmTMAzDMA/zMzADMzMzMzZjMzmTMzzDMz/zNmADNmMzNmZjNmmTNmzDNm/zOZADOZMzOZZjOZmTOZzDOZ/zPMADPMMzPMZjPMmTPMzDPM/zP/ADP/MzP/ZjP/mTP/zDP//2YAAGYAM2YAZmYAmWYAzGYA/2YzAGYzM2YzZmYzmWYzzGYz/2ZmAGZmM2ZmZmZmmWZmzGZm/2aZAGaZM2aZZmaZmWaZzGaZ/2bMAGbMM2bMZmbMmWbMzGbM/2b/AGb/M2b/Zmb/mWb/zGb//5kAAJkAM5kAZpkAmZkAzJkA/5kzAJkzM5kzZpkzmZkzzJkz/5lmAJlmM5lmZplmmZlmzJlm/5mZAJmZM5mZZpmZmZmZzJmZ/5nMAJnMM5nMZpnMmZnMzJnM/5n/AJn/M5n/Zpn/mZn/zJn//8wAAMwAM8wAZswAmcwAzMwA/8wzAMwzM8wzZswzmcwzzMwz/8xmAMxmM8xmZsxmmcxmzMxm/8yZAMyZM8yZZsyZmcyZzMyZ/8zMAMzMM8zMZszMmczMzMzM/8z/AMz/M8z/Zsz/mcz/zMz///8AAP8AM/8AZv8Amf8AzP8A//8zAP8zM/8zZv8zmf8zzP8z//9mAP9mM/9mZv9mmf9mzP9m//+ZAP+ZM/+ZZv+Zmf+ZzP+Z///MAP/MM//MZv/Mmf/MzP/M////AP//M///Zv//mf//zP///6ysqp2dm6Ghn6OjoaSkoqampMbGxcjIx8zMy7e3tpWVlMzMzcvLzL+/wD4+PywsLC8vLzExMTQ0NDg4OEhISG1tbXt7e4mJiaioqLCwsLS0tLu7u8PDw8rKys3Nzc7Ozs/Pz9DQ0NLS0tTU1Nzc3OHh4eLi4gAAACH5BAEAAP8ALAAAAAAMAAwAAAgvAK0IHEhw4L+DCBMKTMjw38KGCB9CdGjl37WLGK8dfFhwoUSIHxuGZDhSYceOAQEAOw==) 0 0.1em no-repeat; }" OMNI_EOL_N
            "div.sntx > input+label+pre { display: none; }" OMNI_EOL_N
            "div.sntx > input:checked+label+pre { display: block; }" OMNI_EOL_N
            "div.sntx > input+label:before { content: \"show\"; }" OMNI_EOL_N
            "div.sntx > input:checked+label:before { content: \"hide\"; }" OMNI_EOL_N;
        }
        html += "div.cpphtml { position: relative; top: -0.3em; padding-left: 0.5em; }" OMNI_EOL_N
        "div.cpphtmllines { float: left; position: relative; top: -0.3em; border-right: 1px solid #1174D6; }" OMNI_EOL_N
        "div.cpphtmlcmnt { float: left; position: relative; top: -0.3em; width: 1.25em; border-right: 1px solid #1174D6; }" OMNI_EOL_N
        "div.cpphtmlcmnt > img { cursor: pointer; position: relative; left: 0.1em; padding-top: 2px; }" OMNI_EOL_N
        "div.cpphtmlcmnt > img+br+div { width: 1px; position: relative; left: 0.5em; border-right: 1px solid #5A5A5A; }" OMNI_EOL_N
        "div.cpphtmlcmnt > img+br+div+div { width: 8px; height: 1px; position: relative; left: 0.55em; border-top: 1px solid #5A5A5A; }" OMNI_EOL_N
        "div.cpphtmlcmnt > img.c { padding-top: 3px; margin-top: -1px; padding-bottom: 1px; }" OMNI_EOL_N
        "div.cpphtmlcmnt > img+br+div+div.c { border-top: 0; }" OMNI_EOL_N
        "div.syn_ex + div.c { position: relative; left: -0.4em; margin-top: -1px; border-bottom: 1px solid #5A5A5A; }" OMNI_EOL_N
        "font.syn_doc { color: #8080FF; font-style: italic; }" OMNI_EOL_N
        "font.syn_ins { color: #FF853E; font-weight: bold; }" OMNI_EOL_N
        "font.syn_typ { color: #18D28F; font-weight: bold; }" OMNI_EOL_N
        "font.syn_pre { color: #C0C0C0; }" OMNI_EOL_N
        "font.syn_num { color: #B1B76B; }" OMNI_EOL_N
        "font.syn_str { color: #D7DC00; }" OMNI_EOL_N
        "font.syn_chr { color: #FF8080; }" OMNI_EOL_N
        "font.syn_opr { color: #FFCC00; font-weight: bold; }" OMNI_EOL_N
        "font.syn_cmt { color: #00FF00; font-style: italic; }" OMNI_EOL_N
        "font.syn_dkw { color: #FF80FF; font-style: italic; }" OMNI_EOL_N
        "</style>" OMNI_EOL_N;
    }
    html += "<div class=\"sntx\">";
    if (genbox) { html += "<input type=\"checkbox\" id=\"c0\" name=\"c0\" checked /><label for=\"c0\"> example</label>"; }
    html += "<pre>" OMNI_EOL_N;
    if (genclasses) {
        OmniDocuGen::DocuGen::ParseSource(OmniDocuGen::Types::SourceGenType::Normal);
        pl("Generating syntax for " << code.size() << " bytes of text...");
        code = OmniDocuGen::DocuGen::GenerateHtmlSyntaxHighlight(code, inchref, dochref, OmniDocuGen::DocuGen::AllMti, false);
    } else {
        pl("Generating syntax for " << code.size() << " bytes of text...");
        OmniDocuGen::MemberTypeInformation::ptr_t empty;
        code = OmniDocuGen::DocuGen::GenerateHtmlSyntaxHighlight(code, inchref, dochref, empty, false);
    }
    html += omni::string::replace_all(code, "&nbsp;", " ") + OMNI_EOL_N "</pre></div>";
    pl(std::endl << "Generated " << html.size() << " bytes:");
    if (ofile.empty()) {
        pl(html);
    } else {
        uint64_t w = (OmniDocuGen::Program::Profile ? html.length() : omni::io::file::write(ofile, html));
        if (w == html.size()) {
            pl("Successfully wrote HTML output to '" << ofile << "'.");
        } else {
            pl("Error writing to '" << ofile << "', wrote " << w << " bytes, but expected " << html.size() << ".");
        }
    }
}

static void UnitTest()
{
    omni::application::argparser& args = omni::application::args();
    pl("Running unit test parser/creator mode");
    OmniDocuGen::MemberTypeInformation::ptr_t mti;
    omni::stopwatch sw;
    std::string pfile = args["-in"];
    if (!pfile.empty() && omni::io::file::exists(pfile)) {
        OmniDocuGen::CodeGen cg(pfile);
        OmniDocuGen::Program::AddParsingCode(pfile);
        if (OmniDocuGen::Util::IsSourceExt(pfile)) {
            sw.start();
            cg.GenerateSourceTypeInfo();
        } else {
            sw.start();
            cg.GenerateTypeInfo();
        }
        OmniDocuGen::Program::RemoveParsingCode(pfile);
        if (cg.MemberInformation) {

            OmniDocuGen::DocuGen::AllMti = OmniDocuGen::MemberTypeInformation::GetOmni(true);
            OmniDocuGen::DocuGen::MtiTree.SetRoot(OmniDocuGen::DocuGen::AllMti);
            OmniDocuGen::DocuGen::AllMti->AddVerify(cg.MemberInformation);
            OmniDocuGen::Types::TreeNode n(cg.MemberInformation);
            foreach (OmniDocuGen::MemberTypeInformation::ptr_t, ti, cg.MemberInformation->Members) {
                OmniDocuGen::DocuGen::AddTree(*ti, n);
            }
            OmniDocuGen::Types::TreeNode::AddNodes(n, OmniDocuGen::DocuGen::MtiTree);

            mti = OmniDocuGen::DocuGen::AllMti->Find(cg.MemberInformation);
            if (!mti) {
                pl("Member type information for " << cg.MemberInformation << " not found.");
            }
            sw.stop();
        } else {
            up("Could not find any member information in {0}", cg.SourceFile);
        }
    } else {
        std::string member = args["-mti"];
        if (member.empty()) {
            pl("No member specified to generate unit test info.");
        } else {
            sw.start();
            OmniDocuGen::DocuGen::ParseSource(OmniDocuGen::Types::SourceGenType::Normal);
            mti = OmniDocuGen::DocuGen::AllMti->Find(member);
            sw.stop();
            if (!mti) {
                pl("Member type information for " << member << " not found.");
            }
        }
    }
    if (mti) {
        up("Found {0} with {1} total members in {2}s ({3}ms)",
            omni::string::to_string(_GetMtiName(mti)),
            omni::string::to_string(mti->GetNodeCount(true)),
            omni::string::to_string(omni::math::round((static_cast<double>(sw.elapsed_ms())/1000), 3)),
            omni::string::to_string(sw.elapsed_ms())
        );
        if (args.contains("-new")) {
            bool no_info_test = args.contains("-noinfo");
            bool do_comment = args.contains("-comment");
            std::string description = args["-desc"];
            List<UtInfo> ut = _GetMtiUnitName(mti);
            std::string tests_hpp = omni::io::path::combine(OmniDocuGen::Program::Settings.UnitTestDirectory, "tests.hpp");
            std::string utname, ofile, data, params, tplate, func_list_add, info_test, tmp;

            if (args.contains("-split")) {
                foreach (UtInfo, uti, ut) {
                    utname = omni::string::to_lower(omni::string::trim(uti->Name));
                    ofile = omni::io::path::combine(omni::io::path::combine(OmniDocuGen::Program::Settings.UnitTestDirectory, "units"), (utname + ".hpp"));

                    tplate = omni::io::file::get_contents(omni::io::path::combine(OmniDocuGen::Program::Settings.UnitTestDirectory, "template.hpp"));
                    tplate = omni::string::replace(tplate, "testname", utname);
                    tplate = omni::string::replace_all(tplate, "TESTNAME", omni::string::to_upper(utname));
                    tplate = omni::string::replace(tplate, "\n            #error MUST DEFINE TESTS", "");
                    tplate = omni::string::replace(tplate, "\n            M_LIST_ADD(a_test, \"tests some other functionality\");", "");
                    if (!description.empty()) {
                        tplate = omni::string::replace(tplate,
                            "// #define UT_DESC \"Some description\" // define if you want a different description",
                            ("#define UT_DESC \"" + description + "\"")
                        );
                    } else {
                        tplate = omni::string::replace(tplate, "\n// #define UT_DESC \"Some description\" // define if you want a different description", "");
                    }
                    if (uti->IsNS) {
                        tplate = omni::string::replace(tplate, "// #define UT_ISNS true // mark if UT_NAME is a namespace", "#define UT_ISNS true");
                    } else {
                        tplate = omni::string::replace(tplate, "\n// #define UT_ISNS true // mark if UT_NAME is a namespace", "");
                    }
                    if (!uti->RootNS.empty()) {
                        tplate = omni::string::replace(tplate,
                            "// #define UT_ROOT_NS xxxx // mark if the root NS is !omni",
                            ("#define UT_ROOT_NS " + omni::string::to_lower(uti->RootNS)));
                    } else {
                        tplate = omni::string::replace(tplate, "\n// #define UT_ROOT_NS xxxx // mark if the root NS is !omni", "");
                    }

                    params = omni::string::trim(_GetMtiParamData(uti->Member)) + "\n\n";
                    params = omni::string::replace_all(params, "\n", "\n            ");
                    data = omni::string::trim(_PrintMtiTestSignatureInfo(uti->Member));
                    data = params + omni::string::replace_all(data, "\n", "\n            ");
                    info_test = "\n            ";
                    if (args.contains("-comment")) {
                        data = "/*" + data + "*/";
                        info_test += "//";
                    }
                    info_test += "print_info(" + uti->Member->FullPath + ");";
                    if (!no_info_test) {
                        tplate = omni::string::replace(tplate, "\n            UT_INFO_TEST();", info_test);
                    }
                    tplate = omni::string::replace(tplate, "omni::x tval;", data);

                    if (args.contains("-print")) {
                        pl("Printing '" << ofile << "'");
                        pl(tplate);
                        pl("");
                    } else {
                        if (omni::io::file::exist(ofile) && !args.contains("-overwrite")) {
                            pl("The unit test file at '" << ofile << "' already exists and -overwite was not specified.");
                        } else {
                            pl("Writing '" << ofile << "'");
                            omni::io::file::write(ofile, tplate);
                            if (omni::io::file::exist(ofile)) {
                                tmp = ("#include \"units/" + utname + ".hpp\"");
                                if (!omni::string::contains(omni::io::file::get_contents(tests_hpp), tmp)) {
                                    omni::io::file::write_line(tests_hpp, tmp, true);
                                }
                                pl("Success.");
                            } else {
                                pl("Failed writing unit test for '" << ofile << "'.");
                            }
                        }
                    }
                }
            } else {
                std::string basestr = "        void base_test()\n        {\n        }\n";
                std::string newbase = "        void base_test()\n        {";
                std::string root_ns = (args.contains("-rootns") ? args["-rootns"] : ut[0].RootNS);
                bool is_ns = (args.contains("-isns") ? true : ut[0].IsNS);
                
                utname = omni::string::to_lower(omni::string::trim((args.contains("-name") ? args["-name"] : ut[0].Name)));
                ofile = omni::io::path::combine(omni::io::path::combine(OmniDocuGen::Program::Settings.UnitTestDirectory, "units"), (utname + ".hpp"));

                tplate = omni::io::file::get_contents(omni::io::path::combine(OmniDocuGen::Program::Settings.UnitTestDirectory, "template.hpp"));
                tplate = omni::string::replace(tplate, "testname", utname);
                tplate = omni::string::replace_all(tplate, "TESTNAME", omni::string::to_upper(utname));
                tplate = omni::string::replace(tplate, "\n            #error MUST DEFINE TESTS", "");
                tplate = omni::string::replace(tplate, "\n            omni::x tval;", "");
                if (!description.empty()) {
                    tplate = omni::string::replace(tplate,
                        "// #define UT_DESC \"Some description\" // define if you want a different description",
                        ("#define UT_DESC \"" + description + "\"")
                    );
                } else {
                    tplate = omni::string::replace(tplate, "\n// #define UT_DESC \"Some description\" // define if you want a different description", "");
                }
                if (is_ns) {
                    tplate = omni::string::replace(tplate, "// #define UT_ISNS true // mark if UT_NAME is a namespace", "#define UT_ISNS true");
                } else {
                    tplate = omni::string::replace(tplate, "\n// #define UT_ISNS true // mark if UT_NAME is a namespace", "");
                }
                if (!root_ns.empty()) {
                    tplate = omni::string::replace(tplate,
                        "// #define UT_ROOT_NS xxxx // mark if the root NS is !omni",
                        ("#define UT_ROOT_NS " + omni::string::to_lower(root_ns)));
                } else {
                    tplate = omni::string::replace(tplate, "\n// #define UT_ROOT_NS xxxx // mark if the root NS is !omni", "");
                }

                data = ""; info_test = "";
                foreach (UtInfo, uti, ut) {
                    params = omni::string::trim(_GetMtiParamData(uti->Member)) + "\n\n";
                    params = omni::string::replace_all(params, "\n", "\n            ");
                    std::string tmp = params + omni::string::replace_all(omni::string::trim(_PrintMtiTestSignatureInfo(uti->Member)), "\n", "\n            ");
                    info_test += "\n            ";
                    if (args.contains("-comment")) {
                        tmp = "/*" + tmp + "*/";
                        info_test += "//";
                    }
                    info_test += "print_info(" + uti->Member->FullPath + ");";
                    data += "\n        void " + uti->Member->Name + "()\n        {\n            " + tmp + "\n        }\n";
                    func_list_add += "\n            M_LIST_ADD(" + uti->Member->Name + ", \"test the functionality in " + uti->Member->FullPath + "\");";
                    newbase += "\n            " + uti->Member->Name + "(); printl(\"\");";
                }
                newbase += "\n        }\n";

                if (!no_info_test) {
                    tplate = omni::string::replace(tplate, "\n            UT_INFO_TEST();", info_test);
                }
                tplate = omni::string::replace(tplate, "\n            M_LIST_ADD(a_test, \"tests some other functionality\");", func_list_add);
                tplate = omni::string::replace(tplate, basestr, basestr + data);
                tplate = omni::string::replace(tplate, basestr, newbase);

                if (args.contains("-print")) {
                    pl("Printing '" << ofile << "'");
                    pl(tplate);
                } else {
                    if (omni::io::file::exist(ofile) && !args.contains("-overwrite")) {
                        pl("The unit test file at '" << ofile << "' already exists and -overwite was not specified.");
                    } else {
                        pl("Writing '" << ofile << "'");
                        omni::io::file::write(ofile, tplate);
                        if (omni::io::file::exist(ofile)) {
                            tmp = ("#include \"units/" + utname + ".hpp\"");
                            if (!omni::string::contains(omni::io::file::get_contents(tests_hpp), tmp)) {
                                omni::io::file::write_line(tests_hpp, tmp, true);
                            }
                            pl("Success.");
                        } else {
                            pl("Failed writing unit test.");
                        }
                    }
                }
            }
        } else {
            pl("Output:" << std::endl);
            std::cout << omni::string::trim(_GetMtiParamData(mti)) << std::endl << std::endl;
            std::cout << omni::string::trim(_PrintMtiTestSignatureInfo(mti)) << std::endl << std::endl;
        }
    }
}

static void Viewer()
{
    omni::application::argparser& args = omni::application::args();
    pl("Running member parser mode");
    bool dotree = args.contains("-tree") || OmniDocuGen::Program::FullTree;
    std::string pfile = args["-in"];
    std::string member = args["-mti"];
    omni::stopwatch sw;
    if (!pfile.empty() && omni::io::file::exists(pfile)) {
        OmniDocuGen::CodeGen cg(pfile);
        OmniDocuGen::Program::AddParsingCode(pfile);
        if (OmniDocuGen::Util::IsSourceExt(pfile)) {
            sw.start();
            cg.GenerateSourceTypeInfo();
        } else {
            sw.start();
            cg.GenerateTypeInfo();
        }
        sw.stop();
        OmniDocuGen::Program::RemoveParsingCode(pfile);
        if (cg.MemberInformation) {
            up("Found {0} top level members with {1} total members in {2}s ({3}ms)",
                omni::string::to_string(cg.MemberInformation->GetNodeCount(false)),
                omni::string::to_string(cg.MemberInformation->GetNodeCount(true)),
                omni::string::to_string(omni::math::round((static_cast<double>(sw.elapsed_ms())/1000), 3)),
                omni::string::to_string(sw.elapsed_ms())
            );
            if (dotree) {
                OmniDocuGen::DocuGen::AllMti = OmniDocuGen::MemberTypeInformation::GetOmni(true);
                OmniDocuGen::DocuGen::MtiTree.SetRoot(OmniDocuGen::DocuGen::AllMti);
                OmniDocuGen::DocuGen::AllMti->AddVerify(cg.MemberInformation);
                OmniDocuGen::Types::TreeNode n(cg.MemberInformation);
                foreach (OmniDocuGen::MemberTypeInformation::ptr_t, ti, cg.MemberInformation->Members) {
                    OmniDocuGen::DocuGen::AddTree(*ti, n);
                }
                OmniDocuGen::Types::TreeNode::AddNodes(n, OmniDocuGen::DocuGen::MtiTree);
            }
        } else {
            dotree = false;
            up("Could not find any member information in {0}", cg.SourceFile);
        }
    } else {
        sw.start();
        OmniDocuGen::DocuGen::ParseSource(OmniDocuGen::Types::SourceGenType::Normal);
        sw.stop();
        if (member.empty()) {
            up("Found {0} top level members with {1} total members in {2}s ({3}ms)",
                omni::string::to_string(OmniDocuGen::DocuGen::AllMti->GetNodeCount(false)),
                omni::string::to_string(OmniDocuGen::DocuGen::AllMti->GetNodeCount(true)),
                omni::string::to_string(omni::math::round((static_cast<double>(sw.elapsed_ms())/1000), 3)),
                omni::string::to_string(sw.elapsed_ms())
            );
        } else {
            OmniDocuGen::MemberTypeInformation::ptr_t mem = OmniDocuGen::DocuGen::AllMti->Find(member);
            if (mem) {
                pl("Member type information for " << member << ": ");
                pl(mem->ToXML());
            } else {
                pl("Member type information for " << member << " not found.");
            }
        }
    }
    if (dotree) {
        pl("Tree for Omni:" << std::endl << OmniDocuGen::DocuGen::MtiTree.GetTextTree());
    }
}

static void Run()
{
    omni::application::argparser& args = omni::application::args();
    if (args.contains("-?") || args.contains("--help") || args.contains("-h")) {
        Usage();
    } else {
        pl("Initializing");
        omni::stopwatch sw;
        sw.start();
        OmniDocuGen::DocuGen::Initialize();
        pl("");
        if (args.contains("-full")) {
            // normal mode
            Full();
        } else if (args.contains("-parser")) {
            // does the member parsing only
            Viewer();
        } else if (args.contains("-ut")) {
            // does the unit test parser/creator
            UnitTest();
        } else if (args.contains("-macro")) {
            // do macro gen
            MacroGen();
        } else if (args.contains("-api")) {
            // do sys api
            SysAPI();
        } else if (args.contains("-html")) {
            // do html highlight
            CodeToHtml();
        } else if (args.contains("-lic")) {
            // do license replacer
            LicenseReplacer();
        } else {
            pl("You must specify a mode to run.");
        }
        sw.start();
        pl("Total run time: " << sw.elapsed_ms() << "ms (" << (omni::math::round(static_cast<double>(sw.elapsed_ms())/1000, 3)) << "s)");
    }
}

static void Signal(int sig)
{
    #if defined(OMNI_WIN_API)
    if (sig == CTRL_C_EVENT)
    #else
    if (sig == SIGINT)
    #endif
    {
        up("Interupt signal received");
        OmniDocuGen::Program::StopReq = true;
    } else {
        up("Illegal signal received");
    }
    omni::application::exit();
}

int main(int argc, const char* argv[])
{
    omni::application::signal_handler::attach(&Signal);
    return omni::application::run(argc, argv, &Run, true);
}
