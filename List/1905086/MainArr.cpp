#include <iostream>
#include <string>
#include <cstdlib>
#include "Arr.cpp"
//#include "LL.cpp"

using namespace std;
template <typename T>
void print(Arr<T> &list, T value)
{
   int pos = list.currPos();
   list.moveToStart();
   cout << "< ";
   for (int i = 0; i < list.length(); i++)
   {
      if (i == pos)
         cout << "| ";
      cout << list.getValue() << ' ';
      list.next();
   }
   cout << ">" << endl;
   if (value != INT_MIN)
      cout << value << endl;
   list.moveToPos(pos);
}
int main()
{
   int K, X, *arr, value = INT_MIN, t = -1;
   cin >> K >> X;
   arr = new int[X];
   for (int i = 0; i < K; i++)
   {
      cin >> arr[i];
   }
   Arr<int> list(arr, K);
   print(list, value);
   while (t)
   {
      cin >> t >> value;
      if (t == 1)
      {
         list.clear();
         print(list, -1);
      }
      else if (t == 2)
      {
         list.insert(value);
         print(list, -1);
      }
      else if (t == 3)
      {
         list.append(value);
         print(list, -1);
      }
      else if (t == 4)
      {
         //cout<<"in remove"<<endl;
         print(list, list.remove());
      }
      else if (t == 5)
      {
         list.moveToStart();
         print(list, -1);
      }
      else if (t == 6)
      {
         list.moveToEnd();
         print(list, -1);
      }
      else if (t == 7)
      {
         list.prev();
         print(list, -1);
      }
      else if (t == 8)
      {
         list.next();
         print(list, -1);
      }
      else if (t == 9)
      {
         print(list, list.length());
      }
      else if (t == 10)
      {
         print(list, list.currPos());
      }
      else if (t == 11)
      {
         list.moveToPos(value);
         print(list, -1);
      }
      else if (t == 12)
      {
         print(list, list.getValue());
      }
      else if (t == 13)
      {
         print(list, list.Search(value));
      }
   }
   return 0;
}