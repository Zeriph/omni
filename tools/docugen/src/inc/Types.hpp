#if !defined(DOCUGEN_TYPES)
#define DOCUGEN_TYPES 1

#include <omnilib>
#include "helpers.hpp"

namespace OmniDocuGen
{
    namespace Types
    {
        class GenerationStatus {
            public:
                /** The underlying enum type expected */
                typedef enum enum_t {
                    ParsingFiles,
                    GenStart,
                    BuildStart,
                    FileViewStart,
                    JsStart,
                    ClassesStart,
                    ClassIndexStart,
                    ExStart,
                    HtmlSyntaxStart,
                    MacroStart,
                    ApiStart,
                    BuildComplete,
                    ClassesComplete,
                    ClassIndexComplete,
                    ExComplete,
                    FileViewComplete,
                    HtmlSyntaxComplete,
                    MacroComplete,
                    JSComplete,
                    ApiComplete,
                    GenComplete,
                    MacroScanComplete,
                    SourceScanComplete,
                    ParseComplete,
                    MainComplete
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 25;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return ParsingFiles;
                }
                
                /** Converts the enum to its string representation */
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                /** Converts the enum to its wide string representation */
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                /** Parsing a string value into its enum representation */
                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                /** Parsing a wide string value into its enum representation */
                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, GenerationStatus& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, GenerationStatus& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                GenerationStatus() :
                    m_val(DEFAULT_VALUE())
                { }

                GenerationStatus(const GenerationStatus& cp) :
                    m_val(cp.m_val)
                { }

                GenerationStatus(enum_t val) : 
                    m_val(val)
                { }

                ~GenerationStatus()
                {
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const GenerationStatus& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                GenerationStatus& operator=(const GenerationStatus& val)
                {
                    if (this != &val) {
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                GenerationStatus& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                GenerationStatus& operator=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(val);
                    return *this;
                }

                bool operator<(const GenerationStatus& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const GenerationStatus& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const GenerationStatus& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val;
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_OSTREAM_FW(OmniDocuGen::Types::GenerationStatus)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, GenerationStatus& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(ParsingFiles)
                        OMNI_S2E_FW(GenStart)
                        OMNI_S2E_FW(BuildStart)
                        OMNI_S2E_FW(FileViewStart)
                        OMNI_S2E_FW(JsStart)
                        OMNI_S2E_FW(ClassesStart)
                        OMNI_S2E_FW(ClassIndexStart)
                        OMNI_S2E_FW(ExStart)
                        OMNI_S2E_FW(HtmlSyntaxStart)
                        OMNI_S2E_FW(MacroStart)
                        OMNI_S2E_FW(ApiStart)
                        OMNI_S2E_FW(BuildComplete)
                        OMNI_S2E_FW(ClassesComplete)
                        OMNI_S2E_FW(ClassIndexComplete)
                        OMNI_S2E_FW(ExComplete)
                        OMNI_S2E_FW(FileViewComplete)
                        OMNI_S2E_FW(HtmlSyntaxComplete)
                        OMNI_S2E_FW(MacroComplete)
                        OMNI_S2E_FW(JSComplete)
                        OMNI_S2E_FW(ApiComplete)
                        OMNI_S2E_FW(GenComplete)
                        OMNI_S2E_FW(MacroScanComplete)
                        OMNI_S2E_FW(SourceScanComplete)
                        OMNI_S2E_FW(ParseComplete)
                        OMNI_S2E_FW(MainComplete)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        case ParsingFiles: ss << "Parsing source files and generating classes."; break;
                        case GenStart: ss << "Generation and build process started."; break;
                        case BuildStart: ss << "Build started."; break;
                        case FileViewStart: ss << "File view (files.html) generation started."; break;
                        case JsStart: ss << "JavaScript search generation started."; break;
                        case ClassesStart: ss << "Class generation started."; break;
                        case ClassIndexStart: ss << "Started the class index (classes/index.html) generatation."; break;
                        case ExStart: ss << "Started examples generation."; break;
                        case HtmlSyntaxStart: ss << "HTML syntax highlighting generation started."; break;
                        case MacroStart: ss << "Macro documentation generation started."; break;
                        case ApiStart: ss << "API documentation generation started."; break;
                        case BuildComplete: ss << "Build complete!"; break;
                        case ClassesComplete: ss << "Class generation complete."; break;
                        case ClassIndexComplete: ss << "The class index (classes/index.html) has been generated."; break;
                        case ExComplete: ss << "Example generation complete."; break;
                        case FileViewComplete: ss << "File view (files.html) generation complete."; break;
                        case HtmlSyntaxComplete: ss << "HTML syntax highlighting complete."; break;
                        case MacroComplete: ss << "Macro documentation generation complete."; break;
                        case JSComplete: ss << "JavaScript search generation complete."; break;
                        case ApiComplete: ss << "API documentation generation complete."; break;
                        case GenComplete: ss << "Generation completed."; break;
                        case MacroScanComplete: ss << "API/Macro scan completed."; break;
                        case SourceScanComplete: ss << "Source scan completed."; break;
                        case ParseComplete: ss << "Source scanning and parsing completed."; break;
                        case MainComplete: ss << "All processes complete."; break;
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        ParsingFiles ||
                        GenStart ||
                        BuildStart ||
                        FileViewStart ||
                        JsStart ||
                        ClassesStart ||
                        ClassIndexStart ||
                        ExStart ||
                        HtmlSyntaxStart ||
                        MacroStart ||
                        ApiStart ||
                        BuildComplete ||
                        ClassesComplete ||
                        ClassIndexComplete ||
                        ExComplete ||
                        FileViewComplete ||
                        HtmlSyntaxComplete ||
                        MacroComplete ||
                        JSComplete ||
                        ApiComplete ||
                        GenComplete ||
                        MacroScanComplete ||
                        SourceScanComplete ||
                        ParseComplete ||
                        MainComplete
                    );
                }
        };

