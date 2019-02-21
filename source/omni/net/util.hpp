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
#include <omni/delegate/0.hpp>
#include <omni/delegate/1.hpp>
#include <omni/exception.hpp>
#include <string>
#include <csignal>

namespace omni {
    namespace net {
        namespace util {
            static std::string getBroadcastFromIpAndSubnet(const std::string &ip, const std::string &subnet);
            
            static omni_sequence_t<networkinterface> getInterfaces();

            static unsigned int ipToNum(const std::string &ip);
            static bool isValidIp(const std::string &ip, bool includeBroadcast = false);
            static bool isValidPort(int port);
            static std::string numToIp(unsigned int num);
            static bool osSupportsIPv4();
            static bool osSupportsIPv6();
            static omni::net::pingreply ping(const std::string &ip);
        }
    }
}

#endif // OMNI_NET_UTIL_HPP
