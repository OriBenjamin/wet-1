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
    Key* key;
    Value* value;
    int height;

    Node();
    Node(Key* key, Value* value);
    ~Node() = default;
    Node(const Node& n) = default;
    Node& operator=(const Node& n) = default;
    bool operator<(const Node<Key,Value>& node) const;

    //const getters
    Key getKey() const;
};


template<class Key, class Value>
Node<Key,Value>::Node():
        right(nullptr), left(nullptr), parent(nullptr), next(nullptr), prev(nullptr),
        key(nullptr), value(nullptr), height(INITIAL_HEIGHT){}

template<class Key, class Value>
Node<Key,Value>::Node(Key* key, Value* value):
        right(nullptr), left(nullptr), parent(nullptr), next(nullptr), prev(nullptr),
        key(key), value(value), height(INITIAL_HEIGHT){}

template<class Key, class Value>
bool Node<Key,Value>::operator<(const Node<Key,Value>& node) const
{
    if(*key < *node.key)
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
void mergeSort(Node<Key,Value>** mergedArray, int t1_size, int t2_size, Node<Key,Value>** t1_array, Node<Key,Value>** t2_array)
{
        int a = 0, b = 0, c = 0;

        while (a < t1_size && b < t2_size)
        {
            if (*t1_array[a] < *t2_array[b])
                mergedArray[c++] = t1_array[a++];
            else
                mergedArray[c++] = t2_array[b++];
        }
        while (a < t1_size)
        {
            mergedArray[c++] = t1_array[a++];
        }
        while (b < t2_size)
        {
            mergedArray[c++] = t2_array[b++];
        }
}


template<class Key, class Value>
Key Node<Key, Value>::getKey() const
{
    return *key;
}
#endif //wet_1_NODE_H
