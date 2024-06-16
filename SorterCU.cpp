#include "SorterCU.h"

SorterCU::SorterCU (bus& rst_, bus& clk_,
	bus& start_, bus& ready_,
    bus&Read_, bus& Write_,
	bus& ldTemp_, bus& ldMin_,
	bus& ldMinAddress_, bus& ldcounter2_, bus& Cnt1_,
	bus& Cnt2_,
	bus& SelMinTemp_, bus& SelInMin_, bus& SelOctaCount_,
	bus& SelAddr_,
    bus& co1_, bus& co2_
    )
    :
	 clk(&clk_), rst(&rst_),
	start(&start_), ready(&ready_),
    Read(&Read_), Write(&Write_),
	ldTemp(&ldTemp_), ldMin(&ldMin_),
	ldMinAddress(&ldMinAddress_), ldcounter2(&ldcounter2_), Cnt1(&Cnt1_),
	Cnt2(&Cnt2_),
	SelMinTemp(&SelMinTemp_), SelInMin(&SelInMin_),
	SelOctaCount(&SelOctaCount_),
	SelAddr(&SelAddr_),
    co1(&co1_), co2(&co2_)
	{
		Nstate = 0;
		Pstate= 0;
	}

void SorterCU::evl () {
	*ready = "0";
	*ldTemp = "0";
	*ldcounter2 = "0";
	*Cnt1 = "0";
	*Cnt2 = "0";
	*SelMinTemp = "0";
	*SelInMin = "0";
	*SelOctaCount = "0";
	*SelAddr = "0";
    *Read = "0";
    *Write = "0";
	*ldMin = "0";
	*ldMinAddress = "0";
	cout <<"----------------------------------------------------------------------------"<<endl<<endl;
	cout<<"pstate is "<<Pstate<<endl;
	switch (Pstate){
		case 0: //Idle
			if( *start == "1" )	Nstate = 1;
			else Nstate = 0;
			break;
		case 1: //Init
			if( *start == "1" ) Nstate = 1;
			else Nstate = 2;
			break;
		case 2: //Get_Min_Reg
			Nstate =8;
			break;
		case 3: //Comp.
            if (*co2 == "1") Nstate = 4;
            else Nstate = 3;
			break;
		case 4: //Update0
			Nstate = 5;
			break;
		case 5: //Update1
			Nstate = 6;
			break;
		case 6: //Update2
            if (*co1 == "0") Nstate = 2;
            else if (*co1 == "1") Nstate = 7;
            else Nstate = 6;
			break;
		case 7: //Ready
			if(*start == "0") Nstate = 0;
			else Nstate = 1;
			break;
		case 8: //Dummy
			Nstate = 3;
            break;
	 }
	 switch (Pstate){
		case 0 : //INITIALIZE
			 break;
		case 1: //Init
			//cout << "State init" << endl;

			break;
		case 2: //Get_Min_Reg
			*ldcounter2 = "1";
			//*Cnt2 = "1";
			*SelOctaCount = "0";
			*SelAddr = "0";
            *ldMin = "1";
			*SelInMin = "1";
            *ldMinAddress = "1";
            *Read = "1";
			break;
		case 3 : //Comp.
			*SelOctaCount = "1";
			*SelAddr = "0";
			*SelInMin = "1";
			*Cnt2 = "1";
			*Read = "1";
			break;
		case 4: //Update0
			*SelOctaCount = "0";
			*SelAddr = "0";
            *ldTemp = "1";
            *Read = "1";
			break;
		case 5: //Update1
			*SelAddr = "0";
			*SelInMin = "0";
            *SelMinTemp = "1";
			*SelOctaCount = "0";
			*Write = "1";
			break;
		case 6: //Update2
			*SelAddr = "1";
            *SelMinTemp = "0";
			*Cnt1 = "1";
			*Write = "1";
			*ldcounter2 = "1";
			break;
		case 7: //Ready
			*ready = "1";
			cout << "Ready" << endl;
			break;
		case 8: //Dummy
			*SelOctaCount = "1";
			*ldcounter2 = "1";
			*Cnt2 = "1";
			break;
	 }
	 if (*rst == "1") Pstate = 0;
	 else if (*clk == "P") Pstate = Nstate;
}