#ifndef Protium_Histogram_hh_
#define Protium_Histogram_hh_

#include <map>

namespace Protium{

	namespace Containers{

		template<class BinType=double>
		class Histogram{

			struct Bin{
				BinType loweredge;
				BinType width;

				bool operator<(const Bin& rhs) const{
					return (this->loweredge) < (rhs.loweredge) ;
				}

				bool operator>(const Bin& rhs) const{
					return (this->loweredge) > (rhs.loweredge) ;
				}

				bool operator==(const Bin& rhs) const{
					return (this->loweredge) == (rhs.loweredge) ;
				}
			};

			std::map<Bin, unsigned> fContents;

		public:
			//! Most Basic Histogram instantiation. Creates uniform size bins
			Histogram( const BinType& lowerEdge, const BinType& upperEdge, const unsigned& nBins){
				for(unsigned i=0; i<nBins; i++){
					Bin tempBin;
					tempBin.width=(upperEdge-lowerEdge)/( (double)nBins );
					tempBin.loweredge = double(i)* (upperEdge-lowerEdge)/( (double)nBins );
					fContents.insert(std::make_pair<Bin, unsigned>(tempBin,0) );
				}
			}

			unsigned GetNBins() const{
				return fContents.size();
			}

			//! Use this for Rebinning. 
			//! Bins overlapping this one get resized so that:
			//!    The bin overlapping the lower edge gets rebinned to the lower edge
			//!    The bin overlapping the upper edge gets rebinned to the upper edge
			//!    The bins overlapping the middle range (inclduing those with matching edges of the new bin)
			//!    get deleted and replaced by the new bin (bin content gets transferred).
			void SetNewBin(const BinType& lowerEdge, const BinType& delta ){
				Bin newBin;
				newBin.width=delta;
				newBin.loweredge = lowerEdge;
				unsigned newContent =0;
				typename std::map<Bin,unsigned>::iterator hIt = fContents.begin();
				//move iterator to the first bin intersects with the  
				while( hIt->first < newBin ){hIt++;}


				fContents[newBin] = newContent;
			}

			BinType GetLowerEdgeByI(const int& i) const {
				int index=0;
				for(typename std::map<Bin, unsigned>::const_iterator it = fContents.begin(); it!=fContents.end(); ++it){
					if(i==index++)
						return (*it).first.loweredge;

				}
			}

			BinType GetBinWidthByI(const int& i) const {
				int index=0;
				for(typename std::map<Bin, unsigned>::const_iterator it = fContents.begin(); it!=fContents.end(); ++it){
					if(i==index++)
						return (*it).first.width;

				}	
			}

			unsigned GetBinContentByI(const int& i) const {
				int index=0;
				for(typename std::map<Bin, unsigned>::const_iterator it = fContents.begin(); it!=fContents.end(); ++it){
					if(i==index++)
						return (*it).second;

				}
			}


			//Histogram(int nBins, std::vector<double>&binWidths, std::vector<double>& );


			//BinType GetBinLowerEdgeByI(const int& i);
			//BinType GetBinLowerEdgeByPos( const BinType& i);

			//BinType GetBinHigherEdgeByI(const int& i);
			//BinType GetBinHigherEdgeByPos( const BinType& i);

			//BinType GetBinWidthByI(const int& i);
			//BinType GetBinWidthByPos( const BinType& i);

			//YType GetBinQuantityByI(const int& i);
			//YType GetBinQuantityByPos( const BinType& i);

			//void AddBin(const BinType& edge, const BinType& width);

			//void Initialize(const int& xbins, const int& ybins, const int& zbins, BinType& defaultBinType );

			//ContentType& IterateBinContent(const BinType& bin );

			//void SetBinContent(const BinType& bin, const ContentType& content);

			//void Normalize();
		};

		typedef Histogram< double> Histo1D;
	}
}


#endif //Protium_Histogram_h_