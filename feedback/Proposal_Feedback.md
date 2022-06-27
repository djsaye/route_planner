### Grade
Partly Competent (70%)

Must resubmit (for up to a 90% grade)!

### Comments
A well-written proposal overall but there are several issues which I have mentioned in the sections below. In summary, your leading questions may need to be altered or explained further, the splitting of graphs has many variables to consider, and your visualization algorithm is currently unclear.

Regarding resubmission, the main issue that needs to be fixed is the visualization algorithm. The other issues are primarily just for additional points on the proposal (and also for your benefit). 

**Leading Question**
The leading questions seem reasonable for the most part (although I would argue that the first and fourth questions are fairly trivial and don't require a graph algorithm to solve). However, it seems like only the second question is actually addressed by your proposed algorithms. The other three are not really solvable by the algorithms you listed. As I mentioned, the first and fourth questions are fairly trivial so you probably don't need an algorithm for them (unless you try to answer #4 with a more complex notion of 'importance'). But the third question is something you could use a graph algorithm to solve. 

I would recommend that you either change your leading questions to be more relevant to your chosen algorithms, or change your algorithms to solve your questions.

**Dataset**
The dataset is well described and the procedure is explained very clearly. However, I am not exactly sure how you arrived at O(nlogn) for the storage cost of your entire graph. 

In addition, I think there is more that needs to be explained in regards to your graph file setup. Firstly, it's not exactly clear how you plan to detect different class hierarchies and split them up. Also, to my understanding, the naming convention of using the 'topmost' course in a hierarchy could run into issues when there are multiple courses at the top of a hierarchy. And finally, you mentioned looking up the correct graph file based on the user's inputted info, but this seems like a non-trivial task to me. How do you plan to actually determine which graph file contains which courses? And what about when the user's course belongs to multiple graphs?

It's fine if you don't yet have an answer to all of the points I brought up, but this is something you should be thinking about from an early stage to make your life easier later on.

**Algorithm**
The runtime you listed for DFS is slightly incorrect, as it should be O(E + N), where E is the number of edges in the graph and N is the number of vertices/classes.

Your runtime for Dijkstra's is correct, although note that it is based on the assumption that your graphs are weakly connected, and that you are using the priority queue implementation of Dijkstra's. 

It's fine to do visualization as one of your algorithms, but I think you need to have a clearer idea of what the general structure will look like. For example, you may want to look into a layered graph drawing. You could also look into different ways to color nodes in your graph visualization (e.g. based on the type of course, or number of connections to that course).
