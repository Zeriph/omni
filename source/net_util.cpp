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
#include <omni/net/util.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>

/**
    Get the broadcast IP from a specified IP address and Subnet mask
    
    @param ip The IP to get the broadcast form
    @param subnet The subnet mask to get the broadcast from
    @return A string representation of the broadcast IP
*/
std::string omni::net::getBroadcastFromIpAndSubnet(const std::string &ip, const std::string &subnet)
{
    if (!omni::net::isValidIp(ip)) {
        #if defined(OMNI_SHOW_DEBUG_L1)
            dbgerr << "Invalid IP: " << ip << std::endl;
        #endif
        #if !defined(OMNI_NOTHROW)
            throw omni::exceptions::net::invalid_ip(ip);
        #endif
        return "";
    }
    if (!omni::net::isValidIp(subnet)) {
        #if defined(OMNI_SHOW_DEBUG_L1)
            dbgerr << "Invalid subnet mask IP: " << subnet << std::endl;
        #endif
        #if !defined(OMNI_NOTHROW)
            throw omni::exceptions::net::invalid_ip(subnet);
        #endif
        return "";
    }
    std::string Value = "255.255.255.255";
    OMNI_SEQ_T<std::string> CurrentIP = omni::string::split(ip, ".");
    OMNI_SEQ_T<std::string> CurrentMask = omni::string::split(subnet, ".");
    OMNI_SEQ_T<std::string> Broadcast;
    for (int count = 0; count < 3; count++) {
        int IpOct = omni::string::convert::toType<int>(CurrentIP[count]);
        int SubOct = omni::string::convert::toType<int>(CurrentMask[count]);
        int BitwiseShift = (IpOct | (SubOct ^ 255));
        Broadcast.push_back(omni::string::convert::fromInt(BitwiseShift));
    }
    Value = Broadcast[0] + "." + Broadcast[1] + "." + Broadcast[2] + "." + Broadcast[3];
    return Value;
}

/**
    Convert an IPv4 address to its numeric representation (e.g. 127.0.0.1 = 2130706433)
    
    @param ip The IPv4 address to convert
    @return An unsigned int representation of the IPv4 address
*/
unsigned int omni::net::ipToNum(const std::string &ip)
{
    if (!omni::net::isValidIp(ip)) {
        #if defined(OMNI_SHOW_DEBUG_L1)
            dbgerr << "Invalid IP: " << ip << std::endl;
        #endif
        #if !defined(OMNI_NOTHROW)
            throw omni::exceptions::net::invalid_ip(ip);
        #endif
        return 0;
    }
    OMNI_SEQ_T<std::string> Octets = omni::string::split(ip, ".");
    std::string soct1 = Octets.at(0);
    std::string soct2 = Octets.at(1);
    std::string soct3 = Octets.at(2);
    std::string soct4 = Octets.at(3);
    unsigned int oct1 = omni::string::convert::toType<int>(soct1) * (255*256*256); // 256^3
    unsigned int oct2 = omni::string::convert::toType<int>(soct2) * (255*256); // 256^2
    unsigned int oct3 = omni::string::convert::toType<int>(soct3) * (256); // 256^1
    unsigned int oct4 = omni::string::convert::toType<int>(soct4); // 256^0
    return (oct1+oct2+oct3+oct4);
}

