#include "CCharakter.h"

CCharakter::CCharakter()
{
    for(int i = 0;i<static_cast<int>(PA_LAST);i++)
    {
        CCharakter::PrimaryAttributs[i].PrimaryAttribut = static_cast<en_PrimaryAttributs>(i);
        CCharakter::PrimaryAttributs[i].tempValue = 0;
        CCharakter::PrimaryAttributs[i].Value = 0;
    }
    for(int i = 0;i<static_cast<int>(SA_LAST);i++)
    {
        CCharakter::SecundaryAttributs[i].SecundaryAttribut = static_cast<en_SecundaryAttributs>(i);
        CCharakter::SecundaryAttributs[i].tempValue = 0;
        CCharakter::SecundaryAttributs[i].Value = 0;
    }
    for(int i = 0;i<static_cast<int>(NA_LAST);i++)
    {
        CCharakter::NegativAttributs[i].NegativAttribut = static_cast<en_NegativAttributs>(i);
        CCharakter::NegativAttributs[i].tempValue = 0;
        CCharakter::NegativAttributs[i].Value = 0;
    }
    for(int i = 0;i<static_cast<int>(SK_LAST);i++)
    {
        CCharakter::Skill[i].Skill = static_cast<en_Skills>(i);
        CCharakter::Skill[i].tempValue = 0;
        CCharakter::Skill[i].Value = 0;
    }
}
CCharakter::~CCharakter()
{

}
void CCharakter::Set_base_PrimaryAttribut(en_PrimaryAttributs Attribut,short nValue)
{
    if(Attribut == PA_LAST)
    {
        return;
    }
    else
    {
        PrimaryAttributs[static_cast<int>(Attribut)].Value = nValue;
    }
}
void CCharakter::Set_base_SecundaryAttribut(en_SecundaryAttributs Attribut,short nValue)
{
    if(Attribut == SA_LAST)
    {
        return;
    }
    else
    {
        SecundaryAttributs[static_cast<int>(Attribut)].Value = nValue;
    }
}
void CCharakter::Set_base_NegativeAttribut(en_NegativAttributs Attribut,short nValue)
{
    if(Attribut == NA_LAST)
    {
        return;
    }
    else
    {
        NegativAttributs[static_cast<int>(Attribut)].Value = nValue;
    }
}
void CCharakter::Set_base_Skill(en_Skills Attribut,short nValue)
{
    if(Attribut == SK_LAST)
    {
        return;
    }
    else
    {
        Skill[static_cast<int>(Attribut)].Value = nValue;
    }
}
void CCharakter::Set_temp_PrimaryAttribut(en_PrimaryAttributs Attribut,short ntempValue)
{
    if(Attribut == PA_LAST)
    {
        return;
    }
    else
    {
        PrimaryAttributs[static_cast<int>(Attribut)].tempValue = ntempValue;
    }
}
void CCharakter::Set_temp_SecundaryAttribut(en_SecundaryAttributs Attribut,short ntempValue)
{
    if(Attribut == SA_LAST)
    {
        return;
    }
    else
    {
        SecundaryAttributs[static_cast<int>(Attribut)].tempValue = ntempValue;
    }
}
void CCharakter::Set_temp_NegativeAttribut(en_NegativAttributs Attribut,short ntempValue)
{
    if(Attribut == NA_LAST)
    {
        return;
    }
    else
    {
        NegativAttributs[static_cast<int>(Attribut)].tempValue = ntempValue;
    }
}
void CCharakter::Set_temp_Skill(en_Skills Attribut,short ntempValue)
{
    if(Attribut == SK_LAST)
    {
        return;
    }
    else
    {
        Skill[static_cast<int>(Attribut)].tempValue = ntempValue;
    }
}
