using namespace std;
/**
 * @author Mennatallah Saleh
 * @version 1.0
 *          This class is an example of a Graph
 */
#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

Graph::Graph(string Name)
{
    this->fileName = Name;
    this->numOfNodes = 1;
    this->numOfEdges = 1;
}

void Graph::convertToCSR(string OutName)
{
    /* Create an input file stream object
    from the graph constructr
    */
    ifstream file(this->fileName);

    /* Create an output file stream object
    named OutName from the function parameter"
    */
    ofstream MyFile(OutName);

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

    /*Defining number of nodes*/
    this->numOfNodes = stoi(temp[2]);

    /*Defining number of edges*/
    this->numOfEdges = stoi(temp[3]);

    /*Defining the offsets array*/
    int ptr[numOfNodes + 1];
    int ptrStart = 4;
    int ptrSize = sizeof(ptr) / sizeof(int);

    /*Defining the indices array*/
    int ind[numOfEdges];
    int indStart = ptrStart + numOfNodes;
    int indSize = sizeof(ind) / sizeof(int);

    /*Filling the offsets array*/
    for (int i = 0; i < numOfNodes; i++)
    {
        ptr[i] = stoi(temp[i + ptrStart]);
    }
    /*The last element should be the total number of edges */
    ptr[numOfNodes] = numOfEdges;

    cout << "Size of the ptr array is: " << ptrSize << endl;
    MyFile << "Size of the ptr array is: " << ptrSize << endl;
    cout << "Printing the ptr array: " << endl;
    MyFile << "Printing the ptr array: " << endl;
    for (int i = 0; i < ptrSize; i++)
    {
        cout << ptr[i] << endl;
        MyFile << ptr[i] << endl;
    }

    /*Filling and printing the indices array*/
    cout << "Size of the indices array is: " << indSize << endl;
    MyFile << "Size of the indices array is: " << indSize << endl;
    cout << "Printing the indices array: " << endl;
    MyFile << "Printing the indices array: " << endl;
    for (int i = 0; i < numOfEdges; i++)
    {
        ind[i] = stoi(temp[i + indStart]);
        cout << ind[i] << endl;
        MyFile << ind[i] << endl;
    }
    this->Offsets = ptr;
    this->Edges = ind;
}

void Graph::bfsTree(int source)
{

    // Array of parents
    // n : nodes we have
    int *parent = (int *)malloc(sizeof(int) * numOfNodes);

    // Array of active vetrices which we are currently visiting
    // Maximum length is n
    int *queue = (int *)malloc(sizeof(int) * numOfNodes);

    // Initialize the array with -1 which means unvisisted.
    for (int i = 0; i < numOfNodes; i++)
    {
        parent[i] = -1;
    }

    // Set the head of the queue to the source vetrex which we get from function signature
    queue[0] = source;

    // Parent of the source vertex equal the source vetrex
    //  This is a special case as not of others will have themseleves as parent.
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
    cout << "Starting q_front: " << q_front << endl;
    cout << "Starting q_back: " << q_back << endl;
    cout << "Initial queue is: " << endl;
    for (int i = 0; i < numOfNodes; ++i)
    {
        cout << queue[i] << " ";
    }
    cout << endl;
    while (q_front != q_back)
    {
        // Dequeue what is currently in the queue
        // queue[q_front++] is post increment so as it is follows:
        //  int current = queue[q_front];
        //  q_front++;

        int current = queue[q_front]; // dequeue
        cout << "Working on vertex : " << current << endl;
        ;
        q_front++;
        cout << "Updating q_front to: " << q_front << endl;
        // Look at the degree which tell us how long do we need to iterate over
        //  in CSR degree is coming from subtract the offset to your right to your offset
        int degree = Offsets[current + 1] - Offsets[current];
        cout << "Degree for vetrex: " << current << " is: " << degree << endl;
        // Iterate over all the neighbors of this vertex who is currently active
        for (int i = 0; i < degree; i++)
        {
            cout << "Processing edge: " << i << " for element:" << current << endl;
            // Edges array is the neighbor array
            // Offsets[current] + i : is the currrent index
            // So we look from the start till the end of a neighbor list in CSR
            int ngh = Edges[Offsets[current] + i];

            cout << "Neighbor is: " << ngh << endl;
            // check if neighbor has't been visited
            if (parent[ngh] == -1)
            {
                // Add the unvisited neighbor to the queue

                parent[ngh] = current;
                cout << "Parent of: " << ngh << " is: " << current << endl;
                // enqueue neighbor
                // queue[q_back++] is post increment so as it is follows:
                // queue[q_back] =ngh;
                // q_back++;
                queue[q_back] = ngh;
                cout << "new queue is: " << endl;
                for (int i = 0; i < numOfNodes; ++i)
                {
                    cout << queue[i] << " ";
                }
                cout << endl;
                q_back++;
            }
            else
            {
                cout << "Neighbor: " << ngh << " is already visisted" << endl;
            }
        }
    }
    cout << "Printing indices of the vertices" << endl;
    for (int i = 0; i < numOfNodes; i++)
    {
        cout << queue[i] << " ";
    }
    cout << endl;
    cout << "Printing the Parent Array" << endl;
    for (int i = 0; i < numOfNodes; i++)
    {
        cout << parent[i] << " ";
    }
    cout << endl;
}

void Graph::abjacencyMatrix()
{
    this->Matrix = new int *[this->numOfNodes];
    int degree;
    /*Calculate the column index*/
    int col;
    /*A counter for the index of Edges array*/
    int counter = 0;
    /*Initializing the array with zeros*/
    for (int i = 0; i < this->numOfNodes; ++i)
    {
        this->Matrix[i] = new int[this->numOfNodes];
        for (int j = 0; j < this->numOfNodes; j++)
        {
            Matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < numOfNodes; ++i)
    {
        degree = Offsets[i + 1] - Offsets[i];
        for (int j = 0; j < degree; j++)
        {
            /*Getting the Edge and use it as a column for the array*/
            col = Edges[counter];
            Matrix[i][col] = 1;
            /*Update the index of Edges array*/
            counter++;
        }
    }
    /*Printing the adjacency matrix*/
    cout <<"Printing the Adjaceny Matrix: "<<endl;
    for (int m = 0; m < this->numOfNodes; ++m)
    {
        for (int n = 0; n < this->numOfNodes; n++)
        {
            cout << Matrix[m][n] << " ";
        }
        cout << endl;
    }
    cout << endl;
}