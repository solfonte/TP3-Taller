#include "common_socket.h"
#include <cstring>
#include <iostream>
#define ERROR -1

Socket::Socket(Socket&& socket){
  this->fd = socket.fd;
  socket.fd = -1;
}

static void hints_innit(struct addrinfo* hints,
                        int ai_family,int ai_socktype,
                        int ai_flags){
  memset(hints,0,sizeof(struct addrinfo));
  hints->ai_family = ai_family;
  hints->ai_socktype = ai_socktype;
  hints->ai_flags = ai_flags;
}

Socket::Socket(){
  this->fd = -1;
}

void Socket::bind_and_listen(const char* host,const char* service){
  int val = 1;
  struct addrinfo hints;
  struct addrinfo* resultados;
  hints_innit(&hints,AF_INET,SOCK_STREAM,AI_PASSIVE);
  if (getaddrinfo(NULL,service, &hints,&resultados) < 0){
    throw SocketException("Fallo la obtencion de conexiones\n");//esta bien??
  }
  //capaz iterar
  int fd = socket(resultados->ai_family, resultados->ai_socktype,
                  resultados->ai_protocol);
  if (fd < 0){
    freeaddrinfo(resultados);
    throw SocketException("Fallo la creacion del socket\n");
  }
  this->fd = fd;
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
  int resultado_bind =  bind(this->fd, resultados->ai_addr,
                          resultados->ai_addrlen);
  freeaddrinfo(resultados);
  if (resultado_bind == ERROR){
    throw SocketException("No se pudo realizar el bind del socket\n");
  }
  int resultado_listen = listen(fd,15);
  if (resultado_listen < 0){
    throw SocketException("Fallo el listen del socket\n");
  }
}

void Socket::aceptar(Socket& peer)const {
  int fd = accept(this->fd, NULL, NULL);
  if (fd < 0){
    throw SocketException("No se pudo aceptar el peer\n");
  }
  peer.fd = fd;
}

Socket::~Socket(){
}
void Socket::cerrar(){
  if (this->fd > -1){
    close(this->fd);
  }
}

void Socket::recibir(std::stringstream& petitorio){
  ssize_t bytes_recv = 0;
  bool termine = false;
  char buffer[20];
  size_t length = 20;
  while (!termine){
    size_t tam_recv = length - (size_t)bytes_recv -1;
    ssize_t resultado_recv = recv(this->fd,buffer,tam_recv,0);
    bytes_recv = resultado_recv;
    if (resultado_recv == -1){
        throw SocketException("Fallo el receive");
    }else if (resultado_recv == 0){
      termine = true;
    }else{
      if (resultado_recv < (ssize_t)length){
      }
      petitorio.write(buffer,resultado_recv);
      bytes_recv = 0;
    }
  }
}

void Socket::conectar(const char* host,const char* service){
  bool conecte = false;
  struct addrinfo hints;
  struct addrinfo* resultados,*ptr;
  hints_innit(&hints,AF_INET,SOCK_STREAM,0);
  if (getaddrinfo(host,service, &hints,&resultados) < 0){
    throw SocketException("No se pudo obtener resultados\n");
  }
  ptr = resultados;
  int res_connect;
  while (ptr != NULL && !conecte){
    int fd = socket(resultados->ai_family, resultados->ai_socktype,
                    resultados->ai_protocol);
    this->fd = fd;
    if (fd != ERROR){
      res_connect = connect(fd,ptr->ai_addr,ptr->ai_addrlen);
      conecte = (res_connect != ERROR?true:false);
    }else{
      throw SocketException("Fallo la creacion del socket\n");
    }
    ptr = ptr->ai_next;
  }
  freeaddrinfo(resultados);
  if (!conecte){
    throw SocketException("Fallo la conexion del socket\n");
  }
}

void Socket::enviar(const char* buffer, size_t length){
  bool termine = false;
  ssize_t bytes_env = 0;
  while (!termine){
    size_t tam_enviar = length - (size_t)bytes_env;
    ssize_t res_env = send(this->fd,&buffer[bytes_env],
                      tam_enviar,MSG_NOSIGNAL);
    if (res_env == ERROR){
      throw SocketException("Hubo un error al enviar\n");
    }else if (res_env == 0){
      termine = true;
    }else{
      bytes_env += res_env;
    }
  }
}

void Socket::cerrar_conexion(int modo){
  if (this->fd > -1){
    shutdown(this->fd,modo);
  }
}
