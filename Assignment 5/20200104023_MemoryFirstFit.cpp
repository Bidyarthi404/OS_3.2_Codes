#include<bits/stdc++.h>
using namespace std;

void First_Fit(int memory_hole_size[], int total_holes, int memory_request_size[], int total_requests)
{
    int flag=0;
    int sum=0;
    int allocation[total_requests];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i <total_requests; i++)
    {
        for (int j = 0; j < total_holes; j++)
        {
            if (memory_hole_size[j]  >= memory_request_size[i])
            {
                allocation[i] = j;
                memory_hole_size[j] =memory_hole_size[j] - memory_request_size[i];
                cout<<"Memory left in Block "<<j+1<<" after assigning the process "<<i+1<<" :";
                cout<<memory_hole_size[j]<<endl;
                break;
            }

        }

    }
    cout<<"Memory Allocation Step by Step:"<<endl;
    cout << "\nRequest No.\tRequest Size\tHole no.\n";
    for (int i = 0; i <total_requests; i++)
    {
        cout << " " << i+1 << "\t\t" << memory_request_size[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
        {
            flag=1;
            cout << "Can't be allocated";
            for(int i=0; i<total_holes; i++)
            {
                sum=sum+memory_hole_size[i];
            }
        }
        cout << endl;
    }
    if(sum==0)
    {
        cout << endl;
        cout << "No External Fragmentation "<< endl;
    }
    if (flag==1)
    {
        cout<<endl;
        cout<<"External Fragmentation " <<sum<<endl;
    }
}
int main()
{

    int memory_hole_size[] = {50,200,70,115,15};

    int memory_request_size[] = {100,10,35,15,23,6,25,55,88,40};

    int total_holes = 5;

    int    total_requests = 10;
    cout<<"*****First Fit*****"<<endl<<endl;
    First_Fit(memory_hole_size, total_holes, memory_request_size,total_requests);
    return 0 ;
}
