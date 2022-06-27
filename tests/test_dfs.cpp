#include "../cs225/catch/catch.hpp"
#include "../WeightedGraph.h"
#include "../DataParser.h"
#include <iostream>


void load_graph_a_1(WeightedGraph & w) { //basic graph 1
    for (int i=1; i<6; i++)
        w.addAirport(i);
   
    w.addRoute(1,2,1);
    w.addRoute(1,3,5);
    w.addRoute(2,3,2);
    w.addRoute(2,4,7);
    w.addRoute(3,4,2);
    w.addRoute(4,5,3); 
}

void load_graph_d_1(WeightedGraph & w) { //basic graph 2
    for (int i=0; i<5; i++)
        w.addAirport(i);
   
    w.addRoute(0,1,1);
    w.addRoute(0,2,5);
    w.addRoute(0,3,2);
    w.addRoute(1,2,7);
    w.addRoute(2,4,2);
}

void load_graph_e_1(WeightedGraph & w) { //basic graph 3
    for (int i=0; i<6; i++)
        w.addAirport(i);
   
    w.addRoute(0,1,1);
    w.addRoute(0,2,5);
    w.addRoute(1,2,2);
    w.addRoute(1,3,7);
    w.addRoute(2,3,2);
    w.addRoute(3,4,2);
    w.addRoute(4,0,2);
    w.addRoute(4,1,2);
    w.addRoute(4,5,2);
}

void load_graph_c_1(WeightedGraph & w) { //basic graph 4
    for (int i=0; i<9; i++)
        w.addAirport(i);
   
    w.addRoute(0,1,4);
    w.addRoute(1,2,8);
    w.addRoute(1,7,11);
    w.addRoute(2,3,7);
    w.addRoute(2,5,4);
    w.addRoute(3,2,7);
    w.addRoute(3,4,9);
    w.addRoute(4,3,9);
    w.addRoute(4,5,10);
    w.addRoute(5,3,14);
    w.addRoute(5,4,10);
    w.addRoute(5,6,2);
    w.addRoute(6,5,2);
    w.addRoute(6,7,1);
    w.addRoute(6,8,6);
    w.addRoute(7,0,8);
    w.addRoute(7,1,11);
    w.addRoute(8,2,2);
    w.addRoute(8,7,7);
   
}

void load_graph_f_1(WeightedGraph & w) { //basic graph 5
    for (int i=0; i<4; i++)
        w.addAirport(i);
   
    w.addRoute(0,1,1);
    w.addRoute(0,2,1);
    w.addRoute(1,2,5);
    w.addRoute(2,0,2);
    w.addRoute(2,3,7);
    w.addRoute(3,3,2);
}

TEST_CASE("DFS Basic Test 1", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_a_1(w);
    
    std::queue<ID> dfs_traversal = w.DFS(1);

    REQUIRE(dfs_traversal.size() == 5);

    REQUIRE(dfs_traversal.front() == 1);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 3);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 4);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 5);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 2);
}

TEST_CASE("DFS Basic Test 2", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_d_1(w);
    
    std::queue<ID> dfs_traversal = w.DFS(0);

    REQUIRE(dfs_traversal.size() == 5);

    REQUIRE(dfs_traversal.front() == 0);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 3);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 2);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 4);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 1);
}

TEST_CASE("DFS Basic Test 3", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_c_1(w);
    
    std::queue<ID> dfs_traversal = w.DFS(0);

    REQUIRE(dfs_traversal.size() == 9);

    REQUIRE(dfs_traversal.front() == 0);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 1);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 7);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 2);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 5);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 6);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 8);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 4);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 3);

}

TEST_CASE("DFS Basic Test 4", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_e_1(w);
    
    std::queue<ID> dfs_traversal = w.DFS(0);

    REQUIRE(dfs_traversal.size() == 6);

    REQUIRE(dfs_traversal.front() == 0);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 2);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 3);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 4);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 5);
    
    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 1);
}

TEST_CASE("DFS Basic Test 5", "[weight=1][part=1]") {
    WeightedGraph w;
    load_graph_f_1(w);
    
    std::queue<ID> dfs_traversal = w.DFS(2);

    REQUIRE(dfs_traversal.size() == 4);

    REQUIRE(dfs_traversal.front() == 2);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 3);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 0);

    dfs_traversal.pop();

    REQUIRE(dfs_traversal.front() == 1);
}

TEST_CASE("DFS Actual Test 1", "[weight=1][part=1]") {
    DataParser parser("data/airports-preprocessed.csv", "data/routes-preprocessed.csv");
    WeightedGraph w(parser);
    
    std::vector<std::string> portNames; //Initialize all our variables for airports
    std::vector<ID> portID;
    std::vector<double> portLatitudes;
    std::vector<double> portLongitudes;
    parser.getAirportsData(portNames, portID, portLatitudes, portLongitudes);

    std::queue<ID> dfs_traversal = w.DFS(3830);

    REQUIRE(dfs_traversal.size() == portID.size());

    
    for(unsigned i = 0; i < dfs_traversal.size(); i++){
        std::cout<<dfs_traversal.front();
        if(i != dfs_traversal.size() - 1){
            std::cout<<"-->";
        }
        dfs_traversal.pop();
    }

    

    

    
}