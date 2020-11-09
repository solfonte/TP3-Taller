#ifndef __THREAD_H__
#define __THREAD_H__
#include <thread>
#include "socket.h"
#include <atomic>
#include <vector>
#include "recursos_protegidos.h"
#include <mutex>

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
    std::mutex &m;
  public:
    ThClient(Socket peer,Recursos_protegidos* recursos,std::mutex &m):
    peer(std::move(peer)),
    keep_talking(true),
    is_running(true),
    recursos(recursos),
    m(m)
      {}
    void run() override;
    void stop();
};

class ThAceptador: public Thread{
  private:
    Socket* aceptador;
    std::vector<ThClient*> clientes;
    Recursos_protegidos* recursos;
    std::mutex &m;
  public:
    ThAceptador(Socket* aceptador,Recursos_protegidos* recursos,std::mutex &m):
    aceptador(aceptador),
    recursos(recursos),
    m(m)
      {}
    void run() override;
};

#endif
