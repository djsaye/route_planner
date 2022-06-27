#pragma once

#include <iostream>
#include "DataParser.h"
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>



class WeightedGraph {
private:
    std::vector<ID> ports;
    //std::map<ID, Airport> ports_map;
    std::map<ID, std::map<ID,double> > routes;
    std::map<ID, bool> marked;

    void markAirport(ID id);
    void markAirport(Airport port);

    bool isMarked(ID id);
    bool isMarked(Airport port);

    void clearMarks();

    std::vector<ID> portIDs;
    std::vector<std::string> names;
    std::vector<double> lats, longs;

public:
    WeightedGraph(DataParser & data);
    WeightedGraph();

    void addAirport(ID id);
    void addAirport(Airport port);

    void addRoute(ID startID, ID endID, double dist);
    void addRoute(Airport start, Airport end);
    void addRoute(Route route);

	std::queue<Airport> routesToAirports(std::stack<Route> routes);

/*
This function uses Dijkstra's algorithm to get all the paths from the start
airport to the end airport.  
*/

// @param startID: aiport identifier that refers to starting point of path
// @param endID: airport identifier that refers to starting point of path
// @return vector that has the encoding for the shortest path from start to end
    std::vector<Route> allPaths(ID startID, ID endID); 
    std::vector<Route> allPaths(Airport start, Airport end);

// @param startID: aiport identifier that refers to starting point of path
// @param endID: airport identifier that refers to starting point of path
// @return stack that entails the shortest path from start to end with the final distance in the bottom
    std::stack<Route> getShortestPath(ID startID, ID endID);
    std::stack<Route> getShortestPath(Airport start, Airport end);

//@param id: aiport identifier that refers to an aiport
//@return queue of all adjacent aiports to the id
    std::queue<ID> getAdjacentAirports(ID id);
    std::queue<ID> getAdjacentAirports(Airport port);

    std::queue<ID> DFS(ID id);
};

