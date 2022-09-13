# OpenFlights route planner

## Welcome!
We used the OpenFlights database to find the optimal paths between airports globally, and plot that path onto a map.

## Using the route planner
We tried to make our project as easy to use as possible. After running `make`, our entire project can be accesed by running `./flights`. An interactive text interface will guide you through how to access the various parts of the project. There are four options: DFS with text output to the console, Dijkstra's Algorithm with text output to the console, Dijkstra's Algorithm with visual output, and a simple test output for drawing the shortest line between two airports.

Within our simple UI, you may select input dataset files for all four of our functions, and output PNG files for our Dijkstra's Algorithm visual output. There are also default file locations for both input and output, so if you would like to use our input data and standard output file location, you can. If you would like to manually change the defaults, they are stored on [lines 403-406 in main.cpp](/main.cpp#L403-L406). You can also set the OPTION macro to what your task is on [line 16 in main.cpp](/main.cpp#L16) with the menu right above it.

We have provided some fun flight paths to try in [/docs/paths_to_try](/docs/paths_to_try.md).

## Code organization
Both our DFS algorithm and Dijkstra's Algorithm are inside the WeightedGraph class (WeightedGraph.cpp). Visual output is handled by the Visual class (Visual.cpp), with text rendering provided by the DrawText class (DrawText.cpp). All of our data is prepared in the DataParser class (DataParser.cpp). Our graph algorithm test cases are inside the [/tests](/tests) folder. All of our input databases, both the pre-processed and post-processed CSV files, are stored in the [/data](/data) folder. Images for the project are stored in the [/images](/images) folder, including (by default) the output image file once it is generated. All documents related to the project, including this one and the report, are stored in [/docs](/docs).

## Test suite
For our test suite, we used Catch v2.13.8, which is in the [/cs225](/cs225) folder. For our Dijkstra's Algorithm and DFS, we created extensive tests to make sure our functions were working as expected. To run our tests, all you need to do is run `make test` and then `./test`.

For testing each graph algorithm, we used some basic graphs, as well as a sample subset of our larger dataset. We then manually computed the expected results, and used Catch to verify that our expected results were met. All of our tests can be found in the [/tests](/tests) folder; *tests_dfs.cpp* contains our tests for DFS, *tests_dijkstra.cpp* contains our tests for Dijkstra's Algorithm, and various images describe our test graphs.

As our visual is mostly based off of Dijkstra's Algorithm, most of the work done in this algorithm is appropriately displaying the visuals, which anyone can test for themselves by playing around with our program for a couple of minutes!

## Third-party components
Lastly, we did use some third-party components to help build our project. All of the third-party components that we used are listed below.

- [rapidcsv: C++ CSV-parsing library](https://github.com/d99kris/rapidcsv) by Kristofer Berggren
	- License included in [LICENSE (rapidcsv).txt](LICENSE%20(rapidcsv).txt)
- [Equirectangular projection SW.jpg](https://commons.wikimedia.org/wiki/File:Equirectangular_projection_SW.jpg) (world map) by [Daniel R. Strebe](https://commons.wikimedia.org/wiki/User:Strebe), 15 Aug 2011
- Fixed Medium Semicondensed 6x13 and Fixed Medium Normal 10x20 (fonts): public domain
	- License text inside [font files themselves](/fonts/fixed-6x13.bdf)
