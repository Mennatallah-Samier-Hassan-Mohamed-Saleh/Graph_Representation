/**
 * @author Mennatallah Saleh
 * @version 1.0
 * This code is to read adjacency graph format into CSR format
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;
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
    /* Create an input file stream object named 'file' and
        open the file "slashdot.adj".
    */
    ifstream file("slashdot.adj");

    /*String to store each line of the file.*/
    string line;

    /*Temporaray vector to read the file*/
    vector<string> temp;

    /*Adding Padding element to match line number with vectore index */
    temp.push_back("Zero");

    /*Reading the file*/
    if (file.is_open())
    {

        /*Read each line from the file and store it in the 'line' variable.*/
        while (getline(file, line))
        {
            /*Store the line in the temp vector*/
            temp.push_back(line);
        }

        /*Close the file stream once all lines have been read.*/
        file.close();
    }
    else
    {
        /*Print an error if the file can't be openned*/
        cerr << "Unable to open file!" << endl;
    }

    cout << "Size of the file is: " << temp.size() << endl;
    /*Defining number of nodes*/
    int n = stoi(temp[2]);
    /*Defining number of edges*/
    int m = stoi(temp[3]);

    /*Defining the offsets array*/
    int ptr[n + 1];
    int ptrStart = 4;
    int ptrSize = sizeof(ptr) / sizeof(int);

    /*Defining the indices array*/
    int ind[m];
    int indStart = ptrStart + n;
    int indSize = sizeof(ind) / sizeof(int);

    /*Filling the offsets array*/
    for (int i = 0; i < n; i++)
    {
        ptr[i] = stoi(temp[i + ptrStart]);
    }
    /*The last element should be the total number of edges */
    ptr[n] = m;
    
    //cout << "Size of the ptr array is: " << ptrSize << endl;
    //cout << "Printing the ptr array: " << endl;
    //for (int i = 0; i < ptrSize; i++)
    //{
       // cout << ptr[i] << endl;
     //}

    //Filling and printing the indices array
    //cout << "Size of the indices array is: " << indSize << endl;
    //cout << "Printing the indices array: " << endl;
    for (int i = 0; i < m; i++)
    {
        ind[i] = stoi(temp[i + indStart]);
        //cout << ind[i] << endl;
    }
    
    /*Running BFS Tree*/
    bfsTree(n, 1, ptr, ind);
    return 0;
}