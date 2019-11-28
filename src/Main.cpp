/* Main.cpp
  The main class for the database, most of it is just taken up by functions that perform the 14 operations needed
  @author Sebastian Brumm
  @author brumm@chapman.edu
  @author Id:2319132
*/
#include <iostream>
#include <fstream>
#include "BinaryTree.h"
#include "GenStack.h"
#include "Undo.h"

using namespace std;

//these operators are for << and the faculty and student classes and will basically just return their information
ostream& operator << (ostream& a, Faculty& b){
  a << "ID: " << b.getID() << endl;
  a << "Name: " << b.getName() << endl;
  a << "Level: " << b.getLevel() << endl;
  a << "Department: " << b.getDepartment() << endl;
  a << "Number of advisees: " << b.getNumAdvisees() << endl;
  a << "Advisees: " << endl;
  for(int i = 0; i < b.getNumAdvisees(); i++){
    a << b.getAdvisee(i) << endl;
  }
  return a;
}

ostream& operator << (ostream& a, Student& b){
  a << "ID: " << b.getID() << endl;
  a << "Name: " << b.getName() << endl;
  a << "Level: " << b.getLevel() << endl;
  a << "Major: " << b.getMajor() << endl;
  a << "GPA: " << b.getGPA() << endl;
  a << "Adivsor ID: " << b.getAdvisor() << endl;
  return a;
}

//prints the student tree to out
void printStudents(BinaryTree<Student>& tree){
  tree.printTree();
}

//prints the faculty tree to out
void printFacultys(BinaryTree<Faculty>& tree){
  tree.printTree();
}

//prints a student to out when given the ID
void displayStudent(BinaryTree<Student>& tree){
  int id;
  cout << "Enter the student ID: \n";
  cin >> id;

  if(tree.search(id)){
    Student temp = tree.returnData(id);
    cout << temp << endl;
  }else{
    cout << "No student with that ID exists.\n";
  }
}

//prints a faculty to out when given the ID
void displayFaculty(BinaryTree<Faculty>& tree){
  int id;
  cout << "Enter the faculty ID: \n";
  cin >> id;

  if(tree.search(id)){
    Faculty temp = tree.returnData(id);
    cout << temp << endl;
  }else{
    cout << "No faculty with that ID exists.\n";
  }
}

//prints the advisor of the student who's ID is given
void findAdvisor(BinaryTree<Faculty>& facTree, BinaryTree<Student>& studTree){
  int id;
  cout << "Enter the student ID: \n";
  cin >> id;

  if(studTree.search(id)){
    if(studTree.returnData(id).getAdvisor() == -1){
      cout << "This student has not been assigned an advisor.\n";
    }else{
      Faculty temp = facTree.returnData(studTree.returnData(id).getAdvisor());
      temp.printFaculty();
    }
  }else{
    cout << "No student with that ID exists.\n";
  }
}

//prints all of the information of the advisees of the faculty who's ID is given
void findAdvisees(BinaryTree<Faculty>& facTree, BinaryTree<Student>& studTree){
  int id;
  cout << "Enter the faculty ID: \n";
  cin >> id;

  if(facTree.search(id)){
    if(facTree.returnData(id).getNumAdvisees() == 0){
      cout << "This faculty has not been assigned any advisees.\n";
    }else{
      for(int i = 0; i < facTree.returnData(id).getNumAdvisees(); i++){
        Student temp = studTree.returnData(facTree.returnData(id).getAdvisee(i));
        cout << temp << endl;
      }
    }
  }else{
    cout << "No faculty with that ID exists.\n";
  }
}

