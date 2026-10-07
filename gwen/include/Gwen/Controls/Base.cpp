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

#include "Base.hpp"
#include "Gwen/Debug.h"
#include "Gwen/Controls/Label.h"

Gwen::Controls::Base::Base( Controls::Base::Pointer pParent, const Gwen::String & Name ) :
	m_Parent(),
	m_ActualParent(),
	m_InnerPanel(),
	m_Platform( nullptr ),
	m_Skin(),
	m_DragAndDrop_Package()
{
	SetName( Name );
	SetParent( pParent );
	m_bHidden = false;
	m_Bounds = Gwen::Rect( 0, 0, 10, 10 );
	m_Padding = Padding( 0, 0, 0, 0 );
	m_Margin = Margin( 0, 0, 0, 0 );
	m_iDock = 0;
	m_DragAndDrop_Package = NULL;
	RestrictToParent( false );
	SetMouseInputEnabled( true );
	SetKeyboardInputEnabled( false );
	Invalidate();
	SetCursor( Gwen::CursorType::CURSOR_NORMAL );
	SetToolTip( Base::Pointer() );
	SetTabable( false );
	SetShouldDrawBackground( true );
	m_bDisabled = false;
	m_bCacheTextureDirty = true;
	m_bCacheToTexture = false;
	m_bIncludeInSize = true;
}

Gwen::Controls::Base::~Base( void )
{
	{
		auto canvas = GetCanvas();

		if ( canvas )
		{ canvas->PreDeleteCanvas( this ); }
	}
	
	Base::List::iterator iter = Children.begin();

	while ( iter != Children.end() )
	{
		auto pChild = *iter;
		iter = Children.erase( iter );
		// delete pChild; //TODO:
	}

	for ( AccelMap::iterator accelIt = m_Accelerators.begin(); accelIt != m_Accelerators.end(); ++accelIt )
	{
		delete accelIt->second;
	}

	m_Accelerators.clear();
	SetParent( NULL );

	if ( Gwen::HoveredControl == this ) 
		Gwen::HoveredControl = Controls::Base::Pointer();

	if ( Gwen::KeyboardFocus == this )
		Gwen::KeyboardFocus = Controls::Base::Pointer();

	if ( Gwen::MouseFocus == this ) 
		Gwen::MouseFocus = Controls::Base::Pointer();

	DragAndDrop::ControlDeleted( this );
	ToolTip::ControlDeleted( this );
#ifndef GWEN_NO_ANIMATION
	Anim::Cancel( this );
#endif

	if ( m_DragAndDrop_Package )
	{
#if 0
		delete m_DragAndDrop_Package;
		m_DragAndDrop_Package = NULL;
#else
		m_DragAndDrop_Package = AutoPointer<Controls::Base>();
#endif 
	}
}

void Gwen::Controls::Base::Invalidate( void )
{
	m_bNeedsLayout = true;
	m_bCacheTextureDirty = true;
}

void Gwen::Controls::Base::DelayedDelete( void )
{
	auto canvas = GetCanvas();
	canvas->AddDelayedDelete( this );
}

Gwen::AutoPointer<Gwen::Controls::Canvas> Gwen::Controls::Base::GetCanvas( void ) const
{
	auto pCanvas = m_Parent;
	if ( !pCanvas ) 
		return Canvas::Pointer();

	return pCanvas->GetCanvas();
}

void Gwen::Controls::Base::SetParent( Controls::Base::Pointer pParent )
{
	if ( m_Parent == pParent )
		return;

	if ( m_Parent )
		m_Parent->RemoveChild( this );

	m_Parent = pParent;
	m_ActualParent = Controls::Base::Pointer();

	if ( m_Parent )
		m_Parent->AddChild( this );
}

void Gwen::Controls::Base::Dock( int iDock )
{
	if ( m_iDock == iDock )
		return;

	m_iDock = iDock;
	Invalidate();
	InvalidateParent();
}

int Gwen::Controls::Base::GetDock( void )
{
	return m_iDock;
}

bool Gwen::Controls::Base::Hidden( void ) const
{
	return m_bHidden;
}

bool Gwen::Controls::Base::Visible( void ) const
{
	if ( Hidden() )
		return false;

	if ( GetParent() )
		return GetParent()->Visible();

	return true;
}

