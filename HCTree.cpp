#include "HCTree.hpp"
#include "HCNode.hpp"


/* Jesse Bishop
 * jtbishop@ucsd.edu
 * Kube 
 *
 * Andrew Weaver
 * amweaver@ucsd.edu
 * Kube
 */


/** Helper method that creates the tree by 
 *  iterativly creating a parent node and pushing
 *  back onto the priority queue
 */
HCNode * createTree(std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> priQueue)
{
    //Create a parent node as well as 2 temp nodes 
    HCNode* parentNode; 

    while(priQueue.size() > 1)
    {
	//Create a RC and LC child for the parent node
        HCNode *LC;
        HCNode *RC;

        //Pop from the queue and make these the right
        //child and left child
        //Pop returns void. Must use top to get element,then delete it
	RC = priQueue.top();
	priQueue.pop();

	LC = priQueue.top();
	priQueue.pop();

 	// Get constructor values 
	// make the new parent node with appropriate values 
	parentNode = new HCNode((RC->count + LC->count),0,RC,LC,0,0);

        //Set the isChild fields
        LC->p = parentNode;
        LC->isChild1 = 1;

        RC->p = parentNode;
        RC->isChild1 = 0;

	//Push the new node back onto the queue
        priQueue.push(parentNode);
    }
    return priQueue.top();
}


/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs)
{
    unsigned int i;
    //This was added from LEC9 page 42
    std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pq;

    HCNode * newNode;

    for(i = 0; i < freqs.size(); i++)
    {
	if(freqs[i] != 0)
	{
		newNode = new HCNode(freqs[i], (unsigned char) i, 0,0,0,0);
		pq.push(newNode);
	}
     	leaves[i] = newNode;
    }        
		
    // Build the tree  
    root = createTree(pq);                           
}

// Recursive function to write each bit in proper order
void writePattern(HCNode * node, BitOutputStream& out)
{
    if(node->p != NULL)
    {
	writePattern(node->p, out);
	out.writeBit(node->isChild1);
    }
    return;
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
   HCNode * node = leaves[(int) symbol];
   writePattern(node, out);
}


/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const
{
    HCNode * currNode = root;
    int bit;
    
    while(currNode->c0 != 0 && currNode->c1 != 0)
    {
	bit = in.readBit();
	if(bit == 1)
	{
            currNode = currNode->c1;
        }
	else if (bit == 0)
        {
            currNode = currNode->c0;
        }
	else
	{
	    return 256;
	}
    }
    int ret = (int) currNode->symbol;  
    return ret;
}
