#pragma once

#include <string>
#include <optional>

struct SFunctionInformation
{
	std::string m_oAuthorString;
	std::string m_oProjectString;
};

class CFunction final
{
public:
	void SetName( const std::string& oNameString );
	std::string GetName() const;

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

	void SetInformation( const SFunctionInformation& oInformation );
	std::optional<SFunctionInformation> GetInformation() const;

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
	std::optional<SFunctionInformation> m_oInformation;
};
