#pragma once
#include "j.h"
#include "t.h"
#include "i.h"
#include <queue>
class Machine: public Task{
	bool bInstaller;
	bool bRemover;
	bool bSink;//sink is where stuff are all done, nothing to do, exit system
	bool bSource;//true if this machine is a source
	std::queue<Job> inputQ;
	//Job job;
public:
	Machine(Task& tt, ItemManager& im);
	void push(Job&& j);
	bool empty(){return inputQ.empty();}
	void print(std::ostream& os);
	void Classify(ItemManager& im);
	bool getBSink(){return bSink;}
	bool getBSource(){return bSource;}
	void setBSource(bool v){bSource = v;}
	void run(ItemManager& im, std::vector<Machine>& machineList);
};