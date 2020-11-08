#ifndef __THREAD_H__
#define __THREAD_H__
#include <thread>
#include "socket.h"

class SThread{
  private:
    std::thread thread;
    Socket socket;
  public:
    SThread () {}
    void start();
    virtual void run() = 0;
    virtual ~SThread() {}
    void join();
    SThread(SThread&& other);
    SThread& operator=(const SThread&) = delete;
    SThread(const SThread&) = delete;
};

class ThClient: public SThread{
  /*private:
    Socket client;*/
  public:
    ThClient(){}
    void run() override;
};

class ThAceptador: public SThread{
  /*private:
    Socket aceptador;*/
  public:
    ThAceptador(){}
    void run() override;
};

#endif
