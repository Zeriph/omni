#if !defined(DOCUGEN_FWEX)
#define DOCUGEN_FWEX 1

#include <omnilib>
#include "helpers.hpp"
#include "DocuSettings.hpp"
#include "Util.hpp"

namespace OmniDocuGen
{
    class FrameworkExample
    {
        public:
            std::string Name;
            std::string Brief;
            std::string Details;
            std::string Example;
            std::string HtmlFile;
            int32_t Index;

            FrameworkExample() :
                Name(),
                Brief(),
                Details(),
                Example(),
                HtmlFile(),
                Index()
            {
            }

            FrameworkExample(const FrameworkExample& cp) :
                Name(cp.Name),
                Brief(cp.Brief),
                Details(cp.Details),
                Example(cp.Example),
                HtmlFile(cp.HtmlFile),
                Index(cp.Index)
            {
            }

            FrameworkExample(std::string dir) :
                Name(),
                Brief(),
                Details(),
                Example(),
                HtmlFile(),
                Index()
            {
                std::string ifile = omni::io::path::combine(dir, "info.txt");
                std::string efile = omni::io::path::combine(dir, "example.cpp");
                std::string sidx = omni::string::to_lower(omni::io::path::get_name(dir));
                this->HtmlFile = sidx.substr(sidx.find('_') + 1) + std::string(".html");
                this->Index = omni::string::util::to_type<int32_t>(sidx.substr(0, sidx.find('_'))) - 1;

                if (omni::io::directory::exists(dir) &&
                    omni::io::file::exists(ifile) &&
                    omni::io::file::exists(efile))
                {
                    std::string info = omni::io::file::get_contents(ifile);
                    int32_t idx = info.find("@name ") + (std::string("@name ").size());
                    int32_t idx2 = info.find("\n", idx);
                    this->Name = omni::string::trim(info.substr(idx, (idx2 - idx)));
                    idx = info.find("@brief ") + (std::string("@brief ").size());
                    idx2 = info.find("\n", idx);
                    this->Brief = omni::string::trim(info.substr(idx, (idx2 - idx)));
                    idx = info.find("@details") + (std::string("@details").size());
                    info = info.substr(idx);
                    this->Details = omni::string::trim(info);
                    this->Example = omni::io::file::get_contents(efile);
                } else {
                    throw omni::exceptions::file_not_found(dir);
                }
            }

            FrameworkExample& operator=(const FrameworkExample& cp)
            {
                this->Name = cp.Name;
                this->Brief = cp.Brief;
                this->Details = cp.Details;
                this->Example = cp.Example;
                this->HtmlFile = cp.HtmlFile;
                this->Index = cp.Index;
                return *this;
            }

            friend std::ostream& operator<<(std::ostream& os, const FrameworkExample& fe)
            {
                os << fe.Name;
                return os;
            }
            
            std::string LiHtml();

            std::string ToHTML();
    };
}

#endif // DOCUGEN_FWEX
