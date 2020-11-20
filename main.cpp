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

double heuristic(MapPoint start, MapPoint end)
{
  int dx = abs(start.x() - end.x());
  int dy = abs(start.y() - end.y());
  return sqrt(pow((double)dx, 2.0) + pow((double)dy, 2.0));
}

void a_star(DisplayMap& cur_map)
{
  map<Node*, bool> closed_set;
  MinHeap open_set;
  Node* start = new Node;
  MapPoint p = cur_map.start();
  start->x = p.x();
  start->y = p.y();
  start->previous = start;
  start->gscore = 0;
  start->fscore = heuristic(cur_map.start(), cur_map.end()); // G-score here is 0 so...
  open_set.add(start);
  //I want everyone to mark that I took a deep breath before starting to write the rest here
  //IT BEGINS
  Node* winner = nullptr;
  while(open_set.size() != 0) {
    Node* cur = open_set.min();
    if(cur_map.end().x() == cur->x && cur_map.end().y() == cur->y) {
      winner = cur->previous; //Establishes the correct path
      break;
    }
    open_set.remove(cur); //Removes the current node from the open set.
    closed_set[cur] = true;

    MapPoint translated = cur_map.get_point(cur->x, cur->y); //Gets the map thing associated with the current node.
    vector<MapPoint> cur_neighbors = cur_map.neighbors(translated); //Gets the neighbors from the current node.
    vector<Node*> neighbor_nodes;
    for (MapPoint neighbor : cur_neighbors) {
      if(neighbor.type() != '#') {
         Node* neigh = new Node;
         neigh->x = neighbor.x();
         neigh->y = neighbor.y();
         neigh->previous = cur;
         neigh->gscore = cur->gscore + 1;
         neigh->fscore = neigh->gscore + heuristic(neighbor, cur_map.end());
         open_set.add(neigh);
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
  while(tracker != start) {
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
