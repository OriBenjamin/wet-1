//
// Created by liels on 28/11/2022.
//

#ifndef HW1_TREE_H
#define HW1_TREE_H

#include <stdlib.h>
#include <string>
#include "Node.h"
#include <iostream>
#include <stdexcept>

const int INITIAL_SIZE_OF_TREE = 0;

class NodeAlreadyExist : public std::exception
{
    public:
    const char* what() const noexcept override {return "Node already exist in this tree";}
};
class NodeDoesNotExist : public std::exception
{
    public:
    const char* what() const noexcept override {return "Node does not exist in this tree";}
};
class OnlyOneNodeInTree : public std::exception
{
public:
    const char* what() const noexcept override {return "There is only one node in this tree";}
};

template<class Key, class Value>
class Tree
{
    private:
    Node<Key,Value>* root;
    int size;

    public:
    Tree():
    root(NULL), size(INITIAL_SIZE_OF_TREE) {}
    Tree(Node<Key,Value>* root, int size):
            root(root), size(size) {}
    Tree(const Tree<Key,Value>& tree) = default;
    ~Tree();
    void deleteTree(bool deleteValues);
    void deleteTreeNodes(Node<Key,Value>* node, bool deleteValues);
    Tree& operator=(const Tree& t) = default;

    //const getters
    Node<Key, Value> *getRoot() const {return root;}
    int getSize() const {return size;}


    //built-in functions
    Node<Key,Value>* insertNode(Node<Key,Value>* currentNode,Node<Key,Value>* nodeForInsertion);
    void insert(Key* key, Value* value);

    Value* remove(Key* key);
    Node<Key,Value>* removeNode(Node<Key,Value>* currentNode, Key* key);
    void balanceTree(Node<Key, Value>* currentNode);

    Value* find(Key* key) const;
    Node<Key,Value>* findNode(Node<Key,Value>* currentNode, Key* key) const;
    bool exists(Key* key) const;

    Node<Key,Value>* getFirstNode() const;
    Value* getLastNodeValue() const;

    int getBalanceFactor(const Node<Key,Value>* node) const;
    void connectSonParent(Node<Key, Value> *currentNode,Node<Key, Value> *son);


   // Node<Key,Value>* convertTreeToArray(const Node<Key,Value>* currentNode, Node<Key,Value>* nodesArray, int& currentNodeIndex);
   // Tree<Key,Value> sortArrayToTree(Node<Key,Value>** array, int newTreeSize, int start, int end, int arraySize, Node<Key,Value>* parent);


    //friend Tree<Key,Value> mergeTrees(Tree<Key,Value>& t1, Tree<Key,Value>& t2);
    Key* getClosestKey(Key* key) const;



    Node<Key, Value> *getRotated(Node<Key, Value> *currentNode, int rightChildBalanceFactor,
                                 int leftChildBalanceFactor, int balanceFactor);

    //Key getClosest(Key key);



    //what is that
    void print() const
    {
        printNode(root);
        //cout << *root->value;
    }
    //what is that
    void printNode(Node<Key,Value>* node) const//also... if yes move outside class
    {
        if(node == nullptr) return;
        printNode(node->left);
        std::cout << *node->value<<", ";
        printNode(node->right);
    }

    //what is that
    friend std::ostream &operator<<(std::ostream &os, const Tree &tree) {
        tree.print();
        return os;
    }

};


