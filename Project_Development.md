# Project Development
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


