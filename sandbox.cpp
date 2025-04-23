#ifndef SANDBOX
#define SANDBOX

#include <SDL3/SDL.h>
#include <iostream>
#include "renderer.cpp"
#include "particles_manager.cpp"
#include "input_handler.cpp"
#include "drawing_utility.cpp"
#include "elements_data.cpp"


#define WINDOW_NAME "Sandbox Engine"
#define WINDOW_WIDTH 1280
#define WINDOW_HEGHT 720
#define PARTICLE_SIZE 5.0
#define UPDATE_INTERVAL_IN_MILLISECONDS 20


class Sandbox
{
    ElementsData elementsData = ElementsData();
    ParticlesManager particlesManager = ParticlesManager( WINDOW_WIDTH/PARTICLE_SIZE, WINDOW_HEGHT/PARTICLE_SIZE, &elementsData );
    Renderer renderer = Renderer( std::string( WINDOW_NAME ), WINDOW_WIDTH, WINDOW_HEGHT, PARTICLE_SIZE, particlesManager.GetBoard(), &elementsData );
    InputHandler inputHandler = InputHandler();
    DrawingUtility drawingUtility = DrawingUtility( &particlesManager );

    SDL_Event event;
    Uint64 timePassedSinceUpdateInMilliseconds = 0;
    bool running = true;


    public: void Start()
    {
        Init();

        while ( running ) 
        {
            HandleInput();
            HandleUpdate();
            Render();
        }
    }


    private: void Init()
    {
        elementsData.LoadDefaultElements();
        int init_exit_code = renderer.Init();
        if ( init_exit_code != 0 )
        {
            std::cerr << "Failed to init renderer. exit code: " << init_exit_code << "\n";
        }
    }


    private: void HandleInput()
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
    }


    private: void HandleUpdate()
    {
        Uint64 newTimePassed = SDL_GetTicks();
        if ( newTimePassed - timePassedSinceUpdateInMilliseconds > UPDATE_INTERVAL_IN_MILLISECONDS )
        {
            particlesManager.Update();
            timePassedSinceUpdateInMilliseconds = newTimePassed;
        }
    }


    private: void Render()
    {
        renderer.Render();
    }
};

#endif