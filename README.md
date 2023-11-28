# AVL Tree vs. Binary Search Tree Height Comparison in C++
**authors:** fayth quinn ([*@losingfayth*](https://github.com/losingfayth)), drue coles

This program implements two tree data structures,
 * A **Binary Search Tree** *(BST)*, defined as a tree where every node can have at most two children, with all children, grandchildren, etc., in its left child having data smaller than its data and all children, grandchildren, etc., in its right child having data greater than its data
 * An **AVL Tree** *(AVL)*, defined as a Binary Search Tree that restructures itself on insertion or deletion to ensure that the height of any given left child of some node and the height of any given right child of that node have a difference of no more than one (1)

The trees created in this project do not support deletions, only insertions.

The purpose of this program is to compare the heights of a BST and an AVL data structure when given the same set of partially sorted data. The data is an array of integers from `1` to some value `m` that has had `m` randomized "inversions" performed. An inversion, in this context, is the swapping of data at index `i` with the data of index `i + 1` if and only if the data at `i + 1` is greater than the data at `i`. This will create a partially sorted array to build the trees with.

To ensure the height values are as accurate as possible, the program will randomize the array some number of times (defined in `main.cpp`, currently ten (10)), building trees with each randomized array, then averaging the heights of all the trees together.


## Context
The program was created as part of a school project. This project was completed in ~4 days.

## Known Issues
The program tends to hang on larger `n` values (`m = 2`<sup>`n`</sup>), as each trial takes some time and each subsequent repition adds onto that. Currently, values >16 are known to take a significant amount of time. The program is working correctly, it just takes a while.

## Feedback Recieved

* dc: Needed to changed `avl_tree.h` to include `bst.cpp` instead of `bst.h` to compile
	* fq: Will not compile with `g++` (`c++11`) with this configuration; `avl_tree.h` needs to include `bst.h` for successful compilation