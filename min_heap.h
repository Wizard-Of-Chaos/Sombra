#include <iostream>
#include <vector>

#ifndef MIN_HEAP_H
#define MIN_HEAP_H

class Node {
  public:
    int x;
    int y;
    double gscore;
    double fscore;
    Node* previous;
};

class MinHeap {
  private:
    std::vector<Node*> m_array;
  public:
    MinHeap();
    void add(Node* n);
    void remove(Node* n);
    Node* min();
    void pop();
    void print() const;
    int size() const;
};

#endif
