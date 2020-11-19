#include "server_recursos_protegidos.h"
#include "server_lock.h"
#include <fstream>

std::string Recursos_protegidos::get_contenido_recurso
                    (const std::string& recurso){
  Lock lock(this->m);
  std::string contenido("");
  try{
    contenido = this->recursos.at(recurso);
  }catch (const std::out_of_range& oor){}
  return contenido;
}

void Recursos_protegidos::guardar_recurso(const std::string& recurso,const
                          std::string& contenido){
  Lock lock(this->m);
    this->recursos[recurso] = contenido;
}

std::string Recursos_protegidos::get_contenido_archivo_root(){
  Lock lock(this->m);
  std::ifstream fs;
  std::string respuesta = "";
  fs.open(this->root_file);
  if (!fs){
    respuesta += "ERROR: no se pudo abrir el archivo" + this->root_file + "\n";
  }else{
    std::string contenido;
    while (getline(fs,contenido,'\n')){
      respuesta += contenido;
    }
    fs.close();
  }
  return respuesta;
}
