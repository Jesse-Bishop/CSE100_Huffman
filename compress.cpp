#include "HCTree.hpp"
#include "HCNode.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

/* Jesse Bishop
 * jtbishop@ucsd.edu
 * Kube 
 *
 * Andrew Weaver
 * amweaver@ucsd.edu
 * Kube
 */

using namespace std;

int main(int argc, char * argv[])
{
   //get the filename from argv[]
   ifstream in (argv[1]);

   //Create a vector to hold the character frequencies
   vector<int> frequency (256, 0);

   // Number of unique symbols in file
   int uniqueS = 0;

   //Create a char variable to hold the charater from the stream
   unsigned char ch;

   //Check that the file exists
   if(in.is_open())
   {
	cout << "Reading from file " << argv[1] << "... ";

	ch = in.get();

	if(in.gcount() < 1)
	{
	    cout << "Uncompressible file" << endl;
	    cout << "Nothing written to file " << argv[2] << endl;
	    ofstream out (argv[2]);
	    in.close();
	    out.close();
	    return 0;
	}
	//Loop until you have reached the end of the file
	while(((unsigned int)ch >=0) && in.good())
	{
	    if(frequency[(unsigned int) ch] == 0)
	    {
		uniqueS++;
	    }
	    frequency[(unsigned int) ch]++;
	    ch = in.get();
	}

	//close the file
	in.close();
   }
   else
   {
	//Specified file was not found
	cout << "No readable file was found" << endl;
	in.close();
	return 0;
   }
   
   cout << "done." << endl;
   cout << "Found " << uniqueS << " unique symbols in input file of size ";
   cout << sizeof(argv[1]) << " bytes" << endl;

   cout << "Building Huffman code tree... ";
   //Build the Huffman tree based on the frequencies
   HCTree* huffTree = new HCTree();
   huffTree->build(frequency); 
   cout << "done." << endl;

   ////////////////////////////////////////
   //Create the header for huffTree      //
   ////////////////////////////////////////

   //Create a stream to read from
   ifstream input(argv[1]);

   //Create a stream to write to using the second command
   //line arguement
   ofstream out;
   out.open(argv[2]);
	
   //create a BitOutputStream to write 1 bit at a time
   BitOutputStream toFile(out);

   unsigned int j;

   cout << "Writing to file " << argv[2] << "... ";
   //Encode the header so that a tree can be reconstructed
   for(j = 0; j < frequency.size(); j++)
   {
	if(frequency[j] != 0)
	{
	    //Format is: char [space] frequency [space] (repeat)
	    out.put(j);
	    out.put(' ');	
		
	    //Need to convert int frequency to string
	    string s = to_string(frequency[j]);
		 
	    //parse the sting to print entire frequency integer
	    for(unsigned int k = 0; k < s.length(); k++)
		out.put(s[k]);
		 
      	    //Another space for formatting
	    out.put(' ');	 
	}
   }

   char charNull = '\0';
   //Use a null Char to signal end of header for uncompress
   out.put(charNull);

//////////////////////////////////////////////////////////////////

   //Create a char variable to hold the charater from the stream
   unsigned char charToEncode;

   //Check that the file exists
   if(input.is_open())
   {	
	charToEncode = input.get();
	//Loop until you have reached the end of the file
	while(((unsigned int)charToEncode >=0) && input.good())
	{
	    huffTree->encode(charToEncode, toFile);
	    charToEncode = input.get();
	}

	//close the file
	toFile.finalFlushOut();
   	cout << "done." << endl;


	input.close();
	out.close();
	huffTree->~HCTree();
   }
   else
   {
	//Specified file was not found
	cout << "No readable file was found" << endl;
	input.close();
	out.close();
	return 0;
   }
   return 0;
}
