#include <iostream>
#include "Arr.cpp"
#include "LL.cpp"

using namespace std;

template <typename T>
void printStack(Arr<T> &st)
{
    int len = st.length();
    T *array = new T[len];
    for (int i = len - 1; i >= 0; i--)
    {
        array[i] = st.pop();
    }
    cout << "<";
    for (int i = 0; i < len; i++)
    {
        cout << array[i];
        st.push(array[i]);
        if (i != len - 1)
        {
            cout << ", ";
        }
    }
    delete [] array;
    cout << ">" << endl;
}
int main()
{
    int size;
    cin >> size;

    Arr<int> st;
    for (int i = 0; i < size; i++)
    {
        int n;
        cin >> n;
        st.push(n);
    }
    printStack(st);
    printStack(st);
    int t = -1, value;
    while (t) {
        cin >> t >> value;
        if (t == 1) {
            st.clear();
            printStack(st);
            cout << -1 << endl;
        }
        else if (t == 2) {
            st.push(value);
            printStack(st);
            cout << -1 << endl;
        }
        else if (t == 3) {
            if(st.length()== 0){
                cout<<"Nothing to pop"<<endl;
                printStack(st);
            }
            else{
            int n = st.pop();
            printStack(st);
            cout << n << endl;
            }

        }
        else if (t == 4) {
            int len = st.length();
            printStack(st);
            cout << len << endl;
        }
        else if (t == 5) {
            int topVal = st.topValue();
            printStack(st);
            if (st.length()!=0) cout << topVal << endl;
            else cout << "Null" << endl;
        }
        else if (t == 6) {
            if (st.length() == 0) {
                st.setDirection(value);
                printStack(st);
                cout << -1 << endl;
            }
            else {
                cout << "Invalid" << endl;
            }
        }
    }

    return 0;
}