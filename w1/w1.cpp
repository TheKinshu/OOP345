/*
  Workshop 1
  title: From One Translation Unit to Another
  by Kelvin Cho
  May 13, 2016
  
*/

#include "CString.h"
#include "process.h"

using namespace w1;

int main(int argc, char* argv[]){

	std::cout << "Command Line :";
	
	//std::cout << strlen(str);
	for (int i = 0; i < argc; i++){
		std::cout << ' ' << argv[i];
	}
  std::cout << '\n';
	//this statement will be on if there no arguement
  //if there is no arguement display the following and exit program
  if (argc == 1){
		std::cout << "Insufficient number of arguments (min 1)\n";
		return 0;
	}
  //This tells the user how many character will be stored
	std::cout << "Maximum number of characters stored : " << 3 << '\n';
  
  //this loop output the 3 character from the arguement
  for (int i = 1; i < argc; i++){
    process(argv[i]);
  }
  std::cout << '\n';
	return 0;
}
