#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <iostream>
#include <vector>


/**************************************************************
 * File:    Graph.h
 * Project: CMSC 341 - Project 5 - Graphs
 * Author : Eliot Carney-Seim
 * Date  Due: 12/9/14
 * Section: 03
 * E-mail:  eliot2@umbc.edu
 *
 * The Graphs method definitions
 *
 *************************************************************/

class Graph
{
	public:
		Graph(std::string filename);
		int trips(int start, int stop, int people);
	private:
		int edges;
		int vertexes;
		std::vector< std::vector<int> > graph;
		int recurseTrips(std::vector< std::vector<int> > masterList, int current, int target,
					  int min, std::vector<int> visited);

};

#endif // GRAPH_H
