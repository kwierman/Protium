#ifndef Protium_Histogram_hh_
#define Protium_Histogram_hh_

#include "Protium/Containers/Functional.hh"

#include <map>

namespace Protium{

	namespace Containers{

		template<typename BinType>
		struct Bin{
			BinType loweredge;
			BinType width;

			Bin(const Bin& other) : loweredge(other.loweredge) , width(other.width) {}

			Bin() : loweredge(0), width(0) {}

			Bin& operator=(const Bin& other){
				this->loweredge = other.loweredge;
				this->width = other.width;
				return *this;
			}

			bool operator<(const Bin& rhs) const{
				return ( (this->loweredge) < (rhs.loweredge) );
			}

			bool operator>(const Bin& rhs) const{
				return ( (this->loweredge) > (rhs.loweredge) );
			}

			bool operator==(const Bin& rhs) const{
				return ( (this->loweredge) == (rhs.loweredge) );
			}

			bool operator<(const BinType& rhs) const{
				return ( (this->loweredge) < rhs );
			}

			bool operator>(const BinType& rhs) const{
				return (this->loweredge + this->width) > (rhs) ;
			}

			bool operator==(const BinType& rhs) const{
				return ((rhs>this->lowerEdge) && (rhs< this->lowerEdge+this->width) ) ;
			}

		};
		typedef Bin<double> DBin;
		typedef Bin<int> IBin;
		typedef Bin<unsigned> UBin;
		typedef Bin<float> FBin;


		/*
			\page Histogramming

			\section 1D Histogramming

			The idea here is this:
			You can either know your range of histogramming, and granularity, or you can not.
			Either way, we should be able to optimize this
		*/

		template<class BinType=double>
		class Histogram1D : public Functional1D< Bin<BinType> , unsigned > {

			typedef Functional1D< Bin<BinType>, unsigned > HistType;
			typedef std::map< Bin<BinType>, unsigned >		DataType;
			typedef typename DataType::iterator DataIt;

		public:
			//! Most Basic Histogram instantiation. Creates uniform size bins
			//! \param lowerEdge Specifies the lowest value that this histogram should accept
			//! \param upperEdge Specifies the highest value that this histogram should accept.
			//! \param nBins Specifies the number of bins that this histogram should have
			//! \note The number of bins this histogram creates is nBins+2. The extra bins are for underflow/overflow. These can be probed by looking for values that are below the lowest edge or above the highest edge.
			Histogram1D( const BinType& lowerEdge, const BinType& upperEdge, const unsigned& nBins){
				double width = (upperEdge-lowerEdge)/double(nBins);
				for(unsigned i=0; i<nBins; i++){
					Bin<BinType> tempBin;
					tempBin.width = width;
					tempBin.loweredge = lowerEdge+double(i)*width;
					this->fData.insert(std::make_pair< Bin<BinType>, unsigned>(tempBin,0) );
				}
			}



			unsigned GetNBins() const{
				return HistType::fData.size();
			}

			//! Use this for Rebinning. 
			//! Bins overlapping this one get resized so that:
			//!    The bin overlapping the lower edge gets rebinned to the lower edge
			//!    The bin overlapping the upper edge gets rebinned to the upper edge
			//!    The bins overlapping the middle range (inclduing those with matching edges of the new bin)
			//!    get deleted and replaced by the new bin (bin content gets transferred).
			/*void SetNewBin(const BinType& lowerEdge, const BinType& delta ){
				Bin newBin;
				newBin.width=delta;
				newBin.loweredge = lowerEdge;
				unsigned newContent =0;
				typename std::map<Bin,unsigned>::iterator hIt = fContents.begin();
				//move iterator to the first bin intersects with the  
				while( hIt->first < newBin ){hIt++;}


				fContents[newBin] = newContent;
			}
			*/
			//void AddBin(const BinType& edge, const BinType& width);

			BinType GetLowerEdgeByIndex(const unsigned& i) const {


				for(unsigned int j =0; j<i; j++){

				}


				return BinType(1e6);
			}

			BinType GetBinWidthByIndex(const int& i) const {
				return HistType::fData[i].first.width;	
			}

			unsigned GetBinContentByIndex(const int& i) const {
				return HistType::fData[i].second;
			}



			BinType GetLowerEdgeByValue(const BinType& i) const {

				return (*HistType::fData.lower_bound(i)).first.loweredge;
			}

			BinType GetBinWidthByValue(const int& i) const {
				return (*HistType::fData.lower_bound(i)).first.width;	
			}

			unsigned GetBinContentByValue(const int& i) const {
				return (*HistType::fData.lower_bound(i)).width;	
			}

			void FillByIndex(const unsigned& i){
				HistType::fData[i].second++;	
			}

			void FillByValue(const BinType& val){
				HistType::RefAt(val)++;
			}
			
		};

		typedef Histogram1D<double> Hist1D;
	}
}


#endif //Protium_Histogram_h_