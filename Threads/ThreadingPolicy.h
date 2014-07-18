#ifndef Protium_ThreadingPolicy_h_
#define Protium_ThreadingPolicy_h_

#include "Protium/Threads/Mutex.h"

namespace Protium{

	namespace Threads{

		template<class Host>
		class ThreadingPrototype{
		public:
			typedef Host VolatileType;
		};

		template<class Host, class MutexPolicy=Mutex>
		class InSingleThread : public ThreadingPrototype<Host> {
		public:
			class Lock{
			public:
				Lock(){}
				explicit Lock(const InSingleThread& ){}
				explicit Lock(const InSingleThread* ){}
			};
		};

		template<class Host, class MutexPolicy=Mutex>
		class InstanceLocked : public ThreadingPrototype<Host>{
			mutable MutexPolicy fMtx;
		public:
	        InstanceLocked() : fMtx() {}
    	    InstanceLocked(const InstanceLocked&) : fMtx() {}
        	~InstanceLocked() {}

        	class Lock;
        	friend class Lock;

	        class Lock{
	        	const InstanceLocked& fHost;
	        	Lock(){}
	        	Lock(const Lock&){}

	        	Lock& operator=(const Lock&){}
	        public:
	            explicit Lock(const InstanceLocked& host) : fHost(host){
	                fHost.fMtx.Lock();
	            }

	            explicit Lock(const InstanceLocked* host) : fHost(*host){
	                fHost.fMtx.Lock();
	            }

	            ~Lock(){
	                fHost.fMtx.Unlock();
	            }
	        };

		};

		template<class Host, class MutexPolicy=Mutex>
		class StaticLocked : public ThreadingPrototype<Host>{

	        static struct Initializer{
	            bool fIsInit;
	            MutexPolicy fMtx;

	            Initializer() : fIsInit(false), fMtx()
	            {
	                fIsInit = true;
	            }

	            ~Initializer()
	            {
	                assert(fIsInit);
	            }
	        } fInitializer;

	    public:
	    	class Lock;
        	friend class Lock;

        	class Lock{
	        public:

    	        Lock()
        	    {
            	    assert(fInitializer.fIsInit);
                	fInitializer.fMtx.Lock();
            	}

            	/// Lock class
            	explicit Lock(const StaticLocked&){
                	assert(fInitializer.fIsInit);
                	fInitializer.fMtx.Lock();
            	}

            /// Lock class
            explicit Lock(const StaticLocked*)
            {
                assert(fInitializer.fIsInit);
                fInitializer.fMtx.Lock();
            }

            /// Unlock class
            ~Lock()
            {
                assert(fInitializer.fIsInit);
                fInitializer.fMtx.Unlock();
            }

        private:
            Lock(const Lock&);
            Lock& operator=(const Lock&);
        };


		};

		template < class Host, class MutexPolicy >
    	typename StaticLocked< Host, MutexPolicy >::Initializer
    	StaticLocked< Host, MutexPolicy >::fInitializer;
	}

}

#endif //File Guardian