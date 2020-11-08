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
    SocketException(const std::string& error):
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
    void aceptar(Socket& peer)const;
    Socket();
    void enviar(const char* buffer, size_t length);
    void recibir(std::stringstream& petitorio);
    void conectar(const char* host,const char* service);
    void cerrar_conexion(int modo);
};

#endif
