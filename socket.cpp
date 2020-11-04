#include "socket.h"
#include <cstring>
#include <iostream>
#define ERROR -1
/*
Socket::Socket(const std::string host,const std::string service){
  this->connect(host,service);
}*/

static void hints_innit(struct addrinfo* hints,
                        int ai_family,int ai_socktype,
                        int ai_flags){
  memset(hints,0,sizeof(struct addrinfo));
  hints->ai_family = ai_family;
  hints->ai_socktype = ai_socktype;
  hints->ai_flags = ai_flags;
}

Socket::Socket(const char* service){
  this->bind_and_listen(INADDR_ANY,service);
}
Socket::Socket(){

}

void Socket::bind_and_listen(const char* host,const char* service){
  int val = 1;
  struct addrinfo hints;
  struct addrinfo* resultados;
  hints_innit(&hints,AF_INET,SOCK_STREAM,AI_PASSIVE);
  if (getaddrinfo(NULL,service, &hints,&resultados) < 0){
    //lanzar exepcion de que fallo getaddrinfo
  }
  //capaz iterar
  int fd = socket(resultados->ai_family, resultados->ai_socktype, resultados->ai_protocol);
  if (fd < 0){
    freeaddrinfo(resultados);
    //excepcion
  }
  this->fd = fd;
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
  int resultado_bind =  bind(this->fd, resultados->ai_addr,resultados->ai_addrlen);
  freeaddrinfo(resultados);
  if (resultado_bind == ERROR){
    //excecion
  }
  int resultado_listen = listen(fd, 10);
  if (resultado_listen < 0){
    //excepcion
  }
}

int Socket::aceptar(){
  int fd = accept(this->fd, NULL, NULL);
  if (fd < 0){
    //throw exceotion
  }
  std::cout << "acpete" <<"\n";
  return fd;//ver si anda
}
Socket::Socket(const int file_descriptor){
  this->fd = file_descriptor;
}

Socket::~Socket(){

}

void Socket::recibir(){
  ssize_t bytes_recv = 0;
  bool termine = false, hubo_error = false;
  char buffer[20];
  size_t length = 20;
  while (!termine && !hubo_error){
    size_t tam_recv = length - (size_t)bytes_recv;
    ssize_t resultado_recv = recv(this->fd,buffer,tam_recv,0);
    bytes_recv = resultado_recv;
    std::cout << buffer <<"\n";
    if (resultado_recv == -1){
      hubo_error = true;
    }else if (resultado_recv == 0){
      termine = true;
    }else{
      bytes_recv = 0;
    }

  }
}
