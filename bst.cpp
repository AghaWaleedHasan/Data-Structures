#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>

template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>:: ~BST(){

    
}

template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
   if (p == NULL)
   {
       return -1;
   }

    int l = (p->left) ? height(p->left) : -1;
    int r = (p->right) ? height(p->right) : -1;
    return max(l, r) + 1;

}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
    if (p==NULL)
    {
        return 0;
    }

    else //if (p->left != NULL && p->right!=NULL)
    {
        return height(p->left) - height(p->right);
    }

    /*else if (p == root)
    {
        return 0;
    }*/
}

template <class T>
void BST<T> :: fixHeight(node<T>* p){
    p->height = height(p);
}

// ROTATING HELPERS
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* z){
    // Rotate left code goes here.
    node<T>* y = z->right;
    node<T>* T2 = y->left;

    z->right = T2;
    y->left = z;

    /*y->height=height(y);
    z->height=height(z);*/
    fixHeight(y);
    fixHeight(z);

    z = y;
    return y;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* z){
    // Rotate right code goes here
    node<T>* y = z->left;
    node<T>* T3 = y->right;

    z->left = T3;
    y->right = z;

    /*z->height = height(z);
    y->height = height(y);*/
    fixHeight(y);
    fixHeight(z);

    z = y;
    return y;
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p){
    //fixHeight(p);
    //return p;
	
    int bal = balanceFactor(p);

    //cout<<"1"<<endl;
    if (bal > 1)
    {
        if ((balanceFactor(p->left)) >= 0)
        {
            p = rotateright(p);
            //cout<<"2"<<endl;
        }

        //cout<<"2"<<endl;

        else
        {
            node<T>* T1 = p->left;
            p->left = rotateleft(T1);
            p=rotateright(p);
            //cout<<"3"<<endl;
        }

        //cout<<"3"<<endl;
    }

    else if (bal < -1)
    {
        if ((balanceFactor(p->right))>0)
        {
            node<T>* T2 = p->right;
            p->right = rotateright(T2);
            p=rotateleft(p);
            //cout<<"4"<<endl;
        }
        else
        {
            p = rotateleft(p);
            //cout<<"5"<<endl;
        }
    }
    fixHeight(p);
    return p;
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){

    root = insertHelper(value,k,root);

}
// insertion helpe  r
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) {

    if (p == NULL)
    {
        node<T>* temp = new node<T>(k, value);
        p = temp;
    }

    else
    {
        if (k < p->key)
        {
            p->left = insertHelper(value, k, p->left);
        }

        else if (k > p->key)
        {
            p->right = insertHelper(value, k, p->right);
        }
    }

    return balance(p);
}

template<class T>
node<T>* BST<T> :: search(T key){
    node<T>* temp = root;

    while (temp != NULL)
    {
        if (temp->key == key)
        {
            return temp;
        }

        else if (key < temp->key)
        {
            temp = temp->left;
        }

        else if (key > temp->key)
        {
            temp = temp -> right;
        }

    }

    return NULL;
    // Search code goes here.
}
// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
    // This function finds the min node of the tree.
    if (p != NULL)
    {
        if (p->left != NULL)
        {
            return findmin(p->left);
        }
        else
        {
            return p;
        }
    }

    else
    {
        return NULL;
    }
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
    if (p != NULL)
    {
        if (p->left != NULL)
        {
            removemin(p->left);
        }
        else
        {
            if (p->right != NULL)
            {
                /*T new_key = (p->right)->key;
                string new_val = (p->right)->value;
                p->key = new_key;
                p->value = new_val;
                p->right = NULL;*/
                p = p->right;
                return p;
            }

            else
            {
                node<T>* temp = searchParent(p, root);
                temp->left = NULL;
            }
        }
    }
    // This function recursively finds the min node and deletes it.

    return balance(p);
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
    // This function uses findmin and deletemin to delete arbitrary node in the tree.*/

    if (p != NULL)
    {
        if (p->key == k)
        {
            if (p->left != NULL && p->right != NULL)
            {
                T rt_subtree_min_key = (findmin(p->right))->key;
                string rt_subtree_min_value = (findmin(p->right))->value;
                removemin(p->right);
                p->key = rt_subtree_min_key;
                p->value = rt_subtree_min_value;
                //return balance(p);

            }

            else if (p->left == NULL ^ p->right == NULL)
            {
                if (p->left == NULL)
                {

                    //node<T>* temp = searchParent(p, root);
                    p = p->right;
                    return p;
                }

                else if (p->right == NULL)
                {

                    //node<T>* temp = searchParent(p, root);
                    p = p->left;
                    return p;
                }
            }

            else if (p->left == NULL && p->right == NULL)
            {

                node<T>* temp = searchParent(p, root);
                if (temp->left == p)
                {
                    temp->left = NULL;
                    return p;
                }

                else
                {
                    temp->right = NULL;
                    return p;
                }
            }
        }

        else
        {
            if (k < p->key)
            {
                p->left = remove(p->left, k);
            }

            else if (k > p->key)
            {
                p->right = remove(p->right, k);
            }
        }
    }

    else
    {
        return p;
    }

    p =  balance(p);
    return p;
   
}


template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}

template<class T>
void BST<T>::printTree(node<T> *root, int space)
{
    int COUNT = 10;

    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    printTree(root->right, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->key<<"\n";

    // Process left child
    printTree(root->left, space);
}

template<class T>
node<T>* BST<T>::searchParent(node<T>* p, node<T>* root)
{
    if (p != root)
    {
        if (root->right == p || root->left == p)
        {
            return root;
        }

        else
        {
            if (p->key < root->key)
            {
                return searchParent(p, root->left);
            }

            else
            {
                return searchParent(p, root->right);
            }
        }
    }

    else
    {
        return root;
    }
}

/*int main()
{
    BST<int> b;
    b.insert("a", 34);
    node<int>* c = b.getRoot();
    //cout<<c->value<<endl;
    b.insert("b", 7);
    //cout<<(c->left)->key<<endl;
    //cout<<"Done!"<<endl;
    b.insert("c", 53);
    //b.print_tree(c);

    //b.insert("d", 66);
    //cout<<(c->right)->key<<endl;

    b.insert("d", 12);
    //cout<<((c->left)->right)->key<<endl;
    b.insert("e", 68);
    b.insert("f", 90);
    b.insert("g", 24);
    b.insert("h", 71);
    b.insert("i", 13);
    b.insert("j", 3);
    b.insert("k", 1);
    b.insert("l", 61);
    b.insert("m", 18);
    b.insert("n", 30);
    b.insert("o", 50);
    b.insert("p", 4);
    b.insert("q", 11);
    b.insert("r", 52);
    b.insert("r", 54);
    b.insert("r", 55);
    b.insert("r", 56);
    b.insert("r", 80);
    b.printTree(c, 0);
    //b.insert("o", 76);
    cout<<endl;
    cout<<"STARTING DELETION"<<endl;
    cout<<endl;

    b.delete_node(90);
    b.printTree(c, 0);
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;

    b.delete_node(18);
    b.printTree(c, 0);
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;

    b.delete_node(50);
    b.printTree(c, 0);
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;

    b.delete_node(24);
    b.printTree(c, 0);
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;

    b.delete_node(68);
    b.printTree(c, 0);
    cout<<endl;
    cout<<"---------------------------------------------"<<endl;

}*/
#endif
