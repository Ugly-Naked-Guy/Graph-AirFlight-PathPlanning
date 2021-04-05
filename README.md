# CS225 Final Project - Shortest path algorithms for flight routes


# Usage:
To run the program. Compile with:
```
make
```
and execute:
```
./main
```
to start the program.

You will get an instruction output like the following:
```
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++ Welcome to Flight Finder ++++++++++++++++++++
Enter the method you want:
Enter a for Findshortest Path Method;
Enter b for Findshortest Path Method with Midpoint;
Enter c for Traversal Method;
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
```
Users can specify the data file for flight routes in the `main.cpp`. Airport information is included by default and contains a large database of airport locations. The program will calculate the distance btween two airports based on their latitude and longitude, which in turn serves as weight of the graph. Note that at present, users needs to specify three captial letter abbreviation of the airport as intput. 

There are three functions, the display will give instruction and expect an letter input corresponding to the functionality. The first two implements Shortest path using Floyd-Warshall Algorithm. 

The first is a simple shortest path implementation to find the shortest flight path from the point of departure to destination. 
```
a
Findshortest Path Method:
Please enter the departure:
SIN
Please enter the destination
HKG
The Shortest path is SIN->HKG, the distance is 9.53495e+06 meters.
```

The second function implements landmark path algorithm, where the user can find a shortest path from two airports through a midpoint.

```
b
Findshortest Path Method:
Please enter the departure:
PEK
Please enter the midpoint:
HKG
Please enter the destination: 
TPE
PEK->CTU, CTU->TPE, TPE->CGO, CGO->HKG, HKG->TPE, the distance is 3.58486e+07 meters.
```
The third function is a BFS traversal that displays all airports in the given flight routes file. User will specify the starting location of the traversal.

```
c
Traversal Method:
Please enter the starting point:
SIN
SIN HKG TPE CGO CTU PEK TXL
```

To test the program. Compile with:
```
make test
```
and execute:
```
./test
```
to see the test results.

