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

void DisplayMap::show_start_obstacles()
{
  int obstaclecount = 0;
  vector<MapPoint> coords;
  if (m_start_coords.x() > 0) {
    coords.push_back(m_map_details[m_start_coords.y()][m_start_coords.x() + 1]);
  }
  if (m_start_coords.x() < m_map[0].length()) {
    coords.push_back(m_map_details[m_start_coords.y()][m_start_coords.x() - 1]);
  } 
  if (m_start_coords.y() > 0) {
    coords.push_back(m_map_details[m_start_coords.y() + 1][m_start_coords.x()]);
  }
  if (m_start_coords.y() < m_map.size()) {
    coords.push_back(m_map_details[m_start_coords.y() - 1][m_start_coords.x()]);
  	}
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
  vector<MapPoint> coords;
  if (m_end_coords.x() > 0) {
    coords.push_back(m_map_details[m_end_coords.y()][m_end_coords.x() + 1]);
  }
  if (m_end_coords.x() < m_map[0].length()) {
    coords.push_back(m_map_details[m_end_coords.y()][m_end_coords.x() - 1]);
  }
  if (m_end_coords.y() > 0) {
    coords.push_back(m_map_details[m_end_coords.y() + 1][m_end_coords.x()]);
  }
  if (m_end_coords.y() < m_map.size()) {
    coords.push_back(m_map_details[m_end_coords.y() - 1][m_end_coords.x()]);
  }
  for (MapPoint p : coords) {
    if (p.type() == '#')
      ++obstaclecount;
  }
  cout << "There are " << obstaclecount << " obstacle(s) next to the end." << endl;
}

void DisplayMap::print()
{
  for (string s : m_map) {
    cout << s << endl;
  }
  cout << "Height / Width: " << m_height << " " << m_width << endl;
}
