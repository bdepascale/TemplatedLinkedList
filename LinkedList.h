#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

template <typename T> class LinkedList {
public:
  struct Node {

    T data;
    Node *next;
    Node *prev;
  };

  Node *head = nullptr;
  Node *tail = nullptr;
  Node *temp;
  Node *curr;
  unsigned int numNodes = 0;

  LinkedList();
  LinkedList(const LinkedList<T> &list);
  ~LinkedList();

  //***************************************************Add/Delete****
  void AddHead(const T &data);
  void AddTail(const T &data);
  void deleteNode(T delData);
  unsigned int Remove(const T &data);
  bool RemoveHead();
  bool RemoveTail();
  bool RemoveAt(int index);
  void AddNodesHead(const T *data, unsigned int count);
  void AddNodesTail(const T *data, unsigned int count);
  void InsertAfter(Node *node, const T &data);
  void InsertBefore(Node *node, const T &data);
  void InsertAt(const T &data, unsigned int index);
  void Clear();
  //************************************************Prints*******
  void PrintForward() const;
  void PrintForwardRecursive(const Node *node) const;
  void PrintReverseRecursive(const Node *node) const;
  void PrintReverse() const;
  //*************************************************Finds********
  void FindAll(vector<Node *> &outData, const T &value) const;
  Node *Find(const T &data);
  const Node *Find(const T &data) const;
  Node *Head();
  Node *Head() const;
  Node *Tail();
  Node *Tail() const;
  Node *GetNode(unsigned int index);
  const Node *GetNode(unsigned int index) const;
  //**********************************************************************
  unsigned int NodeCount() const;
  //****************************************************operators*********
  const T &operator[](unsigned int index) const;
  T &operator[](unsigned int index);
  bool operator==(const LinkedList<T> &rhs) const;
  LinkedList<T> &operator=(const LinkedList<T> &rhs);
};
template <typename T> LinkedList<T>::LinkedList(const LinkedList<T> &list) {

  Node *xfer = list.head;
  while (xfer != nullptr) {
    AddTail(xfer->data);
    xfer = xfer->next;
  }
}
template <typename T> LinkedList<T>::LinkedList() {
  head = nullptr;
  tail = nullptr;
  temp = nullptr;
  curr = nullptr;
  numNodes = 0;
}
template <typename T> LinkedList<T>::~LinkedList() {
  while (head != nullptr) {
    RemoveHead();
  }
}
//***************************************************Add/Delete****
template <typename T> void LinkedList<T>::AddHead(const T &data) {
  Node *n = new Node;
  n->next = nullptr;
  n->prev = nullptr;
  n->data = data;

  if (head != nullptr) {
    curr = head;
    curr->prev = n;
    n->next = curr;
    head = n;

  } else {
    head = n;
    tail = n;
  }
  numNodes++;
}
template <typename T> void LinkedList<T>::AddTail(const T &data) {
  Node *n = new Node;
  n->next = nullptr;
  n->prev = nullptr;
  n->data = data;

  if (tail != nullptr) {
    curr = tail;
    curr->next = n;
    n->prev = curr;
    n->next = nullptr;
    tail = n;

  } else {
    head = n;
    tail = n;
  }
  numNodes++;
}

