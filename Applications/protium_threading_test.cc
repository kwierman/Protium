
#include "Protium/Threads/Thread.hh"

#include <iostream>

#include "Protium/Utilities/SignalCatching.hh"


class TerminatorThread : public Protium::Threads::Thread{
	unsigned thisPar;
	unsigned otherpar;
public:
	TerminatorThread(unsigned which, unsigned other){
		thisPar=which;
		otherpar=other;
	}
	virtual void start(){
		sleep_for(1);
		for(int i=0; i<3;i++){
			std::cout<<"Now in thread: "<<this->thisThreadID()<<std::endl;	
		}
		std::cout<<"The Thread parameter is: "<<thisPar<<","<<otherpar<<std::endl;
	}
};


class ChildThread : public Protium::Threads::Thread{
	unsigned whichOne;
public:
	ChildThread(unsigned something){
		whichOne=something;
	}

	virtual void start(){
		sleep_for(1);
		std::cout<<"Now in thread: "<<this->thisThreadID()<<std::endl;
		std::cout<<"The initial parameter was: "<<whichOne<<std::endl;
		TerminatorThread thread1(whichOne,1);
		TerminatorThread thread2(whichOne,2);
		TerminatorThread thread3(whichOne,3);

		thread1.Create();
		thread2.Create();
		thread3.Create();

		thread1.Join();
		thread2.Join();
		thread3.Join();
	}
};


int main(int argc, char* argv[]){

	Protium::Utilities::SignalCatcher::Instance().Setup();

	std::cout<<"Now testing threads:..."<<std::endl;

	//create 3 child threads, and 
	ChildThread child1(1);
	ChildThread child2(2);
	ChildThread child3(3);

	std::cout<<"Now Starting Threads::..."<<std::endl;
	child1.Create();
	child1.sleep_for(5);
	child2.Create();
	child2.sleep_for(5);
	child3.Create();
	child3.sleep_for(5);

	child1.Join();
	child2.Join();
	child3.Join();
}