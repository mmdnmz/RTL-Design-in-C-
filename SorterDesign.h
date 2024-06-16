#ifndef SORTER_DESIGN
#define SORTER_DESIGN

#include "SorterCU.h"
#include "SorterDP.h"

class SorterDesign
{
	bus *clk, *rst, *start, *ready;
	bus *Result;

	// internal nodes
	bus ldTemp,  ldMin,  ldMinAddress;
	bus ldcounter2,  Cnt1,  Cnt2,  SelMinTemp,  SelInMin,  SelOctaCount,  SelAddr;
	bus co1, co2, lt;
	bus rstResultReg, initResultReg, loadResultReg;
	bus enCounter, rstCounter, initCounter;
	bus co, read;
    bus Read, Write;

	// module
	SorterDP* DP;
	SorterCU* CU;
	public:
		SorterDesign (bus &clk, bus &rst, bus &start,
                     bus &ready, bus&Result);
		~SorterDesign();
		void evl();
		void initialize (const string& filename);
};

#endif