//creates a student and then inserts it into the binary tree
Undo* createStudent(BinaryTree<Student>& studTree){
  int id;
  string name;
  string level;
  string major;
  double gpa;

  cout << "Enter the ID of the student: \n";
  cin >> id;
  if(!studTree.search(id)){
    cout << "Enter the name of the student: \n";
    cin >> name;
    cout << "Enter the level of the student: \n";
    cin >> level;
    cout << "Enter the major of the student: \n";
    cin >> major;
    cout << "Enter the GPA of the student: \n";
    cin >> gpa;

    Student temp(id, name, level, major, gpa, -1);
    studTree.insert(temp, id);
    cout << "Student successfully created. Student is currently not assigned an advisor, to change this select option 11 and enter this student's ID.\n";
    Undo *x = new Undo(id);
    x->setIsStudInsert();
    cout << "test" << endl;
    return x;
  }else{
    cout << "There is already a student with that ID.\n";
  }
}

//deletes a student from the tree given their ID
Undo* deleteStudent(BinaryTree<Faculty>& facTree, BinaryTree<Student>& studTree){
  int id;
  cout << "Enter the student ID: \n";
  cin >> id;

  if(studTree.search(id)){
    int temp = studTree.returnData(id).getAdvisor();
    Undo *x = new Undo(studTree.returnData(id));
    x->setIsStudDelete();
    studTree.deleteNode(id);
    if(temp != -1){
      Faculty tempFac = facTree.returnData(temp);
      tempFac.removeAdvisee(id);
      facTree.deleteNode(temp);
      facTree.insert(tempFac, temp);
    }
    cout << "Student successfully removed.\n";
    return x;

  }else{
    cout << "Error, there is no student with that ID.\n";
  }
}

//creates a faculty and then inserts them into the tree
Undo* createFaculty(BinaryTree<Faculty>& facTree){
  int id;
  string name;
  string level;
  string department;

  cout << "Enter the ID of the faculty: \n";
  cin >> id;
  if(!facTree.search(id)){
    cout << "Enter the name of the faculty: \n";
    cin >> name;
    cout << "Enter the level of the faculty: \n";
    cin >> level;
    cout << "Enter the department of the faculty: \n";
    cin >> department;

    Faculty temp(id, name, level, department);
    facTree.insert(temp, id);
    Undo *x = new Undo(id);
    x->setIsFacInsert();
    cout << "Faculty successfully created. This faculty currently has no advisees.\n";
    return x;
  }else{
    cout << "There is already a faculty with that ID.\n";
  }
}

//deletes a faculty from the tree given their ID
Undo* deleteFaculty(BinaryTree<Faculty>& facTree, BinaryTree<Student>& studTree){
  int id;
  cout << "Enter the faculty ID: \n";
  cin >> id;

  if(facTree.search(id)){
    Faculty temp = facTree.returnData(id);
    Undo *x = new Undo(facTree.returnData(id));
    x->setIsFacDelete();
    facTree.deleteNode(id);
    for(int i = 0; i < temp.getNumAdvisees(); i++){
      int tempID = temp.getAdvisee(i);
      Student studTemp = studTree.returnData(tempID);
      studTemp.setAdvisor(-1);
      studTree.deleteNode(tempID);
      studTree.insert(studTemp, tempID);
    }
    cout << "Faculty successfully removed, all advisees under this faculty are now not assigned an advisor.\n";
    return x;

  }else{
    cout << "Error, there is no faculty with that ID.\n";
  }
}

