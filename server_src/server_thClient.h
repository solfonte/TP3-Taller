#ifndef __THCLIENT_H__
#define __THCLIENT_H__
#include "server_thread.h"

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

#endif
