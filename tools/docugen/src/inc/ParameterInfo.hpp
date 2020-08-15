#if !defined(DOCUGEN_PARAMINFO)
#define DOCUGEN_PARAMINFO 1

#include <omnilib>
#include "helpers.hpp"
#include "Program.hpp"

namespace OmniDocuGen
{
    /// Defines a structure containing basic parameter information of a function
    class ParameterInformation
    {
        public:
            typedef omni::smart_ptr<ParameterInformation> ptr_t;

            /// Gets the original code value set to this instance
            std::string OriginalCode;
            /// Gets the name of the paramter
            std::string Name;
            /// Gets the type of the paramter (int, std::string, object, etc)
            std::string ParamType;

            /// Default constructor
            ParameterInformation() :
                OriginalCode(),
                Name(),
                ParamType()
            {
            }

            ParameterInformation(const ParameterInformation& cp) :
                OriginalCode(cp.OriginalCode),
                Name(cp.Name),
                ParamType(cp.ParamType)
            {
            }

            /// Construct a new instace from parsed code
            explicit ParameterInformation(const std::string& code) :
                OriginalCode(code),
                Name(),
                ParamType()
            {
                std::string tcode = code;
                if (omni::string::contains(tcode, "=")) {
                    tcode = omni::string::trim(tcode.substr(0, tcode.find("=")));
                }
                int32_t sidx = tcode.rfind(" ");
                if (sidx >= 0) {
                    this->Name = omni::string::trim(tcode.substr(sidx + 1));
                    this->ParamType = omni::string::trim(tcode.substr(0, sidx));
                    if (omni::string::contains(this->Name, "(&") && omni::string::contains(this->Name, ")[")) {
                        std::string tmp = this->Name;
                        int32_t idx = tmp.find("[");
                        this->ParamType += " (&)" + tmp.substr(idx, (tmp.find("]") + 1) - idx);
                        idx = tmp.find("(&") + 2;
                        this->Name = tmp.substr(idx, tmp.find(")") - idx);
                    }
                } else {
                    this->Name = "NaN";
                    this->ParamType = omni::string::trim(tcode);
                }
                bool isr = omni::string::contains(this->Name, "&");
                bool isp = omni::string::contains(this->Name, "*");
                if (isr || isp) {
                    std::string tmp = this->Name;
                    this->Name = tmp.substr(tmp.find((isr ? "&" : "*")) + 1);
                    this->ParamType += omni::string::trim(omni::string::replace(tmp, this->Name, ""));
                }
            }

            /// Construct a new instance with name and type info
            /// <param name="nm">The name of the parameter</param>
            /// <param name="pt">The type (int, std::string, etc.) of the parameter</param>
            ParameterInformation(const std::string& nm, const std::string& pt) :
                OriginalCode(),
                Name(nm),
                ParamType(pt)
            {
            }

            std::string ToString() const
            {
                if (omni::string::contains(this->ParamType, "(&)[")) {
                    return omni::string::replace(this->ParamType, "(&)[", (std::string("(&") + this->Name + std::string(")[")));
                }
                return this->ParamType + std::string(" ") + this->Name;
            }

            /// Gets the a std::stringized value of this instance
            operator std::string() const
            {
                return this->ToString();
            }

            ParameterInformation& operator=(const ParameterInformation& cp)
            {
                this->OriginalCode = cp.OriginalCode;
                this->Name = cp.Name;
                this->ParamType = cp.ParamType;
                return *this;
            }

            bool operator==(const ParameterInformation& cp) const
            {
                return this->OriginalCode == cp.OriginalCode &&
                       this->Name == cp.Name &&
                       this->ParamType == cp.ParamType;
            }

            friend std::ostream& operator<<(std::ostream& os, const ParameterInformation& pi)
            {
                os << pi.ToString();
                return os;
            }

            std::string ToXML()
            {
                std::string xml = "<ParameterInformation>\r\n";
                xml += gen_tag(this->Name, "Name");
                xml += gen_tag(this->ParamType, "ParamType");
                xml += gen_tag(this->OriginalCode, "OriginalCode");
                xml += "</ParameterInformation>";
                return xml;
            }

            static ptr_t FromXML(const std::string& xml)
            {
                ptr_t ret(new ParameterInformation());
                ret->Name = get_tag<std::string>(xml, "Name");
                ret->ParamType = get_tag<std::string>(xml, "ParamType");
                ret->OriginalCode = get_tag<std::string>(xml, "OriginalCode");
                return ret;
            }
    };
}

#endif // DOCUGEN_PARAMINFO
