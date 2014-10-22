/**************************************************************
 * File:    Indexer.h
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Eliot Carney-Seim
 * Date  Due: 10/21/14
 * Section: 03
 * E-mail:  eliot2@umbc.edu
 *
 * The Indexer class heder file
 *
 *************************************************************/

#include <string>
#include <iostream>
#include <stdlib.h>
#include "BinarySearchTree.h"
#include "exceptions.h"


#ifndef INDEXER_H
#define INDEXER_H

class Indexer
{
public:
	Indexer(std::string filterName, std::string dataFile);
	void DoIndex();

private:
    bool FileExists(std::string filename);
	void FileFilterReader(std::string filename);
	void FileWordReader(std::string filename);
	void OutputResults();

	BinarySearchTree<Word> filteredBST;
	BinarySearchTree<Word> indexedBST;
	std::string datafile;
	std::string filterfile;
};

#endif