void Gwen::Controls::Base::InvalidateChildren( bool bRecursive )
{
	for ( Base::List::iterator it = Children.begin(); it != Children.end(); ++it )
	{
		( *it )->Invalidate();

		if ( bRecursive )
			( *it )->InvalidateChildren( bRecursive ); 
	}

	if ( m_InnerPanel )
	{
		for ( Base::List::iterator it = m_InnerPanel->Children.begin(); it != m_InnerPanel->Children.end(); ++it )
		{
			( *it )->Invalidate();

			if ( bRecursive )
				( *it )->InvalidateChildren( bRecursive );
		}
	}
}

void Gwen::Controls::Base::Position( int pos, int xpadding, int ypadding )
{
	const Rect & bounds = GetParent()->GetInnerBounds();
	const Margin & margin = GetMargin();
	int x = X();
	int y = Y();

	if ( pos & Pos::Left ) 
		x = bounds.x + xpadding + margin.left;

	if ( pos & Pos::Right ) 
		x = bounds.x + ( bounds.w - Width() - xpadding - margin.right );

	if ( pos & Pos::CenterH ) 
		x = bounds.x + ( bounds.w - Width() )  * 0.5;

	if ( pos & Pos::Top )
		y = bounds.y + ypadding;

	if ( pos & Pos::Bottom )
		y = bounds.y + ( bounds.h - Height() - ypadding );

	if ( pos & Pos::CenterV ) 
		y = bounds.y + ( bounds.h - Height() )  * 0.5;

	SetPos( x, y );
}

void Gwen::Controls::Base::SendToBack()
{
	if ( !m_ActualParent ) { return; }

	if ( m_ActualParent->Children.front() == this ) { return; }

	m_ActualParent->Children.remove( this );
	m_ActualParent->Children.push_front( this );
	InvalidateParent();
}

void Gwen::Controls::Base::BringToFront()
{
	if ( !m_ActualParent ) { return; }

	if ( m_ActualParent->Children.back() == this ) { return; }

	m_ActualParent->Children.remove( this );
	m_ActualParent->Children.push_back( this );
	InvalidateParent();
	Redraw();
}

Gwen::Controls::Base::Pointer Gwen::Controls::Base::FindChildByName( const Gwen::String & name, bool bRecursive )
{
	Base::List::iterator iter;

	for ( iter = Children.begin(); iter != Children.end(); ++iter )
	{
		auto pChild = *iter;

		if ( !pChild->GetName().empty() && pChild->GetName() == name )
		{ return pChild; }

		if ( bRecursive )
		{
			Controls::Base::Pointer pSubChild = pChild->FindChildByName( name, true );

			if ( pSubChild )
			{ return pSubChild; }
		}
	}

	return NULL;
}

void Gwen::Controls::Base::BringNextToControl( Controls::Base::Pointer pChild, bool bBehind )
{
	if ( !m_ActualParent ) 
		return;

	m_ActualParent->Children.remove( this );
	Base::List::iterator it = std::find( m_ActualParent->Children.begin(), m_ActualParent->Children.end(), pChild );

	if ( it == m_ActualParent->Children.end() )
	{ return BringToFront(); }

	if ( bBehind )
	{
		++it;

		if ( it == m_ActualParent->Children.end() )
		{ return BringToFront(); }
	}

	m_ActualParent->Children.insert( it, this );
	InvalidateParent();
}

void Gwen::Controls::Base::AddChild( Controls::Base::Pointer pChild )
{
	if ( m_InnerPanel )
	{
		m_InnerPanel->AddChild( pChild );
		return;
	}

	Children.push_back( pChild );
	OnChildAdded( pChild );
	pChild->m_ActualParent = this;
}
void Gwen::Controls::Base::RemoveChild( Controls::Base::Pointer pChild )
{
	// If we removed our innerpanel
	// remove our pointer to it
	if ( m_InnerPanel == pChild )
		m_InnerPanel = Controls::Base::Pointer();

	if ( m_InnerPanel )
		m_InnerPanel->RemoveChild( pChild );

	Children.remove( pChild );
	OnChildRemoved( pChild );
}

void Gwen::Controls::Base::RemoveAllChildren( void )
{
	while ( Children.size() > 0 )
	{
		RemoveChild( *Children.begin() );
	}
}

unsigned int Gwen::Controls::Base::NumChildren( void )
{
	// Include m_InnerPanel's children here?
	return Children.size();
}

