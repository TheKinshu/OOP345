#include "Message.h"
namespace w5{
      Message::Message(std::ifstream& in, char recDelim){
			
				std::string line;
				getline(in, line, recDelim);
 	
   		  auto cr = line.find('\r');
  			if(cr != string::npos)
  				line.erase(line.begin() + cr);

				int index = 0;
				while(index < line.size() && line[index] != ' '){
					name+= line[index];
          index++;
				}
        
        index++;//skip
				if(index < line.size() && line[index] == '@'){
					index++;
					while(index < line.size() && line[index] != ' ')
						reply += line[index++];
          index++;//skip
				}
				while(index < line.size())
						text += line[index++];
        
			}
      bool Message::empty() const{
				return text.empty();
			}
			void Message::display(std::ostream& os) const{
				os << "Message\n";
				os << " User  : " << name << "\n"; 
				if(!reply.empty())
				os << " Reply : " << reply << "\n"; 
				os << " Tweet : " << text << "\n"; 
			}

}