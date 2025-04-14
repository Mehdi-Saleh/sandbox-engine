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
        inputHandler.HandleInput();
        if ( inputHandler.GetIsQuiting() )
            running = false;
        else if ( inputHandler.GetIsAddingParticle() )
        {
            SDL_FPoint mousePos = inputHandler.GetMousePos();
            mousePos = renderer.GetScreenToBoardSpace( mousePos.x, mousePos.y );
            particlesManager.AddParticleOfSelected( mousePos.x, mousePos.y );
        }
        else if ( inputHandler.GetIsErasingParticle() )
        {
            SDL_FPoint mousePos = inputHandler.GetMousePos();
            mousePos = renderer.GetScreenToBoardSpace( mousePos.x, mousePos.y );
            particlesManager.EraseParticle( mousePos.x, mousePos.y );
        }

        renderer.RenderBoard();
    }
    
    return 0;
}
