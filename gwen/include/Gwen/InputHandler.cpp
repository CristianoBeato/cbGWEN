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

#include "Gwen/InputHandler.hpp"
#include "Gwen/Hook.h"

constexpr float DOUBLE_CLICK_SPEED = 0.5f;
constexpr int MAX_MOUSE_BUTTONS = 5;

// Globals
GWEN_EXPORT Gwen::AutoPointer<Gwen::Controls::Base> HoveredControl = Gwen::AutoPointer<Gwen::Controls::Base>();
GWEN_EXPORT Gwen::AutoPointer<Gwen::Controls::Base> KeyboardFocus = Gwen::AutoPointer<Gwen::Controls::Base>();
GWEN_EXPORT Gwen::AutoPointer<Gwen::Controls::Base> MouseFocus = Gwen::AutoPointer<Gwen::Controls::Base>();

struct Action
{
	unsigned char type;

	int x, y;
	Gwen::UnicodeChar chr;
};

static const float KeyRepeatRate = 0.03f;
static const float KeyRepeatDelay = 0.3f;

struct t_KeyData
{
	t_KeyData()
	{
		for ( int i = 0; i < Gwen::Key::Count; i++ )
		{
			KeyState[i] = false;
			NextRepeat[i] = 0;
		}

		Target = Gwen::AutoPointer<Gwen::Controls::Base>();
		LeftMouseDown = false;
		RightMouseDown = false;
	}

	bool LeftMouseDown;
	bool RightMouseDown;
	bool KeyState[ Gwen::Key::Count ];
	float NextRepeat[ Gwen::Key::Count ];
	Gwen::AutoPointer<Gwen::Controls::Base> Target;

} KeyData;

Gwen::Point	MousePosition;

static float		g_fLastClickTime[MAX_MOUSE_BUTTONS];
static Gwen::Point	g_pntLastClickPos;

enum
{
	ACT_MOUSEMOVE,
	ACT_MOUSEBUTTON,
	ACT_CHAR,
	ACT_MOUSEWHEEL,
	ACT_KEYPRESS,
	ACT_KEYRELEASE,
	ACT_MESSAGE
};

static void UpdateHoveredControl( Gwen::Controls::Base::Pointer pInCanvas )
{
	Gwen::AutoPointer<Gwen::Controls::Base> pHovered = pInCanvas->GetControlAt( MousePosition );

	if ( pHovered != Gwen::HoveredControl )
	{
		if ( Gwen::HoveredControl )
		{
			Gwen::AutoPointer<Gwen::Controls::Base> OldHover = Gwen::HoveredControl;
			Gwen::HoveredControl = NULL;
			OldHover->OnMouseLeave();
		}

		Gwen::HoveredControl = pHovered;

		if ( Gwen::HoveredControl )
			Gwen::HoveredControl->OnMouseEnter();
	}

	Gwen::Controls::Canvas::Pointer canvas = Gwen::MouseFocus->GetCanvas();
	if ( Gwen::MouseFocus && ( canvas == pInCanvas ) )
	{
		if ( Gwen::HoveredControl )
		{
			Gwen::AutoPointer<Gwen::Controls::Base> OldHover = Gwen::HoveredControl;
			Gwen::HoveredControl = NULL;
			OldHover->Redraw();
		}

		Gwen::HoveredControl = Gwen::MouseFocus;
	}
}

static bool FindKeyboardFocus( Gwen::Controls::Base::Pointer pControl )
{
	if ( !pControl )
		return false;

	if ( pControl->GetKeyboardInputEnabled() )
	{
		//Make sure none of our children have keyboard focus first - todo recursive
		for ( Gwen::Controls::Base::List::iterator iter = pControl->Children.begin(); iter != pControl->Children.end(); ++iter )
		{
			Gwen::Controls::Base::Pointer pChild = *iter;

			if ( pChild == Gwen::KeyboardFocus )
				return false;
		}

		pControl->Focus();
		return true;
	}

	return FindKeyboardFocus( pControl->GetParent() );
}

Gwen::Point Gwen::Input::GetMousePosition()
{
	return MousePosition;
}

