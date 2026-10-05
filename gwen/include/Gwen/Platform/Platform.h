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

#pragma once

#include "Gwen/Structures.h"
#include "Gwen/Events.h"

namespace Gwen
{
	namespace Platform
	{
		class GWEN_EXPORT WindowHandle : public Object
		{
			public:
				typedef AutoPointer<Platform::WindowHandle>	Pointer;

				/// @brief Create the Object
				/// @param in_position Window position coordinates.
				/// @param in_width 
				/// @param in_height 
				/// @param in_title 
				/// @return true on success false on error 
				virtual bool Create( const Gwen::Rect &in_rect, const Gwen::String & in_title ) = 0;

				/// @brief Release window object
				virtual void	Destroy( void ) = 0;
				
				///
				virtual void 	SetBounds( const Gwen::Rect &in_rect ) = 0;

				///
				virtual void 	MessagePump( const Gwen::Controls::Canvas* ptarget ) = 0;
				
				virtual bool	HasFocusPlatformWindow( void ) const = 0;
				
				virtual void	SetWindowMaximized( const bool bMaximized, const Gwen::Rect &out_rect ) = 0;
				
				virtual void	SetWindowMinimized( const bool bMinimized ) = 0;
		};

		class GWEN_EXPORT Base : public Object
		{
			public:
				AutoPointer<Platform::Base>	Pointer;
				
				/// @brief Do nothing for this many milliseconds
				/// @param in_ms to wait 
				virtual void Sleep( const uint32_t in_ms ) = 0;

				/// @brief Set the system cursor to iCursor
				/// Cursors are defined in Structures.h
				/// @param in_cursorID cursor indetity
				virtual void SetCursor( const uint8_t in_cursorID ) = 0;

				/// @brief 
				/// @param  
				/// @return 
				virtual float GetTimeInSeconds( void ) = 0;

				/// @brief Get the relative cursor position
				/// @param p position of the cursos
				virtual void GetCursorPos( Gwen::Point & p ) = 0;
				
				/// @brief get the size of the current desktop composition 
				/// @param w desktop Width 
				/// @param h desktop height
				virtual void GetDesktopSize( int & w, int & h ) = 0;

				//
				// Used by copy/paste
				//

				/// @brief aquire the clipboard string content  
				/// @return the clipboard content 
				virtual UnicodeString GetClipboardText( void ) = 0;

				/// @brief Set the clipboard text 
				/// @param str 
				/// @return 
				virtual bool SetClipboardText( const UnicodeString & str ) = 0;

				//
				// System Dialogs ( Can return false if unhandled )
				//
				virtual bool FileOpen( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback );
				virtual bool FileSave( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback );
				virtual bool FolderOpen( const String & Name, const String & StartPath, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback );
		};
	}
}
