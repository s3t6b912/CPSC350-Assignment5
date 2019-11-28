/* Student.h
  An object that is supposed to represent a student in the database
  @author Sebastian Brumm
  @author brumm@chapman.edu
  @author Id:2319132
*/
#include <iostream>

using namespace std;

class Student{
public:
  //variables
  int studID;
  string name;
  string level;
  string major;
  double gpa;
  int advisor;

  //constructors
  Student();
  Student(int a, string b, string c, string d, double e, int f);
  ~Student();

  //helper functions
  void setID(int a);
  int getID();
  void setName(string a);
  string getName();
  void setLevel(string a);
  string getLevel();
  void setMajor(string a);
  string getMajor();
  void setGPA(double a);
  double getGPA();
  void setAdvisor(int a);
  int getAdvisor();

  void printStudent();

  //these overload boolean operators to compare two student IDs
  bool operator == (Student a){
    if(this->studID == a.getID()){
      return true;
    }else{
      return false;
    }
  }

  bool operator < (Student a){
    if(this->studID < a.getID()){
      return true;
    }else{
      return false;
    }
  }

  bool operator > (Student a){
    if(this->studID > a.getID()){
      return true;
    }else{
      return false;
    }
  }
};

//default constructor
Student::Student(){
  studID = 0;
  name = "";
  level = "";
  major = "";
  gpa = 0.0;
  advisor = 0;
}

//overloaded constructor
Student::Student(int a, string b, string c, string d, double e, int f){
  studID = a;
  name = b;
  level = c;
  major = d;
  gpa = e;
  advisor = f;
}

//destructor which is empty
Student::~Student(){

}

//most of the following functions just get and set the member variables
void Student::setID(int a){
  studID = a;
}

int Student::getID(){
  return studID;
}

void Student::setName(string a){
  name = a;
}

string Student::getName(){
  return name;
}

void Student::setLevel(string a){
  level = a;
}

string Student::getLevel(){
  return level;
}

void Student::setMajor(string a){
  major = a;
}

string Student::getMajor(){
  return major;
}

void Student::setGPA(double a){
  gpa = a;
}

double Student::getGPA(){
  return gpa;
}

void Student::setAdvisor(int a){
  advisor = a;
}

int Student::getAdvisor(){
  return advisor;
}

//prints the variables of the student to out
void Student::printStudent(){
  cout << "ID: " << studID << endl;
  cout << "Name: " << name << endl;
  cout << "Level: " << level << endl;
  cout << "Major: " << major << endl;
  cout << "GPA: " << gpa << endl;
  cout << "Adivsor ID: " << advisor << endl;
}
