/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/
#include "Precompiled.hpp"

#ifdef _MSC_VER
#pragma warning(disable:4267)// conversion from 'size_t' to 'int', possible loss of data
#endif

//#ifdef __GNUC__
//#undef vswprintf
//#define vswprintf _vsnwprintf
//#endif

#ifdef _MSC_VER
#define GWEN_FNULL "NUL"
#define va_copy(d,s) ((d) = (s))
#else
#define GWEN_FNULL "/dev/null"
#endif

UnicodeString Gwen::Utility::Format( const wchar_t* fmt, ... )
{
	va_list s;
	int len = 0;
	UnicodeString strOut;
	va_start( s, fmt );
	
#if 0
	// Determine the length of the resulting string, this method is much faster
	// than looping and reallocating a bigger buffer size.
	{	
		FILE* fnull = fopen( GWEN_FNULL, "wb" );
		va_list c;
		va_copy( c, s );
		len = std::vfwprintf( fnull, fmt, c );
		va_end( c );
		fclose( fnull );
	} 
	
	
	if (len > 0)
	{
		strOut.resize( len + 1 );
		va_list c;
		va_copy( c, s );
		len = std::vswprintf( &strOut[0], strOut.size(), fmt, c );
		va_end( c );
		strOut.resize( len );
	}
#else
	static const uint32_t k_MAX_LEN = 4086;
	wchar_t str[k_MAX_LEN];
	std::vswprintf( str, k_MAX_LEN, fmt, s );
	strOut = str;
#endif
	
	va_end( s );
	
	return strOut;
}

void Gwen::Utility::Strings::Split( const Gwen::String & str, const Gwen::String & seperator, Strings::List & outbits, bool bLeave )
{
	int iOffset = 0;
	int iLength = str.length();
	int iSepLen = seperator.length();
	size_t i = str.find( seperator, 0 );

	while ( i != std::string::npos )
	{
		outbits.push_back( str.substr( iOffset, i - iOffset ) );
		iOffset = i + iSepLen;
		i = str.find( seperator, iOffset );

		if ( bLeave )
			iOffset -= iSepLen;
	}

	outbits.push_back( str.substr( iOffset, iLength - iOffset ) );
}

void Gwen::Utility::Strings::Split( const Gwen::UnicodeString & str, const Gwen::UnicodeString & seperator, Strings::UnicodeList & outbits, bool bLeave )
{
	int iOffset = 0;
	int iLength = str.length();
	int iSepLen = seperator.length();
	size_t i = str.find( seperator, 0 );

	while ( i != std::wstring::npos )
	{
		outbits.push_back( str.substr( iOffset, i - iOffset ) );
		iOffset = i + iSepLen;
		i = str.find( seperator, iOffset );

		if ( bLeave )
			iOffset -= iSepLen;
	}

	outbits.push_back( str.substr( iOffset, iLength - iOffset ) );
}

int Gwen::Utility::Strings::To::Int( const Gwen::String & str )
{
	if ( str == "" ) 
		return 0; 

	return std::atoi( str.c_str() );
}

float Gwen::Utility::Strings::To::Float( const Gwen::String & str )
{
	if ( str == "" )
		return 0.0f;

	return ( float ) std::atof( str.c_str() );
}

float Gwen::Utility::Strings::To::Float( const Gwen::UnicodeString & str )
{
	return std::wcstod( str.c_str(), nullptr );
}

bool Gwen::Utility::Strings::To::Bool( const Gwen::String & str )
{
	if ( str.size() == 0 )
		return false;

	if ( str[0] == 'T' || str[0] == 't' || str[0] == 'y' || str[0] == 'Y' )
		return true;

	if ( str[0] == 'F' || str[0] == 'f' || str[0] == 'n' || str[0] == 'N' )
		return false;

	if ( str[0] == '0' )
		return false;

	return true;
}

bool Gwen::Utility::Strings::To::Floats( const Gwen::String & str, float* f, size_t iCount )
{
	Strings::List lst;
	Strings::Split( str, " ", lst );

	if ( lst.size() != iCount ) { return false; }

	for ( size_t i = 0; i < iCount; i++ )
	{
		f[i] = Strings::To::Float( lst[i] );
	}

	return true;
}


bool Gwen::Utility::Strings::Wildcard( const TextObject & strWildcard, const TextObject & strHaystack )
{
	const UnicodeString & W = strWildcard.GetUnicode();
	const UnicodeString & H = strHaystack.GetUnicode();

	if ( strWildcard == "*" ) { return true; }

	int iPos = W.find( L"*", 0 );

	if ( iPos == UnicodeString::npos ) { return strWildcard == strHaystack; }

	// First half matches
	if ( iPos > 0 && W.substr( 0, iPos ) != H.substr( 0, iPos ) )
	{ return false; }

	// Second half matches
	if ( iPos != W.length() - 1 )
	{
		UnicodeString strEnd = W.substr( iPos + 1, W.length() );

		if ( strEnd != H.substr( H.length() - strEnd.length(), H.length() ) )
		{ return false; }
	}

	return true;
}



void Gwen::Utility::Strings::ToUpper( Gwen::UnicodeString & str )
{
	transform( str.begin(), str.end(), str.begin(), towupper );
}

void Gwen::Utility::Strings::Strip( Gwen::UnicodeString & str, const Gwen::UnicodeString & chars )
{
	Gwen::UnicodeString Source = str;
	str = L"";

	for ( uint32_t i = 0; i < Source.length(); i++ )
	{
		if ( chars.find( Source[i] ) != Gwen::UnicodeString::npos )
			continue; 

		str += Source[i];
	}
}



