#include "SorterDP.h"

SorterDP::SorterDP(bus& clk_, bus& rst_,
						bus& Write_, bus&Read_,
			 			bus& ldTemp_, bus& ldMin_, bus& ldMinAddress_,
						bus& ldcounter2_, bus& Cnt1_, bus& Cnt2_, bus& SelMinTemp_,
				     	bus& SelInMin_, bus& SelOctaCount_, bus& SelAddr_,
						bus& co1_, bus& co2_ ,
						bus& Result_)
					:
						clk(&clk_), rst(&rst_),
						Write(&Write_), Read(&Read_),
						ldTemp(&ldTemp_), ldMin(&ldMin_), ldMinAddress(&ldMinAddress_),
						ldcounter2(&ldcounter2_), Cnt1(&Cnt1_), Cnt2(&Cnt2_), SelMinTemp(&SelMinTemp_),
						SelInMin(&SelInMin_), SelOctaCount(&SelOctaCount_), SelAddr(&SelAddr_),
						co1(&co1_), co2(&co2_),
						Result(&Result_)
{
	// internal buses:
	ReadData = "XXXXXXXXXXXXXXXX";
	WriteData = "XXXXXXXXXXXXXXXX";
	Address = "XXXXXXXXXXXXXXXX";
	tempOut = "XXXXXXXXXXXXXXXX";
	minOut  =  "XXXXXXXXXXXXXXXX";
	minAddrOut = "XXXXXXXXXXXXXXXX";
	cnt2Out = "XXXXXXXX";
	cnt1Out = "XXXXXXXX";
	incOut = "XXXXXXXX";
	muxOctaCountOut = "XXXXXXXX";
	inminOut = "XXXXXXXXXXXXXXXX";
	hardOne = "1";
	hardZero = "00000000";
	monoHardzero = "0";
	eq = "X";
	gt = "X";
	lt = "X";
	loadMin = "X";
	loadMinAddr = "X";
	cnt2En = "X";
	Enabler = "X";
	placeHolders = "X";

	tempReg = new dRegisterRaE(ReadData, *clk, *rst, *ldTemp, tempOut);

	minReg = new dRegisterRaE(inminOut, *clk, *rst, loadMin, minOut);

	minAddrReg = new dRegisterRaE(muxOctaCountOut, *clk, *rst, loadMinAddr, minAddrOut);


	mintemp = new Mux(tempOut, minOut, *SelMinTemp, WriteData);

	inmin = new Mux(minOut, ReadData, *SelInMin, inminOut);

	octaCount = new Mux(cnt1Out, cnt2Out, *SelOctaCount, muxOctaCountOut);

	addr = new Mux(muxOctaCountOut, minAddrOut, *SelAddr, Address);

	minRead = new Comparator(ReadData, minOut, lt, eq, gt);

	counter1 = new upCounterRaE(hardZero, *clk, *rst, monoHardzero, *Cnt1, cnt1Out);

	counter2 = new upCounterRaE(cnt1Out, *clk, *rst, *ldcounter2, *Cnt2, cnt2Out);

	dataMemory = new Memory (*rst, *clk, *Read, *Write, WriteData, Address, ReadData, 256) ;
}

void SorterDP::evl()
{

	//cout << "DP evaled" << endl;
	counter1 -> evl();

	incOut = cnt1Out + "00000001";
	//cout <<"incout = " << incOut << endl;

	// cnt2En = *Cnt2;

	// Enabler = *ldcounter2;

	// if ((*Cnt2 == "1")||(*ldcounter2 == "1"))
	// {
	// 	placeHolders = "1";
	// }
	//placeHolders = (*Cnt2 | *ldcounter2);
	cnt2En = *ldcounter2;

	//cout <<"cnt1 = " << cnt1Out << endl;
	counter2 -> evl();
		if (cnt1Out == "11111111")
	{
		*co1 = "1";
	}
	else
	{
		*co1 = "0";
	}
	if (cnt2Out == "11111111")
	{
		*co2 = "1";
	}
		else
	{
		*co2 = "0";
	}

	//counter2 -> evl();


	//cout <<"count 2 = "<<cnt2Out<<endl;

	//cout <<"co2 = " << *co2 << endl;

	octaCount ->evl();

	minAddrReg ->evl();

	addr ->evl();

	dataMemory ->evl();

	minRead  ->evl();
	
	loadMin = (lt | *ldMin);


	loadMinAddr = (lt | *ldMin);

	inmin ->evl();

	minAddrReg ->evl();

	minReg ->evl();

	tempReg ->evl();

	mintemp ->evl();

	dataMemory ->evl();
	*Result = WriteData;
	

	cout << "loadMin "<< loadMin <<" lt "<<lt<<" " << " ldMin "<< *ldMin<<" " << " loadminaddr " <<loadMinAddr<<" "<< endl;
	cout << "minOut  	 = " << minOut << endl;
	cout << "ReadData	 = " <<ReadData<<endl;
	cout << "Address     = " <<Address<<endl;
	cout << "count 2 out = " <<cnt2Out<<endl;
	cout << "input counter 2 = " <<incOut<<endl;
	cout << "rst is = "<<*rst<<endl;
	cout << "load is = " <<*ldcounter2<<endl;
	cout <<"cnt2 is = "<<*Cnt2<<endl;
	cout <<"cnt2Out = " << cnt2Out<<endl;

//	incOut, *clk, *rst, *ldcounter2, *Cnt2, cnt2Out);


//	cout << "result = " <<*Result<<endl;
//	cout << "inminOut "<< inminOut<< " loadMin " << loadMin<< " minOut "<<minOut<<endl;
//	cout << "load min reg = " << loadMin<<endl;

//	cout << "minOut "<<minOut<<endl;

//	cout << "ReadData	= " << ReadData<< " *ldTemp " <<*ldTemp<<" tempOut "<< tempOut<<endl;

//	cout << "selminaddr = "<<*SelAddr<<endl;
	
	cout <<"muxOctaCountOut = "<<muxOctaCountOut<<" muxOcta sel = "<<*SelOctaCount<<endl;
	
//	cout <<muxOctaCountOut<< endl<<"minAddrOut "<<minAddrOut << endl;

//	cout << "Write data "<< WriteData<<endl;
	
//	cout<< "at Address " << Address<<" ? "<<*Write<<endl;

	cout << "SelAddr = "<<*SelAddr<<endl;

//	cout <<"Min Addr is = "<<minAddrOut<<endl;

	cout << "count 1 = " << cnt1Out<<" , And co1 = "<<*co1<<endl;
	
	

	}

// countr1 
// inc 
// counter2

// octamux
// addrreg
// addrmux
// memmory
// Comparator
// inmin Mux

// minadd
// minreg
// temp reg
// mintempmux
// memmory
