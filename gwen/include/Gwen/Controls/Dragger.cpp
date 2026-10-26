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

#include "Gwen/Controls/Dragger.hpp"

#if 0
namespace Gwen
{
	namespace ControlsInternal
	{
		GWEN_CONTROL_CONSTRUCTOR( Dragger )
		{
			m_pTarget = nullptr;
			SetMouseInputEnabled( true );
			m_bDepressed = false;
			m_bDoMove = true;
		}
	}
}
#else
Gwen::ControlsInternal::Dragger::Dragger( Gwen::Controls::Base::Pointer pParent, const Gwen::String& pName ) : BaseClass( pParent, pName )
{
	m_pTarget = nullptr;
	SetMouseInputEnabled( true );
	m_bDepressed = false;
	m_bDoMove = true;
}
#endif

void Gwen::ControlsInternal::Dragger::OnMouseClickLeft( const Gwen::Point &in_mousePos, bool bDown )
{
	if ( bDown )
	{
		m_bDepressed = true;

		if ( m_pTarget )
		{ m_HoldPos = m_pTarget->CanvasPosToLocal( in_mousePos ); }

		Gwen::MouseFocus = this;
		onDragStart.Call( this );
	}
	else
	{
		m_bDepressed = false;
		Gwen::MouseFocus = nullptr;
	}
}

void Gwen::ControlsInternal::Dragger::OnMouseMoved( const Gwen::Point &in_mousePos, const Gwen::Point &in_mouseDelta )
{
	if ( !m_bDepressed )
		return;

	if ( m_bDoMove && m_pTarget )
	{
		Gwen::Point p = Gwen::Point( in_mousePos.x - m_HoldPos.x, in_mousePos.y - m_HoldPos.y );

		// Translate to parent
		if ( m_pTarget->GetParent() )
			p = m_pTarget->GetParent()->CanvasPosToLocal( p ); 

		m_pTarget->MoveTo( p.x, p.y );
	}

	Gwen::Event::Information info;
	info.Point = in_mouseDelta;
	onDragged.Call( this, info );
}

void Gwen::ControlsInternal::Dragger::Render( Skin::Base::Pointer skin )
{
	//skin->DrawButton(this,false,false, false);
}

void Gwen::ControlsInternal::Dragger::OnMouseDoubleClickLeft( const Gwen::Point &in_mousePos )
{
	onDoubleClickLeft.Call( this );
}