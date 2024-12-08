#if !defined(DOCUGEN_CODEGEN)
#define DOCUGEN_CODEGEN 1

#include <omnilib>
#include "helpers.hpp"
#include "DocuSettings.hpp"
#include "MemberTypeInformation.hpp"
#include "Util.hpp"

namespace OmniDocuGen
{
    /// Defines a class for the source to HTML generation
    class CodeGen
    {
        public:
            typedef omni::smart_ptr<CodeGen> ptr_t;

            /// Gets or sets the source file (cpp/hpp/etc) this instance refers to
            std::string SourceFile;
            /// Gets or sets the syntax highlighted generated HTML file (located in the files/ folder)
            std::string HtmlSyntaxFile;
            /// Gets the name of this type (last scope value in scope name)
            std::string Name() const
            {
                if (this->_Name.empty() && !this->SourceFile.empty()) {
                    this->_Name = this->SourceFile.substr(this->SourceFile.rfind(OMNI_PATH_SEPARATOR) + 1);
                }
                return this->_Name;
            }
            
            /// Gets the member type information generated for this instance (if any)
            MemberTypeInformation::ptr_t MemberInformation;

            /// The original source
            std::string RawSourceCode() const
            {
                return this->_RawCode;
            }

            std::string SourceSansComment() const
            {
                return this->_CodeNoCommnet;
            }
            
            /// The default constructor
            CodeGen() :
                SourceFile(),
                HtmlSyntaxFile(),
                MemberInformation(),
                _RawCode(),
                _CodeNoCommnet(),
                _Name()
            {
                this->_Initialize("");
            }

            /// Creates a new instance based from a source file and output directory
            explicit CodeGen(std::string src) :
                SourceFile(),
                HtmlSyntaxFile(),
                MemberInformation(),
                _RawCode(),
                _CodeNoCommnet(),
                _Name()
            {
                this->_Initialize(src);
            }

            CodeGen(const CodeGen& cp) :
                SourceFile(cp.SourceFile),
                HtmlSyntaxFile(cp.HtmlSyntaxFile),
                MemberInformation(cp.MemberInformation),
                _RawCode(cp._RawCode),
                _CodeNoCommnet(cp._CodeNoCommnet),
                _Name(cp._Name)
            {}

            /// Gets if the source code has parsable source (i.e. namespace omni {})
            bool HasParsableCode()
            {
                return !OmniDocuGen::Util::IsSourceExt(this->SourceFile) && omni::string::contains(this->_RawCode, "namespace omni {");
            }

            bool SaveToXML(std::string folder)
            {
                std::string fmt = "<?xml version=\"1.0\"?>\r\n"
                                  "<CodeGen>\r\n"
                                  "<SourceFile>\r\n{0}\r\n</SourceFile>\r\n"
                                  "<MemberTypeInformation>\r\n{1}\r\n</MemberTypeInformation>\r\n"
                                  "</CodeGen>";
                std::string ofile = omni::io::path::combine(folder, omni::string::replace(this->SourceFile, OmniDocuGen::Program::Settings.SourceDirectory, "")) + std::string(".xml");
                std::string xml = OmniDocuGen::Util::Format(fmt, this->SourceFile, (this->MemberInformation ? this->MemberInformation->ToXML() : ""));
                Util::WriteFile(ofile, xml);
                return omni::io::file::exists(ofile);
            }

            /// Generates type info from a source file (not header)
            void GenerateSourceTypeInfo()
            {
                up("Parsing source {0}", this->SourceFile);
                try {
                    this->_GenerateSoureTypeInfo();
                } catch (const std::exception& ex) {
                    OmniDocuGen::Program::AddError(ex, this->Name());
                }
            }

            /// Generates the information from the specified source file
            void GenerateTypeInfo()
            {
                up("Generating type info for {0}", this->SourceFile);
                try {
                    if (OmniDocuGen::Util::IsHeaderExt(this->Name())) {
                        if (OmniDocuGen::CodeGen::IsSpecialHeader(this->SourceFile)) {
                            this->_GenerateSpecialTypeInfo();
                        } else {
                            this->_GenerateTypeInformation();
                        }
                    } else {
                        up(1, "No types to generate for {0}", this->SourceFile);
                    }
                } catch (const std::exception& ex) {
                    OmniDocuGen::Program::AddError(ex, this->Name());
                }
            }

            /// Returns the name of this instance
            operator std::string() const
            {
                return this->Name();
            }

            /// Returns if the file name is a file that needs to be specially parsed (like a .hxx file)
            static bool IsSpecialHeader(std::string file)
            {
                file = omni::io::path::get_name(file);
                return (
                    (file == "string.hxx") ||
                    (file == "ext_const.hxx") ||
                    (file == "const.hxx")
                );
            }

            /// Returns if the file name is a file that needs to be specially parsed (like a .hxx file)
            static inline bool IsSpecialSource(const std::string& file)
            {
                //file = omni::io::path::get_name(file);
                return (
                    (omni::io::path::get_name(file) == "omnilib")
                    //(file == "omnilib") ||
                    //(file == "environment.hxx") ||
                    //(file == "stopwatch.hxx") ||
                    //(file == "system.hxx") ||
                    //(file == "version.hxx")
                );
            }

            /// Returns if the file name is a file that has parsable code, but shouldn't be parsed (like a .hxx file)
            static inline bool IsNoParse(const std::string& file)
            {
                std::deque<std::string> non = omni::string::split(Program::Settings.NoParse, ",");
                return std::find(non.begin(), non.end(), omni::io::path::get_name(file)) != non.end();
                // return omni::string::contains(Program::Settings.NoParse, omni::io::path::get_name(file));
            }

            static ptr_t FromXml(const std::string& file)
            {
                if (omni::io::file::exists(file)) {
                    std::string full = OmniDocuGen::Util::NormalizeEndings(omni::io::file::get_contents(file));
                    int32_t slen = std::string("<?xml version=\"1.0\"?>\r\n<CodeGen>\r\n").length();
                    int32_t len = full.length() - slen - std::string("</CodeGen>").length();
                    full = full.substr(slen, len);
                    std::string sfile = omni::string::trim(OmniDocuGen::Util::GetTagData(full, "SourceFile"));
                    std::string mtixml = OmniDocuGen::Util::GetTag(full, "MemberTypeInformation");
                    ptr_t ret(new CodeGen(sfile));
                    try {
                        ret->MemberInformation = MemberTypeInformation::FromXML(mtixml, sfile);
                    } catch (const std::exception& ex) {
                        //ex.LogError(string.Format("xml: {0}", sfile));
                        OmniDocuGen::Program::AddError(ex, sfile);
                    }
                    return ret;
                }
                return ptr_t();
            }
            
        private:
            std::string _RawCode;
            std::string _CodeNoCommnet;
            mutable std::string _Name;

            /// Initialize the instance
            void _Initialize(const std::string& srcFile);

            /// Generates the class type information based on the code read from the source file
            void _GenerateTypeInformation();

            /// Generates the class type information based on the code read from the source file
            void _GenerateSoureTypeInfo();

            /// Generates the class type information based on the code read from the source file
            void _GenerateSpecialTypeInfo();
    };
}

#endif // DOCUGEN_CODEGEN
