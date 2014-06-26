#ifndef Protium_Matrix_h_
#define Protium_Matrix_h_

#include "Protium/LinearAlgebra/Vector.h"

namespace Protium{
	namespace LinearAlgebra{


		//A matri
		class MatrixPrototype{
		public:
			MatrixPrototype(){}
			virtual ~MatrixPrototype(){}
		};

		template<typename T, int n, int m>
		class Matrix : public MatrixPrototype{
			std::vector< Vector<T,m> > fComponents;
			typedef typename std::vector< Vector<T,m> >::iterator Titer;

		public:
			Matrix() {
				for(int i=0; i<m; i++){
					fComponents.push_back( Vector<T,n>() );
				}
			}

			T& operator[](const int& index){
		    	return fComponents[index];
		    }

		    Vector<T,n>& At(const int& i) const{
		    	return fComponents[i];
		    }

		    //const access, instead of []operator
		    T At(const int& i, const int& j) const{
		    	return fComponents[i].At(j);
		    }

			Matrix& operator+=(const Matrix& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i]  += rhs.At(i);
	    		return *this;
	  		}

	  		//only want to be able to multiply by 
			Matrix& operator*=(const T& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] *=rhs;
	    		return *this;
	  		}

	  		Vector<T,m> operator*=(const Vector<T,n>& rhs) {
	  			Vector<T,n> ret;
	  			for(int i=0; i<n;i++)
	  				ret[i] = (*this)[i] * rhs;
	  			return ret;
	  		}

	  		Matrix& operator*=(const Matrix& rhs){
	  			for(int i=0; i<n;i++)
	  				for(int j=0; j<n;j++)
	  					(*this)[i][j] *= rhs.At(i,j);
	  			return (*this);
	  		}

			Matrix& operator-=(const Matrix& rhs) {
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
				for(int i=0; i<n;i++)
					 (*this)[i] -=rhs.At(i);
	    		return *this;
	  		}

	  		const Matrix operator+(const Matrix& rhs) const {
	    		return Matrix(*this) += rhs;
	  		}
	  		const Matrix operator-(const Matrix& rhs) const {
	    		return Matrix(*this) -= rhs;
	  		}

	  		const Matrix operator*(const Matrix& rhs) const {
	    		return Matrix(this) *= rhs;
	  		}

			const Matrix operator*(const T& rhs) const {
	  			return Matrix(*this) *=rhs;
	  		}

	  		bool operator==( const Matrix &rhs) const {
	  			bool ret=true;
				//PROTIUM_STATIC_ASSERT(n == m,"Vector Dimensions Must Match");
	  			for(int i=0; i<n;i++)
	  				ret &= ( this->At(i) == rhs.At(i) );
	  			return ret;
	  		}
		  	bool operator!=( const Matrix &rhs) const {
	    		return !(*this == rhs);
	  		}


		};

		typedef Matrix<double, 2,2> TwoMatrix;
		typedef Matrix<double,3,3> ThreeMatrix;
		typedef Matrix<double,4,4> FourMatrix;
	}
}


#endif //File Guardian