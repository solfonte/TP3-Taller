#ifndef __PARSER_H__
#define __PARSER_H__
#include <sstream>
#include "metodo.h"

class Parser {
  public:
    Metodo* run(std::stringstream& buffer);
};

#endif
