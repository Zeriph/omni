#include "inc/MemberTypeInformation.hpp"

static std::string replace_special_omni_macros(std::string code)
{
    std::string nm, spcs, rep;
    std::string OMF = "OMNI_MEMBERS_FW(";
    std::string OMFMT = OmniDocuGen::Program::Settings.CommentOmniMembersFw;
    size_t nlb, sp;
    size_t pos = code.find(OMF);
    while (pos != std::string::npos) {
        /*
            OMNI_MEMBERS_FW(omni::application::argparser) // disposing,name,type(),hash()

            omni::event1<void, const {1}& > disposing;
            omni::string_t name;
            uint64_t type() const { return omni::type_id<{1}>(); }
            uint64_t hash() const { return reinterpret_cast<uint64_t>(this); }
        */
        nlb = code.rfind("\n", pos);
        spcs = code.substr(nlb, (pos - nlb));
        sp = code.find("(", pos) + 1;
        nm = code.substr(sp, code.find(")", sp) - sp);        
        rep = OmniDocuGen::Util::Format(OMFMT, spcs, nm);
        code.replace(pos, (code.find("\n", pos) - pos), rep);
        pos = code.find(OMF);
    }

    OMF = "OMNI_OSTREAM_FW(";
    OMFMT = OmniDocuGen::Program::Settings.CommentOmniOstreamFw;
    pos = code.find(OMF);
    while (pos != std::string::npos) {
        /*
            OMNI_OSTREAM_FW(omni::application::argparser)

            friend std::ostream& operator<<(std::ostream& s, const {1}& c) { s << c.v; return s; }
            friend std::wostream& operator<<(std::wostream& s, const {1}& c) { s << c.v; return s; }
        */
        nlb = code.rfind("\n", pos);
        spcs = code.substr(nlb, (pos - nlb));
        sp = code.find("(", pos) + 1;
        nm = code.substr(sp, code.find(")", sp) - sp);        
        rep = OmniDocuGen::Util::Format(OMFMT, spcs, nm);
        code.replace(pos, (code.find("\n", pos) - pos), rep);
        pos = code.find(OMF);
    }
    
    OMF = "OMNI_OSTREAM_FN_FW(";
    OMFMT = OmniDocuGen::Program::Settings.CommentOmniOstreamFnFw;
    pos = code.find(OMF);
    while (pos != std::string::npos) {
        /*
            OMNI_OSTREAM_FN_FW(enum_t)
            friend std::ostream& operator<<(std::ostream& s, const {1}& c) { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const {1}& c) { s << to_wstring(c); return s; }
        */
        nlb = code.rfind("\n", pos);
        spcs = code.substr(nlb, (pos - nlb));
        sp = code.find("(", pos) + 1;
        nm = code.substr(sp, code.find(")", sp) - sp);        
        rep = OmniDocuGen::Util::Format(OMFMT, spcs, nm);
        code.replace(pos, (code.find("\n", pos) - pos), rep);
        pos = code.find(OMF);
    }
    return code;
}

// public
OmniDocuGen::MemberTypeInformation::MemberTypeInformation() :
    CodeType(),
    Comment(),
    FullPath(),
    Index(),
    InheritedFrom(),
    IsStatic(),
    IsInline(),
    IsExplicit(),
    Level(),
    Members(),
    Name(),
    NamespaceAlias(),
    OriginalCode(),
    //Owner(),
    OwnerSourceFile(),
    Overloads(),
    OverloadIndex(),
    Parent(),
    Parameters(),
    ReturnType(),
    ScopeAccessType(OmniDocuGen::Types::CodeScopeAcessType::Public),
    Template(),
    TemplateSpecialization(),
    ImplFile(),
    HeaderFile(),
    FoundAtLine(-1),
    SourceImplLine(-1),
    HeaderLine(-1),
    Signature(),
    Include(),
    This(MemberTypeInformation::ptr_t::get_instance_reference(this))
{
    this->Comment = new CommentInformation("", this->FullPath, this->IsAnOverload(), this->OverloadIndex);
    up(3, "Created default MTI()");
}

OmniDocuGen::MemberTypeInformation::MemberTypeInformation(OmniDocuGen::MemberTypeInformation& cp) :
    CodeType(cp.CodeType),
    Comment(),
    FullPath(cp.FullPath),
    Index(cp.Index),
    InheritedFrom(cp.InheritedFrom),
    IsStatic(cp.IsStatic),
    IsInline(cp.IsInline),
    IsExplicit(cp.IsExplicit),
    Level(cp.Level),
    Members(),
    Name(cp.Name),
    NamespaceAlias(cp.NamespaceAlias),
    OriginalCode(cp.OriginalCode),
    //Owner(cp.Owner),
    OwnerSourceFile(cp.OwnerSourceFile),
    Overloads(cp.Overloads),
    OverloadIndex(cp.OverloadIndex),
    Parent(cp.Parent),
    Parameters(cp.Parameters),
    ReturnType(cp.ReturnType),
    ScopeAccessType(),
    Template(cp.Template),
    TemplateSpecialization(cp.TemplateSpecialization),
    ImplFile(cp.ImplFile),
    HeaderFile(cp.HeaderFile),
    FoundAtLine(cp.FoundAtLine),
    SourceImplLine(cp.SourceImplLine),
    HeaderLine(cp.HeaderLine),
    Signature(cp.Signature),
    Include(cp.Include),
    This(MemberTypeInformation::ptr_t::get_instance_reference(this))
{
    up(3, "Created copy constructed MTI()");
    foreach (ptr_t, m, cp.Members) {
        if (OmniDocuGen::Program::StopReq) { break; }
        //this->AddVerify(m->DeepCopy()); // does the overloads
        this->AddVerify(*m); // does the overloads
    }
    if (this->Parent) {
        this->Parent->AddVerify(cp.This);
    }
    if (this->FullPath.empty()) {
        this->FullPath = this->Name;
    }
    this->Comment = new CommentInformation(cp.Comment->OriginalCode, this->FullPath, this->IsAnOverload(), this->OverloadIndex);
    if (this->Comment->HasIgnoreFlag) {
        this->ScopeAccessType = OmniDocuGen::Types::CodeScopeAcessType::Private;
    }
}

OmniDocuGen::MemberTypeInformation::MemberTypeInformation(bool xml, const std::string& srcFile) :
    CodeType(),
    Comment(),
    FullPath(),
    Index(),
    InheritedFrom(),
    IsStatic(),
    IsInline(),
    IsExplicit(),
    Level(),
    Members(),
    Name(),
    NamespaceAlias(),
    OriginalCode(),
    //Owner(owner),
    OwnerSourceFile(srcFile),
    Overloads(),
    OverloadIndex(),
    Parent(),
    Parameters(),
    ReturnType(),
    ScopeAccessType(OmniDocuGen::Types::CodeScopeAcessType::Public),
    Template(),
    TemplateSpecialization(),
    ImplFile(),
    HeaderFile(),
    FoundAtLine(-1),
    SourceImplLine(-1),
    HeaderLine(-1),
    Signature(),
    Include(),
    This(MemberTypeInformation::ptr_t::get_instance_reference(this))
{
    this->Comment = new CommentInformation("", this->FullPath, this->IsAnOverload(), this->OverloadIndex);
    up(3, "Created MTI() from XML and SRCFILE");
}

/// Construct a new type information parsed from the specified code
/// <param name="code">The code to parse</param>
OmniDocuGen::MemberTypeInformation::MemberTypeInformation(const std::string& code) :
    CodeType(),
    Comment(),
    FullPath(),
    Index(),
    InheritedFrom(),
    IsStatic(),
    IsInline(),
    IsExplicit(),
    Level(),
    Members(),
    Name(),
    NamespaceAlias(),
    OriginalCode(code),
    //Owner(),
    OwnerSourceFile(),
    Overloads(),
    OverloadIndex(),
    Parent(),
    Parameters(),
    ReturnType(),
    ScopeAccessType(OmniDocuGen::Types::CodeScopeAcessType::Public),
    Template(),
    TemplateSpecialization(),
    ImplFile(),
    HeaderFile(),
    FoundAtLine(-1),
    SourceImplLine(-1),
    HeaderLine(-1),
    Signature(),
    Include(),
    This(MemberTypeInformation::ptr_t::get_instance_reference(this))
{
    this->Comment = new CommentInformation("", this->FullPath, this->IsAnOverload(), this->OverloadIndex);
    up(3, "Created MTI() from CODE");
    this->_Parse(code, OmniDocuGen::Types::MemberParseType::AsNamespace);
}

OmniDocuGen::MemberTypeInformation::MemberTypeInformation(const std::string& code, const std::string& srcFile, const std::string& hFile, const std::string& srcCode) :
    CodeType(),
    Comment(),
    FullPath(),
    Index(),
    InheritedFrom(),
    IsStatic(),
    IsInline(),
    IsExplicit(),
    Level(),
    Members(),
    Name(),
    NamespaceAlias(),
    OriginalCode(code),
    //Owner(),
    OwnerSourceFile(),
    Overloads(),
    OverloadIndex(),
    Parent(),
    Parameters(),
    ReturnType(),
    ScopeAccessType(OmniDocuGen::Types::CodeScopeAcessType::Public),
    Template(),
    TemplateSpecialization(),
    ImplFile(),
    HeaderFile(),
    FoundAtLine(-1),
    SourceImplLine(-1),
    HeaderLine(-1),
    Signature(),
    Include(),
    This(MemberTypeInformation::ptr_t::get_instance_reference(this))
{
    this->Comment = new CommentInformation("", this->FullPath, this->IsAnOverload(), this->OverloadIndex);
    up(3, "Created MTI() from CODE, SRCFILE, HFILE, SRCCODE");
    this->_Parse(replace_special_omni_macros(code), OmniDocuGen::Types::MemberParseType::AsNamespace);
    this->SetOwnerInfoAndLinkIndex(srcFile, hFile, srcCode);
}

// This constructor is used to generate "special" headers (like cconst/wconsts, etc.)
OmniDocuGen::MemberTypeInformation::MemberTypeInformation(const std::string& code, const std::string& srcFile, const std::string& hFile, const std::string& srcCode, OmniDocuGen::MemberTypeInformation::ptr_t& allmti) :
    CodeType(),
    Comment(),
    FullPath(),
    Index(),
    InheritedFrom(),
    IsStatic(),
    IsInline(),
    IsExplicit(),
    Level(),
    Members(),
    Name(),
    NamespaceAlias(),
    OriginalCode(code),
    //Owner(),
    OwnerSourceFile(),
    Overloads(),
    OverloadIndex(),
    Parent(),
    Parameters(),
    ReturnType(),
    ScopeAccessType(OmniDocuGen::Types::CodeScopeAcessType::Public),
    Template(),
    TemplateSpecialization(),
    ImplFile(),
    HeaderFile(),
    FoundAtLine(-1),
    SourceImplLine(-1),
    HeaderLine(-1),
    Signature(),
    Include(),
    This(MemberTypeInformation::ptr_t::get_instance_reference(this))
{
    this->Comment = new CommentInformation("", this->FullPath, this->IsAnOverload(), this->OverloadIndex);
    up(3, "Created MTI() from CODE, SRCFILE, HFILE, SRCCODE, ALLMTI");
    this->_Parse(code, OmniDocuGen::Types::MemberParseType::AsNamespace);
    this->SetOwnerInfoAndLinkIndex(srcFile, hFile, srcCode);
    this->LinkSources(allmti);
}

