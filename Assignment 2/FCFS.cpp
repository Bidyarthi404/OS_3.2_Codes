#include<bits/stdc++.h>
using namespace std;
bool sortbysec(const pair<int, pair<int,int>> &a, const pair<int, pair<int,int>> &b)
{
    return (a.second.first < b.second.first);
}
int main()
{
    //Inputs
    int NumProcessor;
    cout<<"Enter the number of process: ";
    cin>>NumProcessor;

    int CpuTime[NumProcessor];
    int ArrivalTime[NumProcessor];
    vector<pair<int,int>>WaitingTime;
    vector<pair<int,int>>TurnaroundTime;

    cout<<"Enter the CPU times"<<endl;
    for(int i=0; i<NumProcessor; i++)
    {
        cin>>CpuTime[i];
    }
    cout<<"Enter the arrival times"<<endl;
    for(int i=0; i<NumProcessor; i++)
    {
        cin>>ArrivalTime[i];
    }

    vector<pair<int, pair<int,int>>>paul;
    for(int i=0; i<NumProcessor; i++)
    {
        paul.push_back(make_pair(i+1, make_pair(ArrivalTime[i],CpuTime[i])));
    }
    sort(paul.begin(), paul.end(), sortbysec);

    //waiting time for all processes
    int temp1, temp2;
    for(int i=0; i<NumProcessor; i++)
    {
        if(i==0)
        {
            WaitingTime.push_back(make_pair(paul[i].first,0));
        }
        else
        {
            WaitingTime.push_back(make_pair(paul[i].first, paul[i-1].second.second+WaitingTime[i-1].second+paul[i-1].second.first-paul[i].second.first));
            //WaitingTime.push_back(make_pair(paul[i].first, paul[i-1].second.second+WaitingTime[i-1].second-paul[i].second.first));
        }
    }

    //TurnAround Time for all processes
    for(int i=0; i<NumProcessor; i++)
    {
        TurnaroundTime.push_back(make_pair(paul[i].first, WaitingTime[i].second+paul[i].second.second));
    }

    //Average Waiting Time and Turnaround Time
    int TotalWaitingTime=0;
    int TotalTurnaroundTime=0;
    double AvgWaitingTime;
    double AvgTurnaroundTime;
    for(int i=0; i<NumProcessor; i++)
    {
        TotalTurnaroundTime+=TurnaroundTime[i].second;
        TotalWaitingTime+=WaitingTime[i].second;
    }
    AvgTurnaroundTime = (double)TotalTurnaroundTime/(double)NumProcessor;
    AvgWaitingTime = (double)TotalWaitingTime/(double)NumProcessor;

    sort(WaitingTime.begin(), WaitingTime.end());
    sort(TurnaroundTime.begin(), TurnaroundTime.end());

    //Lab manual sample Output
    for(int i=0; i<NumProcessor; i++)
    {
        cout<<"Process "<<WaitingTime[i].first<<": "<<"Waiting Time: "<<WaitingTime[i].second<<"   "<<"Turnaround Time: "<<TurnaroundTime[i].second<<endl;
    }
    cout<<endl<<"Average Waiting time: "<<AvgWaitingTime<<endl;
    cout<<"Average Turnaround time: "<<AvgTurnaroundTime<<endl;

    //Gantt chart output
    cout<<endl<<endl<<"GANTT CHART:"<<endl;
    for(int i=0; i<NumProcessor; i++)
    {
        cout<<"|----P"<<paul[i].first<<"----";
    }
    cout<<"|"<<endl;
    cout<<"0          ";
    int temp=paul[0].second.second;
    for(int i=0; i<NumProcessor; i++)
    {
        if(i==0)
        {
            cout<<temp<<"          ";
        }
        else
        {
            temp+=paul[i].second.second;
            cout<<temp<<"          ";
        }
    }

    return 0;
}


/*
3
5 7 9
4 0 2
*/

