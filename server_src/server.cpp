#include "server.h"
#include "server_parser.h"
#include "server_metodo.h"
#include <iostream>
/*
Server& Server::operator=(Server&& other){
  this->service = std::move(other.service);
  this->root_file = std::move(other.root_file);
  this->aceptador = std::move(other.aceptador);
  this->petitorio = std::move(other.petitorio);
  this->recursos = std::move(other.recursos);
  this->thread = std::move(other.thread);
  this->clientes = std::move(other.clientes);
  return *this;
}
*/
void Server::shutdown(){
  this->aceptador.cerrar_conexion(SHUT_RD);
  this->aceptador.cerrar();
  this->thread->join();
  delete this->thread;
}

void Server::run(){
  const char* servicio_aux = this->service.c_str();
  this->aceptador.bind_and_listen(INADDR_ANY,servicio_aux);
  this->thread = new ThAceptador(&this->aceptador,&recursos,this->m);
  this->thread->start();
}

std::string Server::get_contenido_recurso(const std::string& recurso) const{
  return this->recursos.get_contenido_recurso(recurso);
}

std::string Server::get_archivo_root(){
  return this->root_file;
}

void Server::guardar_recurso(const std::string& recurso,
                            const std::string& contenido){
  this->recursos.guardar_recurso(recurso,contenido);
}
