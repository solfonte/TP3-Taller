#ifndef __SOCKET_H__
#define __SOCKET_H__
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <unistd.h>
#include <exception>


class SocketException: public std::exception{
  public:
    std::string error;
    SocketException(const std::string& error):
    error(error)
    {}
    const std::string getError() const { return this->error;}
};

class Socket{
  private:
    int fd;
    //ver si hace falta guardar el buffer aca creeria que no
    void bind_and_listen(const char* host,const char* service);
  public:
    Socket(const int file_descriptor);
    Socket(const char* host,const char* service);
    Socket(const char* service);
    Socket(Socket&& socket);
    ~Socket();
    int aceptar();
    Socket();
    void recibir(/*char* buffer*/);
    void conectar(const char* host,const char* service);
};

#endif
