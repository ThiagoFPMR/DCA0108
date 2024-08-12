#ifndef PROCESS_H
#define PROCESS_H

struct Process
{
    int pid;
    int burstTime;   // in ms
    int arrivalTime; // in ms
};

#endif // PROCESS_H