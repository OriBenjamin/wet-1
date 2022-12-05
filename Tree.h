//
// Created by liels on 28/11/2022.
//

#ifndef HW1_TREE_H
#define HW1_TREE_H

#include <stdlib.h>
#include <string>
#include "Node.h"
#include <iostream>
using namespace std;
const int INITIAL_SIZE_OF_TREE = 0;

template<class Key, class Value>
class Tree
{
    private:
    Node<Key,Value>* Root;
    int Size;

    public:
    Tree():
    Root(NULL), Size(INITIAL_SIZE_OF_TREE){}
//    Tree(const Node<Key,Value>& Root, int Size) = default;
    ~Tree() = default;
    Tree& operator=(const Tree& t) = delete;
    class InvalidArgument: public std::exception
    {
        public:
        const char *what() const noexcept override {return "An invalid argument has passed";}
    };
    class NodeAlreadyExist : public std::exception
    {
    public:
        const char *what() const noexcept override {return "Node already exist in this tree";}
    };
    class NodeDoesNotExist : public std::exception
    {
    public:
        const char *what() const noexcept override {return "Node does not exist in this tree";}
    };

    //built-in functions
    Node<Key,Value>* insertNode(Node<Key,Value>* currentNode,Node<Key,Value>* nodeForInsertion);
    void createAndInsertNode(const Key& key, Value* value);
    Value* remove(const Key& key);
    Node<Key,Value>* removeNode(Node<Key,Value>* currentNode, const Key& key);
    //void update(Key key, Value value);
    void connectSonParent(Node<Key, Value> *currentNode,Node<Key, Value> *son);
    //  friend void mergeTrees(Tree<Key,Value> t1, Tree<Key,Value> t2);
    //Value** toArray(Key begin, Key end);
    //Key getClosest(Key key);
    int getBalanceFactor(const Node<Key, Value>* node);
    Node<Key, Value> *getRotated(Node<Key, Value> *currentNode, int rightChildBalanceFactor, int leftChildBalanceFactor,
               int balanceFactor);
    //////////////////////////
    void print()
    {
        printNode(Root);
        //cout << *Root->value;
    }

    void printNode(Node<Key,Value>* node)
    {
        if(node == nullptr) return;
        printNode(node->left);
        cout << *node->value<<", ";
        printNode(node->right);
    }

