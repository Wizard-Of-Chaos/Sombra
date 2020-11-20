#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "displaymap.h"
#include "min_heap.h"
#include <map>
#include <cmath>
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

double heuristic(Node* start, Node* end)
{
  int dx = abs(start->x - end->x);
  int dy = abs(start->y - end->y);
  return sqrt(pow((double)dx, 2.0) + pow((double)dy, 2.0));
}

void a_star(DisplayMap& cur_map)
{
  MinHeap open_set;
  map<Node*, bool> closed_set;
  open_set.add(cur_map.nstart());
  cur_map.nstart()->gscore = 0;
  cur_map.nstart()->fscore = heuristic(cur_map.nstart(), cur_map.nend());
  for(Node* n : cur_map.node_dump()) {
    closed_set[n] = false;
  }
  Node* winner = nullptr;

  while(open_set.size() != 0) {
    Node* cur = open_set.min();
    if(cur == cur_map.nend()) {
      winner = cur->previous; //Establishes the correct path
      break;
    }

    open_set.pop();
    vector<Node*> cur_neighbors = cur_map.node_neighbors(cur); //Gets the neighbors from the current node.
    closed_set[cur] = true;

    for (Node* neighbor : cur_neighbors) {
      if(cur_map.get_point(neighbor->x, neighbor->y).type() == '#' || closed_set[neighbor] == true) {
        continue;
      }
      if(cur->gscore +1 < neighbor->gscore) {
        neighbor->gscore = cur->gscore + 1;
        neighbor->fscore = neighbor->gscore + heuristic(neighbor, cur_map.nend());
        neighbor->previous = cur;
        open_set.add(neighbor);
      }
    }
  }

  if (winner == nullptr) {
    cur_map.print();
    cout << "No path was found." << endl;
    return;
  }
  Node* tracker = winner->previous;
  cur_map.edit_point(winner->x, winner->y, '*');
  while(tracker != cur_map.nstart()) {
    cur_map.edit_point(tracker->x, tracker->y, '*');
    tracker = tracker->previous;
  }
  cur_map.print();
  cout << "Path found." << endl;
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
  a_star(view);
}
