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

#include "DragAndDrop.h"
#include "Platform/Platform.hpp"

Gwen::AutoPointer<Gwen::DragAndDrop::Package>	Gwen::DragAndDrop::CurrentPackage = Gwen::AutoPointer<Gwen::DragAndDrop::Package>();
Gwen::AutoPointer<Gwen::Controls::Base>			Gwen::DragAndDrop::HoveredControl = Gwen::AutoPointer<Gwen::Controls::Base>();
Gwen::AutoPointer<Gwen::Controls::Base>			Gwen::DragAndDrop::SourceControl = Gwen::AutoPointer<Gwen::Controls::Base>();

static Gwen::AutoPointer<Gwen::Controls::Base> LastPressedControl = Gwen::AutoPointer<Gwen::Controls::Base>();
static Gwen::AutoPointer<Gwen::Controls::Base> NewHoveredControl = Gwen::AutoPointer<Gwen::Controls::Base>();
static Gwen::Point LastPressedPos;
static Gwen::Point m_iMouse = { 0, 0 };

void Gwen::DragAndDrop::ControlDeleted( AutoPointer<Controls::Base> pControl )
{
	if ( SourceControl == pControl )
	{
		SourceControl = nullptr;
		CurrentPackage = nullptr;
		HoveredControl = nullptr;
		LastPressedControl = nullptr;
	}

	if ( LastPressedControl == pControl )
		LastPressedControl = nullptr; 

	if ( HoveredControl == pControl )
		HoveredControl = nullptr;

	if ( NewHoveredControl == pControl )
		NewHoveredControl = nullptr;
}

bool Gwen::DragAndDrop::Start( AutoPointer<Controls::Base> pControl, AutoPointer<Package> pPackage )
{
	if ( CurrentPackage )
		return false;

	CurrentPackage = pPackage;
	SourceControl = pControl;
	return true;
}

static bool OnDrop( const Gwen::Point &in_pos )
{
	bool bSuccess = false;

	if ( Gwen::DragAndDrop::HoveredControl )
	{
		Gwen::DragAndDrop::HoveredControl->DragAndDrop_HoverLeave( Gwen::DragAndDrop::CurrentPackage );
		bSuccess = Gwen::DragAndDrop::HoveredControl->DragAndDrop_HandleDrop( Gwen::DragAndDrop::CurrentPackage, in_pos );
	}

	// Report back to the source control, to tell it if we've been successful.
	Gwen::DragAndDrop::SourceControl->DragAndDrop_EndDragging( bSuccess, in_pos );
	Gwen::DragAndDrop::SourceControl->Redraw();
	Gwen::DragAndDrop::CurrentPackage = nullptr;
	Gwen::DragAndDrop::SourceControl = nullptr;
	return true;
}

bool Gwen::DragAndDrop::OnMouseButton( AutoPointer<Controls::Base> pHoveredControl, const Point &in_pos, bool bDown )
{
	if ( !bDown )
	{
		LastPressedControl = NULL;

		// Not carrying anything, allow normal actions
		if ( !CurrentPackage )
		{ return false; }

		// We were carrying something, drop it.
		OnDrop( in_pos );
		return true;
	}

	if ( !pHoveredControl ) { return false; }

	if ( !pHoveredControl->DragAndDrop_Draggable() ) { return false; }

	// Store the last clicked on control. Don't do anything yet,
	// we'll check it in OnMouseMoved, and if it moves further than
	// x pixels with the mouse down, we'll start to drag.
	LastPressedPos = in_pos;
	LastPressedControl = pHoveredControl;
	return false;
}

static bool ShouldStartDraggingControl( const Gwen::Point &in_pos )
{
	// We're not holding a control down..
	if ( !LastPressedControl ) { return false; }

	// Not been dragged far enough
	int iLength = std::abs( in_pos.x - LastPressedPos.x ) + std::abs( in_pos.y - LastPressedPos.y );

	if ( iLength < 5 ) { return false; }

	// Create the dragging package
	Gwen::DragAndDrop::CurrentPackage = LastPressedControl->DragAndDrop_GetPackage( LastPressedPos.x, LastPressedPos.y );

	// We didn't create a package!
	if ( !Gwen::DragAndDrop::CurrentPackage )
	{
		LastPressedControl = NULL;
		Gwen::DragAndDrop::SourceControl = NULL;
		return false;
	}

	// Now we're dragging something!
	Gwen::DragAndDrop::SourceControl = LastPressedControl;
	Gwen::MouseFocus = NULL;
	LastPressedControl = NULL;
	Gwen::DragAndDrop::CurrentPackage->drawcontrol = NULL;

	// Some controls will want to decide whether they should be dragged at that moment.
	// This function is for them (it defaults to true)
	if ( !Gwen::DragAndDrop::SourceControl->DragAndDrop_ShouldStartDrag() )
	{
		Gwen::DragAndDrop::SourceControl = NULL;
		Gwen::DragAndDrop::CurrentPackage = NULL;
		return false;
	}

	Gwen::DragAndDrop::SourceControl->DragAndDrop_StartDragging( Gwen::DragAndDrop::CurrentPackage, LastPressedPos );
	return true;
}

