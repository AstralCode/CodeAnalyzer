#pragma once

#include <vector>
#include <optional>

#include "Variable.h"
#include "FindDataResult.h"

class CFunction final
{
public:
	struct SInformation
	{
		std::string oAuthorString;
		std::string oProjectString;
	};

	void SetName( const std::string& oNameString );
	const std::string& GetName() const;

	void SetDestructor( const std::string& oDestructorString );
	std::optional<std::string> GetDestructor() const;

	void SetReturnType( const std::string& oReturnTypeString );
	std::optional<std::string> GetReturnType() const;

	void SetClassName( const std::string& oClassNameString );
	std::optional<std::string> GetClassName() const;

	void SetArgumentList( const std::string& oArgumentListString );
	std::optional<std::string> GetArgumentList() const;

	void SetBody( const std::string& oBodyString );
	std::optional<std::string> GetBody() const;

	void SetInformation( const SInformation& oInformation );
	std::optional<SInformation> GetInformation() const;

	void SetLocalVariables( std::vector<SFindDataResult<CVariable>>&& oLocalVariableVector );
	std::optional<std::vector<SFindDataResult<CVariable>>> GetLocalVariables() const;

	bool IsConstructor() const;
	bool IsDestructor() const;

	bool IsMember() const;

private:
	std::string m_oNameString;
	std::optional<std::string> m_oDestructorString;
	std::optional<std::string> m_oReturnTypeString;
	std::optional<std::string> m_oClassNameString;
	std::optional<std::string> m_oArgumentListString;
	std::optional<std::string> m_oBodyString;
	std::optional<SInformation> m_oInformation;
	std::optional<std::vector<SFindDataResult<CVariable>>> m_oLocalVariableVector;
};
