#if !defined(DOCUGEN_MACROOP)
#define DOCUGEN_MACROOP 1

#include <omnilib>
#include "helpers.hpp"
#include "DocuSettings.hpp"
#include "Types.hpp"
#include "Program.hpp"

namespace OmniDocuGen
{
    class MacroOp
    {
        public:
            std::string Name;
            std::string Brief;
            std::string Considerations;
            std::string Description;
            std::string Notes;
            std::string PlatformSpecific;
            std::string Synopsis;
            bool IsHelper;
            bool IsConstant;
            bool IsFWHelp;
            List<std::string> References;

            MacroOp() :
                Name("OMNI_NAME"),
                Brief("A library macro/option"),
                Considerations("No special considerations"),
                Description("A library macro/option that changes certain functionality"),
                Notes("None."),
                PlatformSpecific("No platform specific notes."),
                Synopsis("A library macro/option"),
                IsHelper(),
                IsConstant(),
                IsFWHelp(),
                References(),
                _file()
            {
            }

            MacroOp(const MacroOp& cp) :
                Name(cp.Name),
                Brief(cp.Brief),
                Considerations(cp.Considerations),
                Description(cp.Description),
                Notes(cp.Notes),
                PlatformSpecific(cp.PlatformSpecific),
                Synopsis(cp.Synopsis),
                IsHelper(cp.IsHelper),
                IsConstant(cp.IsConstant),
                IsFWHelp(cp.IsFWHelp),
                References(cp.References),
                _file(cp._file)
            {
            }

            explicit MacroOp(const std::string& xmlfile) :
                Name("OMNI_NAME"),
                Brief("A library macro/option"),
                Considerations("No special considerations"),
                Description("A library macro/option that changes certain functionality"),
                Notes("None."),
                PlatformSpecific("No platform specific notes."),
                Synopsis("A library macro/option"),
                IsHelper(),
                IsConstant(),
                IsFWHelp(),
                References(),
                _file(xmlfile)
            {
                this->LoadNormalized();
            }

            MacroOp(std::string nm, std::string b) :
                Name(nm),
                Brief(b),
                Considerations("No special considerations"),
                Description("A library macro/option that changes certain functionality"),
                Notes("None."),
                PlatformSpecific("No platform specific notes."),
                Synopsis("A library macro/option"),
                IsHelper(),
                IsConstant(),
                IsFWHelp(),
                References(),
                _file()
            {
                this->_setfile();
            }

            MacroOp(std::string nm, std::string b, bool h, bool c, bool f) :
                Name(nm),
                Brief(b),
                Considerations("No special considerations"),
                Description("A library macro/option that changes certain functionality"),
                Notes("None."),
                PlatformSpecific("No platform specific notes."),
                Synopsis("A library macro/option"),
                IsHelper(h),
                IsConstant(c),
                IsFWHelp(f),
                References(),
                _file()
            {
                this->_setfile();
            }

            MacroOp(std::string nm, bool ih, std::string b, std::string s, std::string d, std::string c, std::string p, std::string no) :
                Name(nm),
                Brief(b),
                Considerations(c),
                Description(d),
                Notes(no),
                PlatformSpecific(p),
                Synopsis(s),
                IsHelper(ih),
                IsConstant(),
                IsFWHelp(),
                References(),
                _file()
            {
                this->_setfile();
            }

            bool Empty() const
            {
                return this->_file.empty();
            }

            bool Exists() const
            {
                return omni::io::file::exists(this->_file);
            }

            std::string FileName() const
            {
                return this->_file;
            }

            std::string LiHtmlString() const;

            bool LoadNormalized()
            {
                // DEV_NOTE: this needs to be loaded 'normalized' as line breaks in XML are treated as explicit \n
                // so all endinging need to be normalized to \r\n
                bool ret = false;
                if (omni::io::file::exists(this->_file)) {
                    try {
                        std::string xml = omni::io::file::get_contents(this->_file);
                        this->Name = omni::string::trim(OmniDocuGen::Util::NormalizeEndings(get_tag<std::string>(xml, "Name")));
                        this->Brief = omni::string::trim(OmniDocuGen::Util::NormalizeEndings(get_tag<std::string>(xml, "Brief")));
                        this->Considerations = omni::string::trim(OmniDocuGen::Util::NormalizeEndings(get_tag<std::string>(xml, "Considerations")));
                        this->Description = omni::string::trim(OmniDocuGen::Util::NormalizeEndings(get_tag<std::string>(xml, "Description")));
                        this->Notes = omni::string::trim(OmniDocuGen::Util::NormalizeEndings(get_tag<std::string>(xml, "Notes")));
                        this->PlatformSpecific = omni::string::trim(OmniDocuGen::Util::NormalizeEndings(get_tag<std::string>(xml, "PlatformSpecific")));
                        this->Synopsis = omni::string::trim(OmniDocuGen::Util::NormalizeEndings(get_tag<std::string>(xml, "Synopsis")));
                        this->IsHelper = get_tag<bool>(xml, "IsHelper");
                        this->IsConstant = get_tag<bool>(xml, "IsConstant");
                        this->IsFWHelp = get_tag<bool>(xml, "IsFWHelp");
                        ret = true;
                    } catch (const std::exception& ex) {
                        OmniDocuGen::Program::AddError(ex, std::string("An error occurred loading the settings file: ") + this->_file);
                    }
                }
                return ret;
            }
            
