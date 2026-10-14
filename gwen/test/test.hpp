
#pragma once

#include <string>
#include <exception>
#include <SDL3/SDL.h>

#define GWEN_NO_ANIMATION
#include "Gwen/Gwen.hpp"

class SDLException : public std::exception
{
public:
    SDLException() : m_message( SDL_GetError() ) 
    {
    }

    explicit SDLException( const std::string& context ) : m_message( context + " | Erro SDL: " + SDL_GetError() )
    {
    }

    virtual const char* what( void ) const noexcept override 
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

class crSDLApp
{    
public:
    crSDLApp( void );
    ~crSDLApp( void );
    void    Run( void );

private:
    Gwen::Platform::Base*           m_platform;
    Gwen::Renderer::Base::Pointer   m_renderer;
    Gwen::Skin::Base::Pointer       m_skin;
    Gwen::Controls::Canvas::Pointer m_canvas;
};
