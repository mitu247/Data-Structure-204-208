#include<iostream>
#include "Arr.cpp"
using namespace std;
class Dish{
    public:
    int fr;
    int t;
    int course;
    Dish(){}
    Dish(int fr, int t,int course){
       this->fr = fr;
       this->t = t;
       this->course = course;

    }
};
int main(){
    int n,x;
    cin>>n>>x;
    int *wash = new int[x];
    for(int i=1; i<=x;i++){
        cin>>wash[i];
    }
    Arr <Dish> dirtyStack;
    Arr <Dish> cleanStack;
    int *washTime = new int[n*x];
    int *fullmeal = new int[x];
    Dish dish;
    int fr,t=0,course,sum = 0,i=0,total=0,k=0;
    while(true){  
        cin>>fr>>t>>course;
        if(course==x){
           fullmeal[k]=fr;
           k++;
        }
        if(fr){
            Dish temp(fr,t,course);
            dirtyStack.push(temp);
            dish = dirtyStack.topValue();
            total++;
        }
         if(sum>=dish.t){
            if(fr==0){
               while(dirtyStack.length() && dish.t){
                  dish = dirtyStack.pop();
                  cleanStack.push(dish);
                   sum+=wash[dish.course];
                   washTime[i]=sum;
                   i++;
               }
            break;
            }
            continue;
        }
        if(sum == 0){
            Dish temp = dirtyStack.pop();
            cleanStack.push(temp);
            sum = wash[dish.course] - 1;
            washTime[i] = sum;
            i++;
        }
        else if(dish.t==sum){
            Dish temp = dirtyStack.pop();
            cleanStack.push(temp);
            sum+=wash[dish.course];
            washTime[i] = sum;
            i++;
        }
        else if(sum<dish.t){
            Dish preserve = dirtyStack.pop();
            while(dirtyStack.length()){
                dish = dirtyStack.pop();
                cleanStack.push(dish);
                sum+=wash[dish.course];
                washTime[i]=sum;
                i++;
            }
            dish = preserve;
            if(sum<dish.t){
                sum = dish.t + wash[dish.course]-1;
            }
            else{
                sum = dish.t + wash[dish.course];
            }
            cleanStack.push(dish);
            washTime[i] = sum;
            i++;
        }
    }
    cout<<sum<<endl;
    for(int j=0;j<i;j++){
        cout<<washTime[j]<<' ';
    }
    cout<<'\n';
    if(total==n*x){
        cout<<'Y'<<'\n';
    }
    else{
        cout<<'N'<<'\n';
    }
    for(int m=k-1;m>=0;m--){
        cout<<fullmeal[m]<<' ';
    }
    return 0;
}