#include <bits/stdc++.h>

using namespace std;

typedef struct Node {
    int data;
    struct Node *left = nullptr;
    struct Node *right = nullptr;
}node;

class BST {
public:
    BST(){ root = NULL; };
    void Search(int item, bool &found, node *&pre, node *&p);
    void Insert(int value);
    void Delete(int item);
    void Inorder(node *p) const;
private:
    node *root;
};

void BST::Inorder (node *p) const 
{
    if ( p == nullptr )
        return;
    Inorder(p->left);
    cout << p->data << endl;
    Inorder(p->right);

}

void BST::Search(int item, bool &found, node *&pre, node *&p)
{
    while () {
        if ( found || p == NULL )
            break;

        if ( item < p->data ) {
            pre = p;
            p = p->left;
        }

        else if ( item > p->data ) {
            pre = p;
            p = p->right;
        }

        else
            found = true;
    }
}

void BST::Insert(int value)
{
    bool found = false;
    node *p = root;
    node *pre = p;
    
    Search(value, found, pre, p);
    
    if (found)
        cout << "The value has been in the BST" << endl;
    else {

        node* n = new node;
        n->data = value;
        
        if ( root == nullptr )
            root = n;
        
        else {
            if ( value < pre->data )
                pre->left = n;

            if ( value > pre->data )
                pre->right = n;
        }
    }
}

void BST::Delete(int item)
{
    bool found = false;
    node *p = root;
    node *pre = p;
    
    Search(item, found, pre, p);
    
    if ( !found )
        cout << "The value is not in the BST" << endl;
    
    else {
        
        if ( p->left != nullptr && p->right != nullptr ) {
            
            node *p2 = p->right;
            node *pre2 = p;
            
            while ( p2->left != nullptr ) {
                pre2 = p2;
                p2 = p2->left;
            }

            p->data = p2->data;
            pre = pre2;
            p = p2;
        
        }

        node *subtree = nullptr;
        
        if ( p->left == nullptr )
            subtree = p->right;
        
        if ( p->right == nullptr )
            subtree = p->left;
        
        if ( pre == nullptr )
            root = subtree;
        
        else
            if ( pre->right == p )
                pre->right = subtree;
            else
                pre->left = subtree;
        
        delete p;
    }
}

