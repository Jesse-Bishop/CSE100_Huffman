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

class BitOutputStream {

friend void finalFlush();

private:
	char buf; // one byte buffer of bits
	int nbits; // how many bits have been written to buf
	std::ostream & out; // reference to the output stream to use
public:

// Initialize a BitOutputStream that will use
// the given ostream for output.
//
BitOutputStream(std::ostream & os) : out(os) {
	buf = nbits = 0; // clear buffer and bit counter
}

// Send the buffer to the output, and clear it /
void flushOut();

// Write the least significant bit of the argument to
// the bit buffer, and increment the bit buffer index.
// But flush the buffer first, if it is full.
int writeBit(int i);

//  Sets the value, 1 or 0, of the nth bit from the right of a byte 
//  arguement.
//  POSTCONDITION: Leaves the bits unchanged 
//  RETURNS: The result of the changed bit
byte setBit(char b, int bit, int n);

// Flush any remaining bits
void finalFlushOut();
};
