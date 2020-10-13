#pragma once

#include <string>
#include <optional>

class CVariable final
{
public:
	void SetName( const std::string& oNameString );
	std::string GetName() const;

	void SetType( const std::string& oTypeString );
	std::string GetType() const;

private:
	std::string m_oNameString;
	std::string m_oTypeString;
};
