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

#include "Precompiled.hpp"
#include "Gwen/Platform/SDL3Platform.h"

#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_clipboard.h>
#include <SDL3/SDL_video.h>
#include "SDL3Platform.h"

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

void* Gwen::Platform::SDL3::CreatePlatformWindow( int x, int y, int w, int h, const Gwen::String & strWindowTitle )
{
	// since we need to set the renderer on window creation, we don't crea the window here, 
	// we will create the window direct in the renderer structures 
	SDL3Window* newWindow = new SDL3Window( (uint32_t)w, (uint32_t)h, strWindowTitle.c_str() );
	reinterpret_cast<void*>( newWindow );
}

void Gwen::Platform::SDL3::DestroyPlatformWindow( void* pPtr )
{
	SDL3Window* window = static_cast<SDL3Window*>( pPtr );
	delete window; // just destroy window
}

void Gwen::Platform::SDL3::SetBoundsPlatformWindow( void* pPtr, int x, int y, int w, int h )
{
	SDL3Window* window = static_cast<SDL3Window*>( pPtr );
	// TODO:
}

void Gwen::Platform::SDL3::MessagePump( void* pWindow, Gwen::Controls::Canvas* ptarget )
{
	// TODO:
}

bool Gwen::Platform::SDL3::HasFocusPlatformWindow( void* pPtr )
{
	SDL3Window* window = static_cast<SDL3Window*>( pPtr );
	return window->HasFocus();
}

void Gwen::Platform::SDL3::SetWindowMaximized( void* pPtr, bool bMaximized, Gwen::Point & pNewPos, Gwen::Point & pNewSize )
{
	SDL3Window* window = static_cast<SDL3Window*>( pPtr );
	if ( bMaximized )
		window->Maximize();
	else
		window->Restore();
}

void Gwen::Platform::SDL3::SetWindowMinimized( void* pPtr, bool bMinimized )
{
	SDL3Window* window = static_cast<SDL3Window*>( pPtr );
	if ( bMinimized )
		window->Minimize();
	else
		window->Restore();	
}

Gwen::Platform::SDL3Window::SDL3Window(const uint32_t in_width, const uint32_t in_height, const char *in_title ) : 
	m_width( in_width ),
	m_height( in_height ),
	m_title( in_title ),
	m_window( nullptr )
{
}

Gwen::Platform::SDL3Window::~SDL3Window(void)
{
	if ( m_window != nullptr )
	{
		SDL_DestroyWindow( m_window ); 
		m_window = nullptr;
	}

	m_width = 0;
	m_height = 0;
	m_title = nullptr;
}

bool Gwen::Platform::SDL3Window::Create(const uint32_t in_flags)
{
	m_window = SDL_CreateWindow( m_title, m_width, m_height, in_flags );
    return m_window != nullptr;;
}

void Gwen::Platform::SDL3Window::Maximize(void)
{
	SDL_MaximizeWindow( m_window );
}

void Gwen::Platform::SDL3Window::Minimize(void)
{
	SDL_MinimizeWindow( m_window );
}

void Gwen::Platform::SDL3Window::Restore(void)
{
	SDL_RestoreWindow( m_window );
}

bool Gwen::Platform::SDL3Window::HasFocus(void) const
{
	SDL_WindowFlags flags = SDL_GetWindowFlags( m_window );
	return flags & SDL_WINDOW_INPUT_FOCUS;
}
