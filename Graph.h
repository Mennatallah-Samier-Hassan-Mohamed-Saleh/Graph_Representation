
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
private:
    string fileName;
    int numOfNodes;
    int numOfEdges;
    int* Offsets;
    int* Edges;
    int **Matrix;
 
public:
    /* Constructor
    @name: the Graph file name
    */
    Graph(string name);
    /*Destructor*/
    ~Graph();
    /*Converts Adjacency Graph format to CSR 
    @outName: output file name
    */
    void convertToCSR(string outName);
    /*Converts CSR to BFS Tree
    @source: source of the tree
    */
    void bfsTree(int source, string outName);
    /*Converts CSR to Adjacency Matrix*/
    void adjacencyMatrix();

};
#endif