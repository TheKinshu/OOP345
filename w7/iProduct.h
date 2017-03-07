 #ifndef _I_PRODUCT_H_
 #define _I_PRODUCT_H_

 // Workshop 7 - STL Containers
 // iProduct.h

 #include <iostream>
 #include <fstream>
 #include <iomanip>
 
 namespace w7 {

     class iProduct {
       public:
         virtual double getCharge() const = 0;
         virtual void display(std::ostream&) const = 0;
     };
     class Product : public iProduct{
       int prodID;
       double cost;
       public:
         Product(int,double);
         double getCharge() const;
         void display(std::ostream&) const;
     };
     class TaxableProduct : public iProduct{
       int prodID;
       double cost;
       char tax;
       public:
         TaxableProduct(int,double,const char);
         double getCharge() const;
         void display(std::ostream&) const;
     };
     std::ostream& operator<<(std::ostream&, const iProduct&); 
     iProduct* readProduct(std::ifstream&);

 }
 #endif