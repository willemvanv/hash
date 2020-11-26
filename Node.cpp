#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

Node::Node(char* NameFirst, char* NameLast, int Id, float Gpa) {
  gpa = Gpa;
  id = Id;
  nameFirst = new char[99];
  nameLast = new char[99];
  strcpy(nameFirst, NameFirst);
  strcpy(nameLast, NameLast);
  next = NULL;
}
Node::~Node() {
  delete &nameFirst;
  delete &nameLast;
  delete &id;
  delete &gpa;
  next = NULL;
}
int Node::getId() {
  return id;
}
void Node::setNext(Node* a) {
  next = a;
}
Node* Node::getNext() {
  return next;
}
void Node::printStudent() {
  cout << nameFirst << ' ' << nameLast << ", " << id << ", " << gpa << endl << endl;
}
