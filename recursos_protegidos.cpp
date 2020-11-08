#include "recursos_protegidos.h"

std::string Recursos_protegidos::get_contenido_recurso(const std::string& recurso) const{
  std::string contenido("");
  try{
    contenido = this->recursos.at(recurso);
  }catch (const std::out_of_range& oor){}
  return contenido;

}
void Recursos_protegidos::guardar_recurso(std::string& recurso,std::string& contenido){
    this->recursos[recurso] = contenido;
}

std::string Recursos_protegidos::get_archivo_root(){
  return this->root_file;
}
