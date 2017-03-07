#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "util.h"
using namespace std;

class Task{
	string name, slots, reject, accept;
	///bool validSlots(std::string slot);
public:
	Task(std::vector<std::string> fields);
	void print();
	void graph(std::ofstream& os);
	string& getName(){return name;}
  string& getSlots(){return slots;}
	string& getAccept(){return accept;}
	string& getReject(){return reject;}
};

class TaskManager{
	std::vector<Task> TaskList;
	public:
	TaskManager(vector<vector<string>>& csvdata);
	void print();
	void graph(std::string filename);
	int validate();
	size_t size(){return TaskList.size();}
	Task& at(size_t i){return TaskList.at(i);}
	Task* find(std::string nameKey);
};