        class HashType {
            public:
                /** The underlying enum type expected */
                typedef enum enum_t {
                    SHA256,
                    SHA1,
                    MD5
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 3;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return SHA256;
                }
                
                /** Converts the enum to its string representation */
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                /** Converts the enum to its wide string representation */
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                /** Parsing a string value into its enum representation */
                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                /** Parsing a wide string value into its enum representation */
                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, HashType& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, HashType& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                HashType() :
                    m_val(DEFAULT_VALUE())
                { }

                HashType(const HashType& cp) :
                    m_val(cp.m_val)
                { }

                HashType(enum_t val) : 
                    m_val(val)
                { }

                ~HashType()
                {
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const HashType& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                HashType& operator=(const HashType& val)
                {
                    if (this != &val) {
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                HashType& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                HashType& operator=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(val);
                    return *this;
                }

                bool operator<(const HashType& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const HashType& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const HashType& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val;
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_OSTREAM_FW(OmniDocuGen::Types::HashType)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, HashType& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(SHA256)
                        OMNI_S2E_FW(SHA1)
                        OMNI_S2E_FW(MD5)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(SHA256);
                        OMNI_E2SS_FW(SHA1);
                        OMNI_E2SS_FW(MD5);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        SHA256 ||
                        SHA1 ||
                        MD5
                    );
                }
        };

        class SystemType {
            public:
                /** The underlying enum type expected */
                typedef enum enum_t {
                    Windows,
                    Apple,
                    Linux,
                    Unix,
                    POSIX,
                    STD
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 6;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return POSIX;
                }
                
                /** Converts the enum to its string representation */
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                /** Converts the enum to its wide string representation */
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                /** Parsing a string value into its enum representation */
                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                /** Parsing a wide string value into its enum representation */
                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, SystemType& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, SystemType& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                SystemType() :
                    m_val(DEFAULT_VALUE())
                { }

                SystemType(const SystemType& cp) :
                    m_val(cp.m_val)
                { }

                SystemType(enum_t val) : 
                    m_val(val)
                { }

                ~SystemType()
                {
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const SystemType& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                SystemType& operator=(const SystemType& val)
                {
                    if (this != &val) {
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                SystemType& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                SystemType& operator=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(val);
                    return *this;
                }

                bool operator<(const SystemType& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const SystemType& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const SystemType& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val;
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_OSTREAM_FW(OmniDocuGen::Types::SystemType)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, SystemType& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(Windows)
                        OMNI_S2E_FW(Apple)
                        OMNI_S2E_FW(Linux)
                        OMNI_S2E_FW(Unix)
                        OMNI_S2E_FW(POSIX)
                        OMNI_S2E_FW(STD)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(Windows);
                        OMNI_E2SS_FW(Apple);
                        OMNI_E2SS_FW(Linux);
                        OMNI_E2SS_FW(Unix);
                        OMNI_E2SS_FW(POSIX);
                        OMNI_E2SS_FW(STD);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        Windows ||
                        Apple ||
                        Linux ||
                        Unix ||
                        POSIX ||
                        STD
                    );
                }
        };

        class ProgramStartType {
            public:
                /** The underlying enum type expected */
                typedef enum enum_t {
                    Normal,
                    MacroGen,
                    LicenseRep,
                    NoHPPGen,
                    SysAPI,
                    HtmlHighlight,
                    MISC
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 7;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return Normal;
                }
                
