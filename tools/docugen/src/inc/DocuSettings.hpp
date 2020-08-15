#if !defined(DOCUGEN_DOCUSETTINGS)
#define DOCUGEN_DOCUSETTINGS 1

#include <omnilib>
#include "helpers.hpp"
#include "Program.hpp"
#include "Util.hpp"

namespace OmniDocuGen
{
    class DocuSettings
    {
        public:
            // Gets or sets the source directory used for the Omni Source
            std::string SourceDirectory;
            // Gets or sets the example directory
            std::string ExampleDirectory;
            // Gets or sets the output directory used for HTML output
            std::string OutputDirectory;
            // The previous zip directory
            std::string PrevZipDirectory;
            // Gets or sets the macro/options directory
            std::string MacroDirectory;
            // Gets or sets the blacklisted source directory used
            std::string SystemAPIDirectory;
            // Gets or sets the licence file
            std::string LicenseFile;
            // Gets the templates directory
            std::string TemplateDirectory;
            // Gets the temporary output directory
            std::string TempZipDirectory;
            // Gets the excluded files/folders
            std::string Excluded;
            // Gets the files that shalt not be parsed (like .hxx files)
            std::string NoParse;
            // keywords
            std::string KeywordInstructions;
            std::string KeywordTypes;
            std::string KeywordPreproc;
            std::string KeywordDoxyTags;
            std::string KeywordDoxyCommentTags;
            // Gets or sets the source example directory
            std::string FrameworkExampleDirectory() { return omni::io::path::combine(this->ExampleDirectory, "library"); }
            // Gets or sets the example direcotry used
            std::string ClassExampleDirectory() { return omni::io::path::combine(this->ExampleDirectory, "classes"); }
            // Gets or sets the build example directory
            std::string BuildExDirectory() { return omni::io::path::combine(this->ExampleDirectory, "build"); }
            // Gets the HTML for the docs/htmlsrc/index.html
            std::string HtmlView;
            // Gets the HTML for the docs/htmlsrc/XXX.html
            std::string HtmlViewSyntax;
            // Gets the HTML for the docs/classes/index.html
            std::string HtmlClasses;
            // Gets the HTML for the docs/classes/XXX.html
            std::string HtmlClassTemplate;
            // Gets the HTML for the docs/options/...html
            std::string HtmlOptions;
            // Gets the HTML for the docs/options/macro_name.html template
            std::string HtmlOptionsTemplate;
            // Gets the HTML for the docs/examples/index.html
            std::string HtmlExamples;
            // Gets the HTML for the about/system_api.html
            std::string HtmlSystemAPI;
            // Gets the html for the download.html template
            std::string HtmlDownloadTemplate;
            // Gets the html for the files/index.html template
            std::string HtmlFilesIndex;

            // comment_omni.txt
            std::string CommentOmni;
            //comment_omni_members_fw.txt
            std::string CommentOmniMembersFw;
            // comment_omni_ostream_fw.txt
            std::string CommentOmniOstreamFw;
            // comment_omni_ostream_fn_fw.txt
            std::string CommentOmniOstreamFnFw;

            DocuSettings() : _file() {}

            ~DocuSettings() {}

            void LoadHtmlFromFiles()
            {
                this->HtmlView = this->_set_template_str("htmlsrc_index.html");
                this->HtmlViewSyntax = this->_set_template_str("htmlsrc_help.html");
                this->HtmlClasses = this->_set_template_str("classes_index.html");
                this->HtmlClassTemplate = this->_set_template_str("classes_help.html");
                this->HtmlOptions = this->_set_template_str("options_index.html");
                this->HtmlOptionsTemplate = this->_set_template_str("options_help.html");
                this->HtmlDownloadTemplate = this->_set_template_str("download.html");
                this->HtmlSystemAPI = this->_set_template_str("system_api.html");
                this->HtmlFilesIndex = this->_set_template_str("files_index.html");
                this->HtmlExamples = this->_set_template_str("examples_index.html");

                this->CommentOmni = this->_set_template_str("comment_omni.txt");
                this->CommentOmniMembersFw = this->_set_template_str("comment_omni_members_fw.txt");
                this->CommentOmniOstreamFw = this->_set_template_str("comment_omni_ostream_fw.txt");
                this->CommentOmniOstreamFnFw = this->_set_template_str("comment_omni_ostream_fn_fw.txt");
            }

