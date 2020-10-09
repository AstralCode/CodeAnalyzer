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
// std::optional<std::string> CFunction::SetDestructor
// 3BGO JIRA-238 09-10-2020
void CFunction::SetDestructor( std::string_view oDestructorString )
{
    m_oDestructorString = oDestructorString;
}

// ^^x
// std::optional<std::string> CFunction::GetDestructor
// 3BGO JIRA-238 09-10-2020
std::optional<std::string> CFunction::GetDestructor() const
{
    return m_oDestructorString;
}

// ^^x
// void CFunction::SetReturnType
// 3BGO JIRA-238 09-10-2020
void CFunction::SetReturnType( std::string_view oReturnTypeString )
{
    m_oReturnTypeString = oReturnTypeString;
}

// ^^x
// std::optional<std::string> CFunction::GetReturnType
// 3BGO JIRA-238 09-10-2020
std::optional<std::string> CFunction::GetReturnType() const
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
// std::optional<SFunctionInformation> CFunction::GetInformation
// 3BGO JIRA-238 09-10-2020
bool CFunction::IsConstructor() const
{
    bool bIsConstructor{ false };

    if ( IsMember() )
    {
        bIsConstructor = !m_oReturnTypeString.has_value();
    }

    return bIsConstructor;
}

// ^^x
// std::optional<SFunctionInformation> CFunction::GetInformation
// 3BGO JIRA-238 09-10-2020
bool CFunction::IsDestructor() const
{
    bool bIsDestructor{ false };

    if ( IsMember() )
    {
        bIsDestructor = !m_oReturnTypeString.has_value() && m_oDestructorString.has_value();
    }

    return bIsDestructor;
}

// ^^x
// bool CFunction::IsMember
// 3BGO JIRA-238 09-10-2020
bool CFunction::IsMember() const
{
    return m_oClassNameString.has_value();
}
