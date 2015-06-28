#include "HCTree.hpp"
#include "HCNode.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


int main(int argc, char * argv[]){

        //get the filename from argv[]
   ifstream in (argv[1]);

        //Create a vector to hold the character frequencies
        vector<int> frequency (256, 0);

        //Create a char variable to hold the charater from the stream
        unsigned char ch;

        //Check that the file exists
        if(in.is_open()){        
                
                ch = in.get();
                //frequency[(unsigned int) ch]++;                

                //Loop until you have reached the end of the file
                while(((unsigned int)ch >=0) && in.good()){
                        frequency[(unsigned int) ch]++; 
                        ch = in.get();
                }

                //close the file
                in.close();

        }else{

                //Specified file was not found
           cout << "No readable file was found" << endl;
                return 0;
        }


        //Build the Huffman tree based on the frequencies
        HCTree* huffTree = new HCTree();
   huffTree->build(frequency); 

        ///////////////////////////

        //Create a stream to read from
   ifstream input(argv[1]);

        //Create a stream to write to        using the second command
        //line arguement
        ofstream out;
        out.open(argv[2]);
        
        //create a BitOutputStream to write 1 bit at a time
        BitOutputStream toFile(out);

        unsigned int j;

        //Encode the header so that a tree can be reconstructed
        for(j = 0; j < frequency.size(); j++){
                if(frequency[j] != 0){

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

//////////////////////////////////////////////////////////////////


        //Create a char variable to hold the charater from the stream
        unsigned char charToEncode;

        //Check that the file exists
        if(input.is_open()){        
                
                charToEncode = input.get();
                huffTree->encode(charToEncode, toFile);

                //Loop until you have reached the end of the file
                while(((unsigned int)charToEncode >=0) && input.good()){
                        charToEncode = input.get();
                        huffTree->encode(charToEncode, toFile);
                }

                //close the file
                input.close();

        }else{

                //Specified file was not found
           cout << "No readable file was found" << endl;
                return 0;
        }



///////////////////////////////////////////////////////////////////
                
        out.close();


        
        return 0;

}                        

