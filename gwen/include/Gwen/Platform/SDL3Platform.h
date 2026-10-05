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

#include <SDL3/SDL_video.h>

namespace Gwen
{
	namespace Platform
	{
		class SDL3WindowHandle : public WindowHandle
		{
		public:
			SDL3WindowHandle( void );
			~SDL3WindowHandle( void );

			/// Just store the properties of the window
			virtual bool	Create( const Gwen::Rect &in_rect, const Gwen::String & in_title ) override;
			virtual void	Destroy( void ) override;
			virtual void 	SetBounds( const Gwen::Rect &in_rect );
			virtual void 	MessagePump( const Gwen::Controls::Canvas* ptarget );	
			virtual bool	HasFocus( void ) const;	
			virtual void	SetMaximized( const bool bMaximized, Gwen::Rect &out_rect );				
			virtual void	SetMinimized( const bool bMinimized ) const;

			/// @brief Create a OpenGL Based Window
			/// @return true on success 
			bool	CreateWindowOpenGL( void );
			
			/// @brief Create a Window Hadle 
			/// @return true on succes 
			bool	CreateWindowRenderer( void );

			SDL_Window*	GetHandle( void ) const { return m_handle; }

		private:
			Gwen::Rect			m_bounds;
			SDL_WindowID		m_ID;
			String				m_title;
			SDL_Window*			m_handle;
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
				virtual bool SetClipboardText( const UnicodeString & str );

				/// @brief Needed for things like double click
				/// @return 
				virtual float GetTimeInSeconds( void );

				//
				// System Dialogs ( Can return false if unhandled )
				//
				virtual bool FileOpen( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback ) { return false };
				virtual bool FileSave( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback ) { return false };
				virtual bool FolderOpen( const String & Name, const String & StartPath, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback ) { return false };
		};
	}
}
