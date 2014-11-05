#include "HashedSplays.h"

/**************************************************************
 * File:    HashedSplays.cpp
 * Project: CMSC 341 - Project 3 - Splay Trees
 * Author : Eliot Carney-Seim
 * Date  Due: 11/4/14
 * Section: 03
 * E-mail:  eliot2@umbc.edu
 *
 * The HashedSplays class methd definitions
 *
 *************************************************************/



using namespace std;


HashedSplays::HashedSplays(int size){
    HashedSplays::m_trees = size;
    HashedSplays::table = new SplayTree<Node> [size];
}

HashedSplays::~HashedSplays(){
    delete[] table;
}

void HashedSplays::FileReader(std::string inFileName){

    ifstream infile; // open the file
    infile.open(inFileName.c_str(), ios_base::in);

    char* tempWord;
    char* tempLineArray;
    char* context;
    string wordString;
    string lineTemp;
    //DOUBLE WHILES ARE NOT O(N^2) because it only goes through line once.
    //per line, per word.
    while(getline(infile, lineTemp)){ //begin getting files
        // cast into string to force stop at newline and prevent memory leak.
        tempLineArray = (char*)lineTemp.c_str();
        tempWord = strtok_r(tempLineArray, GENERIC_FILTER_LIST, &context);
        //goddamn string tok. _s and _r can both DIAF.
        while(tempWord != NULL){
            wordString += tempWord;
            wordString = Util::Strip(wordString);
            Node tempNode(wordString, 1);
            //figure out where this word is going
            int index = Util::Lower(wordString)[0]-97;
            if(index >= 0 && index<= 25){
                if(table[index].contains(tempNode)){
                    //backup node before removal
                    Node nodeToIncrease = table[index].containsWithRef(tempNode);
                    printDebug("Testing to make sure the node is a new node");

                                /*intptr_t address1 = (intptr_t)&nodeToIncrease;
                                intptr_t address2 = (intptr_t)&table[index].containsWithRef(tempNode);
                                cout << address1 << endl;
                                cout << address2 <<endl;*/

                    //remove the matching node
                    table[index].remove(tempNode);
                    //create new node with ++ to the old one's frequency
                    nodeToIncrease.IncrementFrequency();
                    //and insert it.
                    table[index].insert(nodeToIncrease);
                }else{
                    table[index].insert(tempNode);
                }
            }
            printDebug("Word being added is: " + wordString);
            wordString.clear();
            tempWord = strtok_r(NULL, GENERIC_FILTER_LIST, &context); //tokenize next word.
        }
    }
    infile.close();
}

void HashedSplays::PrintTree(int index){
    table[index].printTree();
}

void HashedSplays::PrintTree(string letter){
    int index = letter[0]-97;
    if(index >= 0 && index <= 25){
        table[index].printTree();
    }
}

void HashedSplays::FindAll(string inPart){
    inPart = Util::Lower(inPart);
    printDebug("inPart is being testted: " + inPart);
    int index = inPart[0]-97;
    SplayTree<Node> matchTree;
    SplayTree<Node> allTree;
    Node tempNode;
    while(!table[index].isEmpty()){
        //remove top node and place it into temp
        tempNode = table[index].removeWithRef(table[index].findMin());
        //test to see if it contains the inPart string
        if(tempNode.GetWord().find(inPart.c_str(), 0) == 0){
            //if it does, add to matchtree AND alltree
            printDebug("The string DOES contain inPart: " + tempNode.GetWord());
            matchTree.insert(tempNode);
            allTree.insert(tempNode);
        }else{
           //else, add to ONLY alltree
            printDebug("the string does NOT contain inPart: " + tempNode.GetWord());
            allTree.insert(tempNode);
        }
    }
    table[index] = matchTree;
    matchTree.printTree();
}

void HashedSplays::PrintHashCountResults(){
    for(int i = 0; i < m_trees-1; i++){
        table[i].printRoot();
    }


}
