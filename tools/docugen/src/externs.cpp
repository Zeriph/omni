#include "docugen.hpp"

omni::sync::threadpool OmniDocuGen::Program::Tasks;
volatile bool OmniDocuGen::Program::StopReq;
volatile bool OmniDocuGen::Program::Silent;
std::string OmniDocuGen::Program::AppPath;
volatile bool OmniDocuGen::Program::SingleThreaded;
volatile uint32_t OmniDocuGen::Program::Verbosity;
volatile bool OmniDocuGen::Program::Profile;
volatile bool OmniDocuGen::Program::FullTree;
volatile uint32_t OmniDocuGen::Program::MaxMacroTheads;
volatile uint32_t OmniDocuGen::Program::MaxMtiThreads;
volatile uint32_t OmniDocuGen::Program::MaxHtmlSyntaxThreads;
OmniDocuGen::DocuSettings OmniDocuGen::Program::Settings;

std::string OmniDocuGen::OutPaths::TempOut;
std::string OmniDocuGen::OutPaths::ZipDir;
std::string OmniDocuGen::OutPaths::HtmlSrcDir;
std::string OmniDocuGen::OutPaths::ApiHtml;
std::string OmniDocuGen::OutPaths::TempApiHtml;
std::string OmniDocuGen::OutPaths::ClassIndexHtml;
std::string OmniDocuGen::OutPaths::TempClassIndexHtml;
std::string OmniDocuGen::OutPaths::FilesIndexHtml;
std::string OmniDocuGen::OutPaths::TempFilesIndexHtml;
std::string OmniDocuGen::OutPaths::HtmlSrcIndexHtml;
std::string OmniDocuGen::OutPaths::TempHtmlSrcIndexHtml;
std::string OmniDocuGen::OutPaths::OptionsIndexHtml;
std::string OmniDocuGen::OutPaths::TempOptionsIndexHtml;
std::string OmniDocuGen::OutPaths::ExampleIndexHtml;
std::string OmniDocuGen::OutPaths::TempExampleIndexHtml;

List< OmniDocuGen::CodeGen::ptr_t > OmniDocuGen::DocuGen::m_synList;
omni::sync::mutex OmniDocuGen::DocuGen::m_synLock;
volatile uint32_t OmniDocuGen::DocuGen::m_synIdx;
List< OmniDocuGen::MemberTypeInformation::ptr_t > OmniDocuGen::DocuGen::m_classList;
omni::sync::mutex OmniDocuGen::DocuGen::m_classLock;
volatile uint32_t OmniDocuGen::DocuGen::m_classIdx;
volatile bool OmniDocuGen::DocuGen::m_classRecurse;
List<OmniDocuGen::MacroOp> OmniDocuGen::DocuGen::m_macroList;
omni::sync::mutex OmniDocuGen::DocuGen::m_macroLock;
volatile uint32_t OmniDocuGen::DocuGen::m_macIdx;
List<std::string> OmniDocuGen::DocuGen::m_xml;
omni::sync::mutex OmniDocuGen::DocuGen::m_xmllock;

OmniDocuGen::MemberTypeInformation::ptr_t OmniDocuGen::DocuGen::AllMti;
OmniDocuGen::Types::TreeNode OmniDocuGen::DocuGen::MtiTree;
std::string OmniDocuGen::DocuGen::Root;
std::string OmniDocuGen::DocuGen::Files;
std::string OmniDocuGen::DocuGen::Docs;
std::string OmniDocuGen::DocuGen::HtmlSyntax;
std::string OmniDocuGen::DocuGen::FilesSource;
std::string OmniDocuGen::DocuGen::Classes;
std::string OmniDocuGen::DocuGen::Examples;
std::string OmniDocuGen::DocuGen::Options;
std::string OmniDocuGen::DocuGen::Build;
List<OmniDocuGen::MacroOp> OmniDocuGen::DocuGen::Macros;
List<OmniDocuGen::SysAPI> OmniDocuGen::DocuGen::SysAPIs;
List<std::string> OmniDocuGen::DocuGen::SourceFiles;
List<std::string> OmniDocuGen::DocuGen::HeaderFiles;
List< OmniDocuGen::CodeGen::ptr_t > OmniDocuGen::DocuGen::CodeGenList;
List< OmniDocuGen::CodeGen::ptr_t > OmniDocuGen::DocuGen::Parsables;
volatile bool OmniDocuGen::DocuGen::HasParsed;
volatile bool OmniDocuGen::DocuGen::DoClasses = true;
volatile bool OmniDocuGen::DocuGen::DoClassIndex = true;
volatile bool OmniDocuGen::DocuGen::DoMacroOptions = true;
volatile bool OmniDocuGen::DocuGen::DoFilesView = true;
volatile bool OmniDocuGen::DocuGen::DoSyntax = true;
volatile bool OmniDocuGen::DocuGen::DoAPI = true;
volatile bool OmniDocuGen::DocuGen::DoExamples = true;
volatile bool OmniDocuGen::DocuGen::DoBuildFiles = true;
volatile bool OmniDocuGen::DocuGen::DoJs = true;
volatile bool OmniDocuGen::DocuGen::DoHashZipFiles = false;

OmniDocuGen::Util::path_map OmniDocuGen::Util::m_validPaths;
List<std::string> OmniDocuGen::Util::m_validExt;
List<std::string> OmniDocuGen::Util::m_cExt;

List<std::string> OmniDocuGen::Constants::Keywords::Instructions;
List<std::string> OmniDocuGen::Constants::Keywords::Types;
List<std::string> OmniDocuGen::Constants::Keywords::Preproc;
List<std::string> OmniDocuGen::Constants::Keywords::DoxyTags;
List<std::string> OmniDocuGen::Constants::Keywords::DoxyCommentTags;

