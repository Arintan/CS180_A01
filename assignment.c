#include <stdio.h>
#include <stdlib.h>

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
    int timeQuantum = 0, remainingProcesses = _numOfProcesses, waitTime[200] = { 0 }, remainBurstTime[200] = { 0 };
    float maxTurnaroundTime = 0.0f, avgTurnaroundTime = 0.0f, maxWaitingTime = 0.0f, avgWaitingTime = 0.0f;

    printf("Please enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    for (int i = 0; i < _numOfProcesses; ++i)
        remainBurstTime[i] = _burstTime[i];

    for (int i = 0, time = 0; remainingProcesses != 0;)
    {
        if (_arrivalTime[i] <= time)
        {
            if (remainBurstTime[i] == 0)
                ++i;
            else if (remainBurstTime[i] <= timeQuantum)
            {
                time += remainBurstTime[i];
                remainBurstTime[i] = 0;
                waitTime[i] = time - _burstTime[i];
                --remainingProcesses;
                ++i;
            }
            else if (remainBurstTime[i] > timeQuantum)
            {
                remainBurstTime[i] -= timeQuantum;
                time += timeQuantum;
                ++i;
            }

            if (i >= _numOfProcesses)
                i = 0;
        }
        else
        {
            --i;
            //check if i is out of bound and if remaining burst time is 0
            if (i > -1 && remainBurstTime[i] == 0)
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
    int timeQuantum = 0, remainingProcesses = _numOfProcesses, pivotPoint = -1, waitTime[200] = { 0 }, remainBurstTime[200] = { 0 };
    float maxTurnaroundTime = 0.0f, avgTurnaroundTime = 0.0f, maxWaitingTime = 0.0f, avgWaitingTime = 0.0f;

    printf("Please enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    for (int i = 0; i < _numOfProcesses; ++i)
        remainBurstTime[i] = _burstTime[i];

    for (int i = 0, time = 0; remainingProcesses != 0;)
    {
        if (_arrivalTime[i] <= time)
        {
            if (remainBurstTime[i] == 0)
                ++i;
            else if (remainBurstTime[i] <= timeQuantum)
            {
                time += remainBurstTime[i];
                remainBurstTime[i] = 0;
                waitTime[i] = time - _burstTime[i];
                --remainingProcesses;
                ++i;
            }
            else if (remainBurstTime[i] > timeQuantum)
            {
                remainBurstTime[i] -= timeQuantum;
                time += timeQuantum;
                pivotPoint = i;
                ++i;
            }

            if (pivotPoint > -1 && i < _numOfProcesses && remainBurstTime[pivotPoint] <= remainBurstTime[i])
            {
                i = pivotPoint;
                pivotPoint = -1;
            }

            if (i >= _numOfProcesses)
                i = 0;
        }
        else
        {
            --i;
            //check if i is out of bound and if remaining burst time is 0
            if (i > -1 && remainBurstTime[i] == 0)
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

FILE* fileOpen()
{
	FILE* filepath;
	char filename[200] = "";
	printf("Please enter the Full Path of the file: \n");
	scanf("%s", filename);
	filepath = fopen(filename, "r");
	if (filepath == NULL)
	{
		printf("%s " "File not found.", filename);
		exit(EXIT_FAILURE);
	}
    return filepath;
}

int main()
{
    FILE* file = fileOpen();

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
    SRTF(arrivalTime, burstTime, priorityLevel, numOfProcesses);

    return 0;
}
