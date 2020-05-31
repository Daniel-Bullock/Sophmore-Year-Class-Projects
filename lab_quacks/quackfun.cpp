/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{

    // Your code here

    /*T summed = T();
    stack<T> tmp;

    //base case
    if(!s.empty()){

      T topp = s.top();
      tmp.push(topp);
      s.pop();
      summed = sum(s)+ T(topp); //recusive step

    }

    //iterate through temp stack putting elements back on stack
    while(!tmp.empty()){
      s.push(tmp.top());
      tmp.pop();

    }*/


    if(s.size() == 0){
      return 0 ;
    }
    T tmp = s.top();
    s.pop();
    T summed = tmp + sum(s);
    s.push(tmp);




    return summed; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic

    stack<char> x;

    if(input.size() == 0){
      return true;
    }

    for(unsigned i = 0; i < input.size(); i++){
      if(input.front() == '['){
            x.push('[');

      }
      if(input.front() == ']'){
            //if there hasnt been an open yet its unbalanced
            if(x.size() == 0){
              return false;
            }
            //if there is an open at the top of stack its true so you can pop it off
            if(x.top() == '['){
              x.pop();

            }
            //if it's some other character at the front then it is unbalanced
            else{
              return false;
            }

      }

      //push front to back
      input.push(input.front());
      input.pop();
    }

    if(x.size() != 0){
      return false;
    }

    return true;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    // optional: queue<T> q2;
    queue<T> q2;

    // Your code here


    T tmp;

    int c = 1;
    while(!q.empty()){
              if(c % 2 == 0){
                for(int i = 0; i < c; i++){
                    if(!q.empty()){
                      tmp = q.front();
                      q.pop();
                      s.push(tmp);
                    }
                }
                while(!s.empty()){
                    tmp = s.top();
                    q2.push(tmp);
                    s.pop();
                }
              }
              else{

                for(int i = 0; i < c; i++){
                  tmp = q.front();
                  q.pop();
                  q2.push(tmp);
                }


              }

              c+=1;

            }



    while(!q2.empty()){

          q.push(q2.front());
          q2.pop();

    }



    return;




}

/**
 * Checks if the parameter stack and queue are the same. A stack and a queue
 * are considered to the "the same" if they contain only elements of exactly
 * the same values in exactly the same order.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note The back of the queue corresponds to the top of the stack!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 *
 * @param s The stack to compare
 * @param q The queue to compare
 * @return  true if the stack and the queue are the same; false otherwise
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    T one; // rename me
    T two; // rename :)

    // Your code here


  	if(s.size()==0){
  		return true;
    }


  	one = s.top();
  	s.pop();

  	retval = verifySame(s,q);
  	two = q.front();
  	q.pop();

    if(retval && one == two){
      retval = true;
    }
    else{
      retval = false;
    }


  	q.push(two);
  	s.push(one);




    return retval;
}

}
