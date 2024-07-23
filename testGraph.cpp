#include <iostream>
#include "Graph.h"
#include "Graph.cpp"
using namespace std;
int main(){
    int x=0;
    int y=0;
    for (int i=0;i<y;++i){
        x++;
        cout<<"Meann"<<endl;
    }
    std::cout<<x<<endl;

    Graph obj("simpleGRaph.adj");
    obj.convertToCSR("outputFullGraph");
}
