#ifndef Protium_ThreadingPolicy_h_
#define Protium_ThreadingPolicy_h_

#include "Protium/Threads/Mutex.h"

namespace Protium{

	namespace Threads{

		//! Prototype of threading policy
		/**
			Use in order to specify threading policy for a class
			For instance:
			~~~~~~~~~~~~~~~~~~~~~
			template< template<class,class>class threadPolicy = SomeThreadPolicy<MyClass,Mutex> >
			class MyClass {
				typedef MyClass<threadPolicy> localClass;
				typedef SomeThreadPolicy< localClass, Mutex > ThreadModel;
				void SomeFunction(){
	     	    	typename ThreadModel::Lock lock;
        			(void)lock; // get rid of warning
        			//Do Something thread-safe here
				}
			};
			~~~~~~~~~~~~~~~~~~~~~
			
			Now, you can specify what kind of threaded object you want to use

			~~~~~~~~~~~~~~~~~~~~~
			typedef MyClass<InSingleThread<MyClass, Mutex> > MyThreadedClass;
			~~~~~~~~~~~~~~~~~~~~~

			Is you specifically want something to be instance locked, then it has to inherit from the threading policy.

			Like so:
			~~~~~~~~~~~~~~~~~~~~~
			template< template<class,class>class threadPolicy = InstanceLocked<MyClass,Mutex> >
			class MyClass : InstanceLocked<MyClass, Mutex> {
				typedef MyClass<threadPolicy> localClass;
				typedef SomeThreadPolicy< localClass, Mutex > ThreadModel;
				void SomeFunction(){
	     	    	typename ThreadModel::Lock lock(*this);
        			(void)lock; // get rid of warning
        			//Do Something thread-safe here
				}
			};
			~~~~~~~~~~~~~~~~~~~~~


		**/
		template<class Host>
		class ThreadingPrototype{
		public:
			typedef Host VolatileType;
		};

		//! Use to specify non-thread safe classes
		template<class Host, class MutexPolicy=Mutex>
		class InSingleThread : public ThreadingPrototype<Host> {
		public:
			//! Dummy internal class which locks nothing
			class Lock{
			public:
				Lock(){}
				explicit Lock(const InSingleThread& ){}
				explicit Lock(const InSingleThread* ){}
			};
		};

		//! Use to specify instance-locked items
		template<class Host, class MutexPolicy=Mutex>
		class InstanceLocked : public ThreadingPrototype<Host>{
			mutable MutexPolicy fMtx;
		public:
	        InstanceLocked() : fMtx() {}
    	    InstanceLocked(const InstanceLocked&) : fMtx() {}
        	~InstanceLocked() {}

        	//! Internal class which locks the host whenever invoked
        	class Lock;

        	//! Lock is friended to the host
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

		//! Use to specify objects which lock by class
		/**
			For instance, to prevent bad file read-writes, all streams should lock simultaniously by double-lock single check.
		**/
		template<class Host, class MutexPolicy=Mutex>
		class StaticLocked : public ThreadingPrototype<Host>{

			//! Flag-variable class which is used to statically store a mutex.
	        static struct Initializer{
	        	
	        	//! Flag variable to be used in case lock is instantiated mid-initialization
	            bool fIsInit;

	            //! Static mutex for all instances
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
	    	//! Internal class which 
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