static void init_constants()
{
    OmniDocuGen::DocuGen::m_synIdx = 0;
    OmniDocuGen::DocuGen::m_classIdx = 0;
    OmniDocuGen::DocuGen::m_macIdx = 0;

    OmniDocuGen::Util::m_validExt.push_back(".hpp");
    OmniDocuGen::Util::m_validExt.push_back(".hxx");
    OmniDocuGen::Util::m_validExt.push_back(".cpp");
    OmniDocuGen::Util::m_validExt.push_back(".cxx");

    OmniDocuGen::Util::m_cExt.push_back(".hpp");
    OmniDocuGen::Util::m_cExt.push_back(".h");
    OmniDocuGen::Util::m_cExt.push_back(".hxx");
    OmniDocuGen::Util::m_cExt.push_back(".cpp");
    OmniDocuGen::Util::m_cExt.push_back(".c");
    OmniDocuGen::Util::m_cExt.push_back(".cxx");

    OmniDocuGen::Util::m_validPaths["@"] = "@40"; // this first
    //OmniDocuGen::Util::m_validPaths["_"] = "@5F"; // don't replace underscores
    OmniDocuGen::Util::m_validPaths["::"] = "-"; //"_sp_";
    OmniDocuGen::Util::m_validPaths[" "] = "@20"; //"_sp_";
    OmniDocuGen::Util::m_validPaths["!"] = "@21"; //"_ex_";
    OmniDocuGen::Util::m_validPaths["%"] = "@25"; //"_pct_";
    OmniDocuGen::Util::m_validPaths["&"] = "@26"; //"_amp_";
    OmniDocuGen::Util::m_validPaths["("] = "@28"; //"_po_";
    OmniDocuGen::Util::m_validPaths[")"] = "@29"; //"_pc_";
    OmniDocuGen::Util::m_validPaths["*"] = "@2A"; //"_star_")
    OmniDocuGen::Util::m_validPaths["+"] = "@2B"; //"_pls_";
    OmniDocuGen::Util::m_validPaths[","] = "@2C"; //"_cma_";
    OmniDocuGen::Util::m_validPaths["-"] = "@2D"; //"_min_";
    //OmniDocuGen::Util::m_validPaths[":"] = "@3A"; //"_cln_";
    OmniDocuGen::Util::m_validPaths["<"] = "@3C"; //"_lt_";
    OmniDocuGen::Util::m_validPaths["="] = "@3D"; //"_eq_";
    OmniDocuGen::Util::m_validPaths[">"] = "@3E"; //"_gt_";
    OmniDocuGen::Util::m_validPaths["["] = "@5B"; //"_bo_";
    OmniDocuGen::Util::m_validPaths["]"] = "@5D"; //"_bc_";
    OmniDocuGen::Util::m_validPaths["~"] = "@7E"; //"_tld_";
    OmniDocuGen::Util::m_validPaths["\""] = "@22";
    OmniDocuGen::Util::m_validPaths["#"] = "@23";
    OmniDocuGen::Util::m_validPaths["$"] = "@24";
    OmniDocuGen::Util::m_validPaths["'"] = "@27";
    OmniDocuGen::Util::m_validPaths["."] = "@2E";
    OmniDocuGen::Util::m_validPaths["/"] = "@2F";
    OmniDocuGen::Util::m_validPaths["?"] = "@3F";
    OmniDocuGen::Util::m_validPaths["\\"] = "@5C";
    OmniDocuGen::Util::m_validPaths["^"] = "@5E";
    OmniDocuGen::Util::m_validPaths["`"] = "@60";
    OmniDocuGen::Util::m_validPaths["{"] = "@7B";
    OmniDocuGen::Util::m_validPaths["|"] = "@7C";
    OmniDocuGen::Util::m_validPaths["}"] = "@7D";
}

static void init_keywords()
{
    OmniDocuGen::Constants::Keywords::Instructions = OmniDocuGen::Util::Split(OmniDocuGen::Program::Settings.KeywordInstructions, ",");
    OmniDocuGen::Constants::Keywords::Types = OmniDocuGen::Util::Split(OmniDocuGen::Program::Settings.KeywordTypes, ",");
    OmniDocuGen::Constants::Keywords::Preproc = OmniDocuGen::Util::Split(OmniDocuGen::Program::Settings.KeywordPreproc, ",");
    OmniDocuGen::Constants::Keywords::DoxyTags = OmniDocuGen::Util::Split(OmniDocuGen::Program::Settings.KeywordDoxyTags, ",");
    OmniDocuGen::Constants::Keywords::DoxyCommentTags = OmniDocuGen::Util::Split(OmniDocuGen::Program::Settings.KeywordDoxyCommentTags, ",");
    
    // NOTE: 'class' MUST go first .. this is to ensure any replacements of 'class' aren't confused with <font class>
    // stupid hack, I know .. but whatever, this is a stupid tool that gets the job done in seconds, so boo to you!
    if (OmniDocuGen::Constants::Keywords::Types.size() > 0 && OmniDocuGen::Constants::Keywords::Types[0] != "class") {
        List<std::string>::iterator f = std::find(OmniDocuGen::Constants::Keywords::Types.begin(), OmniDocuGen::Constants::Keywords::Types.end(), "class");
        if (f != OmniDocuGen::Constants::Keywords::Types.end()) {
            OmniDocuGen::Constants::Keywords::Types.erase(f);
        }
        OmniDocuGen::Constants::Keywords::Types.insert(OmniDocuGen::Constants::Keywords::Types.begin(), "class");
    }
}

