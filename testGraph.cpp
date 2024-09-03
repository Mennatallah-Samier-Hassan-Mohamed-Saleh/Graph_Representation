#include <iostream>
#include "Graph.h"
#include "Graph.cpp"
using namespace std;
int main(){
    Graph obj("simpleGRaph.adj");
    obj.convertToCSR("outputFullGraph");
    obj.bfsTree(0,"small_output");
    //obj.adjacencyMatrix();

    //Graph obj2("slashdot.adj");
    //obj2.convertToCSR("outputFullGraph2");
    //obj2.bfsTree(1,"big_output");
   // obj2.adjacencyMatrix();
}
