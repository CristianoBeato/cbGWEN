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

#pragma once

namespace Gwen
{
	/*

		TextObjects can be either a UnicodeString or a String

		Just makes things easier instead of having a function taking both.

	*/
	class TextObject
	{
		public:

			TextObject( void );
			TextObject( const Gwen::String & text );
			TextObject( const char* text );
			TextObject( const wchar_t* text );
			TextObject( const Gwen::UnicodeString & unicode );
			inline operator const Gwen::String & () { return m_String; }
			inline operator const Gwen::UnicodeString & () { return m_Unicode; }

			void operator = ( const char* str );
			void operator = ( const Gwen::String & str );
			void operator = ( const Gwen::UnicodeString & unicodeStr );

			inline  bool operator == ( const TextObject & to ) const
			{
				return m_Unicode == to.m_Unicode;
			}

			inline const Gwen::String & Get() const
			{
				return m_String;
			}

			inline const char* c_str() const
			{
				return m_String.c_str();
			}

			inline const Gwen::UnicodeString & GetUnicode() const
			{
				return m_Unicode;
			}

			inline size_t length() const 
			{ 
				return m_Unicode.length(); 
			}

			static String UnicodeToString( const UnicodeString & strIn );
			static UnicodeString StringToUnicode( const String & strIn );
		
			template<typename T> 
			static void Replace( T & str, const T & strFind, const T & strReplace )
			{
				size_t pos = 0;

				while ( ( pos = str.find( strFind, pos ) ) != T::npos )
				{
					str.replace( pos, strFind.length(), strReplace );
					pos += strReplace.length();
				}
			}

			Gwen::UnicodeString		m_Unicode;
			Gwen::String			m_String;
	};
}
