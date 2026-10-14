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

#include "Gwen/Platform/SDL3Platform.hpp"
#include "Gwen/Controls/Canvas.hpp"
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_clipboard.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>

#ifndef DELETE
#undef DELETE
#endif // DELETE

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

constexpr int MAX_EVENTS = 32;
constexpr uint32_t SDL_EVENT_MOUSE_FIRST = 0;
constexpr uint32_t SDL_EVENT_MOUSE_LAST = 0;
constexpr uint32_t SDL_EVENT_KEY_FIRST = 0;
constexpr uint32_t SDL_EVENT_KEY_LAST = 0;
constexpr uint32_t SDL_EVENT_TEXT_FIRST = 0;
constexpr uint32_t SDL_EVENT_TEXT_LAST = 0;

void Gwen::Platform::SDL3WindowHandle::MessagePump( AutoPointer<Controls::Canvas> &pTarget )
{
    SDL_Event loteEventos[MAX_EVENTS];

	SDL_PumpEvents();

	int eventosRetornados = 0;
	while ((eventosRetornados = SDL_PeepEvents(loteEventos, MAX_EVENTS, SDL_GETEVENT, SDL_EVENT_FIRST, SDL_EVENT_LAST)) > 0) 
    {
		for (int i = 0; i < eventosRetornados; ++i) 
        {
            SDL_Event& ev = loteEventos[i];
            Uint32 eventoWindowID = 0;

            // Extrai o windowID baseado no tipo de evento
            if (ev.type >= SDL_EVENT_WINDOW_FIRST && ev.type <= SDL_EVENT_WINDOW_LAST) 
                eventoWindowID = ev.window.windowID;
			else if (ev.type >= SDL_EVENT_MOUSE_FIRST && ev.type <= SDL_EVENT_MOUSE_LAST) 
                eventoWindowID = ev.motion.windowID; // Funciona para motion, button, wheel
			else if (ev.type >= SDL_EVENT_KEY_FIRST && ev.type <= SDL_EVENT_KEY_LAST) 
                eventoWindowID = ev.key.windowID;
			else if (ev.type >= SDL_EVENT_TEXT_FIRST && ev.type <= SDL_EVENT_TEXT_LAST) 
                eventoWindowID = ev.text.windowID;

            // SE O EVENTO PERTENCE A ESTA JANELA: Processa e envia para o Canvas da Gwen
            if ( eventoWindowID == m_ID ) 
            {
				switch (ev.type)
				{
				    // ---------------------------------------------------------------------	
					// Mouse Motion Event
					// ---------------------------------------------------------------------
					case SDL_EVENT_MOUSE_MOTION:
					{
						Gwen::Point pos{};
						Gwen::Point rel{};
						pos.x = static_cast<int32_t>( ev.motion.x );
            			pos.y = static_cast<int32_t>( ev.motion.y );
            			rel.x = static_cast<int32_t>( ev.motion.xrel );
            			rel.y = static_cast<int32_t>( ev.motion.yrel );
						pTarget->InputMouseMoved( pos, rel );
					} break;

					// ---------------------------------------------------------------------	
					// Mouse Button event
					// ---------------------------------------------------------------------
					case SDL_EVENT_MOUSE_BUTTON_DOWN:
        			case SDL_EVENT_MOUSE_BUTTON_UP:
					{
						int32_t x = static_cast<int32_t>(ev.button.x);
						int32_t y = static_cast<int32_t>(ev.button.y);
						int botaoID = -1;

						// Mapeia o botão do SDL para o índice que a Gwen espera
						// Geralmente: 0 = Esquerdo, 1 = Direito, 2 = Meio
						if (ev.button.button == SDL_BUTTON_LEFT)   botaoID = 0;
						if (ev.button.button == SDL_BUTTON_RIGHT)  botaoID = 1;
						if (ev.button.button == SDL_BUTTON_MIDDLE) botaoID = 2;
						if (botaoID != -1)
						{
							bool isDown = (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN);
							pTarget->InputMouseButton( botaoID, isDown );
						}
					} break;

					// ---------------------------------------------------------------------
					// MOUSE SCROLL EVENT
					// ---------------------------------------------------------------------
					case SDL_EVENT_MOUSE_WHEEL:
					{
						// SDL3 usa float para wheel.x (horizontal) e wheel.y (vertical)
						// Multiplicamos por um fator caso queira acelerar o scroll na UI
						int32_t scrollX = static_cast<int32_t>(ev.wheel.x * 60); 
						int32_t scrollY = static_cast<int32_t>(ev.wheel.y * 60);

						// Se o scroll estiver invertido pelo SO (ex: "Natural Scrolling" no macOS)
						if (ev.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
						{
							scrollX *= -1;
							scrollY *= -1;
						}

						pTarget->InputMouseWheel( scrollY ); // Gwen nativamente foca mais no eixo vertical
						
					} break;

					// ---------------------------------------------------------------------
					// KEYBOARD EVENT
					// ---------------------------------------------------------------------
					case SDL_EVENT_KEY_DOWN:
					case SDL_EVENT_KEY_UP:
					{
						uint8_t k = Gwen::Key::INVALID;
						bool isDown = (ev.type == SDL_EVENT_KEY_DOWN);
						SDL_Keycode key = ev.key.key;

						switch ( key )
						{
							case SDLK_RETURN:
							case SDLK_KP_ENTER:
								k = Gwen::Key::RETURN;
								break;
							case SDLK_BACKSPACE:
								k = Gwen::Key::BACKSPACE;
								break;
							case SDLK_DELETE:
								k = Gwen::Key::DELETE;
								break;
							case SDLK_LEFT:
								k = Gwen::Key::LEFT;
								break;
							case SDLK_RIGHT:
								k = Gwen::Key::RIGHT;
								break;
							case SDLK_UP:
								k = Gwen::Key::UP;
								break;
							case SDLK_DOWN:
								k = Gwen::Key::DOWN;
								break;
							case SDLK_HOME:
								k = Gwen::Key::HOME;
								break;
							case SDLK_END:
								k = Gwen::Key::END;
								break;
							case SDLK_TAB:
								k = Gwen::Key::TAB;
								break;
							case SDLK_ESCAPE:
								k = Gwen::Key::ESCAPE;
								break;
						default:
							break;
						}	
					} break;

					// ---------------------------------------------------------------------
					// Text input 
					// ---------------------------------------------------------------------
					case SDL_EVENT_TEXT_INPUT:
					{
						const char* textoUtf8 = ev.text.text;
            			size_t comprimento = SDL_strlen( textoUtf8 );

						// Armazena temporariamente o ponteiro para o SDL percorrer a string
            			const char* ponteiroLeitura = textoUtf8;
						while (ponteiroLeitura < (textoUtf8 + comprimento))
						{
							// SDL_StepUTF8 decodifica o caractere UTF-8 atual para Unicode (Uint32)
							// e avança o ponteiroLeitura automaticamente para o próximo caractere.
							Uint32 unicodeCodepoint = SDL_StepUTF8( &ponteiroLeitura, nullptr );

							// Evita caracteres nulos ou inválidos
							if (unicodeCodepoint != 0)
							{
								// Envia o caractere Unicode convertido diretamente para a Gwen
								pTarget->InputCharacter(static_cast<Gwen::UnicodeChar>(unicodeCodepoint));
							}
						}
						
					} break;
				};
            } 
            else if (eventoWindowID != 0) 
            {
                // SE O EVENTO É DE OUTRA JANELA: Devolvemos ele para a fila do SDL 
                // para que o MessagePump da outra janela possa capturá-lo!
                SDL_PeepEvents(&ev, 1, SDL_ADDEVENT, 0, 0);
            }
            else 
            {
                // Eventos globais do sistema (ex: SDL_EVENT_QUIT ou eventos de Gamepad)
                // Você decide se trata aqui ou se devolve para a fila principal do motor.
                SDL_PeepEvents(&ev, 1, SDL_ADDEVENT, 0, 0);
            }
        }
        
        // Proteção simples para evitar loops infinitos se você reinjetar eventos idênticos
        // no mesmo frame (geralmente quebrado se o lote processar menos do que o disponível)
        if (eventosRetornados < MAX_EVENTS )
            break; 
	}
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

void Gwen::Platform::SDL3::GetCursorPos(Gwen::Point &p)
{
	float globalX = 0.0f;
    float globalY = 0.0f;

	/// Retrieve current global mouse state, but we only need the position, ignore buttons 
	SDL_GetGlobalMouseState(&globalX, &globalY);

	p.x = static_cast<int>( globalX );
	p.y = static_cast<int>( globalY );
}

//TODO: 
void Gwen::Platform::SDL3::GetDesktopSize( Gwen::Point &p )
{
    /// Retrieve the main monitor 
	SDL_DisplayID primaryDisplay = SDL_GetPrimaryDisplay();
    if ( primaryDisplay != 0 )
	{
        // Retrieve actual display mode 
        const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode( primaryDisplay );
        if (mode) 
		{
            p.x = mode->w;
            p.y = mode->h;
        }
    }
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
