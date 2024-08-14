#include <iostream>
#include <fstream>
#include <string>

#include "../include/ProcessQueue.h"
#include "../include/FIFOQueue.h"
#include "../include/SJFQueue.h"
#include "../include/RRQueue.h"

void populateQueue(const std::string &filename, ProcessQueue &processQueue)
{
    std::ifstream file(filename); // Open the file

    if (file.is_open())
    {
        int id, duration;
        while (file >> id >> duration) // Read data from the file
        {
            Process p = {id, duration, 0};
            processQueue.enqueue(p); // Add the process to the queue
        }
        file.close(); // Close the file
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main(int argc, char **argv)
{
    if (argc < 3 || (std::string(argv[1]) == "RR" && argc < 4))
    {
        std::cerr << "Usage: " << argv[0] << " <scheduling_algorihtm> [quantum] <filename>" << std::endl;
        return 1;
    }
    int numProcesses = 0, totalWaitTime = 0;

    std::string algorithm = argv[1];
    ProcessQueue *processQueue = nullptr;

    if (algorithm == "FIFO")
    {
        processQueue = new FIFOQueue();
    }
    else if (algorithm == "SJF")
    {
        processQueue = new SJFQueue();
    }
    else if (algorithm == "RR")
    {
        int quantum = std::stoi(argv[2]);
        processQueue = new RRQueue(quantum);
    }
    else
    {
        std::cerr << "Invalid scheduling algorithm: " << algorithm << std::endl;
        return 1;
    }
    std::cout << "Scheduling algorithm: " << algorithm << std::endl;

    populateQueue(argv[argc - 1], *processQueue);

    int currentTime = 0;
    while (!processQueue->isEmpty())
    {
        Process p = processQueue->dequeue();

        if (p.pid != -1)
        {
            totalWaitTime += currentTime - p.arrivalTime;
            // std::cout << "Process " << p.pid << " waited " << currentTime - p.arrivalTime << " ms" << std::endl;
            numProcesses++;
        }

        currentTime += p.burstTime;
    }

    delete processQueue;

    std::cout << "Average waiting time: " << totalWaitTime / numProcesses << " ms" << std::endl;

    return 0;
}