#include <iostream>
#include <cstring>
#include "Student.h"

using namespace std;

Student::Student() {
  //empty constructor
}

Student::~Student() {
  delete &firstN;
  delete &lastN;
  delete &id;
  delete &gpa;
  delete &index;
}

//getters
char* Student::getFirst() {
  return firstN;
}

char* Student::getLast() {
  return lastN;
}

int* Student::getId() {
  return &id;
}

float* Student::getGpa() {
  return &gpa;
}

int* Student::getIndex() {
  return &index;
}

void Student::setIndex(int newIndex) {
  index = newIndex;
}
