#include "../include/FIFOQueue.h"

// Method to add a process to the queue
void FIFOQueue::enqueue(const Process &process)
{
    queue.push(process);
}

// Method to remove a process from the queue
Process FIFOQueue::dequeue()
{
    if (queue.empty())
    {
        throw std::runtime_error("Queue is empty");
    }
    Process process = queue.front();
    queue.pop();
    return process;
}

// Method to check if the queue is empty
bool FIFOQueue::isEmpty() const
{
    return queue.empty();
}