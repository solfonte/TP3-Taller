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

#endif