OmniDocuGen::MemberTypeInformation::MemberTypeInformation(const std::string& name, int32_t index, OmniDocuGen::Types::CodeStructureType ct, OmniDocuGen::MemberTypeInformation::ptr_t& parent) :
    CodeType(ct),
    Comment(),
    FullPath(name),
    Index(),
    InheritedFrom(),
    IsStatic(),
    IsInline(),
    IsExplicit(),
    Level(),
    Members(),
    Name(name),
    NamespaceAlias(),
    OriginalCode(),
    //Owner(),
    OwnerSourceFile(),
    Overloads(),
    OverloadIndex(),
    Parent(parent),
    Parameters(),
    ReturnType(),
    ScopeAccessType(OmniDocuGen::Types::CodeScopeAcessType::Public),
    Template(),
    TemplateSpecialization(),
    ImplFile(),
    HeaderFile(),
    FoundAtLine(-1),
    SourceImplLine(-1),
    HeaderLine(-1),
    Signature(),
    Include(),
    This(MemberTypeInformation::ptr_t::get_instance_reference(this))
{
    this->Comment = new CommentInformation("", this->FullPath, this->IsAnOverload(), this->OverloadIndex);
    up(3, "Created MTI() from NAME, INDEX, CST, PARENT");
}

/// Construct a new type information parsed from the specified code
/// <param name="code">The code to parse</param>
/// <param name="prnt">The parent</param>
OmniDocuGen::MemberTypeInformation::MemberTypeInformation(const std::string& code, OmniDocuGen::MemberTypeInformation::ptr_t& prnt) :
    CodeType(),
    Comment(),
    FullPath(),
    Index(),
    InheritedFrom(),
    IsStatic(),
    IsInline(),
    IsExplicit(),
    Level(),
    Members(),
    Name(),
    NamespaceAlias(),
    OriginalCode(code),
    //Owner(),
    OwnerSourceFile(),
    Overloads(),
    OverloadIndex(),
    Parent(prnt),
    Parameters(),
    ReturnType(),
    ScopeAccessType(OmniDocuGen::Types::CodeScopeAcessType::Public),
    Template(),
    TemplateSpecialization(),
    ImplFile(),
    HeaderFile(),
    FoundAtLine(-1),
    SourceImplLine(-1),
    HeaderLine(-1),
    Signature(),
    Include(),
    This(MemberTypeInformation::ptr_t::get_instance_reference(this))
{
    this->Comment = new CommentInformation("", this->FullPath, this->IsAnOverload(), this->OverloadIndex);
    up(3, "Created MTI() from CODE, PARENT");
    this->_Parse(code, OmniDocuGen::Types::MemberParseType::AsClass);
}

/// Construct a new type information parsed from the specified code,
/// specifying a code structure of either Typedef or Member.
/// <param name="code">The code to parse</param>
/// <param name="prnt">The parent</param>
/// <param name="cst">The OmniDocuGen::Types::CodeStructureType to set to</param>
OmniDocuGen::MemberTypeInformation::MemberTypeInformation(const std::string& code, OmniDocuGen::MemberTypeInformation::ptr_t& prnt, OmniDocuGen::Types::MemberParseType mpt) :
    CodeType(),
    Comment(),
    FullPath(),
    Index(),
    InheritedFrom(),
    IsStatic(),
    IsInline(),
    IsExplicit(),
    Level(),
    Members(),
    Name(),
    NamespaceAlias(),
    OriginalCode(code),
    //Owner(),
    OwnerSourceFile(),
    Overloads(),
    OverloadIndex(),
    Parent(prnt),
    Parameters(),
    ReturnType(),
    ScopeAccessType(OmniDocuGen::Types::CodeScopeAcessType::Public),
    Template(),
    TemplateSpecialization(),
    ImplFile(),
    HeaderFile(),
    FoundAtLine(-1),
    SourceImplLine(-1),
    HeaderLine(-1),
    Signature(),
    Include(),
    This(MemberTypeInformation::ptr_t::get_instance_reference(this))
{
    this->Comment = new CommentInformation("", this->FullPath, this->IsAnOverload(), this->OverloadIndex);
    up(3, "Created MTI() from CODE, PARENT, MPT");
    this->_Parse(code, mpt);
}

/// Adds a new node to this instance
/// <param name="ti">The type information to add</param>
void OmniDocuGen::MemberTypeInformation::Add(OmniDocuGen::MemberTypeInformation::ptr_t& ti)
{
    if (ti) {
        if (ti->Name.empty()) {
            if (ti->Members.size() > 0) {
                foreach (ptr_t, m, ti->Members) {
                    if (OmniDocuGen::Program::StopReq) { return; }
                    this->_Add(*m);
                }
                std::sort(this->Members.begin(), this->Members.end(), OmniDocuGen::MemberTypeInformation::CompareMemberTypeInformation);
            } else {
                up(4,
                    "An invalid member was detected in source file '{0}', name: {1}\n"
                    "--Start original code for '{2}' in file '{3}'--\n"
                    "{4}\n"
                    "--End original code--",
                    this->OwnerSourceFile,
                    this->Name,
                    ti->Name,
                    ti->OwnerSourceFile,
                    ti->OriginalCode
                );
            }
        } else {
            this->_Add(ti);
            std::sort(this->Members.begin(), this->Members.end(), OmniDocuGen::MemberTypeInformation::CompareMemberTypeInformation);
        }
    }
}

/// Adds a node to this instance if it doesn't exists, otherwise adds its members
/// <param name="ti">The type information to add</param>
void OmniDocuGen::MemberTypeInformation::AddVerify(OmniDocuGen::MemberTypeInformation::ptr_t& ti)
{
    if (!ti) { return; }
    bool same = (this->Name == ti->Name);
    if (same) {
        // if names are equal, then they might be the same one
        if (this->This == ti || this->Equals(ti)) { return; }
        // if it's a function and it's ==, then it's an overload
        if (this->CodeType == OmniDocuGen::Types::CodeStructureType::Operator ||
            this->CodeType == OmniDocuGen::Types::CodeStructureType::Function ||
            this->CodeType == OmniDocuGen::Types::CodeStructureType::Ctor ||
            this->CodeType == OmniDocuGen::Types::CodeStructureType::Member)
        {
            ti->OverloadIndex = this->Overloads.size() + 1;
            this->Overloads.push_back(ti);
            return; // short-circuit
        } else {
            // not a function, then add the members of it to this instance
            foreach (ptr_t, m, ti->Members) {
                if (OmniDocuGen::Program::StopReq) { return; }
                this->AddVerify(*m);
            }
            same = (ti->Members.size() > 0);
        }
    }
    if (!same) {
        bool found = false;
        foreach (ptr_t, m, this->Members) {
            if (OmniDocuGen::Program::StopReq) { return; }
            if (ti->Name == (*m)->Name) {
                (*m)->AddVerify(ti);
                found = true;
                break;
            }
        }
        if (!found) {
            this->Add(ti);
        }
    }
}

/// Makes a deep copy of the current object
/// <returns>A new copy of the current object</returns>
/*
OmniDocuGen::MemberTypeInformation::ptr_t OmniDocuGen::MemberTypeInformation::DeepCopy()
{
    return MemberTypeInformation(*this);
}
*/

bool OmniDocuGen::MemberTypeInformation::Equals(const OmniDocuGen::MemberTypeInformation& mti) const
{
    if (this == &mti) { return true; }
    return (mti.CodeType == this->CodeType &&
            ((mti.Comment && this->Comment) &&
            (mti.Comment->OriginalCode == this->Comment->OriginalCode)) &&
            mti.FullPath == this->FullPath &&
            mti.Template == this->Template &&
            mti.Index == this->Index &&
            mti.InheritedFrom == this->InheritedFrom &&
            mti.Level == this->Level &&
            mti.Name == this->Name &&
            mti.OriginalCode == this->OriginalCode &&
            mti.ReturnType == this->ReturnType &&
            mti.ScopeAccessType == this->ScopeAccessType &&
            omni::sequence::equals(mti.Parameters, this->Parameters) &&
            mti.OwnerSourceFile == this->OwnerSourceFile &&
            mti.IsInline == this->IsInline &&
            mti.IsExplicit == this->IsExplicit &&
            mti.IsOverloaded() == this->IsOverloaded() &&
            mti.IsStatic == this->IsStatic &&
            mti.ImplFile == this->ImplFile &&
            mti.HeaderFile == this->HeaderFile &&
            mti.FoundAtLine == this->FoundAtLine &&
            mti.SourceImplLine == this->SourceImplLine &&
            mti.HeaderLine == this->HeaderLine &&
            omni::sequence::equals(mti.Members, this->Members) &&
            mti.Parent == this->Parent &&
            mti.FullPath == this->FullPath);
}

bool OmniDocuGen::MemberTypeInformation::Equals(OmniDocuGen::MemberTypeInformation::ptr_t& mti) const
{
    if (mti) {
        return this->Equals(*mti);
    }
    return false;
}

/// Finds a MemberTypeInformation object in this member list
/// <param name="m">The member to find</param>
OmniDocuGen::MemberTypeInformation::ptr_t OmniDocuGen::MemberTypeInformation::Find(OmniDocuGen::MemberTypeInformation::ptr_t& m)
{
    if (m->FullPath == this->FullPath) { return this->This; }
    ptr_t r;
    foreach (ptr_t, mi, this->Members) {
        if (OmniDocuGen::Program::StopReq) { return r; }
        if (m->FullPath == (*mi)->FullPath) {
            r = *mi;
            break;
        } else {
            r = (*mi)->Find(m);
            if (r) { break; }
        }
    }
    return r;
}

/// Finds a MemberTypeInformation object in this member list
/// <param name="full_path">The full path of the member to find</param>
OmniDocuGen::MemberTypeInformation::ptr_t OmniDocuGen::MemberTypeInformation::Find(const std::string& full_path)
{
    if (this->FullPath == full_path) { return this->This; }
    ptr_t r;
    foreach (ptr_t, mti, this->Members) {
        if (OmniDocuGen::Program::StopReq) { return r; }
        if ((*mti)->FullPath == full_path) {
            r = *mti;
            break;
        } else {
            r = (*mti)->Find(full_path);
            if (r) { break; }
        }
    }
    return r;
}

/// Gets the number of nodes this instance has
/// <param name="includeSubTrees">If true, all nodes within this node will be counted (not just top)</param>
/// <returns>The number of nodes within this branch</returns>
int32_t OmniDocuGen::MemberTypeInformation::GetNodeCount(bool includeSubTrees)
{
    int32_t r = this->Members.size();
    if (includeSubTrees) {
        List<ptr_t>::iterator t = this->Members.begin();
        foreach (ptr_t, t, this->Members) {
            if (OmniDocuGen::Program::StopReq) { return 0; }
            r += (*t)->GetNodeCount(true);
        }
    }
    return r;
}

/// Gets the full signature of this instance (i.e. omni::name::function(p1, p2)...)
/// <param name="fp">True to use the full path (omni::name::function), false to use just name</param>
/// <param name="fpdesc">True to use the full parameter description, false to use just the type (no name)</param>
std::string OmniDocuGen::MemberTypeInformation::GetSignature(bool fp, bool fpdesc)
{
    if (this->IsNamespaceAlias()) {
        return this->NamespaceAlias; //(fp ? omni::string::replace(this->FullPath, this->Name, "") : "") + this->NamespaceAlias;
    }
    std::string r;
    if (this->IsTemplated()) { r += omni::string::trim(this->Template) + " "; }
    if (this->IsExplicit) { r += "explicit "; }
    if (this->IsStatic) { r += "static "; }
    if (this->IsInline) { r += "inline "; }
    r += this->ReturnType + " ";
    r += omni::string::trim((fp ? this->FullPath : this->Name));
    if (OmniDocuGen::Util::IsTypedef(this->CodeType)) { r = "typedef " + r; }
    if (OmniDocuGen::Util::IsFunction(this->CodeType) || this->Parameters.size() > 0) {
        r += "(";
        for (int32_t i = 0; i < this->Parameters.size(); i++) {
            r += (fpdesc ? static_cast<std::string>(*(this->Parameters[i])) : this->Parameters[i]->ParamType);
            if ((i + 1) < this->Parameters.size()) { r += ", "; }
        }
        r += ")";
    }
    return r;
}

/// Gets this instances file path
std::string OmniDocuGen::MemberTypeInformation::GetFilePath() const
{
    if (this->IsAnOverload()) {
        return OmniDocuGen::Util::ToFilePath(this->FullPath + omni::string::to_string(this->OverloadIndex));
    }
    return OmniDocuGen::Util::ToFilePath(this->FullPath);
}

