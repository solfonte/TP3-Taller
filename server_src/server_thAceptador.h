#ifndef __THACEPTADOR_H__
#define __THACEPTADOR_H__
#include "server_thread.h"
#include "server_thClient.h"
#include <utility>
#include <vector>

class ThAceptador: public Thread{
  private:
    Socket& aceptador;
    std::vector<ThClient*> clientes;
    Recursos_protegidos& recursos;
    void run() override;

  public:
    ThAceptador(Socket& aceptador,Recursos_protegidos& recursos):
    aceptador(aceptador),
    recursos(recursos)
      {}
    void operator()() override;
    void remover_hilos_finalizados();
    void detener_clientes();
};

#endif
