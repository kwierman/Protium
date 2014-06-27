#ifndef Protium_Histogram_h_
#define Protium_Histogram_h_

namespace Protium

	namespace Collections{

		template<class XType, typename YType>
		class HistogramBase






		//the idea is that the 
		template<class Xtype, typename YType >
		class HistogramBase{
			std::map<Xtype, YType>
		};

		typedef Histogram< ,HistogramContent<double> > Histogram1D;
		typedef Histogram< , > Histogram2D;

		//Concrete Example
		template<typename T, int dimensions=1>
		class Histogram : HistogramPrototype{
			struct binContent{
				T content_;
				std::vector<T> bin_;
			};

			std::vector<binContent> bins_;

		public:

			//Step 1: Construction:
			Histogram(){}
			virtual ~Histogram(){};

			int GetNBins() const {return bins.size(); }
			int GetDimensions() const {return dimensions;}
			T& GetBinContent(const int& bin) const;
			void SetBinContent(const int& bin);
		};
	}
}


#endif //Protium_Histogram_h_