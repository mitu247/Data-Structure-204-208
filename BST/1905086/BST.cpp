#include <string>
#include <iostream>
#include <sstream>
using namespace std;
template <typename E>
class Node
{
public:
    E element;
    Node *left;
    Node *right;
    Node()
    {
        left = right = NULL;
    }
    Node(E element, Node *left = NULL, Node *right = NULL)
    {
        this->element = element;
        this->left = left;
        this->right = right;
    }
    ~Node()
    {
    }
};
template <typename T>
class BST
{
private:
    Node<T> *root;
    int count;

    Node<T> *inserthelp(Node<T> *rt, T item)
    {
        if (rt == NULL)
        {
            return new Node<T>(item, NULL, NULL);
        }
        if (item < rt->element)
        {
            rt->left = inserthelp(rt->left, item);
        }
        else if (item >= rt->element)
        {
            rt->right = inserthelp(rt->right, item);
        }
        return rt;
    }

    Node<T> *deletehelper(Node<T> *root, T item)
    {
        if (root == NULL)
            return root;
        if (item < root->element)
        {
            root->left = deletehelper(root->left, item);
        }
        else if (item > root->element)
        {
            root->right = deletehelper(root->right, item);
        }
        else
        {
            if (root->left == NULL)
            {
                Node<T> *temp = root;
                root = root->right;
                delete temp;
            }
            else if (root->right == NULL)
            {
                Node<T> *temp = root;
                root = root->left;
                delete temp;
            }
            else
            {
                Node<T> *temp = maxValueNode(root->left);
                root->element = temp->element;
                root->left = deletemax(root->left);
                delete temp;
            }
        }
        return root;
    }
    void clearhelp(Node<T> *root)
    {
        if (root == NULL)
            return;
        clearhelp(root->left);
        clearhelp(root->right);
        delete root;
    }

    Node<T> *maxValueNode(Node<T> *root)
    {
        Node<T> *current = root;
        while (current && current->right != NULL)
            current = current->right;
        return current;
    }

    Node<T> *deletemax(Node<T> *root)
    {
        if (root->right == NULL)
        {
            return root->left;
        }
        else
        {
            root->right = deletemax(root->right);
            return root;
        }
    }

    Node<T> *findhelp(Node<T> *root, T item)
    {
        if (root == NULL)
            return NULL;
        if (item < root->element)
        {
            return findhelp(root->left, item);
        }
        else if (item > root->element)
        {
            return findhelp(root->right, item);
        }
        else
        {
            return root;
        }
    }
    void printhelp(Node<T> *root, string &str)
    {
        if (root == NULL)
            return;
        string s;
        stringstream ss;
        ss << root->element;
        ss >> s;

        str.append(s);
        if (root->left == NULL && root->right == NULL)
        {
            return;
        }
        str.push_back('(');
        printhelp(root->left, str);
        str.push_back(')');

        str.push_back('(');
        printhelp(root->right, str);
        str.push_back(')');
    }
    void helper_preOrder(Node<T> *root)
    {
        if (root != NULL)
        {
            cout << root->element << ' ';
            helper_preOrder(root->left);
            helper_preOrder(root->right);
        }
    }
    void helper_inOrder(Node<T> *root)
    {
        if (root != NULL)
        {
            helper_inOrder(root->left);
            cout << root->element << ' ';
            helper_inOrder(root->right);
        }
    }

    void helper_postOrder(Node<T> *root)
    {
        if (root != NULL)
        {
            helper_postOrder(root->left);
            helper_postOrder(root->right);
            std::cout << root->element << ' ';
        }
    }

public:
    BST()
    {
        root = NULL;
        count = 0;
    }

    ~BST()
    {
        clearhelp(root);
    }
    void clear()
    {
        clearhelp(root);
        root = NULL;
        count = 0;
    }
    //----------insertion-----------
    void insert(T item)
    {
        root = inserthelp(root, item);
        count++;
    }
    //-------------deletion------------
    void Delete(T item)
    {
        root = deletehelper(root, item);
        count--;
    }

    bool find(T item)
    {
        Node<T> *temp = findhelp(root, item);
        if (temp != NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void print()
    {
        string value = "";
        printhelp(root, value);
        cout << value << endl;
    }
    void in_order()
    {
        helper_inOrder(root);
    }
    void pre_order()
    {
        helper_preOrder(root);
    }
    void post_order()
    {
        helper_postOrder(root);
    }
};