/// Initialize the global ('output') variables and macros
/// <param name="macdir"></param>
void OmniDocuGen::DocuGen::Initialize()
{
    init_constants();
    uint64_t procs = omni::system::processors();
    uint32_t p2 = procs * 2;
    omni::application::argparser& args = omni::application::args();
    std::string settings = args["-settings"];
    OmniDocuGen::Program::AppPath = omni::system::cwd(); // Application.ExecutablePath.Substring(0, Application.ExecutablePath.LastIndexOf(OMNI_PATH_SEPARATOR));
    
    if (settings.empty() || !omni::io::file::exists(settings)) {
        settings = omni::io::path::combine(OmniDocuGen::Program::AppPath, "OmniDocuGen.settings");
    }
    OmniDocuGen::Program::Settings.Load(settings);
    init_keywords();
    OmniDocuGen::Program::Silent = args.contains("-silent");
    OmniDocuGen::Program::SingleThreaded = args.contains("-singlethread");
    OmniDocuGen::Program::Profile = args.contains("-profile");
    OmniDocuGen::Program::FullTree = args.contains("-fulltree");
    if (args.contains("-debug")) {
        OmniDocuGen::Program::Verbosity = 255;
    } else if (args.contains("-v")) {
        OmniDocuGen::Program::Verbosity = args.get_switch_count("-v");
    } else {
        OmniDocuGen::Program::Verbosity = 0;
    }
    if (procs > 2) {
        size_t cnt = (omni::string::is_numeric(args["-maxpool"]) ? omni::string::util::to_type<uint32_t>(args["-maxpool"]) : procs);
        if (cnt > (procs * 4)) {
            up("WARNING! Using more threads than your CPU can handle could cause issues.");
        }
        OmniDocuGen::Program::Tasks.set_min_threads(cnt);
        OmniDocuGen::Program::Tasks.set_max_threads(cnt);
    } else {
        OmniDocuGen::Program::Tasks.set_max_threads(2);
        OmniDocuGen::Program::Tasks.set_min_threads(2);
    }
    
    OmniDocuGen::Program::MaxMacroTheads = (omni::string::is_numeric(args["-maxmacrothreads"]) ? omni::string::util::to_type<uint32_t>(args["-maxmacrothreads"]) : p2);
    OmniDocuGen::Program::MaxMtiThreads = (omni::string::is_numeric(args["-maxmtithreads"]) ? omni::string::util::to_type<uint32_t>(args["-maxmtithreads"]) : p2);
    OmniDocuGen::Program::MaxHtmlSyntaxThreads = (omni::string::is_numeric(args["-maxsyntaxthreads"]) ? omni::string::util::to_type<uint32_t>(args["-maxsyntaxthreads"]) : p2);
    
    OmniDocuGen::DocuGen::AllMti.reset();
    OmniDocuGen::DocuGen::MtiTree.SetRoot(OmniDocuGen::DocuGen::AllMti);
    OmniDocuGen::DocuGen::HasParsed = false;
    OmniDocuGen::DocuGen::SourceFiles.clear();
    OmniDocuGen::DocuGen::HeaderFiles.clear();
    OmniDocuGen::DocuGen::CodeGenList.clear();
    OmniDocuGen::DocuGen::Parsables.clear();

    if (args.contains("-SourceDirectory")) { OmniDocuGen::Program::Settings.SourceDirectory = args["-SourceDirectory"]; }
    if (args.contains("-ExampleDirectory")) { OmniDocuGen::Program::Settings.ExampleDirectory = args["-ExampleDirectory"]; }
    if (args.contains("-OutputDirectory")) { OmniDocuGen::Program::Settings.OutputDirectory = args["-OutputDirectory"]; }
    if (args.contains("-UnitTestDirectory")) { OmniDocuGen::Program::Settings.UnitTestDirectory = args["-UnitTestDirectory"]; }
    if (args.contains("-PrevZipDirectory")) { OmniDocuGen::Program::Settings.PrevZipDirectory = args["-PrevZipDirectory"]; }
    if (args.contains("-MacroDirectory")) { OmniDocuGen::Program::Settings.MacroDirectory = args["-MacroDirectory"]; }
    if (args.contains("-SystemAPIDirectory")) { OmniDocuGen::Program::Settings.SystemAPIDirectory = args["-SystemAPIDirectory"]; }
    if (args.contains("-LicenseFile")) { OmniDocuGen::Program::Settings.LicenseFile = args["-LicenseFile"]; }
    if (args.contains("-TemplateDirectory")) { OmniDocuGen::Program::Settings.TemplateDirectory = args["-TemplateDirectory"]; }
    if (args.contains("-TempZipDirectory")) { OmniDocuGen::Program::Settings.TempZipDirectory = args["-TempZipDirectory"]; }
    if (args.contains("-Excluded")) { OmniDocuGen::Program::Settings.Excluded = args["-Excluded"]; }
    if (args.contains("-NoParse")) { OmniDocuGen::Program::Settings.NoParse = args["-NoParse"]; }

    OmniDocuGen::DocuGen::Root = OmniDocuGen::Program::Settings.OutputDirectory;
    OmniDocuGen::DocuGen::Files = omni::io::path::combine(OmniDocuGen::DocuGen::Root, "files");
    OmniDocuGen::DocuGen::Docs = omni::io::path::combine(OmniDocuGen::DocuGen::Root, "docs");
    OmniDocuGen::DocuGen::FilesSource = omni::io::path::combine(OmniDocuGen::DocuGen::Files, "src");
    OmniDocuGen::DocuGen::HtmlSyntax = omni::io::path::combine(OmniDocuGen::DocuGen::Docs, "htmlsrc");
    OmniDocuGen::DocuGen::Classes = omni::io::path::combine(OmniDocuGen::DocuGen::Docs, "classes");
    OmniDocuGen::DocuGen::Examples = omni::io::path::combine(OmniDocuGen::DocuGen::Docs, "examples");
    OmniDocuGen::DocuGen::Options = omni::io::path::combine(OmniDocuGen::DocuGen::Docs, "options");
    OmniDocuGen::DocuGen::Build = omni::io::path::combine(OmniDocuGen::DocuGen::Docs, "build");

    if (!omni::string::ends_with(OmniDocuGen::DocuGen::FilesSource, OMNI_PATH_SEPARATOR)) {
        OmniDocuGen::DocuGen::FilesSource += OMNI_PATH_SEPARATOR;
    }
    std::string root = OmniDocuGen::DocuGen::Root;
    std::string docs = OmniDocuGen::DocuGen::Docs;
    std::string files = OmniDocuGen::DocuGen::Files;
    if (!omni::string::ends_with(root, OMNI_PATH_SEPARATOR)) { root += OMNI_PATH_SEPARATOR; }
    if (!omni::string::ends_with(docs, OMNI_PATH_SEPARATOR)) { docs += OMNI_PATH_SEPARATOR; }
    if (!omni::string::ends_with(files, OMNI_PATH_SEPARATOR)) { files += OMNI_PATH_SEPARATOR; }

    up(1, "Initialized root paths.");

    OmniDocuGen::OutPaths::TempOut = omni::io::path::combine(OmniDocuGen::Program::Settings.TempZipDirectory, "help") + OMNI_PATH_SEPARATOR;
    OmniDocuGen::OutPaths::ZipDir = omni::io::path::combine(OmniDocuGen::Program::Settings.TempZipDirectory, "zips") + OMNI_PATH_SEPARATOR;
    OmniDocuGen::OutPaths::HtmlSrcDir = omni::io::path::combine(docs, "htmlsrc");

    OmniDocuGen::OutPaths::ApiHtml = omni::io::path::combine(docs, "api.html");
    OmniDocuGen::OutPaths::TempApiHtml = omni::string::replace(OmniDocuGen::OutPaths::ApiHtml, root, OmniDocuGen::OutPaths::TempOut);

    OmniDocuGen::OutPaths::ClassIndexHtml = omni::io::path::combine(OmniDocuGen::DocuGen::Classes, "index.html");
    OmniDocuGen::OutPaths::TempClassIndexHtml = omni::string::replace(OmniDocuGen::OutPaths::ClassIndexHtml, root, OmniDocuGen::OutPaths::TempOut);

    OmniDocuGen::OutPaths::FilesIndexHtml = omni::io::path::combine(files, "index.html");
    OmniDocuGen::OutPaths::TempFilesIndexHtml = omni::string::replace(OmniDocuGen::OutPaths::FilesIndexHtml, root, OmniDocuGen::OutPaths::TempOut);

    OmniDocuGen::OutPaths::HtmlSrcIndexHtml = omni::io::path::combine(OmniDocuGen::OutPaths::HtmlSrcDir, "index.html");
    OmniDocuGen::OutPaths::TempHtmlSrcIndexHtml = omni::string::replace(OmniDocuGen::OutPaths::HtmlSrcIndexHtml, root, OmniDocuGen::OutPaths::TempOut);

    OmniDocuGen::OutPaths::OptionsIndexHtml = omni::io::path::combine(OmniDocuGen::DocuGen::Options, "index.html");
    OmniDocuGen::OutPaths::TempOptionsIndexHtml = omni::string::replace(OmniDocuGen::OutPaths::OptionsIndexHtml, root, OmniDocuGen::OutPaths::TempOut);

    OmniDocuGen::OutPaths::ExampleIndexHtml = omni::io::path::combine(OmniDocuGen::DocuGen::Examples, "index.html");
    OmniDocuGen::OutPaths::TempExampleIndexHtml = omni::string::replace(OmniDocuGen::OutPaths::ExampleIndexHtml, root, OmniDocuGen::OutPaths::TempOut);

    up(1, "Initialized output paths.");

    up(2, "Program settings:\n"
        "Verbosity: {0}\n"
        "Max Macro Threads: {1}\n"
        "Max MTI Threads: {2}\n"
        "Max Syntax Threads: {3}\n"
        "Single threaded: {4}\n"
        "Profile mode: {5}\n"
        "Display full tre: {6}\n",
        omni::string::to_string(OmniDocuGen::Program::Verbosity),
        omni::string::to_string(OmniDocuGen::Program::MaxMacroTheads),
        omni::string::to_string(OmniDocuGen::Program::MaxMtiThreads),
        omni::string::to_string(OmniDocuGen::Program::MaxHtmlSyntaxThreads),
        (OmniDocuGen::Program::SingleThreaded ? "yes" : "no"),
        (OmniDocuGen::Program::Profile ? "yes" : "no"),
        (OmniDocuGen::Program::FullTree ? "yes" : "no")
    );

    up(2, "Root paths:\n"
        "Root: {0}\n"
        "Files: {1}\n"
        "Docs: {2}\n"
        "FilesSource: {3}\n"
        "HtmlSyntax: {4}\n"
        "Classes: {5}\n"
        "Examples: {6}\n"
        "Options: {7}\n"
        "Build: {8}\n",
        OmniDocuGen::DocuGen::Root,
        OmniDocuGen::DocuGen::Files,
        OmniDocuGen::DocuGen::Docs,
        OmniDocuGen::DocuGen::FilesSource,
        OmniDocuGen::DocuGen::HtmlSyntax,
        OmniDocuGen::DocuGen::Classes,
        OmniDocuGen::DocuGen::Examples,
        OmniDocuGen::DocuGen::Options,
        OmniDocuGen::DocuGen::Build
    );
    
    up(2, "Output paths:\n"
        "TempOut: {0}\n"
        "ZipDir: {1}\n"
        "HtmlSrcDir: {2}\n"
        "ApiHtml: {3}\n"
        "TempApiHtml: {4}\n"
        "ClassIndexHtml: {5}\n"
        "TempClassIndexHtml: {6}\n"
        "FilesIndexHtml: {7}\n"
        "TempFilesIndexHtml: {8}\n"
        "HtmlSrcIndexHtml: {9}\n"
        "TempHtmlSrcIndexHtml: {10}\n"
        "OptionsIndexHtml: {11}\n"
        "TempOptionsIndexHtml: {12}\n"
        "ExampleIndexHtml: {13}\n"
        "TempExampleIndexHtml: {14}\n"
        "UnitTestDirectory: {15}\n",
        OmniDocuGen::OutPaths::TempOut,
        OmniDocuGen::OutPaths::ZipDir,
        OmniDocuGen::OutPaths::HtmlSrcDir,
        OmniDocuGen::OutPaths::ApiHtml,
        OmniDocuGen::OutPaths::TempApiHtml,
        OmniDocuGen::OutPaths::ClassIndexHtml,
        OmniDocuGen::OutPaths::TempClassIndexHtml,
        OmniDocuGen::OutPaths::FilesIndexHtml,
        OmniDocuGen::OutPaths::TempFilesIndexHtml,
        OmniDocuGen::OutPaths::HtmlSrcIndexHtml,
        OmniDocuGen::OutPaths::TempHtmlSrcIndexHtml,
        OmniDocuGen::OutPaths::OptionsIndexHtml,
        OmniDocuGen::OutPaths::TempOptionsIndexHtml,
        OmniDocuGen::OutPaths::ExampleIndexHtml,
        OmniDocuGen::OutPaths::TempExampleIndexHtml,
        OmniDocuGen::Program::Settings.UnitTestDirectory
    );
}

