#if !defined(DOCUGEN_PROGRAM)
#define DOCUGEN_PROGRAM 1

#include <omnilib>
#include "helpers.hpp"
#include "Types.hpp"

#include <cstdarg>

#define up(...) OmniDocuGen::Program::UpdateStatus(__VA_ARGS__)

typedef omni::sync::parameterized_thread_start omni_task_t;
typedef omni::generic_ptr void_t;

namespace OmniDocuGen
{
    namespace Util
    {
        static inline std::string Format(const std::string& fmt,
            const std::string& v1)
        {
            return omni::string::replace_all(fmt, "{0}", v1);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            return omni::string::replace_all(ret, "{1}", v2);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            return omni::string::replace_all(ret, "{2}", v3);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            return omni::string::replace_all(ret, "{3}", v4);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            return omni::string::replace_all(ret, "{4}", v5);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            return omni::string::replace_all(ret, "{5}", v6);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            return omni::string::replace_all(ret, "{6}", v7);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            return omni::string::replace_all(ret, "{7}", v8);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            return omni::string::replace_all(ret, "{8}", v9);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            ret = omni::string::replace_all(ret, "{8}", v9);
            return omni::string::replace_all(ret, "{9}", v10);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            ret = omni::string::replace_all(ret, "{8}", v9);
            ret = omni::string::replace_all(ret, "{9}", v10);
            return omni::string::replace_all(ret, "{10}", v11);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            ret = omni::string::replace_all(ret, "{8}", v9);
            ret = omni::string::replace_all(ret, "{9}", v10);
            ret = omni::string::replace_all(ret, "{10}", v11);
            return omni::string::replace_all(ret, "{11}", v12);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            ret = omni::string::replace_all(ret, "{8}", v9);
            ret = omni::string::replace_all(ret, "{9}", v10);
            ret = omni::string::replace_all(ret, "{10}", v11);
            ret = omni::string::replace_all(ret, "{11}", v12);
            return omni::string::replace_all(ret, "{12}", v13);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            ret = omni::string::replace_all(ret, "{8}", v9);
            ret = omni::string::replace_all(ret, "{9}", v10);
            ret = omni::string::replace_all(ret, "{10}", v11);
            ret = omni::string::replace_all(ret, "{11}", v12);
            ret = omni::string::replace_all(ret, "{12}", v13);
            return omni::string::replace_all(ret, "{13}", v14);
        }
        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            ret = omni::string::replace_all(ret, "{8}", v9);
            ret = omni::string::replace_all(ret, "{9}", v10);
            ret = omni::string::replace_all(ret, "{10}", v11);
            ret = omni::string::replace_all(ret, "{11}", v12);
            ret = omni::string::replace_all(ret, "{12}", v13);
            ret = omni::string::replace_all(ret, "{13}", v14);
            return omni::string::replace_all(ret, "{14}", v15);
        }

        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            ret = omni::string::replace_all(ret, "{8}", v9);
            ret = omni::string::replace_all(ret, "{9}", v10);
            ret = omni::string::replace_all(ret, "{10}", v11);
            ret = omni::string::replace_all(ret, "{11}", v12);
            ret = omni::string::replace_all(ret, "{12}", v13);
            ret = omni::string::replace_all(ret, "{13}", v14);
            ret = omni::string::replace_all(ret, "{14}", v15);
            return omni::string::replace_all(ret, "{15}", v16);
        }

        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            ret = omni::string::replace_all(ret, "{8}", v9);
            ret = omni::string::replace_all(ret, "{9}", v10);
            ret = omni::string::replace_all(ret, "{10}", v11);
            ret = omni::string::replace_all(ret, "{11}", v12);
            ret = omni::string::replace_all(ret, "{12}", v13);
            ret = omni::string::replace_all(ret, "{13}", v14);
            ret = omni::string::replace_all(ret, "{14}", v15);
            ret = omni::string::replace_all(ret, "{15}", v16);
            return omni::string::replace_all(ret, "{16}", v17);
        }

        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17, const std::string& v18)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            ret = omni::string::replace_all(ret, "{8}", v9);
            ret = omni::string::replace_all(ret, "{9}", v10);
            ret = omni::string::replace_all(ret, "{10}", v11);
            ret = omni::string::replace_all(ret, "{11}", v12);
            ret = omni::string::replace_all(ret, "{12}", v13);
            ret = omni::string::replace_all(ret, "{13}", v14);
            ret = omni::string::replace_all(ret, "{14}", v15);
            ret = omni::string::replace_all(ret, "{15}", v16);
            ret = omni::string::replace_all(ret, "{16}", v17);
            return omni::string::replace_all(ret, "{17}", v18);
        }

        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17, const std::string& v18,
            const std::string& v19)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            ret = omni::string::replace_all(ret, "{8}", v9);
            ret = omni::string::replace_all(ret, "{9}", v10);
            ret = omni::string::replace_all(ret, "{10}", v11);
            ret = omni::string::replace_all(ret, "{11}", v12);
            ret = omni::string::replace_all(ret, "{12}", v13);
            ret = omni::string::replace_all(ret, "{13}", v14);
            ret = omni::string::replace_all(ret, "{14}", v15);
            ret = omni::string::replace_all(ret, "{15}", v16);
            ret = omni::string::replace_all(ret, "{16}", v17);
            ret = omni::string::replace_all(ret, "{17}", v18);
            return omni::string::replace_all(ret, "{18}", v19);
        }

        static inline std::string Format(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17, const std::string& v18,
            const std::string& v19, const std::string& v20)
        {
            std::string ret = omni::string::replace_all(fmt, "{0}", v1);
            ret = omni::string::replace_all(ret, "{1}", v2);
            ret = omni::string::replace_all(ret, "{2}", v3);
            ret = omni::string::replace_all(ret, "{3}", v4);
            ret = omni::string::replace_all(ret, "{4}", v5);
            ret = omni::string::replace_all(ret, "{5}", v6);
            ret = omni::string::replace_all(ret, "{6}", v7);
            ret = omni::string::replace_all(ret, "{7}", v8);
            ret = omni::string::replace_all(ret, "{8}", v9);
            ret = omni::string::replace_all(ret, "{9}", v10);
            ret = omni::string::replace_all(ret, "{10}", v11);
            ret = omni::string::replace_all(ret, "{11}", v12);
            ret = omni::string::replace_all(ret, "{12}", v13);
            ret = omni::string::replace_all(ret, "{13}", v14);
            ret = omni::string::replace_all(ret, "{14}", v15);
            ret = omni::string::replace_all(ret, "{15}", v16);
            ret = omni::string::replace_all(ret, "{16}", v17);
            ret = omni::string::replace_all(ret, "{17}", v18);
            ret = omni::string::replace_all(ret, "{18}", v19);
            return omni::string::replace_all(ret, "{19}", v20);
        }
    }

    namespace Program
    {
        extern volatile bool StopReq; // = false;
        extern volatile bool Silent; // = false;
        extern volatile uint32_t Verbosity;
        extern std::string AppPath; // = string.Empty;
        extern volatile bool SingleThreaded; // = false;
        extern volatile bool Profile; // = false;
        extern volatile bool FullTree; // = false;
        extern volatile uint32_t MaxMacroTheads;
        extern volatile uint32_t MaxMtiThreads;
        extern volatile uint32_t MaxHtmlSyntaxThreads;
        extern omni::sync::threadpool Tasks;
        
        static inline void AddError(const std::string& ex)
        {
            pl("ERROR: " << ex);
        }

        static inline void AddError(const std::exception& ex)
        {
            AddError(ex.what());
        }

        static inline void AddError(const std::exception& ex, const std::string& err)
        {
            pl("ERROR: " << err << std::endl << "Exception: " << ex.what());
        }

        static inline void AddParsingCode(const std::string& code)
        {
            if (!OmniDocuGen::Program::Silent) {
                pl("PARSING: '" << code << "'");
            }
        }

        static inline void RemoveParsingCode(const std::string& code)
        {
            if (!OmniDocuGen::Program::Silent) {
                pl("DONE_PARSING: '" << code << "'");
            }
        }

        /// Updates the current status
        static inline void UpdateStatus(uint32_t verbosity, const std::string& data)
        {
            if (!OmniDocuGen::Program::Silent && (Program::Verbosity >= verbosity)) {
                if (verbosity > 0) { pv("INFO_" << verbosity << ": "); }
                pl(data);
            }
        }

        static inline void UpdateStatus(const std::string& data)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, data);
        }

        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17, const std::string& v18)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17, const std::string& v18,
            const std::string& v19)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19));
        }
        static inline void UpdateStatus(uint32_t verbosity, const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17, const std::string& v18,
            const std::string& v19, const std::string& v20)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(verbosity, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v18));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17, const std::string& v18)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17, const std::string& v18,
            const std::string& v19)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19));
        }
        static inline void UpdateStatus(const std::string& fmt,
            const std::string& v1, const std::string& v2, const std::string& v3,
            const std::string& v4, const std::string& v5, const std::string& v6,
            const std::string& v7, const std::string& v8, const std::string& v9,
            const std::string& v10, const std::string& v11, const std::string& v12,
            const std::string& v13, const std::string& v14, const std::string& v15,
            const std::string& v16, const std::string& v17, const std::string& v18,
            const std::string& v19, const std::string& v20)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus(0, Util::Format(fmt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v18));
        }

        static inline void SetGenerationProgress(const OmniDocuGen::Types::GenerationStatus& g)
        {
            pl("STATUS: " << g);
        }

        static inline void AddGeneratedHelpFile(const std::string& file)
        {
            if (OmniDocuGen::Program::Silent) { return; }
            UpdateStatus("HTML: generated html class help {0}.html", file);
        }
    }
}

#endif // DOCUGEN_PROGRAM
