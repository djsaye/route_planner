# Dataset

OpenFlights flight path and airport data (https://openflights.org/data.html)

# Leading Questions

1. What is the shortest route from one airport to another?
2. How can we visualize a calculated route on a map?

# Data Acquisition and Processing

Data Format:

- The data is from OpenFlights.org
  ([https://openflights.org/data.html](https://www.google.com/url?q=https://openflights.org/data.html&sa=D&source=editors&ust=1648783801317107&usg=AOvVaw072NtSlBwSn8r4d9UyvswB)).
  Data is divided into routes.dat and airports.dat. The file routes.dat has
  information about what airport a route leaves from and what airport a route
  arrives at, and airports.dat has information about the physical location of
  each airport.

Data Correction:

- It is possible with a different dataset that multiple routes with the same
  source and destination are encoded. This will simply result in multiple edges
  with the same weight being added between the airport vertices in our routing
  graph. We can consider filtering these out in our preprocessing stage.
- We only consider direct flights; that is, rows in routes.dat with Stops != 0
  are excluded.
- Airports with NULL as both the IATA and ICAO codes are excluded in the
  preprocessing stage.
- Routes with NULL as their source or destination airport IDs are excluded in
  the preprocessing stage.

Data Storage:

- Preprocessing: The airports.dat dataset is loaded from disk into a dictionary
  in memory, with airport IDs as the keys. Then, the routes.dat dataset is
  loaded from disk and the rows (routes) are iterated. Each time a route is
  encountered, the respective source and destination airports are looked up in
  the airports dictionary, and the route length is computed using the longitude
  and latitude of the airports. The routes are written to a table on disk, which
  is loaded each subsequent time the routing program is run. The table has one
  row per route, with columns for source airport ID, destination airport ID, and
  route length. A pared-down airports database is also written to disk to allow
  future lookup by IATA or ICAO codes, rather than the numeric ID.
- When running the routing program, the user specifies a source and destination,
  the corresponding IDs are looked up using the pared-down airports database,
  and a directed graph is generated: iterating over each route, the route’s
  source and destination airports will each be stored in a vertex (and reused if
  they already exist), and the length of the route will be stored in an edge
  connecting those vertices.

# Graph Algorithms

Traversal: Depth First Search

- Function Inputs: 3 or 4 letter airport code of the starting airport and the
  destination airport
- Function Outputs: A queue that has the chain of all the airports visited,
  although it will be a suboptimal route compared to Dijkstra’s Algorithm.
- Function Efficiency: In the worst case, this function will take time O(E + V),
  where V is the number of airports in the graph and E is the number of edges.

Algorithm # 1: Shortest Path (Dijkstra’s Algorithm)

- Function Inputs: 3 or 4 letter airport code of the starting airport and the
  destination airport. A weighted graph that has all the vertices and weighted
  edges set.
- Function Outputs: A queue that has the chain of all the airports visited.
- Function Efficiency: The general time efficiency of this function should be
  O((E+V)*log(V)) where E is the total number of edges of the graph and V is the
  number of airports which create each node. Two variables are required for this
  efficiency since there is no mathematical correlation between E and V.

Algorithm # 2: Graphic Output of Flight Path on a Map

- Function Inputs: 3 or 4 letter airport code of the starting airport and the
  destination airport
- Function Outputs: A map showing the shortest path between the two airports,
  with connecting flights as necessary.
- Function Efficiency: We think the efficiency of our function should be O(n)
  for both time and memory. Each airport added increases time and memory
  required in a linear fashion.

# Timeline

- Data Acquisition and Processing: Our first goal will be to make a process to
  extract our data from our dataset and store it in a way that we can use it
  with the rest of our algorithms. Without this, we will not be able to complete
  any other algorithms. Ideal Completion Date: Week of 4/8.
- Completion of Depth First Search: Ideal Completion Date: Week of 4/15 (Before
  mid-project meeting)
- Completion of Shortest Path Algorithm: This will be the second algorithm we
  complete, as the shortest path algorithm will be part of the Graphic Output of
  Graph algorithm, so it is necessary to implement this algorithm first. Ideal
  Completion Date: Week of 4/22
- Completion of Graphic Output of Graph algorithm: This will be the last
  algorithm we complete, as it uses a previously completed algorithm (shortest
  path) and is also the most complex algorithm that we will implement. Ideal
  Completion Date: Week of 4/29
- Production of Final Deliverables: This will be the final task, as we will need
  to prepare for our final project presentation. Ideal Completion Date: Week of
  5/6
