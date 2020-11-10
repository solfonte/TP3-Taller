#include "server_thread.h"

void Thread::start() {
    this->thread = std::thread(&Thread::run,this);
}

void Thread::join() {
    thread.join();
}

Thread::Thread(Thread&& other){
  this->thread = std::move(other.thread);
}
