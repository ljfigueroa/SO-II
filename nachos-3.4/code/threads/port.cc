#include "copyright.h"
#include "synch.h"
#include "system.h"
#include "port.h"

Port::Port(const char* debugName)
{
  name = debugName;
  buffer = new List<int>;
  lock = new Lock("shared lock");
  readyToReceive = new Condition("ReadyToReceive", lock);
  readyToSend = new Condition("ReadyToSend", lock);
  
}

Port::~Port()
{
  delete lock;
  delete buffer;
  delete readyToReceive;
  delete readyToSend;
}

void Port::Send(int message)
{
  lock->Acquire();
  buffer->Append(message);
  readyToSend->Signal();
  readyToReceive->Wait();
  lock->Release();
}

void Port::Receive(int *message)
{
  lock->Acquire();
  while (buffer->IsEmpty())
    readyToSend->Wait();
  *message = buffer->Remove();
  readyToReceive->Signal();
  lock->Release();
}
