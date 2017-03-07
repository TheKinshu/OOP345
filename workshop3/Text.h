#include <fstream>
#include <string>
#include <iostream>

namespace w3{
	class Text{
		size_t count;
		std::string* lineTable;
	public:
		Text();
		~Text();
		Text(const char*);
		size_t size();
		Text& operator=(const Text& rhs);
		Text&& operator=(Text&& rhs);
		Text(const Text& rhs);
		Text(Text&& rhs);
	};
} // end of namespace w3