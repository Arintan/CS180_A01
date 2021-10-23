#include <stdio.h>
#include <stdlib.h>
void FakeRR1() //Sauce: https://www.javatpoint.com/round-robin-program-in-c
{
    // initlialize the variable name  
    int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0, at[10], bt[10], temp[10];
    float avg_wt, avg_tat;
    printf(" Total number of process in the system: ");
    scanf("%d", &NOP);
    y = NOP; // Assign the number of process to variable y  

// Use for loop to enter the details of the process like Arrival time and the Burst Time  
    for (i = 0; i < NOP; i++)
    {
        printf("\n Enter the Arrival and Burst time of the Process[%d]\n", i + 1);
        printf(" Arrival time is: \t");  // Accept arrival time  
        scanf("%d", &at[i]);
        printf(" \nBurst time is: \t"); // Accept the Burst time  
        scanf("%d", &bt[i]);
        temp[i] = bt[i]; // store the burst time in temp array  
    }
    // Accept the Time qunat  
    printf("Enter the Time Quantum for the process: \t");
    scanf("%d", &quant);
    // Display the process No, burst time, Turn Around Time and the waiting time  
    printf("\n Process No \t\t Burst Time \t\t TAT \t\t Waiting Time ");
    for (sum = 0, i = 0; y != 0; )
    {
        if (temp[i] <= quant && temp[i] > 0) // define the conditions   
        {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if (temp[i] > 0)
        {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }
        if (temp[i] == 0 && count == 1)
        {
            y--; //decrement the process no.  
            printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);
            wt = wt + sum - at[i] - bt[i];
            tat = tat + sum - at[i];
            count = 0;
        }
        if (i == NOP - 1)
        {
            i = 0;
        }
        else if (at[i + 1] <= sum)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }
    // represents the average waiting time and Turn Around time  
    avg_wt = wt * 1.0 / NOP;
    avg_tat = tat * 1.0 / NOP;
    printf("\n Average Turn Around Time: \t%f", avg_wt);
    printf("\n Average Waiting Time: \t%f", avg_tat);
    getch();

}

void FakeRR2() //Sauce: https://www.edureka.co/blog/round-robin-scheduling-in-c/
{
    int i, limit, total = 0, x, counter = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10];
    float average_wait_time, average_turnaround_time;
    printf("nEnter Total Number of Processes:t");
    scanf("%d", &limit);
    x = limit;
    for (i = 0; i < limit; i++)
    {
        printf("nEnter Details of Process[%d]n", i + 1);

        printf("Arrival Time:t");

        scanf("%d", &arrival_time[i]);

        printf("Burst Time:t");

        scanf("%d", &burst_time[i]);

        temp[i] = burst_time[i];
    }

    printf("nEnter Time Quantum:t");
    scanf("%d", &time_quantum);
    printf("nProcess IDttBurst Timet Turnaround Timet Waiting Timen");
    for (total = 0, i = 0; x != 0;)
    {
        if (temp[i] <= time_quantum && temp[i] > 0)
        {
            total = total + temp[i];
            temp[i] = 0;
            counter = 1;
        }
        else if (temp[i] > 0)
        {
            temp[i] = temp[i] - time_quantum;
            total = total + time_quantum;
        }
        if (temp[i] == 0 && counter == 1)
        {
            x--;
            printf("nProcess[%d]tt%dtt %dttt %d", i + 1, burst_time[i], total - arrival_time[i], total - arrival_time[i] - burst_time[i]);
            wait_time = wait_time + total - arrival_time[i] - burst_time[i];
            turnaround_time = turnaround_time + total - arrival_time[i];
            counter = 0;
        }
        if (i == limit - 1)
        {
            i = 0;
        }
        else if (arrival_time[i + 1] <= total)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    average_wait_time = wait_time * 1.0 / limit;
    average_turnaround_time = turnaround_time * 1.0 / limit;
    printf("nnAverage Waiting Time:t%f", average_wait_time);
    printf("nAvg Turnaround Time:t%fn", average_turnaround_time);
    return 0;

}

void FakeSRTF()
{
    int a[10], b[10], x[10], i, j, smallest, count = 0, time, n;
    double avg = 0, tt = 0, end;
    printf("enter the number of Processes:\n");
    scanf("%d", &n);
    printf("enter arrival time\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("enter burst time\n");
    for (i = 0; i < n; i++)
        scanf("%d", &b[i]);
    for (i = 0; i < n; i++)
        x[i] = b[i];

    b[9] = 9999;

    for (time = 0; count != n; time++)
    {
        smallest = 9;
        for (i = 0; i < n; i++)
        {
            if (a[i] <= time && b[i] < b[smallest] && b[i]>0)
                smallest = i;
        }
        b[smallest]--;
        if (b[smallest] == 0)
        {
            count++;
            end = time + 1;
            avg = avg + end - a[smallest] - x[smallest];
            tt = tt + end - a[smallest];
        }
    }
    printf("\n\nAverage waiting time = %lf\n", avg / n);
    printf("Average Turnaround time = %lf", tt / n);
    return 0;
}

char* file()
{
	FILE* filepath;
	char filename[100] = "";
	printf("Please enter the Full Path of the file: \n");
	scanf_s("%s", &filename, (unsigned int)sizeof(filename));
	errno_t err = fopen_s(&filepath, filename, "r");
	if (filepath == NULL)
	{
		printf("%s " "File not found.", filename);
		exit(1);
	}
}

int main() 
{
	char filename[100] = file();
    //FakeRR1();
}