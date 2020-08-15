#if !defined(DOCUGEN_MEMBER_TYPE_INFO)
#define DOCUGEN_MEMBER_TYPE_INFO 1

#include <omnilib>
#include "helpers.hpp"
#include "CommentInfo.hpp"
#include "ParameterInfo.hpp"
#include "Program.hpp"
#include "Types.hpp"

namespace OmniDocuGen
{
    //class CodeGen;

    /// Defines a parsed type (class/namespace)
    class MemberTypeInformation
    {
        public:
            typedef omni::smart_ptr<MemberTypeInformation> ptr_t;

            /// Gets the type (class/namespace) this instance represents
            OmniDocuGen::Types::CodeStructureType CodeType;
            /// Gets the doxygen comment (if any)
            OmniDocuGen::CommentInformation::ptr_t Comment;
            /// Gets the full path of this object (x::y::z)
            std::string FullPath;
            /// Gets the index of this instance within the parent node
            int32_t Index;
            /// Gets the object this class type is inherited from (if any).
            /// (applies only to CodeTypes of Class or Typedef)
            std::string InheritedFrom;
            /// Gets if this type is static or not (has keyword static).
            bool IsStatic;
            /// Gets if this type is inline or not (has keyword inline).
            bool IsInline;
            /// Gets if this is an explicit ctor
            bool IsExplicit;
            /// Gets if the function type is overloaded (applies only to functions).
            bool IsOverloaded() const
            {
                return this->Overloads.size() > 0;
            }
            /// Gets if this instance is an overload of another
            bool IsAnOverload() const
            {
                return this->OverloadIndex > 0;
            }
            /// The level in the tree (scope) of this instance
            int32_t Level;
            /// Gets the members associated with this instance
            /// (applies only to CodeTypes of Class or Namespace)
            List<ptr_t> Members;
            /// Gets the name of this instance
            std::string Name;
            /// Gets if this instance is a namespace alias
            /// (applies only to CodeTypes of Namespace)
            bool IsNamespaceAlias() const
            {
                return !this->NamespaceAlias.empty();
            }
            /// Gets the namespace alias (if any)
            /// (applies only to CodeTypes of Namespace)
            std::string NamespaceAlias;
            /// Gets the code originally used to parse this instance
            std::string OriginalCode;
            /// Gets the owner source code of the object
            std::string OwnerSourceFile;
            /// Gets the functions that are overloaded
            /// (applies only to CodeTypes of Function types)
            List<ptr_t> Overloads;
            /// Gets the index of the overload (if any)
            int32_t OverloadIndex;
            /// Gets the parent node of this instance (NULL if this instance is the top)
            ptr_t Parent;
            /// Defines the parameters of the function/member
            /// (applies only to CodeTypes of Function or Typedef)
            List<ParameterInformation::ptr_t> Parameters;
            /// Gets the return type this instance represents
            /// (applies only to CodeTypes of Function, Member or Typedef)
            std::string ReturnType;
            /// Gets the scope access of this instance (public/protected/private)
            /// (does NOT apply to Namespace's)
            OmniDocuGen::Types::CodeScopeAcessType ScopeAccessType;
            /// Gets if the code is a templated class or function
            bool IsTemplated() const
            {
                return !this->Template.empty();
            }
            /// Gets if the code is a specialized templated class or function
            bool IsSpecializedTemplate() const
            {
                return !this->TemplateSpecialization.empty();
            }
            /// Gets the template <> value if any associated with this instance
            /// (applies only to CodeTypes of Class or Namespace)
            std::string Template;
            /// Gets the specialized template value of the class (if any associated)
            /// (applies only to CodeTypes of Class or Namespace)
            std::string TemplateSpecialization;
            /// Gets the file this member is implemented in
            std::string ImplFile;
            /// Gets the header file this member is a part of
            std::string HeaderFile;
            /// Gets where this member was found
            int32_t FoundAtLine;
            /// Gets where this member was found in the source implementation
            int32_t SourceImplLine;
            /// Get the line of the header file this member was found at
            int32_t HeaderLine;
            /// Gets the signature of this instance
            std::string Signature;
            /// the #include file
            std::string Include;
            ptr_t This;

