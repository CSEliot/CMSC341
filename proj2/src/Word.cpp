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
//#include <strstream>


using namespace std;

Word::Word(){}

Word::Word(string inWord, int lineNumber)
{
	count = 0;

	//distinguish between a word for filtered BST and indexed BST
	if (lineNumber != -1)
	{
		ToLower(inWord);
	}

	wordText = inWord;
}

void Word::CountWord(int lineNumber)
{
	count += 1;

	//add to the queue if it is empty
	if (lineNumbers.empty())
		lineNumbers.push(lineNumber);

	//check for a duplicate line number
	if (lineNumbers.back() != lineNumber)
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

ostream& operator<< (ostream& out, const Word &inWord)
{
	if (inWord.GetCount() == 0)
	{
		out << inWord.GetWord();
	}
	else
	{
		//print acording to the indexed words standards

		//the line that will be printed to the console not including the queue
		string line;

		//add the word text and count of the word
		line += inWord.GetWord();

		//get where to insert the periods
		int whereToInsert = line.size();

        stringstream convertInt;
        convertInt << inWord.GetCount();
        line += convertInt.str();


        //char buffer[10];
        //line += itoa(inWord.GetCount(), buffer, 10);

		//get the number of '.' to add
		int numberOfPeriods = 23 - line.size();

		//insert the periods
		line.insert(whereToInsert, numberOfPeriods, '.');


		//add the ':'
		line += ": ";

		//make a copy of the queue 
		queue<int> temp = inWord.GetLineNumbers(); 

		//print the queue
		while (!temp.empty())
		{
            stringstream convertInt;
            convertInt << temp.front();
            line += convertInt.str();
            line += ' ';
			temp.pop();
		}

		out << line;
	}

	return out;

}

//string Word::NormalizeWord(string inWord)
//{
//	//make all letters lower case
//	ToLower(inWord);
//
//	//remove punctuation besides - and '
//	RemovePunc(inWord);
//
//	return inWord;
//}

void Word::ToLower(string & inWord)
{
	int size = inWord.size();
	for (int i = 0; i < size; i++)
	{
		if ((inWord[i] >= 'A') && (inWord[i] <= 'Z'))
		{
			inWord[i] += 32;
		}
	}
}

//void Word::RemovePunc(string & inWord)
//{
//	//go throug the word and erase any unwanted punctuation
//	for (int i = 0; i < inWord.size(); i++)
//	{
//		//the letter is an allowed letter
//		if((inWord[i] != 39) && (inWord[i] != '-') && (!(inWord[i] >= 'a' && inWord[i] <= 'z')))
//		{
//			inWord.erase(i,i + 1);
//		}
//	}
//}
