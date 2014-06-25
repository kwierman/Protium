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
		template<typename T>
		class Histogram : HistogramPrototype{
			//content
			std::vector<T> bins_;

		public:
			int GetNBins() const;
			T& GetBinContent(const int& bin) const;
			void SetBinContent(const int& bin);
			int 
		};

		template<typename T>
		class Histogram1D : Histogram<T>{

		};
	}
}


#endif //Protium_Histogram_h_