#include <iostream>
#include "Arr.cpp"

using namespace std;

template <typename T>
void printQueue(Arr<T> &myQueue) {
 int len = myQueue.length();
    T* printHelper = new T[len];
    for (int i=0; i<len; i++) {
        T store = myQueue.dequeue();
        printHelper[i] = store;
    }
    cout << "<";
    for (int i=0; i<len; i++) {
        cout << printHelper[i];
        if (i != len-1) cout << ", ";
        myQueue.enqueue(printHelper[i]);
    }
    cout << ">" << endl;
    delete [] printHelper;
}

int main() {
    int size;
    cin >> size;
    int *arr = new int[size+1];

    for (int i=1; i<=size; i++) {
        cin >> arr[i];
    }

    Arr<int> queue(arr, size+1);
    printQueue(queue);

    int opNo=-1, input;

    while (opNo) {
        cin >> opNo >> input;
        if (opNo == 1) {
            queue.clear();
            printQueue(queue);
            cout << -1 << endl;
        }
        else if (opNo == 2) {
            queue.enqueue(input);
            printQueue(queue);
            cout << -1 << endl;
        }
        else if (opNo == 3) {
            int item = queue.dequeue();
            printQueue(queue);
            if(queue.length())
            cout << item << endl;
            else
            cout<<-1<<endl;
        }
        else if (opNo == 4) {
            int len = queue.length();
            printQueue(queue);
            cout << len << endl;
        }
        else if (opNo == 5) {
            int frontVal = queue.frontValue();
            printQueue(queue);
            if(queue.length())
            cout << frontVal << endl;
            else
            cout<<-1<<endl;
        }
        else if (opNo == 6) {
            int rearVal = queue.rearValue();
            printQueue(queue);
            if(queue.length())
            cout << rearVal << endl;
            else
            cout<<-1<<endl;
            
        }
        else if (opNo == 7) {
            int leavingQval = queue.leaveQueue();
            printQueue(queue);
            if(queue.length())
            cout << leavingQval << endl;
            else
            cout<<-1<<endl;
            
        }
    }
    return 0;
}