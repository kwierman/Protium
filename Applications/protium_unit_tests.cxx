//#include "Protium/Collections/Histogram.h"
//#include "Protium/Collections/Function.h"
#include "Protium/LinearAlgebra/LinearAlgebra.h"
//#include "Protium/LinearAlgebra/Matrix.h"
#include "Protium/Math/MathFunctions.h"
#include "Protium/Utilities/SignalCatching.h"

#include <iostream>
#include <iomanip>
#include <vector>

using namespace Protium;
int main(int argc, char* argv[]){

	Protium::Utilities::SignalCatcher::Instance().Setup();

	std::cout<<"Starting Basic Unit Tests"<<std::endl;
	std::cout<<"\tMath tests"<<std::setprecision(16)<<std::endl;
	{
		using namespace Math;
		std::cout<<"\t\tInt factorial (6): "<< 
			factorial<unsigned>(3)<<"\t"<<factorial<int>(3)<<
			"\t"<<factorial<long>(3)<<std::endl;

		std::cout<<"\t\tFloat/Double factorial (6): "<< 
			factorial<float>(3)<<"\t"<<factorial<double>(3)<<
			"\t"<<factorial<long double>(3)<<std::endl;

		std::cout<<"\t\tEuler\'s Number (2.71828182845904523536028747135266249775724709369995): "<<nat<<std::endl;
		std::cout<<"\t\t\tError: "<<2.71828182845904523536028747135266249775724709369995-nat<<std::endl;
		std::cout<<"\t\tPowers: "<<std::endl;
		for(double i=0; i<15;i++)for(double j=0; j<15; j++)
			std::cout<<"\t"<<power(i,j)<<"\t";
		std::cout<<std::endl;
	}
	
	std::cout<<"\tLinear Algebra Tests"<<std::endl;
	{
		using namespace LinearAlgebra;
		ThreeVector threeVector1;
		ThreeVector threeVector2;
			


		for(int i=0; i<3;i++){
			std::cout<<threeVector1[i]<<"\t";
			threeVector1[i]=double(i);
			threeVector2[i]=double(i+i);
		}
		std::cout<<std::endl;

		double dot_product = threeVector1* threeVector2;
		std::cout<<"Dot Product: "<<dot_product<<std::endl;
		

		ThreeVector threeVector3 = threeVector1+threeVector2;
		for(int i=0; i<3;i++)
			std::cout<< threeVector3[i]<<"\t";
		std::cout<<std::endl;

		

		TwoVector twoVector = threeVector3.GetSubVector(2);
		for(int i=0; i<2;i++)
			std::cout<<twoVector.At(i)<<"\t";
		std::cout<<std::endl;


		const TwoVector copy1 = twoVector;
		TwoVector copy2(copy1);
		
		
		ThreeMatrix mat;
		std::cout<<mat.GetNRows()<<"\t"<<mat.GetNColumns()<<std::endl;
		ThreeVector temp = mat[0];
		std::cout<<mat.At(0,0)<<std::endl;

		
		for(int i=0; i<3;i++){
			ThreeVector& temp = mat[i];
			for(int j=0; j<3;j++)
				temp[j] = i*j+j*j+i*i;
		}
		
		for(int i=0; i<3;i++){
			for(int j=0; j<3;j++)
				std::cout<< mat[i][j]<<"\t";
			std::cout<<std::endl;
		}

/*
		TwoMatrix mat2 = mat.GetSubMatrix(0,0);
		for(int i=0;i<2;i++)
			for(int j=0; j<2;j++)
				std::cout<<mat2.At(i,j)<<"\t";
*/
	}

}