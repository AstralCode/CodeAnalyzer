#include "Variable.h"

// ^^x
// void CVariable::SetName
// 3BGO JIRA-238 09-10-2020
void CVariable::SetName( const std::string& oNameString )
{
    m_oNameString = oNameString;
}

// ^^x
// std::string CVariable::GetName
// 3BGO JIRA-238 09-10-2020
std::string CVariable::GetName() const
{
    return m_oNameString;
}

// ^^x
// void CVariable::SetType
// 3BGO JIRA-238 09-10-2020
void CVariable::SetType( const std::string& oTypeString )
{
    m_oTypeString = oTypeString;
}

// ^^x
// std::string CVariable::GetType
// 3BGO JIRA-238 09-10-2020
std::string CVariable::GetType() const
{
    return m_oTypeString;
}
