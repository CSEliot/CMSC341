#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <iostream>
#include <vector>

class Graph
{
	public:
		Graph(std::string filename);
		int trips(int start, int stop, int people);
	private:
		int edges;
		int vertexes;
		std::vector< std::vector<int> > graph;
		int recurseTrips(std::vector< std::vector<int> > masterList, int current, int target, int min);

};

#endif // GRAPH_H
