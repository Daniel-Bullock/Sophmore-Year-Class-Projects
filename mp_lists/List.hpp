/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List()   {
    head_ = NULL;
    length_ = 0;
    tail_ = NULL;
}



/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1


  ListNode * temp = head_;

  while(temp != NULL){

    ListNode * nexttemp = temp->next;
    delete temp;
    temp = nexttemp;

  }




}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  if(length_ == 0){
    head_ = newNode;
    tail_ = newNode;
    length_ = 1;

    return;
  }

  head_->prev = newNode;
  newNode->next = head_;
  head_ = head_->prev;




  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newBack = new ListNode(ndata);

  if(length_ == 0){
    head_ = newBack;
    tail_ = newBack;
    length_ = 1;

    return;
  }
  tail_->next = newBack;

  newBack->prev = tail_;
  tail_ = tail_->next;




  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  if(splitPoint < 0){
    splitPoint = 0;
  }
  if(splitPoint > length_){
    splitPoint = length_;
  }

  for (int i = 0; i < splitPoint; i++) {
    //std::cout<< i+20 <<std::endl;
    //std::cout<< curr->data <<std::endl;
    if(curr == NULL){
      return NULL;
    }
    curr = curr->next;

  }
  //std::cout<< curr->data <<std::endl;
  //std::cout<< curr <<std::endl;
  if (curr != NULL) {
      //std::cout<< "2" <<std::endl;
      curr->prev->next = NULL;
      curr->prev = NULL;
      return curr;
  }
  return NULL;

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1

  ListNode * realfront;
  ListNode * realback;
  ListNode * ogtop = head_->next;
  ListNode * ogbottom = tail_;


  while(ogtop != tail_){

    realfront = ogtop->prev;
    realback = ogtop->next;
    tail_ = ogtop;

    ogtop->prev = ogbottom;
    ogbottom->next = ogtop;

    realfront->next = realback;
    realback->prev = realfront;

    ogbottom = ogtop;

    tail_->next = NULL;

    ogtop = realback->next;


  }








}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2

  if(startPoint == endPoint){
    return;
  }

  ListNode * temp = startPoint;
  ListNode * tempnext = startPoint->next;
  ListNode * oghead = head_;
  ListNode * ogtail = tail_;
  ListNode * ogend = endPoint;
  ListNode * sogprev = startPoint -> prev;
  ListNode * ogstart = startPoint;



  temp->next = endPoint->next;

  if(endPoint->next){
    endPoint->next->prev = temp;
  }

  temp = tempnext;
  //std::cout<<"1"<<std::endl;



  while(temp != endPoint && temp != NULL){
    ListNode * ogprev = temp->prev;
    temp->prev = temp->next;
    temp->next = ogprev;
    temp = temp->prev;
  }

  //std::cout<<"2"<<std::endl;
  ListNode * tempprev = temp->prev;
  //std::cout<<"2a"<<std::endl;

  temp->prev = sogprev;
  //std::cout<<"2b"<<std::endl;

  //std::cout<<"3"<<std::endl;

  if(sogprev){
    sogprev->next = temp;
  }
  //std::cout<<"4"<<std::endl;

  temp->next = tempprev;


  if(ogstart == head_){
    head_ = ogend;
    head_->prev = NULL;
  }
  else{
    head_ = oghead;
    head_->prev = NULL;
  }


  if(ogend == tail_){
    tail_ = ogstart;
    tail_->next = NULL;
  }
  else{
    tail_ = ogtail;
    tail_->next = NULL;
  }


}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2

  //ListNode * top = head_;
  //ListNode * back = tail_;
  ListNode * begin = head_;
  ListNode * end = head_;


  while(end != NULL){
    int x = 0;

    while(x<(n-1) && end->next !=NULL){
      end = end->next;
      x = x+1;
    }

    ListNode *next = end->next;

    reverse(begin, end);

    begin = next;
    end = next;
  }





}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2


  ListNode * temp = first;
	ListNode * twoemp = second;


  if (second == NULL){
		return first;
	}

	if (first == NULL){
		return second;
	}

	if (second->data  < first->data){

    temp->prev = twoemp;
		second = twoemp->next;

		if (second != NULL){
			second->prev = NULL;
    }

		twoemp->next = temp;
		first = twoemp;
		twoemp = second;
	}

	while (second != NULL){

    		if (twoemp->data < temp->data){

          second = twoemp->next;
    			temp->prev->next = twoemp;
    			twoemp->prev = temp->prev;
    			twoemp->next = temp;
    			temp->prev = twoemp;
    			twoemp = second;

    		}else if (temp->next != NULL){

          temp = temp->next;

    		}else{

    			temp->next = twoemp;
    			twoemp->prev = temp;
    			second = NULL;

    		}
	}



	return first;


  //return NULL;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2

  //base case
  if(chainLength == 1){

    start->prev = NULL;
    start->next = NULL;
    return start;

  }

  else{

    int stopPoint = (chainLength / 2);

    ListNode* curr = start;

    for(int x=1;x<=stopPoint;x++){

      curr = curr->next;

    }

    
    if (curr != NULL){

      curr->prev->next = NULL;
      curr->prev = NULL;

    }

    //recusive steps
    curr = mergesort(curr, (chainLength-stopPoint));

    start = mergesort(start, stopPoint);

    start = merge(start, curr);

    return start;



  }



  //return NULL;
}
