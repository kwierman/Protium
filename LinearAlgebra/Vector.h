#ifndef Protium_Vector_h_
#define Protium_Vector_h_

#include "Protium/Allocation/SmallObject.h"

#include <vector>
#include <cmath>

namespace Protium{

	namespace LinearAlgebra{

		template<typename T, int n>
		class Vector;


		template<typename T, int n>
		struct SubVector{
			Vector<T, n-1> Of(const Vector<T,n>& other, int i=0){
				Vector<T,n-1> temp;
				int index=0;
				for(int j=0; j<n;j++ ){
					if(j!=i)
						temp[index++] = other.At(j);
				}
				return temp;
			}
		};


		template<typename T>
		struct SubVector<T,1>{
			Vector<T, 0> Of(const Vector<T,1>& other, int i=0){
				Vector<T,0> temp;
				if(i==0)
					temp[0] = other.At(1);
				else
					temp[0] = other.At(0);
				return temp;
			}
		};

		//! Implements vector multiplication, addition, subtraction.
		template <typename T, int n=3>
		class Vector : public Protium::Allocation::DefaultSmallObject {

			//! Holds the components of the vector
			std::vector<T> fComponents;

		public:

			/** Default Constructor.
				\param amplitude the amplitude of the vector
			**/
			Vector<T,n>(const T& amplitude=1) : Protium::Allocation::DefaultSmallObject() {
				fComponents.reserve(n);
				this->Normalize( amplitude );
			}

			/** Construct from an array. Copies contents.
				\param input An array of size n and type T
			**/
			Vector<T,n>(const T* input) : Protium::Allocation::DefaultSmallObject(){
				fComponents.reserve(n);
				for(int i=0; i<n; i++)
					fComponents[i] = T(input[i]);
			}

			/** Construct from STL Vector
			**/
			Vector<T,n>(const std::vector<T>& vec) : Protium::Allocation::DefaultSmallObject(){
				fComponents.reserve(n);
				for(int i=0; i<n;i++)
					fComponents[i] = T(vec[i] );
			}

			/** Copy constructor.
			**/
			Vector<T,n>(const Vector<T,n>& other) : Protium::Allocation::DefaultSmallObject(){
				fComponents.reserve(n);
				for(int i=0; i<n; i++){
					fComponents[i] =  T( other.At(i) );
				}
			}

			/** Default Destructor
			**/
			virtual ~Vector(){
				fComponents.clear();
			}

			/**
				Returns back the template integer parameter
			**/
			static int NDimensions() {
				return n;
			}

			/** Calculates the norm of the vector
				\return The square root of the square of this vector
			**/
		    virtual T Norm() const {
		      return sqrt( (*this)*(*this) );
		    }

		    /** Normalizes this vector to a constant
		    	\param norm The normalization constant
		    	\return The norm of the vector
		    **/
		    virtual T Normalize(const T& norm){
		    	T old_norm = this->Norm();
		    	if(old_norm ==0) return 0;
		    	for(int i=0 ;i<n; i++ )
		    		fComponents[i] *= (norm/old_norm);
		    	return this->Norm();
		    }

		    /** Calculates and returns a vector of one less dimension
		    	\param i The index of the element to be left out
		    	\return A vector of one less dimension
		    **/
		   
		    Vector<T,n-1> GetSubVector(const int& i){
		    	SubVector<T,n> helper;
		    	return helper.Of( (*this), i ); 
		    }
		    
		    /** Access operator.
		    **/
		    T& operator[](const int& index){
		    	return fComponents[index];
		    }

		    /** Const access operator
		    **/
		    const T& At(const int& index) const{
		    	return fComponents[index];
		    }

		    /** Increment operator
		    	\param rhs Vector to increment by (increments each element by it's corresponding one)
		    **/
			Vector<T,n>& operator+=(const Vector<T,n>& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i]  += rhs.At(i);
	    		return *this;
	  		}

	  		/** Operator only defined for multiplying by another type
	  		**/
			Vector<T,n>& operator*=(const T& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] *=rhs;
	    		return *this;
	  		}

	  		/** Decrement operator
	  		**/
			Vector<T,n>& operator-=(const Vector<T,n>& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] -=rhs.At(i);
	    		return *this;
	  		}

	  		/** Addition operator
	  		**/
	  		const Vector<T,n> operator+(const Vector<T,n>& rhs) const {
	    		return Vector(*this) += rhs;
	  		}

	  		/** Subtraction operator
	  		**/
	  		const Vector<T,n> operator-(const Vector<T,n>& rhs) const {
	    		return Vector(*this) -= rhs;
	  		}

	  		/** Multiplication Operator
	  			\param rhs A vector of same type and size
	  			\return constant of vector type
	  		**/
	  		const T operator*(const Vector<T,n>& rhs) const {
	  			T ret=0;
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					ret+= this->At(i) * rhs.At(i);

	    		return ret;
	  		}

	  		/** Multiplication Operator
	  			\param rhs Of vector type
	  			\return Vector of same size and type as current one
	  		**/
			const Vector<T,n> operator*(const T& rhs) const {
	  			return Vector(*this) *=rhs;
	  		}

	  		/** Assignment Operator
	  		**/
	  		Vector<T,n>& operator=( const Vector<T,n>& rhs ){
      			for(int i=0; i<n;i++)fComponents[i] = rhs.At(i);
      			return *this;
  			}

	  		/** Comparison operator
	  		**/
	  		bool operator==( const Vector<T,n> &rhs) const {
	  			bool ret=true;
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
	  			for(int i=0; i<n;i++)
	  				ret &= ( this->At(i) == rhs.At(i) );
	  			return ret;
	  		}

	  		/** Negative comparison operator
	  		**/
		  	bool operator!=( const Vector<T,n> &rhs) const {
	    		return !(*this == rhs);
	  		}

		};

		//! Convenience Typedef of a double twovector
		typedef Vector<double, 2> TwoVector;
		//! Convenience typedef of a double three vector
		typedef Vector<double, 3> ThreeVector;
		//! Convenience typedef of a double four vector
		typedef Vector<double, 4> FourVector;
	}
}


#endif //File Guardian

