/*
 * Copyright (c), Zeriph Enterprises
 * All rights reserved.
 * 
 * Contributor(s):
 * Zechariah Perez, omni (at) zeriph (dot) com
 * 
 * THIS SOFTWARE IS PROVIDED BY ZERIPH AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ZERIPH AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(OMNI_NET_UTIL_HPP)
#define OMNI_NET_UTIL_HPP 1
#include <omni/types/net_t.hpp>
#include <omni/exception.hpp>
#include <omni/string/util.hpp>

namespace omni {
    namespace net {
        namespace util {
            inline bool try_parse_ip4(const std::string& ip, uint32_t& result)
            {
                if (ip.empty()) { return false; }
                if (ip.size() > 19) { return false; }
                int64_t ipval = -1;
                if (ip.find(".") != std::string::npos) { // parse octets
                    omni::seq::std_string_t octs = omni::cstring::split(ip, ".");
                    if (octs.size() > 4 || octs.size() < 2) { return false; }
                    // 0377.0377.0377.0377
                    // 0xFF.0xFF.0xFF.0xFF
                    // 255.255.255.255
                    // A.B.C.D | A.B.D | A.D
                    int oct = -1;
                    ipval = 0;
                    for (int i = 0; i < octs.size(); ++i, oct = -1) {
                        if (octs[i].empty() || octs[i].size() > 4) { return false; }
                        if ((octs[i].size() > 1) && (octs[i].at(0) == '0')) { // hex/octal?
                            if ((octs[i].size() > 2) && ((octs[i].at(1) == 'x') || (octs[i].at(1) == 'X'))) { // hex
                                // it's valid hex if the string is 0x0 to 0xFF
                                if (!omni::char_util::is_hex(octs[i].at(2))) { return false; }
                                if ((octs[i].size() > 3) && !omni::char_util::is_hex(octs[i].at(3))) { return false; }
                                std::stringstream ss;
                                ss << std::hex << octs[i].substr(2);
                                ss >> oct;
                            } else { // octal
                                oct = 0;
                                for (size_t c = 1; c < octs[i].size(); ++c) {
                                    if (!omni::char_util::is_octal(octs[i].at(c))) { return false; }
                                    switch (octs[i].size() - c) {
                                        case 1: oct += (omni::char_util::to_int(octs[i].at(c))); break;
                                        case 2: oct += (omni::char_util::to_int(octs[i].at(c)) * 8); break;
                                        case 3: oct += (omni::char_util::to_int(octs[i].at(c)) * 64); break;
                                    }
                                }
                            }
                        } else { // regular number
                            if (!omni::string::util::is_numeric(octs[i])) { return false; }
                            oct = omni::string::util::to_type<int>(octs[i]);
                        }
                        if (oct > 255 || oct < 0) { return false; }
                        switch (octs.size()) {
                            case 2: ipval += ((i == 0) ? (static_cast<uint32_t>(oct) << 24) : oct); break;
                            case 3:
                                switch (i) {
                                    case 0: ipval += (static_cast<uint32_t>(oct) << 24); break;
                                    case 1: ipval += (static_cast<uint32_t>(oct) << 16); break;
                                    case 2: ipval += oct; break;
                                    default: break;
                                }
                                break;
                            case 4: ipval += (static_cast<uint32_t>(oct) << ((3 - i) * 8)); break;
                            default: break;
                        }
                    }
                } else { // parse hex/octal/numeric
                    // 0xFFFFFFFF <- max hex
                    // 037777777777 <- max octal
                    // 4,294,967,295 <- max int
                    if ((ip.size() > 1) && (ip.at(0) == '0')) { // hex/octal
                        ipval = 0;
                        if ((ip.at(1) == 'x') || (ip.at(1) == 'X')) {
                            // hex
                            std::string tmp_ip = omni::cstring::reverse(ip.substr(2));
                            int64_t p = 1;
                            for (int cnt = 0; cnt < tmp_ip.size(); ++cnt, p *= 16) {
                                if (!omni::char_util::is_hex(tmp_ip.at(cnt))) { return false; }
                                ipval += (static_cast<int64_t>(omni::char_util::to_int(tmp_ip.at(cnt), true)) * p);
                            }
                        } else {
                            // octal
                            std::string tmp_ip = omni::cstring::reverse(ip.substr(1));
                            int64_t p = 1;
                            for (int cnt = 0; cnt < tmp_ip.size(); ++cnt, p *= 8) {
                                if (!omni::char_util::is_octal(tmp_ip.at(cnt))) { return false; }
                                ipval += (static_cast<int64_t>(omni::char_util::to_int(tmp_ip.at(cnt), true)) * p);
                            }
                        }
                    } else if (omni::cstring::is_numeric(ip)) { // numeric val
                        ipval = omni::string::util::to_type<int64_t>(ip);
                    }
                }
                if ((ipval >= 0) && (ipval <= 0xFFFFFFFF)) {
                    result = static_cast<uint32_t>(ipval);
                    return true;
                }
                return false;
            }

            inline bool try_parse_ip4(const std::wstring& ip, uint32_t& result)
            {
                return omni::net::util::try_parse_ip4(omni::string::to_string(ip), result);
            }

            inline bool is_valid_dotted_ip4(const std::string& ip)
            {
                uint32_t tmp = 0;
                return omni::net::util::try_parse_ip4(ip, tmp);
            }

            inline bool is_valid_dotted_ip4(const std::wstring& ip)
            {
                return omni::net::util::is_valid_dotted_ip4(omni::string::to_string(ip));
            }

            inline bool is_valid_ip4(const std::string& ip)
            {
                uint32_t tmp = 0;
                return omni::net::util::try_parse_ip4(ip, tmp);
            }

            inline bool is_valid_ip4(const std::wstring& ip)
            {
                return omni::net::util::is_valid_ip4(omni::string::to_string(ip));
            }

            inline bool is_valid_port(uint64_t port)
            {
                return (port <= 65535);
            }
            
            inline bool is_valid_port(int64_t port) 
            {
                return (port >= 0 && port <= 65535);
            }
            
            inline bool is_valid_port(uint32_t port)
            {
                return (port <= 65535);
            }
            
            inline bool is_valid_port(int32_t port)
            {
                return (port >= 0 && port <= 65535);
            }
            
            inline omni::string_t to_dotted_ip4_string_t(uint32_t num)
            {
                omni::sstream_t ss;
                ss << (num >> 24) << "."
                   << ((num & 0x00FF0000) >> 16) << "."
                   << ((num & 0x0000FF00) >> 8) << "."
                   << (num & 0x000000FF);
                return ss.str();
            }

            inline std::string to_dotted_ip4_string(uint32_t num)
            {
                std::stringstream ss;
                ss << (num >> 24) << "."
                   << ((num & 0x00FF0000) >> 16) << "."
                   << ((num & 0x0000FF00) >> 8) << "."
                   << (num & 0x000000FF);
                return ss.str();
            }

            inline std::wstring to_dotted_ip4_wstring(uint32_t num)
            {
                std::wstringstream ss;
                ss << (num >> 24) << "."
                   << ((num & 0x00FF0000) >> 16) << "."
                   << ((num & 0x0000FF00) >> 8) << "."
                   << (num & 0x000000FF);
                return ss.str();
            }

            //static std::string getBroadcastFromIpAndSubnet(const std::string &ip, const std::string &subnet);
            
            /*
            static omni_sequence_t<networkinterface> getInterfaces();
            static bool osSupportsip4();
            static bool osSupportsIPv6();
            static omni::net::pingreply ping(const std::string &ip);
            */
        }
    }
}

#endif // OMNI_NET_UTIL_HPP
