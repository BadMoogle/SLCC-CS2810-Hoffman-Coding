/* Daniel Harper
 * CS2430-001
 * Huffman coding
 */

#include "tree.h"

Tree::Tree(Node* n)
{
    rootNode = n;
}

Tree::~Tree()
{
    //To-Do: properly clean the tree of nodes on the heap to free up memory.
}

        
Node* Tree::getRoot()
{
    return rootNode;
}

//Finds the node in the tree that has character c in it.
Node* Tree::findNode(char c)
{
    Node* currentNode = rootNode;
    while (true)
    {
        if (c == currentNode->getCharacter())
        {
            return currentNode;
        }
        else if (c < currentNode->getCharacter())
        {
            // Current character is less than the current node.   Check that the left node isn't empty, if it is, add a new node there.
            if(currentNode->getLeft() != 0)
            {
                currentNode = currentNode->getLeft(); //Move to left node if it exists
            }
            else
            {
                return 0;
            }
        }
        else //was greater than current node so we add it to the right
        {
            // Current character is greater than the current node.   Check that the right node isn't empty, if it is, add a new node there.
            if(currentNode->getRight() != 0)
            {
                currentNode = currentNode->getRight(); //Move to right node if it exists
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}

