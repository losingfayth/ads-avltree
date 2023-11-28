/**
 * Implementation file for a Binary Search Tree
 * 
 * A Binary Search Tree is a data structure wherein each node has at most two
 * children, one left and right, where the left child has data less than or
 * equal to the node's data and the right child has data greater than the node's
 * data.
 * 
 * @author fayth quinn
*/

#include <ostream>
#include "bst.h"

/**
 * Prints out the data from the given BST to the given output stream
 * 
 * @param out An ostream object to add the data into
 * @param bst The tree to print out
 * @return An ostream object containing the tree data
*/
template <typename T>
std::ostream& operator<<(std::ostream& out, const BST<T>& bst) {
	print(out, bst.root);
	return out;
}

/**
 * Recursively adds the data of the children of the given node and the data of 
 * the node to the given output stream
 * 
 * @param out An ostream object to add the data into
 * @param n The node to print the data from
*/
template <typename T>
void print(std::ostream& out, Node<T>* n) {

	if (n != nullptr) {
		print(out, n->left);	// Recursively print left child
		out << n->data << " ";	// Print current node
		print(out, n->right);	// Recursively print right child
	}

}

/**
 * Inserts the given data into the tree
 * 
 * @param data The data to be inserted into the tree
*/
template <typename T>
void BST<T>::insert(T data) {
	
	Node<T>* node = new Node<T>(data);
	node->parent = root;
	node->left = nullptr;
	node->right = nullptr;

	// If the tree is empty
	if (root == nullptr) {
		root = node;
		return;
	}

	// Cursor to search through the tree
	Node<T>* curr = root;
	do {

		// Follow left child
		if (node->data <= curr->data) {

			// Insert node at left child
			if (curr->left == nullptr) {
				curr->left = node;
				node->parent = curr;
				break;
			}

			curr = curr->left;
		}
		// Follow right child
		else {

			// Insert node at right child
			if (curr->right == nullptr) {
				curr->right = node;
				node->parent = curr;
				break;
			}

			curr = curr->right;
		}

	} while (true);

	// Update height
	int height = 1;
	while (curr != nullptr) {
		if (height > curr->height) curr->height = height;
		height++;
		curr = curr->parent;
	}

}

/**
 * Deletes the given node
 * 
 * @param n The node to be deleted
*/
template <typename T>
void BST<T>::remove(Node<T>* n) {

	if (n != nullptr) {
		remove(n->left);	// Recursively remove left
		remove(n->right);	// Recursively remove right
		delete n;
	}

}

/**
 * Returns the height of the root node of the tree, and therefore the tree
 * 
 * @return The height of the tree or -1 if tree is empty
*/
template <typename T>
int BST<T>::height(Node<T>* n) {

	if (n == nullptr) return -1;
	else return n->height;

}