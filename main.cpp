#include <SDL3/SDL.h>
#include <iostream>
#include </home/mehdi/My Projects/sandbox-engine/renderer.cpp>
#include </home/mehdi/My Projects/sandbox-engine/particles_manager.cpp>
#include </home/mehdi/My Projects/sandbox-engine/input_handler.cpp>


#define WINDOW_NAME "Sandbox Engine"
#define WINDOW_WIDTH 640
#define WINDOW_HEGHT 480
#define PARTICLE_SIZE 8.0


int main(int argc, char* argv[]) 
{
    ParticlesManager particlesManager = ParticlesManager( WINDOW_WIDTH/PARTICLE_SIZE, WINDOW_HEGHT/PARTICLE_SIZE );
    Renderer renderer = Renderer( string( WINDOW_NAME ), WINDOW_WIDTH, WINDOW_HEGHT, PARTICLE_SIZE, particlesManager.GetBoard() );
    InputHandler inputHandler = InputHandler();
    // inputHandler.particlesManager = particlesManager;
    int init_exit_code = renderer.Init();
    if ( init_exit_code != 0 )
    {
        cerr << "Failed to init renderer. exit code: " << init_exit_code << "\n";
        return 1;
    }

    SDL_Event event;
    bool running = true;
    bool add = false;
    bool erase = false;
    while ( running ) 
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_EVENT_QUIT) 
            {
                running = false;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
            {
                if ( event.button.button == SDL_BUTTON_LEFT )
                    add = true;
                else if ( event.button.button == SDL_BUTTON_RIGHT )
                    erase = true;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) 
            {
                if ( event.button.button == SDL_BUTTON_LEFT )
                    add = false;
                else if ( event.button.button == SDL_BUTTON_RIGHT )
                    erase= false;
            }
        }
        if ( add || erase )
        {
                float x,y;
                SDL_GetMouseState( &x, &y );
                x /= PARTICLE_SIZE;
                y /= PARTICLE_SIZE;
                if ( add )
                    particlesManager.AddParticle( 1, x, y );
                else 
                    particlesManager.EraseParticle( x, y );
        }

        renderer.RenderBoard();
    }
    
    return 0;
}
