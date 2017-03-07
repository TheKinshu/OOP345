#pragma once
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>

namespace w8{
  template<class T>
  class DataTable {
    std::vector<T> x, y;
    int wid, dec;
  public:
    DataTable(std::ifstream& is,int width, int decimal):wid(width),dec(decimal){
      while(is.good()){
      std::string line;
        getline(is, line);
  			auto cr = line.find('\r');
  			if(cr != std::string::npos){
  				line.erase(cr);
  			}
        T xx, yy;
        std::stringstream ss;
			  
        if(not line.empty()){
          ss << line;
          ss >> xx >> yy;
          
          x.push_back(xx);
          y.push_back(yy);
        }
 	  	}
    }

		T mean()const{
      T total = std::accumulate(y.begin(),y.end(), 0.0);
      //std::cout << "Mean: -->"<<total/y.size();
      return total/y.size();
    }

		T sigma() const
		{
			T value = mean();
      T sig = 0;
      
      for(auto i = 0; i < y.size(); i++)
        sig += (y[i] - value) * (y[i] - value);
        
      sig = std::sqrt(sig/y.size());
      
      return sig;
		}

    T median() const{
      std::vector<T> mid;
	    T temp;
      mid = y;
      std::sort(mid.begin(),mid.end());
      
      temp = mid[mid.size()/2];
      
      return temp;
    }

		void regression(T& slope, T& y_intercept) const{
			T meanX = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
			T meanY = mean();

			T num = 0, den = 0;
			for (auto i = 0; i < x.size(); i++){
				num += (x[i] - meanX) * (y[i] - meanY);
				den += (x[i] - meanX) * (x[i] - meanX);
			}
			slope = num/den;
			y_intercept = meanY - slope * meanX;
		}

		void display(std::ostream& os) const{
			os << std::setw(wid) << "x";
			os << std::setw(wid) << "y";
      os << std::endl;

			for (auto i = 0; i < x.size(); i++){
				os << std::setw(wid) << std::setprecision(dec) << x[i];
				os << std::setw(wid) << std::setprecision(dec) << y[i];
        os << std::endl;
			}
		}
  };
  template<class T>
	std::ostream& operator<<(std::ostream& os, const DataTable<T>& dataT){
      dataT.display(os);
      return os;
  }
}