void OmniDocuGen::CodeGen::_Initialize(const std::string& srcFile)
{
    std::string nsrc = omni::string::replace(srcFile, OmniDocuGen::Program::Settings.SourceDirectory, "");
    this->SourceFile = srcFile;
    this->HtmlSyntaxFile = omni::io::path::combine(OmniDocuGen::DocuGen::HtmlSyntax, nsrc) + std::string(".html");
    try {
        this->_RawCode = OmniDocuGen::Util::NormalizeEndings(omni::io::file::get_contents(this->SourceFile));
        this->_CodeNoCommnet = OmniDocuGen::Util::StripComment(this->_RawCode);
    } catch (const std::exception& ex) {
        OmniDocuGen::Program::AddError(ex);
    }
}

/// Generates the class type information based on the code read from the source file
void OmniDocuGen::CodeGen::_GenerateTypeInformation()
{
    if ((omni::string::contains(this->_RawCode, "namespace") || omni::string::contains(this->_RawCode, "class")) &&
            omni::string::contains(this->_RawCode, "{") && omni::string::contains(this->_RawCode, "}"))
    {
        up(2, "Parsing member type information from {0} bytes in {1}", omni::string::to_string(this->_RawCode.size()), this->Name());
        this->MemberInformation = new MemberTypeInformation(this->_RawCode, this->SourceFile, this->SourceFile, this->_CodeNoCommnet);
    } else {
        up(1, "No parsable code found, skipping '{0}'", this->Name());
    }
}

