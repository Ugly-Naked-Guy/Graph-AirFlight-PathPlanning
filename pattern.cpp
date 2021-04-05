#include "pattern.h"
#include "math.h"
#define pi 3.14159265358979323846264338322795
#define EARTH_RADIUS 6378.137
using namespace std;

void Pattern::build_helper_(std::vector<std::pair<std::string, std::string>> &routes)
{

  std::set<std::string> cities;
  //build index dict according to the available routes

  //use set to filter unique airport
  for (auto itr = routes.begin(); itr != routes.end(); ++itr)
  {
    cities.insert(itr->first);
    cities.insert(itr->second);
  }

  auto itr = cities.begin();
  for (size_t i = 0; itr != cities.end(); ++i)
  {
    //std::cout<<*itr<<std::endl;
    airport_to_idx_[*itr] = i;
    idx_to_airport_[i] = *itr;
    ++itr;
  }

  //save to the vertex size
  size_ = cities.size();

  //build adjacency matrix
  matrix_ = std::vector<std::vector<double>>(size_, std::vector<double>(size_, INF));

  //fill the matrix with distance
  for (auto itr = routes.begin(); itr != routes.end(); ++itr)
  {

    double dist = distance(itr->first, itr->second);
    //std::cout<<dist<<" ";

    auto sr = airport_to_idx_.find(itr->first);
    auto dt = airport_to_idx_.find(itr->second);
    if (sr != airport_to_idx_.end() && dt != airport_to_idx_.end())
      matrix_[sr->second][dt->second] = dist;
  }
}

//constructor to read file and call helper to build graph
Pattern::Pattern(std::string file_name)
{

  std::vector<std::pair<std::string, std::string>> routes;

  std::string temp;
  std::ifstream myfile(file_name);

  if (!myfile.is_open())
  {
    std::cout << "Failed to open input file" << std::endl;
    myfile.close();
    return;
  }

  while (getline(myfile, temp))
  {
    //std::cout<<temp<<std::endl;
    std::stringstream linestream(temp);
    std::string line;

    //format of entry: BA,1355,SIN,3316,MEL,3339,Y,0,744
    std::string airline, scr, det;
    std::string airlineNo, scrNum, detNum;

    getline(linestream, airline, ',');
    getline(linestream, airlineNo, ',');
    getline(linestream, scr, ',');
    getline(linestream, scrNum, ',');
    getline(linestream, det, ',');
    getline(linestream, detNum, ',');

    //std::cout<<scr<<" "<<det<<std::endl;
    routes.push_back(std::pair<std::string, std::string>(scr, det));
  }

  //read airport file for necessary distance information
  airportLoc("data/airport.txt");

  build_helper_(routes);
  initFloyd();
  myfile.close();
}

void Pattern::airportLoc(const std::string file)
{
  ifstream myfile(file);
  string temp;
  string str = "no_record";

  if (myfile.is_open())
  {
    while (getline(myfile, temp))
    {
      string id, name, city, country, ICAO_code, IATA_code, latitude, longitude;
      double lat, lgt;

      temp.erase(remove(temp.begin(), temp.end(), '\"'), temp.end());
      std::stringstream linestream(temp);

      getline(linestream, id, ',');
      getline(linestream, name, ',');
      getline(linestream, city, ',');
      getline(linestream, country, ',');
      getline(linestream, IATA_code, ',');
      getline(linestream, ICAO_code, ',');

      getline(linestream, latitude, ',');

      getline(linestream, longitude, ',');

      if (IATA_code == str || latitude == str || longitude == str)
        continue;

      try
      {
        lat = std::stod(latitude);
        lgt = std::stod(longitude);
      }
      catch (const std::invalid_argument &exception)
      {
        continue;
      }

      airport_dict_[IATA_code] = tuple<std::string, double, double>(city, lat, lgt);
    }
  }

  myfile.close();
}

