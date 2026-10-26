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

#include "Gwen/Controls/WindowCanvas.hpp"
#include "Gwen/Platform/Platform.hpp"

#ifndef GWEN_NO_ANIMATION
#include "Gwen/Anim.h"
#endif

Gwen::Controls::WindowCanvas::WindowCanvas( AutoPointer<Platform::Base> &pPlatform, AutoPointer<Skin::Base>	 &pSkin, int x, int y, int w, int h, const Gwen::String & strWindowTitle ) : BaseClass( NULL )
{
	m_pOSPlatform = pPlatform;
	m_bQuit = false;
	m_bIsMaximized = false;
	m_bCanMaximize = true;
	SetPadding( Padding( 1, 0, 1, 1 ) );
	// Centering the window on the desktop
	{
		Point wh;
		m_pOSPlatform->GetDesktopSize( wh );

		if ( x < 0 )
			x = ( wh.x - w ) * 0.5;

		if ( y < 0 )
			y = ( wh.y - h ) * 0.5; 
	}

	m_pOSWindow = m_pOSPlatform->NewWindow();
	if( m_pOSWindow->Create( { x, y, w, h }, strWindowTitle ) )
		throw std::runtime_error( "Failed to create window" );
	
	m_WindowPos  = Gwen::Point( x, y );
	pSkin->GetRender()->InitializeContext( this );
	pSkin->GetRender()->Init();
	m_pSkinChange = pSkin;
	SetSize( w, h );
	m_TitleBar = new Gwen::ControlsInternal::Dragger( this );
	m_TitleBar->SetHeight( 24 );
	m_TitleBar->SetPadding( Padding( 0, 0, 0, 0 ) );
	m_TitleBar->SetMargin( Margin( 0, 0, 0, 0 ) );
	m_TitleBar->Dock( Pos::Top );
	m_TitleBar->SetDoMove( false );
	m_TitleBar->onDragged.Add( this, &ThisClass::Dragger_Moved );
	m_TitleBar->onDragStart.Add( this, &ThisClass::Dragger_Start );
	m_TitleBar->onDoubleClickLeft.Add( this, &ThisClass::OnTitleDoubleClicked );
	m_Title = new Gwen::Controls::Label( m_TitleBar );
	m_Title->SetAlignment( Pos::Left | Pos::CenterV );
	m_Title->SetText( strWindowTitle );
	m_Title->Dock( Pos::Fill );
	m_Title->SetPadding( Padding( 8, 0, 0, 0 ) );
	m_Title->SetTextColor( GetSkin()->Colors.Window.TitleInactive );
	// CLOSE
	{
		m_pClose = new Gwen::Controls::WindowCloseButton( m_TitleBar, "Close" );
		m_pClose->Dock( Pos::Right );
		m_pClose->SetMargin( Margin( 0, 0, 4, 0 ) );
		m_pClose->onPress.Add( this, &WindowCanvas::CloseButtonPressed );
		m_pClose->SetTabable( false );
		m_pClose->SetWindow( this );
	}
	// MAXIMIZE
	{
		m_pMaximize = new Gwen::Controls::WindowMaximizeButton( m_TitleBar, "Maximize" );
		m_pMaximize->Dock( Pos::Right );
		m_pMaximize->onPress.Add( this, &WindowCanvas::MaximizeButtonPressed );
		m_pMaximize->SetTabable( false );
		m_pMaximize->SetWindow( this );
	}
	// MINIMiZE
	{
		m_pMinimize = new Gwen::Controls::WindowMinimizeButton( m_TitleBar, "Minimize" );
		m_pMinimize->Dock( Pos::Right );
		m_pMinimize->onPress.Add( this, &WindowCanvas::MinimizeButtonPressed );
		m_pMinimize->SetTabable( false );
		m_pMinimize->SetWindow( this );
	}
	// Bottom Right Corner Sizer
	{
		m_Sizer = new Gwen::ControlsInternal::Dragger( this );
		m_Sizer->SetSize( 16, 16 );
		m_Sizer->SetDoMove( false );
		m_Sizer->onDragged.Add( this, &WindowCanvas::Sizer_Moved );
		m_Sizer->onDragStart.Add( this, &WindowCanvas::Dragger_Start );
		m_Sizer->SetCursor( Gwen::CursorType::SizeNWSE );
	}
}

Gwen::Controls::WindowCanvas::WindowCanvas::~WindowCanvas( void )
{
	DestroyWindow();
}

void* Gwen::Controls::WindowCanvas::WindowCanvas::GetWindow( void )
{
	return m_pOSWindow;
}

void Gwen::Controls::WindowCanvas::WindowCanvas::Layout( Skin::Base* skin )
{
	m_Sizer->BringToFront();
	m_Sizer->Position( Pos::Right | Pos::Bottom );
	BaseClass::Layout( skin );
}

void Gwen::Controls::WindowCanvas::WindowCanvas::DoThink( void )
{
	Platform::MessagePump( m_pOSWindow, this );
	BaseClass::DoThink();
	RenderCanvas();
}

