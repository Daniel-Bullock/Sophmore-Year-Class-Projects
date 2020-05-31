/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here


      Node * r = t->right;

      t->right = r->left;
      r->left = t;

      r->height = new_height(r);
      t->height = new_height(t);

      t = r;



}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * l = t->left;


    t->left = l->right;
    l->right = t;

    l->height = new_height(l);
    t->height = new_height(t);

    t = l;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here

    if (subtree == NULL){
         return;
    }

    int b = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

    if (b == -2){
         int bl = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
         if (bl < 0) {
             rotateRight(subtree);
         }
         else {
             rotateLeftRight(subtree);
         }
    }else if (b == 2){
         int br = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
         if (br > 0) {
             rotateLeft(subtree);
         }
         else {
             rotateRightLeft(subtree);
         }
    }



}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here


    if(subtree == NULL){
      subtree = new Node(key,value);
      return;
    }else if(key>subtree->key){
      insert(subtree->right,key,value);
    }else if(key<subtree->key){
      insert(subtree->left,key,value);
    }

    if(heightOrNeg1(subtree->left)>heightOrNeg1(subtree->right)){
      subtree->height = 1+heightOrNeg1(subtree->left);
    }else{
      subtree->height = 1+heightOrNeg1(subtree->right);
    }

    rebalance(subtree);


}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left,key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * tmpNode = subtree->left;
            while(tmpNode->right != NULL){
              tmpNode = tmpNode->right;
            }
            subtree->key = tmpNode->key;
            subtree->value = tmpNode->value;
            remove(subtree->left,tmpNode->key);


        } else {
            /* one-child remove */
            // your code here
            Node * tmp;
            if(subtree->left != NULL){
              tmp = subtree->left;


            }else{
              tmp = subtree->right;
            }
            delete subtree;
            subtree = tmp;
        }
        // your code here

    }

    if(heightOrNeg1(subtree->left) > heightOrNeg1(subtree->right)){
      subtree->height = 1 + heightOrNeg1(subtree->left);
    }else{
      subtree->height = 1 + heightOrNeg1(subtree->right);
    }
    rebalance(subtree);
}
template <class K, class V>
int AVLTree<K, V>::new_height(Node*& n)
{
  if(n == NULL){    //go back one if it's NULL
    return -1;
  }
  if(new_height(n->right) > new_height(n->left)){
    return 1 + new_height(n->right);
  }
  else{
    return 1 + new_height(n->left);
  }



}
