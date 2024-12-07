#if !defined(DOCUGEN_COMMENTINFO)
#define DOCUGEN_COMMENTINFO 1

#include <omnilib>
#include "helpers.hpp"
#include "Constants.hpp"
#include "DocuSettings.hpp"
#include "Types.hpp"
#include "Util.hpp"

namespace OmniDocuGen
{
    class CommentInformation
    {
        public:
            typedef omni::smart_ptr<CommentInformation> ptr_t;

            /// @internal
            bool HasIgnoreFlag;
            /// @brief
            std::string Synopsis;
            /// @details, make note of any @see also
            std::string Description;
            /// @return
            std::string ReturnValue;
            /// @exception
            std::string Errors;
            /// @warning
            std::string Considerations;
            /// @invariant 
            std::string Complexity;
            /// @attention
            std::string PlatformSpecific;
            /// @note
            std::string Notes;
            /// @param/@tparam
            List<std::string> Parameters;

            std::string Example; // pulled from example file
            std::string DocComment;
            std::string OriginalCode;

            CommentInformation() :
                HasIgnoreFlag(),
                Synopsis(),
                Description(),
                ReturnValue(),
                Errors(),
                Considerations(),
                Complexity(),
                PlatformSpecific(),
                Notes(),
                Parameters(),
                Example(),
                DocComment(),
                OriginalCode(),
                _paramHtml()
            { }

            CommentInformation(const std::string& comment, const std::string& fullPath, bool isAnOverLoad, int32_t overloadIndex) :
                HasIgnoreFlag(),
                Synopsis(),
                Description(),
                ReturnValue(),
                Errors(),
                Considerations(),
                Complexity(),
                PlatformSpecific(),
                Notes(),
                Parameters(),
                Example(),
                DocComment(),
                OriginalCode(),
                _paramHtml()
            {
                this->_SetParent(fullPath, isAnOverLoad, overloadIndex);
                this->_ParseComment(comment);
            }

            CommentInformation(const CommentInformation& cp) :
                HasIgnoreFlag(cp.HasIgnoreFlag),
                Synopsis(cp.Synopsis),
                Description(cp.Description),
                ReturnValue(cp.ReturnValue),
                Errors(cp.Errors),
                Considerations(cp.Considerations),
                Complexity(cp.Complexity),
                PlatformSpecific(cp.PlatformSpecific),
                Notes(cp.Notes),
                Parameters(cp.Parameters),
                Example(cp.Example),
                DocComment(cp.DocComment),
                OriginalCode(cp.OriginalCode),
                _paramHtml(cp._paramHtml)
            {
            }            

            void ResetParent(const std::string& fullPath, bool isAnOverLoad, int32_t overloadIndex)
            {
                this->_SetParent(fullPath, isAnOverLoad, overloadIndex);
            }

            List<std::string> HtmlList() const;

            operator std::string() const
            {
                return this->OriginalCode;
            }

            CommentInformation& operator=(const CommentInformation& cp)
            {
                this->HasIgnoreFlag = cp.HasIgnoreFlag;
                this->Synopsis = cp.Synopsis;
                this->Description = cp.Description;
                this->ReturnValue = cp.ReturnValue;
                this->Errors = cp.Errors;
                this->Considerations = cp.Considerations;
                this->Complexity = cp.Complexity;
                this->PlatformSpecific = cp.PlatformSpecific;
                this->Notes = cp.Notes;
                this->Parameters = cp.Parameters;
                this->Example = cp.Example;
                this->DocComment = cp.DocComment;
                this->OriginalCode = cp.OriginalCode;
                this->_paramHtml = cp._paramHtml;
                return *this;
            }

