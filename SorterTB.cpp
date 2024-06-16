#include "SorterDesign.h"
#include <chrono>
#include <thread>

int main ()
{
	int ij = 0;

	string filename("dataMem.txt");

	bus clk, rst, start, ready;
	bus Result(16);

	// module instantiation
	SorterDesign *SORTER = new SorterDesign(clk, rst, start, ready, Result);

	SORTER -> initialize(filename);

	do {
		start ="1";
		//cout <<"Enter start = 1 "<<endl;
		//cout <<"start is "<< start << endl;
		SORTER->initialize(filename);
		do{
			clk = "P";
			//cout <<"start is " <<start << endl;
			SORTER -> evl();
			//cout << start << endl;
			start ="0";
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		} while (ready == "0");
		//cout << Result << "\n";
		//cout << "\n" << "Continue (0 or 1)?";
		cin >> ij;

	} while (ij >0);
}