    void updateHeight(Node<Key,Value>* node)
    {
        if(node != nullptr)
        {
            int leftHeight = (node->left) ? node->left->height : -1;
            int rightHeight = (node->right) ? node->right->height : -1;
            node->height = (leftHeight >= rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
        }
    }

};

template<class Key, class Value>
void Tree<Key,Value>::createAndInsertNode(const Key& key, Value* value)
{
    if(value == nullptr)
    {
        throw InvalidArgument();
    }
        Node<Key,Value>* nodeForInsertion = new Node<Key,Value>(key,value);
        Root = insertNode(Root, nodeForInsertion);
        if(nodeForInsertion->next) nodeForInsertion->next->prev = nodeForInsertion;
        if(nodeForInsertion->prev) nodeForInsertion->prev->next = nodeForInsertion;

}

template<class Key, class Value>
int Tree<Key,Value>::getBalanceFactor(const Node<Key, Value>* node)
{
    if (node == nullptr) return 0;
    int leftHeight = (node->left) ? node->left->height : -1;
    int rightHeight = (node->right) ? node->right->height : -1;
    return leftHeight - rightHeight;
}

template<class Key, class Value>
Node<Key,Value>* Tree<Key,Value>::insertNode(Node<Key,Value>* currentNode, Node<Key,Value>* nodeForInsertion)
{
        if(currentNode == nullptr)
        {
            return nodeForInsertion;
        }
        if(nodeForInsertion->key == currentNode->key)
        {
            throw NodeAlreadyExist();
        }
        else if(nodeForInsertion->key < currentNode->key)
        {
            if(!nodeForInsertion->next || nodeForInsertion->next->key > currentNode->key)
            {
                nodeForInsertion->next = currentNode;
            }
            currentNode->left = insertNode(currentNode->left, nodeForInsertion);
            currentNode->left->parent = currentNode;
        }
        else
        {
            if(!nodeForInsertion->prev || nodeForInsertion->prev->key < currentNode->key)
            {
                nodeForInsertion->prev = currentNode;
            }
            currentNode->right = insertNode(currentNode->right, nodeForInsertion);
            currentNode->right->parent = currentNode;
        }
        updateHeight(currentNode);

        int rightChildBalanceFactor = getBalanceFactor(currentNode->right);
        int leftChildBalanceFactor = getBalanceFactor(currentNode->left);
        int balanceFactor = getBalanceFactor(currentNode);
    return getRotated(currentNode, rightChildBalanceFactor, leftChildBalanceFactor, balanceFactor);

}

template<class Key, class Value>
Node<Key, Value> *
Tree<Key, Value>::getRotated(Node<Key, Value> *currentNode, int rightChildBalanceFactor, int leftChildBalanceFactor,
                             int balanceFactor) {
    if(balanceFactor == 2 && leftChildBalanceFactor >= 0)
    {
        //cout << "LL!";
        Node<Key,Value>* A = currentNode;
        Node<Key,Value>* Al = currentNode->left;
        Node<Key,Value>* Alr = currentNode->left->right; //can be null
        if(Alr) Alr->parent = A;
        Al->parent = A->parent;
        Al->right = A;
        A->parent = Al;
        A->left = Alr;
        if(Al->parent) {
            if(Al->parent->right == A)
            {
                Al->parent->right = Al;
            } else
            {
                Al->parent->left = Al;
            }
        }
        updateHeight(A);
        updateHeight(Al);
        updateHeight(Alr);
        return Al;
    }
    else if(balanceFactor==2 && leftChildBalanceFactor==-1)
    {
        //cout << "LR!";
        Node<Key,Value>* A = currentNode;
        Node<Key,Value>* Al = currentNode->left;
        Node<Key,Value>* Alr = currentNode->left->right;
        Node<Key,Value>* Alrr = currentNode->left->right->right; //can be null
        Node<Key,Value>* Alrl = currentNode->left->right->left; //can be null
        if(Alrr) Alrr->parent = A;
        Alr->parent = A->parent;
        A->parent = Alr;
        if(Alrl) Alrl->parent = Al;
        A->left = Alrr;
        Al->right = Alrl;
        Alr->left = Al;
        Alr->right = A;
        if(Alr->parent) {
            if(Alr->parent->right == A)
            {
                Alr->parent->right = Alr;
            } else
            {
                Alr->parent->left = Alr;
            }
        }
        updateHeight(A);
        updateHeight(Al);
        updateHeight(Alr);
        updateHeight(Alrr);
        updateHeight(Alrl);
        return Alr;
    }
    else if(balanceFactor==-2 && rightChildBalanceFactor<=0)
    {
        ///RR
        //cout << "RR!";
        Node<Key,Value>* A = currentNode;
        Node<Key,Value>* Ar = currentNode->right;
        Node<Key,Value>* Arl = currentNode->right->left; //can be null
        if(Arl) Arl->parent = A;
        Ar->parent = A->parent;
        Ar->left = A;
        A->parent = Ar;
        A->right = Arl;
        if(Ar->parent) {
            if(Ar->parent->right == A)
            {
                Ar->parent->right = Ar;
            } else
            {
                Ar->parent->left = Ar;
            }
        }

        updateHeight(A);
        updateHeight(Ar);
        updateHeight(Arl);
        return Ar;

    }
    else if(balanceFactor==-2 && rightChildBalanceFactor==1)
    {
        ///RL
        //cout << "RL!";
        Node<Key,Value>* A = currentNode;
        Node<Key,Value>* Ar = currentNode->right;
        Node<Key,Value>* Arl = currentNode->right->left;
        Node<Key,Value>* Arll = currentNode->right->left->left; //can be null
        Node<Key,Value>* Arlr = currentNode->right->left->right; //can be null
        if(Arll) Arll->parent = A;
        Arl->parent = A->parent;
        A->parent = Arl;
        if(Arlr) Arlr->parent = Ar;
        A->right = Arll;
        Ar->left = Arlr;
        Arl->right = Ar;
        Arl->left = A;
        if(Arl->parent) { //(now Arl is the root)
            if(Arl->parent->right == A)
            {
                Arl->parent->right = Arl;
            } else
            {
                Arl->parent->left = Arl;
            }
        }
        updateHeight(A);
        updateHeight(Ar);
        updateHeight(Arl);
        updateHeight(Arll);
        updateHeight(Arlr);
        return Arl;
    }

    return currentNode;
}


template<class Key, class Value>
Value* Tree<Key,Value>::remove(const Key& key)
{
        Node<Key,Value>* removedNode = removeNode(Root, key);
        Value* val = removedNode->value;
        delete removedNode;
        return val;
}

template<class Key, class Value>
Node<Key,Value>* Tree<Key,Value>::removeNode(Node<Key, Value> *currentNode, const Key &key)
{
    //cout<< "current: " << *currentNode->value<<"\n";
    if(currentNode == nullptr)
    {
        throw NodeDoesNotExist();
    }

    Node<Key, Value>* removedNode = currentNode;
    if(key == currentNode->key)
    {
        if(currentNode->left && !currentNode->right)
        {
            //cout<<"first";
            connectSonParent(currentNode,currentNode->left);
            currentNode = currentNode->parent; //now the root of current tree is the parent
        }

        else if(currentNode->right && !currentNode->left)
        {
            //cout<<"second";
            connectSonParent(currentNode,currentNode->right);
            currentNode = currentNode->parent;
        }
        else if(currentNode->right && currentNode->left)
        {
            //swap
            //cout<<"third";
            Key currentKey = currentNode->key;
            Value* currentValue = currentNode->value;
            currentNode->key = currentNode->next->key;
            currentNode->value = currentNode->next->value;
            currentNode->next->key = currentKey;
            currentNode->next->value = currentValue;
           // cout << "current node:" <<*currentNode->value;
           // this->print();
            removedNode = removeNode(currentNode->next,key);
           // currentNode = currentNode->prev;
          //  cout << "current node:" <<*currentNode->value;
        }
        else
        {
            //cout << "fouth!";
            if(currentNode->parent)
            {
                if(currentNode->parent->left == currentNode) currentNode->parent->left = nullptr;
                else currentNode->parent->right = nullptr;
            }
            if(currentNode->prev) currentNode->prev->next = currentNode->next;
            if(currentNode->next) currentNode->next->prev = currentNode->prev;
            currentNode = currentNode->parent;
        }
    }
    else if(key < currentNode->key)
    {
        removedNode = removeNode(currentNode->left,key);
    }
    else
    {
        removedNode = removeNode(currentNode->right,key);
    }

    updateHeight(currentNode);
    if(currentNode)
    {
        int rightChildBalanceFactor = getBalanceFactor(currentNode->right);
        int leftChildBalanceFactor = getBalanceFactor(currentNode->left);
        int balanceFactor = getBalanceFactor(currentNode);
        Node<Key,Value>* rotatedTree = getRotated(currentNode, rightChildBalanceFactor, leftChildBalanceFactor, balanceFactor);
        if(Root == currentNode)
        {
            Root = rotatedTree;
        }
    }
    return removedNode;
}

template<class Key, class Value>
void Tree<Key,Value>::connectSonParent(Node<Key, Value> *currentNode,Node<Key, Value> *son) {
    son->parent = currentNode->parent;
    if(currentNode->parent)
    {
        if(currentNode->parent->left == currentNode) currentNode->parent->left = son;
        else currentNode->parent->right = son;
    }
    if(son->next == currentNode) son->next = currentNode->next;
    if(son->prev == currentNode) son->prev = currentNode->prev;
    if(son->parent->next == currentNode) son->parent->next = currentNode->next;
    if(son->parent->prev == currentNode) son->parent->prev = currentNode->prev;
    updateHeight(son);
    updateHeight(son->parent);
}


#endif //HW1_TREE_H



