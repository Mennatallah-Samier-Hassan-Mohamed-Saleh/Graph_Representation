
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
 
public:
    Graph(string name);
 
    void convertToCSR(string outName);
};
#endif