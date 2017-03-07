#include "Text.h"
namespace w3{
	Text::Text() : count(0), lineTable(nullptr){}
	
	Text::~Text(){
		delete [] lineTable;
	}
	Text::Text(const char* filename) : count(0), lineTable(nullptr){
		std::ifstream is(filename);
		if(is.is_open()){
			std::string line;
			while(std::getline(is,line)){
				count++;
			}
			std::cout << "Read " << count << " Lines\n";
			
			lineTable = new std::string[count];
			
			//the file is currently at the end of file and in an error state
			is.clear(); //need to clear the 'error-state'
			is.seekg(0);
		  //is.seekp(0);//for files, does exactly the same thing as 'seekg'
			for(int i = 0; i < count; i++){
				std::getline(is,lineTable[i]);
				auto cr = lineTable[i].find( '\r' );
				if(cr != std::string::npos){
					lineTable[i].erase(cr);
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
	size_t Text::size(){
		return count;
	}
	Text& Text::operator=(const Text& rhs){ //C++ assignment operator
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
	Text&& Text::operator=(Text&& rhs){
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
	Text::Text(const Text& rhs) : count(0), lineTable(nullptr){
		*this = rhs;
	}
	Text::Text(Text&& rhs): count(0), lineTable(nullptr){
		*this = std::move(rhs);
	}
}