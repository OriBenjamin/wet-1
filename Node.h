//
// Created by liels on 29/11/2022.
//

#ifndef wet_1_NODE_H
#define wet_1_NODE_H
#include <iostream>
#include <stdlib.h>
#include <memory>
template<class Key, class Value>
class Tree;

const int INITIAL_HEIGHT = 0;

template<class Key, class Value>
class Node
{
    public:
    Node<Key,Value>* right, *left, *parent, *next, *prev;
    Key key;
    Value* value;
    int height;

    Node();
    Node(const Key& key, Value* value);
    ~Node() = default;
    Node(const Node& n) = default;
    Node& operator=(const Node& n) = default;
    bool operator<(const Node<Key,Value>& node) const;

};


template<class Key, class Value>
Node<Key,Value>::Node():
        right(nullptr), left(nullptr), parent(nullptr), next(nullptr), prev(nullptr),
        key(), value(nullptr), height(INITIAL_HEIGHT){}
//no default!
template<class Key, class Value>
Node<Key,Value>::Node(const Key& key, Value* value):
        right(nullptr), left(nullptr), parent(nullptr), next(nullptr), prev(nullptr),
        key(key), value(value), height(INITIAL_HEIGHT){}

template<class Key, class Value>
bool Node<Key,Value>::operator<(const Node<Key,Value>& node) const
{
    if(key < node.key)
    {
        return true;
    }
    return false;
}


template<class Key, class Value>
bool operator==(const Node<Key,Value>& node1, const Node<Key,Value>& node2)
{
    if(!(node1 < node2) && !(node2 < node1))
    {
        return true;
    }
    return false;
}

template<class Key, class Value>
bool operator>(const Node<Key,Value>& node1, const Node<Key,Value>& node2)
{
    if(!(node1 == node2) && !(node1 < node2))
    {
        return true;
    }
    return false;
}

template<class Key, class Value>
void mergeSortWithAVLTree(Node<Key,Value>* mergedArray, int t1_size, int t2_size, Node<Key,Value>* t1_array, Node<Key,Value>* t2_array)
{
   /* if(mergedArray == nullptr || t1_array == nullptr || t1_array == nullptr || mergedArraySize < 1)
    {
        throw std::invalid_argument("invalid argument- cant merge arrays");
    }
    Tree<Node<Key,Value>, Node<Key,Value>> treeOfPointers = Tree<Node<Key,Value>,Node<Key,Value>>();
    treeOfPointers.insert(*t1_array, t1_array);
    treeOfPointers.insert(*t2_array, t2_array);
    for(int i=0; i<mergedArraySize; i++)
    {
        Node<Node<Key,Value>,Node<Key,Value>>* nodeToRemove = treeOfPointers.getFirstNode();
        mergedArray[i] = *(treeOfPointers.removeNode(treeOfPointers.getRoot(),nodeToRemove->key)->value);
        t1_array++;
        treeOfPointers.insert(*t1_array, t1_array);

    }*/


        int i = 0, j = 0, k = 0;

        // Traverse both array
        while (i<t1_size && j <t2_size)
        {
            // Check if current element of first
            // array is smaller than current element
            // of second array. If yes, store first
            // array element and increment first array
            // index. Otherwise do same with second array
            if (t1_array[i] < t2_array[j])
                mergedArray[k++] = t1_array[i++];
            else
                mergedArray[k++] = t2_array[j++];
        }

        // Store remaining elements of first array
        while (i < t1_size)
            mergedArray[k++] = t1_array[i++];

        // Store remaining elements of second array
        while (j < t2_size)
            mergedArray[k++] = t2_array[j++];



}
#endif //wet_1_NODE_H