void Gwen::Input::OnCanvasThink( Gwen::AutoPointer<Gwen::Controls::Base> pControl )
{
	auto platform = pControl->GetPlatfom();
	if ( Gwen::MouseFocus && !Gwen::MouseFocus->Visible() )
		Gwen::MouseFocus = NULL;

	if ( Gwen::KeyboardFocus && ( !Gwen::KeyboardFocus->Visible() ||  !KeyboardFocus->GetKeyboardInputEnabled() ) )
		Gwen::KeyboardFocus = NULL;

	if ( !KeyboardFocus )
		return;

	if ( KeyboardFocus->GetCanvas() != pControl )
		return;

	float fTime = platform->GetTimeInSeconds();

	//
	// Simulate Key-Repeats
	//
	for ( int i = 0; i < Gwen::Key::Count; i++ )
	{
		if ( KeyData.KeyState[i] && KeyData.Target != KeyboardFocus )
		{
			KeyData.KeyState[i] = false;
			continue;
		}

		if ( KeyData.KeyState[i] && fTime > KeyData.NextRepeat[i] )
		{
			KeyData.NextRepeat[i] = platform->GetTimeInSeconds() + KeyRepeatRate;

			if ( KeyboardFocus )
			{
				KeyboardFocus->OnKeyPress( i );
			}
		}
	}
}

bool Gwen::Input::IsKeyDown( int iKey )
{
	return KeyData.KeyState[ iKey ];
}

bool Gwen::Input::IsLeftMouseDown()
{
	return KeyData.LeftMouseDown;
}

bool Gwen::Input::IsRightMouseDown()
{
	return KeyData.RightMouseDown;
}

void Gwen::Input::OnMouseMoved( AutoPointer<Controls::Base> pCanvas, const Point &in_pos, const Point &in_delta )
{
	MousePosition = in_pos;
	UpdateHoveredControl( pCanvas );
}

bool Gwen::Input::OnMouseClicked( AutoPointer<Controls::Base> pCanvas, int iMouseButton, bool bDown )
{
	// If we click on a control that isn't a menu we want to close
	// all the open menus. Menus are children of the canvas.
	if ( bDown && ( !Gwen::HoveredControl || !Gwen::HoveredControl->IsMenuComponent() ) )
	{
		pCanvas->CloseMenus();
	}

	if ( !Gwen::HoveredControl ) { return false; }

	if ( Gwen::HoveredControl->GetCanvas() != pCanvas )
		return false;

	if ( !Gwen::HoveredControl->Visible() ) { return false; }

	if ( Gwen::HoveredControl == pCanvas ) { return false; }

	if ( iMouseButton >= MAX_MOUSE_BUTTONS )
	{ return false; }

	if ( iMouseButton == 0 )		{ KeyData.LeftMouseDown = bDown; }
	else if ( iMouseButton == 1 )	{ KeyData.RightMouseDown = bDown; }

	// Double click.
	// Todo: Shouldn't double click if mouse has moved significantly
	bool bIsDoubleClick = false;

	auto platform = pCanvas->GetPlatfom();
	if ( bDown &&
			g_pntLastClickPos.x == MousePosition.x &&
			g_pntLastClickPos.y == MousePosition.y &&
			( platform->GetTimeInSeconds() - g_fLastClickTime[ iMouseButton ] ) < DOUBLE_CLICK_SPEED )
	{
		bIsDoubleClick = true;
	}

	if ( bDown && !bIsDoubleClick )
	{
		g_fLastClickTime[ iMouseButton ] = platform->GetTimeInSeconds();
		g_pntLastClickPos = MousePosition;
	}

	if ( bDown )
	{
		if ( !FindKeyboardFocus( Gwen::HoveredControl ) )
		{
			if ( Gwen::KeyboardFocus )
			{ Gwen::KeyboardFocus->Blur(); }
		}
	}

	Gwen::HoveredControl->UpdateCursor();

	// This tells the child it has been touched, which
	// in turn tells its parents, who tell their parents.
	// This is basically so that Windows can pop themselves
	// to the top when one of their children have been clicked.
	if ( bDown )
	{ Gwen::HoveredControl->Touch(); }

#ifdef GWEN_HOOKSYSTEM

	if ( bDown )
	{
		if ( Gwen::Hook::CallHook( &Gwen::Hook::BaseHook::OnControlClicked, Gwen::HoveredControl, MousePosition ) )
		{ return true; }
	}

#endif

	switch ( iMouseButton )
	{
		case 0:
			{
				if ( DragAndDrop::OnMouseButton( Gwen::HoveredControl, MousePosition, bDown ) )
				{ return true; }

				if ( bIsDoubleClick )	{ Gwen::HoveredControl->OnMouseDoubleClickLeft( MousePosition ); }
				else					{ Gwen::HoveredControl->OnMouseClickLeft( MousePosition, bDown ); }

				return true;
			}

		case 1:
			{
				if ( bIsDoubleClick )	{ Gwen::HoveredControl->OnMouseDoubleClickRight( MousePosition ); }
				else					{ Gwen::HoveredControl->OnMouseClickRight( MousePosition, bDown ); }

				return true;
			}
	}

	return false;
}

