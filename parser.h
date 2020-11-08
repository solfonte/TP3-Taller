#ifndef __PARSER_H__
#define __PARSER_H__
#include <sstream>
#include "metodo.h"
#include "recursos_protegidos.h"

class Parser {
  public:
    Metodo* run(Recursos_protegidos* recursos, const std::string& buffer);
};

#endif
