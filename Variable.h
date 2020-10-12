#pragma once

#include <string>
#include <optional>

class CVariable final
{
public:
	void SetName( const std::string& oNameString );
	std::string GetName() const;

	void SetReturnType( const std::string& oTypeString );
	std::string GetReturnType() const;

	void SetClassName( const std::string& oClassNameString );
	std::optional<std::string> GetClassName() const;

	bool IsMember() const;

private:
	std::string m_oNameString;
	std::string m_oReturnTypeString;
	std::optional<std::string> m_oClassNameString;
};
