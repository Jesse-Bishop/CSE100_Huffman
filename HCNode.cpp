#include <iostream>
#include "HCNode.hpp"

/* Jesse Bishop
 * jtbishop@ucsd.edu
 * Kube 
 *
 * Andrew Weaver
 * amweaver@ucsd.edu
 * Kube
 */


using namespace std;

/** Check to see whether one is equavelant to other
*   node.
*  RETURNS: True if the nodes are equal, false otherwise
*/  

bool comp(HCNode* one, HCNode* other)
{
 if(one->count == other->count){
  if(one->symbol == other->symbol){
   if(one->c0 == other->c0){
    if(one->c1 == other->c1){
     if(one->p == one->p){
      return true;
      }else{
       return false;
      }
     }else{
      return false;
     }
    }else{
     return false;
    }
   }else{
    return false;
   }
  }else{
   return false;
 }
 return false;
}



  /** Less-than comparison, so HCNodes will work in std::priority_queue
   *  We want small counts to have high priority.
   *  And we want to break ties deterministically.
   */

bool HCNode::operator<(const HCNode& other)
{
  if(count != other.count)
  { 
    return count > other.count;
  }
  else
  {
    return symbol > other.symbol;
  }
}

 /**
 * Returns the value, 1 or 0, of the nth bit from the right of a byte arguement.
 * PRECONDITION: n must be an integer less than or equal to 8.
 * RETURNS: The byte value where the LSB is either 1 or 0, depending on the 
 * bit value at the nth position.
 */
byte bitVal(char b, int n)
{
   return (byte)(b >> n) & 1;
}
