/* Undo.h
  An object that is stores commands that were used in the database to undo them
  @author Sebastian Brumm
  @author brumm@chapman.edu
  @author Id:2319132
*/
#include "Student.h"
#include "Faculty.h"

class Undo{
public:
  //variables
  bool isFacInsert;
  bool isFacDelete;
  bool isStudInsert;
  bool isStudDelete;
  int id;
  Student stud;
  Faculty fac;

  //constructors
  Undo();
  Undo(int d);
  Undo(Faculty d);
  Undo(Student d);
  ~Undo();

  //helper functions
  void setIsFacInsert();
  bool getIsFacInsert();
  void setIsFacDelete();
  bool getIsFacDelete();
  void setIsStudInsert();
  bool getIsStudInsert();
  void setIsStudDelete();
  bool getIsStudDelete();

  int getID();
  Student getStudent();
  Faculty getFaculty();
};

//default constructor
Undo::Undo(){
  isFacInsert = false;
  isFacDelete = false;
  isStudDelete = false;
  isStudInsert = false;
}

//overloaded constructors that are used depending on which action was performed
Undo::Undo(int d){
  isFacInsert = false;
  isFacDelete = false;
  isStudDelete = false;
  isStudInsert = false;
  id = d;
}

Undo::Undo(Faculty d){
  isFacInsert = false;
  isFacDelete = false;
  isStudDelete = false;
  isStudInsert = false;
  id = -1;
  fac = d;
}

Undo::Undo(Student d){
  isFacInsert = false;
  isFacDelete = false;
  isStudDelete = false;
  isStudInsert = false;
  id = -1;
  stud = d;
}

//destructor whihc is empty
Undo::~Undo(){

}

//every other function just sets and returns variables depending on which operation was being performed
void Undo::setIsFacDelete(){
  isFacDelete = true;
}

bool Undo::getIsFacDelete(){
  return isFacDelete;
}

void Undo::setIsFacInsert(){
  isFacInsert = true;
}

bool Undo::getIsFacInsert(){
  return isFacInsert;
}

void Undo::setIsStudDelete(){
  isStudDelete = true;
}

bool Undo::getIsStudDelete(){
  return isStudDelete;
}

void Undo::setIsStudInsert(){
  isStudInsert = true;
}

bool Undo::getIsStudInsert(){
  return isStudInsert;
}

int Undo::getID(){
  return id;
}

Student Undo::getStudent(){
  return stud;
}

Faculty Undo::getFaculty(){
  return fac;
}
