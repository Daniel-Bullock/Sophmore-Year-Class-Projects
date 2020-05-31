/* Your code here! */



#include "dsets.h"

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    set.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
  if (set[elem] < 0) {
    return elem;
  } else {
    int root = find(set[elem]);
    set[elem] = root;
    return root;
  }
}

void DisjointSets::setunion(int a, int b) {
  int parentA = find(a);
  int parentB = find(b);
  int newSize = set[parentA] + set[parentB];

  if (parentA < parentB) {
    set[parentB] = parentA;
    set[parentA] = newSize;
  } else {
    set[parentA] = parentB;
    set[parentB] = newSize;
  }
}

int DisjointSets::size(int elem) {
  return set[find(elem)] * -1;
}
