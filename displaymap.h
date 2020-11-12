#include <iostream>
#include <string>
#include <vector>

#ifndef DISPLAYMAP_H
#define DISPLAYMAP_H
//It's probably bad form to declare two classes at once but eh.
class MapPoint
{
  private:
    int m_x;
    int m_y;
    char m_type;
  public:
    MapPoint();
    MapPoint(int x, int y, char type);
    ~MapPoint(); 
    int x();
    int y();
    char type();
};

class DisplayMap
{
  private:
    std::vector<std::string> m_map;
    std::vector<std::vector<MapPoint>> m_map_details;
    MapPoint m_start_coords;
    MapPoint m_end_coords;
  public:
    DisplayMap(std::vector<std::string> map);
    ~DisplayMap();
    void show_start_obstacles();
    void show_finish_obstacles();
    void print();

};

#endif
