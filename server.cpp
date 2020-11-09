#include "server.h"
#include "parser.h"
#include "metodo.h"
#include <iostream>

void Server::procesar_request(){
  this->clientes[0]->run();//deberia ser start
  delete this->clientes[0];
}

void Server::shutdown(){
  this->aceptador.cerrar_conexion(SHUT_RD);
  this->aceptador.cerrar();
  //this->thread->join();
}

void Server::run(){
  const char* servicio_aux = this->service.c_str();
  this->aceptador.bind_and_listen(INADDR_ANY,servicio_aux);
  //this->thread = new ThAceptador(&this->clientes,&this->aceptador,&recursos);
  std::cout << "entro acac\n";
  this->thread.run();//deberia ser start
}

std::string Server::get_contenido_recurso(const std::string& recurso) const{
  return this->recursos.get_contenido_recurso(recurso);
}

std::string Server::get_archivo_root(){
  return this->root_file;
}

void Server::guardar_recurso(std::string& recurso,std::string& contenido){
  this->recursos.guardar_recurso(recurso,contenido);
}
