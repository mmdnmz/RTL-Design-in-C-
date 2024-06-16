main.exe : utilities.exe SorterTB.exe SorterDesign.exe SorterDP.exe SorterCU.exe classVectorPrimitives.exe  extraClassPrimitives.exe
	g++  utilities.exe SorterTB.exe SorterDesign.exe SorterDP.exe SorterCU.exe classVectorPrimitives.exe -o main.exe
SorterTB.exe : SorterDesign.h SorterTB.cpp
	g++ -c SorterTB.cpp -o SorterTB.exe
SorterDesign.exe : SorterDesign.cpp SorterDesign.h SorterCU.h SorterDP.h
	g++ -c SorterDesign.cpp -o SorterDesign.exe
SorterDP.exe: SorterDP.cpp SorterDP.h classVectorPrimitives.h
	g++ -c SorterDP.cpp -o SorterDP.exe
SorterCU.exe: SorterCU.cpp SorterCU.h classVectorPrimitives.h
	g++ -c SorterCU.cpp -o SorterCU.exe
extraClassPrimitives.exe: extraClassPrimitives.cpp extraClassPrimitives.h classVectorPrimitives.h 
	g++ -c extraClassPrimitives.cpp -o extraClassPrimitives.exe
classVectorPrimitives.exe: classVectorPrimitives.cpp classVectorPrimitives.h utilityFunctions.h 
	g++ -c classVectorPrimitives.cpp -o classVectorPrimitives.exe
utilities.exe : utilityFunctions.h utilityFunctions.cpp
	g++ -c utilityFunctions.cpp -o utilities.exe
clean:
	del *.o
	del *.exe