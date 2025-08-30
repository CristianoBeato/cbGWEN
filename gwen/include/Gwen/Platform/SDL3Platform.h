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

#ifndef GWEN_SDL_PLATFORM_H
#define GWEN_SDL_PLATFORM_H

#include "Gwen/Structures.h"
#include "Gwen/Events.h"

namespace Gwen
{
	namespace Platform
	{
		class SDL3Window
		{
		public:
			SDL3Window( const uint32_t in_width, const uint32_t in_height, const char* in_title );
			~SDL3Window( void );
			bool	Create( const uint32_t in_flags );
			void	Maximize( void );
			void	Minimize( void );
			void	Restore( void );
			bool	HasFocus( void ) const;

		private:
			const char*			m_title;
			uint32_t			m_width;
			uint32_t			m_height;
			struct SDL_Window*	m_window;
		};

		class GWEN_EXPORT SDL3 : public Platform::Base
		{
			public:
				SDL3( void );
				virtual ~SDL3( void );
				
				/// @brief Do nothing for this many milliseconds
				/// @param in_ms to wait 
				virtual void Sleep( const uint32_t in_ms ) override;

				/// @brief Set the system cursor to iCursor
				/// Cursors are defined in Structures.h
				/// @param in_cursorID cursor indetity
				virtual void SetCursor( const uint8_t in_cursorID ) override;

				/// @brief Get the relative cursor position
				/// @param p position of the cursos
				virtual void GetCursorPos( Gwen::Point & p ) override;
				
				/// @brief get the size of the current desktop composition 
				/// @param w desktop Width 
				/// @param h desktop height
				virtual void GetDesktopSize( int & w, int & h ) override;

				//
				// Used by copy/paste
				//

				/// @brief aquire the clipboard string content  
				/// @return the clipboard content 
				virtual UnicodeString GetClipboardText( void );

				/// @brief Set the clipboard text 
				/// @param str 
				/// @return 
				virtual bool SetClipboardText( const UnicodeString & str ) { return false; };

				/// @brief Needed for things like double click
				/// @return 
				virtual float GetTimeInSeconds( void ) { return 0.0f; };

				//
				// System Dialogs ( Can return false if unhandled )
				//
				virtual bool FileOpen( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback ) { return false };
				virtual bool FileSave( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback ) { return false };
				virtual bool FolderOpen( const String & Name, const String & StartPath, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback ) { return false };

				//
				// Window Creation
				//
				virtual void* CreatePlatformWindow( int x, int y, int w, int h, const Gwen::String & strWindowTitle ) { return nullptr; }
				virtual void DestroyPlatformWindow( void* pPtr ) {}
				virtual void SetBoundsPlatformWindow( void* pPtr, int x, int y, int w, int h ) { }
				virtual void MessagePump( void* pWindow, Gwen::Controls::Canvas* ptarget ) { }
				virtual bool HasFocusPlatformWindow( void* pPtr ) { return false; }
				virtual void SetWindowMaximized( void* pPtr, bool bMaximized, Gwen::Point & pNewPos, Gwen::Point & pNewSize ) {}
				virtual void SetWindowMinimized( void* pPtr, bool bMinimized ) {}
		};
	}
}

#endif // !GWEN_SDL_PLATFORM_H