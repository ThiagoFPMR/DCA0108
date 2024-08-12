#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H

#include "Process.h" // Include the header file for the Process struct

class ProcessQueue
{
public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~ProcessQueue() {}

    // Pure virtual function to add a process to the queue
    virtual void enqueue(const Process &process) = 0;

    // Pure virtual function to remove a process from the queue
    virtual Process dequeue() = 0;

    // Pure virtual function to check if the queue is empty
    virtual bool isEmpty() const = 0;
};

#endif // PROCESSQUEUE_H