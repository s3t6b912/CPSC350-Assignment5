/* Faculty.h
  An object that is supposed to represent a faculty member in the database
  @author Sebastian Brumm
  @author brumm@chapman.edu
  @author Id:2319132
*/
#include <iostream>
#include "GenLinkedList.h"

using namespace std;

class Faculty{
public:
  //variables
  int facID;
  string name;
  string level;
  string department;
  GenLinkedList<int> *list;

  //constructors
  Faculty();
  Faculty(int a, string b, string c, string d);
  ~Faculty();

  //helper functions
  void setID(int a);
  int getID();
  void setName(string a);
  string getName();
  void setLevel(string a);
  string getLevel();
  void setDepartment(string a);
  string getDepartment();
  void printAdvisees();
  int getNumAdvisees();

  //modify the advisee list
  void addAdvisee(int d);
  void removeAdvisee(int d);
  int getAdvisee(int d);

  void printFaculty();

  //overloaded boolean operators that compare two faculty IDs
  bool operator == (Faculty a){
    if(facID == a.getID()){
      return true;
    }else{
      return false;
    }
  }

  bool operator < (Faculty a){
    if(facID < a.getID()){
      return true;
    }else{
      return false;
    }
  }

  bool operator > (Faculty a){
    if(facID > a.getID()){
      return true;
    }else{
      return false;
    }
  }
};

//default constructor
Faculty::Faculty(){
  facID = 0;
  name = "";
  level = "";
  department = "";
  list = new GenLinkedList<int>;
}

//overloaded constructor
Faculty::Faculty(int a, string b, string c, string d){
  facID = a;
  name = b;
  level = c;
  department = d;
  list = new GenLinkedList<int>;
}

//destructor which is empty
Faculty::~Faculty(){

}

//most of the following functions set and recieve the member variables
void Faculty::setID(int a){
  facID = a;
}

int Faculty::getID(){
  return facID;
}

void Faculty::setName(string a){
  name = a;
}

string Faculty::getName(){
  return name;
}

void Faculty::setLevel(string a){
  level = a;
}

string Faculty::getLevel(){
  return level;
}

void Faculty::setDepartment(string a){
  department = a;
}

string Faculty::getDepartment(){
  return department;
}

void Faculty::addAdvisee(int d){
  list->insertBack(d);
}

void Faculty::removeAdvisee(int d){
  list->remove(d);
}

void Faculty::printAdvisees(){
  list->printList();
}

int Faculty::getAdvisee(int d){
  list->findPosition(d);
}

int Faculty::getNumAdvisees(){
  return list->getSize();
}

//prints the data of the faculty to out
void Faculty::printFaculty(){
  cout << "ID: " << facID << endl;
  cout << "Name: " << name << endl;
  cout << "Level: " << level << endl;
  cout << "Department: " << department << endl;
  cout << "Advisees: " << endl;
  list->printList();
}
