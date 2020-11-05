#ifndef __SERVER_H__
#define __SERVER_H__
#include "socket.h"
#include <string>
#include <sstream>


class Server{
  private:
    std::string puerto;
    std::string root_file;
    Socket aceptador,peer;
    std::stringbuf buffer;

  public:
    Server(const std::string& service,const std::string& root_file):
    puerto(service),
    root_file(root_file),
    aceptador(service.c_str()),
    //aceptador().aceptar(peer)
    peer(aceptador.aceptar())//chequear por que viola encapsulameinto
    {}
    void recibir();
};

#endif
