/**************************************************************
 * File:    Word.h
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Eliot Carney-Seim
 * Date  Due: 10/21/14
 * Section: 03
 * E-mail:  eliot2@umbc.edu
 *
 * A specialized wrapper data type for strings and tokenized file words.
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
	void CountWord(int lineNumber);
	std::string GetWord() const;
    int GetCount() const; //# of times the word occurred in the file & keeps line history
    bool operator< (const Word &RHS) const; //comparison overload for wrapper class.
    Word operator= (const Word &RHS);// wrapper feature reassignment
	bool operator== (const Word &RHS) const;
    friend std::ostream& operator<< (std::ostream& out, const Word &inWord);

private:
	int count;
	std::queue<int> lineNumbers;
	std::string wordText;

    void LowerAlpha(std::string & inWord); //python inspired helper script
    std::queue<int> GetLineNumbers() const; //helper getter for lineNumber
};

std::ostream& operator<< (std::ostream& out, const Word &inWord);

#endif