Gwen::Controls::Base::Pointer Gwen::Controls::Base::GetChild( unsigned int i )
{
	if ( i >= NumChildren() )
		return Controls::Base::Pointer();

	for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
	{
		if ( i == 0 )
		{ return *iter; }

		i--;
	}

	// Should never happen.
	return NULL;
}

void Gwen::Controls::Base::OnChildAdded( Controls::Base::Pointer /*pChild*/ )
{
	Invalidate();
}

void Gwen::Controls::Base::OnChildRemoved( Controls::Base::Pointer /*pChild*/ )
{
	Invalidate();
}

Gwen::Skin::Base::Pointer Gwen::Controls::Base::GetSkin( void )
{
	if ( m_Skin )
		return m_Skin;

	if ( m_Parent )
		return m_Parent->GetSkin();

	Debug::AssertCheck( 0, "Base::GetSkin Returning NULL!\n" );
	return Skin::Base::Pointer();
}

void Gwen::Controls::Base::MoveBy( int x, int y )
{
	MoveTo( X() + x, Y() + y );
}

void Gwen::Controls::Base::MoveTo( int x, int y )
{
	if ( m_bRestrictToParent && GetParent() )
	{
		auto pParent = GetParent();

		if ( x - GetPadding().left < pParent->GetMargin().left )	{ x = pParent->GetMargin().left + GetPadding().left; }

		if ( y - GetPadding().top < pParent->GetMargin().top ) { y = pParent->GetMargin().top + GetPadding().top; }

		if ( x + Width() + GetPadding().right > pParent->Width() - pParent->GetMargin().right ) { x = pParent->Width() - pParent->GetMargin().right - Width() - GetPadding().right; }

		if ( y + Height() + GetPadding().bottom > pParent->Height() - pParent->GetMargin().bottom ) { y = pParent->Height() - pParent->GetMargin().bottom - Height() - GetPadding().bottom; }
	}

	SetBounds( x, y, Width(), Height() );
}

void Gwen::Controls::Base::SetPos( int x, int y )
{
	SetBounds( x, y, Width(), Height() );
}

bool Gwen::Controls::Base::SetSize( int w, int h )
{
	return SetBounds( X(), Y(), w, h );
}

bool Gwen::Controls::Base::SetSize( const Point & p )
{
	return SetSize( p.x, p.y );
}

bool Gwen::Controls::Base::SetBounds( const Gwen::Rect & bounds )
{
	return SetBounds( bounds.x, bounds.y, bounds.w, bounds.h );
}

bool Gwen::Controls::Base::SetBounds( int x, int y, int w, int h )
{
	if ( m_Bounds.x == x &&
			m_Bounds.y == y &&
			m_Bounds.w == w &&
			m_Bounds.h == h )
	{ return false; }

	Gwen::Rect oldBounds = GetBounds();
	m_Bounds.x = x;
	m_Bounds.y = y;
	m_Bounds.w = w;
	m_Bounds.h = h;
	OnBoundsChanged( oldBounds );
	return true;
}

void Gwen::Controls::Base::OnBoundsChanged( Gwen::Rect oldBounds )
{
	//Anything that needs to update on size changes
	//Iterate my children and tell them I've changed
	//
	if ( GetParent() )
	{ GetParent()->OnChildBoundsChanged( oldBounds, this ); }

	if ( m_Bounds.w != oldBounds.w || m_Bounds.h != oldBounds.h )
	{
		Invalidate();
	}

	Redraw();
	UpdateRenderBounds();
}

void Gwen::Controls::Base::OnScaleChanged()
{
	for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
	{
		( *iter )->OnScaleChanged();
	}
}

void Gwen::Controls::Base::OnChildBoundsChanged( Gwen::Rect oldChildBounds, Controsl::Base::Pointer pChild )
{
}

void Gwen::Controls::Base::Render( Skin::Base::Pointer /*skin*/ )
{
}

