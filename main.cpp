/* Daniel Harper
 * CS2430-001
 * Huffman coding
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <vector>
#include "tree.h"

using namespace std;


//Since we can't output directly on a bit-by-bit level, we need to convert it to bytes
string* convertBinary(string* s)
{
    string* strTemp = new string;
    for (int i = 0; i < (s->length() / 8); i++) //chop the string into sections of 8 for bytes
    {
        
        double tempDbl = 0;
        for (int j = 7; j >= 0; j--)
        {
            if(s->substr((i*8) + j , 1) == "1")
            {
                tempDbl = tempDbl + pow(2, j);
            }
        }
        *strTemp = *strTemp + char(int(tempDbl)); //convert the new section to a character (because ascii character stores better than a raw int)
    }

    return strTemp;
}

int main(int argc, char **argv) 
{
    // Initialize the stuff we need to grab the stats on the file (e.g. how many of each character there is)
    char cList[100]; //100 seems safe for the Engrish alphabet. 26 upper, 26 lower, 10 numbers, then special characters
    int iList[100];
    for (int i = 0; i < 100; i++)
    {
        iList[i] = 0;
    }
    int iterator = 0;
    
    long begin, end; //To calculate file sizes

    
    //First read in the file (taking into account case sensitivity)
    ifstream fLoremFile("lorem.txt");
    //Calculate the file size by subtracting the end of the file size by the beginning
    begin = fLoremFile.tellg();
    fLoremFile.seekg (0, ios::end);
    end = fLoremFile.tellg();
    cout << "Original file size : " << (end - begin) << " bytes." << endl;
    fLoremFile.seekg(0, ios::beg); //Move to the beginning to get percentages
    do 
    {
        char c;
        bool addToList = false;
        fLoremFile >> c;
        for (int i = 0; i <= iterator; i++)
        {
            if(cList[i] == toupper(c))
            {
                iList[i]++;
                addToList = true;
            }
        }
        if(!addToList)
        {
            cList[iterator] = toupper(c);
            iList[iterator]++;
            iterator++;
        }
    } while (!fLoremFile.eof());
    fLoremFile.close();
    
    
    
    //Sort the arrays based on probabilities.  Simple bubble sort since we're dealing with a small character set.
    for (int i = 0; i <= iterator; i++)
    {
      for (int j = 0; j < (iterator - i); j++)
      {
          //Swap the values if the current is greater than the next in line
          if (iList[j] > iList[j + 1])
          {
              int iTemp = iList[j];
              char cTemp = cList[j];
              iList[j] = iList[j + 1];
              cList[j] = cList[j + 1];
              iList[j + 1] = iTemp;
              cList[j + 1] = cTemp;
          }
      }
    }
    //Set up the tree and populate it with the array
    Node* tempNode = new Node(cList[iterator], 0);
    Tree * probTree = new Tree(tempNode); //Our parent Node is 0

    int iTemp = 0;
    for (int i = iterator; i >= 1; i--) //Start from end of array to get the highest probabilities first in the tree
    {
        Node * currentNode = probTree->getRoot();
        bool nodeAdded = false;
        while (nodeAdded == false)
        {
            if(iTemp == 7) //We want to skip 7 because that is our flag to use more than 4 bits for the output.
            {
                iTemp++;
            }
            if (cList[i] < currentNode->getCharacter())
            {
                // Current character is less than the current node.   Check that the left node isn't empty, if it is, add a new node there.
                if(currentNode->getLeft() != 0)
                {
                    currentNode = currentNode->getLeft(); //Move to left node if it exists
                }
                else
                {
                    Node * newNode = new Node(cList[i], iTemp);
                    iTemp++;
                    nodeAdded = true;
                    currentNode->addLeft(newNode);
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
                    Node * newNode = new Node(cList[i], iTemp);
                    iTemp++;
                    nodeAdded = true;
                    currentNode->addRight(newNode);
                }
            }
        }   
    }
    
    //build the new  file using the bytes
    string* tempString = new string;
    fLoremFile.open("lorem.txt");
    fLoremFile.seekg (0, ios::beg); //move to the beginning;
    do 
    {
        char c;
        fLoremFile >> c;
        Node* nTemp = probTree->findNode(toupper(c)); //Find the int representation of the number in the file.
        for(int i = 0; i < nTemp->getBinaryNumber().size(); i++)
        {
            *tempString = *tempString + boost::lexical_cast<string>(nTemp->getBinaryNumber()[i]); //Bad to write store the entire file in memory first, but oh well.
        }
    } while (!fLoremFile.eof());
    fLoremFile.close();
    
    //Write new file
    ofstream myLoremFile("myLorem.txt");
    myLoremFile << *convertBinary(tempString);
    myLoremFile.close();
    delete tempString;

    
    fLoremFile.open("myLorem.txt");
    //Calculate the file size by subtracting the end of the file size by the beginning
    begin = fLoremFile.tellg();
    fLoremFile.seekg (0, ios::end);
    end = fLoremFile.tellg();
    cout << "New file size using dynamic probabilities : " << (end - begin) << " bytes." << endl;
    fLoremFile.seekg(0, ios::beg); //Move to the beginning to get percentages
    fLoremFile.close();
    
    delete probTree; //Free up memory (see To-Do in tree.cpp)
    
    
    //*********************************************Outputting the problem using the probabilities on P 771***********************************************
    //Set up new array for book's probabilities
    char cBookList[100]; 
    cBookList[0] = ',';
    cBookList[1] = '.';
    cBookList[2] = 'Z';
    cBookList[3] = 'Q';
    cBookList[4] = 'J';
    cBookList[5] = 'X';
    cBookList[6] = 'K';
    cBookList[7] = 'V';
    cBookList[8] = 'B';
    cBookList[9] = 'P';
    cBookList[10] = 'G';
    cBookList[11] = 'F';
    cBookList[12] = 'Y';
    cBookList[13] = 'C';
    cBookList[14] = 'W';
    cBookList[15] = 'M';
    cBookList[16] = 'U';
    cBookList[17] = 'L';
    cBookList[18] = 'D';
    cBookList[19] = 'R';
    cBookList[20] = 'X';
    cBookList[21] = 'S';
    cBookList[22] = 'N';
    cBookList[23] = 'H';
    cBookList[24] = 'I';
    cBookList[25] = 'O';
    cBookList[26] = 'A';
    cBookList[27] = 'T';
    cBookList[28] = 'E';
    
    iterator = 28;
    
        //Set up the tree and populate it with the array
    tempNode = new Node(cBookList[iterator], 0);
    probTree = new Tree(tempNode); //Our parent Node is 0

    iTemp = 0;
    for (int i = iterator; i >= 1; i--) //Start from end of array to get the highest probabilities first in the tree
    {
        Node * currentNode = probTree->getRoot();
        bool nodeAdded = false;
        while (nodeAdded == false)
        {
            if(iTemp == 7) //We want to skip 7 because that is our flag to use more than 4 bits for the output.
            {
                iTemp++;
            }
            if (cList[i] < currentNode->getCharacter())
            {
                // Current character is less than the current node.   Check that the left node isn't empty, if it is, add a new node there.
                if(currentNode->getLeft() != 0)
                {
                    currentNode = currentNode->getLeft(); //Move to left node if it exists
                }
                else
                {
                    Node * newNode = new Node(cList[i], iTemp);
                    iTemp++;
                    nodeAdded = true;
                    currentNode->addLeft(newNode);
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
                    Node * newNode = new Node(cList[i], iTemp);
                    iTemp++;
                    nodeAdded = true;
                    currentNode->addRight(newNode);
                }
            }
        }   
    }
    
    //build the new  file using the bytes
    tempString = new string;
    fLoremFile.open("lorem.txt");
    fLoremFile.seekg (0, ios::beg); //move to the beginning;
    do 
    {
        char c;
        fLoremFile >> c;
        Node* nTemp = probTree->findNode(toupper(c)); //Find the int representation of the number in the file.
        for(int i = 0; i < nTemp->getBinaryNumber().size(); i++)
        {
            *tempString = *tempString + boost::lexical_cast<string>(nTemp->getBinaryNumber()[i]);
        }
    } while (!fLoremFile.eof());
    fLoremFile.close();
    
    //Write new file
    myLoremFile.open("bookLorem.txt");
    myLoremFile << *convertBinary(tempString);
    myLoremFile.close();

    
    fLoremFile.open("bookLorem.txt");
    //Calculate the file size by subtracting the end of the file size by the beginning
    begin = fLoremFile.tellg();
    fLoremFile.seekg (0, ios::end);
    end = fLoremFile.tellg();
    cout << "New file size using the book's probabilities : " << (end - begin) << " bytes." << endl;
    fLoremFile.seekg(0, ios::beg); //Move to the beginning to get percentages
    fLoremFile.close();
    
    delete tempString, probTree; //free up memory
    return 0;
}
