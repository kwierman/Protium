/*! \file protium_thread_tests.cxx

*/

#include "Protium/Threads/Mutex.h"
#include "Protium/Threads/ThreadingPolicy.h"

#include "Protium/Threads/Threads.h"

#include <iostream>


class Printer{
	int fMember;
public:
	Printer(const int& x) : fMember(x) {}
	void Print(){std::cout<<"This is Printer: "<<fMember<<std::endl;}
};


template< template<class, class>class ThreadingPolicy>
class ThreadedObject : public ThreadingPolicy<Printer, Protium::Threads::Mutex>, public Printer {
	typedef typename ThreadingPolicy<Printer, Protium::Threads::Mutex>::Lock lock;

public:
	ThreadedObject(const int& x) : Printer(x) {}
	void Print(){
		lock x(*this);
		Printer::Print();
	}
};

typedef ThreadedObject<Protium::Threads::InSingleThread> Single;
typedef ThreadedObject<Protium::Threads::InstanceLocked> Multi1;
typedef ThreadedObject<Protium::Threads::StaticLocked> Multi2;




int main(int argc, char* argv[]){

	Single x(1);
	x.Print();

	Multi1 y(2);
	y.Print();

	Multi2 z(3);
	z.Print();

}