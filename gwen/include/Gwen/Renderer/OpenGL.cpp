
#include "Gwen/Renderer/OpenGL.hpp"
#include "Gwen/WindowProvider.h"

#include <SDL3/SDL_surface.h>
#include <GL/glcorearb.h>

static PFNGLGETBOOLEANVPROC						glGetBooleanv = nullptr;
static PFNGLGETINTEGERVPROC						glGetIntegerv = nullptr;
static PFNGLGETFLOATVPROC						glGetFloatv = nullptr;

static PFNGLENABLEPROC							glEnable = nullptr;
static PFNGLDISABLEPROC							glDisable = nullptr;

static PFNGLFLUSHPROC							glFlush = nullptr;
static PFNGLFINISHPROC							glFinish = nullptr;

static PFNGLSCISSORPROC							glScissor = nullptr;

static PFNGLBLENDFUNCPROC 						glBlendFunc = nullptr;
static PFNGLCLEARCOLORPROC						glClearColor = nullptr;
static PFNGLCLEARPROC							glClear = nullptr;

static PFNGLDRAWARRAYSPROC						glDrawArrays = nullptr;
static PFNGLDRAWELEMENTSINDIRECTPROC			glDrawElementsIndirect = nullptr;

// Buffer Objects
static PFNGLCREATEBUFFERSPROC					glCreateBuffers = nullptr;
static PFNGLDELETEBUFFERSPROC					glDeleteBuffers = nullptr;
static PFNGLNAMEDBUFFERSTORAGEPROC				glNamedBufferStorage = nullptr;
static PFNGLMAPNAMEDBUFFERRANGEPROC				glMapNamedBufferRange = nullptr;
static PFNGLUNMAPNAMEDBUFFERPROC				glUnmapNamedBuffer = nullptr;

// Sampler object
static PFNGLCREATESAMPLERSPROC					glCreateSamplers = nullptr;
static PFNGLDELETESAMPLERSPROC					glDeleteSamplers = nullptr;
static PFNGLSAMPLERPARAMETERIPROC				glSamplerParameteri = nullptr;

// texture Object
static PFNGLCREATETEXTURESPROC					glCreateTextures = nullptr;
static PFNGLDELETETEXTURESPROC					glDeleteTextures = nullptr;
static PFNGLTEXTURESTORAGE2DPROC				glTextureStorage2D = nullptr;
static PFNGLTEXTURESUBIMAGE2DPROC				glTextureSubImage2D = nullptr;
static PFNGLGETTEXTUREIMAGEPROC					glGetTextureImage = nullptr;
static PFNGLGETTEXTURESUBIMAGEPROC				glGetTextureSubImage = nullptr;

// Bindless handle
static PFNGLGETTEXTURESAMPLERHANDLEARBPROC		glGetTextureSamplerHandleARB = nullptr;
static PFNGLMAKETEXTUREHANDLERESIDENTARBPROC	glMakeTextureHandleResidentARB = nullptr;
static PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC	glMakeTextureHandleNonResidentARB = nullptr;

static const GLuint INVALID_TEXTURE_ID = 0XFFFFFFFF;

class glBuffer
{
private:
	GLuint			m_handle;
	GLsizeiptr		m_size;
	GLenum			m_taget;
	void*			m_data;

public:
	
	/// @brief Create a buffer object 
	glBuffer( const GLenum in_target, const GLsizeiptr in_size ) : m_handle( 0 ), m_size( 0 )
	{
		m_taget = m_taget;
		m_size = in_size;

		// create buffer handle
		glCreateBuffers( 1, &m_handle );
		
		// allocate memory for the buffer object 
		glNamedBufferStorage( m_handle, m_size, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT );

		// retrieve data pointer
		m_data = glMapNamedBufferRange( m_handle, 0, m_size, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT ); 
	}
	
	/// @brief Destroy buffer object 
	/// @param  
	~glBuffer( void )
	{
		if( m_handle != 0 )
		{
			glUnmapNamedBuffer( m_handle ); // Release buffer map
			glDeleteBuffers( 1, &m_handle );
			m_handle = 0;
		}
	}

	inline GLuint	Handle( void ) const { return m_handle; }
	inline void*	Data( void ) const { return m_data; } 	
};

class glSampler
{
private:
	GLuint m_handle;

public:
	glSampler( const GLenum in_repeating, const GLenum in_filter ) : m_handle( 0 )
	{
		glCreateSamplers(1, &m_handle );
		glSamplerParameteri( m_handle, GL_TEXTURE_WRAP_S, in_repeating );
		glSamplerParameteri( m_handle, GL_TEXTURE_WRAP_T, in_repeating );
		glSamplerParameteri( m_handle, GL_TEXTURE_MIN_FILTER, in_filter );
		glSamplerParameteri( m_handle, GL_TEXTURE_MAG_FILTER, in_filter );
	}

