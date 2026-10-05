/*
============================================================================================
	cbGWEN

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

#include "Gwen/Platform/SDL3Platform.h"
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_clipboard.h>
#include <SDL3/SDL_video.h>
#include "SDL3Platform.h"

Gwen::Platform::SDL3WindowHandle::SDL3WindowHandle( void ) : 
	m_ID( 0 ),
	m_handle( nullptr )
{
}

Gwen::Platform::SDL3WindowHandle::~SDL3WindowHandle( void )
{
	Destroy();
}

bool Gwen::Platform::SDL3WindowHandle::Create( const Gwen::Rect &in_rect, const Gwen::String &in_title)
{
	m_bounds = in_rect;
	m_title = in_title;
	return true;
}

void Gwen::Platform::SDL3WindowHandle::Destroy( void )
{
	if ( m_handle != nullptr )
	{
		SDL_DestroyWindow( m_handle ); 
		m_handle = nullptr;
	}

	m_bounds.x = 0;
	m_bounds.y = 0;
	m_bounds.w = 0;
	m_bounds.h = 0;
	m_ID = 0;
}

void Gwen::Platform::SDL3WindowHandle::SetBounds(const Gwen::Rect &in_rect )
{
	if( !m_handle )
		return;

	m_bounds = in_rect;
	SDL_SetWindowPosition( m_handle, m_bounds.x, m_bounds.y );
	SDL_SetWindowSize( m_handle, m_bounds.w, m_bounds.h );
}

bool Gwen::Platform::SDL3WindowHandle::HasFocus( void ) const
{
	SDL_WindowFlags flags = SDL_GetWindowFlags( m_handle );
	return flags & SDL_WINDOW_INPUT_FOCUS;
}

void Gwen::Platform::SDL3WindowHandle::SetMaximized( const bool bMaximized, Gwen::Rect &out_rect )
{
	int x = 0, y = 0, w = 0, h = 0;
	if( !m_handle )
		return;

	if( bMaximized )
		SDL_MaximizeWindow( m_handle );
	else
		SDL_RestoreWindow( m_handle );

	SDL_GetWindowPosition( m_handle, &x, &y );

#if 0
	SDL_GetWindowSize( m_handle, &w, &h );
#else
	SDL_GetWindowSizeInPixels( m_handle, &w, &h );
#endif

	/// Update bounds 
	m_bounds.x = x;
	m_bounds.y = y;
	m_bounds.w = w;
	m_bounds.h = h;	

	out_rect = m_bounds;
}

void Gwen::Platform::SDL3WindowHandle::SetMinimized(const bool bMinimized) const
{
	if ( !m_handle )
		return;

	if( bMinimized )	
		SDL_MinimizeWindow( m_handle );
	else
		SDL_RestoreWindow( m_handle );
}

bool Gwen::Platform::SDL3WindowHandle::CreateWindowOpenGL(void)
{
#if 0
	auto windowProperties = SDL_CreateProperties();
	SDL_CreateWindowWithProperties( windowProperties );
#else
	m_handle = SDL_CreateWindow( m_title.c_str(), m_bounds.w, m_bounds.h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS );
#endif
	if( !m_handle )
		return false;

	return true;
}

bool Gwen::Platform::SDL3WindowHandle::CreateWindowRenderer(void)
{
	m_handle = SDL_CreateWindow( m_title.c_str(), m_bounds.w, m_bounds.h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS );
	if( !m_handle )
		return false;

    return true ;
}

Gwen::Platform::SDL3::SDL3( void )
{
}

Gwen::Platform::SDL3::~SDL3( void )
{
}

void Gwen::Platform::SDL3::Sleep( const uint32_t in_ms )
{
	// put thread to sleep
	SDL_Delay( in_ms );
}

static SDL_Cursor* cursor = nullptr;
void Gwen::Platform::SDL3::SetCursor( const uint8_t in_cursorID )
{
	SDL_Cursor* old = nullptr;
	SDL_SystemCursor syscur = SDL_SYSTEM_CURSOR_DEFAULT;

	switch ( in_cursorID )
	{
	case CURSOR_NORMAL:
		syscur = SDL_SYSTEM_CURSOR_DEFAULT;
		break;

	case CURSOR_BEAM:
		syscur = SDL_SYSTEM_CURSOR_TEXT;
		break;

	case CURSOR_SIZENS:
		syscur = SDL_SYSTEM_CURSOR_NS_RESIZE;
		break;

	case CURSOR_SIZEWE:
		syscur = SDL_SYSTEM_CURSOR_EW_RESIZE;
		break;

	case CURSOR_SIZENWSE:
		syscur = SDL_SYSTEM_CURSOR_NESW_RESIZE;
		break;

	case CURSOR_SIZENESW:
		syscur = SDL_SYSTEM_CURSOR_NWSE_RESIZE;
		break;

	case CURSOR_SIZEALL:
		syscur = SDL_SYSTEM_CURSOR_MOVE;
		break;

	case CURSOR_NO:
		syscur = SDL_SYSTEM_CURSOR_NOT_ALLOWED;
		break;

	case CURSOR_WAIT:
		syscur = SDL_SYSTEM_CURSOR_WAIT;
		break;

	case CURSOR_FINGER:
		syscur = SDL_SYSTEM_CURSOR_POINTER;
		break;

	default:
		syscur = SDL_SYSTEM_CURSOR_DEFAULT;
		break;
	}

	// store current cursor
	old = cursor;

	// create a new pointer
	cursor = SDL_CreateSystemCursor( syscur );

	// set the cursor
	SDL_SetCursor( cursor );

	// release the previous cursor pointer
	if ( old != nullptr )
		SDL_DestroyCursor( old );
}

//TODO: 
void Gwen::Platform::SDL3::GetDesktopSize( int & w, int & h )
{

}

Gwen::UnicodeString Gwen::Platform::SDL3::GetClipboardText( void )
{
	Gwen::TextObject inString;
	if ( !SDL_HasClipboardText() )
		return Gwen::UnicodeString();

	// aquire the clipboard
	inString = SDL_GetClipboardText();
	
	return inString.GetUnicode();
}

bool Gwen::Platform::SDL3::SetClipboardText( const UnicodeString & str )
{
	Gwen::TextObject outString = str;
	
	// clear the clipboard before we set a new content 
	SDL_ClearClipboardData();

	return SDL_SetClipboardText( outString.c_str() );
}

float Gwen::Platform::SDL3::GetTimeInSeconds( void )
{
	uint64_t time = SDL_GetTicks();
	return time / 1000;
}

bool Gwen::Platform::SDL3::FileOpen( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
{
	return false; //TODO: SDL3 now suport file open Dialog
}

bool Gwen::Platform::SDL3::FileSave( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
{
	return false; //TODO: SDL3 now suport file open Dialog
}

bool Gwen::Platform::SDL3::FolderOpen( const String & Name, const String & StartPath, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
{
	return false; //TODO: SDL3 now suport file open Dialog
}
