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

#pragma once

#include "Gwen/WindowProvider.h"
#include "Gwen/Platform/Platform.hpp"

namespace Gwen
{
	namespace ControlsInternal
	{
		class Dragger;
	};

	namespace Controls
	{
		class GWEN_EXPORT WindowCloseButton : public Button
		{
				GWEN_CONTROL_INLINE( WindowCloseButton, Button )
				{
					m_pWindow = NULL;
					SetSize( 31, 31 );
					SetText( "" );
				}

				virtual void Render( Skin::Base* skin )
				{
					if ( !m_pWindow ) { return; }

					skin->DrawWindowCloseButton( this, IsDepressed() && IsHovered(), IsHovered() && ShouldDrawHover(), IsDisabled() );
				}

				void SetWindow( Gwen::Controls::Base* p )
				{
					m_pWindow = p;
				}

			protected:

				Controls::Base* m_pWindow;
		};

		class GWEN_EXPORT WindowMaximizeButton : public WindowCloseButton
		{
				GWEN_CONTROL_INLINE( WindowMaximizeButton, WindowCloseButton ) { m_bMaximized = false; };

				virtual void Render( Skin::Base* skin )
				{
					if ( !m_pWindow ) { return; }

					skin->DrawWindowMaximizeButton( this, IsDepressed() && IsHovered(), IsHovered() && ShouldDrawHover(), IsDisabled(), m_bMaximized );
				}

				virtual void SetMaximized( bool b )
				{
					m_bMaximized = b;
				}

			protected:

				bool m_bMaximized;
		};

		class GWEN_EXPORT WindowMinimizeButton : public WindowCloseButton
		{
				GWEN_CONTROL_INLINE( WindowMinimizeButton, WindowCloseButton ) {};

				virtual void Render( Skin::Base* skin )
				{
					if ( !m_pWindow ) { return; }

					skin->DrawWindowMinimizeButton( this, IsDepressed() && IsHovered(), IsHovered() && ShouldDrawHover(), IsDisabled() );
				}

		};

		class GWEN_EXPORT WindowCanvas : public Canvas, public Gwen::WindowProvider
		{
			public:

				GWEN_CLASS( WindowCanvas, Controls::Canvas );

				WindowCanvas( AutoPointer<Platform::Base> &pPlatform, AutoPointer<Skin::Base> &pSkin, int x, int y, int w, int h, const Gwen::String & strWindowTitle = "" );
				~WindowCanvas( void );

				virtual void DoThink( void );

				virtual bool WantsQuit() { return m_bQuit; }

				// Gwen::WindowProvider
				virtual AutoPointer<Platform::WindowHandle> GetWindow( void );

				virtual bool InputQuit();

				Skin::Base::Pointer GetSkin( void );

				virtual void Render( Skin::Base::Pointer skin );

				virtual void SetPos( int x, int y );
				virtual bool IsOnTop();

				virtual void Layout( Skin::Base* skin );

				virtual bool CanMaximize() { return m_bCanMaximize; }
				virtual void SetCanMaximize( bool b );
				virtual void SetMaximize( bool b );

				virtual void SetSizable( bool b ) { m_Sizer->SetHidden( !b ); }
				virtual bool GetSizable() { return m_Sizer->Visible(); }

			protected:
				bool										m_bQuit;
				bool										m_bCanMaximize;
				bool										m_bIsMaximized;
				Gwen::Point									m_WindowPos;
				Gwen::Point									m_HoldPos;
				Platform::WindowHandle::Pointer				m_pOSWindow;
				AutoPointer<Platform::Base>					m_pOSPlatform;
				Gwen::Skin::Base::Pointer					m_pSkinChange;
				ControlsInternal::Dragger::Pointer			m_TitleBar;
				ControlsInternal::Dragger::Pointer			m_Sizer;
				Controls::Label::Pointer					m_Title;
				AutoPointer<Controls::WindowCloseButton>	m_pClose;
				AutoPointer<Controls::WindowMaximizeButton>	m_pMaximize;
				AutoPointer<Controls::WindowMinimizeButton>	m_pMinimize;

				virtual void RenderCanvas( void );
				virtual void DestroyWindow( void );

				virtual void CloseButtonPressed( void );
				virtual void MaximizeButtonPressed( void );
				virtual void MinimizeButtonPressed( void );

				virtual void Dragger_Start( void );
				virtual void Dragger_Moved( void );
				virtual void Sizer_Moved( void );
				virtual void OnTitleDoubleClicked( void );
		};
	}
}