//changes a student's advisor given their IDs and updates both trees' information
void changeAdvisor(BinaryTree<Faculty>& facTree, BinaryTree<Student>& studTree){
  int studID;
  int facID;

  cout << "What is the student's ID: \n";
  cin >> studID;
  if(!studTree.search(studID)){
    cout << "Error, there is no student with that ID.\n";
    return;
  }
  cout << "What is the faculty's ID: \n";
  cin >> facID;
  if(!facTree.search(facID)){
    cout << "Error, there is no faculty with that ID.\n";
    return;
  }else{
    int temp = studTree.returnData(studID).getAdvisor();
    if(temp == -1){
      Faculty tempFac = facTree.returnData(facID);
      tempFac.addAdvisee(studID);
      facTree.deleteNode(facID);
      facTree.insert(tempFac, facID);
      Student tempStud = studTree.returnData(studID);
      tempStud.setAdvisor(facID);
      studTree.deleteNode(studID);
      studTree.insert(tempStud, studID);
      cout << "Advisor successfully changed.\n";
    }else{
      Faculty tempF = facTree.returnData(temp);
      tempF.removeAdvisee(studID);
      facTree.deleteNode(temp);
      facTree.insert(tempF, temp);
      Faculty tempFac = facTree.returnData(facID);
      tempFac.addAdvisee(studID);
      facTree.deleteNode(facID);
      facTree.insert(tempFac, facID);
      Student tempStud = studTree.returnData(studID);
      tempStud.setAdvisor(facID);
      studTree.deleteNode(studID);
      studTree.insert(tempStud, studID);
      cout << "Advisor successfully changed.\n";
    }
  }
}

//removes an advisee from a faculty and updates both trees
void deleteAdvisee(BinaryTree<Faculty>& facTree, BinaryTree<Student>& studTree){
  int studID;
  int facID;

  cout << "What is the faculty's ID: \n";
  cin >> facID;
  if(!facTree.search(facID)){
    cout << "Error, there is no faculty with that ID.\n";
    return;
  }
  cout << "What is the student's ID: \n";
  cin >> studID;
  if(!studTree.search(studID)){
    cout << "Error, there is no student with that ID.\n";
    return;
  }else if(studTree.returnData(studID).getAdvisor() != facID){
    cout << "Error, this student is not an advisee of this faculty.\n";
    return;
  }else{
    Student studTemp = studTree.returnData(studID);
    studTemp.setAdvisor(-1);
    studTree.deleteNode(studID);
    studTree.insert(studTemp, studID);
    Faculty tempFac = facTree.returnData(facID);
    tempFac.removeAdvisee(studID);
    facTree.deleteNode(facID);
    facTree.insert(tempFac, facID);
    cout << "Successfully removed advisee.\n";
  }
}

//undos the last operation if it was an operation that changed the structure of a tree
void rollback(BinaryTree<Faculty>& facTree, BinaryTree<Student>& studTree, GenStack<Undo*>& stack){
  if(!stack.isEmpty()){
    Undo *temp = stack.pop();
    if(temp->getIsFacInsert()){
      facTree.deleteNode(temp->getID());
      cout << "Rollback successful.\n";
    }else if(temp->getIsStudInsert()){
      studTree.deleteNode(temp->getID());
      cout << "Rollback successful.\n";
    }else if(temp->getIsFacDelete()){
      facTree.insert(temp->getFaculty(), temp->getFaculty().getID());
      cout << "Rollback successful.\n";
    }else if(temp->getIsStudDelete()){
      studTree.insert(temp->getStudent(), temp->getStudent().getID());
      cout << "Rollback successful.\n";
    }
  }else{
    cout << "Error, there are currently no changes to the database that can be reversed.\n";
  }
}

//reads two separate files and parses them into the student and faculty trees
void startup(BinaryTree<Faculty>& facTree, BinaryTree<Student>& studTree, ifstream& studIn, ifstream& facIn){
  string line = "";
  while(getline(studIn,line)){
    string tempID = line.substr(4);
    int id = stoi(tempID);
    getline(studIn,line);
    string name = line.substr(6);
    getline(studIn,line);
    string level = line.substr(7);
    getline(studIn,line);
    string major = line.substr(7);
    getline(studIn,line);
    string tempGPA = line.substr(5);
    double gpa = stod(tempGPA);
    getline(studIn,line);
    string tempADID = line.substr(12);
    int adid = stoi(tempADID);

    Student tempStud(id, name, level, major, gpa, adid);
    studTree.insert(tempStud, id);
    getline(studIn,line);
  }
  while(getline(facIn,line)){
    string tempID = line.substr(4);
    int id = stoi(tempID);
    getline(facIn,line);
    string name = line.substr(6);
    getline(facIn,line);
    string level = line.substr(7);
    getline(facIn,line);
    string department = line.substr(12);
    getline(facIn,line);
    string tempNum = line.substr(20);
    int numAdvisees = stoi(tempNum);

    Faculty tempFac(id, name, level, department);
    getline(facIn,line);
    for(int i = 0; i < numAdvisees; i++){
      getline(facIn,line);
      int tempA = stoi(line);
      tempFac.addAdvisee(tempA);
    }

    facTree.insert(tempFac, id);
    getline(facIn,line);
  }
}

