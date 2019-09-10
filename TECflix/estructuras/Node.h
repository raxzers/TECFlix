//
// Created by conejo on 9/9/19.
//

#ifndef TECFLIX_NODE_H
#define TECFLIX_NODE_H
template <class T>
class Node {
private:
    T data;
    Node<T> *next;

public:
    Node(T data) {
        Node::data = data;
        next = nullptr;
    }

    void setData(T data) {
        Node::data = data;
    }

    T getData() {
        return data;
    }

    void setNext(Node *next) {
        Node::next = next;
    }

    Node* getNext() {
        return next;
    }
};
#endif //TECFLIX_NODE_H
