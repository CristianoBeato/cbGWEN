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

namespace Gwen
{
	namespace ControlsInternal
	{
		class GWEN_EXPORT Dragger : public Controls::Base
		{
			public:

				GWEN_CONTROL( Dragger, Controls::Base );

				virtual void OnMouseMoved( const Gwen::Point &in_mousePos, const Gwen::Point &in_mouseDelta );

				virtual void OnMouseClickLeft( const Gwen::Point &in_mousePos, bool bDown );
				virtual void Render( Skin::Base::Pointer skin );

				virtual void SetTarget( Controls::Base::Pointer pBase ) { m_pTarget = pBase; }
				virtual bool IsDepressed( void ) { return m_bDepressed; }

				virtual void SetDoMove( bool b ) { m_bDoMove = b; }

				virtual void OnMouseDoubleClickLeft( const Gwen::Point &in_mousePos );

				Gwen::Event::Caller	onDragged;
				Gwen::Event::Caller	onDragStart;

				Gwen::Event::Caller	onDoubleClickLeft;

			protected:

				bool						m_bDepressed;
				Gwen::Point					m_HoldPos;
				Controls::Base::Pointer		m_pTarget;
				bool						m_bDoMove;
		};
	}
}
