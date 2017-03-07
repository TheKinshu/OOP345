#pragma once

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Grades{
	double* mark;
	string* ID;
	int count;
	public: 
		Grades():ID(nullptr),mark(0),count(0){}
		Grades(string filename):count(0){
     int tempCount = 0;
			string line;
			ifstream is(filename);
			if(!is.is_open()){
				throw string("Cannot open file '" + filename + "'\n");
			}
      if(is.is_open()){
      
      while(getline(is, line))
        count++;
      
      mark = new double[count];
      ID = new string[count];

      is.clear();
      is.seekg(0);
      
  			while(!is.eof()){
          getline(is, line, ' ');
  				auto cr = line.find('\r');
  				if(cr != string::npos){
  					line.erase(cr);
  				}
  				tempCount++;
          
          ID[tempCount-1] = line;
        	getline(is, line);
         
          double temp = stod(line, 0);
          mark[tempCount-1] = temp;
  			}	
      }
			is.close();
		}
    template<typename lambda>
		void displayGrades(ostream& os, lambda letter) const{
      for(int i = 0; i < 9; i++){
        cout << ID[i] << " ";
        cout << mark[i] << " ";
        cout << letter(mark[i]) << "\n";
      }
    }
		
};