#include "iProduct.h"
#include <vector>
namespace w7{
  class Sale{
    std::vector<iProduct*> productList;
    public:
      Sale(const char* filename);
      void display(std::ostream& os) const;
  };
}