void Gwen::Controls::Base::DoCacheRender( Skin::Base::Pointer skin, Controls::Base::Pointer pMaster )
{
	Gwen::Renderer::Base::Pointer render = skin->GetRender();
	Gwen::Renderer::ICacheToTexture* cache = render->GetCTT();

	if ( !cache ) { return; }

	Gwen::Point pOldRenderOffset = render->GetRenderOffset();
	Gwen::Rect rOldRegion = render->ClipRegion();

	if ( this != pMaster )
	{
		render->AddRenderOffset( GetBounds() );
		render->AddClipRegion( GetBounds() );
	}
	else
	{
		render->SetRenderOffset( Gwen::Point( 0, 0 ) );
		render->SetClipRegion( GetBounds() );
	}

	if ( m_bCacheTextureDirty && render->ClipRegionVisible() )
	{
		render->StartClip();
		{
			if ( ShouldCacheToTexture() )
			{ cache->SetupCacheTexture( this ); }

			//Render myself first
			Render( skin );

			if ( !Children.empty() )
			{
				//Now render my kids
				for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
				{
					auto pChild = *iter;

					if ( pChild->Hidden() ) { continue; }

					pChild->DoCacheRender( skin, pMaster );
				}
			}

			if ( ShouldCacheToTexture() )
			{
				cache->FinishCacheTexture( this );
				m_bCacheTextureDirty = false;
			}
		}
		render->EndClip();
	}

	render->SetClipRegion( rOldRegion );
	render->StartClip();
	{
		render->SetRenderOffset( pOldRenderOffset );
		cache->DrawCachedControlTexture( this );
	}
	render->EndClip();
}

void Gwen::Controls::Base::DoRender( Skin::Base::Pointer skin )
{
	// If this control has a different skin,
	// then so does its children.
	if ( m_Skin )
	{ skin = m_Skin; }

	// Do think
	Think();
	Renderer::Base::Pointer render = skin->GetRender();

	if ( render->GetCTT() && ShouldCacheToTexture() )
	{
		DoCacheRender( skin, this );
		return;
	}

	RenderRecursive( skin, GetBounds() );
}

void Gwen::Controls::Base::RenderRecursive( Gwen::Skin::Base::Pointer skin, const Gwen::Rect & cliprect )
{
	Renderer::Base::Pointer render = skin->GetRender();
	Gwen::Point pOldRenderOffset = render->GetRenderOffset();
	render->AddRenderOffset( cliprect );
	RenderUnder( skin );
	Gwen::Rect rOldRegion = render->ClipRegion();

	//
	// If this control is clipping, change the clip rect to ourselves
	// ( if not then we still clip using our parents clip rect )
	//
	if ( ShouldClip() )
	{
		render->AddClipRegion( cliprect );

		if ( !render->ClipRegionVisible() )
		{
			render->SetRenderOffset( pOldRenderOffset );
			render->SetClipRegion( rOldRegion );
			return;
		}
	}

	//
	// Render this control and children controls
	//
	render->StartClip();
	{
		Render( skin );

		if ( !Children.empty() )
		{
			//Now render my kids
			for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
			{
				auto pChild = *iter;

				if ( pChild->Hidden() ) { continue; }

				pChild->DoRender( skin );
			}
		}
	}
	render->EndClip();
	//
	// Render overlay/focus
	//
	{
		render->SetClipRegion( rOldRegion );
		render->StartClip();
		{
			RenderOver( skin );
			RenderFocus( skin );
		}
		render->EndClip();
		render->SetRenderOffset( pOldRenderOffset );
	}
}

void Gwen::Controls::Base::SetSkin( Skin::Base::Pointer skin, bool doChildren )
{
	if ( m_Skin == skin ) { return; }

	m_Skin = skin;
	Invalidate();
	Redraw();
	OnSkinChanged( skin );

	if ( doChildren )
	{
		for ( Base::List::iterator it = Children.begin(); it != Children.end(); ++it )
		{
			( *it )->SetSkin( skin, true );
		}
	}
}

void Gwen::Controls::Base::OnSkinChanged( Skin::Base::Pointer /*skin*/ )
{
	//Do something
}

bool Gwen::Controls::Base::OnMouseWheeled( int iDelta )
{
	if ( m_ActualParent )
	{ return m_ActualParent->OnMouseWheeled( iDelta ); }

	return false;
}

void Gwen::Controls::Base::OnMouseMoved( const Point& /*pos*/, const Point & /*delta*/ )
{
}

void Gwen::Controls::Base::OnMouseEnter( void )
{
	onHoverEnter.Call( this );

	if ( GetToolTip() )
	{ ToolTip::Enable( this ); }
	else if ( GetParent() && GetParent()->GetToolTip() )
	{ ToolTip::Enable( GetParent() ); }

	Redraw();
}