            std::string ToXML() const
            {
                std::string xml = "<CommentInformation>\r\n";
                xml += gen_tag(this->HasIgnoreFlag, "HasIgnoreFlag");
                xml += gen_tag(this->Synopsis, "Synopsis");
                xml += gen_tag(this->Description, "Description");
                xml += gen_tag(this->ReturnValue, "ReturnValue");
                xml += gen_tag(this->Errors, "Errors");
                xml += gen_tag(this->Considerations, "Considerations");
                xml += gen_tag(this->Complexity, "Complexity");
                xml += gen_tag(this->PlatformSpecific, "PlatformSpecific");
                xml += gen_tag(this->Notes, "Notes");
                xml += "<Parameters>";
                foreach_c (std::string, p, this->Parameters) {
                    xml += std::string("<string>") + *p + std::string("</string>");
                }
                xml += "</Parameters>\r\n";
                xml += gen_tag(this->Example, "Example");
                xml += gen_tag(this->DocComment, "DocComment");
                xml += gen_tag(this->OriginalCode, "OriginalCode");
                xml += "</CommentInformation>";
                return xml;
            }

            static ptr_t FromXML(const std::string& xmls)
            {
                std::string xml = xmls.substr(std::string("<CommentInformation>").length());
                xml = xml.substr(0, xml.length() - std::string("</CommentInformation>").length());
                if (xml.empty()) { return ptr_t(); }

                ptr_t ret(new CommentInformation());
                ret->HasIgnoreFlag = omni::string::util::to_type<bool>(OmniDocuGen::Util::GetTagData(xml, "HasIgnoreFlag"));
                xml = OmniDocuGen::Util::RemoveTag(xml, "HasIgnoreFlag");
                ret->Synopsis = OmniDocuGen::Util::GetTagData(xml, "Synopsis");
                xml = OmniDocuGen::Util::RemoveTag(xml, "Synopsis");
                ret->Description = OmniDocuGen::Util::GetTagData(xml, "Description");
                xml = OmniDocuGen::Util::RemoveTag(xml, "Description");
                ret->ReturnValue = OmniDocuGen::Util::GetTagData(xml, "ReturnValue");
                xml = OmniDocuGen::Util::RemoveTag(xml, "ReturnValue");
                ret->Errors = OmniDocuGen::Util::GetTagData(xml, "Errors");
                xml = OmniDocuGen::Util::RemoveTag(xml, "Errors");
                ret->Considerations = OmniDocuGen::Util::GetTagData(xml, "Considerations");
                xml = OmniDocuGen::Util::RemoveTag(xml, "Considerations");
                ret->Complexity = OmniDocuGen::Util::GetTagData(xml, "Complexity");
                xml = OmniDocuGen::Util::RemoveTag(xml, "Complexity");
                ret->PlatformSpecific = OmniDocuGen::Util::GetTagData(xml, "PlatformSpecific");
                xml = OmniDocuGen::Util::RemoveTag(xml, "PlatformSpecific");
                ret->Notes = OmniDocuGen::Util::GetTagData(xml, "Notes");
                xml = OmniDocuGen::Util::RemoveTag(xml, "Notes");
                ret->Parameters.clear(); // = new List<std::string>();

                std::string prs = OmniDocuGen::Util::GetTagData(xml, "Parameters");
                int32_t idx = -1;
                int32_t len = std::string("</string>").length();
                while (!prs.empty()) {
                    ret->Parameters.push_back(OmniDocuGen::Util::GetTagData(prs, "string"));
                    idx = prs.find("</string>");
                    prs = prs.substr(idx + len);
                }
                xml = OmniDocuGen::Util::RemoveTag(xml, "Parameters");
                ret->Example = OmniDocuGen::Util::GetTagData(xml, "Example"); xml = OmniDocuGen::Util::RemoveTag(xml, "Example");
                ret->DocComment = OmniDocuGen::Util::GetTagData(xml, "DocComment"); xml = OmniDocuGen::Util::RemoveTag(xml, "DocComment");
                ret->OriginalCode = OmniDocuGen::Util::GetTagData(xml, "OriginalCode");
                return ret;
            }

