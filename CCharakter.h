// Aufzählung von Primären Eigenschaften
enum en_PrimaryAttributs { PA_KOERPERKRAFT,
                           PA_INTELLIGENZ,
                           PA_REFLEXE,
                           PA_KOORDINATION,
                           PA_LAST};

// Aufzählung von Sekundären Eigenschaften
enum en_SecundaryAttributs { SA_LEBENSPUNKTE,
                             SA_MAGIEPUNKTE,
                             SA_TRAGKRAFT,
                             SA_LAST};

// Aufzählung von Negativen Eigenschaften
enum en_NegativAttributs { NA_ABERGLAUBE,
                           NA_LAST};

// Aufzählung von Skills
enum en_Skills { SK_KAMPF_WAFFENLOS,
                 SK_KAMPF_SCHWERT,
                 SK_KAMPF_DOLCH,
                 SK_LAST};

// Struktur Primäre Eigenschaft
struct St_PrimaryAttributs { en_PrimaryAttributs PrimaryAttribut;
                             short Value;
                             short tempValue;};

// Struktur Sekundäre Eigenschaft
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
    // Array mit den Primären Attributen
    St_PrimaryAttributs PrimaryAttributs[static_cast <int>(PA_LAST)];
    // Array mit den Sekundären Attributen
    St_SecundaryAttributs SecundaryAttributs[static_cast <int>(SA_LAST)];
    // Array mit den Negativen Attributen
    St_NegativAttributs NegativAttributs[static_cast <int>(NA_LAST)];
    // Array mit den Skills
    St_Skills Skill[static_cast <int>(SK_LAST)];
public:
    // Setzt den Basiswert eines Primäres Attribut auf einen Wert
    void Set_base_PrimaryAttribut(en_PrimaryAttributs Attribut,short nValue);
    // Setzt den Basiswert eines Skundäres Attribut auf einen Wert
    void Set_base_SecundaryAttribut(en_SecundaryAttributs Attribut,short nValue);
    // Setzt den Basiswert eines Negatives Attribut auf einen Wert
    void Set_base_NegativeAttribut(en_NegativAttributs Attribut,short nValue);
    // Setzt den Basiswert eines Skills auf einen Wert
    void Set_base_Skill(en_Skills Attribut,short nValue);
    // Setzt ein temporäres Primäres Attribut auf einen Wert
    void Set_temp_PrimaryAttribut(en_PrimaryAttributs Attribut,short ntempValue);
    // Setzt ein temporäres Skundäres Attribut auf einen Wert
    void Set_temp_SecundaryAttribut(en_SecundaryAttributs Attribut,short ntempValue);
    // Setzt ein temporäres Negatives Attribut auf einen Wert
    void Set_temp_NegativeAttribut(en_NegativAttributs Attribut,short ntempValue);
    // Setzt ein temporären Skill auf einen Wert
    void Set_temp_Skill(en_Skills Attribut,short ntempValue);
    // Gibt den Basiswert des Primär Attributes zurück
    short Get_base_PrimaryAttribut(en_PrimaryAttributs Attribut) {return PrimaryAttributs[static_cast <int>(Attribut)].Value;}
    // Gibt den Basiswert des Sekundär Attributes zurück
    short Get_base_SecundaryAttribut(en_SecundaryAttributs Attribut) {return SecundaryAttributs[static_cast <int>(Attribut)].Value;}
    // Gibt den Basiswert des Negativ Attributes zurück
    short Get_base_PrimaryAttribut(en_NegativAttributs Attribut) {return NegativAttributs[static_cast <int>(Attribut)].Value;}
    // // Gibt den Basiswert des des zurück
    short Get_base_Skill(en_Skills Attribut) {return Skill[static_cast <int>(Attribut)].Value;}
    // Gibt den temporären Wert des Primär Attributes zurück
    short Get_temp_PrimaryAttribut(en_PrimaryAttributs Attribut) {return PrimaryAttributs[static_cast <int>(Attribut)].tempValue;}
    // Gibt den temporären Wert des Sekundär Attributes zurück
    short Get_temp_SecundaryAttribut(en_SecundaryAttributs Attribut) {return SecundaryAttributs[static_cast <int>(Attribut)].tempValue;}
    // Gibt den temporären Wert des Negativ Attributes zurück
    short Get_temp_PrimaryAttribut(en_NegativAttributs Attribut) {return NegativAttributs[static_cast <int>(Attribut)].tempValue;}
    // // Gibt den temporären Wert des Skills zurück
    short Get_temp_Skill(en_Skills Attribut) {return Skill[static_cast <int>(Attribut)].tempValue;}
    // Gibt den Gesamtwert des Primär Attributes zurück
    short Get_comp_PrimaryAttribut(en_PrimaryAttributs Attribut) {return PrimaryAttributs[static_cast <int>(Attribut)].tempValue + PrimaryAttributs[static_cast <int>(Attribut)].Value;}
    // Gibt den Gesamtwert des Sekundär Attributes zurück
    short Get_comp_SecundaryAttribut(en_SecundaryAttributs Attribut) {return SecundaryAttributs[static_cast <int>(Attribut)].tempValue + SecundaryAttributs[static_cast <int>(Attribut)].Value;}
    // Gibt den Gesamtwert des Negativ Attributes zurück
    short Get_comp_NegativAttribut(en_NegativAttributs Attribut) {return NegativAttributs[static_cast <int>(Attribut)].tempValue + NegativAttributs[static_cast <int>(Attribut)].Value;}
    // Gibt den Gesamtwert des des zurück
    short Get_comp_Skill(en_Skills Attribut) {return Skill[static_cast <int>(Attribut)].tempValue + Skill[static_cast <int>(Attribut)].Value;}
    // Konstruktor
    CCharakter();
    // Destruktor
    virtual ~CCharakter();
};
