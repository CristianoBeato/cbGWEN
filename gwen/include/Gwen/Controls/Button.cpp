/*
============================================================================================
	GWEN

	Copyright (c) 2010 Facepunch Studios.
	Copyright (c) 2025 Cristiano Beato.

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

#include "Gwen/Controls/Button.hpp"

#if 0
namespace Gwen
{
	namespace Control
	{
		GWEN_CONTROL_CONSTRUCTOR( Button )
		{
			m_Image = NULL;
			m_bDepressed = false;
			m_bCenterImage = false;
			SetSize( 100, 20 );
			SetMouseInputEnabled( true );
			SetIsToggle( false );
			SetAlignment( Gwen::Pos::Center );
			SetTextPadding( Padding( 3, 0, 3, 0 ) );
			m_bToggleStatus = false;
			SetKeyboardInputEnabled( false );
			SetTabable( false );
		}
	};
};
#else
Gwen::Controls::Button::Button( Gwen::Controls::Base::Pointer pParent, const Gwen::String& pName ) : BaseClass( pParent, pName )
{
	m_Image = nullptr;
	m_bDepressed = false;
	m_bCenterImage = false;
	SetSize( 100, 20 );
	SetMouseInputEnabled( true );
	SetIsToggle( false );
	SetAlignment( Gwen::Pos::Center );
	SetTextPadding( Padding( 3, 0, 3, 0 ) );
	m_bToggleStatus = false;
	SetKeyboardInputEnabled( false );
	SetTabable( false );
}
#endif

void Gwen::Controls::Button::Render( Skin::Base::Pointer skin )
{
	if ( !ShouldDrawBackground() ) { return; }

	bool bDrawDepressed = IsDepressed() && IsHovered();

	if ( IsToggle() ) { bDrawDepressed = bDrawDepressed || GetToggleState(); }

	bool bDrawHovered = IsHovered() && ShouldDrawHover();
	skin->DrawButton( this, bDrawDepressed, bDrawHovered, IsDisabled() );
}

void Gwen::Controls::Button::OnMouseClickLeft( const Point &in_pos, bool bDown )
{
	if ( IsDisabled() ) 
		return;

	if ( bDown )
	{
		SetDepressed( true );
		Gwen::MouseFocus = this;
		onDown.Call( this );
	}
	else
	{
		if ( IsHovered() && m_bDepressed )
			OnPress();

		SetDepressed( false );
		Gwen::MouseFocus = NULL;
		onUp.Call( this );
	}
}

void Gwen::Controls::Button::OnMouseClickRight( const Point &in_pos, bool bDown )
{
	if ( IsDisabled() ) { return; }

	if ( bDown )
	{
		SetDepressed( true );
		Gwen::MouseFocus = this;
		onDown.Call( this );
	}
	else
	{
		if ( IsHovered() && m_bDepressed )
			OnRightPress();

		SetDepressed( false );
		Gwen::MouseFocus = NULL;
		onUp.Call( this );
	}
}


void Gwen::Controls::Button::SetDepressed( bool b )
{
	if ( m_bDepressed == b ) { return; }

	m_bDepressed = b;
	Redraw();
}

void Gwen::Controls::Button::OnRightPress( void )
{
	onRightPress.Call( this );
}

void Gwen::Controls::Button::OnPress()
{
	if ( IsToggle() )
	{
		SetToggleState( !GetToggleState() );
	}

	onPress.Call( this );
}


void Gwen::Controls::Button::SetImage( const TextObject & strName, bool bCenter )
{
	if ( strName.GetUnicode() == L"" )
	{
		if ( m_Image )
		{
			// delete m_Image;
			m_Image = nullptr;
		}

		return;
	}

	if ( !m_Image )
		m_Image = new ImagePanel( this );

	m_Image->SetImage( strName );
	m_Image->SizeToContents();
	m_Image->SetMargin( Margin( 2, 0, 2, 0 ) );
	m_bCenterImage = bCenter;
	// Ugh.
	Padding padding = GetTextPadding();
	padding.left = m_Image->Right() + 2;
	SetTextPadding( padding );
}

void Gwen::Controls::Button::SetToggleState( bool b )
{
	if ( m_bToggleStatus == b ) { return; }

	m_bToggleStatus = b;
	onToggle.Call( this );

	if ( m_bToggleStatus )
	{
		onToggleOn.Call( this );
	}
	else
	{
		onToggleOff.Call( this );
	}

	Redraw();
}

void Gwen::Controls::Button::SizeToContents()
{
	BaseClass::SizeToContents();

	if ( m_Image )
	{
		int height = m_Image->Height() + 4;

		if ( Height() < height )
		{
			SetHeight( height );
		}
	}
}

bool Gwen::Controls::Button::OnKeySpace( bool bDown )
{
	if ( bDown )
		OnPress();

	return true;
}

void Gwen::Controls::Button::AcceleratePressed()
{
	OnPress();
}

void Gwen::Controls::Button::UpdateColours()
{
	if ( IsDisabled() )		{ return SetTextColor( GetSkin()->Colors.Button.Disabled ); }

	if ( IsDepressed() || GetToggleState() )	{ return SetTextColor( GetSkin()->Colors.Button.Down ); }

	if ( IsHovered() )		{ return SetTextColor( GetSkin()->Colors.Button.Hover ); }

	SetTextColor( GetSkin()->Colors.Button.Normal );
}

void Gwen::Controls::Button::PostLayout( Skin::Base::Pointer pSkin )
{
	BaseClass::PostLayout( pSkin );

	if ( m_Image )
	{
		if ( m_bCenterImage )
		{ m_Image->Position( Pos::Center ); }
		else
		{ m_Image->Position( Pos::Left | Pos::CenterV ); }
	}
}

void Gwen::Controls::Button::OnMouseDoubleClickLeft( const Point &in_pos )
{
	if ( IsDisabled() )
		return;

	OnMouseClickLeft( in_pos, true );
	onDoubleClick.Call( this );
}

void Gwen::Controls::Button::SetImageAlpha( float f )
{
	if ( !m_Image )
		return;

	m_Image->SetDrawColor( Gwen::Color( 255, 255, 255, 255.0f * f ) );
}

void Gwen::Controls::Button::SetAction( Event::Handler* pObject, Handler::FunctionWithInformation pFunction, void* data )
{
	onPress.Add( pObject, pFunction, data );
}
