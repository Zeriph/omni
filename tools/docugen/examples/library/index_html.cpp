#include <omnilib>

typedef std::vector<omni::net::endpoint_descriptor*> endpoint_list;

class server {
    public:
        server() :
            m_clients(),
            m_sock(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP),
            m_mtx(),
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
            uint32_t sent = 0;
            char buff[] = {'E','N','D','\0'};
            std_foreach(endpoint_list, client, this->m_clients) {
                (*client)->send(buff, sent);
            }
            this->m_run = false;
        }

        operator bool()
        {
            omni::sync::scoped_basic_lock lock(&this->m_mtx);
            return this->m_sock.is_listening();
        }

    private:
        endpoint_list m_clients;
        omni::net::socket m_sock;
        mutable omni::sync::basic_lock m_mtx;
        volatile bool m_run;

        void _stop()
        {
            omni::sync::scoped_basic_lock lock(&this->m_mtx);
            std_foreach(endpoint_list, client, this->m_clients) {
                (*client)->close();
                delete (*client);
            }
            this->m_sock.disconnect(false); // shutdown and don't reuse socket
        }
};

int main(int argc, const char* argv[])
{
    server srv;
    if (srv) {
        omni::application::run_type rt = omni::application::run_type::EXIT_WITH_WORK_THREAD |
                                         omni::application::run_type::KILL_WORKER_ON_SIGNAL;
        omni::application::signal_handler::attach(omni::application::signal_handler::callback::bind<server, &server::signal>(&srv));
        return omni::application::run(argc, argv, omni::sync::bind<server, &server::run>(&srv), rt);
    }
    return -1;
}
