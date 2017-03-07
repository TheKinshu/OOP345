
 // Workshop 6 - Lambda Expression
 // w6.cpp

 #include <iostream>
 #include "Grades.h"

 int main(int argc, char* argv[]) {
     if (argc != 2) {
         std::cerr << argv[0] <<
          ": incorrect number of arguments\n";
         std::cerr << "Usage: " << argv[0] << " file_name\n"; 
         return 1;
     }


     Grades grades(argv[1]);
     // define the lambda expression for letter
		 auto letter = [](double grade) -> std::string{
			std::string lGrad;

			if(grade > 90){ lGrad = "A+"; }
			else if(grade >= 80){ lGrad = "A"; }
			else if(grade >= 75){ lGrad = "B+"; }
			else if(grade >= 70){ lGrad = "B"; }
			else if(grade >= 65){ lGrad = "C+"; }
			else if(grade >= 60){ lGrad = "C"; }
			else if(grade >= 55){ lGrad = "D+"; }
			else if(grade >= 50){ lGrad = "D"; }
			else if(grade >= 0){ lGrad = "F"; }
			
			return lGrad;
		 };

     grades.displayGrades(std::cout, letter);

     std::cout << "Press any key to continue ... ";
     std::cin.get();
     return 0;
 }