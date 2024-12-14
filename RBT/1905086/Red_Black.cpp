#include<bits/stdc++.h>
using namespace std;
class node
{
public:
    int val;
    char color;
    int count;
    node* left;
    node* right;
    node* par;
    node(int val)
    {
        this->val = val;
        count = 0;
        left = NULL;
        right = NULL;
        par = NULL;
        color = 'R';
    }
    node* uncle()
    {
        if(par == NULL || par->par == NULL)
        {
            return NULL;
        }
        if(par->isRight())
        {
            return par->par->left;
        }
        else
        {
            return par->par->right;
        }
    }
    node* sibling()
    {
        if(par == NULL)
            return NULL;
        if(isRight())
            return par->left;
        else
            return par->right;
    }

    bool red_child()
    {
        if((left != NULL && left->color == 'R')||(right!=NULL && right->color == 'R'))
            return true;
        else
            return false;
    }

    bool isRight()
    {
        return this == par->right;
    }

};
class RBT
{
    node* root;
    void Left_rotation(node* rPoint)
    {
        if (rPoint == NULL)
            return;
        node* p_right = rPoint->right;
        rPoint->right = p_right->left;

        if (rPoint->right != NULL)
        {
            rPoint->right->par = rPoint;
        }

        p_right->count = rPoint->count + 1;

        p_right->par = rPoint->par;
        if (rPoint->par == NULL)
        {
            root = p_right;
        }
        else if (rPoint->par->right == rPoint)
        {
            rPoint->par->right = p_right;
        }
        else
        {
            rPoint->par->left = p_right;
        }

        p_right->left = rPoint;
        rPoint->par = p_right;
    }

    void Right_rotation(node* rPoint)
    {
        if (rPoint == NULL) return;
        node* p_left = rPoint->left;
        rPoint->left = p_left->right;
        if (rPoint->left != NULL)
        {
            rPoint->left->par = rPoint;
        }

        if (p_left->right != NULL) {
            rPoint->count = p_left->right->count + 1;
        }

        p_left->par = rPoint->par;
        if (rPoint->par == NULL)
        {
            root = p_left;
        }
        else if (rPoint->par->right == rPoint)
        {
            rPoint->par->right = p_left;
        }
        else
        {
            rPoint->par->left = p_left;
        }

        p_left->right = rPoint;
        rPoint->par = p_left;
    }

    void change_color(node* v1, node* v2)
    {
        char temp;
        temp = v1->color;
        v1->color = v2->color;
        v2->color = temp;
    }

    int findLessVal(node *tRoot, int x)
    {
        int lessCount = 0;
        node* tmp = tRoot;

        while (tmp != nullptr) {
            if (x > tmp->val) {
                lessCount = lessCount + tmp->count + 1;
                tmp = tmp->right;
            }
            else if (x < tmp->val) {
                tmp = tmp->left;
            }
            else if (x == tmp->val) {
                lessCount = lessCount + tmp->count;
                return lessCount;
            }
        }
        return lessCount;
    }
public:
    RBT()
    {
        root = NULL;
    }
    node *getRoot()
    {
        return root;
    }
    node* Search(node* temp, int item)
    {
        if (temp == NULL)
            return temp;
        if (item < temp->val && temp->left != NULL)
        {
            return Search(temp->left, item);
        }
        else if (item > temp->val && temp->right != NULL)
        {
            return Search(temp->right, item);
        }
        return temp;
    }
    void insertion(int value)
    {

        node* new_node = new node(value);
        if(root == NULL)
        {
            root = new_node;
            root->color = 'B';
            //cout<<root->val<<endl;
        }
        else
        {
            node* xt = Search(root,value);
            //cout<<xt->val<<endl;
            if(xt->val == value)
                return;
            new_node->par = xt;
            if(xt->val > value)
                xt->left = new_node;
            else
                xt->right = new_node;

            node *u = new_node;
            while (u->par != NULL)
            {
                if (u == u->par->left) {
                    u->par->count += 1;
                }
                u = u->par;
            }

            internal_propFix(new_node);
        }
    }
    void internal_propFix(node* nx)
    {
        if(nx==root)
        {
            nx->color = 'B';
            return;
        }
        node* p = nx->par;
        node* g = p->par;
        node* un = nx->uncle();
        if(p->color == 'R')
        {
            if(un != NULL && un->color == 'R')
            {
                p->color = 'B';
                un->color = 'B';
                g->color = 'R';
                internal_propFix(g);
            }
            else
            {
                if(p->isRight())
                {
                    if(nx->isRight())
                    {
                        change_color(p,g);
                    }
                    else
                    {
                        Right_rotation(p);
                        change_color(nx,g);
                    }
                    Left_rotation(g);
                }
                else
                {
                    if(nx->isRight())
                    {
                        Left_rotation(p);
                        change_color(nx,g);
                    }
                    else
                    {
                        change_color(p,g);
                    }
                    Right_rotation(g);
                }
            }
        }
    }

