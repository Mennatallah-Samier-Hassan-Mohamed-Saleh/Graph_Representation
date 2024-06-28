#include <iostream>
#include "./2D_array.cpp"
using namespace std;

int main()
{
    twoDimensionArray Graph(4, 4);
    Graph.addElement(0, 0, 12);
    Graph.addElement(0, 2, 26);
    Graph.addElement(2, 1, 19);
    Graph.addElement(3, 1, 14);
    Graph.addElement(3, 3, 7);
    Graph.printArray();
    return 0;
}