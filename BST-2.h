// TODO: PRINT RANGE
#ifndef BST_2_H
#define BST_2_H

#include "Log.h"
#include "NodeT.h"
#include <iostream>
#include <queue>

enum Traversal { preorder, inorder, postorder, levelbylevel };

class BST {
public:
  BST();
  ~BST();
  bool search(Log data) const;
  void add(Log data);
  void remove(Log data);
  bool isEmpty() const;
  int getSize() const;
  // Actividad 3.1
  void print(Traversal t) const;
  int height() const;
  void ancestors(Log data) const;
  int whatLevelAmI(Log data) const;

  void preorderPrint(NodeT *node) const;
  void rangePrint(int range) const;
  void rangePrintHelper(NodeT *node, int) const;
  void inorderPrint(NodeT *node) const;
  void postorderPrint(NodeT *node) const;
  void levelByLevelPrint(NodeT *root) const;

  int heightHelper(NodeT *node) const;
  bool ancestorHelper(NodeT *node, Log data, bool &found) const;
  // Actividad 3.2
  int maxWidth() const;
  Log nearestRelative(Log data1, Log data2) const;
  BST(const BST &bst);
  bool operator==(const BST &bst) const;
  Log findNearestRelative(NodeT *current, Log data1, Log data2) const;

private:
  NodeT *root;
  int size;
  // funciones auxiliares
  void deleteBT(NodeT *node);
  int countChildren(NodeT *node) const;
  bool compareBST(NodeT *, NodeT *) const;
  NodeT *copyBST(NodeT *);
};

BST::BST() {
  root = nullptr;
  size = 0;
}

BST::~BST() { deleteBT(root); }

bool BST::search(Log data) const {
  NodeT *curr = root;
  // solo comparamos el primer numero de la ip
  while (curr != nullptr && curr->getIP()[0] != data.splittedIP[0])
    curr = (data.splittedIP[0] < curr->getIP()[0]) ? curr->getLeft()
                                                   : curr->getRight();
  return curr != nullptr;
}

void BST::add(Log data) {
  if (isEmpty())
    root = new NodeT(data);
  else {
    NodeT *parent = nullptr;
    NodeT *curr = root;
    do {
      // el dato ya existe
      // if (data.splittedIP[0] == curr->getIP()[0])
      //   return;
      parent = curr;
      std::vector<int> parentIP = parent->getIP();
      curr = (compareIP(data.splittedIP, parentIP)) ? curr->getLeft()
                                                    : curr->getRight();
    } while (curr != nullptr);
    std::vector<int> parentIP = parent->getIP();
    if (compareIP(data.splittedIP, parentIP)) {
      parent->setLeft(new NodeT(data));
      // agregamos un 1 al valor para tener la cuenta de cuantas veces aparece
      // este ip
      IPcount[data.splittedIP[0]] += 1;
    } else {
      parent->setRight(new NodeT(data));
      // agregamos un 1 al valor para tener la cuenta de cuantas veces aparece
      // este ip
      IPcount[data.splittedIP[0]] += 1;
    }
  }
  size++;
}

void BST::remove(Log data) {
  NodeT *parent = nullptr;
  NodeT *toRemove = root;
  while (toRemove != nullptr && data.splittedIP[0] != toRemove->getIP()[0]) {
    parent = toRemove;
    toRemove = (data.splittedIP[0] < parent->getIP()[0]) ? parent->getLeft()
                                                         : parent->getRight();
  }
  if (toRemove != nullptr) {
    int children = countChildren(toRemove);
    if (children == 0) { // caso 1: eliminar nodo hoja
      if (parent == nullptr)
        root = nullptr;
      else if (data.splittedIP[0] < parent->getIP()[0])
        parent->setLeft(nullptr);
      else
        parent->setRight(nullptr);
      delete toRemove;
      size--;
    } else if (children == 1) { // caso 1: eliminar nodo con un hijo
      NodeT *child = (toRemove->getLeft() != nullptr) ? toRemove->getLeft()
                                                      : toRemove->getRight();
      if (parent == nullptr)
        root = child;
      else if (data.splittedIP[0] < parent->getIP()[0])
        parent->setLeft(child);
      else
        parent->setRight(child);
      delete toRemove;
      size--;
    } else { // caso 3: eliminar nodo con dos hijos mediante el predecesor
      NodeT *predecessor = toRemove->getLeft();
      while (predecessor->getRight() != nullptr)
        predecessor = predecessor->getRight();
      Log predData = predecessor->getData();
      remove(predData);
      toRemove->setData(predData);
    }
  }
}

bool BST::isEmpty() const { return size == 0; }

int BST::getSize() const { return size; }

// Actividad 3.1

void BST::print(Traversal t) const {
  if (isEmpty()) {
    std::cout << " El arbol esta vacio " << std::endl;
    return;
  }

  switch (t) {
  case preorder:
    std::cout << "Recorrido en preorder: ";
    preorderPrint(root);
    break;
  case inorder:
    std::cout << "Recorrido en inOrder: ";
    inorderPrint(root);
    break;
  case postorder:
    std::cout << "Recorrido en Postorden: ";
    postorderPrint(root);
    break;
  case levelbylevel:
    std::cout << "Recorrido nivel por nivel: ";
    levelByLevelPrint(root);
    break;
  default:
    std::cout << "Tipo de recorrido no valido " << std::endl;
    return;
  }
  std::cout << std::endl;
}

