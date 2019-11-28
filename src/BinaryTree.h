/* BinaryTree.h
  Implementation of a BST
  @author Sebastian Brumm
  @author brumm@chapman.edu
  @author Id:2319132
*/
#include <iostream>
#include <fstream>
#include "TreeNode.h"

using namespace std;

template <class T>
class BinaryTree{
private:
  TreeNode<T> *root;

public:
  BinaryTree();
  ~BinaryTree();

  //core functions
  bool search(int k);
  void insert(T node, int k);
  bool deleteNode(int k);
  T returnData(int k);

  //helper function
  bool isEmpty();
  TreeNode<T>* getMin();
  TreeNode<T>* getMax();
  void printTree();
  void recPrint(TreeNode<T> *node);
  void preorderPrint();
  void recPreorder(TreeNode<T> *node);
  void preorderToFile(ofstream& out);
  void recPreorderToFile(TreeNode<T> *node, ofstream& out);
  TreeNode<T>* getSuccessor(TreeNode<T> *d);
};

//constructor
template <class T>
BinaryTree<T>::BinaryTree(){
  root = NULL;
}

//destructor
template <class T>
BinaryTree<T>::~BinaryTree(){
  delete root;
}

//checks if tree is empty
template <class T>
bool BinaryTree<T>::isEmpty(){
  if(root == NULL){
    return true;
  }else{
    return false;
  }
}

//prints the tree inorder
template <class T>
void BinaryTree<T>::recPrint(TreeNode<T> *node){
  if(node == NULL){
    return;
  }

  recPrint(node->left);
  cout << node->data << endl;
  recPrint(node->right);
}

//calls the recPrint function on the root
template <class T>
void BinaryTree<T>::printTree(){
  recPrint(root);
}

//prints the tree preorder
template <class T>
void BinaryTree<T>::recPreorder(TreeNode<T> *node){
  if(node == NULL){
    return;
  }
  cout << node->data << endl;
  recPreorder(node->left);
  recPreorder(node->right);
}

//calls the recPreorder function on the root
template <class T>
void BinaryTree<T>::preorderPrint(){
  recPreorder(root);
}

//prints the tree to a file preorder
template <class T>
void BinaryTree<T>::recPreorderToFile(TreeNode<T> *node, ofstream& out){
  if(node == NULL){
    return;
  }
  out << node->data << endl;
  recPreorderToFile(node->left, out);
  recPreorderToFile(node->right, out);
}

//calls the recPreorderToFile function on the root
template <class T>
void BinaryTree<T>::preorderToFile(ofstream& out){
  recPreorderToFile(root, out);
}

//returns the node with the lowest key value
template <class T>
TreeNode<T>* BinaryTree<T>::getMin(){
  TreeNode<T> *curr = root;

  if(curr == NULL){
    return NULL;
  }//Empty tree

  while(curr->left != NULL){
    curr = curr->left;
  }
  return curr;
}

//returns the node with the highest key value
template <class T>
TreeNode<T>* BinaryTree<T>::getMax(){
  TreeNode<T> *curr = root;

  if(curr == NULL){
    return NULL;
  }//Empty tree

  while(curr->right != NULL){
    curr = curr->right;
  }
  return curr;
}

//inserts an object into the tree and assigns it a key
template <class T>
void BinaryTree<T>::insert(T node, int k){
  TreeNode<T> *temp = new TreeNode<T>(node, k);

  if(root == NULL){//empty tree
    root = temp;
  }else{//tree not empty, have to find the insert location
    TreeNode<T> *curr = root;
    TreeNode<T> *parent = NULL;

    while(curr != NULL){
      parent = curr;
      if(temp->key < curr->key){
        curr = curr->left;//going to the left child node
        if(curr == NULL){//found insertion point
          parent->left = temp;
          break;
        }
      }else{
        curr = curr->right;//going to the right child node
        if(curr == NULL){//found insertion point
          parent->right = temp;
          break;
        }
      }
    }
  }
}

//will return a bool based on if there is a node with the inputted key in the tree
template <class T>
bool BinaryTree<T>::search(int k){//can change return type to return the value if given a key for something like a string BST
  if(root == NULL){//empty tree
    return false;
  }else{//tree is not empty
    TreeNode<T> *curr = root;

    while(curr->key != k){
      if(k < curr->key){//go left
        curr = curr->left;
      }else{//go right
        curr = curr->right;
      }
      if(curr == NULL){//we did not find the value after reaching the end of the tree
        return false;
      }
    }
  }
  return true;
}

//returns the data of a node if given the key
template <class T>
T BinaryTree<T>::returnData(int k){//can change return type to return the value if given a key for something like a string BST
  TreeNode<T> *curr = root;

  while(curr->key != k){
    if(k < curr->key){//go left
      curr = curr->left;
    }else{//go right
      curr = curr->right;
    }
  }
  return curr->data;
}

//deletes a node with the given key from the tree and returns a bool based of whether it was successful or not
template <class T>
bool BinaryTree<T>::deleteNode(int k){//returns true if successfully deleted and false if the key doesn't exist
  if(root == NULL){//if the tree is empty
    return false;
  }else{//not empty
    TreeNode<T> *curr = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;//if the node is a left child or not

    while(curr->key != k){//same as the search function
      parent = curr;
      if(k < curr->key){//go left
        isLeft = true;
        curr = curr->left;
      }else{//go right
        isLeft = false;
        curr = curr->right;
      }
      if(curr == NULL){//we did not find the value after reaching the end of the tree
        return false;
      }
    }
    //the following code is run if the node to be deleted has been found
    //first have to check the cases
    if(curr->left == NULL && curr->right == NULL){//case 1, no children
      if(curr == root){
        root = NULL;

      }else if(isLeft){
        parent->left = NULL;
      }else{
        parent->right = NULL;
      }
      delete curr;
    }
    //case 2, the node has 1 child
    //first determine if left or right
    else if(curr->right == NULL){//has left child
      if(curr == root){
        root = curr->left;
      }else if(isLeft){
        parent->left = curr->left;
      }else{
        parent->right = curr->left;
      }
      delete curr;
    }else if(curr->left == NULL){//has right child
      if(curr == root){
        root = curr->right;
      }else if(isLeft){
        parent->left = curr->right;
      }else{
        parent->right = curr->right;
      }
      delete curr;
    }else{//case 3, the node has 2 children
      TreeNode<T> *successor = getSuccessor(curr);

      if(curr == root){
        root = successor;
      }else if(isLeft){
        parent->left = successor;
      }else{
        parent->right = successor;
      }

      successor->left = curr->left;
      delete curr;
    }
  }
  return true;
}

//We find the successor of the node by going to the right child and then as far down its left children as we can
template <class T>
TreeNode<T>* BinaryTree<T>::getSuccessor(TreeNode<T> *d){//d is the node being deleted in deleteNode
  TreeNode<T> *sp = d; //sp is successor's parent
  TreeNode<T> *successor = d;
  TreeNode<T> *curr = d->right; //start one right

  while(curr !=NULL){
    sp = successor;
    successor = curr;
    curr = curr->left;
  }

  if(successor != d->right){
    //successor is a descendant of the right child
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}
