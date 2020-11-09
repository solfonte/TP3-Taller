#include "thread.h"
#include "metodo.h"
#include <iostream>
#include "parser.h"

void Thread::start() {
    this->thread = std::thread(&Thread::run,this);
}
void Thread::join() {
    thread.join();
}

Thread::Thread(Thread&& other){
  this->thread = std::move(other.thread);
}

std::string crear_primer_linea(const std::string& petitorio){
  int pos = petitorio.find('\n');
  std::string primer_linea = petitorio;
  if (pos > -1){
    primer_linea = petitorio.substr(0,pos);
  }
  return primer_linea;
}

void ThClient::run(){
  std::stringstream petitorio;
  this->peer.recibir(petitorio);
  this->peer.cerrar_conexion(SHUT_RD);
  std::string primer_linea_petitorio = crear_primer_linea(petitorio.str());
  std::cout << primer_linea_petitorio << "\n";
  Parser parser;
  Metodo* metodo = parser.run(this->recursos,petitorio.str());
  std::string rta = metodo->obtener_respuesta();
  this->peer.enviar(rta.c_str(),rta.size());
  delete metodo;
}

void ThClient::stop(){
  this->keep_talking = false;
  this->peer.cerrar_conexion(SHUT_RD);//a cheqyear
  this->peer.cerrar_conexion(SHUT_WR);
  this->peer.cerrar();
}

//capaz juntar shutdown con close
void ThAceptador::run(){
  Socket peer = Socket();
  this->aceptador->aceptar(peer);
  ThClient* cliente = new ThClient(std::move(peer),this->recursos,this->m);
  this->clientes.push_back(cliente);
  cliente->start();
  cliente->join();
  cliente->stop();
  delete cliente;
}
