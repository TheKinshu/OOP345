#include "Stations.h"
using namespace std;
namespace w2{
	
 Stations::Stations(const char* filename){
		ifstream is(filename);
		if(is.is_open()){
			string line;
			getline(is, line);
			auto cr = line.find('\r');
			
			if(cr != string::npos)
				line.erase(cr);
			cout << "first line: -->" << line << "<--\n";
			
			stringstream ss;
			ss << line;
			ss >> stationCount;
			//cout << "stationCount =" << stationCount << "\n";
			char c;
			ss >> c;
			
			if(c != ';'){
				cerr << "Syntax error line 1: except ';' found '" << c << "'\n";
				exit(2);
			}
			
			stationTable = new Station[stationCount];
			
			for(int i = 0; i < stationCount; i++){
				stationTable[i] = Station(is);
			}
			
			is.close();
		}
		else{
			cerr << "Cannot open file '" << filename << "'\n";
			exit(1);
		}
	}
	
	Stations::~Stations(){
		if(stationTable)
			delete [] stationTable;

	}	
	void Stations::update(){
		/*
		 Passes Sold :
		 -------------
		*/
    cout << endl;
		cout << "Passes Sold :\n";
		cout << "-------------\n";
		for(int i = 0; i < stationCount; i++){
			stationTable[i].update();
		}
	}
	void Stations::restock(){
		/*
		Passes Added :
		--------------
		*/
    cout << "\n";
		cout << "Passes Added :\n";
		cout << "--------------\n";
		for(int i = 0; i < stationCount; i++){
			stationTable[i].restock();
		}
	}
	void Stations::report(){
		/*
		Passes in Stock : Student Adult
	    -------------------------------
	    Spadina               100   200
	    Bathurst              200   300
	    Keele                 100   100
	    Bay                   200   200
		*/
   cout << "\n";
		cout << "Passes in Stock : Student Adult\n";
		cout << "-------------------------------\n";
		for(int i = 0; i < stationCount; i++){
			stationTable[i].report();
		}
	}
}