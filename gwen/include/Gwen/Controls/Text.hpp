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
	namespace ControlsInternal
	{
		class GWEN_EXPORT Text : public Controls::Base
		{
			public:
				typedef AutoPointer<Text>	Pointer;;

				GWEN_CONTROL( Text, Controls::Base );

				virtual 			~Text( void );
				Gwen::Font::Pointer GetFont( void );

				void SetString( const TextObject & str );

				void Render( Skin::Base::Pointer skin );
				void Layout( Skin::Base::Pointer skin );

				void RefreshSize( void );

				void SetFont( Gwen::Font::Pointer pFont );

				const TextObject & GetText( void ) const { return m_String; }

				Gwen::Rect GetCharacterPosition( int iChar );
				int GetClosestCharacter( Gwen::Point p );

				/// return the encapsulating box of the given line
				// @remark this function is necessary to implement multiline selection
				virtual Gwen::Rect GetLineBox( int i ); 

				size_t Length( void ) const 
				{ 
					return m_String.GetUnicode().size(); 
				}

				virtual void SetTextColor( const Gwen::Color & col ) { m_Color = col; }
				virtual void SetTextColorOverride( const Gwen::Color & col ) { m_ColorOverride = col; }

				virtual void OnScaleChanged( void );

				inline const Gwen::Color & TextColor() const { return m_Color; }

				virtual void TextChanged() { m_bTextChanged = true; }
				virtual bool Wrap() { return m_bWrap; }
				virtual void SetWrap( bool b ) { if ( m_bWrap == b ) { return; } m_bWrap = b; m_bTextChanged = true; Invalidate(); }

				virtual Text::Pointer GetLine( int i );
				virtual int GetLineFromChar( int i );
				virtual int GetStartCharFromLine( int i );
				virtual int GetEndCharFromLine( int i );
				virtual int GetCharPosOnLine( int i );
				virtual int NumLines();


			protected:

				virtual void SplitWords(const Gwen::UnicodeString &s, std::vector<Gwen::UnicodeString> &elems);
			
			private: 
				typedef std::list<ControlsInternal::Text::Pointer> TextLines;

				virtual void RefreshSizeWrap( void );

				Gwen::TextObject	m_String;
				Gwen::Font::Pointer	m_Font;
				Gwen::Color			m_Color;
				Gwen::Color			m_ColorOverride;

				bool				m_bWrap;
				bool				m_bTextChanged;

				TextLines										m_Lines;
		};
	}

}
