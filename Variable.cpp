#include "Variable.h"

// ^^x
// void CVariable::SetName
// 3BGO NTP-1 09-10-2020
void CVariable::SetName( const std::string& oNameString )
{
    m_oNameString = oNameString;
}

// ^^x
// const std::string& CVariable::GetName
// 3BGO NTP-1 09-10-2020
const std::string& CVariable::GetName() const
{
    return m_oNameString;
}

// ^^x
// void CVariable::SetType
// 3BGO NTP-1 09-10-2020
void CVariable::SetType( const std::string& oTypeString )
{
    m_oTypeString = oTypeString;
}

// ^^x
// const std::string& CVariable::GetType
// 3BGO NTP-1 09-10-2020
const std::string& CVariable::GetType() const
{
    return m_oTypeString;
}

// ^^x
// void CVariable::SetReferenceType
// 3BGO NTP-1 28-10-2020
void CVariable::SetReferenceType( const EReferenceType eReferenceType )
{
    m_eReferenceType = eReferenceType;
}

// ^^x
// std::optional<CVariable::EReferenceType> CVariable::GetReferenceType
// 3BGO NTP-1 28-10-2020
std::optional<CVariable::EReferenceType> CVariable::GetReferenceType() const
{
    return m_eReferenceType;
}

// ^^x
// bool CVariable::SetArrayType
// 3BGO NTP-1 28-10-2020
void CVariable::SetArrayType( const bool bIsArrayType )
{
    m_bIsArrayType = bIsArrayType;
}

// ^^x
// bool CVariable::IsArrayType
// 3BGO NTP-1 28-10-2020
bool CVariable::IsArrayType() const
{
    return m_bIsArrayType;
}