bool Gwen::Input::HandleAccelerator( AutoPointer<Controls::Base> pCanvas, Gwen::UnicodeChar chr )
{
	//Build the accelerator search string
	Gwen::UnicodeString accelString;

	if ( Gwen::Input::IsControlDown() )
	{ accelString += L"CTRL+"; }

	if ( Gwen::Input::IsShiftDown() )
	{ accelString += L"SHIFT+"; }

	chr = towupper( chr );
	accelString += chr;

	//Debug::Msg("Accelerator string :%S\n", accelString.c_str());

	if ( Gwen::KeyboardFocus && Gwen::KeyboardFocus->HandleAccelerator( accelString ) )
	{ return true; }

	if ( Gwen::MouseFocus && Gwen::MouseFocus->HandleAccelerator( accelString ) )
	{ return true; }

	if ( pCanvas->HandleAccelerator( accelString ) )
	{ return true; }

	return false;
}

bool Gwen::Input::DoSpecialKeys( AutoPointer<Controls::Base> pCanvas, Gwen::UnicodeChar chr )
{
	if ( !Gwen::KeyboardFocus ) { return false; }

	if ( Gwen::KeyboardFocus->GetCanvas() != pCanvas ) { return false; }

	if ( !Gwen::KeyboardFocus->Visible() ) { return false; }

	if ( !Gwen::Input::IsControlDown() ) { return false; }

	if ( chr == L'C' || chr == L'c' )
	{
		Gwen::KeyboardFocus->OnCopy( NULL );
		return true;
	}

	if ( chr == L'V' || chr == L'v' )
	{
		Gwen::KeyboardFocus->OnPaste( NULL );
		return true;
	}

	if ( chr == L'X' || chr == L'x' )
	{
		Gwen::KeyboardFocus->OnCut( NULL );
		return true;
	}

	if ( chr == L'A' || chr == L'a' )
	{
		Gwen::KeyboardFocus->OnSelectAll( NULL );
		return true;
	}

	return false;
}

bool Gwen::Input::OnKeyEvent( AutoPointer<Controls::Base> pCanvas, int iKey, bool bDown )
{
	Controls::Base::Pointer pTarget = Gwen::KeyboardFocus;

	if ( pTarget && pTarget->GetCanvas() != pCanvas ) 
		pTarget = Controls::Base::Pointer();

	if ( pTarget && !pTarget->Visible() ) 
		pTarget = Controls::Base::Pointer();

	if ( bDown )
	{
		if ( !KeyData.KeyState[ iKey ] )
		{
			auto platform = pCanvas->GetPlatfom();
			KeyData.KeyState[ iKey ] = true;
			KeyData.NextRepeat[ iKey ] = platform->GetTimeInSeconds() + KeyRepeatDelay;
			KeyData.Target = pTarget;

			if ( pTarget )
			{ return pTarget->OnKeyPress( iKey ); }
		}
	}
	else
	{
		if ( KeyData.KeyState[ iKey ] )
		{
			KeyData.KeyState[ iKey ] = false;

			// BUG BUG. This causes shift left arrow in textboxes
			// to not work. What is disabling it here breaking?
			//KeyData.Target = NULL;

			if ( pTarget )
			{ return pTarget->OnKeyRelease( iKey ); }
		}
	}

	return false;
}