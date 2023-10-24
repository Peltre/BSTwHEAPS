#ifndef NODET_H
#define NODET_H
#include "Log.h"

class NodeT {
public:
  NodeT(Log data); // constructor
  Log getData();
  std::vector<int> getIP();
  NodeT *getLeft();
  NodeT *getRight();
  void setData(Log);
  void setLeft(NodeT *);
  void setRight(NodeT *);

private:
  Log data;
  NodeT *left;
  NodeT *right;
};

// constructor de nodos
NodeT::NodeT(Log data) {
  this->data = data;
  left = right = nullptr;
}

// constructor
Log NodeT::getData() { return data; }

std::vector<int> NodeT::getIP() { return data.splittedIP; }

// regresa apuntador del arbol izquierdo
NodeT *NodeT::getLeft() { return left; }

// regresa apuntador del arbol izquierdo
NodeT *NodeT::getRight() { return right; }

void NodeT::setData(Log data) { this->data = data; }

void NodeT::setLeft(NodeT *left) { this->left = left; }

void NodeT::setRight(NodeT *right) { this->right = right; }

#endif
