#include "thread.h"
#include "metodo.h"
#include <iostream>
#include "parser.h"
#include "lock.h"

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
  //Lock(&this->m);
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
  this->is_running = false;
}

void ThClient::stop(){
  this->keep_talking = false;
  this->peer.cerrar_conexion(SHUT_RD);//a cheqyear
  this->peer.cerrar_conexion(SHUT_WR);
  this->peer.cerrar();
}

//capaz juntar shutdown con close
void ThAceptador::run(){
/*  Socket peer = Socket();
  this->aceptador->aceptar(peer);
  ThClient* cliente = new ThClient(std::move(peer),this->recursos,this->m);
  this->clientes.push_back(cliente);
  cliente->start();
  cliente->join();
  cliente->stop();
  delete cliente;*/

  bool seguir_aceptando = true;
  int cantidad_clientes;
  while (seguir_aceptando){
    Socket peer = Socket();
    try{
      this->aceptador->aceptar(peer);
      ThClient* cliente = new ThClient(std::move(peer),this->recursos,this->m);
      this->clientes.push_back(cliente);
      cliente->start();
    }catch(const SocketException& se){
      seguir_aceptando = false;
    }
    cantidad_clientes = this->clientes.size();
    for (int i = 0; i < cantidad_clientes; i++){
      if (this->clientes[i]->is_dead()){
        this->clientes[i]->join();
        delete this->clientes[i];//cambiar a lista
        this->clientes.erase(this->clientes.begin() + i);
        cantidad_clientes --;
      }
    }
    cantidad_clientes = this->clientes.size();
    for (int i = 0; i < cantidad_clientes; i++){
      this->clientes[i]->join();
      this->clientes[i]->stop();
      delete this->clientes[i];//cambiar a lista
      this->clientes.erase(this->clientes.begin() + i);
      cantidad_clientes --;
    }
  }
}
bool ThClient::is_dead(){
  return !this->is_running;

}
