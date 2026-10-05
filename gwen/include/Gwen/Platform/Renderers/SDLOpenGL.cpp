/*
============================================================================================
	cbGWEN

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

#include "Gwen/Platform/Renderers/SDLOpenGL.hpp"
#include "Gwen/WindowProvider.h"
#include "Gwen/Platform/SDL3Platform.h"


bool Gwen::Renderer::SDLOpenGL::InitializeContext(Gwen::WindowProvider *pWindow)
{
	Platform::SDL3WindowHandle* window = static_cast<Platform::SDL3WindowHandle*>( pWindow->GetWindow() );
	if( !window )
		return false; /// no window created

	// Create a openGL render capable window 
	if( !window->CreateWindowOpenGL() )
		return false;

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 5 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE );

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// window color depth 
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

	m_rc = SDL_GL_CreateContext( window->GetHandle() );
	if( !m_rc )
		return false;

    return OpenGL::InitializeContext( pWindow );
}

bool Gwen::Renderer::SDLOpenGL::ShutdownContext( Gwen::WindowProvider* pWindow )
{
	if( !pWindow || !pWindow->GetHandle() )
		return false;

	// Release OpenGL Objects
	OpenGL::ShutdownContext( pWindow );

	if( m_rc )
	{
		SDL_GL_DestroyContext( m_rc );
		m_rc = nullptr;
	}
	else 
	{
		return false;
	}

	return true;
}

bool Gwen::Renderer::SDLOpenGL::PresentContext( Gwen::WindowProvider *pWindow )
{
	/// Retrieve window handler 
	Platform::SDL3WindowHandle* window = static_cast<Platform::SDL3WindowHandle*>( pWindow->GetWindow() );
	if( !window || !window->GetHandle() )
		return false; /// no window created

	// Swap window buffers
	SDL_GL_SwapWindow( window->GetHandle() );
    return OpenGL::PresentContext( pWindow );
}
