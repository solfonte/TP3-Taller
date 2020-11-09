#include "server_recursos_protegidos.h"
#include "server_lock.h"

std::string Recursos_protegidos::get_contenido_recurso
                    (const std::string& recurso) const{
  std::string contenido("");
  try{
    contenido = this->recursos.at(recurso);
  }catch (const std::out_of_range& oor){}
  return contenido;
}
void Recursos_protegidos::guardar_recurso(const std::string& recurso,const
                          std::string& contenido){
  Lock(this->m);
    this->recursos[recurso] = contenido;
}

std::string& Recursos_protegidos::get_archivo_root(){
  Lock(this->m);
  return this->root_file;
}
