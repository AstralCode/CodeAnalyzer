#include "Variable.h"

// ^^x
// void CVariable::SetName
// 3BGO JIRA-238 09-10-2020
void CVariable::SetName( std::string_view oNameString )
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
// void CVariable::SetReturnType
// 3BGO JIRA-238 09-10-2020
void CVariable::SetReturnType( std::string_view oTypeString )
{
    m_oReturnTypeString = oTypeString;
}

// ^^x
// std::string CVariable::GetReturnType
// 3BGO JIRA-238 09-10-2020
std::string CVariable::GetReturnType() const
{
    return m_oReturnTypeString;
}

// ^^x
// void CVariable::SetClassName
// 3BGO JIRA-238 09-10-2020
void CVariable::SetClassName( std::string_view oClassNameString )
{
    m_oClassNameString = oClassNameString;
}

// ^^x
// std::optional<std::string> CVariable::GetClassName
// 3BGO JIRA-238 09-10-2020
std::optional<std::string> CVariable::GetClassName() const
{
    return m_oClassNameString;
}

// ^^x
// bool CVariable::IsMember
// 3BGO JIRA-238 09-10-2020
bool CVariable::IsMember() const
{
    return m_oClassNameString.has_value();
}
