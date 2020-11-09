#define CANTIDAD_ARGUMENTOS_SERVER 3
#define POSICION_ROOT_FILE 2
#define POSICION_SERVICE 1
#include <string>
#include "server.h"
#include <iostream>

bool validar_argumentos(int argc, char** argv,std::string &puerto,std::string &root_file){
  if(argc != CANTIDAD_ARGUMENTOS_SERVER){
    return false;
  }else{
    puerto = argv[POSICION_SERVICE];
    root_file = argv[POSICION_ROOT_FILE];
    return true;
  }
}

int main(int argc, char** argv) {
  std::string puerto,root_file;
  std::mutex m;
  if (!validar_argumentos(argc,argv,puerto,root_file)){
    std::cout << "La cantidad de argumentos es incorrecta\n";
    return 1;
  }
  Server server = Server(puerto,root_file,m);
  try{
    server.run();
  }catch(const SocketException& se){
    std::cout << se.getError() <<"\n";
  }
  char c;
  while((c = std::cin.get()) != 'q'){
  }
  server.shutdown();
  //aceptador.join, capaz adentro del server shutdown
  return 0;
}
