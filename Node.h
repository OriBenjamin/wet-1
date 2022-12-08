//
// Created by liels on 29/11/2022.
//

#ifndef wet_1_NODE_H
#define wet_1_NODE_H

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
        right(nullptr), left(nullptr), prev(nullptr), next(nullptr), parent(nullptr),
        key(NULL), value(nullptr), height(INITIAL_HEIGHT){}

template<class Key, class Value>
Node<Key,Value>::Node(const Key& key, Value* value):
        right(nullptr), left(nullptr), prev(nullptr), next(nullptr), parent(nullptr),
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
void mergeSortWithAVLTree(Node<Key,Value>* mergedArray, int mergedArraySize, Node<Key,Value>* t1_array, Node<Key,Value>* t2_array)
{
    if(mergedArray == nullptr || t1_array == nullptr || t1_array == nullptr || mergedArraySize < 1)
    {
        throw std::invalid_argument("invalid argument- cant merge arrays");
    }
    Tree<Node<Key,Value>, Node<Key,Value>> treeOfPointers = Tree<Node<Key,Value>,Node<Key,Value>>();
    treeOfPointers.insert(*t1_array, t1_array);
    treeOfPointers.insert(*t2_array, t2_array);
    for(int i=0; i<mergedArraySize; i++)
    {
        Node<Node<Key,Value>,Node<Key,Value>>* nodeToRemove = treeOfPointers.getFirstNode();
        mergedArray[i] = *(treeOfPointers.remove(nodeToRemove->key));
        nodeToRemove++;
        treeOfPointers.insert(*nodeToRemove->value, nodeToRemove->value);
    }

}
#endif //wet_1_NODE_H
