#include "Sale.h"

namespace w7{
  Sale::Sale(const char* filename){
    std::ifstream is(filename);
    while (!is.eof())	{
      iProduct* product = readProduct(is);
      productList.push_back(product);
    }
    productList.pop_back();
  }
  void Sale::display(std::ostream& os) const{
    double total = 0;
    os << "Product No      Cost Taxable" << '\n';
    for(auto i : productList){
      os << *i;
      total = total + i->getCharge();
    }
    os << std::setw(10) << "Total";
    os << std::setw(10) << total << "\n";
  }
}