double Pattern::distance(std::string source, std::string dest)
{
  double latitude1 = 0.0;
  double longitude1 = 0.0;
  double latitude2 = 0.0;
  double longitude2 = 0.0;

  auto itr_s = airport_dict_.find(source);
  auto itr_d = airport_dict_.find(dest);

  if (itr_s != airport_dict_.end() && itr_d != airport_dict_.end())
  {
    latitude1 = get<1>(itr_s->second);
    latitude2 = get<2>(itr_s->second);
    longitude1 = get<1>(itr_s->second);
    longitude2 = get<2>(itr_s->second);
  }

  double radlat1 = latitude1 * pi / 180.0;
  double radlat2 = latitude2 * pi / 180.0;
  double a = radlat1 - radlat2;
  double b = longitude1 * pi / 180.0 - longitude2 * pi / 180.0;
  double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radlat1) * cos(radlat2) * pow(sin(b / 2), 2)));
  return s * EARTH_RADIUS * 1000;
}

//important to bear in mind: we need to visite every edge of the matrix
vector<std::string> Pattern::traversal(std::string start_pt)
{
  //create and open file to write in
  std::vector<std::string> cities;
  cities.reserve(size_);

  std::vector<int> visited_edge(size_ * size_, 0);
  //access with index (i * size_ + j)

  std::vector<int> visited_vertex(size_, 0);

  std::vector<int> path;
  path.reserve(size_);

  int num = airport_to_idx_[start_pt];
  bfs(num, visited_edge, visited_vertex, path);

  for (auto itr = airport_to_idx_.begin(); itr != airport_to_idx_.end(); ++itr)
  {
    if (visited_vertex[itr->second] != 1)
      bfs(itr->second, visited_edge, visited_vertex, path);
  }
  for (int i : path)
  {
    cities.push_back(idx_to_airport_[i]);
  }

  return cities;
}

void Pattern::bfs(int start, std::vector<int> &visited_edge, std::vector<int> &visited_vertex, std::vector<int> &path)
{
  std::queue<int> queue;

  queue.push(start);
  path.push_back(start);
  visited_vertex[start] = 1;

  while (!queue.empty())
  {
    int current = queue.front();
    queue.pop();
    //this is get adjacent
    for (int i = 0; i < size_; ++i)
    {
      if (matrix_[current][i] != INF && visited_vertex[i] == 0)
      {
        queue.push(i);
        visited_vertex[i] = 1;
        path.push_back(i);
        visited_edge[current * size_ + i] = 1;
      }
      else if (matrix_[current][i] != INF && visited_edge[current * size_ + i] == 0)
      {
        visited_edge[current * size_ + i] = 1;
      }
    }
  }
}

void Pattern::initFloyd()
{
  // Step 1: initialize the path and distance matrix for the floyd algorithm
  shorest_distance_matrix = std::vector<std::vector<double>>(size_, std::vector<double>(size_, INF));
  shorest_path_matrix = std::vector<std::vector<int>>(size_, std::vector<int>(size_, INF));
  for (int i = 0; i < size_; i++)
  {
    for (int j = 0; j < size_; j++)
    {
      //copy every element（direct distance or INF) in the adjacency matrix to the shorest_distance_matrix
      shorest_distance_matrix[i][j] = matrix_[i][j];
      // fill every entry with "-2"
      shorest_path_matrix[i][j] = -2;
      // set the distance to 0, path to -1 if source == dest
      if (i == j)
      {
        shorest_distance_matrix[i][j] = 0;
        shorest_path_matrix[i][j] = -1;
      }
      // set the path to -1 if direct flight exists
      if (matrix_[i][j] < INF)
      {
        shorest_path_matrix[i][j] = -1;
      }
    }
  }

  // Step 2: update each entry in the shoest path and distance matrix
  double tmp_dist = INF;
  for (int k = 0; k < size_; k++)
  {
    for (int i = 0; i < size_; i++)
    {
      for (int j = 0; j < size_; j++)
      {
        if (i != k && j != k && shorest_distance_matrix[i][j] >= INF)
        {
          tmp_dist = INF;
          // if both distance i->k and k->j are not INF, set the temp_dist to the distance sum
          if (shorest_distance_matrix[i][k] < INF && shorest_distance_matrix[k][j] < INF)
          {
            tmp_dist = shorest_distance_matrix[i][k] + shorest_distance_matrix[k][j];
          }
          // if the distance i->k->j < i->j, update the entry in the distance ans path matrix
          if (tmp_dist < shorest_distance_matrix[i][j])
          {
            // record the minimum distance
            shorest_distance_matrix[i][j] = tmp_dist;
            // record the k_th airport
            shorest_path_matrix[i][j] = k;
          }
        }
      }
    }
  }
}

