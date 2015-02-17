#ifndef Protium_Daemon_hh_
#define Protium_Daemon_hh_

#include <>

namespace Protium{
	namespace Threads{

		/** To be instantiated whenever
		**/
		class Daemon{
		private:
			pid_t pid;
			pid_t sid;
		public:
			Daemon(){

			}
			void Fork(){
				pid=fork();

				if(!(pid!=-1) && (pid!=0) )
					exit(EXIT_FAILURE);
				if(pid!=0)//The parent process goes here
					exit(EXIT_SUCCESS);

				if( chdir("/")<0)
					exit(EXIT_FAILURE);
				umask(0);
				sid=setsid();
				if(sid<0)
					exit(EXIT_FAILURE);

				close(STDIN_FILENO);
		        close(STDOUT_FILENO);
        		close(STDERR_FILENO);
			}
			~Daemon(){
				exit(EXIT_SUCCESS);
			}

			void setFileMask(){
				umask(0);
			}
		};
	}
}


#endif //File Guardian