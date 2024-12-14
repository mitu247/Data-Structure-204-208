#include<bits/stdc++.h>
using namespace std;
struct node
{
    string key;
    int value;
    node *next;
};

class linked_list
{
private:
    node *head,*tail;
    int listSize;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
        listSize = 0;
    }
    node* gethead()
    {
        return head;
    }

    void append(string item,int n)
    {
        node *tmp = new node;
        tmp->key = item;
        tmp->value = n;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
        listSize++;
    }
    void deleteNode(string item)
    {

        struct node* tmp = head;
        struct node* prev = NULL;

        if (tmp != NULL && tmp->key == item)
        {
            head = tmp->next;
            listSize--;
            if(listSize==0)
            {
                tail = head;
            }
            delete tmp;
            return;
        }
        else
        {
            while (tmp != NULL && tmp->key != item)
            {
                prev = tmp;
                tmp = tmp->next;
            }
            if (tmp == NULL)
                return;
            if(tmp == tail)
                tail = prev;
            listSize--;
            prev->next = tmp->next;
            delete tmp;
        }
    }
    int Search(string item){
       int found =-1;
       node* temp = head;
       for(int i=0;temp!=NULL;i++){
           if(temp->key==item){
               found=i;
               break;
           }
           temp = temp->next;
       }
       return found;
    }
    void print()
    {
        struct node* ptr;
        ptr = head;
        while (ptr != NULL)
        {
            cout<< ptr->key <<" ";
            ptr = ptr->next;
        }
        cout<<endl;
    }
};
