#ifndef __SERVER_H__
#define __SERVER_H__
#include "socket.h"
#include <string>
#include <sstream>
#include <map>


class Server{
  private:
    std::string service;
    std::string root_file;
    Socket aceptador,peer;
    std::stringstream petitorio;
    std::map<std::string,std::string> request;
    //Thread thread_aceptador;

  public:
    Server(const std::string& service,const std::string& root_file):
    service(service),
    root_file(root_file),
    aceptador(),
    peer(),
    petitorio(),
    request()
    //verificar que exista archivo
    {}
    void run();
    void recibir();
    void enviar();
    void shutdown();
};

#endif
