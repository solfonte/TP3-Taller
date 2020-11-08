#ifndef __SERVER_H__
#define __SERVER_H__
#include "socket.h"
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "thread.h"

class Server{
  private:
    std::string service;
    std::string root_file;
    Socket aceptador,peer;
    std::stringstream petitorio;
    std::map<std::string,std::string> recursos;
    ThAceptador thread;
    std::vector<ThClient> clientes;

  public:
    Server(const std::string& service,const std::string& root_file):
    service(service),
    root_file(root_file),
    aceptador(),
    peer(),
    petitorio(),
    recursos()
    //verificar que exista archivo
    {}
    std::string get_contenido_recurso(const std::string& recurso) const;
    std::string get_archivo_root();
    void run();
    void procesar_request();
    void shutdown();
    void guardar_recurso(std::string& recurso,std::string& contenido);
};

#endif
