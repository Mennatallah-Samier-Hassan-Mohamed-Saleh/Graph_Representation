#include <iostream>
#include "Graph.h"
#include "Graph.cpp"
using namespace std;
int main(){
    Graph obj("simpleGRaph.adj");
    obj.convertToCSR("outputFullGraph");
    obj.bfsTree(0);
    obj.adjacencyMatrix();

    Graph obj2("slashdot.adj");
    obj2.convertToCSR("outputFullGraph2");
    //obj2.bfsTree(1);
    //obj2.abjacencyMatrix();
}