std::string Pattern::findShorestPath(std::string source, std::string dest)
{
  //airport ->index
  int source_idx = airport_to_idx_[source];
  // std::cout << "source_idx: " << source_idx << std::endl;
  int dest_idx = airport_to_idx_[dest];
  // std::cout << "dest_idx: " << dest_idx << std::endl;

  //find the shorest path
  std::string shorest_path;
  int mid_idx = shorest_path_matrix[source_idx][dest_idx];
  // std::cout << "mid_idx: " << mid_idx << std::endl;

  // no path
  if (mid_idx == -2)
  {
    shorest_path = "There is no path from " + source + " to " + dest;
  }
  // direct path
  else if (mid_idx == -1)
  {
    shorest_path = source + "->" + dest;
  }
  //indirect path
  else
  {
    std::string mid = idx_to_airport_[mid_idx];
    shorest_path = findShorestPath(source, mid) + ", " + findShorestPath(mid, dest);
  }

  return shorest_path;
}

double Pattern::findShorestDist(std::string source, std::string dest)
{
  //airport ->index
  int source_idx = airport_to_idx_[source];
  int dest_idx = airport_to_idx_[dest];
  //find the shorest distance
  double shorest_distance;
  //update the shorest_distance if source airport != destination airport
  shorest_distance = shorest_distance_matrix[source_idx][dest_idx];
  if (source_idx == dest_idx)
  {
    shorest_distance = 0;
  }
  return shorest_distance;
}

std::string Pattern::findShorestPathWithMidpoint(std::string source, std::string mid, std::string dest)
{
  // find the shorest distance

  //find the shorest path
  std::string shorest_path;
  shorest_path = findShorestPath(source, mid) + ", " + findShorestPath(mid, dest);

  return shorest_path;
}
double Pattern::findShorestDistWithMidpoint(std::string source, std::string mid, std::string dest)
{ // find the shorest distance
  double shorest_distance = findShorestDist(source, mid) + findShorestDist(mid, dest);
  return shorest_distance;
}

// helper function for testing (print matrix to txt file)

void Pattern::WriteMainMatrix()
{
  std::cout << "Start writing the Main Matrix to txt file ..." << std::endl;
  //create and open file to write in
  ofstream dout("matrix_.txt");

  // start traversal
  for (int i = 0; i < size_; i++)
  {
    std::string source = idx_to_airport_[i];
    for (int j = 0; j < size_; j++)
    {
      std::string dest = idx_to_airport_[j];
      double distance = matrix_[i][j];
      // write to the file
      dout << "[" << i << "]"
           << "[" << j << "] "
           << source << "->" << dest << ", "
           << distance << endl;
    }
  }

  //close the file
  dout.close();
  std::cout << "Finished" << std::endl;
}

void Pattern::WriteDistMatrix()
{
  std::cout << "Start writing the Shorest Distance Matrix to txt file ..." << std::endl;
  //create and open file to write in
  ofstream dout("shorest_distance_matrix.txt");

  // start traversal
  for (int i = 0; i < size_; i++)
  {
    std::string source = idx_to_airport_[i];
    for (int j = 0; j < size_; j++)
    {
      std::string dest = idx_to_airport_[j];
      double distance = shorest_distance_matrix[i][j];
      // write to the file if there is a path (distance < INF)
      dout << "[" << i << "]"
           << "[" << j << "] "
           << source << "->" << dest
           << ", " << distance << endl;
    }
  }

  //close the file
  dout.close();
  std::cout << "Finished" << std::endl;
}

void Pattern::WritePathMatrix()
{
  std::cout << "Start writing the Shorest Path Matrix to txt file ..." << std::endl;
  //create and open file to write in
  ofstream dout("shorest_path_matrix.txt");

  // start traversal
  for (int i = 0; i < size_; i++)
  {
    std::string source = idx_to_airport_[i];
    for (int j = 0; j < size_; j++)
    {
      std::string dest = idx_to_airport_[j];
      double distance = shorest_path_matrix[i][j];
      // write to the file if there is a path (distance < INF)
      if (distance < INF)
      {
        dout << "[" << i << "]"
             << "[" << j << "] "
             << source << "->" << dest << ", "
             << distance << endl;
      }
    }
  }

  //close the file
  dout.close();
  std::cout << "Finished" << std::endl;
}

int Pattern::getSize()
{
  return size_;
}
