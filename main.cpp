#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "displaymap.h"

using namespace std;

vector<string> get_map(string filename)
{
	vector<string> map;
        string s;
	ifstream grab(filename);
	while(getline(grab, s))
	{
		map.push_back(s);
	}
	grab.close();
	return map;
}

int main (int argc, char** argv) 
{
  if (argc < 2) {
    cout << "Please enter in a map file." << endl;
    return -1;
  }
  
  DisplayMap view(get_map(argv[1]));
  view.print();
  view.show_start_obstacles();
  view.show_finish_obstacles();
}