/// Generates the class type information based on the code read from the source file
void OmniDocuGen::CodeGen::_GenerateSoureTypeInfo()
{
    up(2, "Parsing source file {0}", this->SourceFile);
    OmniDocuGen::MemberTypeInformation::ptr_t empty;
    this->MemberInformation = new MemberTypeInformation(this->_RawCode, empty, OmniDocuGen::Types::MemberParseType::AsSource);
    this->MemberInformation->SetOwnerInfoAndLinkIndex(this->SourceFile, "", this->_CodeNoCommnet);
    this->MemberInformation->LinkSources(DocuGen::AllMti);
    // no 'GeneratedNode' here as this is a source file
}

/// Generates the class type information based on the code read from the source file
void OmniDocuGen::CodeGen::_GenerateSpecialTypeInfo()
{
    std::string fname = omni::io::path::get_name(this->SourceFile);
    up(2, "Generating special type info for {0}", this->SourceFile);
    MemberTypeInformation::ptr_t omni = MemberTypeInformation::GetOmni(false);
    if (fname == "string.hxx") {
        // // namespace omni::string/cstring/wstring {
        // // } namespace omni::string/cstring/wstring
        std::string csrc = this->_RawCode;
        std::string nso = "// namespace omni::string/cstring/wstring {";
        std::string nsc = "// } namespace omni::string/cstring/wstring";
        std::string ccode = omni::string::replace(omni::string::replace(csrc, nso, "namespace omni {\r\nnamespace cstring {\r\n"), nsc, "}\r\n}");
        std::string wcode = omni::string::replace(omni::string::replace(csrc, nso, "namespace omni {\r\nnamespace wstring {\r\n"), nsc, "}\r\n}");
        
        // NOTE: is this needed?
        //std::string scode = omni::string::replace(omni::string::replace(csrc, nso, "namespace omni {\r\nnamespace string {\r\n"), nsc, "}\r\n}");
        ccode = omni::string::replace_all(omni::string::replace_all(ccode, "OMNI_STRING_T_FW", "std::string"), "OMNI_CHAR_T_FW", "char");
        wcode = omni::string::replace_all(omni::string::replace_all(wcode, "OMNI_STRING_T_FW", "std::wstring"), "OMNI_CHAR_T_FW", "wchar_t");

        MemberTypeInformation::ptr_t cstr(new MemberTypeInformation(ccode, this->SourceFile, this->SourceFile, ccode, OmniDocuGen::DocuGen::AllMti));
        MemberTypeInformation::ptr_t wstr(new MemberTypeInformation(wcode, this->SourceFile, this->SourceFile, wcode, OmniDocuGen::DocuGen::AllMti));
        //MemberTypeInformation::ptr_t sstr(new MemberTypeInformation(scode, this->SourceFile, this->SourceFile, scode, OmniDocuGen::DocuGen::AllMti));

        omni->Add(cstr);
        omni->Add(wstr);
        //omni->Add(sstr);

    } else if (fname == "ext_const.hxx") {
        omni = new MemberTypeInformation();
    } else if (fname == "const.hxx") {
        // // namespace omni::consts/cconsts/wconsts {
        // // } namespace omni::consts/cconsts/wconsts
        // OMNI_EXTERN OMNI_CHAR_T_FW DELEGATE_NOT_FOUND[] OMNI_EXT_ASSN_FW(= OMNI_STRW_FW("Delegate not found"));
        std::string csrc = omni::string::replace_all(omni::string::replace_all(this->RawSourceCode(), "OMNI_EXT_ASSN_FW(", std::string()), "));", ");");
        std::string nso = "// namespace omni::consts/cconsts/wconsts {";
        std::string nsc = "// } namespace omni::consts/cconsts/wconsts";
        std::string ccode = omni::string::replace_all(omni::string::replace_all(csrc, nso, "namespace omni {\r\nnamespace cconsts {\r\n"), nsc, "}\r\n}");
        std::string wcode = omni::string::replace_all(omni::string::replace_all(csrc, nso, "namespace omni {\r\nnamespace wconsts {\r\n"), nsc, "}\r\n}");
        ccode = omni::string::replace_all(omni::string::replace_all(omni::string::replace_all(ccode, "OMNI_STRW_FW(", std::string()), ");", ";"), "OMNI_CHAR_T_FW", "char");
        wcode = omni::string::replace_all(omni::string::replace_all(omni::string::replace_all(wcode, "OMNI_STRW_FW(", "L"), ");", ";"), "OMNI_CHAR_T_FW", "wchar_t");
        MemberTypeInformation::ptr_t cstr(new MemberTypeInformation(ccode, this->SourceFile, this->SourceFile, ccode, OmniDocuGen::DocuGen::AllMti));
        MemberTypeInformation::ptr_t wstr(new MemberTypeInformation(wcode, this->SourceFile, this->SourceFile, wcode, OmniDocuGen::DocuGen::AllMti));

        omni->Add(cstr);
        omni->Add(wstr);
    }
    this->MemberInformation = omni;
}

