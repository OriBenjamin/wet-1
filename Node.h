//
// Created by liels on 29/11/2022.
//

#ifndef HW1_NODE_H
#define HW1_NODE_H

#include <stdlib.h>
#include <memory>

const int INITIAL_HIGHT = 0;

template<class Key, class Value>
class Node
{
    public:
    Node<Key,Value>* right, *left;
    Node<Key,Value>* parent, *next, *prev;
    Key key;
    Value* value;
    int height;

    Node() = delete;
    Node(const Key& key, Value* value):
         right(nullptr), left(nullptr), prev(nullptr), next(nullptr), parent(nullptr),
         key(key), value(value), height(INITIAL_HIGHT){}
    ~Node() = default;
    Node(const Node& n) = delete;
    Node& operator=(const Node& n) = delete;
/*
    //const getters
    std::shared_ptr<Node<Key,Value>> getRight() const;
    std::shared_ptr<Node<Key,Value>> getLeft() const;
    std::shared_ptr<Node<Key,Value>> getParent() const;
    std::shared_ptr<Node<Key,Value>> getPrev() const;
    std::shared_ptr<Node<Key,Value>> getNext() const;
    Key getKey() const;
    Value getValue() const;

    //getters
    std::shared_ptr<Node<Key,Value>>& getfather();
    std::shared_ptr<Node<Key,Value>>& getright();
    std::shared_ptr<Node<Key,Value>>& getleft();
    std::shared_ptr<Node<Key,Value>>& getprivious();
    std::shared_ptr<Node<Key,Value>>& getnext();
    Key& getkey();
    Value& getvalue();

    //setters
    void setfather();
    void setright();
    void setleft();
    void setprivious();
    void setnext();
    void setkey();
    void setvalue();
*/
};


#endif //HW1_NODE_H
