#ifndef Protium_Vector_h_
#define Protium_Vector_h_

#include <vector>
#include <cmath>

#include "Protium/Allocation/SmallObject"

namespace Protium{

	namespace LinearAlgebra{


		//! Implements vector multiplication, addition, subtraction.
		template <typename T, int n=3>
		class Vector  : public Protium::Allocation::SmallObject {

			//! Required to get sub vectors of a vector
			struct SubVectorHelper{
				//! Returns a subvector of one less dimension than the current one
				Vector<T,n-1> GetSubVector(int i, const Vector<T,n>& vec){
					Vector<T,n-1> temp;
					int index = 0;
					for(int j=0; j< n;j++)
						if(j!=i)
							temp[index++] = vec.At(j);
						return temp;
				};
			};

		protected:
			//! Holds the components of the vector
			T* fComponents;

		public:

			/** Default Constructor.
				\param amplitude the amplitude of the vector
			**/
			Vector(const T& amplitude=1){
				fComponents = new T[n];

				for(int i=0; i<n; i++){
					fComponents[i] =T();
				}
				this->Normalize( amplitude );
			}

			/** Construct from an array. Copies contents.
				\param input An array of size n and type T
			**/
			Vector(const T* input){
				fComponents = new T[n];
				for(int i=0; i<n; i++)
					fComponents[i] = T(input[i]);
			}

			/** Construct from STL Vector
			**/
			Vector(const std::vector<T>& vec){
				fComponents = new T[n];
				for(int i=0; i<n;i++)
					fComponents[i] = vec[i];
			}

			/** Copy constructor.
			**/
			Vector(const Vector<T,n>& other){
				for(int i=0; i<n; i++){
					fComponents[i] =  T(other.At(i) );
				}
			}

			/** Default Destructor
			**/
			virtual ~Vector(){
				delete fComponents;
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
		    	for(Titer it = fComponents.begin(); it!=fComponents.end();++it )
		    		(*it) *= (norm/old_norm);
		    	return this->Norm();
		    }

		    /** Calculates and returns a vector of one less dimension
		    	\param i The index of the element to be left out
		    	\return A vector of one less dimension
		    **/
		    Vector<T,n-1> GetSubVector(const int& i){
		    	SubVectorHelper helper;
		    	return helper.GetSubVector(i, (*this) ); 
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
			Vector& operator+=(const Vector& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i]  += rhs.At(i);
	    		return *this;
	  		}

	  		/** Operator only defined for multiplying by another type
	  		**/
			Vector& operator*=(const T& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] *=rhs;
	    		return *this;
	  		}

	  		/** Decrement operator
	  		**/
			Vector& operator-=(const Vector& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] -=rhs.At(i);
	    		return *this;
	  		}

	  		/** Addition operator
	  		**/
	  		const Vector operator+(const Vector& rhs) const {
	    		return Vector(*this) += rhs;
	  		}

	  		/** Subtraction operator
	  		**/
	  		const Vector operator-(const Vector& rhs) const {
	    		return Vector(*this) -= rhs;
	  		}

	  		/** Multiplication Operator
	  			\param rhs A vector of same type and size
	  			\return constant of vector type
	  		**/
	  		const T operator*(const Vector& rhs) const {
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
			const Vector operator*(const T& rhs) const {
	  			return Vector(*this) *=rhs;
	  		}

	  		/** Comparison operator
	  		**/
	  		bool operator==( const Vector &rhs) const {
	  			bool ret=true;
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
	  			for(int i=0; i<n;i++)
	  				ret &= ( this->At(i) == rhs.At(i) );
	  			return ret;
	  		}
	  		/** Negative comparison operator
	  		**/
		  	bool operator!=( const Vector &rhs) const {
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

