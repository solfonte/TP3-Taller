#ifndef __THREAD_H__
#define __THREAD_H__
#include <thread>
#include "../common_src/common_socket.h"
#include <atomic>
#include <vector>
#include "server_recursos_protegidos.h"
#include <mutex>
#include <utility>
#include <string>

class Thread{
  private:
    std::thread thread;
  protected:
    void start();
    virtual void run() = 0;
  public:
    Thread() {}
    virtual ~Thread() {}
    void join();
    Thread(Thread&& other);
    Thread& operator=(const Thread&) = delete;
    Thread(const Thread&) = delete;
    virtual void operator()() = 0;
};

class ThClient: public Thread{
  private:
    Socket peer;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;
    Recursos_protegidos* recursos;
    std::mutex &m;
    void run() override;

  public:
    ThClient(Socket peer,Recursos_protegidos* recursos,std::mutex &m):
    peer(std::move(peer)),
    keep_talking(true),
    is_running(true),
    recursos(recursos),
    m(m)
      {}
    bool is_dead();
    void stop();
    void operator()() override;
};

class ThAceptador: public Thread{
  private:
    Socket* aceptador;
    std::vector<ThClient*> clientes;
    Recursos_protegidos* recursos;
    std::mutex &m;
    void run() override;

  public:
    ThAceptador(Socket* aceptador,Recursos_protegidos* recursos,std::mutex &m):
    aceptador(aceptador),
    recursos(recursos),
    m(m)
      {}
    void operator()() override;
};

#endif
