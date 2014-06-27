#ifndef Protium_SignalCatching_h_
#define Protium_SignalCatching_h_ 

//---------------------------------------------------------------------

//---------------------------------------------------------------------

namespace Protium{

	namespace Utilities{

		void signal_callback_handler(int signum);
		static inline void print_stacktrace(unsigned int stack_depth = 100);


		class SignalCatcher{
		public:
			static SignalCatcher& GetInstance();
			static void Handle(int signum);
			static void AddHandle(int signum, const FunctorType& handle);

		protected:
			std::map<int, FunctorType> fSignalCatchers;
			static SignalCatcher* instance;
		private:
			SignalCatcher();
			SignalCatcher(const SignalCatcher& other){}
			const SignalCatcher& operator=(const SignalCatcher other);
			virtual ~SignalCatcher(){}

		};

	}
}



#endif //Protium_SignalCatching_h_

