#include <iostream>
#include <vector>
#include <stack>
#include <time.h>
#include <chrono>
#include <stdio.h>
#include <unistd.h>

#include "Tree.h"

int main() {
  typedef BNode<int> b_node;

  typedef Tree<b_node> b_tree;

  b_tree btree(2);

  btree.insert(5);
  btree.insert(3);
  btree.insert(21);
  btree.insert(9);
  btree.insert(1);
  btree.insert(13);
  btree.insert(2);
  btree.insert(7);
  btree.insert(10);
  btree.insert(12);
  btree.insert(4);
  btree.insert(8);

  cout << btree << endl;
}
