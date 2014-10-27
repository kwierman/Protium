#ifndef Protium_RootThread_hh_
#define Protium_RootThread_hh_

namespace Protium{
	namespace Threads{

		class RootThread{
		private:
			static RootThread* fThread;

			RootThread() {
				atexit(&FinishThreads);
			}                                  // Private constructor
			~RootThread() {}
			RootThread(const RootThread&);                 // Prevent copy-construction
			RootThread& operator=(const RootThread&);      // Prevent assignment
		public:
			RootThread* Instance(){
				static RootThread thread;
				return thread;
			}

			static FinishThreads(){
				delete fThread;
				fThread = NULL;
			}
		};
	}
}

#endif //File Guardian