            bool Load()
            {
                pv("Loading settings...");
                bool ret = false;
                if (omni::io::file::exists(this->_file)) {
                    try {
                        std::string xml = omni::io::file::get_contents(this->_file);
                        this->SourceDirectory = get_tag<std::string>(xml, "SourceDirectory");
                        this->ExampleDirectory = get_tag<std::string>(xml, "ExampleDirectory");
                        this->OutputDirectory = get_tag<std::string>(xml, "OutputDirectory");
                        this->PrevZipDirectory = get_tag<std::string>(xml, "PrevZipDirectory");
                        this->MacroDirectory = get_tag<std::string>(xml, "MacroDirectory");
                        this->SystemAPIDirectory = get_tag<std::string>(xml, "SystemAPIDirectory");
                        this->LicenseFile = get_tag<std::string>(xml, "LicenseFile");
                        this->TemplateDirectory = get_tag<std::string>(xml, "TemplateDirectory");
                        this->TempZipDirectory = get_tag<std::string>(xml, "TempZipDirectory");
                        this->Excluded = get_tag<std::string>(xml, "Excluded");
                        this->NoParse = get_tag<std::string>(xml, "NoParse");
                        this->KeywordInstructions = get_tag<std::string>(xml, "KeywordInstructions");
                        this->KeywordTypes = get_tag<std::string>(xml, "KeywordTypes");
                        this->KeywordPreproc = get_tag<std::string>(xml, "KeywordPreproc");
                        this->KeywordDoxyTags = get_tag<std::string>(xml, "KeywordDoxyTags");
                        this->KeywordDoxyCommentTags = get_tag<std::string>(xml, "KeywordDoxyCommentTags");
                        this->LoadHtmlFromFiles();
                        ret = true;
                    } catch (const std::exception& ex) {
                        OmniDocuGen::Program::AddError(ex, this->_file);
                    }
                }
                if (!ret) {
                    up("default loaded");
                    ret = this->Save(false);
                } else {
                    up("done");
                    up(1, "With the following:\n"
                        "SourceDirectory: {0}\n"
                        "ExampleDirectory: {1}\n"
                        "OutputDirectory: {2}\n"
                        "PrevZipDirectory: {3}\n"
                        "MacroDirectory: {4}\n"
                        "SystemAPIDirectory: {5}\n"
                        "LicenseFile: {6}\n"
                        "TemplateDirectory: {7}\n"
                        "TempZipDirectory: {8}\n"
                        "Excluded: {9}\n"
                        "NoParse: {10}",
                        this->SourceDirectory,
                        this->ExampleDirectory,
                        this->OutputDirectory,
                        this->PrevZipDirectory,
                        this->MacroDirectory,
                        this->SystemAPIDirectory,
                        this->LicenseFile,
                        this->TemplateDirectory,
                        this->TempZipDirectory,
                        this->Excluded,
                        this->NoParse
                    );
                }
                return ret;
            }

            void Load(const std::string& file)
            {
                this->SetFile(file);
                this->Load();
            }
            
            void SetFile(const std::string& file)
            {
                this->_file = file;
                up("Using settings file: {0}", this->_file);
            }
            
            bool Save(bool reloadHtml)
            {
                up("Saving current settings");
                try {
                    std::string data = "<?xml version=\"1.0\"?>\n<DocuSettings xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">\n";
                    data += gen_tag(this->SourceDirectory, "SourceDirectory");
                    data += gen_tag(this->ExampleDirectory, "ExampleDirectory");
                    data += gen_tag(this->OutputDirectory, "OutputDirectory");
                    data += gen_tag(this->PrevZipDirectory, "PrevZipDirectory");
                    data += gen_tag(this->MacroDirectory, "MacroDirectory");
                    data += gen_tag(this->SystemAPIDirectory, "SystemAPIDirectory");
                    data += gen_tag(this->LicenseFile, "LicenseFile");
                    data += gen_tag(this->TemplateDirectory, "TemplateDirectory");
                    data += gen_tag(this->TempZipDirectory, "TempZipDirectory");
                    data += gen_tag(this->Excluded, "Excluded");
                    data += gen_tag(this->NoParse, "NoParse");
                    data += gen_tag(this->KeywordInstructions, "KeywordInstructions");
                    data += gen_tag(this->KeywordTypes, "KeywordTypes");
                    data += gen_tag(this->KeywordPreproc, "KeywordPreproc");
                    data += gen_tag(this->KeywordDoxyTags, "KeywordDoxyTags");
                    data += gen_tag(this->KeywordDoxyCommentTags, "KeywordDoxyCommentTags");
                    data += "</DocuSettings>";
                    OmniDocuGen::Util::WriteFile(this->_file, data);
                    if (omni::io::file::exists(this->_file)) {
                        if (reloadHtml) { this->LoadHtmlFromFiles(); }
                        return true;
                    }
                    return false;
                } catch (const std::exception& ex) {
                    OmniDocuGen::Program::AddError(ex, this->_file);
                }
                return false;
            }

        private:
            // The file to save to/load from
            std::string _file;

            std::string _set_template_str(const std::string& file)
            {
                std::string f = omni::io::path::combine(this->TemplateDirectory, file);
                if (omni::io::file::exists(f)) {
                    try {
                        return omni::io::file::get_contents(f);
                    } catch (const std::exception& ex) {
                        OmniDocuGen::Program::AddError(ex);
                    }
                }
                return "<html><head><title>Omni Library</title></head><body><pre>\n";
            }
    };

    namespace Program
    {
        /// The main settings for the program
        extern OmniDocuGen::DocuSettings Settings;
    }

    namespace Util
    {
        static inline omni::seq::std_string_t GetFileList(const std::string& dir, bool includeDir)
        {
            omni::seq::std_string_t r;
            if (includeDir) { r.push_back(dir); }
            omni::seq::std_string_t dirs = omni::io::directory::get_directories(dir);
            omni::seq::std_string_t files = omni::io::directory::get_files(dir);
            omni_foreach (std::string, d, dirs) {
                if (OmniDocuGen::Program::StopReq) { return r; }
                if (omni::string::contains(omni::string::to_lower(Program::Settings.Excluded), omni::string::to_lower(*d))) { continue; }
                omni::sequence::add_range(r, OmniDocuGen::Util::GetFileList(*d, includeDir));
            }
            omni_foreach (std::string, f, files) {
                if (OmniDocuGen::Program::StopReq) { return r; }
                if (omni::string::contains(omni::string::to_lower(Program::Settings.Excluded), omni::string::to_lower(*f))) { continue; }
                r.push_back(*f);
            }
            return r;
        }

        static inline omni::seq::std_string_t GetFileList(const std::string& dir)
        {
            return OmniDocuGen::Util::GetFileList(dir, true);
        }
    }
}

#endif // DOCUGEN_DOCUSETTINGS
