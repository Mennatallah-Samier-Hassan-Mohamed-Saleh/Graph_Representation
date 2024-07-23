
/**
 * @author Mennatallah Saleh
 * @version 1.0
 *          This is the hearder file for a Graph calss
 */
#ifndef GRAPH_H
#define GRAPH_H
 
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

class Graph {
public:
    string fileName;
    int numOfNodes;
    int numOfEdges;
    int* Offsets;
    int* Edges;
    int **Matrix;
 
public:
    Graph(string name);
    /*Converts Adjacency Graph format to CSR*/
    void convertToCSR(string outName);
    /*Converts CSR to BFS Tree*/
    void bfsTree(int source);
    /*Converts CSR to Adjacency Matrix*/
    void abjacencyMatrix();

};
#endif