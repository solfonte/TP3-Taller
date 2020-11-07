#include "parser.h"
#include <iostream>
#include <string>

std::string generar_contenido_recurso(const std::string& petitorio){
  int res = petitorio.find("\n\n");
  std::string contenido("");
  if (res >= 0){
    contenido = petitorio.substr(res,petitorio.size()-1);
    std::cout << contenido << "\n";
  }
  return contenido;
}

std::string generar_recurso(const std::string& petitorio){
  int pos_inicial = petitorio.find('/') + 1;
  int pos_final = petitorio.find("HTTP") - 1;
  std::string recurso = petitorio.substr(pos_inicial,pos_final);
  std::cout << recurso << "\n";
  return recurso;
}

Metodo* parsear_metodo_get(Server& servidor,const std::string& petitorio){
  int res = petitorio.find("/ HTTP");
  if (res >= 0){
    return new GetSinRecurso(servidor.get_archivo_root());
  }else{
    std::string recurso = generar_recurso(petitorio);
    std::string contenido = servidor.get_contenido_recurso(recurso);
    bool recurso_existe = (contenido.size() > 0? true:false);
    return new GetConRecurso(recurso_existe,contenido);
  }
}

Metodo* parsear_metodo_post(Server& servidor,const std::string& petitorio){
  int res = petitorio.find("/ HTTP");
  if(res >= 0){
    return new PostSinRecurso();
  }else{
    std::string recurso = generar_recurso(petitorio);
    std::string contenido = generar_contenido_recurso(petitorio);
    servidor.guardar_recurso(recurso,contenido);
    return new PostConRecurso();
  }
}

Metodo* Parser::run(Server& servidor, const std::string& petitorio){
  int res_get = petitorio.find("GET");
  int res_post = petitorio.find("POST");
  if(res_get >= 0){
    return parsear_metodo_get(servidor,petitorio);
  }else if(res_post >= 0){
    return parsear_metodo_post(servidor,petitorio);
  }else{
    return new MetodoInvalido();
  }
}
