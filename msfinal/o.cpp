#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "util.h"
#include "o.h"

order::order(std::vector<std::string> fields){
	//std::cout << "size="<<fields.size() << " /";
	//for(auto e: fields) std::cout <<fields.size() << " /";
	//std::cout <<"\n";
	if(fields.size()  < 2)
		throw std::string("expected 2 or more fields, found ") + std::to_string(fields.size());
	if(isCustomerName(fields[0]))
		customer = fields[0];
	else
		throw std::string("expected a customer name, found ") + fields[0];
	if(isOrderName(fields[1]))
		product = fields[1];
	else
		throw std::string("expected a  product, found ") + fields[2];

	for(int i = 2; i < fields.size(); i++){
		if(isItemName(fields[i]))
			itemList.push_back(fields[i]);
		else
			throw std::string("expected an Order name, found ") + fields[i];
	}
}
void order::print(){
		std::cout << "customer name="<< customer 
                   << " product="<< product
                   << " Orders= ";

		for(auto e : itemList)
			std::cout << "<<" << e << ">>";
		std::cout << "\n";
}
void order::graph(std::ofstream& os){
	auto f = [&os] (std::string symbol) {os << '"' << symbol << '"';};
	for(auto e: itemList){
		f(customer); 
    os << "->"; 
    f(e); 
    os << "[color=blue];\n";
	}
}

orderManager::orderManager(std::vector<std::vector<std::string>>& csvdata){
int line = 1;
		for(auto fields : csvdata){
			try{
				line++;
				OrderList.push_back(order(fields));
			}catch(std::string& e){
				std::cerr << "Problem with line" << line << ":\n";
				std::cerr << e << "\n";
			}
		}
}
void orderManager::print(){
	for(auto t : OrderList){
		t.print();
	}
}
void orderManager::graph(std::string filename){
	std::ofstream of(filename + ".gv");
	if(of.is_open()){
		of << "digraph myGraph {\n";
		for(auto t : OrderList){
			t.graph(of);
		}
		of << "}\n";
		of.close();
	}
	std::string cmd = "dot -Tpng " + filename + ".gv > " + filename + ".gv.png";
	std::cout << cmd  << "\n";
	system(cmd.c_str());
}

//g++ -std=c++11 csvdump.cpp util.cpp -o csvdump
//dot -Tpng OrderList.dat.gv > OrderList.data.gv.png