	~glSampler( void )
	{
		if( m_handle != 0 )
		{
			glDeleteSamplers( 1, &m_handle );
			m_handle = 0;
		}
	}

	inline GLuint Handle( void ) const { return m_handle; }
};

class glTexture
{
private:
	GLuint	m_id;
	GLuint	m_texture;
	GLuint	m_handle;
	GLsizei	m_width;
	GLsizei	m_height;

public:
	glTexture( const GLuint in_id, const GLsizei in_width, const GLsizei in_height, const GLubyte* in_imgSRC, const glSampler* in_sanpler )
	{
		m_id = in_id;
		m_width = in_width;
		m_height = in_height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_texture );
		
		// Allocate the requered image memory
		glTextureStorage2D( m_texture, 1, GL_RGBA8, m_width, m_height); 

		/// Upload texture pixel data
		glTextureSubImage2D( m_texture, 0, 0, 0, m_width, m_width, GL_RGBA, GL_UNSIGNED_BYTE, in_imgSRC );
		
		m_handle = glGetTextureSamplerHandleARB( m_texture, in_sanpler->Handle() );

		glMakeTextureHandleResidentARB( m_handle );
	}

	~glTexture( void )
	{
		if( m_handle != 0 )
		{
			glMakeTextureHandleNonResidentARB( m_handle );
			m_handle = 0;	
		}

		if( m_texture != 0 )
		{
			glDeleteTextures( 1, &m_texture );
			m_texture = 0;
		}
	}

	void	GetTextureImage( const GLsizei in_bufSize, void* out_pixels)
	{
		glGetTextureImage( m_texture, 0, GL_RGBA, GL_UNSIGNED_BYTE, in_bufSize, out_pixels );
	}

	GLuint 		ID( void ) const { return m_id; }
	GLuint		Texture( void ) const { return m_texture; }
	GLuint64	Handle( void ) const { return m_handle; }
};


Gwen::Renderer::OpenGL::OpenGL( void )
{
	m_fLetterSpacing = 1.0f / 16.0f;
	m_fFontScale[0] = 1.5f;
	m_fFontScale[1] = 1.5f;
	m_pFontTexture = nullptr;

}

Gwen::Renderer::OpenGL::~OpenGL( void )
{
}

void Gwen::Renderer::OpenGL::Init( void )
{
}

void Gwen::Renderer::OpenGL::Begin( void )
{
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	// glAlphaFunc( GL_GREATER, 1.0f );
	glEnable( GL_BLEND );
}

void Gwen::Renderer::OpenGL::End( void )
{
	Flush();
}

void Gwen::Renderer::OpenGL::Flush()
{
	glFlush();
}

void Gwen::Renderer::OpenGL::DrawFilledRect( Gwen::Rect rect )
{
	Translate( rect );

}

void Gwen::Renderer::OpenGL::SetDrawColor( Gwen::Color color )
{
	m_Color = color;
}

void Gwen::Renderer::OpenGL::StartClip( void )
{
	Flush();
	Gwen::Rect rect = ClipRegion();
	// OpenGL's coords are from the bottom left
	// so we need to translate them here.
	{
		GLint view[4];
		glGetIntegerv( GL_VIEWPORT, &view[0] );
		rect.y = view[3] - ( rect.y + rect.h );
	}

	glScissor( rect.x * Scale(), rect.y * Scale(), rect.w * Scale(), rect.h * Scale() );
	glEnable( GL_SCISSOR_TEST );
};

void Gwen::Renderer::OpenGL::EndClip( void )
{
	Flush();
	glDisable( GL_SCISSOR_TEST );
};

void Gwen::Renderer::OpenGL::DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect rect, float u1, float v1, float u2, float v2 )
{
	GLuint* tex = ( GLuint* ) pTexture->data;

	// Missing image, not loaded properly?
	if ( !tex )
		return DrawMissingImage( rect );

	Translate( rect );
}

void Gwen::Renderer::OpenGL::RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString & text )
{
	float fSize = pFont->size * Scale();

	if ( !text.length() )
		return;

	Gwen::String converted_string = Gwen::TextObject::UnicodeToString( text );
	float yOffset = 0.0f;

	for ( int i = 0; i < text.length(); i++ )
	{
		char ch = converted_string[i];
		float curSpacing = sGwenDebugFontSpacing[ch] * m_fLetterSpacing * fSize * m_fFontScale[0];
		Gwen::Rect r( pos.x + yOffset, pos.y - fSize * 0.5, ( fSize * m_fFontScale[0] ), fSize * m_fFontScale[1] );

		if ( m_pFontTexture )
		{
			float uv_texcoords[8] = {0., 0., 1., 1.};

			if ( ch >= 0 )
			{
				float cx = ( ch % 16 ) / 16.0;
				float cy = ( ch / 16 ) / 16.0;
				uv_texcoords[0] = cx;
				uv_texcoords[1] = cy;
				uv_texcoords[4] = float( cx + 1.0f / 16.0f );
				uv_texcoords[5] = float( cy + 1.0f / 16.0f );
			}

			DrawTexturedRect( m_pFontTexture, r, uv_texcoords[0], uv_texcoords[5], uv_texcoords[4], uv_texcoords[1] );
			yOffset += curSpacing;
		}
		else
		{
			DrawFilledRect( r );
			yOffset += curSpacing;
		}
	}
}

