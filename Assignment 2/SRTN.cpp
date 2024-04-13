#include<bits/stdc++.h>
using namespace std;

int main() {
    int numProcesses;
    cout << "Enter the number of process: ";
    cin >> numProcesses;

    vector<int> burstTime(numProcesses);
    vector<int> arrivalTime(numProcesses);
    vector<int> remainingTime(numProcesses, 0);
    vector<int> waitingTime(numProcesses, 0);
    vector<int> turnaroundTime(numProcesses, 0);
    vector<bool> completed(numProcesses, false);
    int currentTime = 0;
    int completedProcesses = 0;


    // Input burst times
    cout << "Enter the burst times:" << endl;
    for (int i = 0; i < numProcesses; i++) {
        cin >> burstTime[i];
        remainingTime[i] = burstTime[i];
    }

    // Input arrival times
    cout << "Enter the arrival times:" << endl;
    for (int i = 0; i < numProcesses; i++) {
        cin >> arrivalTime[i];
    }
    //for Gantt chart
    vector<pair<int,int>>gantt;
    int temp=0;
    while (completedProcesses < numProcesses)
    {
        int shortestJob = -1;
        int shortestTime = INT_MAX;

        // Find the process with the shortest remaining time at the current time
        for (int i = 0; i < numProcesses; i++) {
            if (!completed[i] && arrivalTime[i] <= currentTime && remainingTime[i] < shortestTime) {
                shortestTime = remainingTime[i];
                shortestJob = i;
            }
        }

        if (shortestJob == -1) {
            currentTime++;
        } else {
            remainingTime[shortestJob]--;

            if (remainingTime[shortestJob] == 0) {
                completedProcesses++;
                completed[shortestJob] = true;
                int completionTime = currentTime + 1;
                turnaroundTime[shortestJob] = completionTime - arrivalTime[shortestJob];
                waitingTime[shortestJob] = turnaroundTime[shortestJob] - burstTime[shortestJob];
            }

            currentTime++;
            gantt.push_back(make_pair(++temp, shortestJob+1));
        }
    }
    // Calculate average waiting time and turnaround time
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    for (int i = 0; i < numProcesses; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }
    double avgWaitingTime = totalWaitingTime / numProcesses;
    double avgTurnaroundTime = totalTurnaroundTime / numProcesses;

    // Print the results
    cout<<endl;
    for (int i = 0; i < numProcesses; i++) {
        cout <<"Process "<<i + 1<<":    "<<"Waiting time: "<<waitingTime[i]<<"    Turnaround time: "<<turnaroundTime[i]<< endl;
    }
    cout <<endl<< "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;

    cout << endl << "Gantt Chart:" << endl;
    vector<pair<int, pair<int, int>>>paul;
    int i=0;
    while(i<gantt.size())
    {
        int c = 1;
        for(int j=i+1; j<gantt.size();j++)
        {
            if(gantt[i].second==gantt[j].second)
            {
                c++;
            }
            else
            {
                break;
            }
        }
        if(i==0)
        {
            paul.push_back(make_pair(0, make_pair(gantt[i].second, c)));
        }
        else
        {
            paul.push_back(make_pair(i, make_pair(gantt[i].second, c)));
        }
        i+=c;
    }

    //gant chart output
    for(int i=0;i<paul.size();i++)
    {
        cout<<"|---P"<<paul[i].second.first<<"---|";
    }
    cout<<endl;
    for(int i=0;i<paul.size();i++)
    {
        if(i==(paul.size()-1))
        {
            cout<<paul[i].first<<"        "<<paul[i].second.second+paul[i].first;
        }
        else
        {
            cout<<paul[i].first<<"        ";
        }
    }

    return 0;
}
