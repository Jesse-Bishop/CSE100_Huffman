#include "BitOutputStream.hpp"

/* Jesse Bishop
 * jtbishop@ucsd.edu
 * Kube 
 *
 * Andrew Weaver
 * amweaver@ucsd.edu
 * Kube
 */

// Send the buffer to the output, and clear it /
void BitOutputStream::flushOut()
{
    out.put(buf);
    out.flush();
    buf = nbits = 0;
}


// Write the least significant bit of the argument to
// the bit buffer, and increment the bit buffer index.
// But flush the buffer first, if it is full.

int BitOutputStream::writeBit(int i)
{
    // Write the least significant bit of i into the buffer
    // at the current index
    buf = setBit(buf, i, 7 - nbits);

    // Increment the index
    nbits++;

    if(nbits == 8)
    {
	flushOut();
    }
    return nbits;
}

//  Sets the value, 1 or 0, of the nth bit from the right of a byte 
//  arguement.
//  POSTCONDITION: Leaves the bits unchanged 
//  RETURNS: The result of the changed bit
byte BitOutputStream::setBit(char b, int bit, int n)
{
    if(bit == 1)
    {
	return (byte)b | (1 << n);
    }
    else
    {
	return (byte)b & (~(1 << n));                
    }        
}

void BitOutputStream::finalFlushOut()
{
    if(nbits == 0)
    {
	return;
    }
    else
    {
	flushOut();
    }
}