template <typename T> void LinkedList<T>::deleteNode(T delData) {
  Node *delptr = nullptr;
  temp = head;
  curr = head;
  while (curr != nullptr && curr->data != delData) {
    temp = curr;
    curr = curr->next;
  }
  if (curr == nullptr) {
    cout << "data not found" << endl;
    delete delptr;
  } else {
    delptr = curr;
    curr = curr->next;
    temp->next = curr;
    delete delptr;
    cout << "value deleted" << endl;
    numNodes--;
  }
}
template <typename T> unsigned int LinkedList<T>::Remove(const T &data) {
  Node *delptr = nullptr;
  temp = head;
  curr = head;
  unsigned int nodes = numNodes;
  unsigned int numRemoved = 0;

  for (unsigned int i = 0; i < nodes; i++) {
    if (curr->data == data) {
      delptr = curr;
      curr = curr->next;
      temp->next = curr;
      curr->prev = temp;
      delete delptr;
      numNodes--;
      numRemoved++;
    } else {
      temp = curr;
      curr = curr->next;
    }
  }
  return numRemoved;
  delete delptr;
}
template <typename T> bool LinkedList<T>::RemoveHead() {

  if (numNodes > 1) {
    Node *delptr = head;
    curr = head->next;
    curr->prev = nullptr;
    head = curr;
    numNodes--;
    delete delptr;
    return true;
  } else if (numNodes == 1) {
    Node *delptr = head;
    delete delptr;
    head = nullptr;
    tail = nullptr;
    curr = nullptr;
    numNodes--;

    return true;

  } else {
    return false;
  }
}
template <typename T> bool LinkedList<T>::RemoveTail() {
  if (numNodes > 1) {
    Node *delptr = tail;
    curr = tail->prev;
    curr->next = nullptr;
    tail = curr;
    numNodes--;
    delete delptr;
    return true;
  } else if (numNodes == 1) {
    Node *delptr = head;
    delete delptr;
    head = nullptr;
    tail = nullptr;
    curr = nullptr;
    numNodes--;

    return true;
  } else {
    return false;
  }
}
template <typename T> bool LinkedList<T>::RemoveAt(int index) {

  if (index <= int(NodeCount())) {
    temp = head;
    for (int i = 1; i <= index; i++) {
      temp = temp->next;
    }
    Node *delptr = temp;
    curr = temp->next;
    curr->prev = temp->prev;
    temp = temp->prev;
    temp->next = curr;
    delete delptr;
    numNodes--;
    return true;
  } else {
    return false;
  }
}
template <typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count) {
  for (int i = int(count) - 1; i > -1; i--) {
    AddHead(data[i]);
  }
}
template <typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count) {
  for (unsigned int i = 0; i < count; i++) {
    AddTail(data[i]);
  }
}
template <typename T>
void LinkedList<T>::InsertAfter(Node *node, const T &data) {
  Node *n = new Node;
  n->data = data;
  curr = node;
  temp = curr->next;
  curr->next = n;
  temp->prev = n;
  n->next = temp;
  n->prev = curr;
  numNodes++;
}
template <typename T>
void LinkedList<T>::InsertBefore(Node *node, const T &data) {
  Node *n = new Node;
  n->data = data;
  curr = node;
  temp = curr->prev;
  curr->prev = n;
  temp->next = n;
  n->prev = temp;
  n->next = curr;
  numNodes++;
}
template <typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) {
  if (index <= numNodes) {
    if (index == 0) {
      AddHead(data);

    } else if (index == (numNodes)) {
      AddTail(data);

    } else {
      curr = head;
      Node *n = new Node;
      n->data = data;
      for (unsigned int i = 0; i < index; i++) {
        curr = curr->next;
      }
      temp = curr->prev;
      temp->next = n;
      n->prev = temp;
      n->next = curr;
      curr->prev = n;
      numNodes++;
    }

  } else {
    throw exception();
  }
}
template <typename T> void LinkedList<T>::Clear() {
  while (head != nullptr) {
    RemoveHead();
  }
}
//************************************************Prints*******
template <typename T> void LinkedList<T>::PrintForward() const {
  Node *print = head;

  while (print != nullptr) {
    cout << print->data << endl;
    print = print->next;
  }
  delete print;
}
template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node *node) const {

  if (node != nullptr) {
    cout << node->data << endl;
    PrintForwardRecursive(node->next);
  }
}
template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node *node) const {

  if (node != nullptr) {
    cout << node->data << endl;
    PrintReverseRecursive(node->prev);
  }
}
template <typename T> void LinkedList<T>::PrintReverse() const {
  Node *print = tail;

  while (print != nullptr) {
    cout << print->data << endl;
    print = print->prev;
  }
  delete print;
}

template <typename T> unsigned int LinkedList<T>::NodeCount() const {
  return numNodes;
}

//***********************************************************Finds**********
template <typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T &value) const {

  Node *search = head;
  for (unsigned int i = 0; i < numNodes; i++) {
    if (search->data == value) {
      outData.push_back(search);
      search = search->next;
    } else {
      search = search->next;
    }
  }
  delete search;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) {
  Node *search = head;
  for (unsigned int i = 1; i <= numNodes; i++) {
    if (search->data == data) {
      return search;
    } else {
      search = search->next;
    }
  }
  delete search;
  return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) const {
  Node *search = head;
  for (unsigned int i = 1; i <= numNodes; i++) {
    if (search->data == data) {
      return search;
    } else {
      search = search->next;
    }
  }
  delete search;
  return nullptr;
}

template <typename T> typename LinkedList<T>::Node *LinkedList<T>::Head() {

  return head;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::Head() const {

  return head;
}
template <typename T> typename LinkedList<T>::Node *LinkedList<T>::Tail() {

  return tail;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::Tail() const {

  return tail;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) {
  Node *get = head;
  if (index <= numNodes) {
    for (unsigned int i = 1; i <= index; i++) {
      get = get->next;
    }
    return get;
  } else {
    throw exception();
  }
  delete get;
}

template <typename T>
const typename LinkedList<T>::Node *
LinkedList<T>::GetNode(unsigned int index) const {
  Node *get = head;
  if (index <= numNodes) {
    for (unsigned int i = 1; i <= index; i++) {
      get = get->next;
    }
    return get;
  } else {
    throw exception();
  }
  delete get;
}
//*****************************************************************
//*************************************************************operators**
template <typename T> T &LinkedList<T>::operator[](unsigned int index) {
  if (index <= NodeCount()) {
    temp = head;
    for (unsigned int i = 1; i <= index; i++) {
      temp = temp->next;
    }
    return temp->data;
  } else {
    throw exception();
  }
}
template <typename T>
const T &LinkedList<T>::operator[](unsigned int index) const {
  if (index <= NodeCount()) {
    temp = head;
    for (unsigned int i = 1; i <= index; i++) {
      temp = temp->next;
    }
    return temp->data;
  } else {
    throw exception();
  }
}
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const {
  Node *testL = head;
  Node *testR = rhs.head;
  bool rv = false;
  for (unsigned int i = 0; i < numNodes; i++) {
    if (testL->data == testR->data && numNodes == rhs.numNodes) {
      testL = testL->next;
      testR = testR->next;
      rv = true;
    } else {
      rv = false;
    }
  }
  return rv;
}
template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
  Clear();
  Node *xfer = rhs.head;
  while (xfer != nullptr) {
    AddTail(xfer->data);
    xfer = xfer->next;
  }
  return *this;
}