/**
    Checks if a specified string is a valid IP between 0.0.0.0 and 255.255.255.255
    
    @param ip The value to check
    @param includeBroadcast False to only check between 0.0.0.1 and 255.255.255.254 (default of false)
    @return True if the IPv4 address is valid
*/
bool omni::net::isValidIp(const std::string &ip, bool includeBroadcast)
{
    int Oct1, Oct2, Oct3, Oct4;
    Oct1 = Oct2 = Oct3 = Oct4 = -1;
    OMNI_SEQ_T<std::string> Octets = omni::string::split(ip, ".");
    if (Octets.size() != 4) { return false; }
    std::string soct1 = Octets[0];
    std::string soct2 = Octets[1];
    std::string soct3 = Octets[2];
    std::string soct4 = Octets[3];
    if (!omni::string::isNumeric(soct1) || !omni::string::isNumeric(soct2) || 
        !omni::string::isNumeric(soct3) || !omni::string::isNumeric(soct4)) { return false; }
    Oct1 = atoi(soct1.c_str());
    Oct2 = atoi(soct2.c_str());
    Oct3 = atoi(soct3.c_str());
    Oct4 = atoi(soct4.c_str());
    if (Oct1 < 0 || Oct1 > 255) { return false; }
    if (Oct2 < 0 || Oct2 > 255) { return false; }
    if (Oct3 < 0 || Oct3 > 255) { return false; }
    if (Oct4 < 0 || Oct4 > 255) { return false; }
    if (includeBroadcast) {
        // 0.0.0.0 = network, 255.255.255.255 = broadcast .. valid IP's but not in the IP user space
        bool IsNetwork = (Oct1 == 0 && Oct2 == 0 && Oct3 == 0 && Oct4 == 0);
        bool IsBroadcast = (Oct1 == 255 && Oct2 == 255 && Oct3 == 255 && Oct4 == 255);
        if (IsNetwork || IsBroadcast) { return false; }
    }
    return true;
}

/**
    Checks if a specified port is a valid port between 0 and 65535 inclusivly
    
    @param port The value to check
    @return True if the port is valid, false otherwise
*/
bool omni::net::isValidPort(int port)
{
    return (port >= 0 && port <= 65535);
}

/**
    Convert a number into its IPv4 address string representation (e.g. 2130706433 = 127.0.0.1)
    
    @param num The number to convert to an IP (max of 4294967295)
    @return The IPv4 address string representation of the number passed
*/
std::string omni::net::numToIp(unsigned int num)
{
    unsigned int oct1 = num >> 24;
    unsigned int oct2 = ((num >> 16) ^ (oct1 << 8));
    unsigned int oct3 = (((num >> 8) ^ (oct2 << 8)) ^ (oct1 << 16));
    unsigned int oct4 = (((num ^ (oct1 << 24)) ^ (oct2 << 16)) ^ (oct3 << 8));
    std::string NewIp = (omni::string::convert::fromType<int>(oct1) + "." + 
            omni::string::convert::fromType<int>(oct2) + "." + 
            omni::string::convert::fromType<int>(oct3) + "." + 
            omni::string::convert::fromType<int>(oct4));
    #if defined(OMNI_SHOW_DEBUG_L1)
        if (!omni::net::isValidIp(NewIp, true)) {
            dbg << num << " -> " << NewIp << ", IP is invalid" << std::endl;
        }
    #endif
    return NewIp;
}

/**
    Gets the current network interfaces and their information
    
    @return A OMNI_SEQ_T<omni::net::NetworkInterface> containing all network interfaces on the machine
*/
OMNI_SEQ_T<omni::net::networkinterface> omni::net::getInterfaces()
{
    OMNI_SEQ_T<omni::net::networkinterface> Interfaces;
    //omni::net::NetworkInterface Iface;
    //Iface.Connection = new omni::net::Socket();
    //Interfaces.push_back(Iface);
    return Interfaces;
}

/**
    Gets whether or not the OS supports IPv4
    
    @return True if the OS supports IPv4
*/
bool omni::net::osSupportsIPv4()
{
    // TODO: Finish this
    return true;
}

/**
    Gets whether or not the OS supports IPv6
    
    @return True if the OS supports IPv6
*/
bool omni::net::osSupportsIPv6()
{
    // TODO: Finish this
    return true;
}

/**
    Ping a host or address
    
    @param ip The IP or hostname to ping
    @return A omni::net::pingreply with the ping status results
*/
omni::net::pingreply omni::net::ping(const std::string &ip)
{
    OMNI_UNUSED(ip);
    // TODO: for now .. fix
    omni::net::pingreply *Rep = new omni::net::pingreply();
    omni::net::pingreply Val = *Rep;
    delete Rep;
    return Val;
}
