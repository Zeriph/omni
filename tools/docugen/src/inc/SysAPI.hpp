#if !defined(DOCUGEN_SYSAPI)
#define DOCUGEN_SYSAPI 1

#include <omnilib>
#include "helpers.hpp"
#include "DocuSettings.hpp"
#include "Types.hpp"
#include "Program.hpp"

namespace OmniDocuGen
{
    class SysAPI
    {
        public:
            std::string Name;
            std::string Link;
            OmniDocuGen::Types::SystemType SysType;
            List<std::string> References;

            SysAPI() :
                Name("SystemAPI"),
                Link("http://www.api.com"),
                SysType(OmniDocuGen::Types::SystemType::POSIX),
                References(),
                _file()
            {
            }

            SysAPI(const SysAPI& cp) :
                Name(cp.Name),
                Link(cp.Link),
                SysType(cp.SysType),
                References(cp.References),
                _file(cp._file)
            {
            }

            explicit SysAPI(const std::string& xmlfile) :
                Name("SystemAPI"),
                Link("http://www.api.com"),
                SysType(OmniDocuGen::Types::SystemType::POSIX),
                References(),
                _file(xmlfile)
            {
                this->Load();
            }

            SysAPI(const std::string& nm, const std::string& l) :
                Name(nm),
                Link(l),
                SysType(OmniDocuGen::Types::SystemType::POSIX),
                References(),
                _file()
            {
                this->_setfile();
            }

            SysAPI(const std::string& nm, const std::string& l, const OmniDocuGen::Types::SystemType& t) :
                Name(nm),
                Link(l),
                SysType(t),
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

            bool Load()
            {
                bool ret = false;
                if (omni::io::file::exists(this->_file)) {
                    try {
                        std::string xml = omni::io::file::get_contents(this->_file);
                        this->Name = get_tag<std::string>(xml, "Name");
                        this->Link = get_tag<std::string>(xml, "Link");
                        OmniDocuGen::Types::SystemType::try_parse(get_tag<std::string>(xml, "SysType"), this->SysType);
                        ret = true;
                    } catch (const std::exception& ex) {
                        OmniDocuGen::Program::AddError(std::string("An error occurred loading the settings file: ") + this->_file);
                    }
                }
                return ret;
            }
            
            bool Save()
            {
                up(1, "Saving current settings for system api '{0}'", this->Name);
                if (this->_file.empty()) {
                    this->_setfile();
                }
                try {
                    std::stringstream ss;
                    ss << "<?xml version=\"1.0\"?>\r\n" <<
                          "<SysAPI xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">\r\n" <<
                          "  <Name>" << this->Name << "</Name>\r\n" <<
                          "  <Link>" << this->Link << "</Link>\r\n" <<
                          "  <SysType>" << this->SysType << "</SysType>\r\n" <<
                          "</SysAPI>";
                    Util::WriteFile(this->_file, ss.str());
                    return omni::io::file::exists(this->_file);
                } catch (const std::exception& ex) {
                    OmniDocuGen::Program::AddError(std::string("Error saving file: ") + this->_file);
                }
                return false;
            }

            bool Save(std::string file)
            {
                this->_file = file;
                return this->Save();
            }

            operator std::string() const
            {
                return this->Name;
            }

            SysAPI& operator=(const SysAPI& cp)
            {
                this->Name = cp.Name;
                this->Link = cp.Link;
                this->SysType = cp.SysType;
                this->References = cp.References;
                this->_file = cp._file;
                return *this;
            }

            bool operator==(const SysAPI& cp) const
            {
                return this->Name == cp.Name &&
                        this->Link == cp.Link &&
                        this->SysType == cp.SysType &&
                        this->References == cp.References &&
                        this->_file == cp._file;
            }

            bool operator<(const SysAPI& b) const
            {
                return this->Name < b.Name;
            }

            static inline bool SortByType(const SysAPI& a, const SysAPI& b)
            {
                if (a.SysType == b.SysType) {
                    return a.Name < b.Name;
                }
                return a.SysType < b.SysType;
            }

            friend std::ostream& operator<<(std::ostream& s, const SysAPI& c)
            {
                s << c.Name;
                return s;
            }

            std::string ToHTML() const
            {
                if (this->Link.empty() && this->Name.empty()) { return std::string(); }
                std::stringstream ss;
                ss << "<li><a href=\"" << this->Link << "\" target=\"_blank\">" << this->Name << "</a><ul>\r\n";
                /*foreach_c (std::string, it, this->References) {
                    ss << "<li><a href=\"htmlsrc/" << *it << ".html\">" << *it << "</a></li>\r\n";
                }*/
                ss << "</ul></li>";
                return ss.str();
            }

            std::string ToFullString(bool view_file, bool view_link) const
            {
                std::stringstream ss;
                ss << this->SysType << " API: "<< this->Name;
                if (view_link) {
                    ss << " (" << this->Link << ")";
                }
                if (view_file) {
                    ss << " at '" << this->_file << "'";
                }
                return ss.str();
            }

        private:
            std::string _file;

            void _setfile()
            {
                std::string nm = omni::string::to_lower(this->Name);
                if (omni::string::contains(nm, "::")) { nm = omni::string::replace_all(nm, "::", "-"); }
                this->_file = omni::io::path::combine(OmniDocuGen::Program::Settings.SystemAPIDirectory, nm) + ".xml";
            }
    };
}

#endif // DOCUGEN_SYSAPI
