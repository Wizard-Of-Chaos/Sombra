#include "displaymap.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//-----------------MapPoint functions--------------------

MapPoint::MapPoint(int x, int y, char type) : m_x(x), m_y(y), m_type(type)
{
}

MapPoint::MapPoint() : m_x(0), m_y(0), m_type('.')
{
}

MapPoint::~MapPoint()
{
  //You ever just include stuff out of habit?
}

int MapPoint::x()
{
  return m_x;
}

int MapPoint::y()
{
  return m_y;
}

char MapPoint::type()
{
  return m_type;
}

void MapPoint::set_type(char c)
{
  m_type = c;
}

//----------------DisplayMap functions-------------------

DisplayMap::DisplayMap(vector<string> map, int height, int width) : m_map(map), m_height(height), m_width(width)
{
  int h_pos = 0;
  int w_pos = 0;
  for(string s : map) {
    vector<MapPoint> line;
    for(char c : s) {
      MapPoint p(w_pos, h_pos, c);
      line.push_back(p);
      if (c == 'S') {
        m_start_coords = p;
      }
      if (c == 'F') {
        m_end_coords = p;
      }
      ++w_pos;
    } //Individual characters in string handled.
    m_map_details.push_back(line);
    ++h_pos;
    w_pos = 0;
  } //Detailed map should now be filled out in map points.
  cout << "DEBUGGING" << endl;
  cout << "Start X: " << m_start_coords.x() << " Start Y: " << m_start_coords.y() << endl;
  cout << "End X: " << m_end_coords.x() << " End Y: " << m_end_coords.y() << endl;
}

DisplayMap::~DisplayMap()
{
  //Yeah, definitely habit.
}

bool DisplayMap::inbounds(int x, int y)
{
  if (x < 0 || x >= m_width) return false;
  if (y < 0 || y >= m_height) return false;
  return true;
}

MapPoint DisplayMap::get_point(int x, int y)
{
  for (vector<MapPoint> v : m_map_details) {
    for ( MapPoint p : v) {
      if (p.x() == x && p.y() == y)
        return p;
    }
  }
}

vector<MapPoint> DisplayMap::neighbors(MapPoint point) //Why the hell wasn't this a method from the start? Christ am I dumb.
{
  vector<MapPoint> neighbors;
  if(inbounds(point.x()-1, point.y())) {
   neighbors.push_back(get_point(point.x()-1, point.y()));
  }
  if(inbounds(point.x()+1, point.y())) {
   neighbors.push_back(get_point(point.x()+1, point.y()));
  }
  if(inbounds(point.x(), point.y()-1)) {
   neighbors.push_back(get_point(point.x(), point.y()-1));
  }
  if(inbounds(point.x(), point.y()+1)) {
   neighbors.push_back(get_point(point.x(), point.y()+1));
  }
  return neighbors;
}

void DisplayMap::show_start_obstacles()
{
  int obstaclecount = 0;
  vector<MapPoint> coords = neighbors(m_start_coords);
  for (MapPoint p : coords) {
    	if (p.type() == '#')
      	  ++obstaclecount;
  }
  cout << "There are " << obstaclecount << " obstacle(s) next to the start." << endl;
}

//Order of both displays goes east, west, south, north
void DisplayMap::show_finish_obstacles()
{
  int obstaclecount = 0;
  vector<MapPoint> coords = neighbors(m_end_coords);
  for (MapPoint p : coords) {
    if (p.type() == '#')
      ++obstaclecount;
  }
  cout << "There are " << obstaclecount << " obstacle(s) next to the end." << endl;
}

void DisplayMap::print()
{
  for (vector<MapPoint> v : m_map_details) {
    for( MapPoint p : v) {
      cout << p.type();
    }
    cout << endl;
  }
  cout << "Height / Width: " << m_height << " " << m_width << endl;
}

MapPoint DisplayMap::start()
{
  return m_start_coords;
}

MapPoint DisplayMap::end()
{
  return m_end_coords;
}

void DisplayMap::edit_point(int x, int y, char c)
{ 
  for (vector<MapPoint>& v : m_map_details) {
    for ( MapPoint& p : v) {
      if (p.x() == x && p.y() == y)
        p.set_type(c);
    }
  }
}

