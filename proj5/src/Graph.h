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
};

#endif // GRAPH_H
