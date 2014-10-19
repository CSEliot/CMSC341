/**************************************************************
 * File:    Word.h
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Austin Pagano
 * Date   : 10/15/14
 * Section: 02
 * E-mail:  apagano1@umbc.edu
 *
 * Word class header file
 *
 *************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <queue>

#ifndef WORD_H
#define WORD_H

class Word
{
public:
	Word();
	Word(std::string inWord, int lineNumber = 0);

	void CountWord(int lineNumber);
	std::string GetWord() const;
	int GetCount() const;
	std::queue<int> GetLineNumbers() const;

	bool operator< (const Word &RHS) const;
	Word operator= (const Word &RHS);
	bool operator== (const Word &RHS) const;

	friend std::ostream operator<< (std::ostream out, Word &inWord);

private:
	int count;
	std::queue<int> lineNumbers;
	std::string wordText;
	std::string NormalizeWord(std::string inWord);
	std::string ToLower(std::string inWord);
	std::string RemovePunc(std::string inWord);
};

std::ostream operator<< (std::ostream out, Word &inWord);

#endif