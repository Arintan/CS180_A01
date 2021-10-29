#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void queueInsert(int* queue, int* end, int num)
{
    queue[*end] = num;
    ++(*end);
}

void queuePushFront(int* queue, int* end, int num)
{
    ++(*end);
    for (int i = *end - 1; i > 0; --i)
        queue[i] = queue[i - 1];
    queue[0] = num;
}

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

void SRTF(int* arrivalTime, int* burstTime, int* priorityLevel, int _numOfProcesseses)
{
    int temp[200] = { 0 }, time, count = 0, shortest, numofProcesses = _numOfProcesseses;
    double turnaboutTime = 0.0, avgWaitingTime = 0.0, end;
    for (int i = 0; burstTime[i] != '0'; ++i)
    {
        temp[i] = burstTime[i];
        numofProcesses = i + 1;
    }
    for (time = 0; count != numofProcesses; time++)
    {
        shortest = numofProcesses;
        for (int i = 0; i < numofProcesses; i++)
        {
            if (arrivalTime[i] <= time && burstTime[i] < burstTime[shortest] && burstTime[i]>0)
                shortest = i;
        }
        burstTime[shortest]--;
        if (burstTime[shortest] == 0)
        {
            count++;
            end = (double)time + 1;
            avgWaitingTime = avgWaitingTime + end - arrivalTime[shortest] - temp[shortest];
            turnaboutTime = turnaboutTime + end - arrivalTime[shortest];
        }
    }
    printf("\n\nAverage waiting time = %lf\n", avgWaitingTime / numofProcesses);
    printf("Average Turnaround time = %lf\n", turnaboutTime / numofProcesses);
}

void RRAlgorithm(int* _arrivalTime, int* _burstTime, int* _priorityLevel, int _numOfProcesses)
{
    int timeQuantum = 0, remainingProcesses = _numOfProcesses, end = 0, index = 0, time = 0,
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
        else if(index > -1 && remainBurstTime[index] > timeQuantum)
        {
            remainBurstTime[index] -= timeQuantum;
            time += timeQuantum;
        }

        for (int i = 0; i < _numOfProcesses; ++i)
        {
            if (arrivalflag[i] == 0 && _arrivalTime[i] <= time)
            {
                queueInsert(queue, &end, i);
                arrivalflag[i] = 1;
            }
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

void RRRF(int* _arrivalTime, int* _burstTime, int* _priorityLevel, int _numOfProcesses)
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

FILE* fileOpen(char** argv)
{
	FILE* filepath;
	filepath = fopen(argv[1], "r");
	if (filepath == NULL)
	{
		printf("%s " "File not found.", argv[1]);
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
   
    RRAlgorithm(arrivalTime, burstTime, priorityLevel, numOfProcesses);
    RRRF(arrivalTime, burstTime, priorityLevel, numOfProcesses);
    //SRTF(arrivalTime, burstTime, priorityLevel, numOfProcesses);

    return 0;
}
