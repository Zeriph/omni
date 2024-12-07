#if !defined(DOCUGEN_OUTPATHS)
#define DOCUGEN_OUTPATHS 1

#include <omnilib>
#include "DocuSettings.hpp"

namespace OmniDocuGen
{
    namespace OutPaths
    {
        // string ofile = System.IO.omni::io::path::combine(OmniDocuGen::Program::Settings.OutputDirectory, "docs" OMNI_PATH_SEPARATOR "api.html");
        //string ofile = omni::io::path::combine(DocuGen.Files, "index.html");
        //string ifile = omni::io::path::combine(DocuGen.Docs, "htmlsrc" OMNI_PATH_SEPARATOR "index.html");
        //string ofile = omni::io::path::combine(DocuGen.Options, "index.html");
        //string ofile = omni::io::path::combine(classdir, "index.html");

        extern std::string TempOut;
        extern std::string ZipDir;
        extern std::string HtmlSrcDir;

        extern std::string ApiHtml;
        extern std::string TempApiHtml;

        extern std::string ClassIndexHtml;
        extern std::string TempClassIndexHtml;

        extern std::string FilesIndexHtml;
        extern std::string TempFilesIndexHtml;

        extern std::string HtmlSrcIndexHtml;
        extern std::string TempHtmlSrcIndexHtml;

        extern std::string OptionsIndexHtml;
        extern std::string TempOptionsIndexHtml;

        extern std::string ExampleIndexHtml;
        extern std::string TempExampleIndexHtml;
    };
}

#endif // DOCUGEN_OUTPATHS