List<std::string> OmniDocuGen::CommentInformation::HtmlList() const
{
    List<std::string> ret;
    List<std::string> vals;
    try {
        // note: don't add complexity here
        vals.push_back(this->Synopsis);
        vals.push_back(this->_paramHtml);
        vals.push_back(this->Description);
        vals.push_back(this->Example);
        vals.push_back(this->ReturnValue);
        vals.push_back(this->Errors);
        vals.push_back(this->Considerations);
        vals.push_back(this->PlatformSpecific);
        vals.push_back(this->Notes);

        const std::string odocbeg = "@omni_docugen|";
        size_t idx = 0; // all.find(ooe);
        size_t len = odocbeg.size();
        std::string ooe = "|negucod_inmo@";
        std::string all = "";
        //std::string docdiv = "<div class=\"docdiv\"><a name=\"{0}\"></a>\r\n<font class=\"docu\">{1}</font><br><br>\r\n{2}\r\n<br><br><a class=\"toppg\" href=\"#topopage\">top</a>\r\n</div><br>\r\n";
        List<std::string> docdivs;
        docdivs.push_back("<div class=\"docdiv\"><a name=\"");
        docdivs.push_back("\"></a>\r\n<font class=\"docu\">");
        docdivs.push_back("</font><br><br>\r\n");
        docdivs.push_back("\r\n<br><br><a class=\"toppg\" href=\"#topopage\">top</a>\r\n</div><br>\r\n<br>\r\n");
        
        for (int32_t i = 0; i < vals.size(); ++i) {
            if (OmniDocuGen::Program::StopReq) { return ret; }
            if (!vals[i].empty()) {
                // replace_all(vals[i], 
                vals[i] = omni::string::replace_all(vals[i], "\r\n\r\n", "@omniPara@");
                vals[i] = omni::string::replace_all(vals[i], "\r\n", " ");
                vals[i] = omni::string::trim(omni::string::replace_all(vals[i], "@omniPara@", "\r\n\r\n"));
            }
            all += Util::Format("@omni_docugen|{0} |negucod_inmo@", vals[i]);
        }

        //all = std::string.Format("@omni_docugen|{0} |negucod_inmo@@omni_docugen|{1} |negucod_inmo@@omni_docugen|{2} |negucod_inmo@@omni_docugen|{3} |negucod_inmo@@omni_docugen|{4} |negucod_inmo@@omni_docugen|{5} |negucod_inmo@@omni_docugen|{6} |negucod_inmo@@omni_docugen|{7} |negucod_inmo@@omni_docugen|{8} |negucod_inmo@", this->Synopsis, this->_paramHtml, this->Description, this->Example, this->ReturnValue, this->Errors, this->Considerations, this->PlatformSpecific, this->Notes);
        all = OmniDocuGen::DocuGen::ReplaceFrameworkInfo(all, "", "../options/", "../");

        vals.clear();
        while ((idx = all.find(ooe)) != std::string::npos) {
            if (OmniDocuGen::Program::StopReq) { return ret; }
            vals.push_back(all.substr(len, (idx - len)));
            all = all.substr(idx + ooe.length());
        }
        while (vals.size() < 10) {
            vals.push_back(""); // complexity
        }
        // parameters
        if (this->Parameters.size() > 0) {
            try {
                std::string tmp = "";
                List<std::string> splits = OmniDocuGen::Util::SplitAtEndings(vals[1]);
                foreach (std::string, it, splits) {
                    if (OmniDocuGen::Program::StopReq) { return ret; }
                    tmp += *it + "<br>\r\n";
                }
                //vals[1] = std::string.Format(docdiv, "param", "PARAMETERS", tmp.substr(0, tmp.length() - 6));
                vals[1] = docdivs[0] + "param" + docdivs[1] + "PARAMETERS" + docdivs[2] + tmp.substr(0, tmp.length() - 6) + docdivs[3];
            } catch (const std::exception& iex) {
                Program::AddError(iex, "Paramaters");
            }
        }
        // syntax highlight the 'example' section (black and white is so passe)
        if (!this->Example.empty()) {
            std::string vvv = OmniDocuGen::DocuGen::GenerateHtmlSyntaxHighlight(this->Example, "../", "../", OmniDocuGen::DocuGen::AllMti, false);
            std::string extmp = Util::Format("<div class=\"sntx\"><input type=\"checkbox\" id=\"c0\" name=\"c0\" checked /><label for=\"c0\"> example</label>\r\n<pre>{0}</pre>\r\n</div>Visit the <a href=\"../examples/index.html\">examples</a> page for more.\r\n", vvv);
            //vals[3] = std::string.Format(omni::string::replace_all(docdiv, "{1}</font><br><br>", "{1}</font><br>"), "ex", "EXAMPLE", extmp);
            vals[3] = docdivs[0] + "ex" + docdivs[1] + "EXAMPLE" + docdivs[2] + extmp + docdivs[3];
        }
        if (!this->ReturnValue.empty()) {
            //vals[4] = std::string.Format(docdiv, "ret", "RETURN VALUES", vals[4]);
            vals[4] = docdivs[0] + "ret" + docdivs[1] + "RETURN VALUES" + docdivs[2] + vals[4] + docdivs[3];
        }
        if (!this->Errors.empty()) {
            //vals[5] = std::string.Format(docdiv, "err", "ERRORS", vals[5]);
            vals[5] = docdivs[0] + "err" + docdivs[1] + "ERRORS" + docdivs[2] + vals[5] + docdivs[3];
        }
        if (!this->Considerations.empty()) {
            //vals[6] = std::string.Format(docdiv, "con", "CONSIDERATIONS", vals[6]);
            vals[6] = docdivs[0] + "con" + docdivs[1] + "CONSIDERATIONS" + docdivs[2] + vals[6] + docdivs[3];
        }
        if (!this->PlatformSpecific.empty()) {
            //vals[7] = std::string.Format(docdiv, "pspec", "PLATFORM SPECIFIC", vals[7]);
            vals[7] = docdivs[0] + "pspec" + docdivs[1] + "PLATFORM SPECIFIC" + docdivs[2] + vals[7] + docdivs[3];
        }
        if (!this->Notes.empty()) {
            //vals[8] = std::string.Format(docdiv, "notes", "NOTES", vals[8]);
            vals[8] = docdivs[0] + "notes" + docdivs[1] + "NOTES" + docdivs[2] + vals[8] + docdivs[3];
        }
        if (!this->Complexity.empty()) {
            //vals[9] = std::string.Format(docdiv, "complexity", "COMPLEXITY", vals[9]);
            vals[9] = docdivs[0] + "complexity" + docdivs[1] + "COMPLEXITY" + docdivs[2] + vals[9] + docdivs[3];
        }

        ret.push_back(vals[0]); // {4} - synopsis (@brief)
        ret.push_back(vals[2]); // {5} - desc (@details)
        ret.push_back(vals[1]); // {6} - params (if any) (@param/@tparam)
        ret.push_back(vals[3]); // {7} - example
        ret.push_back(vals[4]); // {8} - return (if any) (@return)
        ret.push_back(vals[5]); // {9} - error (if any) (@exception)
        ret.push_back(vals[6]); // {10} - consider (if any) (@warning)
        ret.push_back(vals[7]); // {11} - platform (if any) (@attention)
        ret.push_back(vals[8]); // {12} - notes (if any) (@note)
        ret.push_back(vals[9]); // {13} - complexity (if any) (@invariant)
    } catch (const std::exception& ex) {
        OmniDocuGen::Program::AddError(ex, __FUNCTION__);
    }
    return ret;
}

