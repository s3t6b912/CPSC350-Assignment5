Name: Sebastian Brumm
ID: 2319132
Section: 01
Date: 11/27/19
Assignment 5 - Binary Search Tree

References:
1. You for showing us the structure of the tree
2. Overloading Operators - https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=vs-2019

How to run:
Change to src directory
Type make in the command line to run
Then ./Assignment5.out
Enter numbers 1-14 based on which operation you want to perform, Ex 1 for printing the student tree

Notes:
1. If a student has their advisor ID as -1, they don't have an advisor
2. The rollback option only undos options that had changed the trees, meaning adding or deleting students or faculty. I thought about having it revert changes to
   the students and faculty themselves, such as changing advisor or advisee, but didn't do it because that doesn't change the structure of the trees.
3. When entering names or departements etc, don't use a space use and underscore (_) instead. It messes up the inputs since C++ recognizes a space as a separate input.
4. Looking back on it I could have made a database object that stores the two trees and all of the functions that are in the main class but I didn't foresee the main
   class being as long as it is.