#include <iostream>
#include "LL.cpp"

using namespace std;

template <typename T>
void printStack(LL<T> &st)
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

    LL<int> st;
    for (int i = 0; i < size; i++)
    {
        int n;
        cin >> n;
        st.push(n);
    }
    printStack(st);
    printStack(st);
    int t = -1, inp;
    while (t) {
        cin >> t >> inp;
        if (t == 1) {
            st.clear();
            printStack(st);
            cout << -1 << endl;
        }
        else if (t == 2) {
            st.push(inp);
            printStack(st);
            cout << -1 << endl;
        }
        else if (t == 3) {
            int n = st.pop();
            printStack(st);
            cout << n << endl;
        }
        else if (t == 4) {
            int len = st.length();
            printStack(st);
            cout << len << endl;
        }
        else if (t == 5) {
            
            int topVal = -1;
            if (st.length() != 0) topVal = st.topValue();
            printStack(st);
            if (st.length()!=0) cout << topVal << endl;
            else cout << "Null" << endl;
        }
    }

    return 0;
}