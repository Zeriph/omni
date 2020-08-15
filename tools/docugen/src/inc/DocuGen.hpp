#if !defined(DOCUGEN_DOCUGEN)
#define DOCUGEN_DOCUGEN 1

#include <omnilib>
#include "helpers.hpp"
#include "Constants.hpp"
#include "Program.hpp"
#include "Types.hpp"
#include "Util.hpp"
#include "MemberTypeInformation.hpp"
#include "MacroOp.hpp"
#include "SysAPI.hpp"
#include "CodeGen.hpp"
#include "OutPaths.hpp"
#include "FrameworkExample.hpp"

namespace OmniDocuGen
{
    namespace DocuGen
    {
        extern List< CodeGen::ptr_t > m_synList;
        extern omni::sync::mutex m_synLock;
        extern volatile uint32_t m_synIdx;

        extern List< MemberTypeInformation::ptr_t > m_classList;
        extern omni::sync::mutex m_classLock;
        extern volatile uint32_t m_classIdx;
        extern volatile bool m_classRecurse;

        extern List<MacroOp> m_macroList;
        extern volatile uint32_t m_macIdx;
        extern omni::sync::mutex m_macroLock;

        extern List<std::string> m_xml;
        extern omni::sync::mutex m_xmllock;

        /// the current member list (allmti)
        extern MemberTypeInformation::ptr_t AllMti;
        /// the current tree node containing AllMti
        extern Types::TreeNode MtiTree;
        /// wwwdocs
        extern std::string Root;
        /// wwwdocs/files
        extern std::string Files;
        /// wwwdocs/docs
        extern std::string Docs;
        /// wwwdocs/docs/htmlsrc/
        extern std::string HtmlSyntax;
        /// wwwdocs/files/src
        extern std::string FilesSource;
        /// wwwdocs/docs/classes
        extern std::string Classes;
        /// wwwdocs/docs/examples
        extern std::string Examples;
        /// wwwdocs/docs/options
        extern std::string Options;
        /// wwwdocs/docs/build
        extern std::string Build;
        /// The current macro list
        extern List<MacroOp> Macros;
        /// Gets the current System API list
        extern List<SysAPI> SysAPIs;
        //ImageList ImageListTree;
        extern List<std::string> SourceFiles;
        extern List<std::string> HeaderFiles;
        extern List< CodeGen::ptr_t > CodeGenList;
        extern List< CodeGen::ptr_t > Parsables;
        extern volatile bool HasParsed;
        extern volatile bool DoClasses;
        extern volatile bool DoClassIndex;
        extern volatile bool DoMacroOptions;
        extern volatile bool DoFilesView;
        extern volatile bool DoSyntax;
        extern volatile bool DoAPI;
        extern volatile bool DoExamples;
        // no parsing needed for these
        extern volatile bool DoBuildFiles;
        extern volatile bool DoJs;
        extern volatile bool DoHashZipFiles;

