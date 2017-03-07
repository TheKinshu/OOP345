#include "m.h"
Machine::Machine(Task& tt, ItemManager& im) 
: Task(tt),bInstaller(false),bRemover(false),bSink(false){
	Classify(im);
}

void Machine::push(Job&& j){
	inputQ.push(move(j));
}
void Machine::print(std::ostream& os){
	os << "Machine name is " << getName();
	if(bInstaller) os <<"<-- installer";
	if(bRemover) os <<"<-- Remover";
	if(bSink) os <<"<-- sink";
	if(!bInstaller && !bRemover) os << "<-- neither Install nor Remove";
}
void Machine::Classify(ItemManager& im){
	bSink = getAccept().empty() && getReject().empty();
	string name = getName();
	for(size_t i = 0; i < im.size(); i++) {
		if(im.getInstaller(i) == name) bInstaller = true;
		if(im.getRemover(i)   == name) bRemover   = true;
	}	
}
void Machine::run(ItemManager& im, std::vector<Machine>& machineList){
	
	if(inputQ.empty()){
		cout << getName() << " inputQ is Empty \n";
		return;
	}
	cout << getName() << " inputQ is not Empty \n";
	
	Job job = move(inputQ.front());
	inputQ.pop();
	
	job.print();
	
	cout << "bSink =" << bSink << "\n";
   /*
     Step 7: check if it sink
   */
	if(bSink){
		if(job.isComplete()){
			
		}
		else{
			throw std::string("Job at sink node " + getName());
		}
	}
	auto route = [&machineList,this] (Job& job, string destination){
		for(auto m = machineList.begin(); m < machineList.end(); m++){
			if(m->getName() == destination){
				m->push(move(job));
				cout << "route moving job from " << getName() << " to " << destination << "\n";
				break;
			}
		}
	};
	
	bool didSomething = false;
	//cout << getAccept();
	cout << "bInstaller =" << bInstaller << "\n";
	if(bInstaller){
		//check if there something empty
		//if not install
		for(size_t i = 0; i < job.size(); i++){
			if(job.isInstalled(i))
				continue;
			string itemName = job.item(i);
			Item* itemPtr = im.find(itemName);
			if(itemPtr && itemPtr->getInstaller() == getName()){
				job.Install(i);
				didSomething = true;
			}
			else
				cout << "item " << itemName << " needs install " << itemPtr->getInstaller() << "\n";
		}
	}
	
	cout << "bRemover =" << bRemover << "\n";
	if(bRemover){
		//check if something is install
		//if install remove
		for(size_t i = 0; i < job.size(); i++){
			if(job.isInstalled(i))
				continue;
			string itemName = job.item(i);
			Item* itemPtr = im.find(itemName);
			if(itemPtr && itemPtr->getInstaller() == getName()){
				job.Remove(i);
				didSomething = true;
			}
			else
				cout << "item " << itemName << " needs remove " << itemPtr->getRemover() << "\n";
		}
	}
 
	string passed = getAccept();
	
	if(!didSomething){
		route(job, passed);
		return;
	}
	
	string failed = getReject();
	
	if(failed.empty()){
	   route(job,passed);
	   return;
	}
	
	if(rand() % 2){
		route(job,passed);
		return;
	}
	else{
		route(job,failed);
		return;
	}

}