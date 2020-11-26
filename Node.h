#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;

class Node {
 public:
  Node(char* NameFirst, char* NameLast, int Id, float Gpa);
  ~Node();
  int getId();
  void setNext(Node* a);
  Node* getNext();
  void printStudent();

 private:
  Node* next;
  char* nameFirst;
  char* nameLast;
  int id;
  float gpa;
};
#endif
