/**************************************************************
 * File:    Word.h
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Eliot Carney-Seim
 * Date  Due: 10/21/14
 * Section: 03
 * E-mail:  eliot2@umbc.edu
 *
 * Word class header file
 *
 *************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <queue>
#include <sstream>

#ifndef WORD_H
#define WORD_H

class Word
{
public:
	Word();
	Word(std::string inWord, int lineNumber = 0);

	//adds a count to the word counter and adds the line number 
	//to the queue if the line number is not already in there
	void CountWord(int lineNumber);

	std::string GetWord() const;
	int GetCount() const;
	std::queue<int> GetLineNumbers() const;

	bool operator< (const Word &RHS) const;
	Word operator= (const Word &RHS);
	bool operator== (const Word &RHS) const;
	void ToLower(std::string & inWord);

	friend std::ostream& operator<< (std::ostream& out, const Word &inWord);

private:
	int count;
	std::queue<int> lineNumbers;
	std::string wordText;

	std::string NormalizeWord(std::string inWord);
	
	void RemovePunc(std::string & inWord);
};

std::ostream& operator<< (std::ostream& out, const Word &inWord);

#endif
