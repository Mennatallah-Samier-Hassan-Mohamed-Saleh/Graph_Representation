#include <iostream>
#include "Graph.h"
#include "Graph.cpp"
using namespace std;
int main(){
    Graph obj("simpleGRaph.adj");
    obj.convertToCSR("outputFullGraph");
}
