#ifndef Protium_SignalCatching_hh_
#define Protium_SignalCatching_hh_ 

#include "Protium/Singleton/Singleton.hh"
#include "Protium/Threads/ThreadingPolicy.hh"
#include "Protium/Threads/Mutex.hh"

#include <signal.h>

#include <iostream>

namespace Protium{

	namespace Private{
		void signal_callback_handler(int signum);
		static inline void print_stacktrace(unsigned int stack_depth = 100);

	}

	namespace Utilities{

		class SignalCatchingImplementation{
			protected: 
				SignalCatchingImplementation(){}
				virtual ~SignalCatchingImplementation(){}
			public:
				void Setup(){
					signal(SIGINT, Protium::Private::signal_callback_handler);
					signal(SIGABRT, Protium::Private::signal_callback_handler);
					signal(SIGBUS , Protium::Private::signal_callback_handler);
					signal(SIGSEGV , Protium::Private::signal_callback_handler);
				}
			private:
	    	    SignalCatchingImplementation( const SignalCatchingImplementation & );
	    	    SignalCatchingImplementation & operator = ( const SignalCatchingImplementation & );
		};


		class SignalCatcher: public SignalCatchingImplementation{

	        typedef Protium::Singleton::Singleton< SignalCatcher, Protium::Singleton::CreateStatic,
	            Protium::Singleton::DeleteLast, Protium::Threads::StaticLocked > SignalCatcherSingleton;

	    public:

	        inline static SignalCatcher& Instance(){
	            return SignalCatcherSingleton::Instance();
	        }

	        inline SignalCatcher() : SignalCatchingImplementation() {}
	        inline ~SignalCatcher( void ) {}
		};

	}
}


#endif //Protium_SignalCatching_h_

