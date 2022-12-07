//
// Created by liels on 29/11/2022.
//

#ifndef wet_1_NODE_H
#define wet_1_NODE_H

#include <stdlib.h>
#include <memory>

const int INITIAL_HEIGHT = 0;

template<class Key, class Value>
class Node
{
    public:
    Node<Key,Value>* right, *left, *parent, *next, *prev;
    Key key;
    Value* value;
    int height;

    Node() = delete;
    Node(const Key& key, Value* value):
         right(nullptr), left(nullptr), prev(nullptr), next(nullptr), parent(nullptr),
         key(key), value(value), height(INITIAL_HEIGHT){}
    ~Node() = default;
    Node(const Node& n) = delete;
    Node& operator=(const Node& n) = delete;


};


#endif //wet_1_NODE_H
