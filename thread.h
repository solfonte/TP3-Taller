#ifndef __THREAD_H__
#define __THREAD_H__
#include <thread>
#include "socket.h"
#include <atomic>
#include <vector>
#include "recursos_protegidos.h"


class Thread{
  private:
    std::thread thread;
  public:
    Thread () {}
    void start();
    virtual void run() = 0;
    virtual ~Thread() {}
    void join();
    Thread(Thread&& other);
    Thread& operator=(const Thread&) = delete;
    Thread(const Thread&) = delete;
};

class ThClient: public Thread{
  private:
    Socket peer;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;
    Recursos_protegidos* recursos;
    Socket& get_peer();
  public:
    Socket& getpeer();
    ThClient(Socket peer,Recursos_protegidos* recursos):
    peer(std::move(peer)),
    recursos(recursos)
      {}
    void run() override;
    void stop();
};

class ThAceptador: public Thread{
  private:
    Socket* aceptador;
    std::vector<ThClient*>* clientes;//capaz referencia al vector
    Recursos_protegidos* recursos;
  public:
    ThAceptador(std::vector<ThClient*>* clientes,Socket* aceptador,Recursos_protegidos* recursos):
    aceptador(aceptador),
    clientes(clientes),
    recursos(recursos)
      {}
    void run() override;
};

#endif
