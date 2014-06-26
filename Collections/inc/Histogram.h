#ifndef Protium_Histogram_h_
#define Protium_Histogram_h_

namespace Protium{

	namespace Collections{

		
		class HistogramPrototype{
		public:
			//Interface Definition
			HistogramPrototype(){}
			virtual ~HistogramPrototype(){}
			int GetNBins(int axis=0)=0;
		};

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