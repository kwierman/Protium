#ifndef Protium_SignalCatching_h_
#define Protium_SignalCatching_h_ 

//---------------------------------------------------------------------

//---------------------------------------------------------------------

namespace Protium{

	namespace Private{
		void signal_callback_handler(int signum);
		static inline void print_stacktrace(unsigned int stack_depth = 100);

	}


	namespace Utilities{

		//! Default Signal callback handler. This needs to be deleted pronto



		class SignalCatcher{
		public:
			static SignalCatcher& GetInstance(){
				static SignalCatcher instance();
				return;
			}
			static void AddHandle(int signum, const Functor<void>& handle){

				fSignalCatchers.insert(std );

			}

			static void Handle(int signum);


		protected:

			void DefaultSigIntHandler(){}
			void DefaultAbortHandler(){}
			void DefaultSigBusHandler(){}
			void DefaultSigSegFaultHandler(){}

			Functor<void> fSigIntHandle;
			Functor<void> fSigAbortHandle;
			Functor<void> fSigBusHandle;
			Functor<void> fSigSegFaultHandle;

		private:

			SignalCatcher() {
				signal(SIGINT, Protium::Private::signal_callback_handler);
				signal(SIGABRT, Protium::Private::signal_callback_handler);
				signal(SIGBUS , Protium::Private::signal_callback_handler);
				signal(SIGSEGV , Protium::Private::signal_callback_handler);
			}

			SignalCatcher(const SignalCatcher& other){}
			const SignalCatcher& operator=(const SignalCatcher other);
			virtual ~SignalCatcher(){}

		};

	}
}



#endif //Protium_SignalCatching_h_

