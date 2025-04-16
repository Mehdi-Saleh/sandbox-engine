#include <SDL3/SDL.h>
#include <iostream>
#include "renderer.cpp"
#include "particles_manager.cpp"
#include "input_handler.cpp"
#include "drawing_utility.cpp"


#define WINDOW_NAME "Sandbox Engine"
#define WINDOW_WIDTH 640
#define WINDOW_HEGHT 480
#define PARTICLE_SIZE 5.0

#define UPDATE_INTERVAL_IN_MILLISECONDS 30


int main(int argc, char* argv[]) 
{
    ParticlesManager particlesManager = ParticlesManager( WINDOW_WIDTH/PARTICLE_SIZE, WINDOW_HEGHT/PARTICLE_SIZE );
    Renderer renderer = Renderer( string( WINDOW_NAME ), WINDOW_WIDTH, WINDOW_HEGHT, PARTICLE_SIZE, particlesManager.GetBoard() );
    InputHandler inputHandler = InputHandler();
    DrawingUtility drawingUtility = DrawingUtility( &particlesManager );

    int init_exit_code = renderer.Init();
    if ( init_exit_code != 0 )
    {
        cerr << "Failed to init renderer. exit code: " << init_exit_code << "\n";
        return 1;
    }

    SDL_Event event;
    Uint64 timePassedSinceUpdateInMilliseconds = 0;
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
            drawingUtility.AddParticles( mousePos.x, mousePos.y );
        }
        else if ( inputHandler.GetIsErasingParticle() )
        {
            SDL_FPoint mousePos = inputHandler.GetMousePos();
            mousePos = renderer.GetScreenToBoardSpace( mousePos.x, mousePos.y );
            drawingUtility.EraseParticles( mousePos.x, mousePos.y );
        }
        else if ( inputHandler.GetIsIncreasingBrushSize() )
        {
            drawingUtility.IncreaseBrushSize( 1 );
        }
        else if ( inputHandler.GetIsDecreasingBrushSize() )
        {
            drawingUtility.DecreaseBrushSize( 1 );
        }
        else if ( inputHandler.GetIsSelectingElement() != -1 )
        {
            drawingUtility.SelectElement( inputHandler.GetIsSelectingElement() );
        }

        Uint64 newTimePassed = SDL_GetTicks();
        if ( newTimePassed - timePassedSinceUpdateInMilliseconds > UPDATE_INTERVAL_IN_MILLISECONDS )
        {
            particlesManager.Update();
            timePassedSinceUpdateInMilliseconds = newTimePassed;
        }
        renderer.RenderBoard();
        
    }
    
    return 0;
}
