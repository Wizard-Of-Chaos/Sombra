#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "displaymap.h"
#include "min_heap.h"

using namespace std;

DisplayMap get_map(string filename)
{
	vector<string> smap;
        string s;
	ifstream grab(filename);
        getline(grab, s);
        int h, w;
        stringstream ss(s);
        ss >> h >> w;
	while(getline(grab, s))
	{
		smap.push_back(s);
	}
	grab.close();
        DisplayMap map(smap, h, w);
	return map;
}

int main (int argc, char** argv) 
{
  if (argc < 2) {
    cout << "Please enter in a map file." << endl;
    return -1;
  }

  bool is_start = false;
  bool is_fin = false;
  ifstream checker(argv[1]);
  string check;
  while(getline(checker, check)) {
    for(char c : check) {
      if (c == 'F') is_fin = true;
      if (c == 'S') is_start = true;
    }
  }
  if(!is_start or !is_fin) {
    cout << "Invalid map." << endl;
    return -1;
  }
  
  DisplayMap view = get_map(argv[1]);
  view.print();
  view.show_start_obstacles();
  view.show_finish_obstacles();
}
