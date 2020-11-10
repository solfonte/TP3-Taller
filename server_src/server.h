#ifndef __SERVER_H__
#define __SERVER_H__
#include "../common_src/common_socket.h"
#include <string>
#include <sstream>
#include <vector>
#include "server_thAceptador.h"
#include "server_thClient.h"
#include "server_recursos_protegidos.h"

class Server{
  private:
    std::string service;
    std::string root_file;
    Socket aceptador;
    std::stringstream petitorio;
    Recursos_protegidos recursos;
    ThAceptador* thread;

  public:
    Server(const std::string& service,
          const std::string& root_file);
    std::string get_contenido_recurso(const std::string& recurso) const;
    void run();
    void procesar_request();
    void shutdown();
    void guardar_recurso(const std::string& recurso,
                          const std::string& contenido);
};

#endif
