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

#include "Gwen/Controls/Canvas.hpp"

#ifndef GWEN_NO_ANIMATION
#	include "Gwen/Anim.h"
#endif

Gwen::Controls::Canvas::Canvas( Gwen::Skin::Base::Pointer pSkin ) : BaseClass( NULL ), m_bAnyDelete( false )
{
	SetBounds( 0, 0, 10000, 10000 );
	SetScale( 1.0f );
	SetBackgroundColor( Color( 255, 255, 255, 255 ) );
	SetDrawBackground( false );

	if ( pSkin ) { SetSkin( pSkin ); }
}

Gwen::Controls::Canvas::~Canvas( void )
{
	ReleaseChildren();
}

void Gwen::Controls::Canvas::RenderCanvas( void )
{
	DoThink();
	AutoPointer<Renderer::Base> render = m_Skin->GetRender();
	render->Begin();
	RecurseLayout( m_Skin );
	render->SetClipRegion( GetBounds() );
	render->SetRenderOffset( Gwen::Point( 0, 0 ) );
	render->SetScale( Scale() );

	if ( m_bDrawBackground )
	{
		render->SetDrawColor( m_BackgroundColor );
		render->DrawFilledRect( GetRenderBounds() );
	}

	DoRender( m_Skin );
	DragAndDrop::RenderOverlay( this, m_Skin );
	ToolTip::RenderToolTip( m_Skin );
	render->End();
}

void Gwen::Controls::Canvas::Render( Skin::Base::Pointer /*pRender*/ )
{
	m_bNeedsRedraw = false;
}

void Gwen::Controls::Canvas::OnBoundsChanged( Gwen::Rect oldBounds )
{
	BaseClass::OnBoundsChanged( oldBounds );
	InvalidateChildren( true );
}


void Gwen::Controls::Canvas::DoThink( void )
{
	ProcessDelayedDeletes();

	if ( Hidden() )
		return; 

#ifndef GWEN_NO_ANIMATION
	Gwen::Anim::Think();
#endif
	// Reset tabbing
	{
		NextTab = nullptr;
		FirstTab = nullptr;
	}
	ProcessDelayedDeletes();
	// Check has focus etc..
	RecurseLayout( m_Skin );

	// If we didn't have a next tab, cycle to the start.
	if ( NextTab == NULL )
		NextTab = FirstTab;

	Gwen::Input::OnCanvasThink( this );
}

void Gwen::Controls::Canvas::SetScale( float f )
{
	if ( m_fScale == f ) 
		return;

	m_fScale = f;

	if ( m_Skin && m_Skin->GetRender() )
		m_Skin->GetRender()->SetScale( m_fScale );

	OnScaleChanged();
	Redraw();
}

void Gwen::Controls::Canvas::AddDelayedDelete( AutoPointer<Controls::Base> pControl )
{
	if ( !m_bAnyDelete || m_DeleteSet.find( pControl ) == m_DeleteSet.end() )
	{
		m_bAnyDelete = true;
		m_DeleteSet.insert( pControl );
		m_DeleteList.push_back( pControl );
	}
}

void Gwen::Controls::Canvas::PreDeleteCanvas( AutoPointer<Controls::Base> pControl )
{
	if ( m_bAnyDelete )
	{
		std::set< Controls::Base::Pointer >::iterator itFind;

		if ( ( itFind = m_DeleteSet.find( pControl ) ) != m_DeleteSet.end() )
		{
			m_DeleteList.remove( pControl );
			m_DeleteSet.erase( pControl );
			m_bAnyDelete = !m_DeleteSet.empty();
		}
	}
}

void Gwen::Controls::Canvas::ProcessDelayedDeletes()
{
	while ( m_bAnyDelete )
	{
		m_bAnyDelete = false;
		Controls::Base::List deleteList = m_DeleteList;
		m_DeleteList.clear();
		m_DeleteSet.clear();

		for ( Gwen::Controls::Base::List::iterator it = deleteList.begin(); it != deleteList.end(); ++it )
		{
			AutoPointer<Controls::Base> pControl = *it;
			pControl->PreDelete( GetSkin() );
			// delete pControl;
			Redraw();
		}
	}
}

void Gwen::Controls::Canvas::ReleaseChildren()
{
	Base::List::iterator iter = Children.begin();

	while ( iter != Children.end() )
	{
		Base* pChild = *iter;
		iter = Children.erase( iter );
		delete pChild;
	}
}

bool Gwen::Controls::Canvas::InputMouseMoved( const Point &in_pos, const Point &in_delta )
{
	if ( Hidden() )
		return false;

	if ( ToolTip::TooltipActive() )
		Redraw();

	// Todo: Handle scaling here..
	//float fScale = 1.0f / Scale();
	Gwen::Input::OnMouseMoved( this, in_pos, in_delta );

	if ( !Gwen::HoveredControl ) 
		return false;

	if ( Gwen::HoveredControl == this )
		return false;

	if ( Gwen::HoveredControl->GetCanvas() != this )
		return false;

	Gwen::HoveredControl->OnMouseMoved( in_pos, in_delta );
	Gwen::HoveredControl->UpdateCursor();
	DragAndDrop::OnMouseMoved( Gwen::HoveredControl, in_pos );
	return true;
}

bool Gwen::Controls::Canvas::InputMouseButton( int iButton, bool bDown )
{
	if ( Hidden() ) { return false; }

	return Gwen::Input::OnMouseClicked( this, iButton, bDown );
}

bool Gwen::Controls::Canvas::InputKey( int iKey, bool bDown )
{
	if ( Hidden() ) { return false; }

	if ( iKey <= Gwen::Key::Invalid ) { return false; }

	if ( iKey >= Gwen::Key::Count ) { return false; }

	return Gwen::Input::OnKeyEvent( this, iKey, bDown );
}

bool Gwen::Controls::Canvas::InputCharacter( Gwen::UnicodeChar chr )
{
	if ( Hidden() )
		return false;

	if ( !iswprint( chr ) )
		return false;

	//Handle Accelerators
	if ( Gwen::Input::HandleAccelerator( this, chr ) )
		return true;

	//Handle characters
	if ( !Gwen::KeyboardFocus )
		return false;

	if ( Gwen::KeyboardFocus->GetCanvas() != this )
		return false;

	if ( !Gwen::KeyboardFocus->Visible() )
		return false;

	if ( Gwen::Input::IsControlDown() )
		return false;

	return KeyboardFocus->OnChar( chr );
}

bool Gwen::Controls::Canvas::InputMouseWheel( int val )
{
	if ( Hidden() )
		return false;

	if ( !Gwen::HoveredControl )
		return false;

	if ( Gwen::HoveredControl == this )
		return false;

	if ( Gwen::HoveredControl->GetCanvas() != this )
		return false;

	return Gwen::HoveredControl->OnMouseWheeled( val );
}