#include "Graph.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[])
{
	string filename = argv[1];
	//read the command line argument and generate a graph
	Graph mygraph(filename);
	int s, d, t;
	//take user input on the source city, destination city, and the number of tourists
	cin>> s >> d >> t;
	//print the minimum number of trips
	cout<<"Minimum Number of Trip: "<<mygraph.trips(s,d,t) <<endl;

	return 0;
}
