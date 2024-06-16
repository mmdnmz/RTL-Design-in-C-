#ifndef SORTER_DP
#define SORTER_DP

#include "classVectorPrimitives.h"
#include <string>
using namespace std;

class SorterDP
{
	bus* clk, * rst;
	bus* ldTemp, * ldMin, * ldMinAddress, * ldcounter2, * Cnt1, * Cnt2, * SelMinTemp, * SelInMin, * SelOctaCount, * SelAddr;
	bus * Read, *Write;
	bus* co1, *co2;
	bus* Result;
	// Components
	dRegisterRaE* tempReg;
	dRegisterRaE* minReg;
	dRegisterRaE* minAddrReg;

	Memory* dataMemory;

	Mux* mintemp;
	Mux* inmin;
	Mux* octaCount;
	Mux* addr;

	Comparator* minRead;

	upCounterRaE* counter1;
	upCounterRaE* counter2;

	bus hardOne;
	bus hardZero;
	bus monoHardzero;
	bus ReadData, WriteData, Address;
	bus tempOut, minOut, minAddrOut, lessThan, cnt2Out, cnt1Out, incOut, muxOctaCountOut, inminOut;
	bus lt, eq, gt;
	bus loadMin, loadMinAddr;
	bus cnt2En, Enabler, placeHolders;

public:
	SorterDP(bus& clk, bus&rst,
			bus& Write, bus& Read,
			bus& ldTemp, bus& ldMin, bus& ldMinAddress,
			bus& ldcounter2, bus& Cnt1, bus& Cnt2, bus& SelMinTemp,
			bus& SelInMin, bus& SelOctaCount, bus& SelAddr,
			bus& co1, bus &co2,
			bus&Result
			);
	~SorterDP();
	void evl();
	void evlMemory() { dataMemory -> evl(); }
	void initMemory (string filename) { dataMemory -> init(filename); }
	void dumpMemory (string filename) { dataMemory -> dump(filename); }
};

#endif
