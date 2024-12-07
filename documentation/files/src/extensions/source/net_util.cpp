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
#include <extensions/net/util.hpp>

// check out /Code/omni/references/future/omni/net.hpp

// TODO: add a omni::net::bluetooth socket and have it non-portable code .. example code:
/*
    #include <stdio.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <bluetooth/bluetooth.h>
    #include <bluetooth/rfcomm.h>

    int main(int argc, char **argv)
    {
        struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
        char buf[1024] = { 0 };
        int s, client, bytes_read;
        socklen_t opt = sizeof(rem_addr);

        if( argc < 2 )
        {	
        printf("usage: %s <bt-port> \n", argv[0]);
        return 1;
        }

        // allocate socket
        s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

        // bind socket to port of the first available 
        // local bluetooth adapter
        loc_addr.rc_family = AF_BLUETOOTH;
        loc_addr.rc_bdaddr = *BDADDR_ANY;
        loc_addr.rc_channel = (uint8_t) atoi(argv[1]);
        bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

        // put socket into listening mode
        listen(s, 1);

        // accept one connection
        client = accept(s, (struct sockaddr *)&rem_addr, &opt);

        ba2str( &rem_addr.rc_bdaddr, buf );
        fprintf(stderr, "accepted connection from %s\n", buf);
        memset(buf, 0, sizeof(buf));

        // read data from the client
        bytes_read = read(client, buf, sizeof(buf));
        if( bytes_read > 0 ) {
            printf("received [%s]\n", buf);
        }

        // close connection
        close(client);
        close(s);
        return 0;
    }
*/

// TODO: omni::net::pingreply ping(const std::string& ip);

