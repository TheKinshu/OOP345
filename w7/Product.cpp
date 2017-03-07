#include "iProduct.h"

namespace w7{
  Product::Product(int id, double price){
    prodID = id;
    cost = price;
  }
  double Product::getCharge() const{
    return cost;
  }
  void Product::display(std::ostream& os) const{
    os << prodID;
    os << cost << '\n';
  }
  TaxableProduct::TaxableProduct(int ID_,double cost_,const char tax_){
    prodID = ID_;
    cost = cost_;
    tax = tax_;
  }
  double TaxableProduct::getCharge() const{
    if(tax == 'H'){
      return cost*1.13;
    }
    else if(tax == 'P'){
      return cost*1.08;
    }
    else{
      return cost;
    }
  }
  void TaxableProduct::display(std::ostream& os) const{
      os << std::fixed << std::setprecision(2);
      os << std::setw(10) << prodID;
      os << std::setw(10) << cost << ' ';
      if(tax == 'H'){
        os << "HST\n";
      }
      else if(tax == 'P'){
        os << "PST\n";
      }
      else{
        os << "\n";
      }
  }
  std::ostream& operator<<(std::ostream& os, const iProduct& product) {
    product.display(os);
    return os;
  }
  iProduct* readProduct(std::ifstream& is) {
    int id_;
    double cost_;
    char tax_;
    iProduct* tempProduct;
    is >> id_;
    is >> cost_;
    if(is.get() == '\n'){
      tempProduct = new Product(id_, cost_);
    }
    else{
      is.get(tax_);
      tempProduct = new TaxableProduct(id_, cost_, tax_);
    }
    return tempProduct;
  }
}