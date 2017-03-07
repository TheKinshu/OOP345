#include "Station.h"

using namespace std;
namespace w2{
  
	Station::Station(){
		stationName = "";
	}
 
	Station::Station(ifstream& is){
			string line;
			getline(is, line);
			auto cr = line.find('\r');
			
			if(cr != string::npos)
				line.erase(cr);
			//cout << "station : -->" << line << "<--\n";
			
			stringstream ss(line);
			getline(ss, stationName, ';');
			//cout << "stationName=" << stationName << "\n";
			ss >> passes[STUDENT_PASS];
			ss >> passes[ADULT_PASS];
			//cout << ", s=" << passes[STUDENT_PASS];
			//cout << ", a=" << passes[ADULT_PASS];
			//cout << "\n";
	}
	void Station::update(){
		int num;
		cout << stationName << "\n";
		cout << " Student Passes sold : ";
		cin >> num;
		passes[STUDENT_PASS] -= num;
		cout << " Adult   Passes sold : ";
		cin >> num;
		passes[ADULT_PASS] -= num;
	}
	void Station::restock(){
		int num;
		cout << stationName << "\n";
		cout << " Student Passes added : ";
		cin >> num;
		passes[STUDENT_PASS] += num;
		cout << " Adult   Passes added : ";
		cin >> num;
		passes[ADULT_PASS] += num;
	}
	void Station::report(){
		cout << setw(19) << left << stationName;
		cout << setw(6)  << right << passes[STUDENT_PASS];
	    cout << setw(6)  << passes[ADULT_PASS];
		cout << "\n";
	}
}