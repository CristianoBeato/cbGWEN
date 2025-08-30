/*
	GWEN
	Copyright (c) 2011 Facepunch Studios
	See license in Gwen.h
*/

#ifndef GWEN_RENDERERS_OPENGL_H
#define GWEN_RENDERERS_OPENGL_H

#include "Gwen/Gwen.h"
#include "Gwen/BaseRender.h"

namespace Gwen
{
	namespace Renderer
	{
		class OpenGL : public Gwen::Renderer::Base
		{
			public:
				struct Vertex
				{
					float x, y, z;
					float u, v;
					unsigned char r, g, b, a;
				};

				OpenGL( void );
				~OpenGL( void );
				virtual void Init( void );
				virtual void Begin( void );
				virtual void End( void );
				virtual void SetDrawColor( Gwen::Color color );
				virtual void DrawFilledRect( Gwen::Rect rect );
				virtual void StartClip( void );
				virtual void EndClip( void );
				virtual void RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString & text );
				virtual Gwen::Point MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString & text );
				virtual void DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect pTargetRect, float u1 = 0.0f, float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f );
				virtual void LoadTexture( Gwen::Texture* pTexture );
				virtual void FreeTexture( Gwen::Texture* pTexture );
				virtual Gwen::Color PixelColour( Gwen::Texture* pTexture, unsigned int x, unsigned int y, const Gwen::Color & col_default );

			protected:

				static const int	MaxVerts = 1024;
				void Flush( void );
				void AddVert( int x, int y, float u = 0.0f , float v = 0.0f );

				Gwen::Color			m_Color;
				int					m_iVertNum;
				Vertex				m_Vertices[ MaxVerts ];
				Gwen::Texture*		m_pFontTexture;
				float				m_fFontScale[2];
				float				m_fLetterSpacing;

			public:
				//
				// Self Initialization
				//
				void CreateDebugFont( void );
				void DestroyDebugFont( void );
				virtual bool InitializeContext( Gwen::WindowProvider* pWindow );
				virtual bool ShutdownContext( Gwen::WindowProvider* pWindow );
				virtual bool PresentContext( Gwen::WindowProvider* pWindow );
				virtual bool ResizedContext( Gwen::WindowProvider* pWindow, int w, int h );
				virtual bool BeginContext( Gwen::WindowProvider* pWindow );
				virtual bool EndContext( Gwen::WindowProvider* pWindow );
				void*	m_pContext;
		};

	}
}
#endif
