/* TreeNode.h
  Node class for a Binary Tree
  @author Sebastian Brumm
  @author brumm@chapman.edu
  @author Id:2319132
*/
template <class T>
class TreeNode{
public:
  TreeNode<T>();
  TreeNode<T>(T d, int k); //d = the data, k = key
  ~TreeNode<T>(); //Destructor

  //variables
  T data;
  int key;
  TreeNode<T> *left;
  TreeNode<T> *right;

};

//default constructor
template <class T>
TreeNode<T>::TreeNode(){
  data = NULL;
  key = 0;
  left = NULL;
  right = NULL;
}

//overloaded constructor
template <class T>
TreeNode<T>::TreeNode(T d, int k){
  data = d;
  key = k;
  left = NULL;
  right = NULL;
}

//destructor
template <class T>
TreeNode<T>::~TreeNode(){
  delete left;
  delete right;
}
