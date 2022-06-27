#include "../cs225/catch/catch.hpp"
#include "../WeightedGraph.h"


void load_graph_a(WeightedGraph & w) { //basic graph
    for (int i=1; i<6; i++)
        w.addAirport(i);
   
    w.addRoute(1,2,1);
    w.addRoute(1,3,5);
    w.addRoute(2,3,2);
    w.addRoute(2,4,7);
    w.addRoute(3,4,2);
    w.addRoute(4,5,3);
}

void load_graph_b(WeightedGraph & w) { //basic graph with double connections
    for (int i=1; i<6; i++)
        w.addAirport(i);
   
    w.addRoute(1,2,1);
    w.addRoute(1,3,5);
    w.addRoute(2,3,2);
    w.addRoute(2,4,7);
    w.addRoute(3,4,2);
    w.addRoute(4,5,3);

    w.addRoute(2,1,1);
    w.addRoute(3,1,5);
    w.addRoute(3,2,2);
    w.addRoute(4,2,7);
    w.addRoute(4,3,2);
    w.addRoute(5,4,3);
}

void load_graph_d(WeightedGraph & w) { //small graph with decimals
    for (int i=1; i<4; i++)
        w.addAirport(i);
   
    w.addRoute(1,3,3.1415926535);
    w.addRoute(3,2,2.7182818284);
    w.addRoute(1,2,420.69);
}

void load_graph_c(WeightedGraph & w) { //weird graph from google images
    for (int i=0; i<9; i++)
        w.addAirport(i);

    w.addRoute(0,1,4);

    w.addRoute(1,2,8);
    w.addRoute(1,7,11);

    w.addRoute(2,5,4);
    w.addRoute(2,3,7);

    w.addRoute(3,4,9);
    w.addRoute(3,2,7);

    w.addRoute(4,3,9);
    w.addRoute(4,5,10);

    w.addRoute(5,4,10);
    w.addRoute(5,3,14);
    w.addRoute(5,6,2);

    w.addRoute(6,8,6);
    w.addRoute(6,5,2);
    w.addRoute(6,7,1);

    w.addRoute(7,1,11);
    w.addRoute(7,0,8);

    w.addRoute(8,7,7);
    w.addRoute(8,2,2);
}

////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////

TEST_CASE("Dijkstra Graph A 1 to 3", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_a(w);
    
    std::stack<Route> path = w.getShortestPath(1,3);

    REQUIRE(path.size() == 2);

    REQUIRE(path.top().getStart() == 1);
    REQUIRE(path.top().getEnd() == 2);
    path.pop();

    REQUIRE(path.top().getStart() == 2);
    REQUIRE(path.top().getEnd() == 3);
    REQUIRE(path.top().getDist() == 3);
    path.pop();

    REQUIRE( path.empty() == true );
}

TEST_CASE("Graph A 5 to 1", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_a(w);

    std::stack<Route> path = w.getShortestPath(5,1);

    REQUIRE(path.size() == 0);
    REQUIRE(path.empty() == true);
}

TEST_CASE("Dijkstra Graph A 1 to 5", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_a(w);
    
    std::stack<Route> path = w.getShortestPath(1,5);

    REQUIRE(path.size() == 4);

    REQUIRE(path.top().getStart() == 1);
    REQUIRE(path.top().getEnd() == 2);
    path.pop();

    REQUIRE(path.top().getStart() == 2);
    REQUIRE(path.top().getEnd() == 3);
    path.pop();

    REQUIRE(path.top().getStart() == 3);
    REQUIRE(path.top().getEnd() == 4);
    path.pop();

    REQUIRE(path.top().getStart() == 4);
    REQUIRE(path.top().getEnd() == 5);
    REQUIRE(path.top().getDist() == 8.0);
    path.pop();

    REQUIRE( path.empty() == true );
}

TEST_CASE("Dijkstra Graph A 1 to 3/5", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_a(w);
    
    std::stack<Route> path13 = w.getShortestPath(1,3);
    std::stack<Route> path15 = w.getShortestPath(1,5);


    REQUIRE(path13.size() == 2);

    REQUIRE(path13.top().getStart() == 1);
    REQUIRE(path13.top().getEnd() == 2);
    path13.pop();

    REQUIRE(path13.top().getStart() == 2);
    REQUIRE(path13.top().getEnd() == 3);
    REQUIRE(path13.top().getDist() == 3.0);
    path13.pop();

    REQUIRE( path13.empty() == true );


    REQUIRE(path15.size() == 4);

    REQUIRE(path15.top().getStart() == 1);
    REQUIRE(path15.top().getEnd() == 2);
    path15.pop();

    REQUIRE(path15.top().getStart() == 2);
    REQUIRE(path15.top().getEnd() == 3);
    path15.pop();

    REQUIRE(path15.top().getStart() == 3);
    REQUIRE(path15.top().getEnd() == 4);
    path15.pop();

    REQUIRE(path15.top().getStart() == 4);
    REQUIRE(path15.top().getEnd() == 5);
    REQUIRE(path15.top().getDist() == 8.0);
    path15.pop();

    REQUIRE( path15.empty() == true );
}