template<class Key, class Value>
void updateHeight(Node<Key,Value>* node)
{
    if(node != nullptr)
    {
        int leftHeight = (node->left) ? node->left->height : -1;
        int rightHeight = (node->right) ? node->right->height : -1;
        node->height = (leftHeight >= rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
}

template<class Key, class Value>
Key* Tree<Key,Value>::getClosestKey(Key* key) const
{
    Node<Key,Value>* node = findNode(root, key);
    if(!node->next && node->prev) return node->prev->key;
    if(node->next && !node->prev) return node->next->key;
    if(!node->next && !node->prev) throw OnlyOneNodeInTree();
    Key* nextNodeKey  = node->next->key;
    Key* prevNodeKey  = node->prev->key;
    return (*nextNodeKey > *prevNodeKey) ? nextNodeKey : prevNodeKey;
}

template<class Key, class Value>
Tree<Key,Value>::~Tree()
{
    deleteTree(true);
}

template<class Key, class Value>
void Tree<Key,Value>::deleteTree(bool deleteValues)
{
    deleteTreeNodes(root, deleteValues);
    root = nullptr;
}

template<class Key, class Value>
void Tree<Key,Value>::deleteTreeNodes(Node<Key,Value>* node, bool deleteValues)
{
    if(!node) return;
    if(node->right)
    {
        deleteTreeNodes(node->right, deleteValues);
        node->right = nullptr;
    }
    if(node->left)
    {
        deleteTreeNodes(node->left, deleteValues);
        node->left = nullptr;
    }

    if(deleteValues)
    {
        delete node->value;
        node->value = nullptr;
    }
    delete node;
    node = nullptr;
}
template<class Key, class Value>
void Tree<Key,Value>::insert(Key* key, Value* value)
{
    if(value == nullptr)
    {
        throw std::invalid_argument("invalid argument- cant insert an empty node");
    }
    Node<Key, Value> *nodeForInsertion = new Node<Key, Value>(key, value);
    root = insertNode(root, nodeForInsertion);
    if(nodeForInsertion->next)
    {
        nodeForInsertion->next->prev = nodeForInsertion;
    }
    if(nodeForInsertion->prev)
    {
        nodeForInsertion->prev->next = nodeForInsertion;
    }
    this->size++;
}

template<class Key, class Value>
int Tree<Key,Value>::getBalanceFactor(const Node<Key,Value>* node) const
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
    if(*nodeForInsertion->key == *currentNode->key)
    {
        throw NodeAlreadyExist();
    }
    else if(*nodeForInsertion->key < *currentNode->key)
    {
        if(!nodeForInsertion->next || *nodeForInsertion->next->key > *currentNode->key)
        {
            nodeForInsertion->next = currentNode;
        }
        currentNode->left = insertNode(currentNode->left, nodeForInsertion);
        currentNode->left->parent = currentNode;
    }
    else
    {
        if(!nodeForInsertion->prev || *nodeForInsertion->prev->key < *currentNode->key)
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
Node<Key, Value> * Tree<Key, Value>::getRotated(Node<Key, Value> *currentNode, int rightChildBalanceFactor, int leftChildBalanceFactor,
                             int balanceFactor)
 {
    if(balanceFactor == 2 && leftChildBalanceFactor > 0)
    {
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
        updateHeight(Alr);
        updateHeight(Al);
        return Al;
    }
    else if(balanceFactor==2 && leftChildBalanceFactor==-1)
    {
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
        Al->parent = Alr;
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
        updateHeight(Alrr);
        updateHeight(Alrl);
        updateHeight(A);
        updateHeight(Al);
        updateHeight(Alr);
        return Alr;
    }
    else if(balanceFactor==-2 && rightChildBalanceFactor<0)
    {
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
        updateHeight(Arl);
        updateHeight(Ar);
        return Ar;
    }
    else if(balanceFactor==-2 && rightChildBalanceFactor==1)
    {
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
        if(Arl->parent)
        { //(now Arl is the root)
            if(Arl->parent->right == A)
            {
                Arl->parent->right = Arl;
            }
            else
            {
                Arl->parent->left = Arl;
            }
        }
        updateHeight(Arll);
        updateHeight(Arlr);
        updateHeight(A);
        updateHeight(Ar);
        updateHeight(Arl);
        return Arl;
    }

    return currentNode;
}

template<class Key,class Value>
void Tree<Key, Value>::balanceTree(Node<Key, Value>* currentNode)
{
    if(currentNode)
    {
        updateHeight(currentNode);
        int rightChildBalanceFactor = getBalanceFactor(currentNode->right);
        int leftChildBalanceFactor = getBalanceFactor(currentNode->left);
        int balanceFactor = getBalanceFactor(currentNode);
        Node<Key, Value> *rotatedTree = getRotated(currentNode, rightChildBalanceFactor, leftChildBalanceFactor,
                                                   balanceFactor);
        if (root == currentNode) {
            root = rotatedTree;
        }

        balanceTree(currentNode->parent);
    }
}

template<class Key, class Value>
Value* Tree<Key,Value>::remove(Key* key)
{
    Node<Key,Value>* removedNode = removeNode(root, key);
    if(!removedNode->parent) root = nullptr;
    else if(!removedNode->parent->parent) root = removedNode->parent;
    balanceTree(removedNode->parent);
    Value* val = removedNode->value;
    delete removedNode;
    removedNode = nullptr;
    this->size--;
    return val;
}

template<class Key, class Value>
Node<Key,Value>* Tree<Key,Value>::removeNode(Node<Key, Value> *currentNode, Key* key)
{
    if(currentNode == nullptr)
    {
        throw NodeDoesNotExist();
    }
    //Node<Key, Value>* removedNode;
    if(*key == *currentNode->key)
    {
        if(currentNode->left && !currentNode->right)
        {
            connectSonParent(currentNode,currentNode->left);
            return currentNode;
            /*if(currentNode->parent) {
                currentNode = currentNode->parent; //now the root of current tree is the parent
            } else {
                currentNode = currentNode->left;
            }
            if(currentNode && !currentNode->parent)
            {
                root = currentNode;
            }
            removedNode = currentNode;*/
        }

        else if(currentNode->right && !currentNode->left)
        {
            connectSonParent(currentNode,currentNode->right);
            return currentNode;
            /*if(currentNode->parent) {
                currentNode = currentNode->parent; //now the root of current tree is the parent
            } else {
                currentNode = currentNode->right;
            }
            if(currentNode && !currentNode->parent)
            {
                root = currentNode;
            }
            removedNode = currentNode;*/
        }
        else if(currentNode->right && currentNode->left)
        {
            //swap
            Key* currentKey = currentNode->key;
            Value* currentValue = currentNode->value;
            currentNode->key = currentNode->next->key;
            currentNode->value = currentNode->next->value;
            currentNode->next->key = currentKey;
            currentNode->next->value = currentValue;
            return removeNode(currentNode->next, key);
        }
        else
        {
            if(currentNode->parent)
            {
                if(currentNode->parent->left == currentNode) currentNode->parent->left = nullptr;
                else currentNode->parent->right = nullptr;
            }
            if(currentNode->prev) currentNode->prev->next = currentNode->next;
            if(currentNode->next) currentNode->next->prev = currentNode->prev;
            return currentNode;
            /*currentNode = currentNode->parent;

            if(currentNode && !currentNode->parent)
            {
                root = currentNode;
            }*/
        }
    }
    else if(*key < *currentNode->key)
    {
        return removeNode(currentNode->left,key);
    }
    else
    {
        return removeNode(currentNode->right,key);
    }

   /* updateHeight(currentNode);

    if(currentNode)
    {
        int rightChildBalanceFactor = getBalanceFactor(currentNode->right);
        int leftChildBalanceFactor = getBalanceFactor(currentNode->left);
        int balanceFactor = getBalanceFactor(currentNode);
        Node<Key,Value>* rotatedTree = getRotated(currentNode, rightChildBalanceFactor, leftChildBalanceFactor, balanceFactor);
        if(root == currentNode)
        {
            root = rotatedTree;
        }
    }*/
    //return removedNode;
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
    if(son->parent) {
        if (son->parent->next == currentNode) son->parent->next = currentNode->next;
        if (son->parent->prev == currentNode) son->parent->prev = currentNode->prev;
    }
    updateHeight(son);
    updateHeight(son->parent);
}


template<class Key, class Value>
bool Tree<Key,Value>::exists(Key* key) const
{
    bool isExist = true;
    try
    {
        find(key);
    }
    catch(NodeDoesNotExist&)
    {
        isExist = false;
    }
    return isExist;
}

template<class Key, class Value>
Value* Tree<Key,Value>::find(Key* key) const
{
    return findNode(root, key)->value;
}

template<class Key, class Value>
Node<Key,Value>* Tree<Key,Value>::findNode(Node<Key,Value>* currentNode, Key* key) const
{
    if(currentNode == nullptr)
    {
        throw NodeDoesNotExist();
    }
    if(*currentNode->key == *key)
    {
        return currentNode;
    }
    else if(*key < *currentNode->key)
    {
        return findNode(currentNode->left, key);
    }
    else
    {
        return findNode(currentNode->right, key);
    }

}

template<class Key, class Value>
Node<Key,Value>* Tree<Key,Value>::getFirstNode() const
{
    Node<Key,Value>* currentNode = root;
    if(currentNode == nullptr)
    {
        throw NodeDoesNotExist(); //other error
    }
    while(currentNode->left)
    {
        currentNode = currentNode->left;
    }
    return currentNode;
}

template<class Key, class Value>
Value* Tree<Key,Value>::getLastNodeValue() const
{
    Node<Key,Value>* currentNode = root;
    if(currentNode == nullptr)
    {
        throw NodeDoesNotExist(); //other error
    }
    while(currentNode->right)
    {
        currentNode = currentNode->right;
    }
    return currentNode->value;
}



template<class Key, class Value>
void convertTreeToArray(const Node<Key,Value>* currentNode, Node<Key,Value>* nodesArray, int& currentNodeIndex)
{
    if(currentNode == nullptr)
    {
        return;
    }
    convertTreeToArray(currentNode->left, nodesArray, currentNodeIndex);
    nodesArray[currentNodeIndex++] = *currentNode;
    convertTreeToArray(currentNode->right, nodesArray, currentNodeIndex);
}

template<class Key, class Value>
void convertTreeToPointersArray(Node<Key,Value>* currentNode, Node<Key,Value>** nodesArray, int& currentNodeIndex)
{
    if(currentNode == NULL)
    {
        return;
    }
    convertTreeToPointersArray(currentNode->left, nodesArray, currentNodeIndex);
    nodesArray[currentNodeIndex++] = currentNode;
    convertTreeToPointersArray(currentNode->right, nodesArray, currentNodeIndex);
}


template<class Key, class Value>
Node<Key,Value>* sortArrayToTree(Node<Key,Value>** array, int start, int end, int arraySize, Node<Key,Value>* parent)
{
    if(start > end)
    {
        return nullptr;
    }
    int middle = (start + end)/2;
    Node<Key,Value>* subRoot = new Node<Key,Value>(**(array+middle)); //allocation!
    if(parent == *array)
    {
        subRoot->parent = nullptr;
    }
    else
    {
        subRoot->parent = parent; //parent!
    }
    subRoot->left = sortArrayToTree(array, start, middle-1, arraySize, subRoot);
    subRoot->right = sortArrayToTree(array, middle+1, end, arraySize, subRoot);
    updateHeight(subRoot);
    return subRoot;
}

template<class Key, class Value>
void updateNextAndPrev(Node<Key,Value>* currentNode, int size, Node<Key,Value>* *nodesArray) //O(n)
{
    int currentNodeIndex = 0;
    convertTreeToPointersArray(currentNode, nodesArray, currentNodeIndex);
    for(int i=0; i<size; i++)
    {
        if(i<=0)
        {
            nodesArray[i]->prev = nullptr;
        } else
        {
            nodesArray[i]->prev = nodesArray[i-1];
        }
        if(i>=size-1)
        {
            nodesArray[i]->next = nullptr;
        } else
        {
            nodesArray[i]->next = nodesArray[i+1];
        }
    }
}

template<class Key, class Value>
Tree<Key,Value> mergeTrees(Tree<Key,Value>& t1, Tree<Key,Value>& t2)
{
    Node<Key,Value>* *t1_array = new Node<Key,Value>*[t1.getSize()];
    Node<Key,Value>* *t2_array = new Node<Key,Value>*[t2.getSize()];
    Node<Key,Value>* *mergedArray = new Node<Key,Value>*[t1.getSize()+t2.getSize()];
    int currentNodeIndex = 0;
    convertTreeToPointersArray(t1.getRoot(), t1_array, currentNodeIndex);
    currentNodeIndex = 0;
    convertTreeToPointersArray(t2.getRoot(), t2_array, currentNodeIndex);
    mergeSortWithAVLTree(mergedArray, t1.getSize(),t2.getSize(), t1_array, t2_array);
    delete[] t1_array;
    delete[] t2_array;
    int start = 0, end = t1.getSize()+t2.getSize() -1;
    Node<Key,Value>* subRoot = sortArrayToTree(mergedArray, start, end,t1.getSize()+t2.getSize(),*mergedArray);
    Node<Key,Value>* *nodesArray = new Node<Key,Value>*[t1.getSize()+t2.getSize()];
    updateNextAndPrev(subRoot, t1.getSize()+t2.getSize(), nodesArray);
    delete[] nodesArray;
    delete[] mergedArray;
    return Tree<Key,Value>(subRoot, t1.getSize()+t2.getSize() -1) ;
}

#endif //HW1_TREE_H



