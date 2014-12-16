#include "Protium/Containers/Histogram.hh"
using Protium::Containers::Hist1D;
#include "Protium/Time/Clock.hh"
using Protium::Time::SingleClocker;
#include "Protium/Time/Time.hh"
using Protium::Time::TimeDate;
#include "Protium/Utilities/SignalCatching.hh"
using Protium::Utilities::SignalCatcher;

#include <iostream>
#include <fstream>




int main(int argc, char* argv[] ){
	SignalCatcher::Instance().Setup();
	std::cout<<"Creating histograms of fixed size..."<<std::endl;

	SingleClocker topClocker;
	topClocker.Start();
	std::ofstream output;
	output.open("histogramAlloc.txt");

	for(unsigned i =0 ; i<1000;i++){
		SingleClocker cl;
		cl.Start();
		Hist1D hist(0,100,i);	
		cl.Stop();
		std::cout<<"Allocated Size: "<<i<<" in time: "<<TimeDate(cl.GetTime() ).AsFormat("%S")<<" seconds"<<std::endl;
		output<<i<<","<<cl.GetTime()<<std::endl;
	}
	topClocker.Stop();
	output.close();
	std::cout<<"Allocated all Histograms in: "<<topClocker.GetTime()<<" Cycles"<<std::endl;

	{
		std::cout<<"Checking out filling algorithms..."<<std::endl;
		Hist1D hist(0,100,1000);
		//checking for blank histogram
		std::cout<<"Number of bins: "<<hist.GetNBins()<<std::endl;
		//fill each bin with the inverse number of fills
		for(double i =0.; i<100; i+=0.1 ){
			for(int j=0; j< int(100.0-i) ;j++){
				hist.FillByValue(i);
			}
		}
		std::cout<<"Finding Bin Contents By Value: "<<std::endl;
		for(double i =0.;i<100;i+=0.1 ){
			std::cout<<"For Value: "<<i<<" bin content: "<<hist.GetByValue(i)<<std::endl;
		}


		//for(unsigned i =0; i< hist.GetNBins() ; i++ ){

		//	std::cout<<"Bin: "<<i<<" content: "<<hist.GetBinContentByIndex(i)<<" loweredge: "<<
		//	hist.GetLowerEdgeByIndex(i)<<" width: "<<hist.GetBinWidthByIndex(i)<<std::endl;
		//}

		//Filling in a line
		/*for(double i=0.0; i<1000.0; i+=0.1){
			for(int j=0; double(j)< i; j++){
				hist.FillByValue(i);
			}
		}*/

	}

	
}