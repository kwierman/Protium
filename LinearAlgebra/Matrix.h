#ifndef Protium_Matrix_h_
#define Protium_Matrix_h_

#include "Protium/LinearAlgebra/Vector.h"

#include <vector>
#include <cmath>


namespace Protium{
	namespace LinearAlgebra{

		template<typename T, int n, int m>
		class Matrix;

		//! Helper struct to retrieve out a submatrix missing it's
		template<typename T, int n, int m>
		struct SubMatrix{
			Matrix<T, n-1,m-1> Of(const Matrix<T,n,m>& other, const int& i=0, const int& j=0){
				Matrix<T,n-1,m-1> temp;
				int index1=0;
				for(int k=0;k<m;k++){
					if(k!=j){
						temp[index1++] = other.At(k).GetSubVector(i);
					}
				}
				return temp;
			}
		};

		template<typename T, int n>
		struct SubMatrix<T,n,0>{
			Matrix<T, n-1,0> Of(const Matrix<T,n,2>& other, const int& i=0, const int& j=0){
				Matrix<T,n-1,1> temp;
				int index1 = j==0? 1 : 0;
				int index2=0;
				for(int k=0;k<n;k++)
					if(k!=i)	
						temp[index2++][0] = T(other.At(k,index1) );
				return temp;
			}
		};

		template<typename T, int m>
		struct SubMatrix<T,0,m>{
			Matrix<T,0,m-1> Of(const Matrix<T,2,m>& other, const int& i=0, const int& j=0){
				Matrix<T,1,m-1> temp;
				int index1 = i==0? 1 : 0;
				int index2=0;
				for(int k=0;k<m;k++)
					if(k!=j)	
						temp[0][index2++] = T(other.At(index1,k) ) ;
				return temp;
			}
		};


		template<typename T>
		struct SubMatrix<T,2,2>{
			Matrix<T,1,1> Of(const Matrix<T,2,2>& other, const int& i=0, const int& j=0){
				Matrix<T,1,1> temp;
				if(i==0){
					if(j==0)
						temp[0][0] = T(other.At(1,1) );
					else
						temp[0][0] = T(other.At(0,1) );
				}
				else{
					if (j==0)
						temp[0][0] = T(other.At(1,0) );
					else
						temp[0][0]= T(other.At(0,0) );
				}
				return temp;
			}
		};

		template<typename T, int n, int m>
		struct Determinant{
			T Of(const Matrix<T,n,m>& other){
				return T( nanf('0') );
			}
		};

		template<typename T, int n>
		struct Determinant<T,n,n>{
			T Of(const Matrix<T,n,n>& other){
				T det = T(0);
				T s = T(1);
				for(int i=0;i<n;i++){
					det+= (s)*(other.At(0,i) )*(other.GetSubMatrix(i,0).GetDeterminant() );
					s = -s;
				}
				return det;
			}
		};

		template<typename T>
		struct Determinant<T,1,1>{
			T Of(const Matrix<T,1,1>& other){
				return T(other.At(0,0) );
			}
		};


		//! Implements matrix operations
		template<typename T, int n, int m>
		class Matrix : public Protium::Allocation::DefaultSmallObject {
			std::vector<Vector<T, n> > fComponents;
		public:

			void Init(){
				for(int i=0; i< m;i++)fComponents.push_back(Vector<T,n>() );
			}

			Matrix() : Protium::Allocation::DefaultSmallObject() {
				Init();
			}
			Matrix(const Matrix<T,n,m>& other) {
				Init();
				for(int i=0; i<n;i++)
					for(int j=0; j<m;j++)
						fComponents[i][j] = T(other.At(i,j) );
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

		    Vector<T,n> At(const int& row) const{
		    	return fComponents.at(row);
		    }

		    /** Const Reference operator
		    **/
		    const T& At(const int& row, const int& column) const{
		    	return fComponents.at(row).At(column);
		    }

		    Matrix<T,m,n> Transpose() const{
		    	Matrix<T,m,n> trans;
		    	for(int i =0;i<n;i++)for(int j=0;j<m;j++)
		    		trans[i][j]= this->At(j,i);
		    	return trans;
		    }

		    Matrix<T,m-1,n-1> GetSubMatrix(const int& i, const int& j) const{
		    	SubMatrix<T, m,n> helper;
		    	return helper.Of( (*this) , i,j);
		    }

		    T GetDeterminant() const{
		    	Determinant<T,m,n> helper;
		    	return helper.Of(*this );
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
						ret[i][j] = (this->At(i) ) * (transpose[j]);
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

	  		static Matrix<T,n,m> Unit(){
	  			Matrix<T,n,m> temp;
	  			for(int i=0; i<m;i++)
	  				temp[i] = Vector<T,n>::UnitVector(i);
	  			return temp;
	  		}
		};

		typedef Matrix<double, 2,2> TwoMatrix;
		typedef Matrix<double, 3,3> ThreeMatrix;
		typedef Matrix<double, 4,4> FourMatrix;
		typedef Matrix<double, 5,5> FiveMatrix;
		typedef Matrix<double, 6,6> SixMatrix;
		typedef Matrix<double, 7,7> SevenMatrix;

	}
}


#endif //File Guardian