            bool Save()
            {
                up(1, "Saving current settings for macro '{0}'", this->Name);
                if (this->_file.empty()) {
                    this->_file = omni::io::path::combine(OmniDocuGen::Program::Settings.MacroDirectory, omni::string::to_lower(this->Name)) + std::string(".xml");
                }
                try {
                    std::string xml = "<?xml version=\"1.0\"?>\r\n<MacroOp xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">\r\n";
                    xml += gen_tag(this->Name, "Name");
                    xml += gen_tag(this->Brief, "Brief");
                    xml += gen_tag(this->Considerations, "Considerations");
                    xml += gen_tag(this->Description, "Description");
                    xml += gen_tag(this->Notes, "Notes");
                    xml += gen_tag(this->PlatformSpecific, "PlatformSpecific");
                    xml += gen_tag(this->Synopsis, "Synopsis");
                    xml += gen_tag(this->IsHelper, "IsHelper");
                    xml += gen_tag(this->IsConstant, "IsConstant");
                    xml += gen_tag(this->IsFWHelp, "IsFWHelp");
                    xml += "</MacroOp>";
                    Util::WriteFile(this->_file, xml);
                    if (omni::io::file::exists(this->_file)) {
                        up("Macro '{0}' saved to '{1}'", this->Name, this->_file);
                        return true;
                    }
                    return false;
                } catch (const std::exception& ex) {
                    OmniDocuGen::Program::AddError(ex, (std::string("Error saving file: ") + this->_file));
                }
                return false;
            }

            bool Save(const std::string& file)
            {
                this->_file = file;
                return this->Save();
            }

            std::string ToHTML() const;

            std::string ToText() const
            {
                std::stringstream ss;
                ss << "<name '" << this->Name << "'>\r\n" <<
                    "@Brief\r\n" << this->Brief << "\r\n@Brief\r\n\r\n" <<
                    "@Considerations\r\n" << this->Considerations << "\r\n@Considerations\r\n\r\n" <<
                    "@Description\r\n" << this->Description << "\r\n@Description\r\n\r\n" <<
                    "@Notes\r\n" << this->Notes << "\r\n@Notes\r\n\r\n" <<
                    "@PlatformSpecific\r\n" << this->PlatformSpecific << "\r\n@PlatformSpecific\r\n\r\n" <<
                    "@Synopsis\r\n" << this->Synopsis << "\r\n@Synopsis\r\n\r\n" <<
                    "@IsHelper\r\n" << (this->IsHelper ? "true" : "false") << "\r\n@IsHelper\r\n\r\n" <<
                    "@IsConstant\r\n" << (this->IsConstant ? "frue" : "false") << "\r\n@IsConstant\r\n\r\n" <<
                    "@IsFWHelp\r\n" << (this->IsFWHelp ? "true" : "false") << "\r\n@IsFWHelp\r\n" <<
                    "</name '" << this->Name << "'>";
                return ss.str();
            }

            operator std::string() const
            {
                return this->Name;
            }

            MacroOp& operator=(const MacroOp& cp)
            {
                this->Name = cp.Name;
                this->Brief = cp.Brief;
                this->Considerations = cp.Considerations;
                this->Description = cp.Description;
                this->Notes = cp.Notes;
                this->PlatformSpecific = cp.PlatformSpecific;
                this->Synopsis = cp.Synopsis;
                this->IsHelper = cp.IsHelper;
                this->IsConstant = cp.IsConstant;
                this->IsFWHelp = cp.IsFWHelp;
                this->References = cp.References;
                this->_file = cp._file;
                return *this;
            }

            bool operator<(const MacroOp& b) const
            {
                return this->Name < b.Name;
            }

            friend std::ostream& operator<<(std::ostream& os, const MacroOp& op)
            {
                os << op.Name;
                return os;
            }

