
#include <iostream>
#include <bitset>
#include <cctype>
#include <cassert>
int main()
{
	const std::uint16_t PolynomicalEquation = 0xC599;   //x^15 + x^14 + x^10+x^8 +x^7 +x^4 + x^3 + 1

	std::bitset<15> l_PecValue;							//Bitset for generated PEC
	l_PecValue[4] = 1;								    //Init value from datasheet (0000 0000 0010 0000)

	std::bitset<7>  l_InValues;							// IN0 IN3 IN 4 IN 7 IN 8 IN 10 IN 14 

	std::bitset<16> l_Din{ 0x0001 };					//Data value for generate PEC, for example in datasheet - 0x0001;
	
	for (int i = 15; i >= 0; i--) 
	{
	//Set Data
	l_InValues[0] = l_Din[i] ^ l_PecValue[14];			// IN 0
	l_InValues[1] = l_InValues[0] ^ l_PecValue[2];		// IN 3
	l_InValues[2] = l_InValues[0] ^ l_PecValue[3];		// IN 4
	l_InValues[3] = l_InValues[0] ^ l_PecValue[6];		// IN 7
	l_InValues[4] = l_InValues[0] ^ l_PecValue[7];		// IN 8
	l_InValues[5] = l_InValues[0] ^ l_PecValue[9];		// IN 10
	l_InValues[6] = l_InValues[0] ^ l_PecValue[13];		// IN 14
	
	//Update registers in PEC
	l_PecValue[14] = l_InValues[6];						//PEC[14] = IN 14
	l_PecValue[13] = l_PecValue[12];					//PEC[13] = PEC[12]
	l_PecValue[12] = l_PecValue[11];					//PEC[12] = PEC[11]
	l_PecValue[11] = l_PecValue[10];					//PEC[11] = PEC[10]
	l_PecValue[10] = l_InValues[5];						//PEC[10] = IN 10
	l_PecValue[9] = l_PecValue[8];						//PEC[9]  = PEC[8]
	l_PecValue[8] = l_InValues[4];						//PEC[8]  = IN 8
	l_PecValue[7] = l_InValues[3];						//PEC[7]  = IN 7 
	l_PecValue[6] = l_PecValue[5];						//PEC[6]  = PEC[5]
	l_PecValue[5] = l_PecValue[4];						//PEC[5]  = PEC[4]
	l_PecValue[4] = l_InValues[2];						//PEC[4]  = IN 4
	l_PecValue[3] = l_InValues[1];						//PEC[3]  = IN 3
	l_PecValue[2] = l_PecValue[1];						//PEC[2]  = PEC[1]
	l_PecValue[1] = l_PecValue[0];						//PEC[1]  = PEC[0]
	l_PecValue[0] = l_InValues[0];						//PEC[0]  = IN 0

	}
	//std::uint16_t expectedConversationResult = l_;

	//Add 0 to  LSB position and reverse the bitset.
	
	const std::bitset<16> expectedBitset = 0x3D6E; // Datasheet sample for computed CRC

	std::bitset<16> l_tempSet;
	for ( int i = 0; i <= l_PecValue.size() - 1 ; i++) 
	{
		l_tempSet[i+1] = l_PecValue[i];
	}
	
	//Expect the example result - 0x3D6E
	assert(l_tempSet == expectedBitset);
    
	return 0;
}

