#include "../include/SJFQueue.h"

// Method to add a process to the queue
void SJFQueue::enqueue(const Process &process)
{
    if (list.empty())
    {
        list.push_back(process);
    }
    else
    {
        auto it = list.begin();
        while (it != list.end() && it->burstTime < process.burstTime)
        {
            it++;
        }
        list.insert(it, process);
    }
}

// Method to remove a process from the queue
Process SJFQueue::dequeue()
{
    if (list.empty())
    {
        throw std::runtime_error("Queue is empty");
    }
    Process process = list.front();
    list.pop_front();
    return process;
}

// Method to check if the queue is empty
bool SJFQueue::isEmpty() const
{
    return list.empty();
}