TEST_CASE("Dijkstra Graph B 1 to 5", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_b(w);
    
    std::stack<Route> path = w.getShortestPath(1,5);

    REQUIRE(path.size() == 4);

    REQUIRE(path.top().getStart() == 1);
    REQUIRE(path.top().getEnd() == 2);
    path.pop();

    REQUIRE(path.top().getStart() == 2);
    REQUIRE(path.top().getEnd() == 3);
    path.pop();

    REQUIRE(path.top().getStart() == 3);
    REQUIRE(path.top().getEnd() == 4);
    path.pop();

    REQUIRE(path.top().getStart() == 4);
    REQUIRE(path.top().getEnd() == 5);
    REQUIRE(path.top().getDist() == 8.0);
    path.pop();

    REQUIRE( path.empty() == true );
}

TEST_CASE("Dijkstra Graph B 5 to 1", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_b(w);
    
    std::stack<Route> path = w.getShortestPath(5,1);

    REQUIRE(path.size() == 4);

    REQUIRE(path.top().getStart() == 5);
    REQUIRE(path.top().getEnd() == 4);
    path.pop();

    REQUIRE(path.top().getStart() == 4);
    REQUIRE(path.top().getEnd() == 3);
    path.pop();

    REQUIRE(path.top().getStart() == 3);
    REQUIRE(path.top().getEnd() == 2);
    path.pop();

    REQUIRE(path.top().getStart() == 2);
    REQUIRE(path.top().getEnd() == 1);
    REQUIRE(path.top().getDist() == 8.0);
    path.pop();

    REQUIRE( path.empty() == true );
}


TEST_CASE("Dijkstra Graph C 0 to 8", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_c(w);

    std::stack<Route> path = w.getShortestPath(0,8);

    REQUIRE(path.size() == 5);

    REQUIRE(path.top().getStart() == 0);
    REQUIRE(path.top().getEnd() == 1);
    path.pop();

    REQUIRE(path.top().getStart() == 1);
    REQUIRE(path.top().getEnd() == 2);
    path.pop();

    REQUIRE(path.top().getStart() == 2);
    REQUIRE(path.top().getEnd() == 5);
    path.pop();

    REQUIRE(path.top().getStart() == 5);
    REQUIRE(path.top().getEnd() == 6);
    path.pop();

    REQUIRE(path.top().getStart() == 6);
    REQUIRE(path.top().getEnd() == 8);
    REQUIRE(path.top().getDist() == 24.0);
    path.pop();

    REQUIRE( path.empty() == true );
}

TEST_CASE("Dijkstra Graph C 5 to 3", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_c(w);

    std::stack<Route> path = w.getShortestPath(5,3);

    REQUIRE(path.size() == 1);

    REQUIRE(path.top().getStart() == 5);
    REQUIRE(path.top().getEnd() == 3);
    REQUIRE(path.top().getDist() == 14.0);
    path.pop();

    REQUIRE( path.empty() == true );
}

TEST_CASE("Dijkstra Graph C 3 to 5", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_c(w);

    std::stack<Route> path = w.getShortestPath(3,5);

    REQUIRE(path.size() == 2);

    REQUIRE(path.top().getStart() == 3);
    REQUIRE(path.top().getEnd() == 2);
    path.pop();

    REQUIRE(path.top().getStart() == 2);
    REQUIRE(path.top().getEnd() == 5);
    REQUIRE(path.top().getDist() == 11.0);
    path.pop();

    REQUIRE( path.empty() == true );
}

TEST_CASE("Dijkstra Graph D 1 to 2", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_d(w);

    std::stack<Route> path = w.getShortestPath(1,2);

    REQUIRE(path.size() == 2);

    REQUIRE(path.top().getStart() == 1);
    REQUIRE(path.top().getEnd() == 3);
    path.pop();

    REQUIRE(path.top().getStart() == 3);
    REQUIRE(path.top().getEnd() == 2);
    REQUIRE(path.top().getDist() == (2.7182818284+3.1415926535));
    path.pop();

    REQUIRE( path.empty() == true );
}   

TEST_CASE("Dijkstra Actual Testcase #1", "[weight=1][part=1]") {
    DataParser parser("data/airports-preprocessed.csv", "data/routes-preprocessed.csv");
    WeightedGraph w(parser);

    std::stack<Route> path = w.getShortestPath(2965,3484);

    REQUIRE(path.size() == 2);

    REQUIRE(path.top().getStart() == 2965);
    REQUIRE(path.top().getEnd() == 2988);
    path.pop();

    REQUIRE(path.top().getStart() == 2988);
    REQUIRE(path.top().getEnd() == 3484);
    bool dist_check = path.top().getDist()>11169.0 && path.top().getDist()<11171.0;
    REQUIRE(dist_check == true);
    path.pop();

    REQUIRE( path.empty() == true );


}

TEST_CASE("Dijkstra Actual Testcase #2", "[weight=1][part=1]") {
    DataParser parser("data/airports-preprocessed.csv", "data/routes-preprocessed.csv");
    WeightedGraph w(parser);

    std::stack<Route> path = w.getShortestPath(3577,18);

    REQUIRE(path.size() == 3);

    REQUIRE(path.top().getStart() == 3577);
    REQUIRE(path.top().getEnd() == 16);
    path.pop();

    REQUIRE(path.top().getStart() == 16);
    REQUIRE(path.top().getEnd() == 8);
    path.pop();

    REQUIRE(path.top().getStart() == 8);
    REQUIRE(path.top().getEnd() == 18);
    bool dist_check = path.top().getDist()>8648.0 && path.top().getDist()<8651.0;
    REQUIRE(dist_check == true);
    path.pop();

    REQUIRE( path.empty() == true );


}


