#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "util.h"

//using namespace std;
class order{
	std::string customer, product;
	std::vector <std::string> itemList;
public:
	order(std::vector<std::string> fields);
	void print();
	void graph(std::ofstream& os);
	size_t size(){return itemList.size();}
	std::string& item(size_t itemIndex){ return itemList[itemIndex];}
};

class orderManager{
	std::vector<order> OrderList;
	public:
	orderManager(std::vector<std::vector<std::string>>& csvdata);
	void print();
	void graph(std::string filename);
	size_t size()const{return OrderList.size();}
	size_t itemListSize(size_t orderIndex){return OrderList[orderIndex].size();}
	std::string& getItem(size_t orderIndex, size_t itemIndex){ return OrderList[orderIndex].item(itemIndex);}
	
	order& getOrder(size_t o) { return OrderList[o]; }
};

//g++ -std=c++11 csvdump.cpp util.cpp -o csvdump
//dot -Tpng ItemList.dat.gv > ItemList.data.gv.png