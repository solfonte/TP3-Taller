#ifndef __SERVER_H__
#define __SERVER_H__
#include "../common_src/common_socket.h"
#include <string>
#include <sstream>
#include <vector>
#include "server_thread.h"
#include "server_recursos_protegidos.h"

class Server{
  private:
    std::string service;
    std::string root_file;
    Socket aceptador;
    std::stringstream petitorio;
    Recursos_protegidos recursos;
    ThAceptador* thread;
    std::vector<ThClient*> clientes;

  public:
    Server(const std::string& service,
          const std::string& root_file,std::mutex &m):
    service(service),
    root_file(root_file),
    aceptador(),
    petitorio(),
    recursos(root_file,m),
    thread(new ThAceptador(&this->aceptador,&recursos,m))
    //verificar que exista archivo
    {}
    std::string get_contenido_recurso(const std::string& recurso) const;
    std::string get_archivo_root();
    void run();
    void procesar_request();
    void shutdown();
    void guardar_recurso(const std::string& recurso,const std::string& contenido);
};

#endif
