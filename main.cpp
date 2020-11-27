#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "Node.h"

using namespace std;

void Add(Node** hashTable, int* hash);
void Print(Node** hashTable, int hash);
void Remove(Node** hashTable, int hash);
void File(Node** hashTable, int hash, int* gen);

int main() {

  //Instructions
  cout << "Commands: add, print, quit, delete, file" << endl;

  //Variables
  int gen = 100000;
  int hash = 101;
  bool running = true;
  Node** hashTable;
  hashTable = new Node*[hash];
  for (int i = 0; i < 101; i++) {
    hashTable[i] = NULL;
    //hashTable[i]->getNext() = NULL;
    //hashTable[i]->getNext()->getNext() = NULL;
  }

  //Main loop
  while (running == true) {
    //Getting input
    char* input;
    input = new char[8];
    cout << "Enter a command" << endl;
    cin.getline(input, 8);
    
    if (input[0] == 'a' && input[1] == 'd' && input[2] == 'd') {
      Add(hashTable, &hash);
    }
    if (input[0] == 'p' && input[1] == 'r' && input[2] == 'i' && input[3] == 'n' &&
	input[4] == 't') {
      Print(hashTable, hash);
    }
    if (input[0] == 'q' && input[1] == 'u' && input[2] == 'i' && input[3] == 't') {
      running = false;
    }
    if (input[0] == 'd' && input[1] == 'e' && input[2] == 'l' && input[3] == 'e' &&
	input[4] == 't' && input[5] == 'e') {
      Remove(hashTable, hash);
    }
    if (input[0] == 'f' && input[1] == 'i' && input[2] == 'l' && input[3] == 'e') {
      File(hashTable, hash, &gen);
    }
  }
  return 0;
}

//Add fuction
void Add(Node** hashTable, int* hash) {
  int id;
  float gpa;
  char* nameFirst;
  char* nameLast;
  nameFirst = new char[99];
  nameLast = new char[99];
  //Gathering input
  cout << "Enter first name" << endl;
  cin.getline(nameFirst, 99);
  cout << "Enter last name" << endl;
  cin.getline(nameLast, 99);
  cout << "Enter id" << endl;
  cin >> id;
  cout << "Enter gpa" << endl;
  cin >> gpa;
  Node* student = new Node(nameFirst, nameLast, id, gpa);
  int b = id % *hash;
  //Add to hashTable or rehash if more than 3 collisions when chaining
  if (hashTable[b] == NULL) {
    hashTable[b] = student;
  }
  else {
    if (hashTable[b]->getNext() == NULL) {
      hashTable[b]->setNext(student);
    }
    else if (hashTable[b]->getNext()->getNext() == NULL) {
      hashTable[b]->getNext()->setNext(student);
    }
    //When more than 3 collisions in chaining, this else will rehash into a table double the size
    else {
      int oldHash = *hash;
      Node** temp;
      temp = new Node*[*hash];
      for (int i = 0; i < *hash; i++) {
	if (hashTable[i] != NULL) {
	  temp[i] = hashTable[i];
	  if (hashTable[i]->getNext() != NULL) {
	    temp[i]->setNext(hashTable[i]->getNext());
	    if (hashTable[i]->getNext()->getNext() != NULL) {
	      temp[i]->getNext()->setNext(hashTable[i]->getNext()->getNext());
	    }
	  }
	}
      }
      *hash = *hash * 2;
      hashTable = new Node*[*hash];
      for (int i = 0; i < oldHash; i++) {
	if (temp[i] != NULL) {
	  int place = temp[i]->getId() % *hash;
	  if (hashTable[place] == NULL) {
	      hashTable[place] = temp[i];
	  }
	  else {
	    if (hashTable[place]->getNext() == NULL) {
	      hashTable[place]->setNext(temp[i]);
	    }
	    else {
	      hashTable[place]->getNext()->setNext(temp[i]);
	    }
	  }
	  if (temp[i]->getNext() != NULL) {
	    place = temp[i]->getNext()->getId() % *hash;
	    if (hashTable[place] == NULL) {
	      hashTable[place] = temp[i];
	    }
	    else {
	      if (hashTable[place]->getNext() == NULL) {
		hashTable[place]->setNext(temp[i]);
	      }
	      else {
		hashTable[place]->getNext()->setNext(temp[i]);
	      }
	    }
	    if (temp[i]->getNext()->getNext() != NULL) {
	      place = temp[i]->getNext()->getNext()->getId() % *hash;
	      if (hashTable[place] == NULL) {
		hashTable[place] = temp[i];
	      }
	      else {
		if (hashTable[place]->getNext() == NULL) {
		  hashTable[place]->setNext(temp[i]);
		}
		else {
		  hashTable[place]->getNext()->setNext(temp[i]);
		}
	      }
	    }
	  }
	}
      }
    }
  }
}

void Print(Node** hashTable, int hash) {
  cout << endl;
  for (int i = 0; i < hash - 1; i++) {
    if (hashTable[i] != NULL) {
      hashTable[i]->printStudent();
      if (hashTable[i]->getNext() != NULL) {
	hashTable[i]->getNext()->printStudent();
	if (hashTable[i]->getNext()->getNext() != NULL) {
	  hashTable[i]->getNext()->getNext()->printStudent();
	}
      }
    }
  }
}

void Remove(Node** hashTable, int hash) {
  cout << "Enter id" << endl;
  int input;
  Node* temp;
  cin >> input;
  cout << endl;
  for (int i = 0; i < hash - 1; i++) {
    if (hashTable[i] != NULL) {
      if (hashTable[i]->getId() == input) {
	if (hashTable[i]->getNext() != NULL) {
	  temp = hashTable[i];
	  hashTable[i] = hashTable[i]->getNext();
	  temp->~Node();
	}
	else {
	  hashTable[i]->~Node();
	  hashTable[i] = NULL;
	}
      }
      else if (hashTable[i]->getNext() != NULL) {
	if (hashTable[i]->getNext()->getId() == input) {
	  if (hashTable[i]->getNext()->getNext() != NULL) {
	    temp = hashTable[i]->getNext()->getNext();
	    hashTable[i]->getNext()->~Node();
	    hashTable[i]->setNext(temp);
	  }
	  else {
	    hashTable[i]->getNext()->~Node();
	    hashTable[i]->setNext(NULL);
	  }
	}
	else if (hashTable[i]->getNext()->getNext() != NULL) {
	  if (hashTable[i]->getNext()->getNext()->getId() == input) {
	    hashTable[i]->getNext()->getNext()->~Node();
	    hashTable[i]->getNext()->setNext(NULL);
	  }
	}
      }   
    }
  }
}
void File(Node** hashTable, int hash, int* gen) {
  char* nameFirst;
  char* nameLast;
  nameFirst = new char[99];
  nameLast = new char[99];
  int d;
  int choice;
  float gpa;
  cout << "How many names would you like to generate?" << endl;
  cin >> d;
  cout << endl;
  for (int i = 0; i < d; i++) {
    fstream myfile;
    myfile.open("first.txt");
    choice = rand() % 15 + 1;
    for (int c = 0; c < choice; c++) {
      myfile.getline(nameFirst, 99, '\n');
    }
    myfile.close();
    fstream file("last.txt");
    choice = rand() % 15 + 1;
    for (int c = 0; c < choice; c++) {
      file.getline(nameLast, 99, '\n');
    }
    file.close();
    gpa = rand() % 4 + rand() % 10 * 0.1;
    hashTable[*gen % hash] = new Node(nameFirst, nameLast, *gen, gpa);
    *gen = *gen + 1;
  }
}
