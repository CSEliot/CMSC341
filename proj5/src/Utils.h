/**************************************************************
 * File:    Utils.cpp
 * Project: CMSC 341 - Project 4 - Hash Table
 * Author : Eliot Carney-Seim
 * Date   : November 18th, 2014
 * Section: Lecture-03
 * E-mail:  eliot2@.umbc.edu
 *
 * Utiliy file for automated common functions.
 *
 *************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <algorithm>
using namespace std;


//Number to String
template<typename T>
string numToString(T num){
	ostringstream aStringStream;
	aStringStream << num;
	return aStringStream.str();
}

const bool DEBUG = true;
const int D_LEVEL = 50;
/* A testing program for debugging output.
 *Pre: Level of severity, lower number = more sever
 *		 message is thing to print
 *Post: Nothing, message outted.
 */
static void printDebug(std::string message, int level){
    if(DEBUG && level <= D_LEVEL){
	   std::cout <<"DEBUG: " <<  message << std::endl;
    }
}

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
	   return true;

    if( n == 1 || n % 2 == 0 )
	   return false;

    for( int i = 3; i * i <= n; i += 2 )
	   if( n % i == 0 )
		  return false;

    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
int nextPrime( int n )
{
    if( n <= 0 )
	   n == 3;

    if( n % 2 == 0 )
	   n++;

    for( ; !isPrime( n ); n += 2 )
	   ;

    return n;
}

/**
* A hash routine for string objects.
*/
int hash( const string & key )
{
    int hashVal = 0;

    for( int i = 0; i < key.length( ); i++ )
	   hashVal = 37 * hashVal + key[ i ];

    return hashVal;
}

/**
 * A hash routine for ints.
 */
int hash( int key ){
    return key;
}

/*Makes my c++ life easier, converts num T to str
 */
template <typename T>
static string str ( T num){
	ostringstream ss;
	ss << num;
	return ss.str();
}

/*converts string to type T
 */
template <typename T>
static T num( const string &Text ){
	istringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

/*replaces string in string with string
 */
static string replace(string s, string toReplace, string replaceWith){
	if(s.length() <= toReplace.length()){
		printDebug("lengths are: " +str<int>(s.length())+" "+str<int>(toReplace.length()), 2);
		return s;
	}else{
    return(s.replace(s.find(toReplace), toReplace.length(), replaceWith));}
}

/* returns a string split by whitespace into a vector
 */
static vector<string> split(string s){
	// construct a stream from the string
	stringstream str(s);

	// use stream iterators to copy the stream to the vector as whitespace separated strings
	istream_iterator<string> it(str);
	istream_iterator<string> end;
	vector<string> results(it, end);
	return results;
}
#endif // UTILS_H
