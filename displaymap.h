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
    void set_type(char c);
};

class DisplayMap
{
  private:
    std::vector<std::string> m_map;
    std::vector<std::vector<MapPoint>> m_map_details;
    int m_height;
    int m_width;
    MapPoint m_start_coords;
    MapPoint m_end_coords;
  public:
    DisplayMap(std::vector<std::string> map, int height, int width);
    ~DisplayMap();
    bool inbounds(int x, int y);
    std::vector<MapPoint> neighbors(MapPoint point);
    void show_start_obstacles();
    void show_finish_obstacles();
    MapPoint start();
    MapPoint end();
    MapPoint get_point(int x, int y);
    void edit_point(int x, int y, char c);
    void print();

};

#endif
