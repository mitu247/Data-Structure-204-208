#ifndef HEAP_H
#define HEAP_H

class Heap
{
private:
    long long maxSize;
    int *arr;
    long long idx;

    void Max_Heapify(long long i)
    {
        long long l = i << 1;
        long long r = l | 1;
        long long largest;
        if (l <= idx && arr[l] > arr[i])
            largest = l;
        else
            largest = i;
        if (r <= idx && arr[r] > arr[largest])
            largest = r;
        if (largest != i)
        {
            int t = arr[largest];
            arr[largest] = arr[i];
            arr[i] = t;
            Max_Heapify(largest);
        }
    }

    void Build_Heap()
    {
        for (long long i = (idx - 1) / 2; i >= 1; i--)
        {
            Max_Heapify(i);
        }
    }

public:
    Heap(long long size)
    {
        arr = new int[size + 1];
        this->maxSize = size + 1;
        idx = 1;
    }
    Heap(std::vector<int> &v)
    {
        arr = new int[v.size() + 1];
        for (long long i = 0; i < v.size(); i++)
        {
            arr[i+1] = v[i];
        }
        this->maxSize = v.size() + 1;
        idx = v.size() + 1;
        Build_Heap();
    }
    ~Heap(){
    delete [] arr;
    }

    void insert(int value)
    {
        if (idx <= maxSize)
        {
            arr[idx++] = value;
            long long child = idx - 1;
            long long parent = child >> 1;
            while (parent > 0 && arr[parent] < arr[child])
            {
                int t = arr[child];
                arr[child] = arr[parent];
                arr[parent] = t;
                child = parent;
                parent = parent >> 1;
            }
        }
    }
    void deleteKey()
    {
        if (idx > 1)
        {
            arr[1] = arr[idx - 1];
            idx--;
            Max_Heapify(1);
        }
    }
    int getMax()
    {
        return arr[1];
    }
    long long size()
    {
        return (idx-1);
    }
};


void heapsort(std::vector<int> &v){
    Heap h(v.size());
    for (int element:v)
    {
        h.insert(element);
    }
    v.clear();
    for(long long i=h.size();i>=1;i--){
        v.push_back(h.getMax());
        h.deleteKey();
    }
}

#endif
