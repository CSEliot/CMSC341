/**************************************************************
 * File:    Indexer.cpp
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Eliot Carney-Seim
 * Date  Due: 10/21/14
 * Section: 03
 * E-mail:  eliot2@umbc.edu
 *
 * The Indexer class methd definitions
 *
 *************************************************************/

#include "Indexer.h"
#include <cstdlib>
#include <fstream>

#include <string.h>
using namespace std;
const char GENERIC_FILTER_LIST[] = "\t \n \r '.!#$%&()`*+,./0123456789:;<=>?@[]^_`~{|}\";";
//the above was found online as a resource for general exception cases for filtering.


Indexer::Indexer(string filterName, string dataFile){
	if ((FileExists(filterName)) && (FileExists(dataFile))) {
		datafile = dataFile;
		filterfile = filterName;
	}else { 
        //file not found exception
        throw IllegalArgumentException();
    }
}

void Indexer::FileFilterReader(string filterName){
    //Specifically for file filter, using trick for distinguishing between the 2.
    ifstream infile; //open the file
	infile.open(filterName.c_str(), ios_base::in);
    string wordText; //initialize extracted text.
	
    int lineNumber = -1; //a trick for controller filtering or not in the word class.

	while(getline(infile, wordText)){
        // while there is a thing to get get
        Word word(wordText, lineNumber); //RAII instantiation to prevent need for delete.
		filteredBST.insert(word);
	}
	infile.close();
}

void Indexer::FileWordReader(string dataFile){
    ifstream infile; // open the file
	infile.open(dataFile.c_str(), ios_base::in);
    int lineNumber = 0; // 0 designated NOT filter.

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
		lineNumber += 1;
        tempWord = strtok_r(tempLineArray, GENERIC_FILTER_LIST, &context);
        //goddamn string tok. _s and _r can both DIAF.
		while(tempWord != NULL){
            wordString += tempWord;
            Word word(wordString,lineNumber);

            if ( (wordString.find('-', 0) != wordString.size() - 1) //if hyphen is IN the word at 0
                 && !filteredBST.contains(word) // if NOT already in the BST
                 && (wordString.find('-', 0) != 0)){ // and hyphen not at beginning, so IN word

                indexedBST.find(word).CountWord(lineNumber); // word count ++, from 0, etc.
                indexedBST.insert(word); //insert word, but not duplicate
			}
            wordString.clear();
            tempWord = strtok_r(NULL, GENERIC_FILTER_LIST, &context); //tokenize next word.
		}
	}
	infile.close();
}

void Indexer::DoIndex(){
    //build BSTs
	FileFilterReader(filterfile);
	FileWordReader(datafile);
    OutputResults(); //print everything out.
}

void Indexer::OutputResults(){
    ofstream out1("filterResults.txt");
    streambuf *coutbuf1 = cout.rdbuf();
    cout.rdbuf(out1.rdbuf());
    filteredBST.printTree();
    cout.rdbuf(coutbuf1);

    ofstream out2("indexResults.txt");
    streambuf *coutbuf2 = cout.rdbuf();
    cout.rdbuf(out2.rdbuf());
    indexedBST.printTree();
    cout.rdbuf(coutbuf2);
}

bool Indexer::FileExists(string filename){
	ifstream infile;
	infile.open(filename.c_str(), ios_base::in);

    // run fail check on file
    if(infile.fail()) {
        return false;
    }
	
	//the file was able to be opened
	else {
		infile.close();
		return true;
	}
}
