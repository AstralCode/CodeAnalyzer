#pragma once

#include <string>
#include <optional>

class CVariable final
{
public:
	void SetName( std::string_view oNameString );
	std::string GetName() const;

	void SetReturnType( std::string_view oTypeString );
	std::string GetReturnType() const;

	void SetClassName( std::string_view oClassNameString );
	std::optional<std::string> GetClassName() const;

	bool IsMember() const;

private:
	std::string m_oNameString;
	std::string m_oReturnTypeString;
	std::optional<std::string> m_oClassNameString;
};
