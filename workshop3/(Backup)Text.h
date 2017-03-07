#include <fstream>
#include <string>
#include <iostream>

namespace w3{
	class Text{
		size_t count;
		std::string* lineTable;
		public:
		Text():count(0), lineTable(nullprt){
		}
		
		~Text(){
			delete [] lineTable;
		}
		
		Text(const char* filename) : count(0), lineTable(nullprt){
			ifstream is(filename);
			if(is.is_open()){
				std::string line;
				while(getline(is)){
					count++;
				}
				std::cout << "Read " << coint << " Lines\n";
				
				lineTable = new std::string[count];
				
				//the file is currently at the end of file and in an error state
				is.clear(); //need to clear the 'error-state'
				is.seekg(0);
				is.seekp(0);//for files, does exactly the same thing as 'seekg'
				for(int i = 0; i < count; i++){
					std::getline(is,lineTable[i]);
					auto cr = lineTable[i].find( '\r' );
					if(cr != std::string::npos){
						lineTable[i].erase(cr)
					}
				}
				/*
				int lines = count;
				if(lines > 20) lines = 20;
				for(int i = 0; i < lines; i++){
					std::cout << i+1 << ": ->>" << lineTable[i] << "<<-\n";
				}
				*/
				is.close();
			}
			else{
				std::cerr << "Cannot open file '" << filename << "'\n";
			    exit(1);
			}
		}
		size_t size(){
			return count;
		}
		Text& operator=(const Text& rhs){ //C++ assignment operator
			if(this != &rhs){
				if(lineTable){
					delete [] lineTable;
					lineTable = nullptr;
					count = 0;
				}
				count = rhs.count;
				if(count){//need to allocate table deep copy the rhs data
					lineTable = new std::string[count]; //allocate space for table
					for(int i = 0; i < count; i++){ // deep copy
						lineTable[i] = rhs.lineTable[i];
					}
				}
			}
			return *this;
		}
		Text&& operator=(Text&& rhs){
			if(this != &rhs){
				if(lineTable){
					delete [] lineTable;
					lineTable = nullptr;
					count = 0;
				}
				
				//move pointer + count
				count = rhs.count;
				lineTable = rhs.lineTable;
				//reset RHS pointer + count
				rhs.count = 0;
				rhs.lineTable = nullptr;
			}
			return std::move(*this);
		}
		Text(const Text& rhs): count(0), lineTable(nullprt){
			*this = rhs;
		}
		Text(Text&& rhs): count(0), lineTable(nullprt){
			*this = std::move(rhs);
		}
	}
} // end of namespace w3