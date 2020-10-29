#pragma once

#include <string>
#include <optional>

class CVariable final
{
public:
	enum class EReferenceType
	{
		Reference,
		Pointer
	};

	void SetName( const std::string& oNameString );
	const std::string& GetName() const;

	void SetType( const std::string& oTypeString );
	const std::string& GetType() const;

	void SetReferenceType( const EReferenceType eReferenceType );
	std::optional<EReferenceType> GetReferenceType() const;

	void SetArrayType( const bool bArrayType );
	bool IsArrayType() const;

private:
	std::string m_oNameString;
	std::string m_oTypeString;
	std::optional<EReferenceType> m_eReferenceType;
	bool m_bIsArrayType;
};
