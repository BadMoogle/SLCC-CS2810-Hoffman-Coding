/* Daniel Harper
 * CS2430-001
 * Huffman coding
 */

#include "node.h"
#include <bits/ios_base.h>

//Constructor that fully populates the variables
Node::Node(char c, int iBin)
{
    cCharacter = c;
    iReferenceNumber = iBin;
    leftNode = 0;
    rightNode = 0;
}

/* Used to convert the integer form of the reference number to it's binary form.
 * Used a vector as the return type since the size of the result varies on the size of the number
 * Using algorithm 1 on page 249 of Discrete Mathmatics and It's Applications by Rosen
 * 
 * Modified for this assignment
 */
vector<int> Node::getBinaryNumber()
{
    vector<int> a, b;
    int iIterator = 0;
    int q = iReferenceNumber;
    while (q != 0)
    {
        a.push_back(q % 2);
        q /= 2;
        iIterator++;
    }
    if (a.size() < 4) //We want to chop up the bits so that 4 will be base, then anything larger than 7 will be a full 6 bits.
    {
        for (int i = 0; i <= (4 - a.size()); i++)
        {
            a.push_back(0);
        }
    }
    else if (a.size() < 6)
    {
        for (int i = 0; i <= (6 - a.size()); i++)
        {
            a.push_back(0);
        }
    }
    for (int i = a.size() - 1; i >= 0; i--)
    {
        b.push_back(a[i]);
    }
    return b;
}

// Returns the character stored in the node
char Node::getCharacter()
{
    return cCharacter;
}   

//Checks if two nodes are equivalent
bool Node::operator== ( const Node& other ) const
{
    if (this->cCharacter == other.cCharacter)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//checks if one node is greater than the other    
bool Node::operator> ( const Node& other )
{
    if (int(this->cCharacter) > int(other.cCharacter))
    {
        return true;
    }
    else
    {
        return false;       
    }
}

//checks if one node is less than the other  
bool Node::operator< ( const Node& other )
{
    if (int(this->cCharacter) < int(other.cCharacter))
    {
        return true;
    }
    else
    {
        return false;       
    }
}

//Adds a node to the left side
void Node::addLeft(Node * n)
{
    leftNode = n;
}
    
//Adds a node to the Right side
void Node::addRight(Node * n)
{
    rightNode = n;
}

//Returns the node on the left side.  0 if it doesn't exist
Node* Node::getLeft()
{
    return leftNode;
}

//Returns the node on the right side.  0 if it doesn't exist
Node* Node::getRight()
{
    return rightNode;
}

//Returns the reference number stored in the node
int Node::getReferenceNumber()
{
    return iReferenceNumber;
}