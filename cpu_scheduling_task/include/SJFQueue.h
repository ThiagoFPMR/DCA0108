#ifndef SJFQUEUE_H
#define SJFQUEUE_H

#include <list>
#include "ProcessQueue.h" // Include the base class header

class SJFQueue : public ProcessQueue
{
public:
    // Constructor
    SJFQueue() = default;

    // Destructor
    ~SJFQueue() override = default;

    // Method to add a process to the queue
    void enqueue(const Process &process) override;

    // Method to remove a process from the queue
    Process dequeue() override;

    // Method to check if the queue is empty
    bool isEmpty() const override;

private:
    std::list<Process> list; // Linked list to store processes
};

#endif // SFJOQUEUE_H