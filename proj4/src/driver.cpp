/**************************************************************
 * File:    driver.cpp
 * Project: CMSC 341 - Project 4 - Hash Table
 * Author : Eliot Carney-Seim
 * Date   : November 18th, 2014
 * Section: Lecture-03
 * E-mail:  eliot2@.umbc.edu
 *
 * Main Program Driver.
 *
 *************************************************************/
#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h>
#include "exceptions.h"
#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleProbing.h"

using namespace std;

int main(int argc, char *argv[]) {

    //Do we have the right number of aruguments?  We will validate those
    //arguments later.
    if (argc != 6) {
	   cout << "BAD ARGS COUNT: " << argc << endl;

        //This is the main driver.
	} 
	else {
	    cout << "Input given is: " << argv[1] << " "
		    << argv[2] << " " <<argv[3] << " " << argv[4] << " " <<argv[5] << endl;
	    string filename = argv[1];
	    int totalNumbersToInsert = atoi(argv[2]);
	    int reportFrequency = atoi(argv[3]); //how often data is put to file
	    int tableSize = atoi(argv[4]);
	    int primeBelowTableSize = atoi(argv[5]);
	    string inFilterFile = filename; //Filter file.
	    ifstream infile;
		try {
			//load file
			infile.open(inFilterFile.c_str());
			cout << "Reading in file was a success" << endl;
		}
		//Something went wrong.
		catch (Exceptions &cException) {
		    cout << "INPUT ERROR" << endl;
		    return 1;
	    }
	    //do program
	    //load all numbers into integer bank
	    int bank[totalNumbersToInsert];

	    string number;
	    int i = 0;
	    //grab each number
	    while(getline(infile, number, ' ')){
		    //store them in an array to be hashed
			bank[i] = atoi(number.c_str());
			printDebug(numToString(bank[i]), 0);
			i++;
	    }

	    //LINEAR PROBING STARTS HERE==================================
	    //initialize everything being tracked.
	    int totalInsertionAttempts = 0;
	    float lambda = 0; // (successful insertions / table size)
	    int totalProbes = 0; //both successful and unsuccessful insertions
	    int totalProbesToInsert = 0;
	    float averageProbesPerInsertion = 0;
	    int totalSuccessfulInsertions = 0;
	    int totalFailedInsertions = 0;
	    int totalClusters = 0;
	    int sizeOfBiggestCluster = 0;
	    float averageClusterSize = 0;
	    char outStringLinear[83] ;
	    LinearHashTable<int> linearTable(tableSize);

	    ofstream outfileNs ("output1.txt", ios::out | ios::binary);
	    outfileNs << "                  Linear Probing Analysis (Table size = " +
				 numToString(tableSize) + ")" << endl;
	    outfileNs << "                --- Inserts ---   ------- Probes -------    ----- Clusters ------" << endl;
	    outfileNs << "    N   lambda  success  failed     total    avg    max     number   avg     max "
				   << endl;
	    for(int x = 0; x < totalNumbersToInsert; x++){
			totalInsertionAttempts++;
			//if insertion was a success
			if(linearTable.insert(bank[x])){
				totalSuccessfulInsertions++;
			}else{
				totalFailedInsertions++;
			}
			lambda = (float)totalSuccessfulInsertions / (float)tableSize;
			totalProbes = linearTable.getTotalProbes();
			averageProbesPerInsertion = linearTable.getAverageProbesPerInsertion();
			totalProbesToInsert = linearTable.getMaxProbesInAnInsert();
			totalClusters = linearTable.getTotalClusters();
			sizeOfBiggestCluster = linearTable.getSizeOfBiggestCluster();
			averageClusterSize = linearTable.getAverageClusterSize();
			sprintf(outStringLinear,
				   "   %2d     %2.2f       %2d       %d       %3d    %2.2f      %d         %d    %2.2f     %d",
					  (x+1),
					  lambda,
					  totalSuccessfulInsertions,
					  totalFailedInsertions,
					  totalProbes,
					  averageProbesPerInsertion,
					  totalProbesToInsert,
					  totalClusters,
					  averageClusterSize,
					  sizeOfBiggestCluster);
			outfileNs << outStringLinear << endl;
	    }
	    outfileNs.close();


	    //QUADRATIC TABLE PROBING==============================
	    totalInsertionAttempts = 0;
	    totalSuccessfulInsertions = 0;
	    totalFailedInsertions = 0;


	    QuadraticHashTable<int> quadTable(tableSize);
		char outStringQuadratic[83];
		outfileNs.open("output1.txt", ios::out | ios::app |ios::binary);
		outfileNs << endl;
		outfileNs << "                  Quadratic Probing Analysis (Table size = " +
				 numToString(tableSize) + ")" << endl;
	    outfileNs << "                --- Inserts ---   ------- Probes -------    ----- Clusters ------" << endl;
	    outfileNs << "    N   lambda  success  failed     total    avg    max     number   avg     max "
				   << endl;
	    for(int x = 0; x < totalNumbersToInsert; x++){
			totalInsertionAttempts++;
			//if insertion was a success
			if(quadTable.insert(bank[x])){
				totalSuccessfulInsertions++;
			}else{
				totalFailedInsertions++;
			}
			lambda = (float)totalSuccessfulInsertions / (float)tableSize;
			totalProbes = quadTable.getTotalProbes();
			averageProbesPerInsertion = quadTable.getAverageProbesPerInsertion();
			totalProbesToInsert = quadTable.getMaxProbesInAnInsert();
			totalClusters = quadTable.getTotalClusters();
			sizeOfBiggestCluster = quadTable.getSizeOfBiggestCluster();
			averageClusterSize = quadTable.getAverageClusterSize();
			sprintf(outStringQuadratic,
				   "   %2d     %2.2f       %2d       %d       %3d    %2.2f      %d         %d    %2.2f     %d",
					  (x+1),
					  lambda,
					  totalSuccessfulInsertions,
					  totalFailedInsertions,
					  totalProbes,
					  averageProbesPerInsertion,
					  totalProbesToInsert,
					  totalClusters,
					  averageClusterSize,
					  sizeOfBiggestCluster);
			outfileNs << outStringQuadratic << endl;
	    }
	    outfileNs.close();

	    //DOUBLE HASHING TABLE PROBING==============================
	    totalInsertionAttempts = 0;
	    totalSuccessfulInsertions = 0;
	    totalFailedInsertions = 0;

		printDebug("Testing DOUBLE HASHING", 1);
	    DoubleHashTable<int> doubleTable(tableSize, primeBelowTableSize);
		char outStringDouble[83];
		outfileNs.open("output1.txt", ios::out | ios::app |ios::binary);
		outfileNs << endl;
		outfileNs << "                  Double Hashing Analysis (Table size = " +
				 numToString(tableSize) + ")" << endl;
	    outfileNs << "                --- Inserts ---   ------- Probes -------    ----- Clusters ------" << endl;
	    outfileNs << "    N   lambda  success  failed     total    avg    max     number   avg     max "
				   << endl;
	    for(int x = 0; x < totalNumbersToInsert; x++){
			totalInsertionAttempts++;
			//if insertion was a success
			if(doubleTable.insert(bank[x])){
				totalSuccessfulInsertions++;
			}else{
				totalFailedInsertions++;
			}
			lambda = (float)totalSuccessfulInsertions / (float)tableSize;
			totalProbes = doubleTable.getTotalProbes();
			averageProbesPerInsertion = doubleTable.getAverageProbesPerInsertion();
			totalProbesToInsert = doubleTable.getMaxProbesInAnInsert();
			totalClusters = doubleTable.getTotalClusters();
			sizeOfBiggestCluster = doubleTable.getSizeOfBiggestCluster();
			averageClusterSize = doubleTable.getAverageClusterSize();
			sprintf(outStringDouble,
				   "   %2d     %2.2f       %2d       %d       %3d    %2.2f      %d         %d    %2.2f     %d",
					  (x+1),
					  lambda,
					  totalSuccessfulInsertions,
					  totalFailedInsertions,
					  totalProbes,
					  averageProbesPerInsertion,
					  totalProbesToInsert,
					  totalClusters,
					  averageClusterSize,
					  sizeOfBiggestCluster);
			outfileNs << outStringDouble << endl;
	    }
	    outfileNs.close();

	    ofstream outfileTable ("output1table.txt", ios::out | ios::binary);
	    outfileTable << "Linear Probing actual table"<<endl;
	    for(int i = 0; i < tableSize; i++){
		    outfileTable << numToString(i) << ": " << linearTable.getElementAt(i)<<endl;

		    printDebug("Element at: "+
					numToString(i) + "is: "+ numToString(linearTable.getElementAt(i)), 1);
	    }
	    outfileTable << endl <<  "Quadratic Probing actual table"<<endl;
	    for(int i = 0; i < tableSize; i++){
		    outfileTable << numToString(i) << ": " << quadTable.getElementAt(i)<<endl;

		    printDebug("Element at: "+
					numToString(i) + "is: "+ numToString(quadTable.getElementAt(i)), 1);
	    }
		outfileTable << endl << "Double Hashing actual table"<<endl;
		for(int i = 0; i < tableSize; i++){
			outfileTable << numToString(i) << ": " << doubleTable.getElementAt(i)<<endl;

			printDebug("Element at: "+
					 numToString(i) + "is: "+ numToString(doubleTable.getElementAt(i)), 1);
		}
		outfileTable.close();
		infile.close();
    }
    //Uncomment for number of seconds running.
    cout << clock() / (float)CLOCKS_PER_SEC << endl;
    return 0;
}

