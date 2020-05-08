#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <vector>
#include "Macros.h"
using namespace std;

template<typename T>
class BNode {
 public:
  typedef T value_t;
  typedef value_t *container_t;
  typedef BNode<value_t> **pcontainer_t;

  unsigned int order;
  container_t data;
  pcontainer_t children;
  size_t sizeOfContainer;
  bool leaf;

  BNode(unsigned int order = 4) : order(order) {
    this->data = new value_t[2 * order - 1];
    this->children = new BNode *[2 * order];
    this->sizeOfContainer = 0;
  }

  void split(int i) {
    auto z = new BNode(this->order);
    auto y = this->children[i];
    z->setLeaf(y->isLeaf());

    int index = this->order - 1;
    z->setN(index);
    for (int j = 0; j < index; ++j) {
      z->data[j] = y->data[j + this->order];
    }

    if (!y->isLeaf()) {
      for (int j = 0; j < this->order; ++j) {
        z->children[j] = y->children[j + this->order];
      }
    }

    y->setN(this->order - 1);

    for(int j = this->getN(); j >= i + 1; j--) {
      this->children[j + 1] = this->children[j];
    }

    this->children[i + 1] = z;

    for (int j = this->getN() - 1; j >= i; j--) {
      this->data[j + 1] = this->data[j];
    }

    this->data[i] = y->data[this->order - 1];
    this->setN(this->getN() + 1);
  }

  void insertNonFull(value_t key) {
    int i = this->getN() - 1;

    if (this->isLeaf()) {
      while (i >= 0 && key < this->data[i]) {
        this->data[i + 1] = this->data[i];
        i--;
      }

      this->data[i + 1] = key;
      this->setN(this->getN() + 1);
      return;
    }

    while (i >= 0 && key < this->data[i]) {
      i--;
    }

    if (this->children[i + 1]->getN() == 2 * this->order - 1) {
      this->split(i + 1);

      if (key > this->data[i + 1]) {
        i++;
      }
    }

    this->children[i + 1]->insertNonFull(key);
  }

  size_t getN() const {
    return this->sizeOfContainer;
  }

  void setN(size_t n) {
    this->sizeOfContainer = n;
  }

  bool isLeaf() const {
    return leaf;
  }

  void setLeaf(bool leaf) {
    BNode::leaf = leaf;
  }

  void traverse() {
    int i;

    for (i = 0; i < this->getN(); i++) {
      if (!this->isLeaf()) {
        this->children[i]->traverse();
      }

      if (&this->data[i] != nullptr) {
        std::cout << " " << this->data[i];
      }
    }

    if (!this->isLeaf()) {
      this->children[i]->traverse();
    }
  }

  ~BNode(void) {}
};

#endif
