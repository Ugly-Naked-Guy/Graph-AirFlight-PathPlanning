# CS225 Final Project Goal
**Dataset**: 
The [route dataset](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat) we are working with is part of the Open flights ([https://openflights.org/data.html](https://openflights.org/data.html))  open source data set of flight routes and airports. The data is currently dated from 2014 and has no path for updates but is still interesting for historical study.

**Sample entries**

|   | Airline | Airline  ID | Source airport | Source airport ID | Destination airport | Destination airport ID | Codeshare | Stops | Equipment |
|:-:|:-------:|:-----------:|:--------------:|:-----------------:|:-------------------:|:----------------------:|:---------:|:-----:|:---------:|
| 1 |    BA   |     1355    |       SIN      |        3316       |         LHR         |           507          |           |   0   |  744 777  |
| 2 |    BA   |     1355    |       SIN      |        3316       |         MEL         |          3339          |           |   Y   |    744    |
| 3 |   TOM   |     5013    |       ACE      |        1055       |         BFS         |           465          |           |   0   |    320    |

**Defin****i****tion of our graph**: 
We plan to load the routes dataset and treat it as a **directed graph**. We treat the each source airport and destination airport as the **vertices**, and routes between them as the **edges**. 
We have provided two definition of the **weights** in the following: 

1. The **weight** for each edge is a decreasing function (e.g. the reciprocal function) of count the number of routes. Thus, smaller weights means there are more routes between 2 airports, AKA, more flight frequency. It means that a passenger is more likely to choose or buy a ticket for this route.
2. The **weight** for each edge is the distance of the route between two airports. it can be calculated given the longitude and latitude. 

**Goal:**
Our goal is to implement the following algorithms to help the passengers to find the optimal paths when given the origin and destination, or origin, destination and midpoint: 

1. Traversals algorithm
2. Shortest Path algorithm
3. Landmark Path algorithm (shortest path from a to b through c)



# Algorithm:
## Traversals
1. BFS (Breadth First Search)

    BFS is an algorithm for traversing or searching tree or graph data structures. It starts at the tree root and explores all of the neighbor nodes at the present depth prior to moving on to the nodes at the next depth level.
![](https://paper-attachments.dropbox.com/s_DA1709E040ABF8BBB119E5577F605CB94E7907764CD542C35444EFFCDFC60F6E_1605674130374_image.png)

    
    







2. DFS (Depth First Search)

    DFS is an algorithm for traversing or searching tree or graph data structures. The algorithm starts at the root node (selecting some arbitrary node as the root node in the case of a graph) and explores as far as possible along each branch before backtracking.
## Covered Algorithms
Shortest Path

   a. Dijkstra’s Algorithm:
        Let the node at which we are starting be called the initial node. Let the distance of node Y be the distance from the initial node to Y. Dijkstra's algorithm will assign some initial distance values and will try to improve them step by step. 

![Dijkstra Animation.gif](https://upload.wikimedia.org/wikipedia/commons/5/57/Dijkstra_Animation.gif)

   b. Floyd-Warshall Algorithm:
        The Floyd–Warshall algorithm compares all possible paths through the graph between each pair of vertices. It is able to do this with several comparisons in a graph, even though there may be up to several edges in the graph, and every combination of edges is tested. It does so by incrementally improving an estimate on the shortest path between two vertices, until the estimate is optimal.
[](https://www.dropbox.com/scl/fi/qulx20kgxksh9kgj6j1tm/CS225-Final-Project-Goal.paper?dl=0&rlkey=05sgitazcpbxgz6s22bthzteg)

    
## Complex or Uncovered Options
Landmark Path (shortest path from a to b through c):
We plan to load the routes dataset and treat it as a directed graph.The basis of the algorithm is the presence of landmarks, placed at different vertices throughout the graph. Each landmark stores the shortest path from itself to all other vertices. LPI works by searching for intersection points along the landmark paths to approximate a path between two points.


