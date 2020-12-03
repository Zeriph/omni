#if !defined(DOCUGEN_HELPER)
#define DOCUGEN_HELPER 1

#include <omnilib>
#include <vector>

#define List std::vector
#define pl(v) std::cout << v << std::endl
#define pv(v) std::cout << v
#define pe(v) std::cerr << v << std::endl
#if defined(DOC_DEBUG)
    #define dbg(v) std::cout << __FUNCTION__ << "_DEBUG: " << v << std::endl
    #define dbgv(v) std::cout << __FUNCTION__ << "_DEBUG: " << v
#else
    #define dbg(v) for(;;)
    #define dbgv(v) for(;;)
#endif
#define foreach(t, n, v) for (List<t>::iterator n = v.begin(); n != v.end(); ++n)
#define foreach_c(t, n, v) for (List<t>::const_iterator n = v.begin(); n != v.end(); ++n)
#define foreach_t(t, n, v) for (t::iterator n = v.begin(); n != v.end(); ++n)
#define foreach_tc(t, n, v) for (t::const_iterator n = v.begin(); n != v.end(); ++n)
#define has(a, v) (std::find(a.begin(), a.end(), v) != a.end())
#define has_not(a, v) (std::find(a.begin(), a.end(), v) == a.end())

/*
static inline std::string get_tag(const std::string& xml, const std::string& tag)
{
    std::size_t pos = xml.find(std::string("<") + tag);
    if (pos != std::string::npos) {
        pos = xml.find(">", pos);
        if (pos != std::string::npos) {
            std::size_t epos = xml.find((std::string("</") + tag), ++pos);
            if (epos != std::string::npos) {
                return xml.substr(pos, (epos - pos));
            }
        }
    }
    return "";
}
*/

template < typename T >
inline T get_tag(const std::string& xml, const std::string& tag)
{
    std::string btag = "<" + tag + ">";
    std::size_t pos = xml.find(btag);
    if (pos != std::string::npos) {
        pos += btag.length();
        if (pos < xml.length()) {
            std::size_t epos = xml.find(("</" + tag + ">"), pos);
            if (epos != std::string::npos) {
                return omni::string::util::template to_type<T>(xml.substr(pos, (epos - pos)));
            }
        }
    }
    return T();
}

template <>
inline std::string get_tag(const std::string& xml, const std::string& tag)
{
    std::string btag = "<" + tag + ">";
    std::size_t pos = xml.find(btag);
    if (pos != std::string::npos) {
        pos += btag.length();
        if (pos < xml.length()) {
            std::size_t epos = xml.find(("</" + tag + ">"), pos);
            if (epos != std::string::npos) {
                return xml.substr(pos, (epos - pos));
            }
        }
    }
    return "";
}

template < typename T >
inline std::string gen_tag(T val, const std::string& tag)
{
    std::stringstream ss;
    ss << "  <" << tag << ">" << val << "</" << tag << ">\r\n";
    return ss.str();
}

template <>
inline std::string gen_tag(bool val, const std::string& tag)
{
    std::stringstream ss;
    ss << "  <" << tag << ">" << (val ? "true" : "false") << "</" << tag << ">\r\n";
    return ss.str();
}

inline std::string replace_dl_html(std::string html)
{
    size_t pos = html.find("<li title=\"Download or view the latest source\">");
    if (pos != std::string::npos) {
        size_t ep = html.find("</li>", pos) + 5;
        if (ep != std::string::npos) {
            ep = html.size();
        }
        html.replace(pos, (ep-pos), "");
    }
    return html;
}

#endif
