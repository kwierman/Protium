#ifndef Protium_Chunk_h_
#define Protium_Chunk_h_

#include <cstddef>

namespace Protium{

	namespace Allocation{

		//! Represents a fixed number of blocks
		class Chunk{
			//!Data
        	unsigned char* fData;
        	//! First Available block
	        unsigned char fFirstAvailable;
	        //! Number of available blocks
	        unsigned char fNAvail;
	        //! The next level up
			friend class FixedAllocator;
			//! Each time a new chunk is created, it must be initialized (or when reused in a pool)
			//! \param size the size per chunk
			//! \param n the number of blocks
        	bool Init( std::size_t size, unsigned char n );
        	//! Each time a chunk is reused, it needs to be reset
	        void Reset( std::size_t blockSize, unsigned char blocks );
	        void Release();
        	void* Allocate( std::size_t blocks );
	        void Deallocate( void * p, std::size_t blocks );
	        bool IsCorrupt( unsigned char numBlocks, std::size_t blockSize, bool checkIndexes ) const;
	        bool IsBlockAvailable( void* p, unsigned char numBlocks, std::size_t blockSize ) const;
	        inline bool HasBlock( void* p, std::size_t chunkLength ) const {
	            unsigned char * pc = static_cast< unsigned char * >( p );
	            return ( fData <= pc ) && ( pc < fData + chunkLength );
	        }

	        inline bool HasAvailable( unsigned char numBlocks ) const {
	        	return ( fNAvail == numBlocks ); 
	        }

	        inline bool IsFilled( void ) const { 
	        	return ( 0 == fNAvail ); 
	        }
		};
	}
}



#endif //File Guardian