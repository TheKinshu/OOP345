#include "CString.h"
#include <cstring>
#pragma warning(disable:4996)

namespace w1{
	CString::CString(char* str){
		if (str == '\0'){
			str_[0] = '\0';
		}
		else{
			strncpy(str_,str,MAX);
      str[3] = '\0';
		}
	}
	void CString::display(std::ostream& os){
    for(int i = 0; i < MAX; i++){
  		os << str_[i];
    }
	}
	std::ostream& operator<<(std::ostream& os, CString str){
		static int insert = 0;

		os << insert << ": ";
		str.display(os);
		insert++;
		return os;
	}
}
