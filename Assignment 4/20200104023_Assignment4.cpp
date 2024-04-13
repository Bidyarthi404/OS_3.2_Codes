#include<bits/stdc++.h>
using namespace std;
int n, cycle = 1;

int getIndex(char nodeArr[], char c)
{
    int nodeIndex;
    for (int i = 0; i < n; i++)
    {
        if (nodeArr[i] == c)
            nodeIndex = i;
    }
    return nodeIndex;
}

void printStack(stack<int> stack, char nodes[], int index)
{
    int k = 0;
    char nameArr[n];
    while (!stack.empty())
    {
        nameArr[k] = nodes[stack.top()];
        k++;
        stack.pop();
        if (nameArr[k - 1] == nodes[index])
            break;
    }
    cout << cycle << " - Deadlock Detected Among nodes: ";
    for (int i = k - 1; i >= 0; i--)
        cout << nameArr[i] << " ";
    cout << endl;
    cycle++;
}

int main()
{
    cout << "Enter number of nodes: ";
    cin >> n;
    int graph[n][n], visited[n];
    char nodeName[n];

    cout << "Node names: ";
    for (int i = 0; i < n; i++)
    {
        cin >> nodeName[i];
        visited[i] = -1;
    }

    //graph initilaize
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    //Edges input until double enter is pressed
    cout << "Edges: ";
    string line;
    cin.ignore();
    getline(cin, line);
    while (line[0] != '\0')
    {
        graph[getIndex(nodeName, line[0])][getIndex(nodeName, line.back())] = 1;
        line = "";
        getline(cin, line);
    }

    cout<<"Output: "<<endl;

    //Comment out codes to print the matrix of the graph
    /*for (int i = 0; i < n; i++)
    {
        cout << "\t" << nodeName[i];
    }
    cout<<endl;
    for (int i = 0; i < n; i++)
    {
        cout << nodeName[i];
        for (int j = 0; j < n; j++)
            cout << "\t" << graph[i][j];
        cout << endl;
    }*/

    stack<int> st;

    for (int node = 0; node < n; node++)
    {
        st.push(node);
        while (!st.empty())
        {
            node = st.top();
            if (visited[node] == 1)
            {
                st.pop();
            }
            if (visited[node] != 1)
            {
                for (int i = 0; i < n; i++)
                {
                    if (graph[node][i] && visited[i] == -1)
                    {
                        visited[node] = 0;
                        st.push(i);
                        break;
                    }
                    else if (graph[node][i] && visited[i] == 0)
                    {
                        visited[node] = 0;
                        for (int j = 0; j < n; j++)
                        {
                            if (graph[i][j] && visited[j] != 1)
                            {
                                visited[i] = 0;
                            }
                            else
                                visited[i] = 1;
                        }
                        printStack(st, nodeName, i);
                    }
                    else
                    {
                        visited[node] = 1;
                    }
                }
            }
        }
    }
    cout << endl;
}
