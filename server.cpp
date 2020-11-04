#include "server.h"
#include <iostream>

Server::Server(const std::string& service,const std::string& root_file){
  this->puerto = service;
  this->root_file = root_file;
  const char* serv_aux = service.c_str();
  this->aceptador = Socket(serv_aux);
  this->peer = Socket(this->aceptador.aceptar());
}
void Server::recibir(){
  this->peer.recibir();
}