            MemberTypeInformation();
            MemberTypeInformation(MemberTypeInformation& cp);
            MemberTypeInformation(bool xml, const std::string& srcFile);
            MemberTypeInformation(const std::string& code);
            MemberTypeInformation(const std::string& code, const std::string& srcFile, const std::string& hFile, const std::string& srcCode);
            MemberTypeInformation(const std::string& code, const std::string& srcFile, const std::string& hFile, const std::string& srcCode, ptr_t& allmti);
            MemberTypeInformation(const std::string& name, int32_t index, OmniDocuGen::Types::CodeStructureType ct, ptr_t& parent);
            MemberTypeInformation(const std::string& code, ptr_t& prnt);
            MemberTypeInformation(const std::string& code, ptr_t& prnt, OmniDocuGen::Types::MemberParseType mpt);
            
            ~MemberTypeInformation()
            {
                this->This.reset();
            }

            void Add(ptr_t& ti);
            void AddVerify(ptr_t& ti);
            /* MemberTypeInformation DeepCopy(); */
            bool Equals(const MemberTypeInformation& mti) const;
            bool Equals(ptr_t& mti) const;
            ptr_t Find(ptr_t& m);
            ptr_t Find(const std::string& full_path);
            int32_t GetNodeCount(bool includeSubTrees);
            std::string GetSignature(bool fp, bool fpdesc);
            std::string GetFilePath() const;
            bool MembersHaveMembes();
            operator std::string() const;
            bool operator==(const MemberTypeInformation& cp) const;
            bool operator==(ptr_t cp) const;
            MemberTypeInformation& operator=(const MemberTypeInformation& cp);
            std::string ToXML() const;
            void SetOwnerInfoAndLinkIndex(const std::string& src, const std::string& hdr, const std::string& code);
            void LinkSources(ptr_t allmti);
            static ptr_t GetOmni(bool includeComment);
            static ptr_t FromXML(std::string xml, const std::string& srcFile);
            static bool CompareMemberTypeInformationDeref(const MemberTypeInformation& x, const MemberTypeInformation& y);
            static bool CompareMemberTypeInformation(const ptr_t& x, const ptr_t& y);

        private:
            void _ResetMemberFullPaths();
            void _Add(ptr_t ti);
            void _Parse(const std::string& code, OmniDocuGen::Types::MemberParseType mpt);
            void _ParseAsNamespace(const std::string& code);
            void _ParseAsClass(const std::string& code);
            void _ParseAsTypedef(const std::string& code);
            void _ParseAsMember(const std::string& code);
            std::string _ParseDocComment(const std::string& cmnt);
            void _ParseFunctionInfo(const std::string& code);
            void _ParseClassMembers(std::string code);
            void _ParseMembers(const std::string& code);
    };

    namespace Types
    {
        struct TreeNode
        {
            uint32_t Level;
            List<TreeNode> Nodes;
            std::string Name;
            std::string Text;
            MemberTypeInformation::ptr_t Tag;

            TreeNode() :
                Level(), Nodes(), Name(), Text(), Tag()
            {}

            explicit TreeNode(const std::string& txt) :
                Level(), Nodes(), Name(), Text(txt), Tag()
            {}

            explicit TreeNode(const MemberTypeInformation::ptr_t& mti) :
                Level(), Nodes(), Name(), Text(), Tag()
            {
                if (mti) {
                    this->SetRoot(mti);
                }
            }

            TreeNode(const TreeNode& cp) :
                Level(cp.Level), Nodes(cp.Nodes), Name(cp.Name), Text(cp.Text), Tag(cp.Tag)
            {}

            void AddNode(TreeNode& node)
            {
                node.Level = this->Level + 1;
                this->Nodes.push_back(node);
            }

            std::string GetTextTree() const
            {
                return TreeNode::GetAsciiTree(*this);
            }

            void SetRoot(const MemberTypeInformation::ptr_t& mti)
            {
                this->Nodes.clear();
                if (mti) {
                    this->Level = mti->Level;
                    this->Name = mti->FullPath;
                    this->Text = mti->Name;
                }
                this->Tag = mti;
            }

            TreeNode& operator=(const TreeNode& cp)
            {
                this->Level = cp.Level;
                this->Nodes = cp.Nodes;
                this->Name = cp.Name;
                this->Text = cp.Text;
                this->Tag = cp.Tag;
                return *this;
            }

