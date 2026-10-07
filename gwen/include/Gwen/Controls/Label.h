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
		class Text;
	};

	namespace Controls
	{
		class GWEN_EXPORT Label : public Controls::Base
		{
			public:

				GWEN_CONTROL( Label, Controls::Base );
				virtual void PreDelete( Gwen::Skin::Base::Pointer skin );

				virtual void SetText( const TextObject & str, bool bDoEvents = true );

				virtual const TextObject & GetText() const { return m_Text->GetText(); }

				virtual void Render( Skin::Base* /*skin*/ ) {}

				virtual void PostLayout( Skin::Base* skin );

				virtual void SizeToContents();

				virtual void SetAlignment( int iAlign );
				virtual int GetAlignment();


				virtual void SetFont( Gwen::UnicodeString strFacename, int iSize, bool bBold );

				virtual void SetFont( Gwen::Font* pFont ) { m_Text->SetFont( pFont ); }
				virtual Gwen::Font* GetFont() { return m_Text->GetFont(); }
				virtual void SetTextColor( const Gwen::Color & col ) { m_Text->SetTextColor( col ); }
				virtual void SetTextColorOverride( const Gwen::Color & col ) { m_Text->SetTextColorOverride( col ); }
				inline const Gwen::Color & TextColor() const { return m_Text->TextColor(); }

				virtual int TextWidth() { return m_Text->Width(); }
				virtual int TextRight() { return m_Text->Right(); }
				virtual int TextHeight() { return m_Text->Height(); }
				virtual int TextX() { return m_Text->X(); }
				virtual int TextY() { return m_Text->Y(); }
				virtual int TextLength() { return m_Text->Length(); }

				Gwen::Rect GetCharacterPosition( int iChar );

				virtual void SetTextPadding( const Padding & padding ) { m_Text->SetPadding( padding ); Invalidate(); InvalidateParent(); }
				virtual const Padding & GetTextPadding() { return m_Text->GetPadding(); }

				inline int Alignment() const { return m_iAlign; }

				virtual void MakeColorNormal() { SetTextColor( GetSkin()->Colors.Label.Default ); }
				virtual void MakeColorBright() { SetTextColor( GetSkin()->Colors.Label.Bright ); }
				virtual void MakeColorDark() { SetTextColor( GetSkin()->Colors.Label.Dark ); }
				virtual void MakeColorHighlight() { SetTextColor( GetSkin()->Colors.Label.Highlight ); }

				virtual TextObject GetValue() { return GetText(); }
				virtual void SetValue( const TextObject & strValue ) { return SetText( strValue ); }

				virtual bool Wrap() { return m_Text->Wrap(); }
				virtual void SetWrap( bool b ) { m_Text->SetWrap( b ); }

				virtual void OnBoundsChanged( Gwen::Rect oldChildBounds );

			protected:

				virtual void OnTextChanged() {};

				Gwen::Font*					m_CreatedFont;
				ControlsInternal::Text*		m_Text;
				int m_iAlign;


		};
	}
}
#endif
