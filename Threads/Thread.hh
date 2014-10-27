#ifndef Protium_Thread_hh_
#define Protium_Thread_hh_

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

			MyThreadedTask mytask;
			//Start the thread

			myTask.Create();

			~~~~~~~~
		**/

		namespace Private{
			//Use this to call up the thread via the owning object, which should 
			void threadingFunction(AbstractThreadThread* thread){
				thread->start();
			}
		}

		/**
			\class Abstract Thread

			\When starting a new thread, this class is meant to be 

		**/
		class Thread : {
			typedef typename InstanceLocked<Thread, Mutex>::Lock lock;
			//now, in each method that needs to be locked, you need to use lock l(this);
			//followed by (void)l;

		private:
			//! Holds the thread in question
			pthread_t thread;
			//! Holds the thread attributes
			pthread_attr_* attr;

			//! Represents a thread status
			enum Status{
				idle, running, exited, killed;
			}

			//! Holds this thread status
			Status stat;

			//The children of this node
			std::vector<Thread> fChildren;
			typedef std::vector<Thread>::iterator ThreadIt;
			const Thread* fParent;//Points to the parent node. Does not own
			//now for the root thread
			class RootThread: Thread{
				pid_t fThreadID;
				RootThread() : Thread(NULL){
					atexit(&FinishThreads);
					fThreadID = thisThread();
				}
				~RootThread(){

				}
				void FinishThreads(){
					delete fRoot;
					fRoot=null;
				}
			};
			static RootThread* fRoot;

			static Thread GetRootThread(){
				//Since the root thread will always be instantiated in the main thread, we can assume the 

				if(!fRoot)
					fRoot = new RootThread();
				return fRoot;
			}


			//this
			Thread(const Thread* parent) : stat(idle), fParent(parent){
				Init();
			}

			virtual ~Thread(){
				Kill();
				for(ThreadIt it = fChildren.begin(); it!= fChildren.end(); ++it){
					this->Join(*it);
				}
			}

		public:
			//! Starts this thread from the parent thread. Needs to be overriden for root thread
			virtual void Create(){
				pthread_create (thread,attr,threadingFunction,this);				
			}

		protected:

			//! Calls exit on the current thread
			void Exit(){
				pthread_exit (*stat);
			}

		public:

			//! Calls cancel on this thread from another thread
			void Cancel(){
				pthread_cancel (thread);				
			}

		private:

			//! Initiates this thread's attributes
			void Init(){
				pthread_attr_init (attr);				
			}
			//! De-initializes this thread's attributes. Should only be called in conjunction with Init();
			void Kill(){
				pthread_attr_destroy(attr);
			}
		public:

			//Override this for a threading routine
			void start() =0;

			//Call this to join with the child thread. Blocks calling thread until the child thread joins.
			//void Join(){
				//pthread_join(thread[t], &status);
			//}

			pid_t thisThread(){
				return pthread_self();
			}

			bool equal(pid_t& other){
				return  (this->pid, other);
			}

			void sleep_for(unsigned time){
				sleep(time);
			}

			const ThreadNode* getParent(){
				return fParent;
			}

			template<class T>
			const T* Create(){
				T* temp = new T();
				this->fChildren.push_back(*temp);
				return temp;
			}
			//create is used to get the thread for the parent object to hold onto, now for the wierd part
			template<class T=Thread>
			const T* Get(pid_t id){
				return NULL;
			}

			void Kill(pid_t id){
				for(ThreadIt it = fChildren.begin(); it!= fChildren.end(); ++it){
						this->Join(*it);
					}
			}



			//pthread_attr_getstacksize (attr, stacksize)

			//pthread_attr_setstacksize (attr, stacksize)

			//pthread_attr_getstackaddr (attr, stackaddr)

			//pthread_attr_setstackaddr (attr, stackaddr) 
			//void setstacksize(){
				//pthread_attr_setstacksize(/*It's over NINE THOUSAND!!!*/);
			//}
		};



	}
}



#endif  //File Guardian