                /** Converts the enum to its string representation */
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                /** Converts the enum to its wide string representation */
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                /** Parsing a string value into its enum representation */
                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                /** Parsing a wide string value into its enum representation */
                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, ProgramStartType& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, ProgramStartType& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                ProgramStartType() :
                    m_val(DEFAULT_VALUE())
                { }

                ProgramStartType(const ProgramStartType& cp) :
                    m_val(cp.m_val)
                { }

                ProgramStartType(enum_t val) : 
                    m_val(val)
                { }

                ~ProgramStartType()
                {
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const ProgramStartType& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                ProgramStartType& operator=(const ProgramStartType& val)
                {
                    if (this != &val) {
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                ProgramStartType& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                ProgramStartType& operator=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(val);
                    return *this;
                }

                bool operator<(const ProgramStartType& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const ProgramStartType& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const ProgramStartType& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val;
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_OSTREAM_FW(OmniDocuGen::Types::ProgramStartType)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, ProgramStartType& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(MISC)
                        OMNI_S2E_FW(Normal)
                        OMNI_S2E_FW(MacroGen)
                        OMNI_S2E_FW(LicenseRep)
                        OMNI_S2E_FW(NoHPPGen)
                        OMNI_S2E_FW(SysAPI)
                        OMNI_S2E_FW(HtmlHighlight)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(MISC);
                        OMNI_E2SS_FW(Normal);
                        OMNI_E2SS_FW(MacroGen);
                        OMNI_E2SS_FW(LicenseRep);
                        OMNI_E2SS_FW(NoHPPGen);
                        OMNI_E2SS_FW(SysAPI);
                        OMNI_E2SS_FW(HtmlHighlight);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        MISC ||
                        Normal ||
                        MacroGen ||
                        LicenseRep ||
                        NoHPPGen ||
                        SysAPI ||
                        HtmlHighlight
                    );
                }
        };

        // region MemberTypeInformation Types

        class CodeStructureType {
            public:
                /** The underlying enum type expected */
                typedef enum enum_t {
                    Namespace,
                    Class,
                    Struct,
                    Enum,
                    Ctor,
                    Dtor,
                    Function,
                    Operator,
                    Member,
                    Typedef,
                    File,
                    Unknown
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 12;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return Unknown;
                }
                
                /** Converts the enum to its string representation */
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                /** Converts the enum to its wide string representation */
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                /** Parsing a string value into its enum representation */
                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                /** Parsing a wide string value into its enum representation */
                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, CodeStructureType& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, CodeStructureType& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                CodeStructureType() :
                    m_val(DEFAULT_VALUE())
                { }

                CodeStructureType(const CodeStructureType& cp) :
                    m_val(cp.m_val)
                { }

                CodeStructureType(enum_t val) : 
                    m_val(val)
                { }

                ~CodeStructureType()
                {
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const CodeStructureType& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                CodeStructureType& operator=(const CodeStructureType& val)
                {
                    if (this != &val) {
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                CodeStructureType& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                CodeStructureType& operator=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(val);
                    return *this;
                }

                bool operator<(const CodeStructureType& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const CodeStructureType& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const CodeStructureType& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val;
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_OSTREAM_FW(OmniDocuGen::Types::CodeStructureType)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, CodeStructureType& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(Namespace)
                        OMNI_S2E_FW(Class)
                        OMNI_S2E_FW(Struct)
                        OMNI_S2E_FW(Enum)
                        OMNI_S2E_FW(Ctor)
                        OMNI_S2E_FW(Dtor)
                        OMNI_S2E_FW(Function)
                        OMNI_S2E_FW(Operator)
                        OMNI_S2E_FW(Member)
                        OMNI_S2E_FW(Typedef)
                        OMNI_S2E_FW(File)
                        OMNI_S2E_FW(Unknown)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(Namespace);
                        OMNI_E2SS_FW(Class);
                        OMNI_E2SS_FW(Struct);
                        OMNI_E2SS_FW(Enum);
                        OMNI_E2SS_FW(Ctor);
                        OMNI_E2SS_FW(Dtor);
                        OMNI_E2SS_FW(Function);
                        OMNI_E2SS_FW(Operator);
                        OMNI_E2SS_FW(Member);
                        OMNI_E2SS_FW(Typedef);
                        OMNI_E2SS_FW(File);
                        OMNI_E2SS_FW(Unknown);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        Namespace ||
                        Class ||
                        Struct ||
                        Enum ||
                        Ctor ||
                        Dtor ||
                        Function ||
                        Operator ||
                        Member ||
                        Typedef ||
                        File ||
                        Unknown
                    );
                }
        };

        class CodeScopeAcessType {
            public:
                /** The underlying enum type expected */
                typedef enum enum_t {
                    Public,
                    Protected,
                    Private
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 3;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return Public;
                }
                
