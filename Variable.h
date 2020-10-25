#pragma once

#include <string>

class CVariable final
{
public:
	void SetName( const std::string& oNameString );
	const std::string& GetName() const;

	void SetType( const std::string& oTypeString );
	const std::string& GetType() const;

private:
	std::string m_oNameString;
	std::string m_oTypeString;
};
