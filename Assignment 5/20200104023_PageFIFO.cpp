#include<bits/stdc++.h>
using namespace std;

int FIFO_algo(int pRef, int refString[], int frame)
{
    int fault = 0;
    int pageFrames[frame], ref_no = 0,frame_no = 0;

    for (int i = 0; i < frame; i++)
    {
        pageFrames[i] = -1;
    }

    while (ref_no < pRef)
    {
        bool pageFault= false;
        for (int i = 0; i < frame; i++)
        {
            if (refString[ref_no] != pageFrames[i])
            {
                pageFault= true;
            }
            else
            {
                pageFault = false;
                break;
            }
        }
        if (pageFault)
        {
            cout<<refString[ref_no]<<" --> "<<pageFrames[frame_no] ;

            if(pageFrames[frame_no]!=-1)
            {
                cout<<"  Page fault";
            }
            cout<<endl;

            pageFrames[frame_no] = refString[ref_no];
            fault++;
            frame_no++;
            if (frame_no == frame)
            {
                frame_no = 0;
            }
        }
        ref_no++;

    }
    return fault;
}

void faultRate(int fault, int pRef)
{
    int rate = round( (double)fault/ pRef*100);
    cout << "Page Fault Rate: " << rate << " %" << endl;
}

int main()
{
    int page,pRef,frame,fifo;
    cout << "Number of pages: ";
    cin >> page;
    cout << "Number of page References: ";
    cin >> pRef;
    cout << "Reference String: ";
    int refString[pRef];
    for (int i = 0; i < pRef; i++)
    {
        cin >> refString[i];
    }
    cout << "Number of Memory  Frame: ";
    cin >> frame;

    fifo = FIFO_algo(pRef, refString, frame);

    cout << "Number of page fault using FIFO Page replacement Algorithm: " << fifo << endl;
    faultRate(fifo, pRef);

    return 0;
}


/*
6
22
7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1
3
*/
