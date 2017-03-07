#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "Station.h"
#include <iostream>


namespace w2{
	 class Stations{
		 int stationCount;
		 Station* stationTable;
		 public:
		 Stations(const char*);
		 ~Stations();
		 void update();
		 void restock();
		 void report();
	 };
}//end of w2