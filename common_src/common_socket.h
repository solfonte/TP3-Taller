#ifndef __SOCKET_H__
#define __SOCKET_H__
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <unistd.h>
#include <exception>
#include <sstream>

class SocketException: public std::exception{
  public:
    std::string error;
    explicit SocketException(const std::string& error):
    error(error)
    {}
    const std::string getError() const { return this->error;}
};

class Socket{
  private:
    int fd;
  public:
    void bind_and_listen(const char* host,const char* service);
    void cerrar();
    Socket(Socket&& socket);
    ~Socket();
    Socket();
    Socket(const Socket& socket) = delete;
    void aceptar(Socket& peer)const;
    void enviar(const char* buffer, size_t length);
    ssize_t recibir(char* buffer, size_t length);
    void conectar(const char* host,const char* service);
    void cerrar_conexion(int modo);
};

#endif
