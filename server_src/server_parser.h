#ifndef __PARSER_H__
#define __PARSER_H__
#include <sstream>
#include "server_metodo.h"
#include "server_recursos_protegidos.h"
#include <string>

class Parser {
  public:
    Metodo* run(Recursos_protegidos* recursos, const std::string& buffer);
};

#endif
