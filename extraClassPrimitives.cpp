// Do not add to project
// Contents of this file are included, does not compile independently

////////////////////////////////// Somayeh inserted/////////////////////////////
#include "extraClassPrimitives.h"
// #include "classVectorPrimitives.h"	
#include <cmath>


extern bus bval(int a, int size){
	bus result(size);
	for (int i = 0; i<size; i++)
	{
		if (a%2 == 1) result[i] = '1';
		else result[i] = '0';
		a = a/2;
	}
	return result;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Somayeh inserted////////////////////////////////
extern double fval (bus v)
{
	int aSize = v.length();
	double ia=0.0;
	for (int i = 0; i < aSize; i++) {
		if (v.at(i) == "1") ia = ia + double( pow((2.0), (-1*(aSize-i)) ));
	}
	return ia;
}

//////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
