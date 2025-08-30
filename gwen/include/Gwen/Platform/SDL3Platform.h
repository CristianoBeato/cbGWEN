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

#ifndef GWEN_PLATFORM_H
#define GWEN_PLATFORM_H

#include "Gwen/Structures.h"
#include "Gwen/Events.h"

namespace Gwen
{
	namespace Platform
	{
		class GWEN_EXPORT Base
		{
			public:
				Base( void );
				virtual ~Base( void );
				
				/// @brief Do nothing for this many milliseconds
				/// @param in_ms to wait 
				virtual void Sleep( const uint32_t in_ms ) {};

				/// @brief Set the system cursor to iCursor
				/// Cursors are defined in Structures.h
				/// @param in_cursorID cursor indetity
				virtual void SetCursor( const uint8_t in_cursorID ) {};

				/// @brief Get the relative cursor position
				/// @param p position of the cursos
				virtual void GetCursorPos( Gwen::Point & p ) {};
				
				/// @brief get the size of the current desktop composition 
				/// @param w desktop Width 
				/// @param h desktop height
				virtual void GetDesktopSize( int & w, int & h ) {};

				//
				// Used by copy/paste
				//

				/// @brief aquire the clipboard string content  
				/// @return the clipboard content 
				virtual UnicodeString GetClipboardText( void ) {};

				/// @brief Set the clipboard text 
				/// @param str 
				/// @return 
				virtual bool SetClipboardText( const UnicodeString & str ) { return false; };

				/// @brief Needed for things like double click
				/// @return 
				virtual float GetTimeInSeconds( void ) {};

				//
				// System Dialogs ( Can return false if unhandled )
				//
				virtual bool FileOpen( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback );
				virtual bool FileSave( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback );
				virtual bool FolderOpen( const String & Name, const String & StartPath, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback );

				//
				// Window Creation
				//
				virtual void* CreatePlatformWindow( int x, int y, int w, int h, const Gwen::String & strWindowTitle );
				virtual void DestroyPlatformWindow( void* pPtr );
				virtual void SetBoundsPlatformWindow( void* pPtr, int x, int y, int w, int h );
				virtual void MessagePump( void* pWindow, Gwen::Controls::Canvas* ptarget );
				virtual bool HasFocusPlatformWindow( void* pPtr );
				virtual void SetWindowMaximized( void* pPtr, bool bMaximized, Gwen::Point & pNewPos, Gwen::Point & pNewSize );
				virtual void SetWindowMinimized( void* pPtr, bool bMinimized );
		};
	}
}
#endif
