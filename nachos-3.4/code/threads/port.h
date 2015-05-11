// port.h

#ifndef PORT_H
#define PORT_H

#include "copyright.h"
#include "thread.h"
#include "list.h"
#include "synch.h"

// The following class defines a "communication port" between two threads.
// In a port these conditions are held:
//     1. The thread trying to receive a message from a port will
//     wait until a sender is ready to send.
//     2. The thread trying to send a message to a port will wait
//     until there is a receiver ready to receive.
//     3. If there are multiple senders and receivers at
//     a given moment only two thread at a time can access
//     to the port.

class Port {
 public:
    Port(const char* debugName);    // initialize a port
    ~Port();                        // de-allocate a port

    const char* getName() { return (name); }

    void Send(int message);          // put a message to the buffer
    void Receive(int* message);      // read from the buffer and write it
                                     // on the given address

 private:
    const char* name;                // port name
    Lock* lock;                      // enforce mutual exclusive access to the port
    Condition* readyToSend;          // wait if there isn't receiver
    Condition* readyToReceive;       // wait if there isn't sender
    List<int>* buffer;               // the unsynchronized buffer
};

#endif // PORT_H