static void UpdateHoveredControl( Gwen::AutoPointer<Gwen::Controls::Base> pCtrl, const Gwen::Point &in_pos )
{
	//
	// We use this global variable to represent our hovered control
	// That way, if the new hovered control gets deleted in one of the
	// Hover callbacks, we won't be left with a hanging pointer.
	// This isn't ideal - but it's minimal.
	//
	NewHoveredControl = pCtrl;

	// Nothing to change..
	if ( Gwen::DragAndDrop::HoveredControl == NewHoveredControl ) 
		return;

	auto platform = NewHoveredControl->GetPlatfom();

	// We changed - tell the old hovered control that it's no longer hovered.
	if ( Gwen::DragAndDrop::HoveredControl && Gwen::DragAndDrop::HoveredControl != NewHoveredControl )
		Gwen::DragAndDrop::HoveredControl->DragAndDrop_HoverLeave( Gwen::DragAndDrop::CurrentPackage ); 

	// If we're hovering where the control came from, just forget it.
	// By changing it to NULL here we're not going to show any error cursors
	// it will just do nothing if you drop it.
	if ( NewHoveredControl == Gwen::DragAndDrop::SourceControl )
		NewHoveredControl = nullptr;

	// Check to see if the new potential control can accept this type of package.
	// If not, ignore it and show an error cursor.
	while ( NewHoveredControl && !NewHoveredControl->DragAndDrop_CanAcceptPackage( Gwen::DragAndDrop::CurrentPackage ) )
	{
		// We can't drop on this control, so lets try to drop
		// onto its parent..
		NewHoveredControl = NewHoveredControl->GetParent();

		// Its parents are dead. We can't drop it here.
		// Show the NO WAY cursor.
		if ( !NewHoveredControl )
			platform->SetCursor( Gwen::CursorType::CURSOR_NO );
	}

	// Become out new hovered control
	Gwen::DragAndDrop::HoveredControl = NewHoveredControl;

	// If we exist, tell us that we've started hovering.
	if ( Gwen::DragAndDrop::HoveredControl )
	{
		Gwen::DragAndDrop::HoveredControl->DragAndDrop_HoverEnter( Gwen::DragAndDrop::CurrentPackage, in_pos );
	}

	NewHoveredControl = NULL;
}

void Gwen::DragAndDrop::OnMouseMoved( Gwen::AutoPointer<Gwen::Controls::Base> pHoveredControl, const Point &in_pos )
{
	auto platform = pHoveredControl->GetPlatfom();

	// Always keep these up to date, they're used to draw the dragged control.
	m_iMouse = in_pos;

	// If we're not carrying anything, then check to see if we should
	// pick up from a control that we're holding down. If not, then forget it.
	if ( !CurrentPackage && !ShouldStartDraggingControl( in_pos ) )
	{ return; }

	// Make sure the canvas redraws when we move
	if ( CurrentPackage && CurrentPackage->drawcontrol )
	{ CurrentPackage->drawcontrol->Redraw(); }

	// Swap to this new hovered control and notify them of the change.
	UpdateHoveredControl( pHoveredControl, in_pos );

	if ( !HoveredControl ) { return; }

	// Update the hovered control every mouse move, so it can show where
	// the dropped control will land etc..
	HoveredControl->DragAndDrop_Hover( CurrentPackage, in_pos );
	// Override the cursor - since it might have been set my underlying controls
	// Ideally this would show the 'being dragged' control. TODO
	platform->SetCursor( Gwen::CursorType::CURSOR_NORMAL );
	pHoveredControl->Redraw();
}

void Gwen::DragAndDrop::RenderOverlay( AutoPointer<Controls::Canvas> /*pCanvas*/, AutoPointer<Skin::Base> skin )
{
	if ( !CurrentPackage ) 
		 return; 

	if ( !CurrentPackage->drawcontrol ) { return; }

	Gwen::Point pntOld = skin->GetRender()->GetRenderOffset();
	skin->GetRender()->AddRenderOffset( Gwen::Rect( m_iMouse.x - SourceControl->X() - CurrentPackage->holdoffset.x, m_iMouse.y - SourceControl->Y() - CurrentPackage->holdoffset.y, 0, 0 ) );
	CurrentPackage->drawcontrol->DoRender( skin );
	skin->GetRender()->SetRenderOffset( pntOld );
}