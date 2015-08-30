#include "Misc.h"

en_Relationship** CFaction::FactionTable = 0;
unsigned int CFaction::ClassCounter = 0;

CFaction::CFaction()
{
    ClassCounter++;
    if(ClassCounter == 1)
    {
        FactionTable = new en_Relationship*[FAC_COUNTER];
        // erstellen eines 2D array pro schleife wird das 2te Element um eins kleiner
        // dadurch entsteht eine Dreiecksform
        for (int i = 0;i<FAC_COUNTER;i++)
        {
            FactionTable[i] = new en_Relationship[FAC_COUNTER-i];
            FactionTable[i][FAC_COUNTER-i] = RS_NEUTRAL;
        }
    }
}
CFaction::~CFaction()
{
    ClassCounter--;
    if(ClassCounter == 0)
    {
        for (int i = 0;i<FAC_COUNTER;i++)
        {
            delete[] FactionTable[i];
        }
        delete[] FactionTable;
        FactionTable = 0;
    }
}
void CFaction::Set_Relationship(en_Faction FactionOne,en_Faction FactionTwo,en_Relationship Relationship)
{
    if(ClassCounter == 0)
    {
        return;
    }
    else
    {
        if(FactionTwo < FactionOne)
        {
            en_Faction TempFaction = FactionOne;
            FactionOne = FactionTwo;
            FactionTwo = TempFaction;
        }
        FactionTable[FactionOne][FactionTwo] = Relationship;
    }
}
en_Relationship CFaction::Get_Relationship(en_Faction FactionOne,en_Faction FactionTwo)
{
    if(ClassCounter == 0)
    {
        return RS_FAIL;
    }
    else
    {
        if(FactionTwo < FactionOne)
        {
            en_Faction TempFaction = FactionOne;
            FactionOne = FactionTwo;
            FactionTwo = TempFaction;
        }
        return FactionTable[FactionOne][FactionTwo];
    }
    return RS_FAIL;
}
