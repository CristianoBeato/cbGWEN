
#include "test.hpp"
#include <cstdlib>
#include <cstdint>
#include <cstdarg>
#include <stdexcept>
#include <iostream>

#include "Gwen/Platform/SDL3Platform.hpp"
#include "Gwen/Platform/Renderers/SDLOpenGL.hpp"
#include "Gwen/Skins/Simple.hpp"

crSDLApp::crSDLApp( void )
{
    if( !SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) )
        throw SDLException();

    m_platform = new Gwen::Platform::SDL3();
    m_renderer = new Gwen::Renderer::SDLOpenGL();
    m_skin = new Gwen::Skin::Simple();

    m_canvas = new Gwen::Controls::WindowCanvas( 0, 0, 800, 600, m_platform, m_skin, "SDL3Teste" );
}

crSDLApp::~crSDLApp( void )
{
    SDL_Quit();
}

void crSDLApp::Run(void)
{
    if( !m_canvas )
        return;
    
    while ( !m_canvas->InputQuit() )
    {
        /* code */
    }
    
}

int main( int argc, char* argv[] )
{
    try
    {
        crSDLApp app = crSDLApp();
        app.Run(); 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}