void Gwen::Controls::Base::OnMouseLeave()
{
	onHoverLeave.Call( this );

	if ( GetToolTip() )
	{ ToolTip::Disable( this ); }

	Redraw();
}


bool Gwen::Controls::Base::IsHovered()
{
	return Gwen::HoveredControl == this;
}

bool Gwen::Controls::Base::ShouldDrawHover()
{
	return Gwen::MouseFocus == this || Gwen::MouseFocus == NULL;
}

bool Gwen::Controls::Base::HasFocus()
{
	return Gwen::KeyboardFocus == this;
}

void Gwen::Controls::Base::Focus()
{
	if ( Gwen::KeyboardFocus == this ) { return; }

	if ( Gwen::KeyboardFocus )
	{ Gwen::KeyboardFocus->OnLostKeyboardFocus(); }

	Gwen::KeyboardFocus = this;
	OnKeyboardFocus();
	Redraw();
}

void Gwen::Controls::Base::Blur()
{
	if ( Gwen::KeyboardFocus != this ) { return; }

	Gwen::KeyboardFocus = NULL;
	OnLostKeyboardFocus();
	Redraw();
}

void Gwen::Controls::Base::SetDisabled( const bool active )
{ 
	if ( m_bDisabled == active ) 
		return;

	m_bDisabled = active; 
	Redraw(); 
}
				
bool Gwen::Controls::Base::IsOnTop( void )
{
	if ( !GetParent() )
		return false;

	Base::List::iterator iter = GetParent()->Children.begin();
	auto pChild = *iter;

	if ( pChild == this )
	{ return true; }

	return false;
}


void Gwen::Controls::Base::Touch()
{
	if ( GetParent() )
		GetParent()->OnChildTouched( this );
}

void Gwen::Controls::Base::OnChildTouched( Controls::Base::Pointer /*pChild*/ )
{
	Touch();
}

Gwen::Controls::Base::Pointer Gwen::Controls::Base::GetControlAt( const Point &in_pos, bool bOnlyIfMouseEnabled )
{
	if ( Hidden() )
		return Controls::Base::Pointer();

	if ( in_pos.x < 0 || in_pos.y < 0 || in_pos.x >= Width() || in_pos.y >= Height() )
		return Controls::Base::Pointer();

	Base::List::reverse_iterator iter;

	for ( iter = Children.rbegin(); iter != Children.rend(); ++iter )
	{
		Base::Pointer pChild = *iter;
		Base::Pointer pFound = Base::Pointer();
		pFound = pChild->GetControlAt( Gwen::Point( in_pos.x - pChild->X(), in_pos.y - pChild->Y() ), bOnlyIfMouseEnabled );

		if ( pFound ) 
			return pFound;
	}

	if ( bOnlyIfMouseEnabled && !GetMouseInputEnabled() )
		return Base::Pointer();

	return this;
}


void Gwen::Controls::Base::Layout( Skin::Base::Pointer skin )
{
	if ( skin->GetRender()->GetCTT() && ShouldCacheToTexture() )
	{ skin->GetRender()->GetCTT()->CreateControlCacheTexture( this ); }
}

