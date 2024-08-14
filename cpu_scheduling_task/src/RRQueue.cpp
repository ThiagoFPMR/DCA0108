#include "../include/RRQueue.h"

// Constructor
RRQueue::RRQueue(const int quantum) : quantum(quantum) {}

// Method to add a process to the queue
void RRQueue::enqueue(const Process &process)
{
    list.push_back(process);
    if (list.size() == 1)
    {
        currentProcess = list.begin();
    }
}

// Method to remove a process from the queue
Process RRQueue::dequeue()
{
    if (list.empty())
    {
        throw std::runtime_error("Queue is empty");
    }

    Process process = *currentProcess;

    // Update process queue and process what to return
    if (process.burstTime > quantum)
    {
        currentProcess->burstTime -= quantum;
        process.pid = -1;
        process.burstTime = quantum;
        currentProcess++;
    }
    else
    {
        currentProcess = list.erase(currentProcess);
    }

    // Circular queue behavior
    if (currentProcess == list.end())
    {
        currentProcess = list.begin();
    }

    return process;
}

// Method to check if the queue is empty
bool RRQueue::isEmpty() const
{
    return list.empty();
}