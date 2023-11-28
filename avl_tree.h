/**
 * An AVL tree. Deletions are not supported.
 *
 * @authors Drue Coles, fayth quinn
 */

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "bst.h"

template <typename T>
class AvlTree : public BST<T> {

public:
    void insert(T data);
     
private:
    Node<T>* trinode_successor(Node<T>*);
    Node<T>* trinode_restructure(Node<T>*, Node<T>*, Node<T>*);
    bool unbalanced(Node<T>*);

    Node<T>* right_rotate(Node<T>*, Node<T>*);  // fayth quinn
    Node<T>* left_rotate(Node<T>*, Node<T>*);   // fayth quinn

    void height_update(Node<T>*);   // fayth quinn
};

#endif