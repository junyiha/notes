#include "header.h"

#include <socket.h>
#include <in.h>
class Server
{
public:
    bool m_is_ip6;
    std::string m_ip_addr;
    int m_type;
    int m_protocol;
    struct sockaddr m_addr;

public:
    Server();

    virtual ~Server();
public:
    int demo();

};

Server::Server()
{
    m_is_ip6 = false;
    m_type = SOCK_STREAM;
    m_protocol = IPPROTO_TCP;
    m_addr.sa_data = "127.0.0.1:9999";

}

Server::~Server()
{

}

int Server::demo()
{
    int af = m_is_ip6 : AF_INET6 : AF_INET;
    int fd = socket(af, m_type, m_protocol);

    bind(fd, m_addr, sizeof(m_addr));

    listen(fd, 3);
}