            bool operator==(const TreeNode& cp) const
            {
                return this->Level == cp.Level &&
                       this->Nodes == cp.Nodes &&
                       this->Name == cp.Name &&
                       this->Text == cp.Text && 
                       this->Tag == cp.Tag;
            }

            bool operator!=(const TreeNode& cp) const
            {
                return !(this->Level == cp.Level &&
                         this->Nodes == cp.Nodes &&
                         this->Name == cp.Name &&
                         this->Text == cp.Text && 
                         this->Tag == cp.Tag);
            }

            bool operator<(const TreeNode& cp) const
            {
                if (this->Level == cp.Level) {
                    return this->Name < cp.Name;
                }
                return this->Level < cp.Level;
            }

            bool operator>(const TreeNode& cp) const
            {
                if (this->Level == cp.Level) {
                    return this->Name > cp.Name;
                }
                return this->Level > cp.Level;
            }

            List<TreeNode>::iterator Find(const std::string& name, bool search_all)
            {
                foreach (TreeNode, node, this->Nodes) {
                    if (OmniDocuGen::Program::StopReq) { return this->Nodes.end(); }
                    if (node->Name == name) {
                        return node;
                    }
                    if (search_all) {
                        if (OmniDocuGen::Program::StopReq) { return this->Nodes.end(); }
                        List<TreeNode>::iterator sub = node->Find(name, true);
                        if (sub != node->Nodes.end()) {
                            return sub;
                        }
                    }
                }
                return this->Nodes.end();
            }

            static void AddNodes(TreeNode& n, TreeNode& tnc)
            {
                if (n.Text == tnc.Text) {
                    foreach (TreeNode, t, n.Nodes) {
                        if (OmniDocuGen::Program::StopReq) { return; }
                        //((OmniDocuGen::MemberTypeInformation&)tnc.Tag).AddVerify((OmniDocuGen::MemberTypeInformation&)t.Tag);
                        TreeNode::AddNodes(*t, tnc);
                    }
                } else {
                    bool found = false;
                    foreach (TreeNode, t, tnc.Nodes) {
                        if (OmniDocuGen::Program::StopReq) { return; }
                        if (n.Text == t->Text) {
                            foreach (TreeNode, t2, n.Nodes) {
                                if (OmniDocuGen::Program::StopReq) { return; }
                                //((OmniDocuGen::MemberTypeInformation&)t.Tag).AddVerify((OmniDocuGen::MemberTypeInformation&)t2.Tag);
                                TreeNode::AddNodes(*t2, *t);
                            }
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        //((OmniDocuGen::MemberTypeInformation&)tnc.Tag).AddVerify((OmniDocuGen::MemberTypeInformation&)n.Tag);
                        tnc.AddNode(n);
                    }
                }
            }

            static std::string GetAsciiTree(const TreeNode& root)
            {
                std::string t = "";
                if (OmniDocuGen::Program::FullTree) { t = "[NS] "; }
                std::string r = t + root.Text + OMNI_EOL_N + "{" + OMNI_EOL_N;
                foreach_c (TreeNode, sub, root.Nodes) {
                    if (OmniDocuGen::Program::StopReq) { return ""; }
                    r += TreeNode::GetAsciiSubTree(*sub, ".  ");
                }
                return r + "}" + OMNI_EOL_N;
            }

            static std::string GetAsciiSubTree(const TreeNode& node, const std::string& level)
            {
                std::string t = node.Text;
                if (OmniDocuGen::Program::FullTree) {
                    if (node.Tag) {
                        t = "[" + Util::ToString(node.Tag->CodeType, true) + "] " + node.Tag->FullPath;
                    } else {
                        t = "[UNK] " + t;
                    }
                }
                std::string r = level + t + OMNI_EOL_N;
                if (node.Nodes.size() > 0) {
                    r += level + "{" + OMNI_EOL_N;
                }
                foreach_c (TreeNode, sub, node.Nodes) {
                    if (OmniDocuGen::Program::StopReq) { return ""; }
                    r += TreeNode::GetAsciiSubTree(*sub, (level + ".  "));
                }
                if (node.Nodes.size() > 0) {
                    r += level + "}" + OMNI_EOL_N;
                }
                return r;
            }
        };
    }
}

#endif // DOCUGEN_MEMBER_TYPE_INFO
