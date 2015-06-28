#include <iostream>
#include <fstream>
#include "HCNode.hpp"

/* Jesse Bishop
 * jtbishop@ucsd.edu
 * Kube 
 *
 * Andrew Weaver
 * amweaver@ucsd.edu
 * Kube
 */

class BitInputStream {

  friend void finalFillIn();

  private:
  char buf; // one byte buffer of bits
  int nbits; // how many bits have been read from buf
  std::istream & in; // the input stream to use

public:
  /** Initialize a BitInputStream that will use
  * the given istream for input.
  */

  BitInputStream(std::istream & is) : in(is)
  {
	buf = 0; // clear buffer
	nbits = 8; // initialize bit index
  }

  /** Fill the buffer from the input */
  void fillIn();
 
  /* 
   * Read in the next bit from the input stream first if needed.
   * Return 1 if the bit read is 1;
   * return 0 if the bit read is 0.
   *
   */
  int readBit();

  byte bitVal(char b, int n);

  void finalFillIn();
};
