/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
     if (first[curDim] < second[curDim]) {
       return true;
     } else if (first[curDim] > second[curDim]) {
       return false;
     } else {
       return first < second;
     }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
     double currBestToTarg = 0;
     double potentialToTarg = 0;

     //(p-q)^2
     //minimum of distance squared is the same as minimum of distance
     for (unsigned i = 0; i < Dim; i++) {
       currBestToTarg = currBestToTarg + ((target[i] - currentBest[i]) * (target[i] - currentBest[i]));
       potentialToTarg = potentialToTarg + ((target[i] - potential[i]) * (target[i] - potential[i]));
     }

     if (potentialToTarg < currBestToTarg) {
       return true;
     } else if (potentialToTarg > currBestToTarg) {
       return false;
     } else  {
       return potential < currentBest;
     }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
     root = constructorHelper(newPoints, 0);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    return fNN(query, root, 0);
}