std::string OmniDocuGen::FrameworkExample::LiHtml()
{
    std::string dg = OmniDocuGen::DocuGen::ReplaceFrameworkInfo(this->Brief, "../classes/", "../options/", "../");
    return OmniDocuGen::Util::Format("<a href=\"{0}\"><font class=\"hdr\">{1}</font></a><br>{2}<br><br>", this->HtmlFile, this->Name, dg);
}

std::string OmniDocuGen::FrameworkExample::ToHTML()
{
    std::string dets = this->Details;
    List<std::string> ctags;
    if (omni::string::contains(dets, "@code")) {
        dets = omni::string::replace_all(omni::string::replace_all(dets, "\r\n\r\n@code", "\r\n@code"), "@code\r\n\r\n", "@code");
        List<int> idxs = OmniDocuGen::Util::IndexesOf(dets, "@code");
        for (int32_t x = 0; x < idxs.size(); x += 2) {
            if (OmniDocuGen::Program::StopReq) { return ""; }
            ctags.push_back(dets.substr(idxs[x], (idxs[x + 1] - idxs[x]) + 5));
        }
        for (int32_t x = 0; x < ctags.size(); ++x) {
            if (OmniDocuGen::Program::StopReq) { return ""; }
            dets = omni::string::replace_all(dets, ctags[x], (std::string("@code") + omni::string::to_string(x) + std::string(" ")));
        }
    }
    dets = OmniDocuGen::DocuGen::ReplaceFrameworkInfo(dets, "../classes/", "../options/", "../");
    int32_t excnt = 0;
    std::string dghtml;
    std::string fmt = "<div class=\"sntx\"><input type=\"checkbox\" id=\"c{0}\" name=\"c{0}\" /><label for=\"c{0}\">&nbsp;</label><pre>{1}</pre></div>";
    for (int32_t x = 0; x < ctags.size(); ++x) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        dghtml = omni::string::trim(omni::string::replace_all(ctags[x], "@code", ""));
        try {
            dghtml = OmniDocuGen::DocuGen::GenerateHtmlSyntaxHighlight(dghtml, "../", "../", OmniDocuGen::DocuGen::AllMti, false);
        } catch (const std::exception& ex) {
            Program::AddError(ex, Util::Format("Error for @code #{0}, in {1}", omni::string::to_string(excnt+1), this->Name));
        }
        dets = omni::string::replace_all(dets,
            (std::string("@code") + omni::string::to_string(x) + std::string(" ")),
            OmniDocuGen::Util::Format(fmt, omni::string::to_string(excnt), dghtml)
        );
        ++excnt;
    }
    dghtml = OmniDocuGen::DocuGen::GenerateHtmlSyntaxHighlight(this->Example, "../", "../", OmniDocuGen::DocuGen::AllMti, false);
    dets += OmniDocuGen::Util::Format(
        "<br><br><font class=\"hdr\">Example</font><br><div class=\"sntx\"><input type=\"checkbox\" id=\"c{0}\" name=\"c{0}\" checked /><label for=\"c{0}\">&nbsp;</label><pre>{1}</pre></div>",
        omni::string::to_string(excnt), dghtml
    );
    return OmniDocuGen::Util::Format(OmniDocuGen::Program::Settings.HtmlExamples, this->Name, dets);
}

