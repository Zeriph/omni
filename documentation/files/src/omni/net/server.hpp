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
#if !defined(OMNI_NET_SERVER_HPP)
#define OMNI_NET_SERVER_HPP 1
#include <omni/types/net_t.hpp>
#include <omni/net/socket.hpp>
#include <omni/net/endpoint_descriptor.hpp>
#include <omni/delegate/1.hpp>
#if defined(OMNI_SAFE_NET_SERVER)
    #include <omni/sync/basic_lock.hpp>
#endif

namespace omni {
    namespace net {
        class server
        {
            public:
                server() :
                    m_clients(),
                    m_sock(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP),
                    m_run(false)
                {
                    if (this->m_sock.bind(12345) == omni::net::socket_error::SUCCESS) {
                        this->m_sock.listen();
                    }
                }

                ~server()
                {
                    this->_stop();
                }

                void swap(omni::net::server& other);
                omni::event1<void, omni::net::endpoint_descriptor&> data_received;
                

                bool is_running() const
                {
                    omni::sync::scoped_basic_lock lock(&this->m_mtx);
                    return this->m_run;
                }

                void run()
                {
                    this->m_mtx.lock();
                    if (this->m_sock.is_listening()) {
                        this->m_run = true;
                    }
                    this->m_mtx.unlock();
                    while (this->is_running()) {
                        omni::net::endpoint_descriptor* client = new omni::net::endpoint_descriptor();
                        if (this->m_sock.accept(*client) == omni::net::socket_error::SUCCESS) {
                            this->m_clients.push_back(client);
                        }
                    }
                }

                void signal(int sig)
                {
                    omni::sync::scoped_basic_lock lock(&this->m_mtx);
                    uint32_t xfr = 0;
                    for (std::vector<omni::net::endpoint_descriptor*>::iterator client = this->m_clients.begin();
                        client != this->m_clients.end();
                        ++client)
                    {
                        (*client)->send("END", xfr);
                    }
                    this->m_run = false;
                }

                operator bool()
                {
                    omni::sync::scoped_basic_lock lock(&this->m_mtx);
                    return this->m_sock.is_listening();
                }

            private:
                std::vector<omni::net::endpoint_descriptor*> m_clients;
                omni::net::socket m_sock;
                mutable omni::sync::basic_lock m_mtx;
                volatile bool m_run;

                void _stop()
                {
                    omni::sync::scoped_basic_lock lock(&this->m_mtx);
                    for (std::vector<omni::net::endpoint_descriptor*>::iterator client = this->m_clients.begin();
                        client != this->m_clients.end();
                        ++client)
                    {
                        (*client)->close();
                        delete (*client);
                    }
                    this->m_clients.clear();
                    this->m_sock.disconnect(false); // shutdown and do not reuse socket
                }
        };
    }
}

namespace std {
    inline void swap(omni::net::server& o1, omni::net::server& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_NET_SERVER_HPP
