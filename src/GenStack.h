/* GenStack.h
  This is the header file and implementation of a generic stack using an array
  @author Sebastian Brumm
  @author brumm@chapman.edu
  @author Id:2319132
*/
#include <iostream>

using namespace std;

template <class T>
class GenStack{
public:
  GenStack();
  GenStack(int maxSize);
  ~GenStack();

  //Core funcions
  void push(T d);
  void extend();
  T pop();
  T peek();

  //Aux functions
  bool isFull();
  bool isEmpty();

  //Variables
  int size;
  int top;
  T *myArray;
};

//Default constructor for the stack with size 128
template <class T>
GenStack<T>::GenStack(){
  myArray = new T[128];
  size = 128;
  top = -1;
}

//Overloaded constructor for the stack with size as inputted
template <class T>
GenStack<T>::GenStack(int maxSize){
  myArray = new T[maxSize];
  size = maxSize;
  top = -1;
}

//Destructor
template <class T>
GenStack<T>::~GenStack(){
  delete []myArray;
}

//Pushes a value to the stack and calls the extend function if stack is full
template <class T>
void GenStack<T>::push(T d){
  if(isFull()){
    extend();
  }
  myArray[++top] = d;
}

//Uses a temporary array to store the stack and then doubles the stack size
template <class T>
void GenStack<T>::extend(){
  T temp[size];
  for(int i = 0; i < size; i++){
    temp[i] = myArray[i];
  }
  delete []myArray;
  myArray = new T[size*2];
  for(int i = 0; i < size; i++){
    myArray[i] = temp[i];
  }
  size = size*2;
}

//Checks if the stack is empty and if not will remove and return the top value
template <class T>
T GenStack<T>::pop(){
  try{
    if (top == -1){
      throw top;
    }
    return myArray[top--];
  }catch (int e){
    cout << "Stack is empty." << endl;
  }
}

//Checks if the stack is empty and if not will return the top value
template <class T>
T GenStack<T>::peek(){
  try{
    if (top == -1){
      throw top;
    }
    return myArray[top];
  }catch (int e){
    cout << "Stack is empty." << endl;
  }
}

//Detects if the stack is full
template <class T>
bool GenStack<T>::isFull(){
  return (top == size-1);
}

//Detects if the stack is empty
template <class T>
bool GenStack<T>::isEmpty(){
  return (top == -1);
}
