#ifndef Protium_Function_h_
#define Protium_Function_h_

#include <map>

namespace Protium{

	namespace Collections{

		template<class XType, class YType>
		class FunctionPrototype{
			std::map<XType, YType> fComponents;

			FunctionPrototype(){}
			virtual ~FunctionPrototype(){}

			void Set(const XType& x, const YType& y) = 0;
			YType Eval(const XType& x);
		};//class function prototype

		//statically define as follows


		typedef FunctionPrototype<double, double> Function1D;
		typedef FunctionPrototype< std::pair<double, double>, double > Function2D;


	}//namespace collections
}//namespace protium


#endif //Header Guardian