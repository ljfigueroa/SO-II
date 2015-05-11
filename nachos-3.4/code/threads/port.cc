#include "copyright.h"
#include "synch.h"
#include "system.h"
#include "port.h"

//----------------------------------------------------------------------
// Port::Port
//	Allocate and initialize the data structures needed for a
//	port, empty to start with.
//	Messages can now be transmitted through the port.
//----------------------------------------------------------------------

Port::Port(const char* debugName)
{
    name = debugName;
    buffer = new List<int>;
    lock = new Lock("shared lock");
    readyToReceive = new Condition("ReadyToReceive", lock);
    readyToSend = new Condition("ReadyToSend", lock);
}

//----------------------------------------------------------------------
// Port::~Port
//      De-allocate the data structures created for the communication
//      through the port.
//----------------------------------------------------------------------

Port::~Port()
{
    delete lock;
    delete buffer;
    delete readyToReceive;
    delete readyToSend;
}

//----------------------------------------------------------------------
// Port::Send
//      Put a message in the buffer. Wake up anyone
//      waiting for an message to be ready and waits until a
//      receiver informs that the buffer was read.
//----------------------------------------------------------------------

void Port::Send(int message)
{
    lock->Acquire();
    buffer->Append(message);
    readyToSend->Signal();
    readyToReceive->Wait();
    lock->Release();
}

//----------------------------------------------------------------------
// Port::Receive
//      Remove the message from the buffer and informs about it to
//      the sender and copies the message to the given address.
//      Wait if the buffer is empty until is woken up from a sender
//      and there is a message in the buffer.
//----------------------------------------------------------------------

void Port::Receive(int *message)
{
    lock->Acquire();
    while (buffer->IsEmpty())
        readyToSend->Wait();
    *message = buffer->Remove();
    readyToReceive->Signal();
    lock->Release();
}
