#ifndef __THCLIENT_H__
#define __THCLIENT_H__
#include "server_thread.h"
#include <utility>
#include <string>

class ThClient: public Thread{
  private:
    Socket peer;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;
    Recursos_protegidos& recursos;
    void run() override;

  public:
    ThClient(Socket peer,Recursos_protegidos& recursos):
    peer(std::move(peer)),
    keep_talking(true),
    is_running(true),
    recursos(recursos)
      {}
    bool is_dead();
    void stop();
    void operator()() override;
};

#endif
