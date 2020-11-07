#include "metodo.h"
#include <fstream>
#include <iostream>
#include <sstream>

/*
GetSinRecurso::GetSinRecurso(){

}*/

Metodo::Metodo(){

}

GetConRecurso::GetConRecurso(){

}

PostSinRecurso::PostSinRecurso(){

}

PostConRecurso::PostConRecurso(){

}

MetodoInvalido::MetodoInvalido(){

}

std::string GetSinRecurso::obtener_respuesta(){
  std::string respuesta = "HTTP 200 OK\nContent-Type: text/html\n\n";
  std::ifstream fs;
  fs.open(this->archivo);
  std::cout << this->archivo;
  std::string contenido;
  while(getline(fs,contenido,'\n')){
    respuesta += contenido;
  }
  fs.close();
  return respuesta;

}

std::string GetConRecurso::obtener_respuesta(){
  std::string respuesta = "get con recurso";
  return respuesta;
}

std::string PostSinRecurso::obtener_respuesta(){
  std::string respuesta = "post sin recurso";
  return respuesta;
}

std::string PostConRecurso::obtener_respuesta(){
  std::string respuesta = "post con recurso";
  return respuesta;
}

std::string MetodoInvalido::obtener_respuesta(){
  std::string respuesta = "invalido";
  return respuesta;
}