        private:
            std::string _paramHtml;

            std::string _GetCommentTagData(const std::string& tag, const std::string& def)
            {
                if (omni::string::contains(this->DocComment, tag)) {
                    try {
                        std::string r = this->DocComment.substr(this->DocComment.find(tag) + tag.length());
                        int32_t idx = -1;
                        size_t i;
                        foreach (std::string, t, OmniDocuGen::Constants::Keywords::DoxyCommentTags) {
                            if (OmniDocuGen::Program::StopReq) { return ""; }
                            i = r.find(*t);
                            if (i == std::string::npos) { continue; }
                            if (idx < 0) { idx = i; }
                            if (i < idx) { idx = i; }
                        }
                        if (idx > 0) { r = r.substr(0, idx); }
                        r = omni::string::trim(r);
                        if (!r.empty()) { return r; }
                    } catch (const std::exception& ex) {
                        OmniDocuGen::Program::AddError(ex);
                    }
                }
                return def;
            }

            List<std::string> _GetCommentParamTagData()
            {
                List<std::string> ret;
                this->_paramHtml = "";
                if (!omni::string::contains(this->DocComment, "@param") &&
                    !omni::string::contains(this->DocComment, "@tparam"))
                { return ret; }

                List<int32_t> pidx = OmniDocuGen::Util::IndexesOf(this->DocComment, "@param");
                List<int32_t> tidx = OmniDocuGen::Util::IndexesOf(this->DocComment, "@tparam");
                int32_t tlen = std::string("@tparam").length();
                int32_t len = std::string("@param").length();
                int32_t i = -1;
                size_t idx;
                std::string tmp;
                std::string consts[] = { "<code>", "</code> - ", "\r\n" };
                List<std::string>::const_iterator tag;
                List<int32_t>::iterator x;
                for (x = pidx.begin(); x != pidx.end(); ++x) {
                    if (OmniDocuGen::Program::StopReq) { return ret; }
                    tmp = this->DocComment.substr(*x + len);
                    i = -1;
                    for (tag = OmniDocuGen::Constants::Keywords::DoxyCommentTags.begin();
                         tag != OmniDocuGen::Constants::Keywords::DoxyCommentTags.end(); ++tag)
                    {
                        if (OmniDocuGen::Program::StopReq) { return ret; }
                        idx = tmp.find(*tag);
                        if (idx == std::string::npos) { continue; }
                        if (i < 0) { i = idx; }
                        if (idx < i) { i = idx; }
                    }
                    if (i >= 0) { tmp = omni::string::trim(tmp.substr(0, i)); }
                    tmp = omni::string::trim(omni::string::replace_all(tmp, "\r\n", " "));
                    this->_paramHtml += consts[0] + omni::string::trim(tmp.substr(0, tmp.find(" "))) +
                                        consts[1] + omni::string::trim(tmp.substr(tmp.find(" "))) + consts[2];
                    ret.push_back(tmp);
                }
                for (x = tidx.begin(); x != tidx.end(); ++x) {
                    if (OmniDocuGen::Program::StopReq) { return ret; }
                    tmp = this->DocComment.substr(*x + tlen);
                    i = -1;
                    for (tag = OmniDocuGen::Constants::Keywords::DoxyCommentTags.begin();
                         tag != OmniDocuGen::Constants::Keywords::DoxyCommentTags.end(); ++tag)
                    {
                        if (OmniDocuGen::Program::StopReq) { return ret; }
                        idx = tmp.find(*tag);
                        if (idx == std::string::npos) { continue; }
                        if (i < 0) { i = idx; }
                        if (idx < i) { i = idx; }
                    }
                    if (i >= 0) { tmp = omni::string::trim(tmp.substr(0, i)); }
                    tmp = omni::string::trim(omni::string::replace_all(tmp, "\r\n", " "));
                    this->_paramHtml += consts[0] + omni::string::trim(tmp.substr(0, tmp.find(" "))) +
                                        consts[1] + omni::string::trim(tmp.substr(tmp.find(" "))) + consts[2];
                    ret.push_back(tmp);
                }
                return ret;
            }

