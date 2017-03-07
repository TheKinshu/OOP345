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
			Message(std::ifstream&, char);
			bool empty() const;
			void display(std::ostream&) const;
	};
}//end of namespace