/**************************************************************
 * File:    driver.cpp
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : 
 * Date   : 04-November-2014
 * Section: Lecture-02
 * E-mail:  
 *
 * HashedSplays Class implementation.
 *
 *************************************************************/
#include "HashedSplays.h"  // Includes constants
#include "Util.h"
using namespace std;

int main(int argc, char* argv[]){

    string testStr = "-Pie-s12@-p^-";
    string findTest = "to";
    printDebug(testStr + "g");
    printDebug("Test");
    printDebug(testStr = Util::Lower(testStr));
    printDebug(testStr = Util::Strip(testStr));
    bool fileIs = Util::FileExists(argv[1]);
    cout << "Does this file exist? " << argv[1] << " " << fileIs << endl;
    HashedSplays testHash(26);
    testHash.FileReader(argv[1]);
    testHash.PrintTree(18);
    testHash.PrintTree(19);
    testHash.PrintTree(20);
    testHash.FindAll(findTest);
    return 0;
}

/*
int main(int argc, char *argv[]) {
    try {
        // Instatiate the main object
        HashedSplays wordFrequecy(ALPHABET_SIZE);
        // Build the trees
        wordFrequecy.FileReader(argv[1]);

        // Test methods to show hashed splay trees work
        wordFrequecy.PrintHashCountResults();
        wordFrequecy.PrintTree(19); // Prints the "T" tree
        wordFrequecy.PrintTree("F");
        wordFrequecy.PrintTree("K"); // should be mpty running input1
        wordFrequecy.FindAll("The"); // should find all the's (ignoring case)
        cout << endl;
    }

    // Error catching
    catch (Exceptions &cException) {
        cout << "EXCEPTION: " << cException.GetMessage() << endl;
        return 1;
    }
    
    //Uncomment for number of seconds running.
    //cout << clock() / (float)CLOCKS_PER_SEC) << endl;
    return 0;
}*/
