#define CANTIDAD_ARGUMENTOS_CLIENT 3
#define POSICION_SERVICE 2
#define POSICION_HOST 1
#include <iostream>
#include "client.h"

static bool validar_argumentos(int argc, char** argv,std::string &host,
                              std::string &service){
  if (argc != CANTIDAD_ARGUMENTOS_CLIENT){
    return false;
  }else{
    host = argv[POSICION_HOST];
    service = argv[POSICION_SERVICE];
    return true;
  }
}

int main(int argc, char** argv) {
  std::string host,service;
  if (!validar_argumentos(argc,argv,host,service)){
    std::cout << "La cantidad de argumentos es incorrecta\n";
    return 0;
  }
  Client cliente = Client(host,service);
  try{
    cliente.run();
  }catch(const SocketException& se){
    std::cout << se.getError();
    return 0;
  }
  cliente.enviar();
  cliente.recibir();
  return 0;
}
