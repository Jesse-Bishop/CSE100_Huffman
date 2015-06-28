#include "BitInputStream.hpp"

/* Jesse Bishop
 * jtbishop@ucsd.edu
 * Kube 
 *
 * Andrew Weaver
 * amweaver@ucsd.edu
 * Kube
 */

/** Fill the buffer from the input */
void BitInputStream::fillIn()
{
    buf = in.get();
    nbits = 0;
}

 /* 
 * Read in the next bit from the input stream first if needed.
 * Return 1 if the bit read is 1;
 * return 0 if the bit read is 0.
 */
int BitInputStream::readBit()
{
    // If all bits in the buffer are read, fill the buffer first
    if(nbits == 8)
    {
	fillIn();
    }

    // Get the bit at the appriopriate location in the bit
    // buffer, and return the appropriate int
    int i;
    i = bitVal(buf, 7- nbits);
	
    // Increment the index
    nbits++;

    return (int) i;	
}

byte BitInputStream::bitVal(char b, int n)
{
    return (byte)(b >> n) & 1;
}

void BitInputStream::finalFillIn()
{
    if(nbits == 0)
    {
	return;
    }
    else
    {
	fillIn();
    }
}