void Gwen::Controls::Base::RecurseLayout( Skin::Base::Pointer skin )
{
	if ( m_Skin )
		skin = m_Skin;

	if ( Hidden() )
		return;

	if ( NeedsLayout() )
	{
		m_bNeedsLayout = false;
		Layout( skin );
	}

	Gwen::Rect rBounds = GetRenderBounds();
	// Adjust bounds for padding
	rBounds.x += m_Padding.left;
	rBounds.w -= m_Padding.left + m_Padding.right;
	rBounds.y += m_Padding.top;
	rBounds.h -= m_Padding.top + m_Padding.bottom;

	for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
	{
		auto pChild = *iter;

		if ( pChild->Hidden() )
			continue;

		int iDock = pChild->GetDock();

		if ( iDock & Pos::Fill )
			continue;

		if ( iDock & Pos::Top )
		{
			const Margin & margin = pChild->GetMargin();
			pChild->SetBounds( rBounds.x + margin.left, rBounds.y + margin.top, rBounds.w - margin.left - margin.right, pChild->Height() );
			int iHeight = margin.top + margin.bottom + pChild->Height();
			rBounds.y += iHeight;
			rBounds.h -= iHeight;
		}

		if ( iDock & Pos::Left )
		{
			const Margin & margin = pChild->GetMargin();
			pChild->SetBounds( rBounds.x + margin.left, rBounds.y + margin.top, pChild->Width(), rBounds.h - margin.top - margin.bottom );
			int iWidth = margin.left + margin.right + pChild->Width();
			rBounds.x += iWidth;
			rBounds.w -= iWidth;
		}

		if ( iDock & Pos::Right )
		{
			// TODO: THIS MARGIN CODE MIGHT NOT BE FULLY FUNCTIONAL
			const Margin & margin = pChild->GetMargin();
			pChild->SetBounds( ( rBounds.x + rBounds.w ) - pChild->Width() - margin.right, rBounds.y + margin.top, pChild->Width(), rBounds.h - margin.top - margin.bottom );
			int iWidth = margin.left + margin.right + pChild->Width();
			rBounds.w -= iWidth;
		}

		if ( iDock & Pos::Bottom )
		{
			// TODO: THIS MARGIN CODE MIGHT NOT BE FULLY FUNCTIONAL
			const Margin & margin = pChild->GetMargin();
			pChild->SetBounds( rBounds.x + margin.left, ( rBounds.y + rBounds.h ) - pChild->Height() - margin.bottom, rBounds.w - margin.left - margin.right, pChild->Height() );
			rBounds.h -= pChild->Height() + margin.bottom + margin.top;
		}

		pChild->RecurseLayout( skin );
	}

	m_InnerBounds = rBounds;

	//
	// Fill uses the left over space, so do that now.
	//
	for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
	{
		auto pChild = *iter;
		int iDock = pChild->GetDock();

		if ( !( iDock & Pos::Fill ) )
		{ continue; }

		const Margin & margin = pChild->GetMargin();
		pChild->SetBounds( rBounds.x + margin.left, rBounds.y + margin.top, rBounds.w - margin.left - margin.right, rBounds.h - margin.top - margin.bottom );
		pChild->RecurseLayout( skin );
	}

	PostLayout( skin );

	if ( IsTabable() && !IsDisabled() )
	{
		if ( !GetCanvas()->FirstTab ) { GetCanvas()->FirstTab = this; }

		if ( !GetCanvas()->NextTab ) { GetCanvas()->NextTab = this; }
	}

	if ( Gwen::KeyboardFocus == this )
	{
		GetCanvas()->NextTab = NULL;
	}
}

bool Gwen::Controls::Base::IsChild( Controls::Base::Pointer pChild )
{
	for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
	{
		if ( pChild == ( *iter ) ) 
			return true;
	}

	return false;
}

Gwen::Point Gwen::Controls::Base::LocalPosToCanvas( const Gwen::Point & pnt )
{
	if ( m_Parent )
	{
		int x = pnt.x + X();
		int y = pnt.y + Y();

		// If our parent has an innerpanel and we're a child of it
		// add its offset onto us.
		//
		if ( m_Parent->m_InnerPanel && m_Parent->m_InnerPanel->IsChild( this ) )
		{
			x += m_Parent->m_InnerPanel->X();
			y += m_Parent->m_InnerPanel->Y();
		}

		return m_Parent->LocalPosToCanvas( Gwen::Point( x, y ) );
	}

	return pnt;
}

Gwen::Point Gwen::Controls::Base::CanvasPosToLocal( const Gwen::Point & pnt )
{
	if ( m_Parent )
	{
		int x = pnt.x - X();
		int y = pnt.y - Y();

		// If our parent has an innerpanel and we're a child of it
		// add its offset onto us.
		//
		if ( m_Parent->m_InnerPanel && m_Parent->m_InnerPanel->IsChild( this ) )
		{
			x -= m_Parent->m_InnerPanel->X();
			y -= m_Parent->m_InnerPanel->Y();
		}

		return m_Parent->CanvasPosToLocal( Gwen::Point( x, y ) );
	}

	return pnt;
}

bool Gwen::Controls::Base::IsMenuComponent( void )
{
	if ( !m_Parent )
		return false;

	return m_Parent->IsMenuComponent();
}

void Gwen::Controls::Base::CloseMenus( void )
{
	for ( Base::List::iterator it = Children.begin(); it != Children.end(); ++it )
	{
		( *it )->CloseMenus();
	}
}

