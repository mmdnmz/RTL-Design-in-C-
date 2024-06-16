#ifndef SORTER_CU
#define SORTER_CU

#include "classVectorPrimitives.h"
#include <string>
using namespace std;

class SorterCU {
	bus* clk, * rst;
	bus *co1, *co2;
	bus* Read, *Write;
	bus* start, * ready;
	bus* ldTemp, * ldMin, * ldMinAddress;
	bus* ldcounter2, * Cnt1, * Cnt2;
	bus* SelMinTemp, * SelInMin, * SelOctaCount, * SelAddr;
	int Nstate, Pstate;
public:
	SorterCU(bus& clk, bus&rst,
				bus& start, bus& ready,
				bus&Read, bus& Write,
				bus& ldTemp, bus& ldMin, bus& ldMinAddress,
				bus& ldcounter2, bus& Cnt1, bus& Cnt2, bus& SelMinTemp,
				bus& SelInMin, bus& SelOctaCount, bus& SelAddr,
				bus& co1, bus& co2
				);
	~SorterCU();
	void evl();
};

#endif