            void _ParseComment(std::string comment)
            {
                try {
                    if (!comment.empty()) {
                        this->OriginalCode = comment;
                        this->DocComment = omni::string::trim(OmniDocuGen::Util::StripDocCommentStars(comment));
                        this->HasIgnoreFlag = omni::string::contains(this->DocComment, "@internal");
                        this->Description = this->_GetCommentTagData("@details", "No description.");
                        this->ReturnValue = this->_GetCommentTagData("@return", "");
                        this->Errors = this->_GetCommentTagData("@exception", "");
                        this->Considerations = this->_GetCommentTagData("@warning", "");
                        this->PlatformSpecific = this->_GetCommentTagData("@attention", "");
                        this->Notes = this->_GetCommentTagData("@note", "");
                        this->Complexity = this->_GetCommentTagData("@invariant", "");
                        this->Synopsis = this->_GetCommentTagData("@brief", "");
                        if (this->Synopsis == "") {
                            int32_t i = -1;
                            List<size_t> idxs;
                            idxs.push_back(this->DocComment.find("@details"));
                            idxs.push_back(this->DocComment.find("@return"));
                            idxs.push_back(this->DocComment.find("@exception"));
                            idxs.push_back(this->DocComment.find("@warning"));
                            idxs.push_back(this->DocComment.find("@attention"));
                            idxs.push_back(this->DocComment.find("@note"));
                            idxs.push_back(this->DocComment.find("@invariant"));
                            idxs.push_back(this->DocComment.find("@param"));
                            idxs.push_back(this->DocComment.find("@tparam"));
                            
                            foreach (size_t, it, idxs) {
                                if (OmniDocuGen::Program::StopReq) { return; }
                                if (*it == std::string::npos) { continue; }
                                if (i < 0) { i = static_cast<int32_t>(*it); }
                                if (*it < i) { i = *it; }
                            }
                            if (i >= 0) {
                                this->Synopsis = omni::string::trim(this->DocComment.substr(0, i));
                            } else {
                                this->Synopsis = (this->DocComment.empty() ? "No synopsis." : this->DocComment);
                            }
                            this->Synopsis = omni::string::replace_all(this->Synopsis, "\r\n", " ");
                        }
                        this->Parameters = this->_GetCommentParamTagData();
                    } else {
                        this->OriginalCode = "";
                        this->DocComment = "";
                        this->HasIgnoreFlag = false;
                        this->Description = "No description.";
                        this->Synopsis = "No synopsis.";
                        this->Parameters.clear();
                        this->ReturnValue = "";
                        this->Errors = "";
                        this->Considerations = "";
                        this->PlatformSpecific = "";
                        this->Notes = "";
                        this->Complexity = "";
                    }
                } catch (const std::exception& ex) {
                    OmniDocuGen::Program::AddError(ex);
                }
            }

            void _SetParent(const std::string& fullPath, bool isAnOverload, int32_t overloadIndex)
            {
                try {
                    std::string fpath = omni::string::replace_all(OmniDocuGen::Util::ToFilePath(fullPath), "@@", "-");
                    fpath = omni::string::replace_all(fpath, "-", "/");
                    std::string edoc = omni::io::path::combine(OmniDocuGen::Program::Settings.ClassExampleDirectory(),
                                                        ((isAnOverload ? (fpath + omni::string::to_string(overloadIndex)) : fpath) + ".cpp"));
                    this->Example = (omni::io::file::exists(edoc) ? omni::io::file::get_contents(edoc) : "");
                } catch (const std::exception& ex) {
                    OmniDocuGen::Program::AddError(ex);
                }
            }
    };
}

#endif // DOCUGEN_COMMENTINFO
