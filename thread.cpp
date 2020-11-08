#include "thread.h"

void SThread::start() {
    this->thread = std::thread(&SThread::run,this);
}
void SThread::join() {
    this->thread.join();
}

SThread::SThread(SThread&& other){
  this->thread = std::move(other.thread);
}

void ThClient::run(){

}

void ThAceptador::run(){

}
