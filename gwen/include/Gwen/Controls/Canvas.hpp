/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_CANVAS_H
#define GWEN_CONTROLS_CANVAS_H

#include <set>
#include "Gwen/Controls/Base.h"
#include "Gwen/InputHandler.h"

namespace Gwen
{
	namespace Controls
	{
		class GWEN_EXPORT Canvas : public Base
		{
			public:
				typedef AutoPointer<Controls::Canvas>	Pointer;
				typedef Controls::Base BaseClass;

				Canvas( Skin::Base::Pointer pSkin );
				virtual ~Canvas();

				//
				// For additional initialization
				// (which is sometimes not appropriate in the constructor)
				//
				virtual void Initialize( void ) {};

				//
				// You should call this to render your canvas.
				//
				virtual void RenderCanvas( void );

				//
				// Call this whenever you want to process input. This
				// is usually once a frame..
				//
				virtual void DoThink( void );

				//
				// In most situations you will be rendering the canvas
				// every frame. But in some situations you will only want
				// to render when there have been changes. You can do this
				// by checking NeedsRedraw().
				//
				virtual bool NeedsRedraw( void ) { return m_bNeedsRedraw; }
				virtual void Redraw( void ) { m_bNeedsRedraw = true; }

				// Internal. Do not call directly.
				virtual void Render( Skin::Base::Pointer pRender );

				// Childpanels call parent->GetCanvas() until they get to
				// this top level function.
				virtual Controls::Canvas::Pointer GetCanvas( void ) { return AutoPointer<Controls::Canvas>( this ); }

				virtual void SetScale( float f );
				virtual float Scale( void ) const { return m_fScale; }

				virtual void OnBoundsChanged( Gwen::Rect oldBounds );

				// Delete all children (this is done called in the destructor too)
				virtual void ReleaseChildren();

				// Delayed deletes
				virtual void AddDelayedDelete( Controls::Base::Pointer pControl );
				virtual void ProcessDelayedDeletes();

				Controls::Base::Pointer	FirstTab;
				Controls::Base::Pointer	NextTab;

				// Input
				virtual bool InputMouseMoved( int x, int y, int deltaX, int deltaY );
				virtual bool InputMouseButton( int iButton, bool bDown );
				virtual bool InputKey( int iKey, bool bDown );
				virtual bool InputCharacter( Gwen::UnicodeChar chr );
				virtual bool InputMouseWheel( int val );
				virtual bool InputQuit() { return true; };

				// Background
				virtual void SetBackgroundColor( const Gwen::Color & color ) { m_BackgroundColor = color; }
				virtual void SetDrawBackground( bool bShouldDraw ) { m_bDrawBackground = bShouldDraw; }

			protected:
				bool								m_bNeedsRedraw;
				bool								m_bDrawBackground;
				bool								m_bAnyDelete;
				float								m_fScale;
				Controls::Base::List				m_DeleteList;
				std::set< Controls::Base::Pointer>	m_DeleteSet;
				Gwen::Color							m_BackgroundColor;

				friend class Controls::Base;
				void PreDeleteCanvas( Controls::Base::Pointer );
		};
	}
}
#endif
