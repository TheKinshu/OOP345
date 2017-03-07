#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace w2{

	enum PASS_TYPE { STUDENT_PASS, ADULT_PASS, PASS_COUNT };
 
	 class Station{
			std::string stationName;
			int passes[PASS_COUNT];
		 public:
			Station();
			Station(std::ifstream& is);
			void report();
      void update();
      void restock();
	 };
   
}//end of w2