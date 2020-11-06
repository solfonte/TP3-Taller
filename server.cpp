#include "server.h"
#include <iostream>


void Server::recibir(){
  //char* buffer_aux =
  this->peer.recibir(/*this->buffer*/);
  //parseo
  //envio en otro metodo
}

void Server::run(){
  const char* servicio_aux = this->service.c_str();
  this->aceptador.bind_and_listen(INADDR_ANY,servicio_aux);
  //lanzo el thread acetador y ahi se llama al accept
  this->aceptador.aceptar(this->peer);
}
