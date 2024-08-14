#ifndef RRQUEUE_H
#define RRQUEUE_H

#include <list>
#include "ProcessQueue.h" // Include the base class header

class RRQueue : public ProcessQueue
{
public:
    // Constructor
    RRQueue(int quantum);

    // Destructor
    ~RRQueue() override = default;

    // Method to add a process to the queue
    void enqueue(const Process &process) override;

    // Method to remove a process from the queue
    Process dequeue() override;

    // Method to check if the queue is empty
    bool isEmpty() const override;

private:
    int quantum;                                 // Quantum for the Round Robin algorithm
    std::list<Process> list;                     // Linked list to store processes
    std::list<Process>::iterator currentProcess; // Iterator to the current process
};

#endif // RRQUEUE_H