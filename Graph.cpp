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
    this->Offsets = NULL;
    this->Edges = NULL;
    this->Matrix = NULL;
}

Graph::~Graph()
{
    if (Offsets != NULL)
    {
        delete Offsets;
    }
    if (Edges != NULL)
    {
        delete Edges;
    }
    if (this->Matrix != NULL)
    {
        for (int i = 0; i < this->numOfNodes; i++)
        {
            delete Matrix[i];
        }
        delete Matrix;
    }
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
    vector<int> temp;

    /*Reading the file*/
    if (file.is_open())
    {
        /*Skip the first line*/
        getline(file, line);

        /*Read each line from the file and store it in the 'line' variable.*/
        while (getline(file, line))
        {
            /*Store the line in the temp vector*/
            temp.push_back(stoi(line));
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
    this->numOfNodes = temp[0];

    /*Defining number of edges*/
    this->numOfEdges = temp[1];

    /*Defining the offsets array*/
    this->Offsets = new int[numOfNodes + 1];
    int OffsetsStart = 2;
    int OffsetsSize = numOfNodes + 1;

    /*Defining the Edges array*/
    this->Edges = new int[numOfEdges];
    int EdgesStart = OffsetsStart + numOfNodes;
    int EdgesSize = numOfEdges;

    /*Filling the offsets array*/
    for (int i = 0; i < numOfNodes; i++)
    {
        this->Offsets[i] = temp[i + OffsetsStart];
    }
    /*The last element should be the total number of edges */
    this->Offsets[numOfNodes] = numOfEdges;

    cout << "Size of the Offsets array is: " << OffsetsSize << endl;
    MyFile << "Size of the Offsets array is: " << OffsetsSize << endl;
    cout << "Printing the Offsets array: " << endl;
    MyFile << "Printing the Offsets array: " << endl;
    for (int i = 0; i < OffsetsSize; i++)
    {
        cout << this->Offsets[i] << endl;
        MyFile << this->Offsets[i] << endl;
    }

    /*Filling and printing the Edges array*/
    cout << "Size of the Edges array is: " << EdgesSize << endl;
    MyFile << "Size of the Edges array is: " << EdgesSize << endl;
    cout << "Printing the Edges array: " << endl;
    MyFile << "Printing the Edges array: " << endl;
    for (int i = 0; i < numOfEdges; i++)
    {
        this->Edges[i] = temp[i + EdgesStart];
        cout << this->Edges[i] << endl;
        MyFile << this->Edges[i] << endl;
    }
}

void Graph::bfsTree(int source)
{
    if (this->Offsets == NULL | this->Edges == NULL)
    {
        cout << "Can't convert to BFS Tree, Please run convertToCSR function first" << endl;
    }
    else
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

                // check if neighbor has't been visited
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
}

void Graph::adjacencyMatrix()
{
    if (this->Offsets == NULL | this->Edges == NULL)
    {
        cout << "Can't convert to Adjacency Matrix, Please run convertToCSR function first" << endl;
    }
    else
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
        if (this->numOfEdges <= 10)
        {
            /*Printing the adjacency matrix*/
            cout << "Printing the Full Adjaceny Matrix: " << endl;
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
        else
        {
            cout << "Printing the sparse Adjaceny Matrix: " << endl;
            for (int m = 0; m < this->numOfNodes; ++m)
            {
                for (int n = 0; n < this->numOfNodes; n++)
                {
                    if (Matrix[m][n] == 1)
                    {
                        cout << m << " " << n << " " << Matrix[m][n] << endl;
                    }
                }
            }
            cout << endl;
        }
    }
}