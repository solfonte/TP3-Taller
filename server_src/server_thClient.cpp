#include "server_thClient.h"
#include "server_parser.h"
#include "server_lock.h"
#include <iostream>
#include "server_metodo.h"

static std::string crear_primer_linea(const std::string& petitorio){
  int pos = petitorio.find('\n');
  std::string primer_linea = petitorio;
  if (pos > -1){
    primer_linea = petitorio.substr(0,pos);
  }
  return primer_linea;
}
void ThClient::operator()(){
  this->start();
}

void ThClient::recibir(std::stringstream& petitorio){
  char buffer[20];
  size_t length = 20;
  ssize_t cant_recibido;
  do{
    cant_recibido = this->peer.recibir(buffer,length);
    petitorio.write(buffer,cant_recibido);
  }while (cant_recibido > 0);
}

void ThClient::run(){
  std::stringstream petitorio;
  this->recibir(petitorio);
  this->peer.cerrar_conexion(SHUT_RD);
  std::string primer_linea_petitorio = crear_primer_linea(petitorio.str());
  primer_linea_petitorio += "\n";
  std::cout << primer_linea_petitorio;
  Parser parser;
  Metodo* metodo = parser.run(this->recursos,petitorio.str());
  std::string rta = metodo->obtener_respuesta();
  this->peer.enviar(rta.c_str(),rta.size());
  this->peer.cerrar_conexion(SHUT_WR);
  this->peer.cerrar();
  delete metodo;
  this->is_running = false;
}

void ThClient::stop(){
  this->keep_talking = false;
  this->peer.cerrar_conexion(SHUT_RDWR);
  this->peer.cerrar();
}

bool ThClient::is_dead(){
  return !this->is_running;
}
