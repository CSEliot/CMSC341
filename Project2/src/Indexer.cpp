/**************************************************************
 * File:    Indexer.cpp
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Eliot Carney-Seim
 * Date Due: 10/21/14
 * Section: 03
 * E-mail:  eliot2@umbc.edu
 *
 * Indexer class method definitions
 *
 *************************************************************/

#include "Indexer.h"
#include <fstream>
using namespace std;

Indexer::Indexer(string filterName, string dataFile)
{
	if ((FileExists(filterName)) && (FileExists(dataFile))) {
		datafile = dataFile;
		filterfile = filterName;
		cout << "Files Found. Continuing." << endl;
	}

	//one or more of the files were not found, send error
	else { 
		cout << "how did I get in here?" << endl;
		throw IllegalArgumentException(); 
	}

}

void Indexer::FileFilterReader(string filterName)
{
	//open the file
	ifstream infile;
	infile.open(filterName.c_str(), ios_base::in);

	int lineNumber = 0;
	string wordText;

	//read in all words from the file
	while(!infile.eof())
	{
		string line;
		getline(infile, line);

		lineNumber += 1;

		int size = line.size();

		//line size may need to be changed to check for size of 0 not 1
		for (int i = 0; i <= size; i++)
		{
			//check if we are at the end of reading a word
			if (((line[0] == ' ') || (line[0] == NULL)) && (wordText.size() > 0))
			{
				//the word is complete and should not add a space
				Word word(wordText, lineNumber);
				
				//check if the word is a duplicate
				if (filteredBST.contains(word))
				{
					filteredBST.find(word).CountWord(lineNumber);
				}

				//the word is a new word so add to BST
				else
				{
					filteredBST.insert(word);
				}
				

				//now clear the wordtext
				wordText.clear();
			}

			//word not complete
			else 
			{
				//add the next letter
				wordText += line[0];
			}

			//now delete the letter added or space
			line.erase(line.begin());
		}
	}
	infile.close();
}

void Indexer::FileWordReader(string dataFile)
{
	//open the file
	ifstream infile;
	infile.open(dataFile.c_str(), ios_base::in);

	//read in all words from file
	while (!infile.eof())
	{
		string word;
		infile >> word;

		//make sure the word is not to be ignored
		if (!filteredBST.contains(word))
		{
			indexedBST.insert(word);
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