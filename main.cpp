/*
  Linked Lists part 2 - this is a Student List concept with the use of linked lists (no vectors)
    by Stefan Ene, base Node.o code of Andrew T.
    Works Cited: ADD function method done with help from Omar Nassar
                 delete function inpired of an online method tree, could not find link again
*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include "Node.h"
#include "Student.h"

using namespace std;

//functions
void ADD (Node* &head, Node* prev, Student* stud);
void PRINT (Node* head);
void AVERAGE(Node* next, int counter);
void DELETE(Node* &head, Node* next, Node* prev, char lname[]);
void PrintStud(Node* current);

int main () {
  //varaibles
  bool run = true;
  char input[10];
  Node* head = NULL;  //first node
  int counter = 0;  //number of nodes
  //begin program
  cout << "----------------------------------------------------------------------" << endl;
  cout << "Welcome to Stefan's Linked Lists Pt2, based on Andrew T.\'s code." << endl;
  //program
  while (run) {
    cout << endl << "Five functions: ADD, PRINT, DELETE, AVERAGE, QUIT." << endl;;
    cout << "Input one of these:" << endl;
    cin.get(input, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    //if input is add
    if (strcmp(input, "add") == 0) {
      counter++;
      Student* newStud = new Student();
      //add student specifications
      cout << "=============ADD=============" << endl;
      cout << "Input student\'s first name:" << endl;
      cin.get(newStud->getFirst(), 30);
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "Input student\'s last name:" << endl;
      cin.get(newStud->getLast(), 30);
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "Input student\'s ID:" << endl;
      cin >> *newStud->getId();
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "Input student\'s GPA:" << endl;
      cin >> *newStud->getGpa();
      cin.clear();
      cin.ignore(10000, '\n');
      ADD(head, head, newStud);
      cout << "=======Student=Added=========" << endl;
    }
    //is input is print
    else if (strcmp(input, "print") == 0) {
      PRINT(head);
    }
    //if input is delete
    else if (strcmp(input, "delete") == 0) {
      if (head == NULL) {
	cout << endl << "Empty list. No Students to delete." << endl;
      }
      else {
	char in[30];
	cout << endl << "What student would you like to delete? Give last name:" << endl;
	cin.get(in, 30);
	cin.clear();
	cin.ignore(10000, '\n');
	DELETE(head, head, NULL, in);
      }
    }
    //if input is average
    else if (strcmp(input, "average") == 0) {
      AVERAGE(head, counter);
    }
    //if input is quit
    else if (strcmp(input, "quit") == 0) {
      run = false;
      cout << endl << "Thank you for using the program." << endl;
    }
    //any other invalid input
    else {
      cout << endl <<  "Unknown commnad. Try again" << endl;
    }
  }
  //end program
  return 0;
}

//ADD funtion
void ADD (Node* &head, Node* prev, Student* stud) {
  if (head == NULL) {  //on first node
    head = new Node(stud);  //create first node
  }
  else if (prev->getNext() == NULL) {  //on second node
    if (*stud->getId() > *head->getStudent()->getId()) {
      Node* newNode = new Node(stud);
      prev->setNext(newNode);
    } else {
      Node* temp = new Node(head->getStudent());
      head = new Node(stud);
      head->setNext(temp);
    }
  }
  else if (*stud->getId() < *head->getStudent()->getId()) {  //new id < first id
    //swap first two nodes
    Node* temp =new Node(head->getStudent());
    temp->setNext(head->getNext());
    head = new Node(stud);
    head->setNext(temp);
    //PRINT(head);
  }
  else if (*stud->getId() < *prev->getNext()->getStudent()->getId()) {  //new id < current id
    //insert new node
    Node* newNode = new Node(stud);
    newNode->setNext(prev->getNext());  //next is prev->next
    prev->setNext(newNode);  //prev is newNode
    //PRINT(head);
  }
  else {
    ADD(head, prev->getNext(), stud);  //RECURSION - move to next node
  }
}

//PRINT function
void PRINT (Node* head) {
  Node* current = head;
  if(current == NULL) {
    cout << endl << "Student list empty. Add some students before printing." << endl;
  }
  else {
    cout << endl << "=============Student=List=============" << endl;
    do {
      cout << current->getStudent()->getFirst() << " ";
      cout << current->getStudent()->getLast() << ", ";
      cout << "ID " << *current->getStudent()->getId() << ", ";
      cout << "GPA " << fixed << setprecision(2) << *current->getStudent()->getGpa() << endl;
      current = current->getNext();
    } while (current != NULL);
    cout << "======================================" << endl; 
  }
}

//AVERTAGE function
void AVERAGE(Node* head, int counter) {
  Node* current = head;
  float total = 0;
  if(head == NULL) {  //if no nodes
    cout << endl << "Student list empty. Add some students before printing." << endl;
  }
  else {
    total += *current->getStudent()->getGpa();  //begin with first student
    while (current->getNext() != NULL) { //keep adding next GPAs
      total += *current->getNext()->getStudent()->getGpa();
      current = current->getNext();
    }
  }
  //cout << counter << "   " << total << endl;
  cout << endl << "======================================" << endl;
  cout << "The average GPA is " << fixed << setprecision(2) << (total/counter) << "." << endl;
  cout << "======================================" << endl;
}

//DELETE function
void DELETE(Node* &head, Node* next, Node* prev, char lname[]) {
  char yn; //for answer input
  if (next == head &&
      strcmp(lname, next->getStudent()->getLast()) == 0) {  //working with first node
    PrintStud(next);
    cout << "Would you like to delete this student? y or n:" << endl;
    cin >> yn;
    cin.clear();
    cin.ignore(10000, '\n');
    if (yn == 'y') {  //delete student/node
      cout << endl << "===========Student=Deleted============" << endl;
      if (head->getNext() == NULL) {
	//next->~Node();    for some reason, when deleting this, I'd get an 'Aborted (code dumped) error and could not find a workaround except for not deleting the pointers
	head = NULL;
      } else {
	head = next->getNext();
	//next->~Node();
	DELETE(head, head, NULL, lname);  //RECURSION
      }
    }
    else if (yn == 'n') {
      cout << endl << "Student not deleted." << endl;
      if (next->getNext() != NULL) {
	DELETE(head, next->getNext(), next, lname);  //RECURSION
      }
    }
    else {
      cout << endl << "Invalid input. Try again." << endl;
    }
  }
  else if (strcmp(lname, next->getStudent()->getLast()) == 0) {  //working with any other node
    PrintStud(next);
    cout << "Would you like to delete this student? y or n:" << endl;
    cin >> yn;
    cin.clear();
    cin.ignore(10000, '\n');
    if (yn == 'y') {
      cout << endl << "===========Student=Deleted============" << endl;
      prev->setNext(next->getNext());
      //next->~Node();
    }
    else if (yn == 'n') {
      cout << endl << "Student not deleted." << endl;
    }
    else {
      cout << endl << "Invalid input. Try again." << endl;
    }
  }
  if (next->getNext() != NULL) {
    DELETE(head, next->getNext(), next, lname);  //RECURSION
  }
  else {
    cout << endl << "No student with such last name. Try again." << endl;
  }
}

void PrintStud(Node* current) {
  cout << endl << current->getStudent()->getFirst() << " ";
  cout << current->getStudent()->getLast() << ", ";
  cout << "ID " << *current->getStudent()->getId() << ", ";
  cout << "GPA " << fixed << setprecision(2) << *current->getStudent()->getGpa() << endl;
}
