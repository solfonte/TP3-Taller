#include "server.h"
#include "parser.h"
#include "metodo.h"
#include <iostream>


void Server::recibir(){
  ssize_t bytes_recv = 0;
  bool termine = false, hubo_error = false;
  char buffer[20];
  size_t length = 20;
  while (!termine && !hubo_error){
    size_t tam_recv = length - (size_t)bytes_recv -1;
    ssize_t resultado_recv = this->peer.recibir(buffer,tam_recv);
    bytes_recv = resultado_recv;
    if (resultado_recv == -1){
      hubo_error = true;
        throw SocketException("Fallo el receive");
    }else if (resultado_recv == 0){
      termine = true;
    }else{
      if(resultado_recv < (ssize_t)length){
      }
      //buffer[resultado_recv] = '\n';
      this->petitorio.write(buffer,resultado_recv);
      std::cout.write (buffer,resultado_recv);
      bytes_recv = 0;
    }
  }
  Parser parser;
  Metodo* metodo = parser.run(this->petitorio);
  std::string rta = metodo->obtener_respuesta();
  std::cout << rta << "\n";
  delete metodo;
}

void Server::shutdown(){
  this->peer.cerrar_conexion(SHUT_RD);
  this->aceptador.cerrar_conexion(SHUT_RD);
}

void Server::run(){
  const char* servicio_aux = this->service.c_str();
  this->aceptador.bind_and_listen(INADDR_ANY,servicio_aux);
  //lanzo el thread acetador y ahi se llama al accept
  this->aceptador.aceptar(this->peer);
}