A typical session of the program looks like this:
![image](https://github-dev.cs.illinois.edu/cs225-fa20/wanrong2-zheli3-yuqi6-yiminw3/blob/master/images/catch_test.png)

# GOALS
Our goal is to implement the following algorithms to help the passengers to find the optimal paths when given the origin and destination, or origin, destination and midpoint: 

1. Traversals algorithm
2. Shortest Path algorithm
3. Landmark Path algorithm (shortest path from a to b through c)


**Dataset**: 
The [route dataset](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat) and [airports dataset] (https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat) we are working with is part of the Open flights ([Airport, airline and route data](https://openflights.org/data.html))  open source data set of flight routes and airports. The data is currently dated from 2014 and has no path for updates but is still interesting for historical study.

**Sample entries**

Routes

|   | Airline | Airline  ID | Source airport | Source airport ID | Destination airport | Destination airport ID | Codeshare | Stops | Equipment |
|:-:|:-------:|:-----------:|:--------------:|:-----------------:|:-------------------:|:----------------------:|:---------:|:-----:|:---------:|
| 1 |    BA   |     1355    |       SIN      |        3316       |         LHR         |           507          |           |   0   |  744 777  |
| 2 |    BA   |     1355    |       SIN      |        3316       |         MEL         |          3339          |           |   Y   |    744    |
| 3 |   TOM   |     5013    |       ACE      |        1055       |         BFS         |           465          |           |   0   |    320    |


Airports
```
507,"London Heathrow Airport","London","United Kingdom","LHR","EGLL",51.4706,-0.461941,83,0,"E","Europe/London","airport","OurAirports"
26,"Kugaaruk Airport","Pelly Bay","Canada","YBB","CYBB",68.534401,-89.808098,56,-7,"A","America/Edmonton","airport","OurAirports"
3127,"Pokhara Airport","Pokhara","Nepal","PKR","VNPK",28.200899124145508,83.98210144042969,2712,5.75,"N","Asia/Katmandu","airport","OurAirports"
8810,"Hamburg Hbf","Hamburg","Germany","ZMB",\N,53.552776,10.006683,30,1,"E","Europe/Berlin","station","User"
```

**Defin****i****tion of our graph**: 
We plan to load the routes dataset and treat it as a **directed graph**. We treat the each source airport and destination airport as the **vertices**, and routes between them as the **edges**. 
We have provided two definition of the **weights** in the following: 

1. The **weight** for each edge is a decreasing function (e.g. the reciprocal function) of count the number of routes. Thus, smaller weights means there are more routes between 2 airports, AKA, more flight frequency. It means that a passenger is more likely to choose or buy a ticket for this route.
2. The **weight** for each edge is the distance of the route between two airports. it can be calculated given the longitude and latitude. 

## Algorithm:
### Traversals
1. BFS (Breadth First Search)

    BFS is an algorithm for traversing or searching tree or graph data structures. It starts at the tree root and explores all of the neighbor nodes at the present depth prior to moving on to the nodes at the next depth level.
![](https://paper-attachments.dropbox.com/s_DA1709E040ABF8BBB119E5577F605CB94E7907764CD542C35444EFFCDFC60F6E_1605674130374_image.png)

2. DFS (Depth First Search)

    DFS is an algorithm for traversing or searching tree or graph data structures. The algorithm starts at the root node (selecting some arbitrary node as the root node in the case of a graph) and explores as far as possible along each branch before backtracking.
### Covered Algorithms
Shortest Path

   a. Dijkstra’s Algorithm:
        Let the node at which we are starting be called the initial node. Let the distance of node Y be the distance from the initial node to Y. Dijkstra's algorithm will assign some initial distance values and will try to improve them step by step. 

![Dijkstra Animation.gif](https://upload.wikimedia.org/wikipedia/commons/5/57/Dijkstra_Animation.gif)

   b. Floyd-Warshall Algorithm:
        The Floyd–Warshall algorithm compares all possible paths through the graph between each pair of vertices. It is able to do this with several comparisons in a graph, even though there may be up to several edges in the graph, and every combination of edges is tested. It does so by incrementally improving an estimate on the shortest path between two vertices, until the estimate is optimal.
[](https://www.dropbox.com/scl/fi/qulx20kgxksh9kgj6j1tm/CS225-Final-Project-Goal.paper?dl=0&rlkey=05sgitazcpbxgz6s22bthzteg)
   
### Complex or Uncovered Options
Landmark Path (shortest path from a to b through c):
We plan to load the routes dataset and treat it as a directed graph.The basis of the algorithm is the presence of landmarks, placed at different vertices throughout the graph. Each landmark stores the shortest path from itself to all other vertices. LPI works by searching for intersection points along the landmark paths to approximate a path between two points.

---

# DEVELOPMENT

## November 22nd
Met for 1 hour and discussed how to start the project. For the project to begin, we need to write the class for the airport data,deciding on the implementation of the graph structure and parse the data set. Group members are not very familiar the algorithms we are going to implement so we decided to spend two days learn on our own the algorithms and different graph implementations. We will meet again on the 24th and start working on the header file and parser. To reiterate the objectives for the next meeting:

* Learn Floyd-Warshall Algorithm and Landmark Path Algorithm
* Figure out three implementations of graph and where direction and weight fits in

## November 24th
Met for 2 hours and discussed details of implementation. Decided to implement adjacency matrix as graph structure. Assigned tasks to members and try to clarify each person's responsibilities. Before next meeting, the following functions will be implemented:

* Read files from airport.dat and build a dictionary of city name and corresponding airport name
* In the main constructor for the graph class, read from file and build adjacency matrix of each flights, use distance location as weights
* Read location info from airpot.dat and implement a function go grab distance between two cities
* Write test functions as needed

```
//@author: r.w.
//take the city name as user input and find matching
//airport abbreviation as output, the query info should come from airports.dat
//this can be in an auxilirary class
//@input "New York"
//@return "JFK"
std::string cityToAirport(std::string city_name) 

//@author: r.w.
//@author: z.l + y.z
//this functionality is part of the constructor of pattern class
//read flight data from routes.dat and return a collection of data pairs contains the
//start point and destination of the flight
//@input "routes.txt"
//@output a vector of string pairs 
//std::vector<std::pair<std::string, std::string>> 

//@author: z.l + y.z
//this is a helper function within the constructor to establish the adjacency matrix
//the column and rows are airport, and each element holds the distance between the two
//@input a vector holding every distinct airport
void Pattern::construct_(vector<std::string> airport_list)

//@author: w.c
//read airport name and location from airports.dat and save the data tuple
//of alll airports as a dictionary dict_
//there are duplicate entries in the dataset, need to omit duplicate flights
//this function should also set size_, the number of airport in the dictionary. This can be 
//achieved with size() function in unordered_map
//@input "airport.txt"
void Pattern::airportLoc(std::string file)


//@author: w.c
//given names of the airport, return the distance between them
//this serves as the weight of the edges
//@input two distinct string corresponding to source and destination
//@output distance according to the location of the two airport
double Pattern::distance(std::string source, std::string dest)
```

## November 27th
After 24th, met once on the following day and discussed a short documentation to clarify each person's role. Right now, we are almost finished with writing the graph object, including grabbing necessary information in two text files(r.w. and w.c.), and constructing the adjacency matrix (z.l). Made some progress on the shortest path implementation(y.z), the code is ready, to be tested alongside the constructor. Since the mid-point check point is next Friday, wewill work towards finishing up with constructor and shortest path algorithm. If we have time, we will be working towards making necessary test cases for the constructor and shortes path functions and start developing traversal algorithm. 

## December 1st
Met with TA and went over out project. TA helped to clarify some of the project goals and details about the presentation.

## December 6th
Met and discussed how to wrap up the project. We discussed the plan for the next week before everyone gets busy with the finals. The remaining tasks are debug shortest path algorithm (y.z.), write test cases(r.w.), write the front end(w.c.) and finish the traversal implementation(z.l.). We agree to meet next Thursday to wrap up.

---
## RESULTS

We are able to implement the three functionalities we set out to achieve: traversal through BFS, shortest path through Floyd-Warshall algorithm and Landmark Path algorithm implemented through Floyd-Warshall. 

![image](https://github-dev.cs.illinois.edu/cs225-fa20/wanrong2-zheli3-yuqi6-yiminw3/blob/master/images/workflow.png)

We spent most of our time design and set up the graph structure through adjacency matrix and implementing the Floyd-Warshall algorithm. Setting up the adjacency matrix is easierly said than done. We need to read and process information from two files and set up a directed, weighted graph structure. We also set up simple front end and make files for the user to interact with the program through command line interface. 

![image](https://github-dev.cs.illinois.edu/cs225-fa20/wanrong2-zheli3-yuqi6-yiminw3/blob/master/images/graph.png)

We had to abandon some of our functionalities in the fron end because coordinating information from two files became hindrance to the functionality of the program. But at the end, we were able to thoroughly test out our implementation, which is probably the biggest achievement in this project. As four non-CS major, we are very proud of what are able to achieve under the time constraint, especially considering one of our member is abroad and wee had to coordinate our time differences.

- When implementing the algorithms, we had some interesting finding:

When we use a small part of the route dataset, the algoritms ran pretty fast. However, when we use the entire routes dataset which contains thousands of entries, the number of airports is extemly large thus the adj matrix is also very large. thus it would take a long time to run the floyd shoreat algoritm. The reason is that the space complexity is O(n^2) and the time complxtity is O(n^3) is the number of unique airports. Moreover, when the number of unique airports is much less than the number of paths, the adj matrix can be very sparse and leads to a waste of space. In addition, it could be very hard to find the direct or indirect path between source and destination.


 - As a team, we have learned that:
1. Compared to MPs, we learned how to build a project to acomplish the data structure algoritms from scrach
2. How multiple people working on the project and coding together through github 

- If we have more time in the future, we would consider:
1. Enable city name as input instead of IATA code 
2. Build a user-friendly graphic front-end interface
