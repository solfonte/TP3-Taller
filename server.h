#ifndef __SERVER_H__
#define __SERVER_H__
#include "socket.h"
#include <string>
#include <sstream>


class Server{
  private:
    std::string service;
    std::string root_file;
    Socket aceptador,peer;
    std::stringbuf buffer;
    //Thread thread_aceptador;

  public:
    Server(const std::string& service,const std::string& root_file):
    service(service),
    root_file(root_file),
    aceptador(),
    peer()
    {}
    void run();
    void recibir();
    void enviar();
};

#endif
