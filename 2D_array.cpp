#include <iostream>
using namespace std;
/**
 * @author Mennatallah Saleh
 * @version 1.0
 *          This class is an example of a two dimensioal array
 */
class twoDimensionArray
{
private:
    int rows;
    int cols;
    int **array;

public:
    twoDimensionArray(int numRows, int numCols)
    {
        this->rows = numRows;
        this->cols = numCols;

        /** Initializing the array with zeros**/
        this->array = new int *[this->rows];
        for (int i = 0; i < this->rows; ++i)
        {
            this->array[i] = new int[this->cols];
            for (int j = 0; j < this->cols; j++)
            {
                array[i][j] = 0;
            }
        }
    }

    /* Adding an element at a specific row and column */
    void addElement(int m, int n, int value)
    {
        array[m][n] = value;
    }

    /* Printing the entire array */
    void printArray()
    {
        for (int i = 0; i < this->rows; ++i)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

/*
int main(){
    cout<<"Hello"<<endl;
    twoDimensionArray Object(3,3);
    Object.printArray();
    Object.addElement(0,0,5);
    Object.printArray();
    Object.addElement(0,1,6);
    Object.addElement(0,2,7);
    Object.addElement(1,0,8);
    Object.addElement(1,1,9);
    Object.addElement(1,2,10);
    Object.addElement(2,0,11);
    Object.addElement(2,1,12);
    Object.addElement(2,2,13);
    Object.printArray();
}
*/