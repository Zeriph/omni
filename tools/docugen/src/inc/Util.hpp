#if !defined(DOCUGEN_UTIL)
#define DOCUGEN_UTIL 1

#include <omnilib>
#include <map>
#include "helpers.hpp"
#include "Program.hpp"
#include "Types.hpp"

#if !defined(OMNIDOCUGEN_OMNI_PATH)
    #if defined(OMNI_OS_WIN)
        #define OMNIDOCUGEN_OMNI_PATH "C:\\Code\\omni\\"
    #else
        #define OMNIDOCUGEN_OMNI_PATH "/Code/omni/"
    #endif
#endif

namespace OmniDocuGen
{
    /**
     * A simple utilitarian class
     */
    namespace Util
    {
        const uint32_t KB = 1000;
        const uint32_t MB = 1000000;
        const uint32_t GB = 1000000000;
        const uint64_t TB = 1000000000000;
        const uint32_t KiB = 1024;
        const uint32_t MiB = 1048576;
        const uint32_t GiB = 1073741824;
        const uint64_t TiB = 1099511627776;

        // The Windows line ending
        const std::string WinLe = OMNI_EOL_RN;
        // The *nix line ending
        const std::string NixLe = OMNI_EOL_N;
        // Defines the current Omni library base directory (not source)
        const std::string OmniPath = OMNIDOCUGEN_OMNI_PATH;
        // OMNI_INCLUDE_OBJECT_HDR
        const std::string OIOH = "OMNI_INCLUDE_OBJECT_HDR";

        typedef std::map<std::string, std::string> path_map;
        extern path_map m_validPaths;
        extern List<std::string> m_validExt;
        extern List<std::string> m_cExt;

        
        bool DeleteFile(const std::string& fpath);
        bool MoveFile(const std::string& s, const std::string& d);
        bool CopyFile(const std::string& s, const std::string& d, bool o);
        void CopyDirectory(const std::string& s, const std::string& sp, const std::string& d, bool r, bool o);
        void CopyDirectory(const std::string& s, const std::string& d, bool r, bool o);
        void CopyDirectory(const std::string& s, const std::string& d, bool r);
        bool WriteFile(const std::string& file, std::string text, int rtry, int tout, bool repnl);
        bool WriteFile(std::string file, std::string text);
        bool WriteFile(std::string file, std::string text, bool repnl);
        void WriteRedirect(const std::string& dir, const std::string& redir, uint32_t idx);
        void CheckAndCreateDirWithRedir(const std::string& dir, const std::string& redir, uint32_t idx);
        void CheckAndCreateDir(const std::string& dir);
        void WriteRedirectDirectories(const std::string& dir, const std::string& redir, uint32_t idx);
        bool ZipDirectory(const std::string& dir, const std::string& z, bool id);
        bool ZipDirectory(const std::string& dir, const std::string& z);
        bool RemoveEntryFromZip(const std::string& z, const std::string& f);
        std::string LastWriteTime(const std::string& file);
        std::string StripSlashes(const std::string& s);
        std::string NormalizeEndings(const std::string& s);
        std::string NormalizeEndings(const std::string& s, bool usrn);
        std::string NormalizeRN(const std::string& s);
        std::string NormalizeN(const std::string& s);
        std::string ToHTML(const std::string& s);
        std::string TabToWhitespaceHTML(const std::string& s);
        std::string ReplaceAll(std::string hay, const std::string& ndl, const std::string& rep);
        std::string StripHTMLbr(const std::string& s);
        List<std::string> SplitAtEndings(const std::string& s);
        List<std::string> Split(const std::string& s, const std::string& del);
        int IndexOfNonWsChar(const std::string& s);
        int IndexOfWsChar(const std::string& s);
        int IndexOfNonWsChar(const std::string& s, int idx);
        int IndexOfWsChar(const std::string& s, int idx);
        std::string ReplaceBeginingWhitespaceHTML(const std::string& s);
        std::string DiskSpaceToString(long diskSpace, int digits, std::string btype);
        std::string DiskSpaceToString(long diskSpace);
        std::string MergeWithNewLine(const List<std::string>& arr);
        List<int32_t> IndexesOf(const std::string& s, const std::string& val);
        std::map<size_t, size_t> IndexOfCompliments(const std::string& str, const std::string& val, bool useFindFirst);
        std::map<size_t, size_t> IndexOfCompliments(const std::string& str, const std::string& val);
        // does auto '{' '}'
        int32_t IndexOfCompliment(const std::string& s, int32_t idx);
        int32_t IndexOfCompliment(const std::string& s, int32_t idx, char bc, char ec);
        int32_t IndexOfCompliment(const std::string& s, int32_t idx, const std::string& bc, const std::string& ec);
        int32_t IndexOfChar(const std::string& s, int32_t idx, char c);
        int32_t IndexOfString(const std::string& s, int32_t idx, const std::string& t);
        int32_t IndexOfStringReverse(const std::string& s, int32_t idx, const std::string& t);
        int32_t TemplateBefore(const std::string& s, int32_t clsidx);
        int32_t CommentBefore(const std::string& s, int32_t idx);
        std::string GetComment(const std::string& s, int32_t idx);
        std::string GetComment(const std::string& s);
        bool IsWithinComment(const std::string& s, const std::string& val);
        std::string StripDocCommentStars(const std::string& s);
        std::string StripComments(const std::string& s);
        std::string StripComment(const std::string& code);
        std::string ToFilePath(const std::string& s);
        std::string GetTag(const std::string& s, const std::string& tag_name);
        std::string GetTagData(const std::string& s, const std::string& tag_name);
        std::string RemoveTag(const std::string& s, const std::string& tag_name);
        std::string GetLineOfStringData(const std::string& str, const std::string& find, size_t start);
        std::string GetLineOfStringData(const std::string& str, const std::string& find);
        bool IsPrivate(const OmniDocuGen::Types::CodeScopeAcessType& csat);
        bool IsProtected(const OmniDocuGen::Types::CodeScopeAcessType& csat);
        bool IsPublic(const OmniDocuGen::Types::CodeScopeAcessType& csat);
        bool IsNamespace(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsFile(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsEnum(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsStruct(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsClass(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsCtor(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsDtor(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsFunction(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsMember(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsTypedef(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsNsOrClass(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsMemberFnType(const OmniDocuGen::Types::CodeStructureType&  cst);
        bool IsClassOrStruct(const OmniDocuGen::Types::CodeStructureType&  cst);
        std::string ToString(const OmniDocuGen::Types::CodeStructureType& cst, bool useShortHand);
        bool IsValidExt(const std::string& ext);
        bool IsSourceExt(const std::string& ext);
        bool IsHeaderExt(const std::string& ext);
        bool IsCExtension(const std::string& ext);
    }
}

#endif // DOCUGEN_UTIL