bool OmniDocuGen::MemberTypeInformation::MembersHaveMembes()
{
    if (this->Members.size() > 0) {
        foreach (ptr_t, m, this->Members) {
            if ((*m)->Members.size() > 0) { return true; }
        }
    }
    return false;
}

/// Gets the name of this instance
OmniDocuGen::MemberTypeInformation::operator std::string() const
{
    return this->Name;
}

bool OmniDocuGen::MemberTypeInformation::operator==(const MemberTypeInformation& cp) const
{
    return this->Equals(cp);
}

bool OmniDocuGen::MemberTypeInformation::operator==(ptr_t cp) const
{
    if (!cp) return false;
    return this->Equals(*cp);
}

OmniDocuGen::MemberTypeInformation& OmniDocuGen::MemberTypeInformation::operator=(const OmniDocuGen::MemberTypeInformation& cp)
{
    this->CodeType = cp.CodeType;
    this->Comment = cp.Comment;
    this->FullPath = cp.FullPath;
    this->Index = cp.Index;
    this->InheritedFrom = cp.InheritedFrom;
    this->IsStatic = cp.IsStatic;
    this->IsInline = cp.IsInline;
    this->IsExplicit = cp.IsExplicit;
    this->Level = cp.Level;
    this->Members = cp.Members;
    this->Name = cp.Name;
    this->NamespaceAlias = cp.NamespaceAlias;
    this->OriginalCode = cp.OriginalCode;
    //this->Owner = cp.Owner;
    this->OwnerSourceFile = cp.OwnerSourceFile;
    this->Overloads = cp.Overloads;
    this->OverloadIndex = cp.OverloadIndex;
    this->Parent = cp.Parent;
    this->Parameters = cp.Parameters;
    this->ReturnType = cp.ReturnType;
    this->ScopeAccessType = cp.ScopeAccessType;
    this->Template = cp.Template;
    this->TemplateSpecialization = cp.TemplateSpecialization;
    this->ImplFile = cp.ImplFile;
    this->HeaderFile = cp.HeaderFile;
    this->FoundAtLine = cp.FoundAtLine;
    this->SourceImplLine = cp.SourceImplLine;
    this->HeaderLine = cp.HeaderLine;
    this->Signature = cp.Signature;
    this->Include = cp.Include;
    return *this;
}

std::string OmniDocuGen::MemberTypeInformation::ToXML() const
{
    std::string xml = "<MemberTypeInformation>\r\n";
    xml += gen_tag(this->Name, "Name");
    xml += gen_tag(this->FullPath, "FullPath");
    xml += gen_tag(this->Signature, "Signature");
    xml += gen_tag(this->InheritedFrom, "InheritedFrom");
    xml += gen_tag(this->NamespaceAlias, "NamespaceAlias");
    xml += gen_tag(this->ReturnType, "ReturnType");
    xml += gen_tag(this->Template, "Template");
    xml += gen_tag(this->TemplateSpecialization, "TemplateSpecialization");
    xml += gen_tag(this->ImplFile, "ImplFile");
    xml += gen_tag(this->HeaderFile, "HeaderFile");
    xml += gen_tag(this->Include, "Include");
    xml += gen_tag(this->Level, "Level");
    xml += gen_tag(this->Index, "Index");
    xml += gen_tag(this->OverloadIndex, "OverloadIndex");
    xml += gen_tag(this->FoundAtLine, "FoundAtLine");
    xml += gen_tag(this->SourceImplLine, "SourceImplLine");
    xml += gen_tag(this->HeaderLine, "HeaderLine");
    xml += gen_tag(this->CodeType, "CodeType");
    xml += gen_tag(this->ScopeAccessType, "ScopeAccessType");
    xml += gen_tag(this->IsStatic, "IsStatic");
    xml += gen_tag(this->IsInline, "IsInline");
    xml += gen_tag(this->IsExplicit, "IsExplicit");
    xml += gen_tag(this->OriginalCode, "OriginalCode");
    xml += gen_tag(("\r\n" + this->Comment->ToXML() + "\r\n"), "Comment");
    xml += "<Parameters>\r\n";
    if (this->Parameters.size() > 0) {
        List<ParameterInformation::ptr_t>::const_iterator pi = this->Parameters.begin();
        for (; pi != this->Parameters.end(); ++pi) {
            if (OmniDocuGen::Program::StopReq) { return ""; }
            xml += (*pi)->ToXML() + "\r\n";
        }
    }
    xml += "</Parameters>\r\n<Overloads>\r\n";
    List<ptr_t>::const_iterator m;
    for (m = this->Overloads.begin(); m != this->Overloads.end(); ++m) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        xml += (*m)->ToXML() + "\r\n";
    }
    xml += "</Overloads>\r\n<Members>\r\n";
    for (m = this->Members.begin(); m != this->Members.end(); ++m) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        xml += (*m)->ToXML() + "\r\n";
    }
    xml += "</Members>\r\n</MemberTypeInformation>";
    return xml;
}

void OmniDocuGen::MemberTypeInformation::SetOwnerInfoAndLinkIndex(const std::string& src, const std::string& hdr, const std::string& code)
{
    std::string srcdir = (omni::string::ends_with(OmniDocuGen::Program::Settings.SourceDirectory, OMNI_PATH_SEPARATOR) ? OmniDocuGen::Program::Settings.SourceDirectory : (OmniDocuGen::Program::Settings.SourceDirectory + OMNI_PATH_SEPARATOR));
    //this->Owner = cg;
    this->OwnerSourceFile = src;
    this->HeaderFile = hdr;
    this->ImplFile = src;
    int32_t tln = code.find(OmniDocuGen::Util::StripComment(this->OriginalCode));
    this->FoundAtLine = ((tln > 0) ? OmniDocuGen::Util::SplitAtEndings(code.substr(0, tln)).size() : tln);
    //this->FoundAtLine = src.find(this->OriginalCode);
    this->HeaderLine = this->FoundAtLine;
    this->SourceImplLine = this->FoundAtLine;
    this->Include = std::string("#include <") +
                    omni::string::replace(omni::string::replace(this->HeaderFile, srcdir, ""), "\\", "/")
                    + std::string(">");
    List<ptr_t>::iterator m;
    if (!OmniDocuGen::Util::IsNsOrClass(this->CodeType)) {
        this->Signature = this->GetSignature(true, true) + "\r\n";
    } else {
        this->Signature = this->Name + "\r\n";
        if (this->FullPath != "omni") { // for the main omni namespace, don't print32_t the entire class tree
            std::string tmp;
            for (m = this->Members.begin(); m != this->Members.end(); ++m) {
                if (OmniDocuGen::Program::StopReq) { return; }
                if (OmniDocuGen::Util::IsPrivate((*m)->ScopeAccessType)) { continue; }
                tmp = (*m)->GetSignature(true, true);
                if (tmp.empty()) { tmp = "\r\n"; }
                this->Signature += tmp + "\r\n";
            }
        }
    }
    this->Signature = omni::string::trim_end(this->Signature);
    
    for (m = this->Overloads.begin(); m != this->Overloads.end(); ++m) {
        if (OmniDocuGen::Program::StopReq) { return; }
        (*m)->SetOwnerInfoAndLinkIndex(src, hdr, code);
    }
    for (m = this->Members.begin(); m != this->Members.end(); ++m) {
        if (OmniDocuGen::Program::StopReq) { return; }
        (*m)->SetOwnerInfoAndLinkIndex(src, hdr, code);
    }
    this->Comment->ResetParent(this->FullPath, this->IsAnOverload(), this->OverloadIndex);
    if (this->Comment->HasIgnoreFlag) {
        this->ScopeAccessType = OmniDocuGen::Types::CodeScopeAcessType::Private;
    }
}

void OmniDocuGen::MemberTypeInformation::LinkSources(OmniDocuGen::MemberTypeInformation::ptr_t allmti)
{
    ptr_t fnd;
    if (allmti) { fnd = allmti->Find(this->This); }
    if (fnd) {
        bool thdr = this->HeaderFile.empty();
        bool mhdr = fnd->HeaderFile.empty();
        if (thdr && !mhdr) {
            this->HeaderFile = fnd->HeaderFile;
            this->HeaderLine = fnd->HeaderLine;
        } else if (!thdr && mhdr) {
            fnd->HeaderFile = this->HeaderFile;
            fnd->HeaderLine = this->HeaderLine;
        }
        bool timp = this->ImplFile.empty();
        bool mimp = fnd->ImplFile.empty();
        if (timp && !mimp) {
            this->ImplFile = fnd->ImplFile;
            this->SourceImplLine = fnd->SourceImplLine;
        } else if (!timp && mimp) {
            fnd->ImplFile = this->ImplFile;
            fnd->SourceImplLine = this->SourceImplLine;
        }
        if ((!timp && !mimp) && (fnd->ImplFile != this->ImplFile) && OmniDocuGen::Util::IsHeaderExt(fnd->ImplFile)) {
            fnd->ImplFile = this->ImplFile;
            fnd->SourceImplLine = this->SourceImplLine;
        }
        bool tdoc = this->Comment->OriginalCode.empty();
        bool mdoc = fnd->OriginalCode.empty();
        if (tdoc && !mdoc) {
            this->Comment = new CommentInformation(fnd->Comment->OriginalCode, this->FullPath, this->IsAnOverload(), this->OverloadIndex);
            if (this->Comment->HasIgnoreFlag) {
                this->ScopeAccessType = OmniDocuGen::Types::CodeScopeAcessType::Private;
            }
        } else if (!tdoc && mdoc) {
            fnd->Comment = new CommentInformation(this->Comment->OriginalCode, fnd->FullPath, fnd->IsAnOverload(), fnd->OverloadIndex);
            if (fnd->Comment->HasIgnoreFlag) {
                fnd->ScopeAccessType = OmniDocuGen::Types::CodeScopeAcessType::Private;
            }
        }
    }
    foreach (ptr_t, mti, this->Members) {
        if (OmniDocuGen::Program::StopReq) { return; }
        (*mti)->LinkSources(allmti);
    }
}

OmniDocuGen::MemberTypeInformation::ptr_t OmniDocuGen::MemberTypeInformation::GetOmni(bool includeComment)
{
    std::string comment = "";
    ptr_t empty;
    ptr_t omni(new MemberTypeInformation("omni", 0, OmniDocuGen::Types::CodeStructureType::Namespace, empty));
    omni->HeaderFile = omni::io::path::combine(omni::io::path::combine(OmniDocuGen::Program::Settings.SourceDirectory, "omni"), "library.hpp");
    omni->ImplFile = omni->HeaderFile;
    omni->HeaderLine = 1;
    omni->FoundAtLine = 1;
    if (includeComment) {
        comment = Program::Settings.CommentOmni;
    }
    omni->Comment = new CommentInformation(comment, omni->FullPath, omni->IsAnOverload(), omni->OverloadIndex);
    return omni;
}

