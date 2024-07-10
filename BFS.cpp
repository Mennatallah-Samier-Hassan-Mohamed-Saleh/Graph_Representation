/**
 * @author Mennatallah Saleh
 * @version 1.0
 * This code is to read a graph frpm CSR format to BFS Tree array
 */
#include <iostream>

using namespace std;

void bfsTree(int n, int source, int *Offsets, int *Edges)
{
    // Array of parents
    // n : nodes we have
    int *parent = (int *)malloc(sizeof(int) * n);

    // Array of active vetrices which we are currently visiting
    // Maximum length is n
    int *queue = (int *)malloc(sizeof(int) * n);

    // Initialize the array with -1 which means unvisisted.
    for (int i = 0; i < n; i++)
    {
        parent[i] = -1;
    }

    // Set the head of the queue to the source vetrex which we get from function signature
    queue[0] = source;

    // Parent of the source vertex equal the source vetrex
    //  This is a special case as not of others wiill have themseleves as parent.
    //  As if we set the source to visited
    parent[source] = source;

    // How long is the queue right now.
    int q_front = 0, q_back = 1;

    // until the queue is empty we are going to look only at the front of the queue
    // And add all the neighbors of whatever was in the front the have not yet been visited

    // Assume the graph is in CSR: offsets and edges array with no weights
    // We have n vertices and m edges
    // As long as the queue is not empty q_front != q_back
    //  1- Dequeue the element at the front of the queue
    //  2- Look at the degree which tell us how long do we need to iterate over
    // while queue not empty
    while (q_front != q_back)
    {
        // Dequeue what is currently in the queue
        // queue[q_front++] is post increment so as it is follows:
        //  int current = queue[q_front];
        //  q_front++;
        int current = queue[q_front]; // dequeue
        q_front++;
        // Look at the degree which tell us how long do we need to iterate over
        //  in CSR degree is coming from subtract the offset to your right to your offset
        int degree = Offsets[current + 1] - Offsets[current];
        // Iterate over all the neighbors of this vertex who is currently active
        for (int i = 0; i < degree; i++)
        {
            // Edges array is the neighbor array
            // Offsets[current] + i : is the currrent index
            // So we look from the start till the end of a neighbor list in CSR
            int ngh = Edges[Offsets[current] + i];
            // check if neighbor has been visited
            if (parent[ngh] == -1)
            {
                // Add the unvisited neighbor to the queue
                parent[ngh] = current;
                // enqueue neighbor
                // queue[q_back++] is post increment so as it is follows:
                // queue[q_back] =ngh;
                // q_back++;
                queue[q_back] = ngh;
                q_back++;
            }
        }
    }
    cout << "Printing indices of the vertices" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << queue[i] << " ";
    }
    cout << endl;
    cout << "Printing the Parent Array" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << parent[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n = 5;
    int source = 0;
    int Offsets[6] = {0, 2, 2, 5, 7, 9};
    int Edges[9] = {1, 2, 1, 3, 4, 2, 4, 0, 1};
    bfsTree(n, 0, Offsets, Edges);
    return 0;
}