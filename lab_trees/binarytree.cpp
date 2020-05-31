/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);



}
    template <typename T>
void BinaryTree<T>::mirror(Node * subRoot)
{
//your code here

//base case to test if reached bototm
    if(subRoot == NULL){
      return;
    }

  //iterates to bottom
  mirror(subRoot->left);
  mirror(subRoot->right);

  //swap left and right
  Node * temp = subRoot->right;
  subRoot->right = subRoot->left;
  subRoot->left = temp;

  return;




}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    InorderTraversal<int> iOI(root);

    int x = 0;
    T curr;
    bool ordered = true;


    for (typename TreeTraversal<T>::Iterator iter = iOI.begin(); iter != iOI.end(); ++iter) {
        if(x != 0){
          if((*iter)->elem <= curr){
            ordered = false;
          }
        }
        curr = (*iter)->elem;
        x++;
    }


    return ordered;
}


/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
 template <typename T>
 bool BinaryTree<T>::isOrderedRecursive() const
 {

     return isOrderedRecursive(root);


 }

template <typename T>
T BinaryTree<T>::getRight(const Node* subRoot) const{

   if (subRoot->right == NULL){
       return subRoot->elem;
   }
   return getRight(subRoot->right);

}
template <typename T>
T BinaryTree<T>::getLeft(const Node* subRoot) const{

    if (subRoot->left == NULL){
        return subRoot->elem;
    }
    return getLeft(subRoot->left);
}




template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* subRoot) const
{
    // your code here

    int farr = 0;
    bool right = false;
    int farl = 0;
    bool left = false;


    if (subRoot == NULL){
        return true;
    }
    if (subRoot->left != NULL){
        left = isOrderedRecursive(subRoot->left);
        farr = getRight(subRoot->left);
    }
    else{
        left = true;
        farr = subRoot->elem;
    }

    if (subRoot->right != NULL){
        right = isOrderedRecursive(subRoot->right);
        farl = getLeft(subRoot->right);
    }
    else{
        right = true;
        farl = subRoot->elem;
    }
    if(left && right && (farl>=subRoot->elem) && (farr<=subRoot->elem)){
        return true;
    }



    else{
      return false;
    }

}




/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    // your code here
    std::vector<T> curr;
    getPaths(paths, curr, root);

}

template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths,std::vector<T> curr,Node* subRoot) const
{
    // your code here
    if(subRoot == NULL){
      return;
    }

    curr.push_back(subRoot->elem);

    if(subRoot->left == NULL && subRoot->right == NULL){
      paths.push_back(curr);
    }

    getPaths(paths,curr,subRoot->left);
    getPaths(paths,curr,subRoot->right);

    curr.pop_back();

}




/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int d = 0;

    sumDistances(d, root->left);
    sumDistances(d, root->right);

    return d;

}

template <typename T>
int BinaryTree<T>::sumDistances(int &summ, const Node * subTree) const
{
    int d = 0;

    if(subTree == NULL){
      return 0;
    }

    d = sumDistances(summ,subTree->right) + sumDistances(summ,subTree->left) + d + 1;

    summ += d;

    return d;
}