Gwen::Point Gwen::Renderer::OpenGL::MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString & text )
{
	Gwen::Point p;
	float fSize = pFont->size * Scale();
	Gwen::String converted_string = Gwen::TextObject::UnicodeToString( text );
	float spacing = 0.0f;

	for ( int i = 0; i < text.length(); i++ )
	{
		char ch = converted_string[i];
		spacing += sGwenDebugFontSpacing[ch];
	}

	p.x = spacing * m_fLetterSpacing * fSize * m_fFontScale[0];
	p.y = pFont->size * Scale();
	return p;
}

void Gwen::Renderer::OpenGL::LoadTexture( Gwen::Texture* pTexture )
{
	GLuint id = INVALID_TEXTURE_ID;
	SDL_Surface* surface = nullptr;
	if( !pTexture )
		return;

	surface = SDL_LoadBMP( pTexture->name.c_str() );
	if( !surface )
		return;

	/// Get first
	for ( GLuint i = 0; i < MAX_TEXTURE_COUNT; i++)
	{	
		if( m_textureArray[i] == nullptr )
		{
			id = i;
			break;
		}
	}

	/// check for free texture slot 
	if( id == INVALID_TEXTURE_ID )
	{
		SDL_DestroySurface( surface );
		return;	
	}

	// Create texture object
	m_textureArray[id] = new glTexture( id, surface->w, surface->h, static_cast<GLubyte*>( surface->pixels ), m_fontSamp );

	/// Release source surface
	SDL_DestroySurface( surface );

	GLuint64* handleArray = static_cast<GLuint64*>( m_textureHandleBuffer->Data() );
	handleArray[id] = m_textureArray[id]->Handle();

	pTexture->data = reinterpret_cast<void*>( m_textureArray[id] );
}

void Gwen::Renderer::OpenGL::FreeTexture( Gwen::Texture* pTexture )
{
	glTexture* tex = static_cast<glTexture*>( pTexture->data );
	if ( !tex ) 
		return; 

	GLuint id = tex->ID();
	if( id < INVALID_TEXTURE_ID )
		return;
		
	m_textureArray[id] = 0;
	delete tex;
	pTexture->data = nullptr;
}

Gwen::Color Gwen::Renderer::OpenGL::PixelColour( Gwen::Texture* pTexture, unsigned int x, unsigned int y, const Gwen::Color & col_default )
{
	glTexture* tex = static_cast<glTexture*>( pTexture->data );

	if ( !tex )
		return col_default;

#if 1
	size_t buffSize = pTexture->width * pTexture->height * sizeof( unsigned char ) * 4 ;

	unsigned char* data = ( unsigned char* ) malloc( buffSize );

	tex->GetTextureImage( buffSize, data );


	unsigned int iOffset = ( y * pTexture->width + x ) * 4;
	Gwen::Color c;
	c.r = data[0 + iOffset];
	c.g = data[1 + iOffset];
	c.b = data[2 + iOffset];
	c.a = data[3 + iOffset];
#else


#endif
	//
	// Retrieving the entire texture for a single pixel read
	// is kind of a waste - maybe cache this pointer in the texture
	// data and then release later on? It's never called during runtime
	// - only during initialization.
	//
	free( data );
	return c;
}

void Gwen::Renderer::OpenGL::CreateBuffers(void)
{
}

bool Gwen::Renderer::OpenGL::InitializeContext(Gwen::WindowProvider *pWindow)
{
	CreateDebugFont();
	return true;
}

bool Gwen::Renderer::OpenGL::ShutdownContext( Gwen::WindowProvider* pWindow )
{
	DestroyDebugFont();
	return true;
}

bool Gwen::Renderer::OpenGL::PresentContext( Gwen::WindowProvider* pWindow )
{
	return true;
}

bool Gwen::Renderer::OpenGL::ResizedContext( Gwen::WindowProvider* pWindow, int w, int h )
{
	return true;
}

bool Gwen::Renderer::OpenGL::BeginContext( Gwen::WindowProvider* pWindow )
{
	/// Clear buffers
	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	return true;
}

bool Gwen::Renderer::OpenGL::EndContext( Gwen::WindowProvider* pWindow )
{
	glFinish(); // wait to be draw
	return true;
}