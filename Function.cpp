#include "Function.h"

// ^^x
// void CFunction::SetName
// 3BGO JIRA-238 09-10-2020
void CFunction::SetName( const std::string& oNameString )
{
    m_oNameString = oNameString;
}

// ^^x
// const std::string& CFunction::GetName
// 3BGO JIRA-238 09-10-2020
const std::string& CFunction::GetName() const
{
    return m_oNameString;
}

// ^^x
// std::optional<std::string> CFunction::SetDestructor
// 3BGO JIRA-238 09-10-2020
void CFunction::SetDestructor( const std::string& oDestructorString )
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
void CFunction::SetReturnType( const std::string& oReturnTypeString )
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
void CFunction::SetClassName( const std::string& oClassNameString )
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
void CFunction::SetArgumentList( const std::string& oArgumentListString )
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
void CFunction::SetBody( const std::string& oBodyString )
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
void CFunction::SetInformation( const SInformation& oInformation )
{
    m_oInformation = oInformation;
}

// ^^x
// std::optional<SInformation> CFunction::GetInformation
// 3BGO JIRA-238 09-10-2020
std::optional<CFunction::SInformation> CFunction::GetInformation() const
{
    return m_oInformation;
}

// ^^x
// void CFunction::SetLocalVariables
// 3BGO JIRA-238 09-10-2020
void CFunction::SetLocalVariables( std::vector<SFindDataResult<CVariable>>&& oVariableVector )
{
    m_oLocalVariableVector = std::move( oVariableVector );
}

// ^^x
// std::optional<std::vector<SFindDataResult<CVariable>>> CFunction::GetLocalVariables
// 3BGO JIRA-238 09-10-2020
std::optional<std::vector<SFindDataResult<CVariable>>> CFunction::GetLocalVariables() const
{
    return m_oLocalVariableVector;
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
