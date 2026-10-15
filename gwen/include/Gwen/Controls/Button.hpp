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
	namespace Controls
	{
		class ImagePanel;

		class GWEN_EXPORT Button : public Label
		{
			public:
				AutoPointer<Controls::Button>	Pointer;

				GWEN_CONTROL( Button, Label );

				virtual void Render( Skin::Base::Pointer skin );
				virtual void OnMouseClickLeft( const Point &in_pos, bool bDown );
				virtual void OnMouseClickRight( const Point &in_pos, bool bDown );
				virtual void OnMouseDoubleClickLeft( const Point &in_pos );
				virtual bool OnKeySpace( bool bDown );

				virtual void OnPress( void );
				virtual void OnRightPress( void );

				virtual void AcceleratePressed( void );

				virtual bool IsDepressed() const { return m_bDepressed; }
				virtual void SetDepressed( bool b );

				//
				// Buttons can be toggle type, which means that it is
				// toggled on and off. Its toggle status is in IsDepressed.
				//
				virtual void SetIsToggle( bool b ) { m_bToggle = b; }
				virtual bool IsToggle() const { return m_bToggle; }
				virtual bool GetToggleState() const { return m_bToggleStatus; }
				virtual void SetToggleState( bool b );
				virtual void Toggle() { SetToggleState( !GetToggleState() ); }


				virtual void SetImage( const TextObject & strName, bool bCenter = false );

				virtual void SizeToContents();
				virtual void PostLayout( Skin::Base::Pointer pSkin );
				virtual void UpdateColours();

				virtual void SetImageAlpha( float fMultiply );

				virtual void DoAction() { OnPress(); }
				virtual void SetAction( Event::Handler* pObject, Handler::FunctionWithInformation pFunction, void* data );

			public:

				Gwen::Event::Caller	onPress;
				Gwen::Event::Caller	onRightPress;
				Gwen::Event::Caller	onDown;
				Gwen::Event::Caller	onUp;
				Gwen::Event::Caller	onDoubleClick;
				Gwen::Event::Caller	onToggle;
				Gwen::Event::Caller	onToggleOn;
				Gwen::Event::Caller	onToggleOff;

			protected:
			bool							m_bDepressed;
			bool							m_bToggle;
			bool							m_bToggleStatus;
			bool							m_bCenterImage;
			Controls::ImagePanel::Pointer	m_Image;
		};
	}
}