//the main function which calls all of the functions above based on the input
int main(int argc, char *argv[]){
  BinaryTree<Student> masterStudent;
  BinaryTree<Faculty> masterFaculty;
  GenStack<Undo*> undoStack;
  ifstream studInput("studentTable.txt");
  ifstream facInput("facultyTable.txt");

  if(studInput.is_open() && facInput.is_open()){
    startup(masterFaculty, masterStudent, studInput, facInput);
  }
  string answer = "";

  while(answer != "14"){
    cout << "Please choose one of the options listed below by entering the number that proceeds them:\n";
    cout << "1. Print all students and their information (sorted by ascending id #)\n";
    cout << "2. Print all faculty and their information (sorted by ascending id #)\n";
    cout << "3. Find and display student information given the students id\n";
    cout << "4. Find and display faculty information given the faculty id\n";
    cout << "5. Given a student’s id, print the name and info of their faculty advisor\n";
    cout << "6. Given a faculty id, print all the names and info of his/her advisees\n";
    cout << "7. Add a new student\n";
    cout << "8. Delete a student given the id\n";
    cout << "9. Add a new faculty member\n";
    cout << "10. Delete a faculty member given the id\n";
    cout << "11. Change a student’s advisor given the student id and the new faculty id\n";
    cout << "12. Remove an advisee from a faculty member given the ids\n";
    cout << "13. Undo (reverts a change involving adding/removing a student/faculty)\n";
    cout << "14. Exit\n";
    cout << endl;
    cout << "PS: when noting a space, use _ instead, so Sebastian_Brumm instead of Sebastian Brumm\n";
    cin >> answer;

    if(answer == "1"){
      printStudents(masterStudent);
      cout << endl;
    }else if(answer == "2"){
      printFacultys(masterFaculty);
      cout << endl;
    }else if(answer == "3"){
      displayStudent(masterStudent);
      cout << endl;
    }else if(answer == "4"){
      displayFaculty(masterFaculty);
      cout << endl;
    }else if(answer == "5"){
      findAdvisor(masterFaculty, masterStudent);
      cout << endl;
    }else if(answer == "6"){
      findAdvisees(masterFaculty, masterStudent);
      cout << endl;
    }else if(answer == "7"){
      undoStack.push(createStudent(masterStudent));
      cout << endl;
    }else if(answer == "8"){
      undoStack.push(deleteStudent(masterFaculty, masterStudent));
      cout << endl;
    }else if(answer == "9"){
      undoStack.push(createFaculty(masterFaculty));
      cout << endl;
    }else if(answer == "10"){
      undoStack.push(deleteFaculty(masterFaculty, masterStudent));
      cout << endl;
    }else if(answer == "11"){
      changeAdvisor(masterFaculty, masterStudent);
      cout << endl;
    }else if(answer == "12"){
      deleteAdvisee(masterFaculty, masterStudent);
      cout << endl;
    }else if(answer == "13"){
      rollback(masterFaculty, masterStudent, undoStack);
    }else if(answer == "14"){
      ofstream studOutput("studentTable.txt");
      ofstream facOutput("facultyTable.txt");
      masterFaculty.preorderToFile(facOutput);
      masterStudent.preorderToFile(studOutput);
    }else{
      cout << "You did not enter a valid option.\n";
      cout << endl;
    }
  }

  return 0;
}