void BST::preorderPrint(NodeT *node) const {
  if (node != nullptr) {
    node->getData().print();
    preorderPrint(node->getLeft());
    preorderPrint(node->getRight());
  }
}

void BST::rangePrint(int range) const {
  rangePrintHelper(root, range);
  return;
}

void BST::rangePrintHelper(NodeT *node, int range) const {
  if (node == nullptr)
    return;

  rangePrintHelper(node->getLeft(), range);

  if (node->getIP()[0] == range) {
    node->getData().print();
  }

  rangePrintHelper(node->getRight(), range);

  // if (range < node->getIP()[0]) {
  //   rangePrintHelper(node->getLeft(), range);
  // }
  //
  // if (range == node->getIP()[0]) {
  //   node->getData().print();
  //   rangePrintHelper(node->getRight(), range);
  // }
  //
  // if (range > node->getIP()[0]) {
  //   rangePrintHelper(node->getRight(), range);
  // }
  return;
}

void BST::inorderPrint(NodeT *node) const {
  if (node != nullptr) {
    inorderPrint(node->getLeft());
    node->getData().print();
    inorderPrint(node->getRight());
  }
}

void BST::postorderPrint(NodeT *node) const {
  if (node != nullptr) {
    postorderPrint(node->getLeft());
    postorderPrint(node->getRight());
    node->getData().print();
  }
}

void BST::levelByLevelPrint(NodeT *root) const {
  if (root == nullptr)
    return;
  std::queue<NodeT *> q;
  q.push(root);

  while (!q.empty()) {
    NodeT *curr = q.front();
    q.pop();
    curr->getData().print();

    if (curr->getLeft() != nullptr)
      q.push(curr->getLeft());

    if (curr->getRight() != nullptr)
      q.push(curr->getRight());
  }
}

int BST::height() const { return heightHelper(root); }

int BST::heightHelper(NodeT *node) const {
  if (node == nullptr) {
    return 0; // Devuelve 0 si el árbol está vacío
  }

  int leftHeight = heightHelper(node->getLeft());
  int rightHeight = heightHelper(node->getRight());

  // La altura del árbol es el máximo entre las alturas de sus subárboles
  // izquierdo y derecho, más 1 para contar la raíz
  return 1 + std::max(leftHeight, rightHeight);
}

// Actividad 3.2

// funcion que devuelve el maximo ancho del BST
// o(n)
// entrada: nada, salida: int
int BST::maxWidth() const {
  if (isEmpty()) {
    return 0;
  }

  int maxWidth = 0;

  std::queue<NodeT *> q;
  q.push(root);

  while (!q.empty()) {
    int levelSize = q.size();

    if (levelSize > maxWidth) {
      maxWidth = levelSize;
    }

    for (int i = 0; i < levelSize; i++) {
      NodeT *curr = q.front();
      q.pop();

      if (curr->getLeft() != nullptr) {
        q.push(curr->getLeft());
      }

      if (curr->getRight() != nullptr) {
        q.push(curr->getRight());
      }
    }
  }
  return maxWidth;
}

BST::BST(const BST &bst) { root = copyBST(bst.root); }

bool BST::operator==(const BST &otherBST) const {
  return compareBST(root, otherBST.root);
}

// FUNCIONES AUXILIARES

// borra el BST
// o(n)
// entrada: una referencia a un nodo, salida: nada
void BST::deleteBT(NodeT *node) {
  if (node != nullptr) {
    deleteBT(node->getLeft());
    deleteBT(node->getRight());
    delete node;
  }
}

// cuenta los hijos de un nodo
//  o(n)
//  entrada: referencia a un nodo, salida: entero
int BST::countChildren(NodeT *node) const {
  int children = 0;
  children += (node->getLeft() == nullptr) ? 0 : 1;
  children += (node->getRight() == nullptr) ? 0 : 1;
  return children;
}

// compara arboles, ayuda al operador ==
// o(n)
// entrada, dos nodos, salida: un valor booleano
bool BST::compareBST(NodeT *node, NodeT *otherNode) const {
  if (node == nullptr && otherNode == nullptr)
    return true;

  if (node->getIP()[0] == otherNode->getIP()[0]) {
    return compareBST(node->getLeft(), otherNode->getLeft()) &&
           compareBST(node->getRight(), otherNode->getRight());
  }
  return false;
}

// copia el BST, ayuda al copy constructor
// o(n)
// entrada: nodo, salida: nodo
NodeT *BST::copyBST(NodeT *node) {
  if (node == nullptr) {
    return nullptr;
  }

  NodeT *newNode = new NodeT(node->getData());

  newNode->setLeft(copyBST(node->getLeft()));
  newNode->setRight(copyBST(node->getRight()));

  return newNode;
}

#endif // BST_2_H
