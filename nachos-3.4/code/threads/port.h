#ifndef PORT_H
#define PORT_H

#include "copyright.h"
#include "thread.h"
#include "list.h"
#include "synch.h"

class Port {
 public:
  Port(const char* debugName);

  ~Port();

  const char* getName() { return (name); }

  void Send(int message);
  void Receive(int* message);

 private:
  const char* name;
  Lock* lock;
  Condition* readyToSend;
  Condition* readyToReceive;
  List<int>* buffer;
};

#endif // PORT_H
