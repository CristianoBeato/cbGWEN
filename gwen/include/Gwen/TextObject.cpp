/*
============================================================================================
	GWEN

	Copyright (c) 2010 Facepunch Studios.
	Copyright (c) 2025-2026 Cristiano Beato.

	MIT License

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
============================================================================================
*/

#include "TextObject.hpp"

Gwen::TextObject::TextObject(void)
{
}

Gwen::TextObject::TextObject( const Gwen::String & text )
{
	m_String = text;
	m_Unicode = StringToUnicode( m_String );
}
			
Gwen::TextObject::TextObject( const char* text )
{
	m_String = text;
	m_Unicode = StringToUnicode( m_String );
}

Gwen::TextObject::TextObject( const wchar_t* text )
{
	m_Unicode = text;
	m_String = UnicodeToString( m_Unicode );
}

Gwen::TextObject::TextObject( const Gwen::UnicodeString & unicode )
{
	*this = unicode;
}

void Gwen::TextObject::operator = ( const char* str )
{
	m_String = str;
	m_Unicode = StringToUnicode( m_String );
}

void Gwen::TextObject::operator = ( const Gwen::String & str )
{
	m_String = str;
	m_Unicode = StringToUnicode( m_String );
}

void Gwen::TextObject::operator = ( const Gwen::UnicodeString & unicodeStr )
{
	m_Unicode = unicodeStr;
	m_String = UnicodeToString( m_Unicode );
}

Gwen::String Gwen::TextObject::UnicodeToString( const UnicodeString & strIn )
{
    if ( !strIn.length() ) { return "\0"; }

	String temp( strIn.length(), ( char ) 0 );
	std::use_facet< std::ctype<wchar_t> > ( std::locale() ). \
	narrow( &strIn[0], &strIn[0] + strIn.length(), ' ', &temp[0] );
	return temp;
}

Gwen::UnicodeString Gwen::TextObject::StringToUnicode( const String & strIn )
{
    if ( !strIn.length() )     
    { 
        return L"\0"; 
    }

	UnicodeString temp( strIn.length(), ( wchar_t ) 0 );
	std::use_facet< std::ctype<wchar_t> > ( std::locale() ). \
	widen( &strIn[0], &strIn[0] + strIn.length(), &temp[0] );
	return temp;
}