        void _GenerateCGHtmlSynFileThread(CodeGen::ptr_t& c);
        void _GenerateClassIndexHtml();
        void _GenerateHtmlClassHelpNR();
        void _GenerateHtmlSyntaxFilesThread();
        void _GenerateClassFilesThread();
        void _GenerateMacroOptionThreadFunc(const MacroOp& m);
        void _GenerateMacroOptionsThread();
        void _SortSourceAndDelegateHeaders();
        void _ScanSourcedir(const std::string& srcdir);
        bool ParseNeeded();
        void Initialize();
        void LoadMacros(const std::string& macdir);
        void LoadSystemAPI(const std::string& apidir);
        List<std::string> GetMtiClassFilePath(MemberTypeInformation::ptr_t& mti);
        void CheckClassDir();
        void GenerateHtmlSyntaxFiles(List<CodeGen::ptr_t>& files);
        void GenerateHtmlSyntaxFiles();
        void GenerateClassFiles(List<MemberTypeInformation::ptr_t>& members, bool recurse);
        void GenerateClassFiles();
        void GenerateExamplesZipFile();
        void GenerateExamplesHtml();
        void GenerateAPIs();
        void GenerateMacroOptions(List<MacroOp> options);
        void GenerateMacroOptions();
        void GenerateJavaScriptSearchList();
        void LinkMacroApiToSource();
        void ScanSourceDir(const std::string& srcdir);
        void ParseSource(const Types::SourceGenType& sgt);
        void GenerateAndBuild();
        void StartSource(const Types::SourceGenType& sgt);
        void StartBuild();
        // mti gen
        void AddTree(MemberTypeInformation::ptr_t& mti, Types::TreeNode& tv);
        void GenerateMemberInfo(bool isBuildToo);
        // html gen
        bool _CompareFileNames(const std::string& fname1, const std::string& fname2);
        std::string _GetFileViewTplate(const std::string& fname, const std::string& srcdir, bool verbose, bool includeNonHpp, bool isPlainText);
        std::string _GetFolderViewTplate(const std::string& dir, const std::string& srcdir, bool verbose, bool isPlainText);
        std::string _GenerateHtmlSyntaxFromTemplate(const std::string& name, const std::string& title, std::string sntx);
        std::string _ColorizePreproc(std::string sntx);
        std::string _ColorizeStrings(const std::string& sntx);
        std::string _ColorizeComments(std::string sntx, bool docmntdiv);
        std::string _RemoveInnerCodeTags(std::string val);
        std::string ReplaceHtmlDoxyCodeTags(const std::string& val, const std::string& iref);
        std::string ReplaceIncludes(std::string sntx, std::string inchref);
        std::string ReplaceMacroInfo(const std::string& val, const std::string& lvl, bool codeTags);
        std::string ReplaceSysApiInfo(const std::string& val, bool codeTags);
        std::string ReplaceKeywords(const std::string& code, bool hasq, bool hasnc);
        std::string GetFileTree(bool verbose, bool isPlainText);
        // gen mti html
        std::string ReplaceMemberInfo(MemberTypeInformation::ptr_t& mti, const std::string& val, const std::string& lvl, bool codeTags);
        std::string GetHTMLTree(MemberTypeInformation::ptr_t& mti, bool includePrivate);
        void GenerateClassesIndexHtml(const std::string& classdir, MemberTypeInformation::ptr_t& allmti);
        std::string GenerateHtmlSyntaxHighlight(const std::string& code, const std::string& inchref, const std::string& dochref, MemberTypeInformation::ptr_t& allmti, bool docmntdiv);
        std::string _GenerateMemberHtmlNameAnchors(const std::string& srcfile, const std::string& html, MemberTypeInformation::ptr_t& m);
        std::string GenerateHtmlSyntaxHighlight(const std::string& srcfile, const std::string& code, MemberTypeInformation::ptr_t& allmti, const std::string& dochref, const std::string& inchref, bool docmntdiv);
        std::string GenerateHtmlClassHelp(MemberTypeInformation::ptr_t& mti);
        void GenerateHtmlClassHelp(const std::string& classdir, MemberTypeInformation::ptr_t& mti, bool recurse);
        void GenerateHtmlSyntax(CodeGen::ptr_t& c);
        void GenerateFilesViewHtml();
        std::string ReplaceFrameworkInfo(const std::string& val, const std::string& mihref, const std::string& dhref, const std::string& fref);
        // build gen
        std::string _GenBuildFileFromSrcs(const List<std::string>& srcs, const std::string& srcdir, const std::string& slash, const std::string& fmt, bool isnlwin, bool use_nl, bool trim_end);
        std::string _GenBuildFileFromSrcs(const List<std::string>& srcs, const std::string& srcdir, const std::string& slash, const std::string& fmt);
        void _GenBuildFile(const List<std::string>& hdrs, const List<std::string>& srcs, const std::string& srcdir, const std::string& file, const std::string& odir);
        void _GenBuildExamples(const List<std::string>& hdrs, const List<std::string>& srcs, const std::string& srcdir, const std::string& bdir, const std::string& odir);
        void _GenBF(const std::string& t, const std::string& o, const List<std::string>& hdrs, const List<std::string>& srcs, const std::string& srcdir);
        void _GenerateTempHelp(std::string thelp);
        void _CreateAndMoveZips(const std::string& tpath, const std::string& srcdir, const std::string& thelp, const std::string& fsz, const std::string& fhz, const std::string& foz, const std::string& fbz, const std::string& fez, const std::string& frz);
        void _SetHashInFile(const std::string& file, const std::string& hsh);
        void _DoAPI(void_t parm);
        void _DoFilesView(void_t parm);
        void _DoClassIndex(void_t parm);
        void GenerateHashFiles();
        void GenerateBuildFiles();
        void CheckGenerateBuildJsHash();
        void GenerateExampleIndexHtml(bool writeHtml);
    }
}

#endif // DOCUGEN_DOCUGEN
