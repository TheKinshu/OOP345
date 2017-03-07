#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
namespace w5{
	class Message{
		string name, text, reply;
		public:
			Message(){}
			Message(std::ifstream& in, char recDelim){
				
				name.clear();
				reply.clear();
				text.clear();
				
				std::string line;
				getline(in, line, recDelim);
 	
   		  auto cr = line.find('\r');
  			if(cr != string::npos)
  				line.erase(line.begin() + cr);
          
				cout << "Line = -->" << line << "<--\n";
				int index = 0;
				while(index < line.size() && line[index] != ' '){
					name+= line[index];
          index++;
				}
        
				cout << "name= -->" << name << "<--\n";
        cout << "gaewgae";
        index++;//skip
				if(index < line.size() && line[index] == '@'){
					index++;
					while(index < line.size() && line[index] != ' ')
						reply += line[index];
					cout << "reply=" << reply << "\n";
					index++;//skip
				}
				while(index < line.size())
						text += line[index];
				cout << "text=" << text << "\n";	
			}
			bool empty() const{
				return text.empty();
			}
			void display(std::ostream& os) const{
				os << "Message\n";
				os << " User  :" << name << "\n"; 
				if(!reply.empty())
				os << " Reply :" << reply << "\n"; 
				os << " Tweet :" << text << "\n"; 
			}
	};
}//end of namespace