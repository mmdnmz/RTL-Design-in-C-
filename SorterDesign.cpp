#include "SorterDesign.h"
#include <chrono>
#include <thread>


SorterDesign::SorterDesign(bus &clk_, bus &rst_, bus &start_, bus &ready_, bus&Result_)
                        :
			            clk(&clk_), rst(&rst_), start(&start_), ready(&ready_), Result(&Result_)
{
	DP = new SorterDP(* clk, * rst,
					 Write, Read,
                     ldTemp,  ldMin,  ldMinAddress,
                     ldcounter2,  Cnt1,  Cnt2,  SelMinTemp,  SelInMin,  SelOctaCount,  SelAddr,
                     co1, co2,
					 *Result);
	CU = new SorterCU (*rst, *clk, *start, *ready,
                     Read, Write,
                     ldTemp,  ldMin,  ldMinAddress,
                     ldcounter2,  Cnt1,  Cnt2,  SelMinTemp,  SelInMin,  SelOctaCount,  SelAddr,
                     co1, co2);
}
void SorterDesign::evl()
{
	DP -> evl();
	
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
	CU -> evl();
	//cout <<"/*...............*/"<<endl<<endl<<endl;
}
void SorterDesign::initialize(const string& filename)
{
	//resetting
	*rst = "1";
	DP -> evlMemory();
	DP -> evl();
	CU -> evl();
	*rst = "0";
	//Initialize fractionsMemory and dump
	DP -> initMemory (filename);
	DP -> dumpMemory ("beforeFile.txt");
}

