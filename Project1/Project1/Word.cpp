/**************************************************************
 * File:    Word.cpp
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Austin Pagano
 * Date   : 10/15/14
 * Section: 02
 * E-mail:  apagano1@umbc.edu
 *
 * Word class method definitions
 *
 *************************************************************/

#include "Word.h"

using namespace std;

Word::Word(){}

Word::Word(string inWord, int lineNumber)
{
	lineNumbers.push(lineNumber);
	count = 1;
	wordText = NormalizeWord(inWord);
}

void Word::CountWord(int lineNumber)
{
	count += 1;
	lineNumbers.push(lineNumber);
}

string Word::GetWord() const
{
	return wordText;
}

int Word::GetCount() const
{
	return count;
}

queue<int> Word::GetLineNumbers() const
{
	return lineNumbers;
}

bool Word::operator<(const Word &RHS) const
{
	string LHS = GetWord();

	for (int i = 0; ((i < LHS.size()) && (i < RHS.GetWord().size())); i++)
	{
		//basic check if the letter in LHS word is smaller than letter in RHS
		if (LHS[i] < RHS.GetWord()[i])
		{return true;}

		if (LHS[i] > RHS.GetWord()[i])
		{return false;}

	}
	//letters are found to be equal throughout the loop, check for size
	
	//return true if LHS is a longer word then RHS
	return (LHS.size() < RHS.GetWord().size());
	
}

bool Word::operator==(const Word &RHS) const
{
	string LHS = GetWord();

	for (int i = 0; (i < LHS.size()) && (i < RHS.GetWord().size()); i++)
	{
		if (LHS[i] != RHS.GetWord()[i])
		{return false;}
	}
	return true;
}

Word Word::operator=(const Word &RHS)
{
	//check if they are equal
	if (!((*this) == RHS))
	{
		wordText = RHS.GetWord();
		count = RHS.GetCount();
		lineNumbers.empty();
		lineNumbers = RHS.GetLineNumbers();
	}
	return (*this);
}
string Word::NormalizeWord(string inWord)
{
	//make all letters lower case
	string lowerCaseWord = ToLower(inWord);

	//remove punctuation besides - and '
	return RemovePunc(inWord);
}

string Word::ToLower(string inWord)
{
	int size = inWord.size();
	for (int i = 0; i < size; i++)
	{
		if ((inWord[i] >= 'A') && (inWord[i] <= 'Z'))
		{
			inWord[i] += ('z' - 'Z');
		}
	}
	return inWord;
}

string Word::RemovePunc(string inWord)
{
	string normalWord;
	int size = inWord.size();

	for (int i = 0; i < size; i++)
	{
		//the letter is an allowed letter
		if((inWord[i] == 39) || (inWord[i] == '-') || ((inWord[i] >= 'a' && inWord[i] <= 'z')))
		{
			normalWord += inWord[i];
		}

		//do nothing so that the letter is not added to the result
	}
	return normalWord;
}