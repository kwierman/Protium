#ifndef Protium_Threads_h_
#define Protium_Threads_h_

namespace Protium{

	namespace Threads{

		/*! \class ThreadOwner
			\brief A policy class to be used for object wishing to create their own threads and interact between threads

		 */
		class ThreadOwner{
		public:
			bool CreateNewThread();
			bool IsRunningAsSeparateThread();
			bool ThreadExit();
			bool CancelThread();
			template<typename XType>
			void SetThreadAttributes();
		};

		/*
		pthread_create (thread,attr,start_routine,arg)

		pthread_exit (status)

		pthread_cancel (thread)

		pthread_attr_init (attr)

		pthread_attr_destroy (attr) 
		*/


		class JoinableThreadOwner : public ThreadOwner{

		};

		class DetacheableThreadOwner : public ThreadOwner{

		};




	}
}


#endif //Protium_Threads_h_