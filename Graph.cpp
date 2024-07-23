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
    for (int i = 0; i < m; i++)
    {
        ind[i] = stoi(temp[i + indStart]);
        cout << ind[i] << endl;
        MyFile << ind[i] << endl;
    }
}