OmniDocuGen::MemberTypeInformation::ptr_t OmniDocuGen::MemberTypeInformation::FromXML(std::string xml, const std::string& srcFile)
{
    xml = xml.substr(std::string("<MemberTypeInformation>").size());
    xml = xml.substr(0, xml.size() - std::string("</MemberTypeInformation>").size());
    if (xml.empty()) { return ptr_t(); }
    ptr_t ret(new MemberTypeInformation(true, srcFile));

    ret->Name = OmniDocuGen::Util::GetTagData(xml, "Name");
    xml = OmniDocuGen::Util::RemoveTag(xml, "Name");
    ret->FullPath = OmniDocuGen::Util::GetTagData(xml, "FullPath");
    xml = OmniDocuGen::Util::RemoveTag(xml, "FullPath");
    ret->Signature = OmniDocuGen::Util::GetTagData(xml, "Signature");
    xml = OmniDocuGen::Util::RemoveTag(xml, "Signature");
    ret->InheritedFrom = OmniDocuGen::Util::GetTagData(xml, "InheritedFrom");
    xml = OmniDocuGen::Util::RemoveTag(xml, "InheritedFrom");
    ret->NamespaceAlias = OmniDocuGen::Util::GetTagData(xml, "NamespaceAlias");
    xml = OmniDocuGen::Util::RemoveTag(xml, "NamespaceAlias");
    ret->ReturnType = OmniDocuGen::Util::GetTagData(xml, "ReturnType");
    xml = OmniDocuGen::Util::RemoveTag(xml, "ReturnType");
    ret->Template = OmniDocuGen::Util::GetTagData(xml, "Template");
    xml = OmniDocuGen::Util::RemoveTag(xml, "Template");
    ret->TemplateSpecialization = OmniDocuGen::Util::GetTagData(xml, "TemplateSpecialization");
    xml = OmniDocuGen::Util::RemoveTag(xml, "TemplateSpecialization");
    ret->ImplFile = OmniDocuGen::Util::GetTagData(xml, "ImplFile");
    xml = OmniDocuGen::Util::RemoveTag(xml, "ImplFile");
    ret->HeaderFile = OmniDocuGen::Util::GetTagData(xml, "HeaderFile");
    xml = OmniDocuGen::Util::RemoveTag(xml, "HeaderFile");
    ret->Include = OmniDocuGen::Util::GetTagData(xml, "Include");
    xml = OmniDocuGen::Util::RemoveTag(xml, "Include");
    ret->Level = omni::string::util::to_type<int32_t>(OmniDocuGen::Util::GetTagData(xml, "Level"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "Level");
    ret->Index = omni::string::util::to_type<int32_t>(OmniDocuGen::Util::GetTagData(xml, "Index"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "Index");
    ret->OverloadIndex = omni::string::util::to_type<int32_t>(OmniDocuGen::Util::GetTagData(xml, "OverloadIndex"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "OverloadIndex");
    ret->FoundAtLine = omni::string::util::to_type<int32_t>(OmniDocuGen::Util::GetTagData(xml, "FoundAtLine"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "FoundAtLine");
    ret->SourceImplLine = omni::string::util::to_type<int32_t>(OmniDocuGen::Util::GetTagData(xml, "SourceImplLine"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "SourceImplLine");
    ret->HeaderLine = omni::string::util::to_type<int32_t>(OmniDocuGen::Util::GetTagData(xml, "HeaderLine"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "HeaderLine");
    ret->CodeType = OmniDocuGen::Types::CodeStructureType::parse(OmniDocuGen::Util::GetTagData(xml, "CodeType"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "CodeType");
    ret->ScopeAccessType = OmniDocuGen::Types::CodeScopeAcessType::parse(OmniDocuGen::Util::GetTagData(xml, "ScopeAcessType"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "ScopeAcessType");
    ret->IsStatic = omni::string::util::to_type<bool>(OmniDocuGen::Util::GetTagData(xml, "IsStatic"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "IsStatic");
    ret->IsInline = omni::string::util::to_type<bool>(OmniDocuGen::Util::GetTagData(xml, "IsInline"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "IsInline");
    ret->IsExplicit = omni::string::util::to_type<bool>(OmniDocuGen::Util::GetTagData(xml, "IsExplicit"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "IsExplicit");
    ret->OriginalCode = OmniDocuGen::Util::GetTagData(xml, "OriginalCode");
    xml = OmniDocuGen::Util::RemoveTag(xml, "OriginalCode");
    ret->Comment = CommentInformation::FromXML(OmniDocuGen::Util::GetTagData(xml, "Comment"));
    xml = OmniDocuGen::Util::RemoveTag(xml, "Comment");

    std::string prs = OmniDocuGen::Util::GetTagData(xml, "Parameters");
    while (!prs.empty()) {
        std::string tag = OmniDocuGen::Util::GetTag(prs, "ParameterInformation");
        ret->Parameters.push_back(ParameterInformation::FromXML(tag));
        prs = prs.substr(tag.length() + 2);
    }
    xml = OmniDocuGen::Util::RemoveTag(xml, "Parameters");

    prs = OmniDocuGen::Util::GetTagData(xml, "Overloads");
    while (!prs.empty()) {
        std::string tag = OmniDocuGen::Util::GetTag(prs, "MemberTypeInformation");
        ret->Overloads.push_back(MemberTypeInformation::FromXML(tag, srcFile));
        prs = prs.substr(tag.length() + 2);
    }
    xml = OmniDocuGen::Util::RemoveTag(xml, "Overloads");

    prs = OmniDocuGen::Util::GetTagData(xml, "Members");
    while (!prs.empty()) {
        std::string tag = OmniDocuGen::Util::GetTag(prs, "MemberTypeInformation");
        ret->Members.push_back(MemberTypeInformation::FromXML(tag, srcFile));
        prs = prs.substr(tag.length() + 2);
    }
    return ret;
}

bool OmniDocuGen::MemberTypeInformation::CompareMemberTypeInformationDeref(const OmniDocuGen::MemberTypeInformation& x, const OmniDocuGen::MemberTypeInformation& y)
{
    if (x.CodeType < y.CodeType) {
        return true;
    } else if (x.CodeType > y.CodeType) {
        return false;
    }
    const char* dg = "delegate"; // 8
    const char* ev = "event"; // 5
    const char* ac = "action"; // 6
    const char* cb = "callback"; // 8
    if (((x.CodeType == OmniDocuGen::Types::CodeStructureType::Class) || (x.CodeType == OmniDocuGen::Types::CodeStructureType::Typedef)) &&
        (
        ((x.Name.find(dg) != std::string::npos) && (y.Name.find(dg) != std::string::npos)) ||
        ((x.Name.find(ev) != std::string::npos) && (y.Name.find(ev) != std::string::npos)) ||
        ((x.Name.find(ac) != std::string::npos) && (y.Name.find(ac) != std::string::npos)) ||
        ((x.Name.find(cb) != std::string::npos) && (y.Name.find(cb) != std::string::npos))
        ))
    {
        std::string n1, n2;
        if ((x.Name.find(dg) != std::string::npos) || (x.Name.find(cb) != std::string::npos)) {
            // delegate/callback
            n1 = x.Name.substr(8);
            n2 = y.Name.substr(8);
        } else if (x.Name.find(ev) != std::string::npos) {
            // event
            n1 = x.Name.substr(5);
            n2 = y.Name.substr(5);
        } else {
            // action
            n1 = x.Name.substr(6);
            n2 = y.Name.substr(6);
        }
        uint32_t v1 = (omni::string::is_numeric(n1) ? omni::string::util::to_type<uint32_t>(n1) : 0);
        uint32_t v2 = (omni::string::is_numeric(n2) ? omni::string::util::to_type<uint32_t>(n2) : 0);
        return v1 < v2;
    }
    return (x.Name < y.Name);
}

bool OmniDocuGen::MemberTypeInformation::CompareMemberTypeInformation(const OmniDocuGen::MemberTypeInformation::ptr_t& x, const OmniDocuGen::MemberTypeInformation::ptr_t& y)
{
    if (!x && y) { return false; }
    if (x && !y) { return true; }
    if (x == y) { return false; }
    return CompareMemberTypeInformationDeref(*x, *y);
}

// private 

void OmniDocuGen::MemberTypeInformation::_ResetMemberFullPaths()
{
    foreach (ptr_t, mti, this->Members) {
        if (OmniDocuGen::Program::StopReq) { return; }
        (*mti)->FullPath = this->FullPath + "::" + (*mti)->Name;
        (*mti)->_ResetMemberFullPaths();
    }
}

void OmniDocuGen::MemberTypeInformation::_Add(ptr_t ti)
{
    ti->Parent = this;
    ti->Level = this->Level + 1;
    ti->Index = this->Members.size();
    ti->FullPath = (this->FullPath.empty() ? this->Name : this->FullPath) + "::" + ti->Name;
    ti->_ResetMemberFullPaths();
    this->Members.push_back(ti);

    if (Util::IsEnum(ti->CodeType) && !Util::IsPrivate(ti->ScopeAccessType)) {
        foreach (ptr_t, ev, ti->Members) {
            MemberTypeInformation* np = new MemberTypeInformation(*(*ev)); // make copy
            np->FullPath = omni::string::replace(np->FullPath, "::enum_t", "");
            this->Members.push_back(ptr_t(np));
        }
    }
}

/// Parses the code to determine type (class/namespace/etc) and any members associated
/// <param name="code">The code to parse</param>
void OmniDocuGen::MemberTypeInformation::_Parse(const std::string& code, OmniDocuGen::Types::MemberParseType mpt)
{
    if (!code.empty() && (mpt != OmniDocuGen::Types::MemberParseType::AsSource)) {
        up(2, "Parsing {0} bytes {1}", omni::string::to_string(code.size()), mpt);
        switch (mpt) {
            case OmniDocuGen::Types::MemberParseType::AsNamespace: this->_ParseAsNamespace(code); break;
            case OmniDocuGen::Types::MemberParseType::AsClass: this->_ParseAsClass(code); break;
            case OmniDocuGen::Types::MemberParseType::AsTypedef: this->_ParseAsTypedef(code); break;
            case OmniDocuGen::Types::MemberParseType::AsMember: this->_ParseAsMember(code); break;
            case OmniDocuGen::Types::MemberParseType::AsSource: break; //this->_ParseAsSource(code); break;
        }
        up(2, "Parsed {0} bytes {1}: {2}", omni::string::to_string(code.size()), mpt, this->FullPath);
    }
}

/// Parses the code as a class/namespace
/// <param name="code">The code to parse</param>
void OmniDocuGen::MemberTypeInformation::_ParseAsNamespace(const std::string& code)
{
    /*
    All namespace declarations in Omni follow the below syntax layout:
    
    namespace omni {
        namespace inner_ns_name {
            code.
        }
    }
    
    */
    std::string tcode = Util::StripComments(code);
    std::string nss = "namespace ";
    if (omni::string::contains(tcode, nss)) {
        std::string nsomni = "namespace omni {";
        if (omni::string::contains(tcode, nsomni)) {
            this->CodeType = OmniDocuGen::Types::CodeStructureType::Namespace;
            this->Name = "omni";
            this->FullPath = "omni";
            int32_t idx = code.find(nsomni);
            idx = (idx + nsomni.length() - 1);
            int32_t edx = (OmniDocuGen::Util::IndexOfCompliment(code, idx) - idx) - 1;
            tcode = code.substr(idx + 1, edx);
            up(4, "Parsing omni namespace members.");
            this->_ParseMembers(tcode);
        } else {
            size_t nspos = tcode.find(nss) + nss.size() + 1;
            int32_t eidx = tcode.find("\n", nspos);
            std::string xns = tcode.substr(nspos-1, (eidx - nspos));
            std::string cmnt;
            this->Name = omni::string::trim(xns.substr(0, xns.find(" ")));
            this->CodeType = OmniDocuGen::Types::CodeStructureType::Namespace;
            this->FullPath = this->Name;
            if (this->Parent && !this->Parent->FullPath.empty()) {
                this->FullPath = this->Parent->FullPath + "::" + this->Name;
            }
            if (this->Parent && this->Level == 0) { this->Level = this->Parent->Level + 1; }
            this->Parameters.clear();
            nspos = code.find(xns);
            eidx = Util::CommentBefore(code, nspos);
            if (eidx >= 0) {
                cmnt = Util::GetComment(code, eidx); //omni::string::trim(code.substr(eidx, (nspos - eidx)));
            }
            this->Comment = new CommentInformation(cmnt, this->FullPath, this->IsAnOverload(), this->OverloadIndex);
            if (this->Comment->HasIgnoreFlag) {
                this->ScopeAccessType = OmniDocuGen::Types::CodeScopeAcessType::Private;
            }
            if (omni::string::contains(xns, "=")) {
                // namespace err = XYZ;
                this->NamespaceAlias = omni::string::replace(xns.substr(xns.find(this->Name)), ";", "");
                this->CodeType = OmniDocuGen::Types::CodeStructureType::Member;
            } else {
                // namespace consts {
                int32_t ti = code.find("{", code.find(xns));
                tcode = omni::string::trim(code.substr(ti + 1, (OmniDocuGen::Util::IndexOfCompliment(code, ti) - ti) - 1));
                up(4, "Parsing members on {0} bytes", omni::string::to_string(tcode.size()));
                this->_ParseMembers(tcode);
            }
        }
    } else {
        up(2, "No 'namespace omni' found in code for {0}", this->OwnerSourceFile);
    }
}

/// Parses the code as a class/namespace
/// <param name="code">The code to parse</param>
void OmniDocuGen::MemberTypeInformation::_ParseAsClass(const std::string& code)
{
    /*
        All class declarations in Omni follow the below syntax layout:
        
        (template <*>)
        class class_name(<template_specialization>) ( : ((virtual) (public/protected/private)) inherited_class)
        {
            code.
        };
    */
    // remove comments so any thing found doesn't need to be checked if it's actually a declaration or if it's within a comment
    std::string tcode = OmniDocuGen::Util::StripComments(code);
    if (omni::string::contains(tcode, "class ") && omni::string::contains(tcode, "{") && omni::string::contains(tcode, "};")) {
        try {
            this->CodeType = OmniDocuGen::Types::CodeStructureType::Class;
            std::string line = Util::GetLineOfStringData(tcode, "class ");
            size_t beg, end;
            size_t cbeg = tcode.find("class ");
            if (omni::string::contains(line, "template ") && omni::string::contains(line, "<") && omni::string::contains(line, ">")) {
                // all templates follow (template<*>)
                cbeg = line.find("class");
                beg = line.find("<");
                end = line.find(">");
                if ((cbeg > beg) && (cbeg < end)) {
                    beg = tcode.find(line) + line.size();
                    cbeg = tcode.find("class ", beg);
                }
            }
            // name
            line = tcode.substr(cbeg);
            line = omni::string::trim(line.substr(0, line.find("\n")));

            beg = tcode.find("{", cbeg);
            end = OmniDocuGen::Util::IndexOfCompliment(tcode, beg) + 2;
            std::string sub = tcode.substr(cbeg, beg-cbeg+1);
            int32_t idx = code.find(sub);
            if (idx >= 0) {
                beg = OmniDocuGen::Util::IndexOfChar(code, idx, '{');
                int32_t tidx = OmniDocuGen::Util::TemplateBefore(code, idx);
                if (tidx >= 0) {
                    idx = tidx;
                    this->Template = omni::string::trim(code.substr(tidx, (code.find("\n", tidx) - tidx)));
                }
                int32_t cidx = OmniDocuGen::Util::CommentBefore(code, idx);
                if (cidx >= 0) {
                    idx = cidx;
                    this->Comment = new CommentInformation(omni::string::trim(code.substr(cidx, idx - cidx)), this->FullPath, this->IsAnOverload(), this->OverloadIndex);
                    if (this->Comment->HasIgnoreFlag) {
                        this->ScopeAccessType = OmniDocuGen::Types::CodeScopeAcessType::Private;
                    }
                }
                idx = OmniDocuGen::Util::IndexOfChar(code, idx, '{');
                cidx = OmniDocuGen::Util::IndexOfCompliment(code, idx);
                tcode = omni::string::trim(code.substr(idx + 1, cidx - idx - 1));
            } else {
                tcode = omni::string::trim(tcode.substr(beg + 1, (OmniDocuGen::Util::IndexOfCompliment(tcode, beg) - beg) - 1));
            }
            this->Name = omni::string::trim(omni::string::replace(line, "class ", ""));
            if (omni::string::contains(line, " :")) {
                this->Name = omni::string::trim(this->Name.substr(0, this->Name.find(" ")));
                this->InheritedFrom = line.substr(line.rfind(" "));
            } else if (this->IsTemplated()) {
                std::string t = omni::string::replace(this->Template, " ", "");
                if (t == "template<>" && omni::string::contains(line, "<") && omni::string::contains(line, ">")) {
                    int32_t lt = line.find('<');
                    int32_t gt = OmniDocuGen::Util::IndexOfChar(line, lt, '>');
                    this->TemplateSpecialization = line.substr(lt, gt - lt + 1);
                }
            }
            this->FullPath = this->Name;
            if (this->Parent && !this->Parent->FullPath.empty()) {
                this->FullPath = this->Parent->FullPath + "::" + this->Name;
            }
            if (this->Parent && this->Level == 0) { this->Level = this->Parent->Level + 1; }
            this->Parameters.clear();
            up(4, "Parsed class: {0}", this->FullPath);
            this->_ParseMembers(tcode);
        } catch (const std::exception& ex) {
            OmniDocuGen::Program::AddError(ex, "MTI error parsing as class");
        }
    } else {
        this->_ParseMembers(code);
    }
}

/// Parses the code as a struct
/// <param name="code">The code to parse</param>
void OmniDocuGen::MemberTypeInformation::_ParseAsTypedef(const std::string& code)
{
    /*
        typedef's in Omni currently reside in the following formats:
        
        typedef ret_t (function pointer type); -- typedef ret_t (* ..); these are ONLY from the delegates
        typedef (original type) new_type_name;
        typedef struct/enum/union struct_name {
        } struct_name;
    */
    up(4, "Parsing as typedef");
    std::string tcode = code;
    std::string tdef_struct = "typedef struct ";
    std::string tdef_union = "typedef union ";
    std::string tdef_enum = "typedef enum ";
    std::string sval = "";
    if (omni::string::contains(tcode, tdef_struct)) {
        this->CodeType = OmniDocuGen::Types::CodeStructureType::Struct;
        sval = tdef_struct;
    } else {
        if (omni::string::contains(tcode, tdef_union)) {
            this->CodeType = OmniDocuGen::Types::CodeStructureType::Struct;
            sval = tdef_union;
        } else if (omni::string::contains(tcode, tdef_enum)) {
            this->CodeType = OmniDocuGen::Types::CodeStructureType::Enum;
            sval = tdef_enum;
        } else {
            this->CodeType = OmniDocuGen::Types::CodeStructureType::Typedef;
        }
    }
    int32_t sidx = tcode.find(sval);
    int32_t tlen = sidx + sval.length();
    int32_t bidx = OmniDocuGen::Util::IndexOfChar(tcode, sidx, '{');
    int32_t cidx = OmniDocuGen::Util::CommentBefore(tcode, sidx);
    int32_t eidx = OmniDocuGen::Util::IndexOfCompliment(tcode, bidx);

    this->Name = omni::string::trim(tcode.substr(tlen, bidx - tlen));
    if (cidx >= 0) {
        this->Comment = new CommentInformation(tcode.substr(cidx, sidx - 1), this->FullPath, this->IsAnOverload(), this->OverloadIndex);
        if (this->Comment->HasIgnoreFlag) {
            this->ScopeAccessType = OmniDocuGen::Types::CodeScopeAcessType::Private;
        }
    }
    std::string ocode = omni::string::trim(tcode.substr(bidx + 1, eidx - bidx - 1));
    this->FullPath = this->Name;
    if (this->Parent && !this->Parent->FullPath.empty()) {
        this->FullPath = this->Parent->FullPath + "::" + this->Name;
    }
    if (this->Parent && this->Level == 0) { this->Level = this->Parent->Level + 1; }
    this->Parameters.clear();
    this->_ParseMembers(ocode);
    eidx += this->Name.length() + 3;
    if (eidx > tcode.length()) { eidx = tcode.length(); }
    if (cidx >= 0) {
        ocode = tcode.substr(cidx, eidx - cidx);
    } else {
        ocode = tcode.substr(sidx, eidx - sidx);
    }
    tcode = omni::string::replace(tcode, ocode, "");
    this->_ParseMembers(tcode);
    up(3, "Parsed {0} as typedef with {1} members", this->FullPath, omni::string::to_string(this->Members.size()));
}

/// Parses the code as a typedef/function/member
/// <param name="code">The code to parse</param>
void OmniDocuGen::MemberTypeInformation::_ParseAsMember(const std::string& code)
{
    int32_t idx = -1;
    std::string tcode;
    up(4, "Parsing {0} bytes of member data", omni::string::to_string(code.size()));
    this->CodeType = OmniDocuGen::Types::CodeStructureType::Member;
    if (omni::string::contains(code, "/**") && omni::string::contains(code, "*/")) {
        this->Comment = new CommentInformation(OmniDocuGen::Util::GetComment(code), this->FullPath, this->IsAnOverload(), this->OverloadIndex);
        tcode = omni::string::trim_front(omni::string::replace(code, this->Comment->OriginalCode, ""));
    } else {
        tcode = code;
    }
    // remove comments so anything found doesn't need to be checked if it's actually a declaration or if it's within a comment
    tcode = OmniDocuGen::Util::StripComments(tcode);
    if (omni::string::contains(tcode, "typedef ")) {
        /*
            typedef's in Omni currently reside in the following formats:
        
            typedef (function pointer type); -- typedef ret_t (* .. these are ONLY from the delegates
            typedef (original type) new_type_name;
            typedef struct/enum/union struct_name {
            } struct_name;

            old regex:
            ((typedef)\\s* ([0-9A-Za-z_:<>\\s,\\(\\)\\&\\~\\\"\\*]*) \\s ([0-9A-Za-z_:<>\\s,\\(\\)\\&\\~\\\"\\*]*) \\s*;)
            ((typedef\\ *([0-9A-Za-z_<>\\s,\\&\\~\\*]*))\\ *(\\(\\*[0-9A-Za-z_<>\\s,\\&\\~\\*]*\\))(\\([0-9A-Za-z_<>\\s,\\&\\~\\*]*\\));)
            else.. it's "typedef [X] [Y({)] .. where X is the original type or one of {struct/enum/union}
            and Y is the type name .. if Y is a {struct/etc} then it will have a "{" at the end
        */
        if (omni::string::contains(tcode, "typedef ret_t ")) {
            this->CodeType = OmniDocuGen::Types::CodeStructureType::Typedef;
            this->ReturnType = "ret_t";
            this->Name = (omni::string::contains(tcode, "typedef ret_t (*functor)") ? "(*functor)" : "(*function_ptr)");
        } else {
            std::string line = tcode.substr(tcode.find("typedef "));
            line = omni::string::trim(line.substr(0, line.find("\n")));
            if (omni::string::contains(line, ";")) {
                this->CodeType = OmniDocuGen::Types::CodeStructureType::Typedef;
                this->Name = omni::string::trim(line.substr(line.rfind(" ")));
                line = line.substr(line.find(" "));
                line = line.substr(0, line.rfind(" "));
                this->ReturnType = omni::string::trim(line);
                up(4, "Parsed code as typedef");
            } else {
                this->_ParseAsTypedef(tcode);
            }
        }
    } else if (
        (
            omni::string::contains(tcode, "(") && omni::string::contains(tcode, ")")
            && !omni::string::contains(tcode, "OMNI_CONSTEXT_FW const")
        )
        && 
        (
            !omni::string::contains(tcode, "=") ||
            (
                omni::string::contains(tcode, "operator") ||
                (
                    omni::string::contains(tcode, "virtual") &&
                    (omni::string::contains(tcode, "= 0") || omni::string::contains(tcode, "=0"))
                )
            )
        )
    )
    {
        up(4, "Function Parse start");
        std::string line, tname, tparms, expl;
        size_t ppos, apos;
        this->CodeType = OmniDocuGen::Types::CodeStructureType::Function;
        if (omni::string::contains(tcode, "template <") || omni::string::contains(tcode, "template<")) {
            int32_t tidx = tcode.find("template");
            int32_t eidx = OmniDocuGen::Util::IndexOfChar(tcode, tidx, '<');
            eidx = OmniDocuGen::Util::IndexOfCompliment(tcode, eidx, '<', '>');
            if (eidx >= 0) {
                this->Template = tcode.substr(tidx, eidx - tidx + 1);
                tcode = omni::string::trim(omni::string::replace(tcode, this->Template, ""));
            }
        }

        if (omni::string::contains(tcode, " :") || omni::string::contains(tcode, " : ") || omni::string::contains(tcode, " :\r\n")) {
            /* ptrn
                (
                    ([^\\:].*)
                    \\s\\:
                    (.*)
                )
            */
            line = Util::GetLineOfStringData(tcode, " :");
            if (!omni::string::contains(line, "(") || !omni::string::contains(line, ")")) {
                ppos = tcode.rfind("\n", tcode.find("("));
                if (ppos == std::string::npos) { ppos = 0; }
                line = tcode.substr(ppos, (tcode.find(" :") + 2) - ppos);
            }
            while (omni::string::contains(line, " (")) {
                line = omni::string::replace(line, " (", "(");
            }
            apos = line.find("(");
            ppos = line.rfind(" ", apos)+1;
        } else if (omni::string::contains(tcode, "operator")) {
            this->CodeType = OmniDocuGen::Types::CodeStructureType::Operator;
            /* OP_FUNCTION:
                (
                    ([0-9A-Za-z_:<>\\s,\\(\\)\\&\\~\\\"\\*]*)
                    (operator(.*))
                    \\(
                        (
                            ([0-9A-Za-z_=:<>\\s,\\(\\)\\&\\~\\\"\\*]*)
                        )
                    \\);?
                )
            */
            line = Util::GetLineOfStringData(tcode, "operator");
            apos = line.find("(");
            ppos = line.find("operator");
        } else if (omni::string::contains(tcode, "explicit ") || omni::string::contains(tcode, "OMNI_EXPLICIT ")) {
            /* EXPLICIT_CTOR:
                (
                    (\\b?explicit|OMNI_EXPLICIT\\b
                        ([^\\(].*)
                        \\(
                            (.*)
                        \\)
                        ;?
                    )
                )
            */
            if (omni::string::contains(tcode, "explicit ")) {
                expl = "explicit ";
            } else {
                expl = "OMNI_EXPLICIT ";
            }
            line = Util::GetLineOfStringData(tcode, expl);
            if (!omni::string::contains(line, "(") || !omni::string::contains(line, ")")) {
                ppos = tcode.rfind("\n", tcode.find(expl));
                if (ppos == std::string::npos) { ppos = 0; }
                line = tcode.substr(ppos, (tcode.find(")") + 1) - ppos);
            }
            apos = line.find("(");
            ppos = line.find(expl);
        } else {
            /* FUNCTION:
                ((return_type)\\s(function_name)\\((function_params)\\);?
                (
                    ([0-9A-Za-z_:<>\\s,\\&\\~\\\"\\*]*)
                    \\s
                    ([0-9A-Za-z_:<>\\s,\\&\\~\\\"\\*]*)
                    \\(
                        (
                            (.*)
                        )
                    \\);?
                )
            */
            line = Util::GetLineOfStringData(tcode, "(");
            if (!omni::string::contains(line, ")")) {
                ppos = tcode.rfind("\n", tcode.find("("));
                if (ppos == std::string::npos) { ppos = 0; }
                line = tcode.substr(ppos, (tcode.find(")") + 1) - ppos);
            }
            while (omni::string::contains(line, " (")) {
                line = omni::string::replace(line, " (", "(");
            }
            apos = line.find("(");
            ppos = line.rfind(" ", apos)+1;
        }
        
        if (!line.empty()) {
            up(4, "Parsing line");
            tname = line.substr(ppos, apos-ppos);
            if (line.substr(apos+1) == ")") {
                tparms = "";
            } else {
                tparms = line.substr(apos+1);
                tparms = tparms.substr(0, tparms.find(")"));
            }

            this->ReturnType = omni::string::trim(line.substr(0, ppos));
            if (omni::string::contains(this->ReturnType, "static ")) {
                this->IsStatic = true;
                this->ReturnType = omni::string::replace(this->ReturnType, "static ", "");
            }
            if (omni::string::contains(this->ReturnType, "inline ")) {
                this->IsInline = true;
                this->ReturnType = omni::string::replace(this->ReturnType, "inline ", "");
            }
            if (!expl.empty() && omni::string::contains(this->ReturnType, expl)) {
                this->IsExplicit = true;
                this->ReturnType = omni::string::replace(this->ReturnType, expl, "");
            }

            if (this->Parent &&
                (this->Parent->CodeType == OmniDocuGen::Types::CodeStructureType::Class ||
                this->Parent->CodeType == OmniDocuGen::Types::CodeStructureType::Struct) &&
                this->ReturnType.length() > this->Parent->Name.length() &&
                (this->ReturnType.substr(0, this->Parent->Name.length() + 1) == this->Parent->Name + "("))
            {
                // ctor
                this->Name = this->ReturnType.substr(0, this->ReturnType.find(")") + 1);
                this->ReturnType = "";
                idx = this->Name.find("(");
                tcode = this->Name.substr(idx + 1, (this->Name.find(")") - 1) - idx);
            } else {
                this->Name = tname;
                tcode = tparms;
                if (this->CodeType != OmniDocuGen::Types::CodeStructureType::Operator) {
                    std::string tmp;
                    if (omni::string::contains(this->Name, "*")) {
                        tmp = this->Name;
                        this->Name = tmp.substr(tmp.find("*") + 1);
                        this->ReturnType += omni::string::trim(omni::string::replace(tmp, this->Name, ""));
                    } else if (omni::string::contains(this->Name, "&")) {
                        tmp = this->Name;
                        this->Name = tmp.substr(tmp.find("&") + 1);
                        this->ReturnType += omni::string::trim(omni::string::replace(tmp, this->Name, ""));
                    } else if (this->Name.substr(0, 1) == "~") {
                        this->ReturnType = "";
                    }
                }
            }

            if (omni::string::trim(tcode) != "") {
                //List<std::string> splits = omni::string_util::split(tcode, ',');
                std::string p;
                List<std::string> splits = Util::Split(tcode, ",");
                for (int32_t si = 0; si < splits.size(); ++si) {
                    if (OmniDocuGen::Program::StopReq) { return; }
                    p = splits[si];
                    if (omni::string::contains(p, "<") && !omni::string::contains(p, ">")) {
                        while (!omni::string::contains(p, ">")) {
                            if (OmniDocuGen::Program::StopReq) { return; }
                            p += "," + splits[++si];
                        }
                    }
                    if (OmniDocuGen::Program::StopReq) { return; }
                    ParameterInformation::ptr_t param(new ParameterInformation(omni::string::trim(p)));
                    this->Parameters.push_back(param);
                }
            }
        } else {
            up("PROGRAMMER ERROR: should not reach this code!!!!");
            omni::application::exit();
            /*
                std::string tmp = omni::string::trim(tcode);
                idx = tcode.find("(");
                this->Name = tmp.substr(0, idx);
                this->ReturnType = "";
                tcode = tmp.substr(idx);
                tcode = tcode.substr(1, (tcode.find(")") - 1));
                if (omni::string::trim(tcode) != "") {
                    std::string p;
                    List<std::string> splits = Util::Split(tcode, ",");
                    for (int32_t si = 0; si < splits.size(); ++si) {
                        p = splits[si];
                        if (OmniDocuGen::Program::StopReq) { return; }
                        if (omni::string::contains(p, "<") && !omni::string::contains(p, ">")) {
                            while (!omni::string::contains(p, ">")) {
                                p += splits[++si];
                            }
                        }
                        if (OmniDocuGen::Program::StopReq) { return; }
                        ParameterInformation::ptr_t param(new ParameterInformation(omni::string::trim(p)));
                        this->Parameters.push_back(param);
                    }
                }
            */
        }

        // dtor/ctor
        if (this->Parent && (this->Parent->CodeType == OmniDocuGen::Types::CodeStructureType::Class || this->Parent->CodeType == OmniDocuGen::Types::CodeStructureType::Struct)) {
            if (omni::string::contains(this->Name, this->Parent->Name)) {
                if (omni::string::contains(this->Name, "~")) {
                    this->Name = "~" + this->Parent->Name;
                    this->CodeType = OmniDocuGen::Types::CodeStructureType::Dtor;
                } else {
                    this->Name = this->Parent->Name;
                    this->CodeType = OmniDocuGen::Types::CodeStructureType::Ctor;
                }
            }
        }
    } else {
        std::string line, tname, trtype;
        size_t ppos, apos;
        this->CodeType = OmniDocuGen::Types::CodeStructureType::Member;
        /* MEMBER:
            ((return_type)\\s(member_name);)
            (
                ([0-9A-Za-z_:<>\\s,\\(\\)\\&\\~\\\"\\*]*)
                \\s
                ([0-9A-Za-z_:<>\\s,\\(\\)\\&\\~\\\"\\*]*);
            )
        */
        if (omni::string::contains(tcode, "=")) {
            // const int32_t DAYS_TO_MONTH_365[] = {
            // UNSPECIFIED = AF_UNSPEC,
            std::string tmpc = omni::string::trim_end(tcode.substr(0, tcode.find("="))) + ";";
            if (omni::string::contains(tmpc, "[];")) {
                // const int32_t DAYS_TO_MONTH_365[];
                tmpc = omni::string::replace(tmpc, "[];", ";");
            }
            line = tmpc;
            ppos = line.rfind(" ");
            if (ppos != std::string::npos) {
                tname = omni::string::trim(line.substr(ppos));
                apos = line.rfind(" ", ppos-1);
                trtype = omni::string::trim(line.substr(apos, (ppos-apos)));
            } else {
                tname = line;
                trtype = "";
            }
        } else {
            std::string occ = "OMNI_CONSTEXT_FW const ";
            if (omni::string::contains(tcode, occ)) {
                line = omni::string::trim(Util::GetLineOfStringData(tcode, occ));
                // OMNI_CONSTEXT_FW const wchar_t STRING_NOT_NUMERIC[] LOMNI_STRING_NOT_NUMERIC_STR;
                // OMNI_CONSTEXT_FW const uint32_t KB OMNI_EXT_ASSN_FW(OMNI_KIB_IVAL);
                line = line.substr(occ.size());
                ppos = line.find(" ");
                trtype = line.substr(0, ppos);
                line = line.substr(ppos+1);
                ppos = line.find(" ");
                tname = line.substr(0, ppos);
                if (omni::string::contains(tname, "[")) {
                    tname = tname.substr(0, tname.find("["));
                }
                ppos = line.find("OMNI_EXT_ASSN_FW");
                if (ppos != std::string::npos) {
                    line = line.substr(ppos);
                    line = line.substr(line.find("(") + 1);
                    line = line.substr(0, line.find(")"));
                }
            } else if (omni::string::contains(tcode, "extern const ")) {
                line = omni::string::trim(Util::GetLineOfStringData(tcode, "extern const "));
                // "extern const " = 13
                ppos = std::string("extern const ").size() + 1;
                apos = line.find(" ", ppos);
                trtype = line.substr(ppos, apos - ppos);
                tname = omni::string::trim(line.substr(apos));
                if (omni::string::contains(tname, "[")) {
                    tname = tname.substr(0, tname.find("["));
                }
            } else if (omni::string::contains(tcode, ";")) {
                line = omni::string::trim(Util::GetLineOfStringData(tcode, ";"));
                ppos = line.rfind(" ");
                tname = omni::string::trim(line.substr(ppos));
                apos = line.rfind(" ", ppos-1);
                if (apos == std::string::npos) {
                    apos = 0;
                }
                trtype = omni::string::trim(line.substr(apos, (ppos-apos)));
            }
        }
        if (!line.empty()) {
            if (tname[tname.size()-1] == ';') {
                tname = tname.substr(0, tname.size()-1);
            }
            this->Name = tname;
            this->ReturnType = omni::string::trim(trtype);
            ppos = Util::CommentBefore(code, code.rfind(tname));
            if (ppos >= 0) {
                this->Comment = new CommentInformation(Util::GetComment(code, ppos), this->FullPath, this->IsAnOverload(), this->OverloadIndex);
            }
        } else {
            up(4, "Parsing unknown as member");
            if (omni::string::contains(omni::string::trim(tcode), " ")) {
                idx = tcode.rfind(" ");
                if (omni::string::contains(tcode, "=")) {
                    idx = tcode.find("=");
                    std::string t = tcode.substr(0, idx - 1);
                    if (this->Parent && this->Parent->CodeType == OmniDocuGen::Types::CodeStructureType::Enum) {
                        this->Name = t;
                        this->ReturnType = "int";
                    } else {
                        idx = t.rfind(" ");
                        this->Name = tcode.substr(idx + 1, code.find(";") - idx);
                        this->ReturnType = omni::string::trim(omni::string::replace(code, this->Name, ""));
                        idx = this->Name.find("=");
                        this->Name = omni::string::trim_end(this->Name.substr(0, idx));
                    }
                } else {
                    int32_t semiidx = code.find(";");
                    if (semiidx < 0) {
                        OmniDocuGen::Program::AddError(Util::Format("Invalid index detected, original code:{0}{1}", OMNI_EOL_N, code));
                        return;
                    }
                    this->Name = code.substr(idx + 1, code.find(";") - idx);
                    this->ReturnType = omni::string::trim(omni::string::replace(code, this->Name, ""));
                    if (omni::string::contains(this->Name, "[") && omni::string::contains(this->Name, "]")) {
                        this->Name = this->Name.substr(0, this->Name.find("[")) + ";";
                    }
                }
            }
        }
    }
    if (this->Parent->CodeType == OmniDocuGen::Types::CodeStructureType::Enum && omni::string::trim(this->Name).empty()) {
        if (omni::string::contains(tcode, ",")) {
            this->Name = tcode.substr(0, tcode.find(','));
        } else {
            this->Name = omni::string::trim(tcode);
        }
    }
    if (omni::string::contains(this->Name, ";")) {
        this->Name = omni::string::trim(omni::string::replace(this->Name, ";", ""));
    }
    this->FullPath = this->Name;
    if (this->Parent && !this->Parent->FullPath.empty()) {
        this->FullPath = this->Parent->FullPath + "::" + this->Name;
    }
    if (this->Comment->HasIgnoreFlag) {
        this->ScopeAccessType = OmniDocuGen::Types::CodeScopeAcessType::Private;
    }
    up(4, "Parsed member data: fullpath = '{0}', code type = '{1}', return = '{2}', param count = {3}", this->FullPath, this->CodeType, this->ReturnType, omni::string::to_string(this->Parameters.size()));
}

/// Parses this instance as source code, getting function info and doc comments
/// <param name="code">The code to parse</param>
// void _ParseAsSource(const std::string& code) // SEE MemberTypeInformation.cs

/// Parse the doc comment
/// <param name="cmnt"></param>
std::string OmniDocuGen::MemberTypeInformation::_ParseDocComment(const std::string& cmnt)
{
    std::string r = "";
    List<std::string> ta = OmniDocuGen::Util::SplitAtEndings(cmnt);
    foreach (std::string, t, ta) {
        if (OmniDocuGen::Program::StopReq) { return ""; }
        r += omni::string::trim(*t) + "\r\n";
    }
    return omni::string::trim_end(r);
}

/// Parses the function information for this type
/// <param name="code">The code to parse</param>
void OmniDocuGen::MemberTypeInformation::_ParseFunctionInfo(const std::string& code)
{
    std::string tcode = code;
    List<std::string> lines = OmniDocuGen::Util::SplitAtEndings(tcode);
    std::string s, t, dc;
    int32_t len = lines.size(), cidx = 0, blvl = 0;
    bool iscmnt = false, isdoccmnt = false;
    OmniDocuGen::Types::CodeScopeAcessType csat = OmniDocuGen::Types::CodeScopeAcessType::Public;
    for (int32_t i = 0; i < len; ++i) {
        if (OmniDocuGen::Program::StopReq) { return; }
        try {
            s = lines[i];
            if (s.empty()) { continue; }
            // ignore any OMNI_XX_FW compile flags, as those are noted in the other docs
            if (omni::string::contains(s, "OMNI_") && omni::string::contains(s, "_FW")) {
                s = omni::string::trim(s);
                if ((omni::string::starts_with(s, "//") || omni::string::starts_with(s, "#")) ||
                    (!omni::string::contains(s, " ") && omni::string::starts_with(s, "OMNI_") && omni::string::ends_with(s, "_FW")))
                { continue; }

                if (omni::string::starts_with(s, "OMNI_MEMBERS_FW") ||
                    omni::string::starts_with(s, "OMNI_OSTREAM_FW") ||
                    omni::string::starts_with(s, "OMNI_OSTREAM_FN_FW"))
                {
                    up("Progamming error, this should not be here!");
                    omni::application::exit();
                }
                s = lines[i];
            }
            cidx += s.length() + 2; // account for \r\n
            if (isdoccmnt) {
                dc += s + "\r\n";
            }
            if ((!iscmnt && !isdoccmnt) && omni::string::contains(s, "/*")) {
                iscmnt = true;
                t = s.substr(s.find("/*"));
                if ((t.length()) > 2 && (t.substr(0, 3) == "/**")) {
                    isdoccmnt = true;
                    iscmnt = false;
                    dc = t + "\r\n";
                }
            }
            if (omni::string::contains(s, "*/")) {
                if (isdoccmnt) {
                    s = omni::string::replace(s, omni::string::trim(dc), "");
                } else if (iscmnt) {
                    s = s.substr(s.find("*/") + 2);
                }
                iscmnt = isdoccmnt = false;
            }
            t = omni::string::trim(s);
            if (t.length() > 1) {
                // it's a comment or #def
                if ((t.substr(0, 2) == "//") || (t.substr(0, 1) == "#")) { continue; }
                // it's a using declaration (e.g. using omni:: or using std:: .. like 'using omni::sync::runnable::operator==');
                if (omni::string::contains(t, "using ")) { continue; }

                /*
                    OLD: note .. not sure if this was old code, but "OMNI_INCLUDE_OBJECT_HDR" isn't
                    anywhere in any code (omni or here) ...
                    if (t.length() > OmniDocuGen::Util::OIOH.length()) {
                        if (t.substr(0, OmniDocuGen::Util::OIOH.length()) == OmniDocuGen::Util::OIOH) { continue; }
                    }
                */
            }
            if (dc.empty() && omni::string::trim(s).empty()) { continue; }
            if (iscmnt || isdoccmnt) { continue; } // nothing to process for comments
            if (this->CodeType == OmniDocuGen::Types::CodeStructureType::Class || this->CodeType == OmniDocuGen::Types::CodeStructureType::Struct) {
                if (t == "public:") {
                    csat = OmniDocuGen::Types::CodeScopeAcessType::Public;
                    continue;
                } else if (t == "protected:") {
                    csat = OmniDocuGen::Types::CodeScopeAcessType::Protected;
                    continue;
                } else if (t == "private:") {
                    csat = OmniDocuGen::Types::CodeScopeAcessType::Private;
                    continue;
                }
            }
            if (omni::string::contains(t, "(")) {
                List<int32_t> oidxs = OmniDocuGen::Util::IndexesOf(t, "(");
                List<int32_t> cidxs = OmniDocuGen::Util::IndexesOf(t, ")");
                blvl += oidxs.size();
                blvl -= cidxs.size();
                if (blvl > 0) {
                    for (++i; i < len; ++i) {
                        if (OmniDocuGen::Program::StopReq) { return; }
                        s = lines[i];
                        cidx += s.length() + 2; // account for \r\n
                        oidxs = OmniDocuGen::Util::IndexesOf(s, "(");
                        cidxs = OmniDocuGen::Util::IndexesOf(s, ")");
                        blvl += oidxs.size();
                        blvl -= cidxs.size();
                        t += omni::string::trim(s);
                        if (blvl == 0) { break; }
                    }
                }
            }
            if (omni::string::contains(t, "{")) {
                blvl = (omni::string::contains(t, "}") ? 0 : 1);
                if (t == "{") {
                    for (++i; i < len; ++i) {
                        if (OmniDocuGen::Program::StopReq) { return; }
                        s = lines[i];
                        cidx += s.length() + 2; // account for \r\n
                        if (omni::string::contains(s, "{")) { ++blvl; }
                        if (omni::string::contains(s, "}")) { --blvl; }
                        if (blvl == 0) { break; }
                    }
                    if (blvl == 0) { continue; }
                }
                int32_t tmpx = t.find("{") - 1;
                if (tmpx < 0) { tmpx = 0; }
                t = omni::string::trim_end(t.substr(0, tmpx));
            }
            if (omni::string::ends_with(t, "throw()")) { t = omni::string::trim_end(t.substr(0, t.rfind("throw()"))); }
            if (omni::string::ends_with(t, "OMNI_FUNC_NO_THROW")) { t = omni::string::trim_end(t.substr(0, t.rfind("OMNI_FUNC_NO_THROW"))); }
            if (omni::string::ends_with(t, "OMNI_DTOR_NO_THROW")) { t = omni::string::trim_end(t.substr(0, t.rfind("OMNI_DTOR_NO_THROW"))); }
            if (omni::string::ends_with(t, "const")) { t = omni::string::trim_end(t.substr(0, t.rfind("const"))); }
            tcode = t;
            if (!dc.empty()) {
                if ((i + 1) < len) {
                    s = lines[++i];
                    tcode = dc + s;
                }
                dc = std::string();
            }
            if (omni::string::contains(tcode, "template <") || omni::string::contains(tcode, "template<")) {
                int32_t idx = tcode.find("template");
                int32_t eidx = OmniDocuGen::Util::IndexOfChar(tcode, idx, '<');
                eidx = OmniDocuGen::Util::IndexOfCompliment(tcode, eidx, '<', '>');
                if (eidx >= 0 && eidx <= tcode.length()) {
                    t = tcode.substr(eidx + 1);
                    if (t.empty() || (!omni::string::contains(t, "(") && !omni::string::contains(t, ")"))) {
                        s = lines[++i];
                        cidx += s.length() + 2; // acount for /r/n
                        tcode += "\r\n" + s;
                        while (!omni::string::contains(s, "(")) {
                            s = lines[++i];
                            cidx += s.length() + 2; // acount for /r/n
                            tcode += "\r\n" + s;
                        }
                        if (omni::string::contains(s, "(") && !omni::string::contains(s, ")")) {
                            for (++i; i < len; ++i) {
                                if (OmniDocuGen::Program::StopReq) { return; }
                                s = lines[i];
                                cidx += s.length() + 2; // account for \r\n
                                tcode += "\r\n" + s;
                                if (omni::string::contains(s, ")")) {
                                    if (omni::string::contains(s, "{") && !omni::string::contains(s, "}")) {
                                        blvl = 1;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (!omni::string::trim(tcode).empty()) {
                try {
                    up(5, "Parsing MTI AsMember");
                    ptr_t mi(new MemberTypeInformation(tcode, this->This, OmniDocuGen::Types::MemberParseType::AsMember));
                    mi->ScopeAccessType = csat;
                    up(4, "Parsed {0} {1} '{2}'", mi->ScopeAccessType, mi->CodeType, mi->FullPath);
                    this->AddVerify(mi);
                    if (mi->CodeType == OmniDocuGen::Types::CodeStructureType::Ctor) {
                        if (!omni::string::contains(tcode, " :") && !omni::string::contains(tcode, ";") && !omni::string::contains(tcode, "{")) {
                            // it's a constructor but no ":" or ";" or "{", so find it
                            for (++i; i < len; ++i) {
                                if (OmniDocuGen::Program::StopReq) { return; }
                                s = lines[i];
                                cidx += s.length() + 2; // account for \r\n
                                if (omni::string::contains(s, ";") ||
                                    omni::string::contains(s, "{"))
                                {
                                    tcode = s;
                                    break;
                                }
                            }
                        }
                    }
                } catch (const std::exception& mex) {
                    OmniDocuGen::Program::AddError(mex, Util::Format("MTI error parsing funciton member info: tcode={0}", tcode));
                }
            }
            if (blvl > 0) {
                for (++i; i < len; ++i) {
                    if (OmniDocuGen::Program::StopReq) { return; }
                    s = lines[i];
                    cidx += s.length() + 2; // account for \r\n
                    if (omni::string::contains(s, "{")) { ++blvl; }
                    if (omni::string::contains(s, "}")) { --blvl; }
                    if (blvl == 0) { break; }
                }
            } else {
                if (omni::string::contains(tcode, " :\r\n") || omni::string::contains(tcode, " : ") || omni::string::ends_with(tcode, " :")) {
                    tcode = s.substr(s.rfind(" :"));
                    if (omni::string::contains(tcode, "{")) {
                        if (omni::string::contains(tcode, "}")) { continue; }
                        blvl = 1;
                    } else {
                        for (++i; i < len; ++i) {
                            if (OmniDocuGen::Program::StopReq) { return; }
                            s = lines[i];
                            cidx += s.length() + 2; // account for \r\n
                            if (omni::string::contains(s, "{") || omni::string::contains(s, ";")) {
                                blvl = 1;
                                break;
                            }
                        }
                        if (blvl == 1 && (omni::string::contains(s, "}") || omni::string::contains(s, ";"))) {
                            blvl = 0;
                            continue;
                        }
                    }
                    for (++i; i < len; ++i) {
                        if (OmniDocuGen::Program::StopReq) { return; }
                        s = lines[i];
                        cidx += s.length() + 2; // account for \r\n
                        if (omni::string::contains(s, "{")) { ++blvl; }
                        if (omni::string::contains(s, "}")) { --blvl; }
                        if (blvl == 0) { break; }
                    }
                } else if (omni::string::contains(tcode, "{")) {
                    if (omni::string::contains(tcode, "{") && omni::string::contains(tcode, "}")) { continue; }
                    blvl = 1;
                    for (++i; i < len; ++i) {
                        if (OmniDocuGen::Program::StopReq) { return; }
                        s = lines[i];
                        cidx += s.length() + 2; // account for \r\n
                        if (omni::string::contains(s, "{")) { ++blvl; }
                        if (omni::string::contains(s, "}")) { --blvl; }
                        if (blvl == 0) { break; }
                    }
                }
            }
        } catch (const std::exception& ex) {
            OmniDocuGen::Program::AddError(ex, "MTI error generally parsing function info");
        }
    }
}

/// 
/// <param name="code"></param>
void OmniDocuGen::MemberTypeInformation::_ParseClassMembers(std::string code)
{
    up(4, "Parsing class members.");
    const std::string tdef_struct = "typedef struct ";
    const std::string tdef_union = "typedef union ";
    const std::string tdef_enum = "typedef enum ";
    while (!omni::string::trim(code).empty()) {
        std::string tcode = OmniDocuGen::Util::StripComments(code);
        if (omni::string::trim(tcode).empty()) { return; }
        // remove comments so any thing found doesn't need to be checked if it's actually a declaration or if it's within a comment
        if (omni::string::contains(tcode, "class ") && omni::string::contains(tcode, "{") && omni::string::contains(tcode, "};")) {
            try {
                std::string line = Util::GetLineOfStringData(tcode, "class ");
                size_t beg, end;
                size_t cbeg = tcode.find("class ");
                if (omni::string::contains(line, "template ") && omni::string::contains(line, "<") && omni::string::contains(line, ">")) {
                    // all templates follow (template<*>)
                    cbeg = line.find("class");
                    beg = line.find("<");
                    end = line.find(">");
                    if ((cbeg > beg) && (cbeg < end)) {
                        beg = tcode.find(line) + line.size();
                        cbeg = tcode.find("class ", beg);
                    }
                }
                beg = tcode.find("{", cbeg);
                end = OmniDocuGen::Util::IndexOfCompliment(tcode, beg) + 2;
                std::string ocode = omni::string::trim_front(tcode.substr(0, end));
                std::string sub = tcode.substr(cbeg, beg-cbeg+1);
                int32_t idx = code.find(sub);
                if (idx >= 0) {
                    beg = OmniDocuGen::Util::IndexOfChar(code, idx, '{');
                    int32_t tidx = OmniDocuGen::Util::TemplateBefore(code, idx);
                    if (tidx >= 0) { idx = tidx; }
                    int32_t cidx = OmniDocuGen::Util::CommentBefore(code, idx);
                    if (cidx >= 0) { idx = cidx; }
                    int32_t eidx = OmniDocuGen::Util::IndexOfCompliment(code, beg) + 2;
                    ocode = code.substr(idx, eidx - idx);
                }
                try {
                    up(5, "Parsing class");
                    ptr_t mti(new MemberTypeInformation(ocode, this->This, OmniDocuGen::Types::MemberParseType::AsClass));
                    if (OmniDocuGen::Util::IsClassOrStruct(mti->CodeType) && OmniDocuGen::Util::IsClassOrStruct(this->CodeType)) {
                        idx = code.find("private:");
                        if ((idx >= 0) && (idx < code.find(ocode))) {
                            mti->ScopeAccessType = OmniDocuGen::Types::CodeScopeAcessType::Private;
                        }
                    }
                    up(4, "Parsed {0} {1} '{2}'", mti->ScopeAccessType, mti->CodeType, mti->FullPath);
                    this->AddVerify(mti);
                } catch (const std::exception& iex) {
                    OmniDocuGen::Program::AddError(iex, (std::string("Error parsing typedef, original code follows: ") + std::string(OMNI_EOL_N) + ocode));
                }

                code = omni::string::replace(code, ocode, "");
                up(4, "Parsed class, parsing additional code");
                //this->_ParseMembers(tcode);
            } catch (const std::exception& ex) {
                OmniDocuGen::Program::AddError(ex, "MTI error parsing member info");
            }
        } else if (omni::string::contains(tcode, tdef_struct) || omni::string::contains(tcode, tdef_union) || omni::string::contains(tcode, tdef_enum)) {
            up(4, "Code contains typedef struct/union/enum");
            std::string sval = "";
            if (omni::string::contains(tcode, tdef_struct)) {
                sval = tdef_struct;
            } else {
                if (omni::string::contains(tcode, tdef_union)) {
                    sval = tdef_union;
                } else {
                    sval = tdef_enum;
                }
            }
            try {
                int32_t sidx = code.find(sval);
                int32_t tlen = sidx + sval.length();
                int32_t bidx = OmniDocuGen::Util::IndexOfChar(code, sidx, '{');
                int32_t cidx = OmniDocuGen::Util::CommentBefore(code, sidx);
                int32_t eidx = OmniDocuGen::Util::IndexOfCompliment(code, bidx);
                std::string nm = omni::string::trim(code.substr(tlen, bidx - tlen));
                eidx += nm.length() + 2;
                if (cidx >= 0) { sidx = cidx; }
                std::string ocode = code.substr(sidx, eidx - sidx + 1);
                try {
                    ptr_t mti(new MemberTypeInformation(ocode, this->This, OmniDocuGen::Types::MemberParseType::AsTypedef));
                    this->AddVerify(mti);
                } catch (const std::exception& iex) {
                    OmniDocuGen::Program::AddError(iex, (std::string("Error parsing typedef, original code follows: ") + std::string(OMNI_EOL_N) + ocode));
                }

                code = omni::string::replace(code, ocode, "");
                up(4, "Parsing additional code");
                //this->_ParseMembers(tcode);
            } catch (const std::exception& ex) {
                OmniDocuGen::Program::AddError(ex, "MTI error parsing typedef");
            }
        } else {
            up(5, "Parsing function info.");
            this->_ParseFunctionInfo(code);
            up(4, "Parsed function info for {0}", this->FullPath);
            break;
        }
    }
}

/// If this instance is a class or namespace, this function is called which
/// parses the inner code for additional
/// <param name="code"></param>
void OmniDocuGen::MemberTypeInformation::_ParseMembers(const std::string& code)
{
    /*
        All namespace declarations in Omni follow the below syntax layout:
        
        namespace omni {
            namespace inner_ns_name {
                code.
            }
        }
        All class declarations in Omni follow the below syntx layout:
        
        (template <*>)
        class class_name (<template_specialization>) ( : ((virtual) (public/protected/private)) inherited_class)
        {
            code.
        };
        typedef's in Omni currently reside in the following formats:
        
        typedef (original type) new_type_name;
        typedef (function pointer type);
        typedef struct/enum/union struct_name {
        } struct_name;
    */
    if (omni::string::trim(code).empty()) { return; }
    std::string nss = "namespace ";
    // remove comments so any thing found doesn't need to be checked if it's actually a declaration or if it's within a comment
    std::string tcode = OmniDocuGen::Util::StripComments(code);
    if (omni::string::contains(tcode, nss)) {
        up(4, "Code contains 'namespace ', parsing.");
        size_t nspos = tcode.find(nss);
        std::string xns = Util::GetLineOfStringData(tcode, nss);
        if (omni::string::contains(xns, "=")) {
            // namespace err = XYZ;
            try {
                std::string ocode = "";
                int32_t idx = nspos;
                int32_t eidx = tcode.find(";", nspos);
                std::string sub = tcode.substr(idx, eidx - idx + 1);
                idx = code.find(sub);
                if (idx >= 0) {
                    eidx = idx + sub.length();
                    int32_t cidx = OmniDocuGen::Util::CommentBefore(code, idx);
                    if (cidx >= 0) { idx = cidx; }
                    ocode = omni::string::trim(code.substr(idx, eidx - idx));
                    tcode = omni::string::replace(code, ocode, "");
                } else {
                    ocode = omni::string::trim(tcode.substr(0, eidx));
                    tcode = omni::string::replace(tcode, ocode, "");
                }
                up(4, "Parsing potential namespace alias");
                ptr_t mti(new MemberTypeInformation(ocode, this->This, OmniDocuGen::Types::MemberParseType::AsNamespace));
                this->AddVerify(mti);
            } catch (const std::exception& ex) {
                OmniDocuGen::Program::AddError(ex, "MTI error parsing namespace");
            }
        } else {
            // namespace consts {
            xns = tcode.substr(nspos + nss.length());
            xns = xns.substr(OmniDocuGen::Util::IndexOfWsChar(xns));
            up(4, "Parsing namespace data");
            try {
                std::string ocode = "";
                int32_t idx = nspos;
                int32_t oidx = OmniDocuGen::Util::IndexOfChar(tcode, idx, '{');
                int32_t eidx = OmniDocuGen::Util::IndexOfCompliment(tcode, oidx);
                std::string sub = tcode.substr(idx, oidx - idx + 1);
                idx = code.find(sub);
                if (idx >= 0) {
                    oidx = OmniDocuGen::Util::IndexOfChar(code, idx, '{');
                    eidx = OmniDocuGen::Util::IndexOfCompliment(code, oidx);
                    int32_t cidx = OmniDocuGen::Util::CommentBefore(code, idx);
                    if (cidx >= 0) { idx = cidx; }
                    ocode = omni::string::trim(code.substr(idx, eidx - idx + 1));
                    tcode = omni::string::replace(code, ocode, "");
                } else {
                    ocode = omni::string::trim(tcode.substr(0, eidx));
                    tcode = omni::string::replace(tcode, ocode, "");
                }
                up(4, "Parsing namespace info");
                ptr_t mti(new MemberTypeInformation(ocode, this->This, OmniDocuGen::Types::MemberParseType::AsNamespace));
                this->AddVerify(mti);
            } catch (const std::exception& ex) {
                OmniDocuGen::Program::AddError(ex, "MTI error parsing general member");
            }
        }
        if (tcode == code && OmniDocuGen::Util::IsWithinComment(tcode, nss)) {
            this->_ParseClassMembers(tcode);
        } else {
            this->_ParseMembers(tcode);
        }
    } else {
        this->_ParseClassMembers(code);
    }
}