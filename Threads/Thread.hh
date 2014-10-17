#ifndef Protium_Thread_hh_
#define Protium_Thread_hh_

#include <exception>

#include "Protium/Threads/ThreadingPolicy.hh"

namespace Protium{

	namespace Threads{

		/**
			\file Thread.h
			\author Kevin Wierman
			\date \today

			\brief An object-oriented thread class

			To be used as such:

			~~~~~~~~
			class MyThreadedTask : AbstractThread{
				...Some Fields...
			public:
				virtual void start(){
					std::cout<<"In the start method of the thread"<<std::endl;
				}
				...
			};

			//Then later on in code:

			MyThreadedTask* mytask = Thread::GetRootThread()->;
			//Start the thread
			myTask->Run();
			//Check to see if it is joinable
			if( myTask->isJoinable() ){
				//and join
				myTask->Join();
			}

			~~~~~~~~
		**/

		namespace Private{
			//Use this to call up the thread via the owning object, which should 
			void threadingFunction(AbstractThread* thread){
				thread->main();
			}
		}

		class ThreadAlreadyStartedException : std::exception{
			virtual const char* what() const throw(){
				return "Thread Already Started";
			}
		};


		/**
			\class AbstractThread

		**/
		class AbstractThread {
		private:
			//! Contains the pthread object itself
			pthread_t thread;
			//! Contains the thread attributes
			pthread_attr_ attr;
			bool isRunning;
			ThreadAlreadyStartedException threadStarted;


			typedef InstanceLocked< AbstractThread, Mutex > ThreadModel;
			typedef ThreadModel::Lock lock;

			//now for status
			enum Status{
				ready,
				running,
				stoppedNormally,
				cancelled,
				joined;
			};

			Status stat;

		public:

			//! Default constructor
			AbstractThread(): isRunning(false) {
				Init();
			}

			//! Call this method to spin off this thread
			void Run() throw(ThreadAlreadyStartedException){
				if(isRunning)
					throw threadStarted;
				pthread_create (thread,attr,threadingFunction,this);				
			}

		protected:

			//! Call this method to kill the calling thread.
			void Exit(){
				(void)lock;
				stat=cancelled;
				pthread_exit(stat);				
			}

		public:

			//! Request the thread to be canceled. Used from anywhere
			void Cancel(){
				pthread_cancel (thread);
				stat=cancelled;				
			}
		private:

			//! Initializes the thread attributes
			void Init(){
				(void)lock;
				pthread_attr_init (attr);				
			}
			void Uninit(){
				(void)lock;
				pthread_attr_destroy(attr);
			}

			//Override this for a threading routine
			void main() =0;
			//TODO: Add in joining
			void Join(){
				//TODO: hand in the thread of the 
				 pthread_join(thread, &status);
			}

			//To be used for retreiving back this thread
			pid_t thisThread(){
				return pthread_self();
			}

			//Check to see if this thread isequal to another
			bool equal(pid_t& other){
				return  (this->pid, other);
			}

			size_t GetStackSize(){
				size_t s;
				pthread_attr_getstacksize(this->attr, s);
				return s;
			}
			void SetStackSize(size_t s){
				pthread_attr_setstacksize(this->attr, s);
			}


			//pthread_attr_getstackaddr (attr, stackaddr)

			//pthread_attr_setstackaddr (attr, stackaddr) 
		};

		//TODO: Add in the parent singleton which will be used to spawn the threads from the parent thread.
		//TODO; THe Parent singleton needs to finish last with pthread_exit(null); as an one of it's parameters.
	}
}



#endif  //File Guardian

