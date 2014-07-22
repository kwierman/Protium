#ifndef Protium_Matrix_h_
#define Protium_Matrix_h_

#include "Protium/LinearAlgebra/Vector.h"

#include <vector>

namespace Protium{
	namespace LinearAlgebra{

		//! Implements matrix operations
		template<typename T, int n, int m>
		class Matrix : public Protium::Allocation::DefaultSmallObject {
			std::vector<Vector<T, n> > fComponents;
		public:
			Matrix() : Protium::Allocation::DefaultSmallObject() {
				for(int i=0; i< m;i++)fComponents.push_back(Vector<T,n>() );
			}
			~Matrix(){
				fComponents.clear();
			}

			inline static int GetNRows(){return n;}
			inline static int GetNColumns(){return m;}

		    /** Reference Access operator.
		    **/
		    Vector<T, n>& operator[](const int& row){
		    	return fComponents[row];
		    }

		    /** Const Reference operator
		    **/
		    const T& At(const int& row, const int& column){
		    	return fComponents[row][column];
		    }

		    Matrix<T,m,n> Transpose(){
		    	Matrix<T,m,n> trans;
		    	for(int i =0;i<n;i++)for(int j=0;j<m;j++)
		    		trans[i][j]=fComponents[j][i];
		    	return trans;
		    }

		    /** Increment operator
		    	\param rhs Matrix to increment by (increments each element by it's corresponding one)
		    **/
			Matrix<T,n,m>& operator+=(const Matrix<T,n,m>& rhs) {
				for(int i=0; i<n;i++)
					 (*this)[i]  += rhs.At(i);
	    		return *this;
	  		}

	  		/** Operator only defined for multiplying by another type
	  		**/
			Matrix<T,n,m>& operator*=(const T& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] *=rhs;
	    		return *this;
	  		}

			Vector<T,m> operator*=(const Vector<T,n>& rhs) {
				Vector<T,m> other;

				for(int i=0; i<m;i++)
					other[i] = fComponents[i]*rhs;
	    		return other;
	  		}

	  		template<int k>
	  		Matrix<T,n,k> operator*=(const Matrix<T,m,k>& rhs) const {
	  			Matrix<T,k,m> transpose = rhs.Transpose();
	  			Matrix<T,n,k> ret;
				for(int i=0; i<n;i++)
					for(int j=0;j<k;j++)
						ret[i][j] = ((*this)[i]) * (transpose[j]);
	    		return ret;
	  		}

	  		/** Decrement operator
	  		**/
			Matrix<T,n,m>& operator-=(const Matrix<T,n,m>& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] -=rhs.At(i);
	    		return *this;
	  		}

	  		/** Addition operator
	  		**/
	  		const Matrix<T,n,m> operator+(const Matrix<T,n,m>& rhs) const {
	    		return Matrix<T,n,m>(*this) += rhs;
	  		}

	  		/** Subtraction operator
	  		**/
	  		const Matrix<T,n,m> operator-(const Matrix<T,n,m>& rhs) const {
	    		return Matrix<T,n,m>(*this) -= rhs;
	  		}

	  		/** Multiplication Operator
	  			on the lhs we have this, a matrix of dimensions nxm or m vectors of n length
	  			on the rhs, we have a matrix of dimensions mxk or k vectors of m length
	  			the product is a vector of size nxk
	  			transpose the 
	  			\param rhs A vector of same type and size
	  			\return constant of vector type
	  		**/
	  		template<int k>
	  		const Matrix<T,n,k> operator*(const Matrix<T,m,k>& rhs) const {
	  			Matrix<T,k,m> transpose = rhs.Transpose();
	  			Matrix<T,n,k> ret;
				for(int i=0; i<n;i++)
					for(int j=0;j<k;j++)
						ret[i][j] = ((*this)[i]) * (transpose[j]);
	    		return ret;
	  		}

	  		/** Multiplication Operator
	  			\param rhs Of vector type
	  			\return Vector of same size and type as current one
	  		**/
			const Matrix<T,n,m> operator*(const T& rhs) const {
	  			return Matrix<T,n,m>(*this) *=rhs;
	  		}

	  		const Vector<T,m> operator*(const Vector<T,n>& rhs) {
				Vector<T,m> other;

				for(int i=0; i<m;i++)
					other[i] = fComponents[i]*rhs;
	    		return other;
	  		}


	  		/** Assignment Operator
	  		**/
	  		Matrix<T,n,m>& operator=( const Matrix<T,n,m>& rhs ){
      			for(int i=0; i<n;i++)fComponents[i] = rhs.At(i);
      			return *this;
  			}

	  		/** Comparison operator
	  		**/
	  		bool operator==( const Matrix<T,n,m> &rhs) const {
	  			bool ret=true;
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
	  			for(int i=0; i<n;i++)
	  				ret &= ( this->At(i) == rhs.At(i) );
	  			return ret;
	  		}

	  		/** Negative comparison operator
	  		**/
		  	bool operator!=( const Matrix<T,n,m>&rhs) const {
	    		return !(*this == rhs);
	  		}


		};

		typedef Matrix<double, 2,2> TwoMatrix;
		typedef Matrix<double, 3,3> ThreeMatrix;
		typedef Matrix<double, 4,4> FourMatrix;

	}
}


#endif //File Guardian