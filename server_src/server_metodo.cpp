#include "server_metodo.h"
#include <fstream>
#include <iostream>
#include <sstream>

PostSinRecurso::PostSinRecurso(){
}

std::string GetSinRecurso::obtener_respuesta(){
  std::string respuesta = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
  std::ifstream fs;
  fs.open(this->archivo);
  if(!fs){
    respuesta += "ERROR: no se pudo abrir el archivo" + this->archivo + "\n";
  }else{
    std::string contenido;
    while (getline(fs,contenido,'\n')){
      respuesta += contenido;
    }
    fs.close();
  }
  return respuesta;
}

std::string GetConRecurso::obtener_respuesta(){
  std::string respuesta;
  if (this->recurso_existe){
    respuesta = "HTTP/1.1 200 OK \n\n" + this->contenido_recurso;
  }else{
    respuesta = "HTTP/1.1 404 NOT FOUND\n\n";
  }
  return respuesta;
}

std::string PostSinRecurso::obtener_respuesta(){
  std::string respuesta = "HTTP/1.1 403 FORBIDDEN\n\n";
  return respuesta;
}

std::string PostConRecurso::obtener_respuesta(){
  std::string respuesta = "HTTP/1.1 200 OK \n\n" + this->body;
  return respuesta;
}

std::string MetodoInvalido::obtener_respuesta(){
  std::string respuesta = "HTTP/1.1 405 METHOD NOT ALLOWED\n\n" +
                          this->metodo_invalido + "es un comando desconocido\n";
  return respuesta;
}
