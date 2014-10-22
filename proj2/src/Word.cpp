/**************************************************************
 * File:    Word.cpp
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Eliot Carney-Seim
 * Date  Due: 10/21/14
 * Section: 03
 * E-mail:  eliot2@umbc.edu
 *
 * A specialized wrapper data type for strings and tokenized file words.
 *
 *************************************************************/

#include "Word.h"
//#include <strstream>


using namespace std;

Word::Word(){}

Word::Word(string inWord, int lineNumber){
	count = 0;
	if (lineNumber != -1){
        //a trick in code to determine filter vs book.
        LowerAlpha(inWord);
        wordText = inWord;
    }else{
        wordText = inWord;
    }
}

void Word::CountWord(int lineNumber){
    count ++;
    if (lineNumbers.empty()){
        //if nothing is in the queue, simply push
		lineNumbers.push(lineNumber);
    }else if(lineNumbers.back() != lineNumber){
        //don't add line locations twice, so if it appears twice on a line, don't add.
		lineNumbers.push(lineNumber);
    }
}

bool Word::operator<(const Word &RHS) const{
	string LHS = GetWord();
	for (int i = 0; ((i < LHS.size()) && (i < RHS.GetWord().size())); i++){
        //		check if left is greater than right, or right greater than left.
        if (LHS[i] < RHS.GetWord()[i]){
            return true;}
        if (LHS[i] > RHS.GetWord()[i]){
            return false;
        }
	}
    //if one word contains the other, compare size.
	return (LHS.size() < RHS.GetWord().size());
}

bool Word::operator==(const Word &RHS) const{
    string sLHS = GetWord();
    string sRHS = RHS.GetWord();
    for (int i = 0; (i < sLHS.size()) && (i < sRHS.size()); i++){
        if (sLHS[i] != sRHS[i]){
            //compare the strings letter for letter, any fails return false.
            return false;
        }
	}
	return true;
}

Word Word::operator=(const Word &RHS){
    if (!((*this) == RHS)){
        //if word wrappers aren't equal, reassign new values in.
        count = RHS.GetCount();
        wordText = RHS.GetWord();
        lineNumbers.empty();
        lineNumbers = RHS.GetLineNumbers();
    }
    return (*this);
}

ostream& operator<< (ostream& out, const Word &inWord){
    if (inWord.GetCount() == 0){
        //redirect output and do no formatting if it's an empty wrapper.
		out << inWord.GetWord();
	}
	else{
        //format the output.
        string line; //initialized line to be formatted to console/file.
        line += inWord.GetWord(); //add word to line.
        int periodInsert = line.size(); //distance to add count
        stringstream convertInt; //convert string to int.
        convertInt << inWord.GetCount(); //throw int into stringstream
        line += convertInt.str(); //get converted integer.
        int distanceFromRight = 23; //period formatting.
        int totalPeriodsNum = distanceFromRight - line.size();
        line.insert(periodInsert, totalPeriodsNum, '.'); //format in the periods/dots.
        line += ": "; //format in the colon.
        queue<int> tempQueue = inWord.GetLineNumbers();// build temp.

        while (!tempQueue.empty()){
            //loop through whole queue, and format in the proper line findings.
            stringstream convertInt;
            convertInt << tempQueue.front();
            line += convertInt.str();
            //^^above is int to string conversion again
            line += ' ';
            tempQueue.pop();
		}
        out << line; //send the stream out of the properly fomatted line.
	}
	return out;
}

void Word::LowerAlpha(string & inWord){
    //Python inspired script! :D
    int wordSize = inWord.size();
    for (int i = 0; i < wordSize; i++){
        if ( (inWord[i] <= 'Z') && (inWord[i] >= 'A')){
            //move all alphanumeric characters up the character chart nums
            inWord[i] += 32;
        }
	}
}

string Word::GetWord() const{
    return wordText;
}

int Word::GetCount() const{
    return count;
}

queue<int> Word::GetLineNumbers() const{
    return lineNumbers;
}
