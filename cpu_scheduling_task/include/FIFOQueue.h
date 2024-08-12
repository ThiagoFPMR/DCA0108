#ifndef FIFOQUEUE_H
#define FIFOQUEUE_H

#include <queue>
#include "ProcessQueue.h" // Include the base class header

class FIFOQueue : public ProcessQueue
{
public:
    // Constructor
    FIFOQueue() = default;

    // Destructor
    ~FIFOQueue() override = default;

    // Method to add a process to the queue
    void enqueue(const Process &process) override;

    // Method to remove a process from the queue
    Process dequeue() override;

    // Method to check if the queue is empty
    bool isEmpty() const override;

private:
    std::queue<Process> queue; // Queue to store processes
};

#endif // FIFOQUEUE_H