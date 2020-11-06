#include "client.h"
#include <iostream>
#include <sstream>

void Client::run(){
  const char* host_aux = host.c_str();
  const char* service_aux = service.c_str();
  this->client.conectar(host_aux,service_aux);
}

void Client::enviar(){
  std::string linea;
  while(std::getline(std::cin,linea,'\n')){
    if (linea.size() != 0){
      std::cout << "hola\n";
    }
  }
}
