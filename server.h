#ifndef __SERVER_H__
#define __SERVER_H__
#include "socket.h"
#include <string>

class Server{
  private:
    std::string puerto;
    std::string root_file;
    Socket aceptador,peer;

  public:
    Server(const std::string& puerto,const std::string& root_file);
    void recibir();
    //run();
};

#endif