    void double_black_fix(node* nx)
    {
        if(nx == root)
            return;
        node* s = nx->sibling();
        node* p = nx->par;
        if(s==NULL)
        {
            double_black_fix(p);
        }
        else
        {
            if(s->color == 'R')
            {
                p->color = 'R';
                s->color = 'B';
                if(s->isRight())
                {
                    Left_rotation(p);
                }
                else
                {
                    Right_rotation(p);
                }
                double_black_fix(nx);
            }
            else
            {
                if(s->red_child())
                {
                    if(s->right != NULL && s->right->color== 'R')
                    {

                        if(s->isRight())  ///right-right
                        {
                            s->right->color = s->color;
                            s->color = p->color;
                            Left_rotation(p);
                        }
                        else ///left-right
                        {
                            s->right->color = p->color;
                            Left_rotation(s);
                            Right_rotation(p);
                        }
                    }
                    else
                    {
                        if(s->isRight()) ///right-left
                        {
                            s->left->color = p->color;
                            Right_rotation(s);
                            Left_rotation(p);
                        }
                        else ///left-left
                        {
                            s->left->color = s->color;
                            s->color = p->color;
                            Right_rotation(p);
                        }
                    }
                    p->color = 'B';
                }
                else
                {
                    s->color = 'R';
                    if(p->color == 'B')
                        double_black_fix(p);
                    else
                        p->color = 'B';
                }
            }
        }
    }

    node* minValueNode(node* temp)
    {
        node* current = temp;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    node* replace_node(node* temp)
    {
        if(temp->left == NULL && temp->right == NULL)
            return NULL;
        else if(temp->right == NULL)
            return temp->left;
        else if(temp->left == NULL)
            return temp->right;
        else
            return minValueNode(temp->right);
    }
    void delete_node(node* found)
    {
        while (found != NULL) {

            node* rfound = replace_node(found);
            bool double_black = false;
            if((rfound==NULL || rfound->color == 'B')&&(found->color == 'B'))
                double_black = true;
            node* p = found->par;
            if(rfound == NULL) ///found leaf
            {
                if(found == root)
                {
                    root = NULL;
                }
                else
                {
                    if(double_black == true)
                    {
                        double_black_fix(found);
                    }
                    else
                    {
                        if(found->sibling() != NULL)
                            found->sibling()->color = 'R';
                    }
                    if(found->isRight())
                        p->right = NULL;
                    else
                        p->left = NULL;
                }
                delete found;
                return;
            }
            if(found->left == NULL || found->right == NULL)
            {
                if(found == root)
                {
                    found->val = rfound->val;
                    found->left = found->right = NULL;
                    delete rfound;
                }
                else
                {
                    if(found->isRight())
                        p->right = rfound;
                    else
                        p->left = rfound;
                    delete found;
                    rfound->par = p;
                    if(double_black)
                        double_black_fix(rfound);
                    else
                        rfound->color = 'B';
                }
                return;
            }
            int temp;
            temp = rfound->val;
            rfound->val = found->val;
            found->val = temp;
            found = rfound;
        }
    }

    void deletion(int value)
    {
        if(root == NULL)
            return;
        node* found = Search(root,value);
        if(found == NULL || found->val != value)
            return;
        else
        {
            node *u = found;
            while (u->par != nullptr)
            {
                if (u == u->par->left) {
                    u->par->count -= 1;
                }
                u = u->par;
            }

            delete_node(found);
        }
    }

    int find(int x)
    {
        return findLessVal(root, x);
    }

};



