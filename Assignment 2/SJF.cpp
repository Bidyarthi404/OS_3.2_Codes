#include <bits/stdc++.h>
using namespace std;

struct process
{
    int ArrivalWait;
    int status;
    int processNo;
    int CpuTime;
    int ArrivalTime;
    int EndTime;
    int TurnAround; // TurnAround=EndTime-ArrivalTime
    int WaitingTime;  // WaitingTime=TurnAround-CpuTime
};

bool sortByArrivalWait(process &a, process &b)
{
    return a.ArrivalWait < b.ArrivalWait;
}

int main()
{
    //Inputs
    int n;
    int completed = 0;
    int ganttProgress = 0;
    float avg_TAT = 0, avg_WT = 0;
    cout << "Enter the number of Processes : ";
    cin >> n;
    cout << endl;
    process p[n];

    cout << "Enter CPU time : " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].CpuTime;
        p[i].processNo = i + 1;
        p[i].status = 0;
    }

    cout << "Enter arrival time : " << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> p[i].ArrivalTime;
    }

    //Calculations
   while(completed!=n)
   {
    int min_index=-1;
    int minimum=INT_MAX;
    for(int i=0;i<n;i++)
    {
        if(p[i].ArrivalTime<=ganttProgress&&p[i].status==0)
        {
            if(p[i].CpuTime<minimum)
            {
                minimum=p[i].CpuTime;
                min_index=i;
            }

        if(p[i].CpuTime==minimum)
        {
            if(p[i].ArrivalTime<p[min_index].ArrivalTime)
            {
                minimum=p[i].CpuTime;
                min_index=i;
            }
        }
        }
    }
    if(min_index!=-1)
    {
        ganttProgress+=p[min_index].CpuTime;
        completed++;
        p[min_index].EndTime=ganttProgress;
        p[min_index].status=1;
    }
    else
    {
        ganttProgress++;
    }
   }

   //Calculating TurnAround
    for(int i=0;i<n;i++)
    {
        p[i].TurnAround=p[i].EndTime-p[i].ArrivalTime;
        avg_TAT+=p[i].TurnAround;
    }
    avg_TAT=avg_TAT/n;
    //Calculating WaitingTime
    for(int i=0;i<n;i++)
    {
        p[i].WaitingTime=p[i].TurnAround-p[i].CpuTime;
        avg_WT+=p[i].WaitingTime;
    }
    avg_WT=avg_WT/n;

    for(int i =0;i<n;i++)
    {
        cout << "Process " << p[i].processNo <<" : Waiting Time : "<<p[i].WaitingTime << " TurnAround Time : "<< p[i].TurnAround << endl;
         p[i].ArrivalWait = p[i].ArrivalTime + p[i].WaitingTime;
    }
    cout <<endl<< "Average Waiting time : "<< avg_WT << endl;
    cout << "Average Turnaround time : "<< avg_TAT << endl;


    //Gantt Chart output
    cout <<endl<< "Gantt Chart : " <<endl;

    sort(&p[0], &p[n], sortByArrivalWait);
    cout << "\n|";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].CpuTime - 1; j++)
            cout << "-";
        cout << "p" << p[i].processNo;
        for (int j = 0; j < p[i].CpuTime - 1; j++)
            cout << "-";
        cout << "|";
        //If there is any ideal time between process
        if (p[i].EndTime != p[i + 1].ArrivalWait && i + 1 < n)
        {
            for (int j = 0; j < (p[i + 1].ArrivalWait - p[i].EndTime) - 1; j++)
            {
                cout << "-";
            }
            cout << "|";
        }
    }
    cout << endl;

    int prev_print = 0;
    cout << p[0].ArrivalWait;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].CpuTime; j++)
        {
            cout << "  ";
        }
        cout << p[i].EndTime;
        if (p[i].EndTime != p[i + 1].ArrivalWait && i + 1 < n)
        {
            for (int j = 0; j < (p[i + 1].ArrivalWait - p[i].EndTime) - 1; j++)
            {
                cout << " ";
            }
            cout << p[i+1].ArrivalWait;
        }
    }
    return 0;
}
