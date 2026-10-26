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
		class GWEN_EXPORT ImagePanel : public Controls::Base
		{
			public:
				typedef AutoPointer<Controls::ImagePanel> Pointer;

				GWEN_CONTROL_INLINE( ImagePanel, Controls::Base )
				{
					SetUV( 0, 0, 1, 1 );
					SetMouseInputEnabled( false );
					m_DrawColor = Colors::White;
					SetStretch( true );
				}

				virtual ~ImagePanel( void )
				{
					m_Texture.Release( GetSkin()->GetRender() );
				}

				virtual void SetUV( float u1, float v1, float u2, float v2 )
				{
					m_uv[0] = u1;
					m_uv[1] = v1;
					m_uv[2] = u2;
					m_uv[3] = v2;
				}

				virtual void SetImage( const TextObject & imageName )
				{
					m_Texture.Load( imageName, GetSkin()->GetRender() );
				}

				virtual TextObject & GetImage( void )
				{
					return m_Texture.name;
				}

				virtual int TextureWidth( void )
				{
					return m_Texture.width;
				}

				virtual int TextureHeight( void )
				{
					return m_Texture.height;
				}

				virtual const TextObject & GetImageName( void )
				{
					return m_Texture.name;
				}

				virtual void Render( Skin::Base::Pointer skin )
				{
					skin->GetRender()->SetDrawColor( m_DrawColor );

					if ( m_bStretch )
					{ skin->GetRender()->DrawTexturedRect( &m_Texture, GetRenderBounds(), m_uv[0], m_uv[1], m_uv[2], m_uv[3] ); }
					else
					{ skin->GetRender()->DrawTexturedRect( &m_Texture, Gwen::Rect( 0, 0, m_Texture.width, m_Texture.height ), m_uv[0], m_uv[1], m_uv[2], m_uv[3] ); }
				}

				virtual void SizeToContents( void )
				{
					SetSize( m_Texture.width, m_Texture.height );
				}

				virtual void SetDrawColor( Gwen::Color color )
				{
					m_DrawColor = color;
				}

				virtual bool FailedToLoad( void )
				{
					return m_Texture.FailedToLoad();
				}

				virtual bool GetStretch( void ) { return m_bStretch; }
				virtual void SetStretch( bool b ) { m_bStretch = b; }

			protected:
				float			m_uv[4];
				bool			m_bStretch;
				Texture			m_Texture;
				Gwen::Color		m_DrawColor;
		};
	}
}
