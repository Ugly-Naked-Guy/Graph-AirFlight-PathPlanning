#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <limits.h>
#include <float.h>
#include <cstdlib>
#include <set>
#include <queue>
using namespace std;

class Pattern
{
  //naming: please put a dash after private members
private:
  //establish the adjacency matrix the column and rows are airport, and each
  //element holds the distance between the two
  std::vector<std::vector<double>> matrix_;
  //number of airport/vertex
  int size_;

  double INF = DBL_MAX;
  // map to find the initial of the airport based on col/row index and vice versa
  std::unordered_map<string, int> airport_to_idx_;
  std::unordered_map<int, string> idx_to_airport_;

  // matrix for floyd-warshall algorithm to find the shorest path
  std::vector<std::vector<int>> shorest_path_matrix;
  std::vector<std::vector<double>> shorest_distance_matrix;

  //dictionary from airport.txt, key is airport abbreviation, tuple consists of
  //location info (longitude and lattitude) and name of the city
  std::unordered_map<std::string, std::tuple<string, double, double>> airport_dict_;

  //called by constructor to fill matrix_, index dictionary
  void build_helper_(std::vector<std::pair<std::string, std::string>> &routes);
  //helper function for bfs traversal
  void bfs(int start, std::vector<int>& visited_edge, std::vector<int>& visited_vertex, std::vector<int>& path);

  /**
   * @author: y.z
   * this function will build the distance and path matrix for Floyd algorithm
   * helper function
   */
  void initFloyd();

  //@author: w.c
  //read airport name and location from airports.dat and save the data tuple
  //of alll airports as a vector
  //there are duplicate entries in the dataset, need to omit duplicate flights
  //@input "airport.txt"
  //@output each tuple consists of abbreviation of the airpot, lattitude and longitude
  void airportLoc(std::string file);

  //@author: w.c
  //given names of the airport, return the distance between them
  //this serves as the weight of the edges
  //@input two distinct string corresponding to source and destination
  //@output distance according to the location of the two airport
  double distance(std::string source, std::string dest);

public:
  //constructor that takes a flight routes file and build adjacency matrix
  //@author: z.l.
  Pattern(std::string file);

  //traversal through all airports in the graph, implemented with BFS
  //return a list of abbreviations for airports
  //@author: z.l.
  vector<std::string> traversal(std::string start_pt);


  // helper functions for test and debug
  /**
   * @author: y.z.
   * this function will output all the airports (verteices) and airlines (edges) to a txt file
   * reference: https://blog.csdn.net/u012273127/article/details/61915310
   */
  void WriteMainMatrix();
  void WriteDistMatrix();
  void WritePathMatrix();
  int getSize();

  /**
   * @author: y.z
   * @param source: the initial of source airport
   * @param dest: the initial of destination airport
   * @output: a pair of the path (JFK->CHI->LAS) and distance(12232.73)
   * refernce: https://houbb.github.io/2020/01/23/data-struct-learn-03-graph-floyd
  */
  std::string findShorestPath(std::string source, std::string dest);
  double findShorestDist(std::string source, std::string dest);

  /**
   * @author: y.z
   * @param source: the initial of source airport
   * @param mid: the initial of midpoint airport
   * @param dest: the initial of destination airport
   * @output: a pair of the path with the midpoint(JFK->CHI->LAS) and distance(12232.73)
  */
  std::string findShorestPathWithMidpoint(std::string source, std::string mid, std::string dest);
  double findShorestDistWithMidpoint(std::string source, std::string mid, std::string dest);
};
