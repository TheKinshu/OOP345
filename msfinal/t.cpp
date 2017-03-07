#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "util.h"
#include "t.h"	
Task::Task(std::vector<std::string> fields) :slots("1"){
	switch (fields.size()){
	case 4:
		if (validName(fields[3]))
				reject = fields[3];
		else{
			throw std::string("expected a name, found a ") + fields[3];
		}
	case 3:
		if (validName(fields[2]))
			accept = fields[2];
		else
			throw std::string("expected a name, found a ") + fields[2];
	case 2:
		if (validSlots(fields[1]))
			slots = fields[1];
		else
			throw std::string("expected a name, found a ") + fields[1];
	case 1:
		if (validName(fields[0]))
			name = fields[0];
		else
			throw std::string("expected a name, found a ") + fields[0];
		break;
	default:
		throw std::string("expected 1, 2, 3, or 4 fields, found ") + to_string(fields.size());
	}
}
void Task::print(){
		std::cout << "name,slots,accept,reject="
				  << name << ","
				  << slots << ","
				  << accept << ","
				  << reject
				  <<"\n";
}
void Task::graph(std::ofstream& os){
	auto f = [&os] (std::string symbol) {os << '"' << symbol << '"';};
	if(not accept.empty()){
		//os << '"' << name << '"' << "->" << '"' << accept << '"' << "[color=green];\n";
		f(name); os << "->"; f(accept); os << "[color=green];\n";
	}
	if(not reject.empty()){
		f(name); os << "->"; f(reject); os << "[color=red];\n";
		//os << '"' << name << '"' << "->" << '"' << reject << '"' << "[color=red];\n";
	}
	if(accept.empty() and reject.empty()){
		//os << '"' << name << '"' << ";\n";
		f(name); os << ";\n";
	}
	os << "\n";
}


TaskManager::TaskManager(vector<vector<string>>& csvdata){
	int line = 1;
	for(auto fields : csvdata){
		try{
			line++;
			TaskList.push_back(Task(fields));
		}catch(std::string& e){
			std::cerr << "Problem with line" << line << ":\n";
			std::cerr << e << "\n";
		}
	}
}
void TaskManager::print(){
	for(auto t : TaskList){
		t.print();
	}
}
void TaskManager::graph(std::string filename){
	std::ofstream of(filename + ".gv");
	if(of.is_open()){
		of << "digraph myGraph {\n";
		for(auto t : TaskList){
			t.graph(of);
		}
		of << "}\n";
		of.close();
	}
	std::string cmd = "dot -Tpng " + filename + ".gv > " + filename + ".gv.png";
	std::cout << cmd  << "\n";
	system(cmd.c_str());
}

int TaskManager::validate(){
	int errors = 0;
	
	for(int i = 0; i < TaskList.size(); i++){
		string s = TaskList[i].getAccept();
		if(!s.empty()){
			if(!find(s)){
				std::cerr << "Cannot find accept task" << s << "\n";
				errors++;
			}
		}
		
		s = TaskList[i].getReject();
		if(!s.empty()){
			if(!find(s)){
				std::cerr << "Cannot find reject task" << s << "\n";
				errors++;
			}
		}
	}
 return errors;
}

Task* TaskManager::find(std::string nameKey){
	for(int i = 0; i < TaskList.size(); i++){
		if(TaskList[i].getName() == nameKey)
			return &TaskList[i];
	}
	return nullptr;
}