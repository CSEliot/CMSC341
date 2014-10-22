/**************************************************************
 * File:    Indexer.h
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Austin Pagano
 * Date   : 10/15/14
 * Section: 02
 * E-mail:  apagano1@umbc.edu
 *
 * Indexer class header file
 *
 *************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string>
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