std::string OmniDocuGen::MacroOp::LiHtmlString() const
{
    std::string b = OmniDocuGen::DocuGen::ReplaceFrameworkInfo(this->Brief, "../classes/", "", "../");
    return std::string("    <li><code><a href=\"") +
            omni::string::to_lower(this->Name) +
            ".html\">" +
            this->Name +
            "</a></code> - " +
            b +
            "</li>";
}

std::string OmniDocuGen::MacroOp::ToHTML() const
{
    size_t idx = 0; // all.find(ooe);
    size_t len = std::string("@omni_docugen|").size();
    std::string ooe = "|negucod_inmo@";

    List<std::string> afmt;
    afmt.push_back("@omni_docugen|");
    afmt.push_back(" |negucod_inmo@@omni_docugen|");
    afmt.push_back(" |negucod_inmo@@omni_docugen|");
    afmt.push_back(" |negucod_inmo@@omni_docugen|");
    afmt.push_back(" |negucod_inmo@@omni_docugen|");
    afmt.push_back(" |negucod_inmo@@omni_docugen|");
    afmt.push_back(" |negucod_inmo@");
    
    List<std::string> vals;
    vals.push_back(this->Name);
    vals.push_back(this->Brief);
    vals.push_back(this->Synopsis);
    vals.push_back(this->Description);
    vals.push_back(this->Considerations);
    vals.push_back(this->PlatformSpecific);
    vals.push_back(this->Notes);
    
    List< List<std::string> > ctags;
    for (int i = 1; i <= 6; ++i) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        vals[i] = omni::string::trim(vals[i]);
        ctags.push_back( List<std::string>() );
        if (omni::string::contains(vals[i], "@code")) {
            vals[i] = omni::string::replace_all(omni::string::replace_all(vals[i], "\r\n\r\n@code", "\r\n@code"), "@code\r\n\r\n", "@code");
            List<int> idxs = OmniDocuGen::Util::IndexesOf(vals[i], "@code");
            for (size_t x = 0; x < idxs.size(); x += 2) {
                if (OmniDocuGen::Program::StopReq) { return ""; }
                ctags[i - 1].push_back(vals[i].substr(idxs[x], (idxs[x + 1] - idxs[x]) + 5));
            }
            for (int x = 0; x < ctags[i - 1].size(); ++x) {
                if (OmniDocuGen::Program::StopReq) { return ""; }
                vals[i] = omni::string::replace_all(vals[i], ctags[i - 1][x], (std::string("@code") + omni::string::to_string(x) + std::string(" ")));
            }
        }
    }
    std::string fmtd = afmt[0] + vals[1] + afmt[1] + vals[2] + afmt[2] + vals[3] + afmt[3] + vals[4] + afmt[4] + vals[5] + afmt[5] + vals[6] + afmt[6];
    std::string all = OmniDocuGen::DocuGen::ReplaceFrameworkInfo(fmtd, "../classes/", std::string(), "../");
    int excnt = 0;
    std::string strexcnt, dghtml, repval;
    for (int i = 1; i <= 6; ++i) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        idx = all.find(ooe);
        vals[i] = all.substr(len, (idx - len));
        for (int x = 0; x < ctags[i - 1].size(); ++x) {
            if (OmniDocuGen::Program::StopReq) { return ""; }
            strexcnt = omni::string::to_string(excnt);
            dghtml = OmniDocuGen::DocuGen::GenerateHtmlSyntaxHighlight(omni::string::trim(omni::string::replace_all(ctags[i - 1][x], "@code", "")), "../", "../", OmniDocuGen::DocuGen::AllMti, false);
            repval = std::string("<div class=\"sntx\"><input type=\"checkbox\" id=\"c") + strexcnt + std::string("\" name=\"c") +
                        strexcnt + std::string("\" checked /><label for=\"c") + strexcnt + std::string("\">&nbsp;</label><pre>") +
                        dghtml + std::string("</pre></div>");
            vals[i] = omni::string::replace_all(vals[i], (std::string("@code") + omni::string::to_string(x) + std::string(" ")), repval);
            ++excnt;
        }
        vals[i] = omni::string::trim(vals[i]);
        all = all.substr(idx + ooe.size());
    }
    return OmniDocuGen::Util::Format(OmniDocuGen::Program::Settings.HtmlOptionsTemplate, vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6]);
}