/*

    //A simple Ping program to ping any address such as google.com in Linux 
    //run program as : gcc -o ping ping.c
    // then : ./ping google.com
    //can ping localhost addresses 
    //see the RAW socket implementation

    #include <stdio.h>
    #include <signal.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <netinet/ip_icmp.h>
    #include <netdb.h>
    #include <setjmp.h>
    #include <errno.h>
    #define PACKET_SIZE     4096
    #define MAX_WAIT_TIME   5
    #define MAX_NO_PACKETS  3

    char sendpacket[PACKET_SIZE];
    char recvpacket[PACKET_SIZE];
    int sockfd, datalen = 56;
    int nsend = 0, nreceived = 0;
    struct sockaddr_in dest_addr;
    pid_t pid;
    struct sockaddr_in from;
    struct timeval tvrecv;
    void statistics(int signo);
    unsigned short cal_chksum(unsigned short *addr, int len);
    int pack(int pack_no);
    void send_packet(void);
    void recv_packet(void);
    int unpack(char *buf, int len);
    void tv_sub(struct timeval *out, struct timeval *in);

    void statistics(int signo)
    {
        printf("\n--------------------PING statistics-------------------\n");
        printf("%d packets transmitted, %d received , %%%d lost\n", nsend, nreceived, (nsend - nreceived) / nsend * 100);
        close(sockfd);
        exit(1);
    } 

    unsigned short cal_chksum(unsigned short *addr, int len)
    {
        int nleft = len;
        int sum = 0;
        unsigned short *w = addr;
        unsigned short answer = 0;

        while (nleft > 1)
        {
            sum +=  *w++;
            nleft -= 2;
        }

        if (nleft == 1)
        {
            *(unsigned char*)(&answer) = *(unsigned char*)w;
            sum += answer;
        }
        sum = (sum >> 16) + (sum &0xffff);
        sum += (sum >> 16);
        answer = ~sum;
        return answer;
    }

    int pack(int pack_no)
    {
        int i, packsize;
        struct icmp *icmp;
        struct timeval *tval;
        icmp = (struct icmp*)sendpacket;
        icmp->icmp_type = ICMP_ECHO;
        icmp->icmp_code = 0;
        icmp->icmp_cksum = 0;
        icmp->icmp_seq = pack_no;
        icmp->icmp_id = pid;
        packsize = 8+datalen;
        tval = (struct timeval*)icmp->icmp_data;
        gettimeofday(tval, NULL); 
        icmp->icmp_cksum = cal_chksum((unsigned short*)icmp, packsize); 
        return packsize;
    }

    void send_packet()
    {
        int packetsize;
        while (nsend < MAX_NO_PACKETS)
        {
            nsend++;
            packetsize = pack(nsend); 
            if (sendto(sockfd, sendpacket, packetsize, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0)
            {
                perror("sendto error");
                continue;
            } sleep(1); 
        }
    }

    void recv_packet()
    {
        int n, fromlen;
        extern int errno;
        signal(SIGALRM, statistics);
        fromlen = sizeof(from);
        while (nreceived < nsend)
        {
            alarm(MAX_WAIT_TIME);
            if ((n = recvfrom(sockfd, recvpacket, sizeof(recvpacket), 0, (struct sockaddr*) &from, &fromlen)) < 0)
            {
                if (errno == EINTR)
                    continue;
                perror("recvfrom error");
                continue;
            } gettimeofday(&tvrecv, NULL); 

            if (unpack(recvpacket, n) ==  - 1)
                continue;

            nreceived++;
        }
    }

    int unpack(char *buf, int len)
    {
        int i, iphdrlen;
        struct ip *ip;
        struct icmp *icmp;
        struct timeval *tvsend;
        double rtt;
        ip = (struct ip*)buf;
        iphdrlen = ip->ip_hl << 2; 
        icmp = (struct icmp*)(buf + iphdrlen);
        len -= iphdrlen; 
        if (len < 8)
        {
            printf("ICMP packets\'s length is less than 8\n");
            return  - 1;
        } 

        if ((icmp->icmp_type == ICMP_ECHOREPLY) && (icmp->icmp_id == pid))
        {
            tvsend = (struct timeval*)icmp->icmp_data;
            tv_sub(&tvrecv, tvsend); 
            rtt = tvrecv.tv_sec * 1000+tvrecv.tv_usec / 1000;
            printf("%d byte from %s: icmp_seq=%u ttl=%d rtt=%.3f ms\n", len, inet_ntoa(from.sin_addr), icmp->icmp_seq, ip->ip_ttl, rtt);
        }
        else
            return  - 1;
    }

    main(int argc, char *argv[])
    {
        struct hostent *host;
        struct protoent *protocol;
        unsigned long inaddr = 0l;
        int waittime = MAX_WAIT_TIME;
        int size = 50 * 1024;
        if (argc < 2)
        {
            printf("usage:%s hostname/IP address\n", argv[0]);
            exit(1);
        }
        
        if ((protocol = getprotobyname("icmp")) == NULL)
        {
            perror("getprotobyname");
            exit(1);
        }

        if ((sockfd = socket(AF_INET, SOCK_RAW, protocol->p_proto)) < 0)
        {
            perror("socket error");
            exit(1);
        }

        setuid(getuid());
        setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
        bzero(&dest_addr, sizeof(dest_addr));
        dest_addr.sin_family = AF_INET;

        if (inaddr = inet_addr(argv[1]) == INADDR_NONE)
        {
            if ((host = gethostbyname(argv[1])) == NULL)
            {
                perror("gethostbyname error");
                exit(1);
            }
            memcpy((char*) &dest_addr.sin_addr, host->h_addr, host->h_length);
        }
        else
            dest_addr.sin_addr.s_addr = inet_addr(argv[1]);

        pid = getpid();
        printf("PING %s(%s): %d bytes data in ICMP packets.\n", argv[1], inet_ntoa(dest_addr.sin_addr), datalen);
        send_packet(); 
        recv_packet(); 
        statistics(SIGALRM); 
        return 0;
    }

    void tv_sub(struct timeval *out, struct timeval *in)
    {
        if ((out->tv_usec -= in->tv_usec) < 0)
        {
            --out->tv_sec;
            out->tv_usec += 1000000;
        } out->tv_sec -= in->tv_sec;
    }
*/


// TODO: omni::net::socket_error poll(omni::net::socket_t handle, uint32_t us, omni::net::select_mode mode);