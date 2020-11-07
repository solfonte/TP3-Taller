#ifndef __PARSER_H__
#define __PARSER_H__
#include <sstream>
#include "metodo.h"
#include "server.h"


class Parser {
  public:
    Metodo* run(Server& servidor, const std::string& buffer);
};

#endif