void Gwen::Controls::WindowCanvas::WindowCanvas::RenderCanvas( void )
{
	//
	// If there isn't anything going on we sleep the thread for a few ms
	// This gives some cpu time back to the os. If you're using a rendering
	// method that needs continual updates, just call canvas->redraw every frame.
	//
	if ( !NeedsRedraw() )
	{
		Platform::Sleep( 10 );
		return;
	}

	m_bNeedsRedraw = false;
	Gwen::Renderer::Base* render = m_Skin->GetRender();

	if ( render->BeginContext( this ) )
	{
		render->Begin();
		RecurseLayout( m_Skin );
		render->SetClipRegion( GetRenderBounds() );
		render->SetRenderOffset( Gwen::Point( X() * -1, Y() * -1 ) );
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

	render->EndContext( this );
	render->PresentContext( this );
}

void Gwen::Controls::WindowCanvas::WindowCanvas::Render( Skin::Base* skin )
{
	bool bHasFocus = IsOnTop();

	if ( bHasFocus )
	{ m_Title->SetTextColor( GetSkin()->Colors.Window.TitleActive ); }
	else
	{ m_Title->SetTextColor( GetSkin()->Colors.Window.TitleInactive ); }

	skin->DrawWindow( this, m_TitleBar->Bottom(), bHasFocus );
}


void Gwen::Controls::WindowCanvas::WindowCanvas::DestroyWindow( void )
{
	if ( m_pOSWindow )
	{
		GetSkin()->GetRender()->ShutdownContext( this );
		Gwen::Platform::DestroyPlatformWindow( m_pOSWindow );
		m_pOSWindow = NULL;
	}
}

bool Gwen::Controls::WindowCanvas::WindowCanvas::InputQuit( void )
{
	m_bQuit = true;
	return true;
}

Gwen::Skin::Base Gwen::Controls::WindowCanvas::WindowCanvas::GetSkin( void )
{
	if ( m_pSkinChange )
	{
		SetSkin( m_pSkinChange );
		m_pSkinChange = NULL;
	}

	return BaseClass::GetSkin();
}

void Gwen::Controls::WindowCanvas::WindowCanvas::Dragger_Start( void )
{
	Gwen::Platform::GetCursorPos( m_HoldPos );
	m_HoldPos.x -= m_WindowPos.x;
	m_HoldPos.y -= m_WindowPos.y;
}

void Gwen::Controls::WindowCanvas::WindowCanvas::Dragger_Moved( void )
{
	Gwen::Point p;
	Gwen::Platform::GetCursorPos( p );

	//
	// Dragged out of maximized
	//
	if ( m_bIsMaximized )
	{
		float fOldWidth = Width();
		SetMaximize( false );
		// Change the hold pos to be the same distance across the titlebar of the resized window
		m_HoldPos.x = ( ( float ) m_HoldPos.x ) * ( ( float ) Width() / fOldWidth );
		m_HoldPos.y = 10;
	}

	SetPos( p.x - m_HoldPos.x, p.y - m_HoldPos.y );
}

void Gwen::Controls::WindowCanvas::WindowCanvas::SetPos( int x, int y )
{
	int w, h;
	Gwen::Platform::GetDesktopSize( w, h );
	y = Gwen::Clamp( y, 0, h );
	m_WindowPos.x = x;
	m_WindowPos.y = y;
	Gwen::Platform::SetBoundsPlatformWindow( m_pOSWindow, x, y, Width(), Height() );
}

void Gwen::Controls::WindowCanvas::WindowCanvas::CloseButtonPressed( void )
{
	InputQuit();
}

bool Gwen::Controls::WindowCanvas::WindowCanvas::IsOnTop( void )
{
	return Gwen::Platform::HasFocusPlatformWindow( m_pOSWindow );
}


void Gwen::Controls::WindowCanvas::WindowCanvas::Sizer_Moved( void )
{
	Gwen::Point p;
	Gwen::Platform::GetCursorPos( p );
	int w = ( p.x ) - m_WindowPos.x;
	int h = ( p.y ) - m_WindowPos.y;
	w = Clamp( w, 100, 9999 );
	h = Clamp( h, 100, 9999 );
	Gwen::Platform::SetBoundsPlatformWindow( m_pOSWindow, m_WindowPos.x, m_WindowPos.y, w, h );
	GetSkin()->GetRender()->ResizedContext( this, w, h );
	this->SetSize( w, h );
	BaseClass::DoThink();
	RenderCanvas();
}

void Gwen::Controls::WindowCanvas::WindowCanvas::OnTitleDoubleClicked()
{
	if ( !CanMaximize() ) { return; }

	SetMaximize( !m_bIsMaximized );
}

void Gwen::Controls::WindowCanvas::WindowCanvas::SetMaximize( bool b )
{
	m_bIsMaximized = b;
	m_pMaximize->SetMaximized( m_bIsMaximized );
	Gwen::Point pSize, pPos;
	Gwen::Platform::SetWindowMaximized( m_pOSWindow, m_bIsMaximized, pPos, pSize );
	SetSize( pSize.x, pSize.y );
	m_WindowPos = pPos;
	GetSkin()->GetRender()->ResizedContext( this, pSize.x, pSize.y );
	BaseClass::DoThink();
	RenderCanvas();
}

void Gwen::Controls::WindowCanvas::WindowCanvas::MaximizeButtonPressed()
{
	if ( !CanMaximize() ) { return; }

	SetMaximize( !m_bIsMaximized );
}

void Gwen::Controls::WindowCanvas::WindowCanvas::MinimizeButtonPressed()
{
	Gwen::Platform::SetWindowMinimized( m_pOSWindow, true );
}

void Gwen::Controls::WindowCanvas::WindowCanvas::SetCanMaximize( bool b )
{
	if ( m_bCanMaximize == b ) { return; }

	m_bCanMaximize = b;
	m_pMaximize->SetDisabled( !b );
}