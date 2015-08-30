#ifndef MISC_H
#define MISC_H

// Fraktion die zur Auswahl stehen
enum en_Faction {FAC_PLAYER,
                 FAC_MONSTER,
                 //... Hier Zwischen können neue Fraktionen Eingetragen werden
                 FAC_COUNTER};
// Zustände die zwischen 2 Fraktionen herrschen können
enum en_Relationship {RS_FRIENDLY,
                      RS_NEUTRAL,
                      RS_HOSTIL,
                      RS_FAIL};

class CFaction
{
private:
    //
    en_Faction MyFaction;
    //
    static en_Relationship** FactionTable;
    //
    static unsigned int ClassCounter;
public:
    //
    void Set_Faction(en_Faction NewFaction) {MyFaction = NewFaction;}
    //
    en_Faction Get_Faction() {return MyFaction;}
    //
    static en_Relationship Get_Relationship(en_Faction FactionOne,en_Faction FactionTwo);
    //
    static void Set_Relationship(en_Faction FactionOne,en_Faction FactionTwo,en_Relationship Relationship);
    //
    CFaction();
    //
    ~CFaction();
};

#endif
