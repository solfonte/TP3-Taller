#include "server_thread.h"
#include "server_metodo.h"
#include <iostream>
#include "server_parser.h"
#include "server_lock.h"

void Thread::start() {
    this->thread = std::thread(&Thread::run,this);
}

void Thread::join() {
    thread.join();
}

Thread::Thread(Thread&& other){
  this->thread = std::move(other.thread);
}

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

void ThAceptador::operator()(){
  this->start();
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
  this->is_running = false;
}

void ThClient::stop(){
  this->keep_talking = false;
  this->peer.cerrar_conexion(SHUT_RD);
  this->peer.cerrar_conexion(SHUT_WR);
  this->peer.cerrar();
}

void ThAceptador::remover_hilos_finalizados(){
  int cantidad_clientes = this->clientes.size();
  for (int i = 0; i < cantidad_clientes; i++){
    if (this->clientes[i]->is_dead()){
      this->clientes[i]->join();
      delete this->clientes[i];
      this->clientes.erase(this->clientes.begin() + i);
      cantidad_clientes --;
    }
  }
}

void ThAceptador::detener_clientes(){
  int cantidad_clientes = this->clientes.size();
  for (int i = 0; i < cantidad_clientes; i++){
    this->clientes[i]->join();
    this->clientes[i]->stop();
    delete this->clientes[i];
    this->clientes.erase(this->clientes.begin() + i);
    cantidad_clientes --;
  }
}

void ThAceptador::run(){
  bool seguir_aceptando = true;
  while (seguir_aceptando){
    //int cantidad_clientes;
    Socket peer = Socket();
    try{
      this->aceptador->aceptar(peer);
      ThClient* cliente = new ThClient(std::move(peer),this->recursos,this->m);
      this->clientes.push_back(cliente);
      (*cliente)();
    }catch(const SocketException& se){
      seguir_aceptando = false;
    }
    this->remover_hilos_finalizados();
  }
  this->detener_clientes();
}
bool ThClient::is_dead(){
  return !this->is_running;
}
