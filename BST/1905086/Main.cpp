#include <iostream>
#include "BST.cpp"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
int main()
{
    string text;
    ifstream MyReadFile("input.txt");
    char opNo;
    string value;
    BST<int> obj;
    while (MyReadFile >> opNo >> value)
    {
        if (opNo == 'F')
        {
            int value1;
            stringstream ss;
            ss << value;
            ss >> value1;
            if (obj.find(value1))
            {
                cout << "True" << endl;
            }
            else
            {
                cout << "False" << endl;
            }
        }
        else if (opNo == 'I')
        {
            int value1;
            stringstream ss;
            ss << value;
            ss >> value1;
            obj.insert(value1);
            obj.print();
        }
        else if (opNo == 'D')
        {
            int value1;
            stringstream ss;
            ss << value;
            ss >> value1;
            if (obj.find(value1))
            {
                obj.Delete(value1);
                obj.print();
            }
            else
            {
                cout << "Invalid Operation" << endl;
            }
        }
        else if (opNo == 'T')
        {
            if (value == "In")
            {
                obj.in_order();
            }
            else if (value == "Pre")
            {
                obj.pre_order();
            }
            else if (value == "Post")
            {
                obj.post_order();
            }
            cout << endl;
        }
    }
    MyReadFile.close();
    return 0;
}
