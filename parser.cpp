#include "parser.h"
#include <iostream>
#include <string>

Metodo* parsear_metodo_get(std::string& petitorio){
  if(petitorio.find("/ HTTP") >= 0){
    return new GetSinRecurso("root");
  }else{
    return new GetConRecurso();
  }
}

Metodo* parsear_metodo_post(std::string& petitorio){
  if(petitorio.find("/ HTTP") >= 0){
    return new PostSinRecurso();
  }else{
    return new PostConRecurso();
  }
}

Metodo* parsear_metodo_invalido(std::string& petitorio){
  return new MetodoInvalido();
}
//capaz le llegaria una referencia a una reqquest para que la inicialice
Metodo* parsear_petitorio(std::string& petitorio){
  int res_get = petitorio.find("GET");
  int res_post = petitorio.find("POST");
  if(res_get >= 0){
    return parsear_metodo_get(petitorio);
  }else if(res_post >= 0){
    return parsear_metodo_post(petitorio);
  }else{
    return parsear_metodo_invalido(petitorio);
  }
}

Metodo* Parser::run(std::stringstream& buffer){
  std::string petitorio = buffer.str();
  return parsear_petitorio(petitorio);
}
