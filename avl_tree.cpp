/**
 * Implementation file for an AVL Tree
 * 
 * An AVL Tree is a type of self-adjusting Binary Search Tree with the defining
 * property that the difference in height between a given node's left child and
 * right child is no greater than one (1).
 * 
 * @author fayth quinn
*/

#include "avl_tree.h"

/**
 * Inserts the given data into the tree then performs restructuring if necessary
 * 
 * @param data The data to be inserted into the tree
*/
template <typename T>
void AvlTree<T>::insert(T data) {

	// Insert data like in standard Binary Search Tree
	BST<T>::insert(data);

	// Search for the newly inserted data
	// <Copied from Dr. Coles>
	Node<T>* p = BST<T>::root;
	while (data != p->data) p = (data <= p->data ? p->left : p->right);
	p = p->parent;
	// </Copied from Dr. Coles>

	// Move up the tree, checking for unbalanced nodes
	while (p != nullptr && !unbalanced(p)) p = p->parent;

	if (p == nullptr) return; // No unbalanced nodes
	else {

		Node<T>* q = trinode_successor(p); // Find successor of unbalanced node
		Node<T>* r = trinode_successor(q); // Find successor of successor

		Node<T>* s = trinode_restructure(p, q, r);	// Restructuring nodes
		if (p == BST<T>::root) BST<T>::root = s;	// Adjust root, if needed

	}

}

/**
 * Finds the node needed to perform a trinode structure with the given node
 * 
 * @return The next node in line for the trinode restructuring
*/
template <typename T>
Node<T>* AvlTree<T>::trinode_successor (Node<T>* p) {

	// Return other node if one is null
	// <Copied from Dr. Coles>
	if (p->right == nullptr) return p->left;
	else if (p->left == nullptr) return p->right;

	int a = BST<T>::height(p->left);
	int b = BST<T>::height(p->right);

	// Compare heights and return taller branch
	if (a > b || (a == b && p->left->data <= p->data)) return p->left;
	else return p->right;
	// </Copied from Dr. Coles>

}

/**
 * Takes the given nodes, checks for their relationships, then performs the
 * correct rotation according to AVL tree properties.
 * 
 * @param x The root node of the branch
 * @param y The child of node x
 * @param z The child of node y
 * @return The node now at the root of the branch
*/
template <typename T>
Node<T>* AvlTree<T>::trinode_restructure(Node<T>* x, Node<T>* y, Node<T>* z) {

	Node<T>* n = x; // Will store new root after restructuring

	if (x->left == y) {

		if (y->left == z) n = right_rotate(x, y);
		else {
			/*
			 * Perform a right-left rotation, as follows:
			 *       X                     Z
			 *      / \                  /   \
			 *     Y   a                Y     X
			 *    / \          ==>     / \   / \
			 *   b   Z                b   c d   a
			 *      / \
			 *     c   d
			 */
			left_rotate(y, z);	// First, perform left rotation
			n = right_rotate(x, z);	// Then, perform right rotation
		}

	}
	else {

		if (y->right == z) n = left_rotate(x, y);
		else {
			/*
			 * Performs a left-right rotation, as follows:
			 *       X                     Z
			 *      / \                  /   \
			 *     a   y                X     Y
			 *        / \      ==>     / \   / \
			 *       Z   b            a   c d   b
			 *      / \
			 *     c   d
			 */
			right_rotate(y, z); // First, perform right rotation
			n = left_rotate(x, z); // Then, perform left rotation
		}

	}


	// If parent is unbalanced, restucture it as well
	if (n->parent != nullptr && unbalanced(n->parent)) {

		n = n->parent;

		Node<T>* o = trinode_successor(n);
		Node<T>* p = trinode_successor(o);

		return trinode_restructure(n, o, p);
	}

	return n; // Return new branch root
}

/**
 * A method for checking whether or not a supplied node is "balanced". That
 * being, the given node's children differ in height by no more than one (1).
 * 
 * @return True if node is unbalanced, False otherwise
*/
template <typename T>
bool AvlTree<T>::unbalanced(Node<T>* node) {
	return (BST<T>::height(node->left) - BST<T>::height(node->right) > 1
	|| BST<T>::height(node->left) - BST<T>::height(node->right) < -1);
}

/**
 * Performs a right rotation, as follows:
 * 
 *          X                 Y
 *         / \              /   \
 *        Y   a            Z     X
 *       / \       ==>    / \   / \
 *      Z   b            c   d b   a
 *     / \
 *    c   d
 * 
 * @param x The unbalanced node
 * @param y The child of the unbalanced node for restructuring
 * @return The node now at the root of the branch
*/
template <typename T>
Node<T>* AvlTree<T>::right_rotate(Node<T>* x, Node<T>* y) {

	Node<T>* b = y->right;

	// Swap the nodes and their children
	y->right = x;
	x->left = b;

	y->parent = x->parent;
	x->parent = y;

	// Update child's parent, if child exists
	if (b != nullptr) b->parent = x;

	// Update root's parent with new child, if parent exists
	if (y->parent != nullptr) {

		if (y->parent->right == x) y->parent->right = y;
		else y->parent->left = y;

	}
	
	height_update(x); // Update the height of all nodes
	return y; // Return new root
}

/**
 * Performs a left rotation, as follows:
 * 
 *     X                Y
 *    / \             /   \
 *   a   Y    ==>    X     Z
 *      / \         / \   / \
 *     b   Z       a   b c   d
 *        / \
 *       c   d
 * 
 * @param x The unbalanced node
 * @param y The child of the unbalanced node for restructuring
 * @return The node now at the root of the branch
*/
template <typename T>
Node<T>* AvlTree<T>::left_rotate(Node<T>* x, Node<T>* y) {

	Node<T>* b = y->left;

	// Swap the nodes and their children
	y->left = x;
	x->right = b;

	y->parent = x->parent;
	x->parent = y;

	// Update child's parent, if child exists
	if (b != nullptr) b->parent = x;

	// Update root's parent with new child, if parent exists
	if (y->parent != nullptr) {

		if (y->parent->left == x) y->parent->left = y;
		else y->parent->right = y;

	}

	height_update(x); // Update the height of all nodes
	return y; // Return new root
}

/**
 * Updates the height of the given node recursively updates the height of all
 * other nodes above it
 * 
 * @param n The node to update the height for
*/
template <typename T>
void AvlTree<T>::height_update(Node<T>* n) {

	if (n == nullptr) return; // Base case
	
	// If node has both a right and a left child
	if (n->left != nullptr && n->right != nullptr)
		// Get the greater height, add 1
		n->height = (n->left->height > n->right->height ?
		n->left->height + 1 : n->right->height +1);

	// If node only has a left child
	else if (n->left != nullptr) n->height = n->left->height + 1;
	// If node only has a right child
	else if (n->right != nullptr) n->height = n->right->height + 1;
	// If node has no children 
	else n->height = 0;

	height_update(n->parent); // Update parent's height
}