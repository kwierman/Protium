#ifndef Protium_Thread_h_
#define Protium_Thread_h_


namespace Protium{

	namespace Threads{

		//Use this to call up the thread, the owning object will then
		void threadingFunction(AbstractThread* thread){
			thread->start();
		}

		/**
			\class Abstract Thread

			\When starting a new thread, this class is meant to be 

		**/
		class AbstractThread{
			pthread_t thread;
			//Add this to 

			void Create(){
				pthread_create (thread,attr,threadingFunction,this);				
			}
			void Exit(){
				pthread_exit (status);				
			}
			void Cancel(){
				pthread_cancel (thread);				
			}
			void Init(){
				pthread_attr_init (attr);				
			}
			void Kill(){
				pthread_attr_destroy(attr);
			}

			//Override this for a threading routine
			void start() =0;
			//TODO: Add in joining
			void join(){
				 pthread_join(thread[t], &status);
			}

			pid_t thisThread(){
				return pthread_self();
			}

			bool equal(pid_t& other){
				return  (this->pid, other);
			}


pthread_attr_getstacksize (attr, stacksize)

pthread_attr_setstacksize (attr, stacksize)

pthread_attr_getstackaddr (attr, stackaddr)

pthread_attr_setstackaddr (attr, stackaddr) 
			void setstacksize(){
				pthread_attr_setstacksize(/*It's over NINE THOUSAND!!!*/);
			}
		};

		//TODO: Add in the parent singleton which will be used to spawn the threads from the parent thread.
		//TODO; THe Parent singleton needs to finish last with pthread_exit(null); as an one of it's parameters.
	}
}



#endif  //File Guardian

