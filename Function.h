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
	void SetName( std::string_view oNameString );
	std::string GetName() const;

	void SetReturnType( std::string_view oReturnTypeString );
	std::string GetReturnType() const;

	void SetClassName( std::string_view oClassNameString );
	std::optional<std::string> GetClassName() const;

	void SetArgumentList( std::string_view oArgumentListString );
	std::optional<std::string> GetArgumentList() const;

	void SetBody( std::string_view oBodyString );
	std::optional<std::string> GetBody() const;

	void SetInformation( const SFunctionInformation& oInformation );
	std::optional<SFunctionInformation> GetInformation() const;

	bool IsMember() const;

private:
	std::string m_oNameString;
	std::string m_oReturnTypeString;
	std::optional<std::string> m_oClassNameString;
	std::optional<std::string> m_oArgumentListString;
	std::optional<std::string> m_oBodyString;
	std::optional<SFunctionInformation> m_oInformation;
};
