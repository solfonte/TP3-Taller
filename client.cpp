#include "client.h"
#include <iostream>
#include <sstream>

void Client::run(){
  const char* host_aux = host.c_str();
  const char* service_aux = service.c_str();
  this->client.conectar(host_aux,service_aux);
}

void Client::enviar(){
  std::string petitorio = " ";
  while (getline(std::cin,petitorio,'\n') && petitorio.size() != 0){
    if(petitorio.size() != 0){
      petitorio.push_back('\n');
      this->client.enviar(petitorio.c_str(),petitorio.size());
    }
  }
  this->client.cerrar_conexion(SHUT_WR);
}
