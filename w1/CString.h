#ifndef CSTRING_H_
#define CSTRING_H_

#include <iostream>

namespace w1{
	const int MAX = 3;
	class CString{
	private:
		char str_[MAX + 1];
	public:
		CString(char*);
		void display(std::ostream&);
	};
	std::ostream& operator<<(std::ostream&, CString);
}
#endif
