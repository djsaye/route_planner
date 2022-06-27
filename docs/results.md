OpenFlights provides our flights and routes data as separate CSV files. There
are a number of minor issues with the raw data, however, and we handle these in
a separate data preprocessing stage so that our central code doesn't have to
deal with them at runtime, repeating the work each time the program is run. This
preprocessing stage is performed by the `import-data.py` Python program. This
program accepts the raw airports and routes CSV datasets and produces its own
trimmed-down airports and routes CSV datasets. Using the default raw dataset
locations, we would run the following command line to generate the pared-down
datasets.

	$ ./import-data.py data/airports.csv data/routes.csv

`import-data` produces files *data/airports-preprocessed.csv* and
*data/routes-preprocessed.csv*. Since we use ICAO codes as the user-friendly
airport identifiers, `import-data` skips airports that don't have one defined.
`import-data` filters out problematic data: some routes don't define their
starting or ending airport, and some routes refer to airports that aren't
defined in the airports database. `import-data` also integrates some airport
data, such as longitude and latitude, into the routes data so that the
route-selecting program can compare distances more directly. `import-data`'s
output only includes the fields our program is interested in so that time is not
wasted loading unused data at runtime.

At runtime, the DataParser class calls the rapidcsv CSV parser library to pull
in the preprocessed values and load data structures appropriately.  

Our DFS algorithm was implemented within the WeightedGraph class. The algorithm incorporates the classes Airport and Route, several private variables from the WeightedGraph class, and the function getAdjacentAirports within WeightedGraph. The function DFS takes in the ID of a starting airport (it is defined as a unsigned int) and returs a queue full of IDs (unsigned ints) that represents the DFS traversal of all airports. In terms of depth-first search, our algorithm makes use of a stack and a set that keeps track of all airports that have not been visited. The chosen starting point would be pushed into the stack, added to the DFS queue, and removed from the set. The starting point would then get popped off the stack, and all of the adjacent airports to the starting airport, if they had not been visited already, would be pushed into the stack. These adjacent airports would then be marked as visited. This process would be repeated until the stack was empty. In testing our code, we realized that our dataset did not produce a graph of one connected component and that our DFS was not visiting all the airports. As a result, the set of unvisited airports was added and an extra while loop, which checked for if there were still elements inside the set, was also added to account for the unconnected graph issue. The first set of tests that were done on our DFS algorithm involved small-scale connected graphs, which were used to test whether our algorithm would work. There was another test done on our actual dataset of airports, through which we discovered our unconnected graph issue.  

Our Dijkstra's Algorithm was implemented within the WeightedGraph Class and uses the Route class extensively. Inside of the WeightedGraph class, this function uses several other helper functions and private member variables. Dijkstra's Algorithm is implemented within two function. One function, allPaths takes in a start and destination airport and returns a queue of all the common airports in between the starting and destination airports. To do this, the allPaths function uses the std::priority_queue container, where a Route object is the item in the container. This container requires its objects to have the <,>,== operators overwritten so the objects can be organized as a Heap. The Route class used the distance of one airport to another, or the weight of an edge to overwrite the operators. Then, starting from the start point, we inputed Route objects into the priotity queue that had the distance variable as the distance from the start node to the current node. When we popped a Route from the priority queue, we then added all the Route objects to the neighbors of the end node. Once we found the destination airport, we retuned the queue entailling the Route objects. The second function, is called the getShortestPath function and has the same inputs as the allPaths function. The return is a stack of Route objects where the total distance is encoded in the bottom Route of the stack. This function calls the allPaths function and goes through the return queue and inputs any Routes that are apart of the direct Route from the start to the end into the return stack.  

Our visual output algorithm was several different functions within the "visual" class. The function that starts a visual output is the "addTour" function, which takes a a vector of airports generated from our Dijkstra's Algorithm. This algorithm essentially initialized the rest of our visual output. It would first determine that the vector was in the correct order for us to perform our operations on. What this means, is that the default side for the algorithm to draw on must be the left side of our base image. We checked this by measuring the difference in longitudes from the start point and the end point of the proposed flight path. From there, the vector was reversed if there was an issue, and left alone if not. Next, each individual airport within the vector is taken in order and input into our "addLine" function. This function takes inputs of the latitude and longitude of the source airport and the target airport. The main job of this function is to determine what side of the image the line needs to be drawn on. It does this by quickly calculating the shortest distance of the available 4 combinations of points that could be drawn.  

![](/docs/results_images/4choices.png) *The four options to choose from*

In order to choose between the options, we calculate the length of the line of only 3 of the possible options (The orange lines are the same distance, they are chosed based on "priority"). In this case, the green line is the shortest route, so it is an obvious pick for our algorithm. But in the case that it is the orange line, the current "priority" is important to make sure we draw the line in the correct place. This is why it is important that the default priority is always 0, as otherwise the function has no baseline. Whenever the line crossed the midpoint of the two images (red or green line), the priority is updated. Otherwise, it is kept the same, and all lines will be plotted on the side that has the current priority. Once the correct line to draw is calculated, "createLine" is called, and it creates a line between the two points calculated by "addLine". After the line is drawn, the next airport in the queue is iterated to, and the cycle repeats until the vector is empty. As an added feature, we decided to also create the DrawText class, which gets called during "addTour". This class adds visual text enhancements to our output. The first thing it does is render the ICAO codes of each airport next to its indicator on the map, and also displays the total distance of the rout in the top left corner of the map. There is also a drop shadow rendered behind the text for enhanced clarity.   

As for our test cases with this algorithm, we think that our output file speaks for itself. While creating this algorithm, we came up with many issues that gave us suboptimal output. Issues that we made sure to fix were: Drawing on the wrong side (fixed with "priority"), divide by 0 errors when drawing vertical lines, line not being fully drawn when slope is too steep, and drawing the line in between incorrect airports. Here are some example outputs of the finished product:  

![](/docs/results_images/product1.png)  
*O'Hare to Sydney, with labeled ICAO*  
  
![](/docs/results_images/product2.png)  
*Total distance display in top left corner*  

In summary, we believe our two leading questions were answered in full. *1. What is the shortest route from one airport to another?* This question is answer completely by our implementation of Dijkstra's Algorithm. It was fascinating to see Djikstra's algorithm at work in such a useful real-world application such as flight path mapping. Looking at our second leading question, *2. How can we visualize a calculated route on a map?*, we believe our project comes full circle. When combining our Dijkstra's Algorithm with our Visual Output algorithms, we answer both questions simultaneously. Furthermore, in an algorithm we thought could not reveal any information to us, we were surprised to have our DFS reveal that we were working with a disconnected graph. We believe that our project was a complete success, and are very proud of what we accomplished.