                /** Converts the enum to its string representation */
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                /** Converts the enum to its wide string representation */
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                /** Parsing a string value into its enum representation */
                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                /** Parsing a wide string value into its enum representation */
                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, CodeScopeAcessType& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, CodeScopeAcessType& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                CodeScopeAcessType() :
                    m_val(DEFAULT_VALUE())
                { }

                CodeScopeAcessType(const CodeScopeAcessType& cp) :
                    m_val(cp.m_val)
                { }

                CodeScopeAcessType(enum_t val) : 
                    m_val(val)
                { }

                ~CodeScopeAcessType()
                {
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const CodeScopeAcessType& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                CodeScopeAcessType& operator=(const CodeScopeAcessType& val)
                {
                    if (this != &val) {
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                CodeScopeAcessType& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                CodeScopeAcessType& operator=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(val);
                    return *this;
                }

                bool operator<(const CodeScopeAcessType& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const CodeScopeAcessType& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const CodeScopeAcessType& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val;
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_OSTREAM_FW(OmniDocuGen::Types::CodeScopeAcessType)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, CodeScopeAcessType& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(Public)
                        OMNI_S2E_FW(Protected)
                        OMNI_S2E_FW(Private)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(Public);
                        OMNI_E2SS_FW(Protected);
                        OMNI_E2SS_FW(Private);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        Public ||
                        Protected ||
                        Private
                    );
                }
        };

        class MemberParseType {
            public:
                /** The underlying enum type expected */
                typedef enum enum_t {
                    AsNamespace,
                    AsClass,
                    AsTypedef,
                    AsMember,
                    AsSource
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 5;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return AsNamespace;
                }
                
                /** Converts the enum to its string representation */
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                /** Converts the enum to its wide string representation */
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                /** Parsing a string value into its enum representation */
                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                /** Parsing a wide string value into its enum representation */
                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, MemberParseType& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, MemberParseType& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                MemberParseType() :
                    m_val(DEFAULT_VALUE())
                { }

                MemberParseType(const MemberParseType& cp) :
                    m_val(cp.m_val)
                { }

                MemberParseType(enum_t val) : 
                    m_val(val)
                { }

                ~MemberParseType()
                {
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const MemberParseType& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                MemberParseType& operator=(const MemberParseType& val)
                {
                    if (this != &val) {
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                MemberParseType& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                MemberParseType& operator=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(val);
                    return *this;
                }

                bool operator<(const MemberParseType& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const MemberParseType& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const MemberParseType& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val;
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_OSTREAM_FW(OmniDocuGen::Types::MemberParseType)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, MemberParseType& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(AsNamespace)
                        OMNI_S2E_FW(AsClass)
                        OMNI_S2E_FW(AsTypedef)
                        OMNI_S2E_FW(AsMember)
                        OMNI_S2E_FW(AsSource)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(AsNamespace);
                        OMNI_E2SS_FW(AsClass);
                        OMNI_E2SS_FW(AsTypedef);
                        OMNI_E2SS_FW(AsMember);
                        OMNI_E2SS_FW(AsSource);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        AsNamespace ||
                        AsClass ||
                        AsTypedef ||
                        AsMember ||
                        AsSource
                    );
                }
        };

        class SourceGenType {
            public:
                /** The underlying enum type expected */
                typedef enum enum_t {
                    Normal,
                    BuildToo,
                    Xml
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 3;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return Normal;
                }
                
                /** Converts the enum to its string representation */
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                /** Converts the enum to its wide string representation */
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                /** Parsing a string value into its enum representation */
                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                /** Parsing a wide string value into its enum representation */
                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, SourceGenType& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, SourceGenType& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                SourceGenType() :
                    m_val(DEFAULT_VALUE())
                { }

                SourceGenType(const SourceGenType& cp) :
                    m_val(cp.m_val)
                { }

                SourceGenType(enum_t val) : 
                    m_val(val)
                { }

                ~SourceGenType()
                {
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const SourceGenType& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                SourceGenType& operator=(const SourceGenType& val)
                {
                    if (this != &val) {
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                SourceGenType& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                SourceGenType& operator=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(val);
                    return *this;
                }

                bool operator<(const SourceGenType& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const SourceGenType& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const SourceGenType& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val;
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_OSTREAM_FW(OmniDocuGen::Types::SourceGenType)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, SourceGenType& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(Normal)
                        OMNI_S2E_FW(BuildToo)
                        OMNI_S2E_FW(Xml)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(Normal);
                        OMNI_E2SS_FW(BuildToo);
                        OMNI_E2SS_FW(Xml);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        Normal ||
                        BuildToo ||
                        Xml
                    );
                }
        };

        // endregion
    }
}

#endif // DOCUGEN_TYPES