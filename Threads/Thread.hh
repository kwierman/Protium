#ifndef Protium_Thread_hh_
#define Protium_Thread_hh_

#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <algorithm>

#include "Protium/Design/Unused.hh"

#include "Protium/Threads/ThreadingPolicy.hh"

#include <iostream>//destroy this later

namespace Protium{

	namespace Threads{
		/**
			Threading functions are meant to be created in the following way:

			~~~
			class MyThread : public Thread{
				public:
					void start(){
						//Insert threading functionality here
					}
			};
			~~~

			From the main function, this thread can be called up easily,

			~~~
			MyThread mythread= ...init...;
			mythread.Create();//will spool off the thread
			myThread.Join();//Join with the thread
			myThread.ReInit();//Reset the thread state to get it ready to go again.
			~~~


		**/

		namespace Private{
			void* threadingFunction(void* thread);
		}

		class Thread : public InstanceLocked<Thread, Mutex>{
			pthread_t thread;
			pthread_attr_t attr;			
		protected:
			enum Status{
				idle, //in Pre
				running, //in Run
				exited, //in Post
				killed //Exited bad
			} stat;

			typedef InstanceLocked< Thread, Mutex > ThreadModel;
			typedef typename ThreadModel::Lock lock;

			Thread() : stat(idle) {
				Init();
			}
			~Thread(){
				DeInit();
			}
			void ReInit(){
				DeInit();
				Init();
			}
		public:
			void sleep_for(unsigned time){					
				lock l(this);
				Protium_Unused(l);
				usleep(time);
			}

			static pid_t thisThreadID() {
				return pthread_self();
			}


			virtual void Join(){
				pthread_join(thread, 0);
			}

			virtual void Create(){
				lock l(this);
				Protium_Unused(l);
				this->stat=running;
				pthread_create(&thread,&attr,::Protium::Threads::Private::threadingFunction,this);
			}
			virtual void start(){}
		private:

			//! Initiates this thread's attributes
			void Init(){
				pthread_attr_init (&attr);				
			}
			//! De-initializes this thread's attributes. Should only be called in conjunction with Init();
			void DeInit(){
				pthread_attr_destroy(&attr);
			}


		protected:

			//! Calls exit on the current thread
			void Exit(){
				stat=killed;
				pthread_exit (&stat);
			}

		public:

			//! Calls cancel on this thread from another thread, or this one
			void Cancel(){
				pthread_cancel (thread);				
			}

		};


	}
}



#endif  //File Guardian

