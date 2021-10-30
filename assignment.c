/*!*****************************************************************************
\file assignment.c
\author Tan Wei Jie, Heng Zeng Le, Tan Chor Yeong, Jiang Chuqiao
\par DP email: weijie.tan\@digipen.edu, h.zengle\@digipen.edu, 
                choryeong.tan\@digipen.edu, c.jiang\@digipen.edu
\par Course: CS180/CSD2180
\par Project Assignment 1
\date 10-30-2021
\brief
This file contains functions that performs the logic for the proposed
RRR algorithm
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*!*****************************************************************************
\brief
    This function inserts an integer to the end of an array
\param queue
    The array to insert into
\param end
    A variable that keeps track of the current end index of the array
\param num
    An integer value to insert into the array
*******************************************************************************/
void queueInsert(int* queue, int* end, int num)
{
    queue[*end] = num;
    ++(*end);
}

/*!*****************************************************************************
\brief
    This function inserts an integer to the start of an array
\param queue
    The array to insert into
\param end
    A variable that keeps track of the current end index of the array
\param num
    An integer value to insert into the array
*******************************************************************************/
void queuePushFront(int* queue, int* end, int num)
{
    ++(*end);
    for (int i = *end - 1; i > 0; --i)
        queue[i] = queue[i - 1];
    queue[0] = num;
}

/*!*****************************************************************************
\brief
    This function "pop off" the value at the front of the array and 
    moves the subsequent values one position forward
\param queue
    The array to "pop" the value from
\param end
    A variable that keeps track of the current end index of the array
\return
    Returns the value at the front of the array
*******************************************************************************/
int queueTop(int* queue, int* end)
{
    if (*end > 0)
    {
        int num = queue[0];
        for (int i = 0; i < *end - 1; ++i)
            queue[i] = queue[i + 1];
        --(*end);
        return num;
    }
    return -1;
}

/*!*****************************************************************************
\brief
    This function contains the logic of the RRR algorithm based off of the
    principles of the Round Robin Scheduling algorithm
\param _arrivalTime
    The array that contains the arrival time of all the processes
\param _burstTime
    The array that contains the burst time of all the processes
\param _priorityLevel
    The array that contains the priority level of all the processes
\param _numOfProcesses
    An integer specifying the total number of processes
*******************************************************************************/
void RRR(int* _arrivalTime, int* _burstTime, int* _priorityLevel, int _numOfProcesses)
{
    int timeQuantum = 0, remainingProcesses = _numOfProcesses, end = 0, index = 0, time = 0, pivotPoint = -1,
        waitTime[200] = { 0 }, remainBurstTime[200] = { 0 }, queue[200] = { 0 }, arrivalflag[200] = { 0 };

    float maxTurnaroundTime = 0.0f, avgTurnaroundTime = 0.0f, maxWaitingTime = 0.0f, avgWaitingTime = 0.0f;

    printf("Please enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    for (int i = 0; i < _numOfProcesses; ++i)
        remainBurstTime[i] = _burstTime[i];

    queueInsert(queue, &end, 0);
    arrivalflag[0] = 1;

    while (remainingProcesses != 0)
    {

        index = queueTop(queue, &end);

        if (index > -1 && remainBurstTime[index] <= timeQuantum)
        {
            time += remainBurstTime[index];
            remainBurstTime[index] = 0;
            waitTime[index] = time - _arrivalTime[index] - _burstTime[index];
            --remainingProcesses;
        }
        else if (index > -1 && remainBurstTime[index] > timeQuantum)
        {
            remainBurstTime[index] -= timeQuantum;
            time += timeQuantum;
            pivotPoint = index;
        }

        for (int i = 0; i < _numOfProcesses; ++i)
        {
            if (arrivalflag[i] == 0 && _arrivalTime[i] <= time)
            {
                queueInsert(queue, &end, i);
                arrivalflag[i] = 1;
            }
        }

        if (pivotPoint > -1 && remainBurstTime[pivotPoint] <= remainBurstTime[queue[0]])
        {
            queuePushFront(queue, &end, pivotPoint);
            pivotPoint = -1;
            continue;
        }

        if (index > -1 && remainBurstTime[index] != 0)
        {
            queueInsert(queue, &end, index);
        }

        if (end <= 0)
        {
            ++time;
        }
    }

    for (int i = 0; i < _numOfProcesses; ++i)
    {
        maxWaitingTime += waitTime[i];
        maxTurnaroundTime += _burstTime[i] + waitTime[i];
    }

    avgWaitingTime = maxWaitingTime / _numOfProcesses;
    avgTurnaroundTime = maxTurnaroundTime / _numOfProcesses;

    printf("average turnaround time: %.2f\n", avgTurnaroundTime);
    printf("maximum turnaround time: %.2f\n", maxTurnaroundTime);
    printf("average waiting time: %.2f\n", avgWaitingTime);
    printf("maximum waiting time: %.2f\n", maxWaitingTime);
}

/*!*****************************************************************************
\brief
    This function opens a file specified through a command line input
\param argv
    This is the name of the file to be opened
\return 
    Returns the file to be opened
*******************************************************************************/
FILE* fileOpen(char** argv)
{
	FILE* filepath;
	filepath = fopen(argv[1], "r");
	if (filepath == NULL)
	{
		printf("%s " "File not found.\n", argv[1]);
		exit(EXIT_FAILURE);
	}
    return filepath;
}

int main(int argc, char** argv)
{
    FILE* file = fileOpen(argv);

    int arrivalTime[200], burstTime[200], priorityLevel[200], numOfProcesses = 0;
    int i = 0;
    while (fscanf(file, "%d %d %d", &arrivalTime[i], &burstTime[i], &priorityLevel[i]) != EOF)
    {
        ++i;
    }
    fclose(file);
    arrivalTime[i] = burstTime[i] = priorityLevel[i] = '0';
    numOfProcesses = i;
   
    RRR(arrivalTime, burstTime, priorityLevel, numOfProcesses);

    return 0;
}
