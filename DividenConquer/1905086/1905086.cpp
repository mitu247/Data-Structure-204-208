#include<bits/stdc++.h>
#include<ctime>
#include<fstream>
using namespace std;
int random = 0;

void Merge(int arr[],int p,int q,int r){
    int n1 = q-p+1;
    int n2 = r-q;
    int L[n1],R[n2];
    for(int i = 0;i < n1;i++){
        L[i] = arr[p+i];
    }
    for(int j = 0;j < n2; j++){
        R[j] = arr[q+1+j];
    }
    int i,j,k;
    i = 0;
    j = 0;
    k = p;
    while(i < n1 && j < n2){
        if(L[i]<=R[j]){
            arr[k++] = L[i++];
        }
        else{
            arr[k++] = R[j++];
        }
    }
    while(i<n1){
        arr[k++] = L[i++];
    }
    while(j<n2){
        arr[k++] = R[j++];
    }
}

void MergeSort(int arr[],int l,int h){
    if(l<h){
    int md = (l+h)/2;
    MergeSort(arr,l,md);
    MergeSort(arr,md+1,h);
    Merge(arr,l,md,h);
    }
}
void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}
int partition(int arr[],int low,int high){
    int pivot = arr[high];
    int idx = low - 1;
    for(int i = low;i < high; i++){
       if(arr[i] <= pivot){
        swap(arr[i],arr[++idx]);
       }
    }
    swap(arr[++idx],arr[high]);
    return idx;
}
int random_partition(int arr[],int low,int high){
    int pivot, n;
    n = rand();
    pivot = low + n%(high-low+1);
    swap(arr[pivot],arr[high]);
    int index = partition(arr,low,high);
    return index;
}
void QuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        QuickSort(arr, low, pivot - 1);
        QuickSort(arr, pivot + 1, high);
    }
}
void Randomized_QuickSort(int arr[],int low, int high)
{
    if (low < high)
    {
        int pivot = random_partition(arr, low, high);
        QuickSort(arr, low, pivot - 1);
        QuickSort(arr, pivot + 1, high);
    }
}
void InsertionSort(int arr[],int n)
{
    for(int i = 1;i<n;i++){
            int curr = arr[i];
    int j = i-1;
    while(j>=0 && arr[j]>curr){
       arr[j+1] = arr[j];
       j--;
    }
    arr[j+1] = curr;
    }
}
void randomNumGen(int arr[],int n){
    srand(random++);
    for(int i = 0; i < n; i++){
        arr[i] = rand();
    }
}
//void printArray(int arr[],int n){
//    for(int i = 0; i < n; i++){
//        cout<<arr[i]<<" ";
//    }
//    cout<<'\n';
//}
int main(){

    int valueSet[] = {5,10,100,1000,10000,100000};
    int n =sizeof(valueSet)/sizeof(valueSet[0]);
    ofstream outFile("out.txt");
    outFile<<",,,,Time required in ms"<<endl;
    outFile<<"n,Merge Sort,QuickSort,Randomized QuickSort,Insertion Sort,QuickSort with Sorted Input,Randomized QuickSort With Sorted Input,STL Sort() Function"<<endl;

    for(int i = 0;i < n; i++){
        int n1 = valueSet[i];
        int arr[n1];
        float diff_merge = 0.0;
        for(int k = 0;k < 20; k++){
            randomNumGen(arr, n1);
            clock_t start_time = clock();
            MergeSort(arr, 0, n1-1);
            diff_merge+=float(clock() - start_time)/CLOCKS_PER_SEC;
        }
        cout<<"average time needed for merge sort: "<<(diff_merge*1000)/20<<'\n';

        float diff_quick = 0.0;
        random = 0;
        for(int k = 0;k < 20; k++){
            randomNumGen(arr, n1);
            clock_t start_time = clock();
            QuickSort(arr, 0, n1-1);
            diff_quick+=float(clock() - start_time)/CLOCKS_PER_SEC;
        }
        cout<<"average time needed for quick sort: "<<(diff_quick*1000)/20<<'\n';
        random = 0;
        float diff_ranquick = 0.0;
        for(int k = 0;k < 20; k++){
            randomNumGen(arr, n1);
            clock_t start_time = clock();
            Randomized_QuickSort(arr, 0, n1-1);
            diff_ranquick+=float(clock() - start_time)/CLOCKS_PER_SEC;
        }
        cout<<"average time needed for random quick sort: "<<(diff_ranquick*1000)/20<<'\n';
        random = 0;
        float diff_insert = 0.0;
        for(int k = 0;k < 20; k++){
            randomNumGen(arr, n1);
            clock_t start_time = clock();
            InsertionSort(arr, n1);
            diff_insert+=float(clock() - start_time)/CLOCKS_PER_SEC;
        }
        cout<<"average time needed for insertion sort: "<<(diff_insert*1000)/20<<'\n';
        random = 0;
        float diff_stlsort = 0.0;
        for(int k = 0;k < 20; k++){
            randomNumGen(arr, n1);
            clock_t start_time = clock();
            sort(arr, arr+n1);
            diff_stlsort+=float(clock() - start_time)/CLOCKS_PER_SEC;
        }
        cout<<"average time needed for stl sort: "<<(diff_stlsort*1000)/20<<'\n';
        random = 0;
        float diff_q = 0.0;
        for(int k = 0;k < 20; k++){
            randomNumGen(arr, n1);
            MergeSort(arr,0,n1-1);
            clock_t start_time = clock();
            QuickSort(arr, 0, n1-1);
            diff_q+=float(clock() - start_time)/CLOCKS_PER_SEC;
        }
        cout<<"average time needed for sorted quick sort: "<<(diff_q*1000)/20<<'\n';
        random = 0;
        float diff_r = 0.0;
        for(int k = 0;k < 20; k++){
            randomNumGen(arr, n1);
            MergeSort(arr,0,n1-1);
            clock_t start_time = clock();
            Randomized_QuickSort(arr, 0, n1-1);
            diff_r+=float(clock() - start_time)/CLOCKS_PER_SEC;
        }
        cout<<"average time needed for sorted random quick sort: "<<(diff_r*1000)/20<<'\n';
        outFile<<valueSet[i]<<","<<(diff_merge*1000)/20<<","<<(diff_quick*1000)/20<<","<<(diff_ranquick*1000)/20<<","<<(diff_insert*1000)/20<<","
                                                                        <<(diff_q*1000)/20<<","<<(diff_r*1000)/20<<","<<(diff_stlsort*1000)/20<<endl;
    }
    outFile.close();
    return 0;
}
