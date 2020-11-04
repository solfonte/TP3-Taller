#ifndef __SOCKET_H__
#define __SOCKET_H__
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <unistd.h>

class Socket{
  private:
    int fd;
    //ver si hace falta guardar el buffer aca creeria que no
    void bind_and_listen(const char* host,const char* service);
  public:
    Socket(const int file_descriptor);
    Socket(const char* host,const char* service);
    Socket(const char* service);
    ~Socket();
    int aceptar();
    Socket();
    void recibir();

};

#endif
