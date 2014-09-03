#ifndef Protium_FunctionMapped_h_
#define Protium_FunctionMapped_h_

#include <map>
#include <string>
#include <cstdlib>


namespace Protium{
	namespace Design{
		class FunctionMappedPrototype{
			virtual ~FunctionMappedPrototype(){}
			virtual void Set(const std::string& key, const std::string& value )=0;
		};

		template<class Derived>
		class FunctionMapped : public FunctionMappedPrototype{
			typedef void (Derived::*d_func)(double);
			typedef std::map<std::string, d_func> func_map;
			func_map d_config;

			void AddValueToMap(const std::string& value, d_func f){
				d_config.insert(std::make_pair(value,f));
			}
			void Set(const std::string& value, const std::string& value){
				double newValue = std::atof(value.c_str() );
				d_func call = d_config[key];
				if(!call) return;
				Derived* d = dynamic_cast<Derived*>(this);
				(d->*call)(newValue);
			}
		};
	}
}


#endif //File Guardian
