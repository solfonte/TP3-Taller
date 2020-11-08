#include "server.h"
#include "parser.h"
#include "metodo.h"
#include <iostream>

std::string crear_primer_linea(const std::string& petitorio){
  int pos = petitorio.find('\n');
  std::string primer_linea = petitorio;
  if (pos > -1){
    primer_linea = petitorio.substr(0,pos);
  }
  return primer_linea;
}

void Server::procesar_request(){
  this->peer.recibir(this->petitorio);
  this->peer.cerrar_conexion(SHUT_RD);
  std::string primer_linea_petitorio = crear_primer_linea(this->petitorio.str());
  std::cout << primer_linea_petitorio << "\n";
  Parser parser;
  Metodo* metodo = parser.run(*this,this->petitorio.str());
  std::string rta = metodo->obtener_respuesta();
  this->peer.enviar(rta.c_str(),rta.size());
  delete metodo;
}

void Server::shutdown(){
  this->aceptador.cerrar_conexion(SHUT_RD);
}

void Server::run(){
  const char* servicio_aux = this->service.c_str();
  this->aceptador.bind_and_listen(INADDR_ANY,servicio_aux);

  //lanzo el thread acetador y ahi se llama al accept
  this->aceptador.aceptar(this->peer);
  
}

std::string Server::get_contenido_recurso(const std::string& recurso) const{
  std::string contenido("");
  try{
    contenido = this->recursos.at(recurso);
  }catch (const std::out_of_range& oor){}
  return contenido;
}

std::string Server::get_archivo_root(){
  return this->root_file;
}

void Server::guardar_recurso(std::string& recurso,std::string& contenido){
  this->recursos[recurso] = contenido;
}
