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

int main(int argc, char * argv[]){

    //get the filename from argv[]
    ifstream in (argv[1]);

    //Create a vector to hold the character frequencies
    vector<int> frequency (256, 0);

    //Create a char variable to hold the charater from the stream
    unsigned char ch;

    // Number of unique symbols
    int uniqueS = 0;

    //create an integer to hold frequency of parsed string
    int freqNumber = 0;

    //Check that the file exists
    if(in.is_open())
    {        
        //Declare a char for the integers only
        unsigned char numChar = '\0';

        //Create string to get full frequency in char form
        unsigned int indexCounter = 0;

        //Create an array to hold the integer frequency
        char numArray[10] = {}; 

        //Get the character 
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

	cout << "Reading header from file " << argv[1] << "... ";
        //Loop to get the header
        while(in.good() && (unsigned int)ch >= 0)
        {
            //The header is terminated with the null
            //character, so break when this happens
            if(ch == '\0')
            {
                break;                
            }
            else
            {                
                //Ignore the space
                in.ignore();

                //Parse the string until we hit a space
                while((numChar = in.get()) != ' ')
                {
                    numArray[indexCounter] = numChar;
                    indexCounter++;
                }

                //Convert string to integer
                freqNumber = atoi(numArray);
                frequency[(unsigned int) ch] = freqNumber; 
                
                //Reset the array to null values
                //not efficient...
                for(unsigned int j = 0; j < 10; j++)
                    numArray[j] = '\0';        

                //Reset the index counter
                indexCounter = 0;        
            }
            //Get the character 
            ch = in.get();
	    uniqueS++;
        }
	cout << "done." << endl;
    }
    else
    {
        //Specified file was not found
        cout << "No readable file was found" << endl;
	in.close();
        return 0;
    }

    cout << "Uncompressed file will have " << uniqueS << " unique symbols" << endl;
    cout << "Building Huffman coding tree... ";
    //Build the Huffman tree based on the frequencies
    HCTree* huffTree = new HCTree();
    huffTree->build(frequency); 
    cout << "done." << endl;

    ///////////////////////////////////////////////
    //open the output file to scan and read from///
    ///////////////////////////////////////////////

    //Create a stream to write to using the second command
    //line arguement
    ofstream out;
    out.open(argv[2]);
        
    //Create a BitInputStream
    BitInputStream toFile(in);

    //Check that the file exists
    if(in.is_open())
    {
	cout << "Writing to file " << argv[2] << "... ";
	unsigned int decodedAscii;
        decodedAscii = huffTree->decode(toFile);
        //Loop until you have reached the end of the file
        while(decodedAscii >= 0 && in.good() && decodedAscii != 256)
	{
            out.put((unsigned char) decodedAscii);
            decodedAscii = huffTree->decode(toFile);
        }
	
	toFile.finalFillIn();		 
	huffTree->~HCTree();
	cout << "done." << endl;
        //close the file
        in.close();
        out.close();
    }
    else
    {
	//Specified file was not found
        cout << "No readable file was found" << endl;
	in.close();
	out.close();
        return 0;
    }
    return 0;
}
