/**************************************************************
 * File:    driver.cpp
 * Project: CMSC 341 - Project 2 - Index Creator
 * Author : Mr. Lupoli (with help)
 * Date   : 17-June-2014
 * Section: Lecture-02
 * E-mail:  slupoli@cs.umbc.edu
 *
 * Main Program Driver.
 *
 *************************************************************/
#include <iostream>
#include <string>
#include <ctime>
#include "exceptions.h"
#include "Utils.h"
#include "QuadraticProbing.h"

using namespace std;

int main(int argc, char *argv[]) {

   cout << "TITS";
    //Do we have the right number of aruguments?  We will validate those
    //arguments later.
    if (argc != 6) {
	   cout << "BAD ARGS COUNT: " << argc << endl;

        //This is the main driver.
	} 
	else {
	    string inFilterFile = argv[1]; //Filter file.
		try {
			//load file
		}
		//Something went wrong.
		catch (Exceptions &cException) {
		    cout << "INPUT ERROR" << endl;
		    return 1;
	    }
    }
    //Uncomment for number of seconds running.
    cout << clock() / (float)CLOCKS_PER_SEC << endl;
    int stop;
    cin >> stop;
    return 0;
}

