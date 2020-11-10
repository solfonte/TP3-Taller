#include "server_parser.h"
#include <string>

std::string generar_metodo_invalido(const std::string& petitorio){
  int res = petitorio.find("/");
  std::string contenido("");
  if (res >= 0){
    contenido = petitorio.substr(0,res);
  }
  return contenido;
}

std::string generar_contenido_recurso(const std::string& petitorio){
  int inicio = petitorio.find("<");
  int fin = petitorio.find_last_of(">") - 1;
  std::string contenido("");
  if (inicio >= 0 && fin >= 0){
    contenido = petitorio.substr(inicio,fin);
  }
  return contenido;
}

std::string generar_recurso(const std::string& petitorio){
  int pos_inicial = petitorio.find('/') + 1;
  int pos_final = petitorio.find("HTTP") - 1;
  std::string recurso = petitorio.substr(pos_inicial,pos_final);
  return recurso;
}

static Metodo* parsear_metodo_get(Recursos_protegidos& recursos,
                            const std::string& petitorio){
  int res = petitorio.find("/ HTTP");
  if (res >= 0){
    return new GetSinRecurso(recursos.get_archivo_root());
  }else{
    std::string recurso = generar_recurso(petitorio);
    std::string contenido = recursos.get_contenido_recurso(recurso);
    bool recurso_existe = (contenido.size() > 0? true:false);
    return new GetConRecurso(recurso_existe,contenido);
  }
}

static Metodo* parsear_metodo_post(Recursos_protegidos& recursos,
                            const std::string& petitorio){
  int res = petitorio.find("/ HTTP");
  if (res >= 0){
    return new PostSinRecurso();
  }else{
    std::string recurso = generar_recurso(petitorio);
    std::string contenido = generar_contenido_recurso(petitorio);
    recursos.guardar_recurso(recurso,contenido);
    return new PostConRecurso(contenido);
  }
}

Metodo* Parser::run(Recursos_protegidos& recursos,
                    const std::string& petitorio){
  int res_get = petitorio.find("GET");
  int res_post = petitorio.find("POST");
  if (res_get >= 0){
    return parsear_metodo_get(recursos,petitorio);
  }else if (res_post >= 0){
    return parsear_metodo_post(recursos,petitorio);
  }else{
    std::string metodo = generar_metodo_invalido(petitorio);
    return new MetodoInvalido(metodo);
  }
}
