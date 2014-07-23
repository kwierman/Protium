#ifndef Protium_Histogram_h_
#define Protium_Histogram_h_

#include <map>

namespace Protium{

	namespace Containers{


		struct Bin{
			double fLowerEdge;
			double fWidth;
		};




		//the idea is that the 
		template<class Xtype, typename YType >
		class HistogramBase{
			std::map<Xtype, YType> fComponents;
		};


		class Histogram{
		public:
			XType GetBinLowerEdgeByI(const int& i);
			XType GetBinLowerEdgeByPos( const XType& i);

			XType GetBinHigherEdgeByI(const int& i);
			XType GetBinHigherEdgeByPos( const XType& i);

			XType GetBinWidthByI(const int& i);
			XType GetBinWidthByPos( const XType& i);

			YType GetBinQuantityByI(const int& i);
			YType GetBinQuantityByPos( const XType& i);
		};
	}
}


#endif //Protium_Histogram_h_