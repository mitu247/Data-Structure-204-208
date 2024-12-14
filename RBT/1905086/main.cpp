#include "Red_Black.cpp"
#include<bits/stdc++.h>
using namespace std;
int main(){
    RBT tree;
    node* found;
    int n,e,r,x;
    cin>>n;
    cout<<n<<endl;
    for(int i=0; i<n; i++){
       cin>>e>>x;
       if(e == 0){
        r = 1;
        found = tree.Search(tree.getRoot(),x);
        if(found != NULL && found->val != x){
            r = 0;
        }
        else{
            r = 1;
            tree.deletion(x);
        }
        cout<<e<<" "<<x<<" "<<r<<endl;
       }
       else if(e == 1){
        r = 1;
        found = tree.Search(tree.getRoot(),x);
        if(found != NULL && found->val == x){
            r = 0;
        }
        else{
            r = 1;
            tree.insertion(x);
        }
        cout<<e<<" "<<x<<" "<<r<<endl;
       }
       else if(e == 2){
        found = tree.Search(tree.getRoot(),x);
        r = 1;
        if(found != NULL && found->val != x){
            r = 0;
        }
        cout<<e<<" "<<x<<" "<<r<<endl;
       }
       else if(e == 3){
        r = tree.find(x);
        cout<<e<<" "<<x<<" "<<r<<endl;
       }
    }
    return 0;
}
