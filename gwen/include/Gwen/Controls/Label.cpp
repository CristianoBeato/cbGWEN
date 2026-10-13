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

#include "Gwen/Controls/Label.hpp"
#include "Gwen/Controls/Text.hpp"

namespace Gwen
{
	namespace Controls
	{
		GWEN_CONTROL_CONSTRUCTOR( Label )
		{
			m_CreatedFont = nullptr;
			m_Text = new ControlsInternal::Text( this );
			m_Text->SetFont( GetSkin()->GetDefaultFont() );
			SetMouseInputEnabled( false );
			SetBounds( 0, 0, 100, 10 );
			SetAlignment( Gwen::Pos::Left | Gwen::Pos::Top );
		}
	}
}
void Gwen::Controls::Label::PreDelete( Skin::Base::Pointer skin )
{
	if ( m_CreatedFont )
	{
		skin->ReleaseFont( m_CreatedFont );
		m_CreatedFont = nullptr;
		SetFont( nullptr );
	}
}

void Gwen::Controls::Label::PostLayout( Skin::Base::Pointer /*skin*/ )
{
	m_Text->Position( m_iAlign );
}

void Gwen::Controls::Label::SetAlignment( int iAlign )
{
	if ( m_iAlign == iAlign ) { return; }

	m_iAlign = iAlign;
	Invalidate();
}

int Gwen::Controls::Label::GetAlignment()
{
	return m_iAlign;
}

void Gwen::Controls::Label::SetText( const TextObject & str, bool bDoEvents )
{
	if ( m_Text->GetText() == str.GetUnicode() )
		return;

	m_Text->SetString( str );
	Redraw();

	if ( bDoEvents )
		OnTextChanged();
}

const Gwen::TextObject & Gwen::Controls::Label::GetText( void ) const 
{ 
	return m_Text->GetText(); 
}

void Gwen::Controls::Label::SizeToContents( void )
{
	m_Text->SetPos( m_Padding.left, m_Padding.top );
	m_Text->RefreshSize();
	SetSize( m_Text->Width() + m_Padding.left + m_Padding.right, m_Text->Height() + m_Padding.top + m_Padding.bottom );
}

Gwen::Rect Gwen::Controls::Label::GetCharacterPosition( int iChar )
{
	Gwen::Rect p = m_Text->GetCharacterPosition( iChar );
	p.x += m_Text->X();
	p.y += m_Text->Y();
	return p;
}

void Gwen::Controls::Label::OnBoundsChanged( Gwen::Rect oldChildBounds )
{
	BaseClass::OnBoundsChanged( oldChildBounds );

	if ( m_Text->Wrap() )
	{
		m_Text->RefreshSize();
		Invalidate();
	}
}

void Gwen::Controls::Label::SetFont( Gwen::UnicodeString strFacename, int iSize, bool bBold )
{
	if ( m_CreatedFont )
	{
		GetSkin()->ReleaseFont( m_CreatedFont );
		// delete m_CreatedFont;
		m_CreatedFont = nullptr;
		SetFont( nullptr );
	}

	m_CreatedFont = new Gwen::Font();
	Debug::AssertCheck( m_CreatedFont != NULL, "Couldn't Create Font!" );
	m_CreatedFont->bold = bBold;
	m_CreatedFont->facename = strFacename;
	m_CreatedFont->size = iSize;
	SetFont( m_CreatedFont );
	m_Text->RefreshSize();
}

void Gwen::Controls::Label::SetFont( Gwen::Font::Pointer pFont ) 
{ 
	m_Text->SetFont( pFont ); 
}

Gwen::Font::Pointer Gwen::Controls::Label::GetFont( void ) 
{ 
	return m_Text->GetFont(); 
}

void Gwen::Controls::Label::SetTextColor( const Gwen::Color & col ) 
{ 
	m_Text->SetTextColor( col ); 
}

void Gwen::Controls::Label::SetTextColorOverride( const Gwen::Color & col ) 
{ 
	m_Text->SetTextColorOverride( col ); 
}

const Gwen::Color & Gwen::Controls::Label::TextColor( void ) const 
{ 
	return m_Text->TextColor(); 
}

int Gwen::Controls::Label::TextWidth( void ) 
{ 
	return m_Text->Width(); 
}

int Gwen::Controls::Label::TextRight( void ) 
{ 
	return m_Text->Right(); 
}

int Gwen::Controls::Label::TextHeight( void ) 
{ 
	return m_Text->Height(); 
}

int Gwen::Controls::Label::TextX( void ) 
{ 
	return m_Text->X(); 
}

int Gwen::Controls::Label::TextY( void ) 
{ 
	return m_Text->Y(); 
}

int Gwen::Controls::Label::TextLength( void ) 
{ 
	return m_Text->Length(); 
}

void Gwen::Controls::Label::SetTextPadding( const Padding & padding ) 
{ 
	m_Text->SetPadding( padding ); 
	Invalidate(); 
	InvalidateParent(); 
}

const Gwen::Padding & Gwen::Controls::Label::GetTextPadding( void ) 
{ 
	return m_Text->GetPadding(); 
}

bool Gwen::Controls::Label::Wrap( void ) 
{ 
	return m_Text->Wrap(); 
}

void Gwen::Controls::Label::SetWrap( bool b ) 
{ 
	m_Text->SetWrap( b ); 
}
