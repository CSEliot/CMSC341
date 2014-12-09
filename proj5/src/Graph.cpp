#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include "exceptions.h"
#include "Utils.h"

using namespace std;
Graph::Graph(string filename)
{
		filename; //Filter file.
		ifstream infile(filename.c_str());
		if(infile.is_open()){
			printDebug("Reading in file was a success" ,2);
		}else{
			cout << "INPUT ERROR" << endl;
			exit(EXIT_FAILURE);
		}
		//do program
		//load all numbers into integer bank

		string line;
		int i = 0;
		//grab each number
		printDebug("did thing?!", 5);
		while(getline(infile, line, ' ')){
			printDebug("Number is: "+line, 0);
			 int temp = num<int>(line.c_str());
			 i++;
		}
		printDebug("did thing!!", 5);
}
