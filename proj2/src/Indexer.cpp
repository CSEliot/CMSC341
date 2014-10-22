/**************************************************************
 * File:    Indexer.cpp
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Austin Pagano
 * Date   : 10/15/14
 * Section: 02
 * E-mail:  apagano1@umbc.edu
 *
 * Indexer class method definitions
 *
 *************************************************************/

#include "Indexer.h"
#include <fstream>
#include <cstdlib>

#include <string.h>
using namespace std;

//the list of characters that need to be ignored when reading in words
char IGNORE_LIST[] = " \t\n!#$%&()*+,./0123456789:;<=>?@[]^_`~{|}\"";

Indexer::Indexer(string filterName, string dataFile)
{
	if ((FileExists(filterName)) && (FileExists(dataFile))) 
	{
		datafile = dataFile;
		filterfile = filterName;
	}

	//one or more of the files were not found, send error
	else { 
		throw IllegalArgumentException(); }

}

void Indexer::FileFilterReader(string filterName)
{
	//open the file
	ifstream infile;
	infile.open(filterName.c_str(), ios_base::in);
	string wordText;
	
	//distinguish between a word for filtered BST and indexed BST
	int lineNumber = -1;

	//read in one line of the file
	while(getline(infile, wordText))
	{
		//get each word from the filter file

		Word word = Word(wordText, lineNumber);

		filteredBST.insert(word);
	}
	infile.close();
}

void Indexer::FileWordReader(string dataFile)
{
	
	//open the file
	ifstream infile;
	infile.open(dataFile.c_str(), ios_base::in);
	
	int lineNumber = 0;

	string wordText;
	string tempLineStr;
	char* tempWord;
	char* context;
	char* tempLineChar;

	//read in all words from the file
	while(getline(infile, tempLineStr))
	{
		//get the line as string so that it will stop at '\n' 
		//and not have to allocate memory

		tempLineChar = (char*)tempLineStr.c_str();

		lineNumber += 1;

        tempWord = strtok_r(tempLineChar, IGNORE_LIST, &context);

		while(tempWord != NULL)
		{
			wordText += tempWord;
			
			Word word = Word(wordText,lineNumber);

			if (!filteredBST.contains(word) && (wordText.find('-', 0) != wordText.size() - 1) && (wordText.find('-', 0) != 0))
			{
				//this will look for the word in the BST, if found
				//it will add one to that word's count and queue
				//if not found then it will make the initial count for the new
				//word
				indexedBST.find(word).CountWord(lineNumber);

				//insert the new word, will not insert it if it is a duplicate
				indexedBST.insert(word);
			}
			//do not insert if it exists in the filtered BST
			wordText.clear();
            tempWord = strtok_r(NULL, IGNORE_LIST, &context);
		}
	}
	infile.close();
}

void Indexer::DoIndex()
{
	//read in the files to make their BSTs
	FileFilterReader(filterfile);
	FileWordReader(datafile);

	OutputResults();

}

void Indexer::OutputResults()
{
	//filteredBST.printTree();
	indexedBST.printTree();
}

bool Indexer::FileExists(string filename)
{
	ifstream infile;
	infile.open(filename.c_str(), ios_base::in);

	 //if the opening failed
	if(infile.fail()) {return false;}
	
	//the file was able to be opened
	else 
	{
		infile.close();
		return true;
	}
}
