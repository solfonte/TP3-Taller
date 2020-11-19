#include "client.h"
#include <iostream>

void Client::run(){
  const char* host_aux = host.c_str();
  const char* service_aux = service.c_str();
  this->client.conectar(host_aux,service_aux);
}

void Client::enviar(){
  std::string petitorio = " ";
  while (getline(std::cin,petitorio,'\n') && !std::cin.eof()){
    if (petitorio.size() != 0){
      petitorio.push_back('\n');
      this->client.enviar(petitorio.c_str(),petitorio.size());
    }
  }
  this->client.cerrar_conexion(SHUT_WR);
}

void Client::recibir(){
  char buffer[20];
  size_t length = 20;
  ssize_t cant_recibido;
  std::stringstream respuesta;
  do{
    cant_recibido = this->client.recibir(buffer,length);
    respuesta.write(buffer,cant_recibido);
  }while (cant_recibido > 0);
  std::string rta = respuesta.str();
  std::cout << rta;
  this->client.cerrar();
}
