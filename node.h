/* Daniel Harper
 * CS2430-001
 * Huffman coding
 */

#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

class Node
{
private:
    char cCharacter;
    int iReferenceNumber;
    Node* leftNode;
    Node* rightNode;
    Node* parentNode;
    
protected:
    Node(); //because we don't like empty nodes.  Protected in case I ever reuse this for inheritance.
    

public:
    Node(char c, int iBin);
    virtual bool operator> ( const Node& other );
    virtual bool operator< ( const Node& other );
    virtual bool operator== ( const Node& other ) const;
    void addLeft(Node * n);
    void addRight(Node * n);
    Node* getLeft();
    Node* getRight();
    vector<int> getBinaryNumber();
    int getReferenceNumber();
    char getCharacter();
};

#endif // NODE_H
