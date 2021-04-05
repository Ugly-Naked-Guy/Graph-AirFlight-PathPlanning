#include "pattern.h"

int main()
{

  Pattern *test = new Pattern("data/rt_sm_test.txt");
  string method;
  string source, dest, mid;
  cout << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "++++++++++++++++++++ Welcome to Flight Finder ++++++++++++++++++++\n";
  cout << "Enter the method you want:\nEnter a for Findshortest Path Method;\n";
  cout << "Enter b for Findshortest Path Method with Midpoint;\nEnter c for Traversal Method;" << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << endl;
  cin >> method;

  if (method == "a")
  {
    cout << "Findshortest Path Method:\nPlease enter the departure:" << endl;
    //getline(cin, source);
    cin >> source;
    cout << "Please enter the destination" << endl;
    //getline(cin, dest);
    cin >> dest;
    if (source != "" && dest != "")
    {
      cout << "The Shortest path is " << test->findShorestPath(source, dest) << ", the distance is " << test->findShorestDist(source, dest) << " meters.\n";
    }
    else
      return 0;
  }
  else if (method == "b")
  {
    cout << "Findshortest Path Method:\nPlease enter the departure:" << endl;
	cin >> source;
    cout << "Please enter the midpoint:" << endl;
	cin >> mid;
    cout << "Please enter the destination: " << endl;
	cin >> dest;
    if (source != "" && mid != "" && dest != "")
    {
      cout << test->findShorestPathWithMidpoint(source, mid, dest) << ", the distance is " << test->findShorestDistWithMidpoint(source, mid, dest) <<" meters.\n";

    }
    else
      return 0;
  }
  else if (method == "c")
  {
    cout << "Traversal Method:\nPlease enter the starting point:" << endl;
	cin >> source;
    vector<string> cities = test->traversal(source);
    for (string i : cities)
    {
      cout << i << " ";
    }
    cout << endl;
  }

  return 0;
}
