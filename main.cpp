#include <iostream>
#include <fstream>
#include <string>

vector<vector<Point>> get_map(std::string filename)
{
	vector<vector<Point>> map;
	ifstream grab(filename);
	while(getline(grab))
	{
		//load stuff into the map vector
	}
	grab.close();
	return map;
}

int main (int argc, char** argv) 
{
  std::cout << "Placeholder!" << std::endl;
}
