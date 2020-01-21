#ifndef STUDENT_H
#define STUDENT_H

using namespace std;

class Student {
 public:
  Student();
  ~Student();
  //getters
  char* getFirst();
  char* getLast();
  int* getId();
  float* getGpa();
  int* getIndex();
  void setIndex(int);
 private:
  char firstN[20];
  char lastN[20];
  int id;
  float gpa;
  int index;
};
#endif
