#if !defined(DOCUGEN_CONSTANTS)
#define DOCUGEN_CONSTANTS 1

#include <omnilib>
#include "helpers.hpp"

namespace OmniDocuGen
{
    namespace Constants
    {
        namespace Keywords
        {
            extern List<std::string> Instructions;
            extern List<std::string> Types;
            extern List<std::string> Preproc;
            extern List<std::string> DoxyTags;
            extern List<std::string> DoxyCommentTags;
        }

        namespace Tags
        {
            const std::string IL_SRC = "zeriph_inline_source";
            const std::string IL_HDR = "zeriph_inline_header";
            const std::string IL_SRC_NONL = "zeriph_inline_source_nonl";
            const std::string OMNI_SECTION = "start_zeriph_omni_section";
            const std::string MAKE_FILE = "zeriph_inline_makefile_source";
            const std::string XCODE_SREF = "zeriph_xcode_source_ref";
            const std::string XCODE_SHEX = "zeriph_xcode_sref_hex";
            const std::string XCODE_FREF = "zeriph_xcode_file_ref";
            const std::string XCODE_FHEX = "zeriph_xcode_fref_hex";
            const std::string XCODE_PARSE = "zeriph_xcode_parse";
        }

        const std::string nl = "\r\n";

        const std::string HtmlHashTable =
            "Download the latest version: <b>" OMNI_FW_VER_STR "</b><br><div class=\"dltbl code\" style=\"font-size:14px;\"><div><span><a href=\"files/src.zip\">" OMNI_EOL_RN
            "<img src=\"content/dl.gif\">src.zip</a><span>({0})</span></span><span>- The latest source files." OMNI_EOL_RN
            "<font class=\"toppg\">(<a href=\"download.html#srczip\">info</a>)</font></span></div><div><span><a href=\"files/help.zip\">" OMNI_EOL_RN
            "<img src=\"content/dl.gif\">help.zip</a><span>({1})</span></span><span>- The help documentation for the library (this site)." OMNI_EOL_RN
            "<font class=\"toppg\">(<a href=\"download.html#helpzip\">info</a>)</font></span></div><div><span><a href=\"files/omni.zip\">" OMNI_EOL_RN
            "<img src=\"content/dl.gif\">omni.zip</a><span>({2})</span></span><span>- A combined file of the src.zip and help.zip." OMNI_EOL_RN
            "<font class=\"toppg\">(<a href=\"download.html#omnizip\">info</a>)</font></span></div></div>" OMNI_EOL_RN;

        const std::string ViewFolderTemplate = "<li class=\"fldr\" title=\"folder: {0}\"><label for=\"{0}_fldr\">{0}</label>\r\n<input type=\"checkbox\" id=\"{0}_fldr\" name=\"{0}_fldr\" />\r\n<ol id=\"fldr_{0}\" name=\"fldr_{0}\">\r\n";
        const std::string ViewFolderPlainTemplate = "<li title=\"folder: {0}\">{0}<ul>\r\n";
    }
}

#endif // DOCUGEN_CONSTANTS
