#include "Function.h"

// ^^x
// void CFunction::SetName
// 3BGO JIRA-238 09-10-2020
void CFunction::SetName( std::string_view oNameString )
{
    m_oNameString = oNameString;
}

// ^^x
// std::string CFunction::GetName
// 3BGO JIRA-238 09-10-2020
std::string CFunction::GetName() const
{
    return m_oNameString;
}

// ^^x
// void CFunction::SetReturnType
// 3BGO JIRA-238 09-10-2020
void CFunction::SetReturnType( std::string_view oReturnTypeString )
{
    m_oReturnTypeString = oReturnTypeString;
}

// ^^x
// std::string CFunction::GetReturnType
// 3BGO JIRA-238 09-10-2020
std::string CFunction::GetReturnType() const
{
    return m_oReturnTypeString;
}

// ^^x
// void CFunction::SetClassName
// 3BGO JIRA-238 09-10-2020
void CFunction::SetClassName( std::string_view oClassNameString )
{
    m_oClassNameString = oClassNameString;
}

// ^^x
// std::optional<std::string> CFunction::GetClassName
// 3BGO JIRA-238 09-10-2020
std::optional<std::string> CFunction::GetClassName() const
{
    return m_oClassNameString;
}

// ^^x
// void CFunction::SetArgumentList
// 3BGO JIRA-238 09-10-2020
void CFunction::SetArgumentList( std::string_view oArgumentListString )
{
    m_oArgumentListString = oArgumentListString;
}

// ^^x
// std::optional<std::string> CFunction::GetArgumentList
// 3BGO JIRA-238 09-10-2020
std::optional<std::string> CFunction::GetArgumentList() const
{
    return m_oArgumentListString;
}

// ^^x
// void CFunction::SetBody
// 3BGO JIRA-238 09-10-2020
void CFunction::SetBody( std::string_view oBodyString )
{
    m_oBodyString = oBodyString;
}

// ^^x
// std::optional<std::string> CFunction::GetBody
// 3BGO JIRA-238 09-10-2020
std::optional<std::string> CFunction::GetBody() const
{
    return m_oBodyString;
}

// ^^x
// void CFunction::SetInformation
// 3BGO JIRA-238 09-10-2020
void CFunction::SetInformation( const SFunctionInformation& oInformation )
{
    m_oInformation = oInformation;
}

// ^^x
// std::optional<SFunctionInformation> CFunction::GetInformation
// 3BGO JIRA-238 09-10-2020
std::optional<SFunctionInformation> CFunction::GetInformation() const
{
    return m_oInformation;
}

// ^^x
// bool CFunction::IsMember
// 3BGO JIRA-238 09-10-2020
bool CFunction::IsMember() const
{
    return m_oClassNameString.has_value();
}
