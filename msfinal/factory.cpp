#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "util.h"
#include "i.h"
#include "o.h"
#include "t.h"
#include "m.h"

class factory{
	ItemManager  im;
	orderManager om;
	TaskManager  tm;
	vector<Machine> ml;
public:
	factory(ItemManager &&imArg, orderManager &&omArg, TaskManager &&tmArg)
	  : im(move(imArg)), om(move(omArg)), tm(move(tmArg))
	{
		/*
			Step 1: Create a factory of machines
		*/
		for(size_t t = 0; t < tm.size(); t++){
			ml.push_back(Machine(tm.at(t),im));
		}
		/*
			Step 2: Find source for graph
		*/
		enum{SOURCE_NOT_FOUND = -1};
		int source = SOURCE_NOT_FOUND;
		for(size_t m = 0; m < ml.size(); m++){
			ml[m].setBSource(true);
		}
		for(size_t t = 0; t < tm.size(); t++){
			// flag accept as not source since we are the incoming task for accept
			string s;
			Machine* mPtr;
			auto find = [&] (std::string n) -> Machine* {
				for(size_t m = 0; m < ml.size(); m++) {
					if(ml[m].getName()  == n)
						return &ml[m];
				}
				return nullptr;
			};
			s = tm.at(t).getAccept();
			if(not s.empty()) {
				mPtr = find(s);
				if(mPtr)  // returns a Machine*
					mPtr->setBSource(false);  // set Machine* not source
			}
			s = tm.at(t).getReject();
			if(not s.empty()) {
				mPtr = find(s);
				if(mPtr)  // returns a Machine*
					mPtr->setBSource(false);  // set Machine* not source
			}
		}
		int sourceCount = 0;
		for(size_t m = 0; m < ml.size(); m++){
			if(ml[m].getBSource() && source == SOURCE_NOT_FOUND){
				source = m;
				sourceCount++;
			}
			if(sourceCount > 1){
				throw string("multiple sources, fix task data and re-run.");
			}
			//cout << count << "\n";
		}
		cout << ml[source].getBSink() << "\n";
		cout << "source = " << source << " name = '" << ml[source].getName() << "' slots = '" << ml[source].getSlots() << "' passed = '" << ml[source].getAccept()<<"'\n";
		
		/*
			Step 3: Load job to source machine
		*/
		for(size_t j = 0; j < om.size(); j++)
			ml[source].push( Job( om.getOrder(j) ) );
		
		cout << "Om size = " << om.size() << "\n";
		/*
			Step 4: time loop
		*/
		
		for(int time = 0; true ; time++) {
			cout << "TIME LOOP: time=" << time << "\n";
			/*
				Step 5: if all inputQ's are empty, we are done
			*/
			bool allDone = true;
			for(size_t m = 0; m < ml.size(); m++) {
				if(not ml[m].empty()) {
					cout << "machine " << m << " found job\n";
					allDone = false;
					break;
				}
			}
			if(allDone) break;  // allDone, break out of time loop
			
			cout << "allDone=" << allDone << "\n";
			
			/*
				Step 6: Mchine loop
			*/
			for(size_t m = 0 ; m < ml.size(); m++) {
				ml[m].run(im, ml);
			}
			
			//break; // TODO: JUST TESTING...
		}
			
		cout << "**** ALL DONE --- RUN OVER ****\n";
		
	}
};

int validate(ItemManager &im, orderManager &om, TaskManager &tm){
	int errors = 0;
	//for items
	for(size_t i = 0; i < im.size(); i++){
		string s = im.getInstaller(i);
		if(not tm.find(s)){
			cerr << "Cannot find installer task '" << s <<"'\n";
			errors++;
		}
		s = im.getRemover(i);
		if(not tm.find(s)){
			cerr << "Cannot find remover task '" << s <<"'\n";
			errors++;
		}
	}
	//for order
	for(size_t orderIndex = 0; orderIndex < om.size(); orderIndex++){
		for(size_t itemIndex = 0; itemIndex < om.itemListSize(orderIndex); itemIndex++){
			string s = om.getItem(orderIndex,itemIndex);
			if(not im.find(s)){
				cerr << "Cannot find item task '" << s <<"'\n";
				errors++;
			}
		}
	}
	errors += tm.validate();
	
	if(errors){
    cerr << "+++++++++++++++++++++++++++++++++++\n";
    cerr << "+    Integrity check failed       +\n";
    cerr << "+           NOT GOOD              +\n";
    cerr << "+++++++++++++++++++++++++++++++++++\n";
    cerr << "Not good. " << errors << " errors in data. Please fix and resubmit.\n";
	}else{
		//cout << "Good to no - no errors in data.\n";
    cout << "+++++++++++++++++++++++++++++++++++\n";
    cout << "+    Integrity check passed       +\n";
    cout << "+          GOOD TO GO             +\n";
    cout << "+++++++++++++++++++++++++++++++++++\n";
	}
	return errors;
}

int main(int argc, char*argv[]){
	if (argc != 5){
		cerr << "Usage: " << argv[0] << "item-csv order-csv task-csv separator-char\n";
		return 1;
	}

	string itemfile = argv[1];
	string orderfile = argv[2];
	string taskfile = argv[3];
	char   delimiter = argv[4][0];

	//cout << "The delimeter is '" << delimiter << "'\n";
	try{
		
		vector<vector<string>> itemcsv;
		vector<vector<string>> ordercsv;
		vector<vector<string>> taskcsv;
		
		readcsv(itemfile, delimiter, itemcsv);
		//printcsv(itemcsv);	
		ItemManager im(itemcsv);
		//im.print();
			
		readcsv(orderfile, delimiter, ordercsv);
		//printcsv(ordercsv);	
		orderManager om(ordercsv);
		//om.print();
		
		readcsv(taskfile, delimiter, taskcsv);
		//printcsv(taskcsv);	
		TaskManager tm(taskcsv);
		tm.print();
		
		cout << "+++++++++++++++++++++++++++++++++++\n";
    cout << "+             Item                +\n";
    cout << "+++++++++++++++++++++++++++++++++++\n";
    cout << "# file: " << itemfile << " delimiter -->" << delimiter << "<--\nCommand ";
    im.graph(itemfile);
    cout << "+++++++++++++++++++++++++++++++++++\n";
    cout << "+             Order               +\n";
    cout << "+++++++++++++++++++++++++++++++++++\n";
    cout << "# file: " << orderfile <<" delimiter -->" << delimiter << "<--\nCommand ";
    om.graph(orderfile);
    cout << "+++++++++++++++++++++++++++++++++++\n";
    cout << "+             Task                +\n";
    cout << "+++++++++++++++++++++++++++++++++++\n";
    cout << "# file: "  << taskfile << " delimiter -->" << delimiter << "<--\nCommand ";
    tm.graph(taskfile);
    
	int errors = validate(im,om,tm);
	//throw string("validate returned " + to_string(errors) + " syntax error\n");
	factory f(move(im),move(om),move(tm));
	
	}
	catch (string & e){
		cerr << e << "\n";
	}
	return 0;
}