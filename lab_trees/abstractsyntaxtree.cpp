#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return eval(root);
}
double AbstractSyntaxTree::eval(AbstractSyntaxTree::Node*subTree) const {
    // @TODO Your code goes here...
    if(subTree == NULL){
      return -1;
    }
    if(subTree->elem == "*"){
      return eval(subTree->left) * eval(subTree->right);
    }
    if(subTree->elem == "/"){
      return eval(subTree->left) / eval(subTree->right);
    }
    if(subTree->elem == "+"){
      return eval(subTree->left) + eval(subTree->right);
    }
    if(subTree->elem == "-"){
      return eval(subTree->left) - eval(subTree->right);
    }
    else{
      return std::stod(subTree->elem);
    }
}
