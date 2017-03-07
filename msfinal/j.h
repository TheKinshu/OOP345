#pragma once

#include "o.h"

class Job : public order{
	std::vector<bool> installed;
public:
	//Job(){}
	Job(order& oo):order(oo){
	for(size_t i = 0; i < size(); i++);
		installed.push_back(false);
	}
	bool isComplete(){
		for(auto e: installed)
			if(not e) return false;
		return true;
	}
	void Install(int i){installed[i] = true;}
	void Remove(int i){installed[i] = false;}
	bool isInstalled(int i){return installed[i];}
};