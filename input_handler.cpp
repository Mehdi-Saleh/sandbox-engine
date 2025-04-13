#include <SDL3/SDL.h>
#include <iostream>
// #include </home/mehdi/My Projects/sandbox-engine/particles_manager.cpp>


class InputHandler
{
    // public: ParticlesManager particlesManager;


    public: void HandleInput()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
            {
                // particlesManager.AddParticle( 1, 20, 20 );
                std::cout << "clicked!\n";
            }
        }
    }
};
