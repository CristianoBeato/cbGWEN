/*
	GWEN
	Copyright (c) 2011 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#include "Gwen/Gwen.h"

class glBuffer;
class glSampler;
class glTexture;

namespace Gwen
{
	namespace Renderer
	{
		inline constexpr int MAX_TEXTURE_COUNT = 512;

		class OpenGL : public Gwen::Renderer::Base
		{
			public:
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
				void Flush( void );

				Gwen::Color			m_Color;
				Gwen::Texture*		m_pFontTexture;
				float				m_fFontScale[2];
				float				m_fLetterSpacing;
				glBuffer*			m_indirectDraw;
				glBuffer*			m_vertexBuffer;
				glBuffer*			m_indexBuffer;
				glBuffer*			m_textureHandleBuffer;
				glSampler*			m_whiteSamp;
				glTexture*			m_white;
				glSampler*			m_fontSamp;
				glTexture*			m_fontText;
				glTexture*			m_textureArray[MAX_TEXTURE_COUNT];			

			public:
				//
				// Self Initialization
				//
				void			CreateBuffers( void );
				void			CreateShaders( void );
				void			CreateDebugFont( void );
				void			DestroyDebugFont( void );
				void			DestoryShaders( void );
				void			DestroyBuffers( void );
				virtual bool	InitializeContext( Gwen::WindowProvider* pWindow );
				virtual bool	ShutdownContext( Gwen::WindowProvider* pWindow );
				virtual bool	PresentContext( Gwen::WindowProvider* pWindow );
				virtual bool	ResizedContext( Gwen::WindowProvider* pWindow, int w, int h );
				virtual bool	BeginContext( Gwen::WindowProvider* pWindow );
				virtual bool	EndContext( Gwen::WindowProvider* pWindow );
		};

	}
}