            std::string ToFullString(bool view_file, bool view_brief, bool view_deets, bool view_is) const
            {
                std::stringstream ss;
                if (view_file) {
                    ss << "MACRO at '" << this->_file << "':" << std::endl;
                }
                if (view_brief || view_deets || view_is) {
                    ss << "<name '" << this->Name << "'>" << std::endl;
                    if (view_brief) {
                        ss << "@Brief" << std::endl << this->Brief << std::endl << "@Brief" << std::endl << std::endl;
                    }
                    if (view_deets) {
                        ss << "@Considerations" << std::endl << this->Considerations << std::endl << "@Considerations" << std::endl << std::endl;
                        ss << "@Description" << std::endl << this->Description << std::endl << "@Description" << std::endl << std::endl;
                        ss << "@Notes" << std::endl << this->Notes << std::endl << "@Notes" << std::endl << std::endl;
                        ss << "@PlatformSpecific" << std::endl << this->PlatformSpecific << std::endl << "@PlatformSpecific" << std::endl << std::endl;
                        ss << "@Synopsis" << std::endl << this->Synopsis << std::endl << "@Synopsis" << std::endl << std::endl;
                    }
                    if (view_is) {
                        ss << "@IsHelper" << std::endl << (this->IsHelper ? "true" : "false") << std::endl << "@IsHelper" << std::endl << std::endl;
                        ss << "@IsConstant" << std::endl << (this->IsConstant ? "true" : "false") << std::endl << "@IsConstant" << std::endl << std::endl;
                        ss << "@IsFWHelp" << std::endl << (this->IsFWHelp ? "true" : "false") << std::endl << "@IsFWHelp" << std::endl << std::endl;
                    }
                    ss << "</name '" << this->Name << "'>";
                } else {
                    ss << "MACRO name: " << this->Name << std::endl;
                }
                if (view_file || view_brief || view_deets || view_is) {
                    ss << std::endl;
                }
                return ss.str();
            }

            static MacroOp FromText(std::string data)
            {
                bool ih = false;
                std::string nm, b, s, d, c, p, no, line;
                List<std::string> lines = OmniDocuGen::Util::SplitAtEndings(data);
                for (size_t i = 0; i < lines.size(); ++i) {
                    line = lines[i];
                    if (line.empty()) { continue; }
                    if (omni::string::starts_with(line, "<name '")) {
                        nm = omni::string::trim_end(line, "\r\n").substr(7);
                        nm = nm.substr(0, nm.size() - 2);
                    } else if (omni::string::starts_with(line, "</name '")) {
                        break;
                    } else {
                        if (line == "@Brief") {
                            for (++i; i < lines.size(); ++i) {
                                if (lines[i] == "@Brief") { break; }
                                b += lines[i] + "\r\n";
                            }
                        } else if (line == "@Considerations") {
                            for (++i; i < lines.size(); ++i) {
                                if (lines[i] == "@Considerations") { break; }
                                c += lines[i] + "\r\n";
                            }
                        } else if (line == "@Description") {
                            for (++i; i < lines.size(); ++i) {
                                if (lines[i] == "@Description") { break; }
                                d += lines[i] + "\r\n";
                            }
                        } else if (line == "@Notes") {
                            for (++i; i < lines.size(); ++i) {
                                if (lines[i] == "@Notes") { break; }
                                no += lines[i] + "\r\n";
                            }
                        } else if (line == "@PlatformSpecific") {
                            for (++i; i < lines.size(); ++i) {
                                if (lines[i] == "@PlatformSpecific") { break; }
                                p += lines[i] + "\r\n";
                            }
                        } else if (line == "@Synopsis") {
                            for (++i; i < lines.size(); ++i) {
                                if (lines[i] == "@Synopsis") { break; }
                                s += lines[i] + "\r\n";
                            }
                        } else if (line == "@IsHelper") {
                            for (++i; i < lines.size(); ++i) {
                                if (lines[i] == "@IsHelper") { break; }
                                if (lines[i] == "true") { ih = true; }
                            }
                        }
                        /*
                        else if (line == "@IsConstant") {
                            for (++i; i < lines.size(); ++i) {
                                b += lines[i] + "\r\n";
                                if (lines[i] == "@IsConstant") { break; }
                            }
                        } else if (line == "@IsFWHelp") {
                            for (++i; i < lines.size(); ++i) {
                                b += lines[i] + "\r\n";
                                if (lines[i] == "@IsFWHelp") { break; }
                            }
                        }
                        */
                    }
                }
                return MacroOp(nm, ih,
                    omni::string::trim_end(b, "\r\n"),
                    omni::string::trim_end(s, "\r\n"),
                    omni::string::trim_end(d, "\r\n"),
                    omni::string::trim_end(c, "\r\n"),
                    omni::string::trim_end(p, "\r\n"),
                    omni::string::trim_end(no, "\r\n")
                );
            }

        private:
            std::string _file;

            void _setfile()
            {
                this->_file = omni::io::path::combine(
                    OmniDocuGen::Program::Settings.MacroDirectory,
                    omni::string::to_lower(this->Name)
                ) + std::string(".xml");
            }
    };
}

#endif // DOCUGEN_MACROOP