void Gwen::Controls::Base::UpdateRenderBounds( void )
{
	m_RenderBounds.x = 0;
	m_RenderBounds.y = 0;
	m_RenderBounds.w = m_Bounds.w;
	m_RenderBounds.h = m_Bounds.h;
}

void Gwen::Controls::Base::UpdateCursor( void )
{
	Debug::AssertCheck( m_Platform != nullptr, "m_Platform Returning NULL!\n" );
	m_Platform->SetCursor( m_Cursor );
}

Gwen::AutoPointer<Gwen::DragAndDrop::Package> Gwen::Controls::Base::DragAndDrop_GetPackage( const Gwen::Point &in_pos )
{
	return m_DragAndDrop_Package;
}

bool Gwen::Controls::Base::DragAndDrop_HandleDrop( Gwen::DragAndDrop::Package::Pointer /*pPackage*/, const Gwen::Point &in_pos )
{
	DragAndDrop::SourceControl->SetParent( this );
	return true;
}

bool Gwen::Controls::Base::DragAndDrop_Draggable( void )
{
	if ( !m_DragAndDrop_Package )
		return false;
	return m_DragAndDrop_Package->draggable;
}

void Gwen::Controls::Base::DragAndDrop_SetPackage( bool bDraggable, const String & strName, void* pUserData )
{
	if ( !m_DragAndDrop_Package )
		m_DragAndDrop_Package = new Gwen::DragAndDrop::Package();

	m_DragAndDrop_Package->draggable = bDraggable;
	m_DragAndDrop_Package->name = strName;
	m_DragAndDrop_Package->userdata = pUserData;
}

void Gwen::Controls::Base::DragAndDrop_StartDragging( Gwen::DragAndDrop::Package::Pointer pPackage, const Point &in_pos )
{
	pPackage->holdoffset = CanvasPosToLocal( in_pos );
	pPackage->drawcontrol = this;
}

bool Gwen::Controls::Base::SizeToChildren( bool w, bool h )
{
	Gwen::Point size = ChildrenSize();
	size.y += GetPadding().bottom;
	size.x += GetPadding().right;
	return SetSize( w ? size.x : Width(), h ? size.y : Height() );
}

Gwen::Point Gwen::Controls::Base::ChildrenSize( void )
{
	Gwen::Point size;

	for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
	{
		auto pChild = *iter;

		if ( pChild->Hidden() )
			continue; 

		if ( !pChild->ShouldIncludeInSize() )
			continue;

		size.x = Gwen::Max( size.x, pChild->Right() );
		size.y = Gwen::Max( size.y, pChild->Bottom() );
	}

	return size;
}

void Gwen::Controls::Base::SetPadding( const Gwen::Padding & padding )
{
	if ( m_Padding.left == padding.left &&
			m_Padding.top == padding.top &&
			m_Padding.right == padding.right &&
			m_Padding.bottom == padding.bottom )
	{ return; }

	m_Padding = padding;
	Invalidate();
	InvalidateParent();
}

void Gwen::Controls::Base::SetMargin( const Margin & margin )
{
	if ( m_Margin.top == margin.top &&
			m_Margin.left == margin.left &&
			m_Margin.bottom == margin.bottom &&
			m_Margin.right == margin.right )
	{ return; }

	m_Margin = margin;
	Invalidate();
	InvalidateParent();
}

bool Gwen::Controls::Base::HandleAccelerator( Gwen::UnicodeString & accelerator )
{
	if ( Gwen::KeyboardFocus == this || !AccelOnlyFocus() )
	{
		AccelMap::iterator iter = m_Accelerators.find( accelerator );

		if ( iter != m_Accelerators.end() )
		{
			iter->second->Call( this );
			return true;
		}
	}

	for ( Base::List::iterator it = Children.begin(); it != Children.end(); ++it )
	{
		if ( ( *it )->HandleAccelerator( accelerator ) )
			return true;
	}

	return false;
}

