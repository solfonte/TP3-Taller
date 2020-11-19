#include "server_thAceptador.h"

void ThAceptador::operator()(){
  this->start();
}

void ThAceptador::remover_hilos_finalizados(){
  int cantidad_clientes = this->clientes.size();
  std::vector<ThClient*> clientes_filtrados;
  for (int i = 0; i < cantidad_clientes; i++){
    if (this->clientes[i]->is_dead()){
      this->clientes[i]->join();
      delete this->clientes[i];
    }else{
      clientes_filtrados.push_back(this->clientes[i]);
    }
  }
  this->clientes.swap(clientes_filtrados);
}

void ThAceptador::detener_clientes(){
  int cantidad_clientes = this->clientes.size();
  for (int i = 0; i < cantidad_clientes; i++){
    this->clientes[i]->stop();
    this->clientes[i]->join();
    delete this->clientes[i];
  }
}

void ThAceptador::run(){
  bool seguir_aceptando = true;
  while (seguir_aceptando){
    Socket peer = Socket();
    try{
      this->aceptador.aceptar(peer);
      ThClient* cliente = new ThClient(std::move(peer),this->recursos);
      this->clientes.push_back(cliente);
      (*cliente)();
    }catch(const SocketException& se){
      seguir_aceptando = false;
    }
    this->remover_hilos_finalizados();
  }
  this->detener_clientes();
}
