/* Daniel Harper
 * CS2430-001
 * Huffman coding
 */

#ifndef TREE_H
#define TREE_H

#include "node.h"

class Tree
{
private:
    Node * rootNode;
    
public:
    Tree(Node* n);
    virtual ~Tree();
    Node* getRoot();
    Node* findNode(char c);
};

#endif // TREE_H
