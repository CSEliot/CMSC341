#include "Graph.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include "exceptions.h"
#include "Utils.h"

using namespace std;
Graph::Graph(string filename){
	filename; //Filter file.
	ifstream infile(filename.c_str());
	if(infile.is_open()){
		printDebug("Reading in file was a success" ,2);
	}else{
		cout << "INPUT ERROR" << endl;
		exit(EXIT_FAILURE);
	}
	//do program

	string line;
	int i = 0;
	//grab each number

	//add input to graph
	while(getline(infile, line)){
		int startVertex;
		int targetVertex;
		int cost;
		vector<string> lineVector = split(line);
		//test the split function for accuracy
		for(int x = 0; x < lineVector.size(); x++){
			printDebug(lineVector[x], 5);
		}
		//first line different from rest
		if (i == 0){
			vertexes = num<int>(lineVector.at(0));
			edges = num<int>(lineVector.at(1));
			graph.resize(vertexes);
			for (int x = 0; x < vertexes; x++){
				graph[x].resize(vertexes);
				for(int y = 0; y < graph[x].size(); y++){
					graph[x][y] = -1; //assign default -1
				}
			}
			i++;
		}else{
			startVertex  = num<int>(lineVector[0])-1;
			targetVertex = num<int>(lineVector[1])-1;
			cost = num<int>(lineVector[2]);
			graph[startVertex][targetVertex] = cost;
		}
	}

	//test proper graph
	if(DEBUG){
		printDebug("   01, 02, 03, 04, 05, 06, 07", 5);
		for(int x = 0; x < graph.size(); x++ ){
			string printString = ""+str<int>(x+1);
			for(int y = 0; y < graph[x].size(); y++){
				printString += ", "+str<int>(graph[x][y]);
			}
			printDebug(printString, 5);
		}
	}
}

int Graph::trips(int start, int stop, int people){
	printDebug("trips was called!", 0);
	start --;
	stop --;
	//build master list!
	//get largest edge and the vertices it connects.
	vector< vector<int> > masterList(edges);
	int biggest = 0;
	vector<int> biggestLocation(2);
	bool hasStart = false;
	bool hasEnd = false;
	int i= 0;
	while(hasStart == false || hasEnd == false){
		printDebug("inLOOP", 0);
		biggest = 0;
		for(int x = 0; x < graph.size(); x++ ){
			for(int y = 0; y < graph[x].size(); y++){
				if(graph[x][y] > biggest){
					biggest = graph[x][y];
					biggestLocation[0] = x;
					biggestLocation[1] = y;
				}
			}
		}
		vector<int> tempVector(3);
		tempVector[0] = biggest;
		tempVector[1] = biggestLocation[0];
		tempVector[2] = biggestLocation[1];

		graph[1][4] = -1;
		graph[biggestLocation[0]][biggestLocation[1]] = -1;

		masterList[i] = tempVector;

		if(biggestLocation[0] == start || biggestLocation[1] == start){
			hasStart = true;
			printDebug("TRUTHSSTART", 0);
		}
		if(biggestLocation[0] == stop || biggestLocation[1] == stop){
			hasEnd = true;
			printDebug("TRUTHSEND", 0);
		}
		if(DEBUG){
			cout << "locations vs start and stop: " <<
				   biggestLocation[0] <<  ", " <<
				   biggestLocation[1] << ", " <<
				   start << ", " <<
				   stop << endl;
		}
		i++;
	}
	if(DEBUG){
		printDebug("Master List: ", 5);
		for(int x = 0; x < masterList.size(); x++ ){
			string printString = ""+str<int>(x+1);
			for(int y = 0; y < masterList[x].size(); y++){
				printString += ", "+str<int>(masterList[x][y]);
			}
			printDebug(printString, 5);
		}
	}
	int minTrips = -1;
	while(minTrips == -1){
		minTrips = recurseTrips(masterList, start, stop, minTrips);
		if(minTrips == -1){
			biggest = 0;
			for(int x = 0; x < graph.size(); x++ ){
				for(int y = 0; y < graph[x].size(); y++){
					if(graph[x][y] > biggest){
						biggest = graph[x][y];
						biggestLocation[0] = x;
						biggestLocation[1] = y;
					}
				}
			}
			vector<int> tempVector(3);
			tempVector[0] = biggest;
			tempVector[1] = biggestLocation[0];
			tempVector[2] = biggestLocation[1];

			graph[1][4] = -1;
			graph[biggestLocation[0]][biggestLocation[1]] = -1;

			masterList[i] = tempVector;
			i++;
			printDebug("minTrips failed, increased master size: ");

			if(DEBUG){
				printDebug("Master List: ", 5);
				for(int x = 0; x < masterList.size(); x++ ){
					string printString = ""+str<int>(x+1);
					for(int y = 0; y < masterList[x].size(); y++){
						printString += ", "+str<int>(masterList[x][y]);
					}
					printDebug(printString, 5);
				}
			}
		}
	}
	printDebug("end of graph", 0);
	//grab edge w/ start node from master list.
	//while endNotReached;
	//does current have any adjacencies in master list?
	//if so, how many?
		//for each adjacency set min to go through that many times and
	return 5;
}

Graph::recurseTrips(std::vector<vector<int> > masterList, int current, int target, int min){
	return -1;
}