bool Gwen::Controls::Base::OnKeyPress( int iKey, bool bPress )
{
	bool bHandled = false;

	switch ( iKey )
	{
		case Key::Tab:
			bHandled = OnKeyTab( bPress );
			break;

		case Key::Space:
			bHandled = OnKeySpace( bPress );
			break;

		case Key::Home:
			bHandled = OnKeyHome( bPress );
			break;

		case Key::End:
			bHandled = OnKeyEnd( bPress );
			break;

		case Key::Return:
			bHandled = OnKeyReturn( bPress );
			break;

		case Key::Backspace:
			bHandled = OnKeyBackspace( bPress );
			break;

		case Key::Delete:
			bHandled = OnKeyDelete( bPress );
			break;

		case Key::Right:
			bHandled = OnKeyRight( bPress );
			break;

		case Key::Left:
			bHandled = OnKeyLeft( bPress );
			break;

		case Key::Up:
			bHandled = OnKeyUp( bPress );
			break;

		case Key::Down:
			bHandled = OnKeyDown( bPress );
			break;

		case Key::Escape:
			bHandled = OnKeyEscape( bPress );
			break;

		default:
			break;
	}

	if ( !bHandled && GetParent() )
	{ GetParent()->OnKeyPress( iKey, bPress ); }

	return bHandled;
}

bool Gwen::Controls::Base::OnKeyRelease( int iKey )
{
	return OnKeyPress( iKey, false );
}

bool Gwen::Controls::Base::OnKeyTab( bool bDown )
{
	if ( !bDown ) { return true; }

	if ( GetCanvas()->NextTab )
	{
		GetCanvas()->NextTab->Focus();
		Redraw();
	}

	return true;
}

void Gwen::Controls::Base::RenderFocus( AutoPointer<Skin::Base> skin )
{
	if ( Gwen::KeyboardFocus != this ) { return; }

	if ( !IsTabable() ) { return; }

	skin->DrawKeyboardHighlight( this, GetRenderBounds(), 3 );
}

void Gwen::Controls::Base::SetToolTip( const TextObject & strText )
{
	AutoPointer<Label> tooltip = new Controls::Label( this );
	tooltip->SetText( strText );
	tooltip->SetTextColorOverride( GetSkin()->Colors.TooltipText );
	tooltip->SetPadding( Padding( 5, 3, 5, 3 ) );
	tooltip->SizeToContents();
	SetToolTip( tooltip );
}

TextObject Gwen::Controls::Base::GetChildValue( const Gwen::String & strName )
{
	auto pChild = FindChildByName( strName, true );

	if ( !pChild ) { return ""; }

	return pChild->GetValue();
}

Gwen::TextObject Gwen::Controls::Base::GetValue()
{
	// Generic value accessor should be filled in if we have a value to give.
	return "";
}

void Gwen::Controls::Base::SetValue( const TextObject & strValue )
{
}

int Gwen::Controls::Base::GetNamedChildren( Gwen::ControlList & list, const Gwen::String & strName, bool bDeep )
{
	int iFound = 0;
	Base::List::iterator iter;

	for ( iter = Children.begin(); iter != Children.end(); ++iter )
	{
		Base* pChild = *iter;

		if ( !pChild->GetName().empty() && pChild->GetName() == strName )
		{
			list.Add( pChild );
			iFound++;
		}

		if ( !bDeep ) { continue; }

		iFound += pChild->GetNamedChildren( list, strName, bDeep );
	}

	return iFound;
}

Gwen::ControlList Gwen::Controls::Base::GetNamedChildren( const Gwen::String & strName, bool bDeep )
{
	Gwen::ControlList list;
	GetNamedChildren( list, strName, bDeep );
	return list;
}

#ifndef GWEN_NO_ANIMATION

void Gwen::Controls::Base::Anim_WidthIn( float fLength, float fDelay, float fEase )
{
	Gwen::Anim::Add( this, new Gwen::Anim::Size::Width( 0, Width(), fLength, false, fDelay, fEase ) );
	SetWidth( 0 );
}

void Gwen::Controls::Base::Anim_HeightIn( float fLength, float fDelay, float fEase )
{
	Gwen::Anim::Add( this, new Gwen::Anim::Size::Height( 0, Height(), fLength, false, fDelay, fEase ) );
	SetHeight( 0 );
}

void Gwen::Controls::Base::Anim_WidthOut( float fLength, bool bHide, float fDelay, float fEase )
{
	Gwen::Anim::Add( this, new Gwen::Anim::Size::Width( Width(), 0, fLength, bHide, fDelay, fEase ) );
}

void Gwen::Controls::Base::Anim_HeightOut( float fLength, bool bHide, float fDelay, float fEase )
{
	Gwen::Anim::Add( this, new Gwen::Anim::Size::Height( Height(), 0, fLength, bHide, fDelay, fEase ) );
}

#endif
