#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "i.h"
#include "util.h"

//using namespace std;

Item::Item(std::vector<std::string> fields){
	switch (fields.size()){
	case 5:
		description = fields[4];
	case 4:
		if (isCode(fields[3]))
			code = fields[3];
		else{
			throw std::string("expected a numerical code, found a ") + fields[3];
		}
	case 3:
		if (isItemName(fields[2]))
			remover = fields[2];
		else
			throw std::string("expected a remover task, found a ") + fields[2];
	case 2:
		if (isItemName(fields[1]))
			installer = fields[1];
		else
			throw std::string("expected a installer task, found a ") + fields[1];
	case 1:
		if (isItemName(fields[0]))
			name = fields[0];
		else
			throw std::string("expected a item, found ") + fields[0];
		break;
	default:
		throw std::string("expected 4 or 5 fields, found ") + std::to_string(fields.size());
	}
}
void Item::print(){
		std::cout << "name,installer,remover,code [description] = /"
				  << name << "/"
				  << installer << "/"
				  << remover << "/"
				  << code;
				  if(not description.empty())
					  std::cout << "/" << description;
				  std::cout <<"\n";
}
void Item::graph(std::ofstream& os){
	auto f = [&os] (std::string symbol) {os << '"' << symbol << '"';};
	f(std::string("Item: ") + name); os << "->"; f(installer); os << "[color=green];\n";
	f(std::string("Item: ") + name); os << "->"; f(remover); os << "[color=red];\n";
}


ItemManager::ItemManager(std::vector<std::vector<std::string>>& csvdata){
	int line = 1;
	for(auto fields : csvdata){
		try{
			line++;
			ItemList.push_back(Item(fields));
		}catch(std::string& e){
			std::cerr << "Problem with line" << line << ":\n";
			std::cerr << e << "\n";
		}
	}
}
void ItemManager::print(){
	for(auto t : ItemList){
		t.print();
	}
}
void ItemManager::graph(std::string filename){
	std::ofstream of(filename + ".gv");
	if(of.is_open()){
		of << "digraph myGraph {\n";
		for(auto t : ItemList){
			t.graph(of);
		}
		of << "}\n";
		of.close();
	}
	std::string cmd = "dot -Tpng " + filename + ".gv > " + filename + ".gv.png";
	std::cout << cmd  << "\n";
	system(cmd.c_str());
}
Item* ItemManager::find(std::string itemKey){
	for(int i = 0; i < ItemList.size(); i++){
		if(ItemList[i].getName() == itemKey)
			return &ItemList[i];
	}
	return nullptr;
}
//g++ -std=c++11 csvdump.cpp util.cpp -o csvdump
//dot -Tpng ItemList.dat.gv > ItemList.data.gv.png