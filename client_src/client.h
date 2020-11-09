#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "../common_src/common_socket.h"
#include <string>
#include <sstream>

class Client{
  private:
    Socket client;
    std::string host;
    std::string service;
    std::stringstream respuesta;
  public:
    Client(const std::string& host,const std::string& service):
      client(),
      host(host),
      service(service)
      {}
    void enviar();
    void run();
    void recibir();
};

#endif
