#include<iostream>
#include<cmath>
using namespace std;
struct node
{
    node* left;
    node* right;
    node* parent;
    node* child;
    int id;
    int key;
    int degree;
    bool visit;
    bool mark;
};
class FibonacciHeap
{
private:
    int total_nodes;
    struct node* mini;
public:
    FibonacciHeap()
    {
        total_nodes = 0;
        mini = NULL;
    }
    bool isEmpty() {
        return mini == NULL;
    }
    int getID() {
        return mini->id;
    }
    void insertion(int value, int id)
    {
        struct node* new_node = new node();
        new_node->id = id;
        new_node->key = value;
        new_node->left = new_node;
        new_node->right = new_node;
        new_node->parent = NULL;
        new_node->child = NULL;
        new_node->degree = 0;
        new_node->mark = false;
        new_node->visit = false;
        if(mini != NULL)
        {
            new_node->left = mini->left;
            new_node->right = mini;
            mini->left->right = new_node;
            mini->left = new_node;
            if(new_node->key < mini->key)
            {
                mini = new_node;
            }
        }
        else
        {
            mini = new_node;
        }
        total_nodes++;
    }
    void fibo_union(struct node* ptr1,struct node* ptr2)
    {
        ptr2->left->right = ptr2->right;
        ptr2->right->left = ptr2->left;
        if(ptr1->left == ptr1)
        {
            mini = ptr1;
        }
        ptr2->left = ptr2;
        ptr2->right = ptr2;
        ptr2->parent = ptr1;
        if(ptr1->child == NULL)
            ptr1->child = ptr2;
        ptr2->right = ptr1->child;
        ptr2->left = ptr1->child->left;
        (ptr1->child->left)->right = ptr2;
        ptr1->child->left = ptr2;
        ptr1->degree++;
        if (ptr2->key < (ptr1->child)->key)
            ptr1->child = ptr2;
    }
    void consolidate()
    {
        int n1;
        int n2 = (int)(log(total_nodes)/log(2));
        //cout<<n2<<endl;
        struct node* arr[n2+1];
        for(int i = 0; i <= n2; i++)
            arr[i] = NULL;
        node *ptr1,*ptr2,*ptr3,*temp;
        ptr1 = ptr3 = mini;
        do
        {
            ptr3 = ptr3->right;
            n1 = ptr1->degree;
            while(arr[n1]!=NULL)
            {
                ptr2 = arr[n1];
                if(ptr2->key<ptr1->key)
                {
                    temp = ptr1;
                    ptr1 = ptr2;
                    ptr2 = temp;
                }
                if(ptr2 == mini)
                {
                    mini = ptr1;
                }
                fibo_union(ptr1,ptr2);
                if(ptr1->left==ptr1)
                {
                    mini = ptr1;
                }
                arr[n1] = NULL;
                n1++;
            }
            arr[n1] = ptr1;
            ptr1 = ptr1->right;
        }
        while(ptr1 != mini);
        //cout<<"exit"<<endl;
        mini = NULL;
        for(int i = 0; i<=n2; i++)
        {
            if(arr[i]!=NULL)
            {
                arr[i]->left = arr[i];
                arr[i]->right = arr[i];
                if (mini != NULL)
                {
                    arr[i]->right = mini;
                    arr[i]->left = mini->left;
                    mini->left->right = arr[i];
                    mini->left = arr[i];
                    if (arr[i]->key < mini->key)
                        mini = arr[i];
                }
                else
                {
                    mini = arr[i];
                }
            }
        }
    }

    int Extract_min()
    {
        if(mini == NULL)
            return -1;
        node *temp,*ptr,*curr;
        int minValue = mini->key;

        temp = ptr = mini;
        curr = NULL;
        if(temp->child != NULL)
        {
            curr = temp->child;
            do
            {
                ptr = curr->right;
                curr->right = mini;
                curr->left = mini->left;
                mini->left->right = curr;
                mini->left = curr;
                curr->parent = NULL;
                if(curr->key<mini->key)
                {
                    mini = curr;
                }
                curr = ptr;
            }
            while(ptr!=temp->child);
        }
        temp->left->right = temp->right;
        temp->right->left = temp->left;
        mini = temp->right;
        if(temp==temp->left && temp->child == NULL)
        {
            mini = NULL;
        }
        else
        {
            mini = temp->right;
            consolidate();
        }
        total_nodes--;

        return minValue;
    }
    struct node* Find(struct node* head,int id)
    {
        struct node* found = NULL;
        node* temp = head;
        temp->visit = true;
        if(temp->id == id)
        {
            found = temp;
            temp->visit = false;
            return found;
        }
        if(found == NULL)
        {
            if(temp->child != NULL)
            {
                found = Find(temp->child, id);
            }
            if((temp->right)->visit == false)
            {
                found = Find(temp->right, id);
            }
        }
        temp->visit = false;
        return found;
    }
    void Cut(struct node* found, struct node* temp)
    {
        if(found == found->left)
            temp->child = NULL;
        if(found == temp->child)
            temp->child = found->right;

        found->left->right = found->right;
        found->right->left = found->left;
        temp->degree = temp->degree - 1;
        found->right = mini;
        found->left = mini->left;
        mini->left->right = found;
        mini->left = found;
        found->parent = NULL;
        found->mark = false;
        temp->mark = true;
    }
    void cascade_cut(struct node* temp)
    {
        node* ptr = temp->parent;
        if(ptr != NULL)
        {
            if(temp->mark == false)
            {
                temp->mark == true;
            }
            else
            {
                Cut(temp,ptr);
                cascade_cut(ptr);
            }
        }
    }
    void decrease_key(int k, int id)
    {
        struct node *found, *temp;
        if(mini==NULL)
            return;
        found = Find(mini, id);
        if(found == NULL)
            return;
        found->key = k;
        temp = found->parent;
        if(temp != NULL && found->key<temp->key)
        {
            Cut(found,temp);
            cascade_cut(temp);
        }
        if(found->key<mini->key)
            mini = found;
    }
};
