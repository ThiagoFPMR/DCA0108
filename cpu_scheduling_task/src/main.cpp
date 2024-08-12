#include <iostream>
#include <fstream>
#include <string>

#include "../include/ProcessQueue.h"
#include "../include/FIFOQueue.h"
#include "../include/SJFQueue.h"

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
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    int numProcesses = 0, totalWaitTime = 0;

    FIFOQueue processQueue;
    populateQueue(argv[1], processQueue);

    int currentTime = 0;
    while (!processQueue.isEmpty())
    {
        Process p = processQueue.dequeue();

        std::cout << "Process " << p.pid << " waited " << currentTime - p.arrivalTime << " seconds" << std::endl;

        currentTime += p.burstTime;
        totalWaitTime += currentTime - p.arrivalTime;
        numProcesses++;
    }

    std::cout << "Average waiting time: " << totalWaitTime / numProcesses << " seconds" << std::endl;

    return 0;
}