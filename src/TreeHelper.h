#ifndef TREE_HELPER_H
#define TREE_HELPER_H

#include <iostream>
#include "BNode.h"
#include "BPlusNode.h"
#include "BSTNode.h"
using namespace std;

template<typename Node, typename ValueNode, int Flag>
struct TreeHelper {
  typedef Node node_t;
  typedef typename node_t::value_t value_t;

  static void insert(node_t **head, const value_t &val, unsigned int order) {
    cout << "el tipo de dato no es compatible" << endl;
  }

  static void print(node_t **head, std::ostream &out) {
  }
};

template<typename ValueNode>
struct TreeHelper<BSTNode<ValueNode>, ValueNode, BST_NODE_FLAGXX> {
  typedef BSTNode<ValueNode> node_t;
  typedef typename node_t::value_t value_t;

  static void insert(node_t **head, const value_t &val, unsigned int order) {
    auto temp = new node_t(val);

    if ((*head) == nullptr) {
      (*head) = temp;
      return;
    }

    if ((*head)->data > val) {
      insert(&(*head)->children[0], val, order);
      return;
    }

    if ((*head)->data < val) {
      insert(&(*head)->children[1], val, order);
      return;
    }
    cout << "Duplicates not allowed" << endl;
  }

  //BST Print
  static void print(node_t **head, std::ostream &out) {
    std::stack<node_t *> nodes;
    node_t *curr = *head;

    while (curr) {
      out << "Node: " << curr->data << endl;
      if (curr->children[1]) {
        nodes.push(curr->children[1]);
      }
      if (curr->children[0]) {
        curr = curr->children[0];
      } else {
        if (!nodes.empty()) {
          curr = nodes.top();
          nodes.pop();
        } else {
          curr = nullptr;
        }
      }
    }
  }
};

template<typename ValueNode>
struct TreeHelper<BNode<ValueNode>, ValueNode, B_NODE_FLAGXX> {
  typedef BNode<ValueNode> node_t;
  typedef typename node_t::value_t value_t;

  static void insert(node_t **head, const value_t &val, unsigned int order) {
    if (!(*head)) {
      (*head) = new node_t(order);
      (*head)->data[0] = val;
      (*head)->setN(1);
      (*head)->setLeaf(true);
      return;
    }

    if ((*head)->getN() != 2 * order - 1) {
      (*head)->insertNonFull(val);
      return;
    }

    auto s = new BNode<ValueNode>(order);
    s->setLeaf(false);
    s->children[0] = (*head);
    s->split(0);
    s->insertNonFull(val);
    (*head) = s;
  }

  static void print(node_t **head, std::ostream &out) {
    (*head)->traverse();
  }
};

#endif