/**
 * @author Mennatallah Saleh
 * @version 1.0
 * This code is to read adjacency graph format into CSR format
 */
#include <fstream> 
#include <iostream> 
#include <string> 
#include <vector>
#include <typeinfo>

using namespace std; 
  
int main() 
{ 
    // Create an input file stream object named 'file' and 
    // open the file "slashdot.adj". 
    ifstream file("slashdot.adj"); 
  
    // String to store each line of the file. 
    string line; 
    
    //Temporaray vector to read the file
    vector<string> temp;

    //Adding Padding to match line number with vectore index
    temp.push_back("Zero");

    if (file.is_open()) { 
        // Read each line from the file and store it in the 
        // 'line' variable. 
        while (getline(file, line)) { 
            //cout << line << endl; 
            temp.push_back(line);
        } 
  
        // Close the file stream once all lines have been 
        // read. 
        file.close(); 
    } 
    else { 
        // Print an error message to the standard error 
        // stream if the file cannot be opened. 
        cerr << "Unable to open file!" << endl; 
    } 
    cout<<"Size of the vector: "<<temp.size()<<endl;  
    /*Defining number of nodes*/
    int n= stoi(temp[2]);
    /*Defining number of edges*/
    int m=stoi(temp[3]);

    /*Defining the offsets array*/
    int ptr[n+1];
    int ptrStart= 4 ;
    int ptrSize= sizeof(ptr) /sizeof (int);

    /*Defining the indices array*/
    int ind[m];
    int indStart= ptrStart+n;
    int indSize= sizeof(ind) /sizeof (int);


    /*Filling the offsets array*/
    for (int i=0; i < n; i++)
    {
        ptr[i]= stoi(temp[i+ptrStart]);
    }
    /*The last element should be the total number of edges */
    ptr[n] = m;

    cout <<"Size of the ptr array is: "<<ptrSize <<endl;
    cout <<"Printing the ptr array: " <<endl;
    for (int i=0; i < ptrSize; i++)
    {
        cout <<ptr[i]<<endl;
    }

    /*Filling and printing the indices array*/
    cout <<"Size of the indices array is: "<<indSize <<endl;
    cout <<"Printing the indices array: " <<endl;
    for (int i=0; i < m; i++)
    {
        ind[i]= stoi(temp[i+indStart]);
        cout <<ind[i]<<endl;
    }

    return 0; 
}