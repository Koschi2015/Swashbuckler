// Aufz�hlung von Prim�ren Eigenschaften
enum en_PrimaryAttributs { PA_KOERPERKRAFT,
                           PA_INTELLIGENZ,
                           PA_REFLEXE,
                           PA_KOORDINATION,
                           PA_LAST};

// Aufz�hlung von Sekund�ren Eigenschaften
enum en_SecundaryAttributs { SA_LEBENSPUNKTE,
                             SA_MAGIEPUNKTE,
                             SA_TRAGKRAFT,
                             SA_LAST};

// Aufz�hlung von Negativen Eigenschaften
enum en_NegativAttributs { NA_ABERGLAUBE,
                           NA_LAST};

// Aufz�hlung von Skills
enum en_Skills { SK_KAMPF_WAFFENLOS,
                 SK_KAMPF_SCHWERT,
                 SK_KAMPF_DOLCH,
                 SK_LAST};

// Struktur Prim�re Eigenschaft
struct St_PrimaryAttributs { en_PrimaryAttributs PrimaryAttribut;
                             short Value;
                             short tempValue;};

// Struktur Sekund�re Eigenschaft
struct St_SecundaryAttributs { en_SecundaryAttributs SecundaryAttribut;
                               short Value;
                               short tempValue;};

// Struktur Negative Eigenschaft
struct St_NegativAttributs { en_NegativAttributs NegativAttribut;
                             short Value;
                             short tempValue;};

// Struktur Skill
struct St_Skills { en_Skills Skill;
                   short Value;
                   short tempValue;};

// Charakter klasse
class CCharakter
{
protected:
    // Array mit den Prim�ren Attributen
    St_PrimaryAttributs PrimaryAttributs[static_cast <int>(PA_LAST)];
    // Array mit den Sekund�ren Attributen
    St_SecundaryAttributs SecundaryAttributs[static_cast <int>(SA_LAST)];
    // Array mit den Negativen Attributen
    St_NegativAttributs NegativAttributs[static_cast <int>(NA_LAST)];
    // Array mit den Skills
    St_Skills Skill[static_cast <int>(SK_LAST)];
public:
    // Setzt den Basiswert eines Prim�res Attribut auf einen Wert
    void Set_base_PrimaryAttribut(en_PrimaryAttributs Attribut,short nValue);
    // Setzt den Basiswert eines Skund�res Attribut auf einen Wert
    void Set_base_SecundaryAttribut(en_SecundaryAttributs Attribut,short nValue);
    // Setzt den Basiswert eines Negatives Attribut auf einen Wert
    void Set_base_NegativeAttribut(en_NegativAttributs Attribut,short nValue);
    // Setzt den Basiswert eines Skills auf einen Wert
    void Set_base_Skill(en_Skills Attribut,short nValue);
    // Setzt ein tempor�res Prim�res Attribut auf einen Wert
    void Set_temp_PrimaryAttribut(en_PrimaryAttributs Attribut,short ntempValue);
    // Setzt ein tempor�res Skund�res Attribut auf einen Wert
    void Set_temp_SecundaryAttribut(en_SecundaryAttributs Attribut,short ntempValue);
    // Setzt ein tempor�res Negatives Attribut auf einen Wert
    void Set_temp_NegativeAttribut(en_NegativAttributs Attribut,short ntempValue);
    // Setzt ein tempor�ren Skill auf einen Wert
    void Set_temp_Skill(en_Skills Attribut,short ntempValue);
    // Gibt den Basiswert des Prim�r Attributes zur�ck
    short Get_base_PrimaryAttribut(en_PrimaryAttributs Attribut) {return PrimaryAttributs[static_cast <int>(Attribut)].Value;}
    // Gibt den Basiswert des Sekund�r Attributes zur�ck
    short Get_base_SecundaryAttribut(en_SecundaryAttributs Attribut) {return SecundaryAttributs[static_cast <int>(Attribut)].Value;}
    // Gibt den Basiswert des Negativ Attributes zur�ck
    short Get_base_PrimaryAttribut(en_NegativAttributs Attribut) {return NegativAttributs[static_cast <int>(Attribut)].Value;}
    // // Gibt den Basiswert des des zur�ck
    short Get_base_Skill(en_Skills Attribut) {return Skill[static_cast <int>(Attribut)].Value;}
    // Gibt den tempor�ren Wert des Prim�r Attributes zur�ck
    short Get_temp_PrimaryAttribut(en_PrimaryAttributs Attribut) {return PrimaryAttributs[static_cast <int>(Attribut)].tempValue;}
    // Gibt den tempor�ren Wert des Sekund�r Attributes zur�ck
    short Get_temp_SecundaryAttribut(en_SecundaryAttributs Attribut) {return SecundaryAttributs[static_cast <int>(Attribut)].tempValue;}
    // Gibt den tempor�ren Wert des Negativ Attributes zur�ck
    short Get_temp_PrimaryAttribut(en_NegativAttributs Attribut) {return NegativAttributs[static_cast <int>(Attribut)].tempValue;}
    // // Gibt den tempor�ren Wert des Skills zur�ck
    short Get_temp_Skill(en_Skills Attribut) {return Skill[static_cast <int>(Attribut)].tempValue;}
    // Gibt den Gesamtwert des Prim�r Attributes zur�ck
    short Get_comp_PrimaryAttribut(en_PrimaryAttributs Attribut) {return PrimaryAttributs[static_cast <int>(Attribut)].tempValue + PrimaryAttributs[static_cast <int>(Attribut)].Value;}
    // Gibt den Gesamtwert des Sekund�r Attributes zur�ck
    short Get_comp_SecundaryAttribut(en_SecundaryAttributs Attribut) {return SecundaryAttributs[static_cast <int>(Attribut)].tempValue + SecundaryAttributs[static_cast <int>(Attribut)].Value;}
    // Gibt den Gesamtwert des Negativ Attributes zur�ck
    short Get_comp_NegativAttribut(en_NegativAttributs Attribut) {return NegativAttributs[static_cast <int>(Attribut)].tempValue + NegativAttributs[static_cast <int>(Attribut)].Value;}
    // Gibt den Gesamtwert des des zur�ck
    short Get_comp_Skill(en_Skills Attribut) {return Skill[static_cast <int>(Attribut)].tempValue + Skill[static_cast <int>(Attribut)].Value;}
    // Konstruktor
    CCharakter();
    // Destruktor
    virtual ~CCharakter();
};
