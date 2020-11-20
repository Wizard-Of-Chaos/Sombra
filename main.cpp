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

double heuristic(Node* start, Node* end, char type)
{
  int dx = abs(start->x - end->x);
  int dy = abs(start->y - end->y);
  if (type == 'E')
    return sqrt(pow((double)dx, 2.0) + pow((double)dy, 2.0));
  if (type == 'M')
    return (double)abs((double)dx + (double)dy);
} // Returns either the Euclidean or Manhattan distance depending on which program is running

void a_star(DisplayMap& cur_map, char heur_type)
{
  MinHeap open_set;
  map<Node*, bool> closed_set;
  open_set.add(cur_map.nstart());
  cur_map.nstart()->gscore = 0;
  cur_map.nstart()->fscore = heuristic(cur_map.nstart(), cur_map.nend(), heur_type);
  for(Node* n : cur_map.node_dump()) {
    closed_set[n] = false; //Sets all nodes in map
  }
  Node* winner = nullptr; //The node that got to the finish first

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
      if(cur_map.get_point(neighbor->x, neighbor->y).type() == '#' || closed_set[neighbor] == true) { //Checks if it's either in the closed set or if it's an obstacle
        continue;
      }
      if(cur->gscore +1 < neighbor->gscore) { //If that gscore is better than the neighbors gscore add the neighbor to the open set
        neighbor->gscore = cur->gscore + 1;
        neighbor->fscore = neighbor->gscore + heuristic(neighbor, cur_map.nend(), heur_type);
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
  int count = 0;
  Node* tracker = winner->previous;
  cur_map.edit_point(winner->x, winner->y, '*');
  count += 1;
  while(tracker != cur_map.nstart()) {
    cur_map.edit_point(tracker->x, tracker->y, '*');
    tracker = tracker->previous;
    count++;
  }
  cur_map.print();
  cout << "Path found." << endl;
  cout << "Shortest path: " << count << endl;
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
  char heur;
  string name(argv[0]);
  if (name == "./Euclidean")
    heur = 'E';
  if (name == "./Manhattan")
    heur = 'M';
  
  DisplayMap view = get_map(argv[1]);
  view.print();
  view.show_start_obstacles();
  view.show_finish_obstacles();
  a_star(view, heur);
}
