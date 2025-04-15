#include <SDL3/SDL.h>
#include <iostream>
#include <functional>


class InputHandler
{
    private: bool isQuiting = false;
    private: bool isAddingParticle = false;
    private: bool isErasingParticle = false;
    private: SDL_FPoint mousePos = SDL_FPoint();


    public: void HandleInput()
    {
        SDL_GetMouseState( &mousePos.x, &mousePos.y );

        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_EVENT_QUIT) 
            {
                isQuiting = true;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
            {
                if ( event.button.button == SDL_BUTTON_LEFT )
                    isAddingParticle = true;
                else if ( event.button.button == SDL_BUTTON_RIGHT )
                    isErasingParticle = true;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) 
            {
                if ( event.button.button == SDL_BUTTON_LEFT )
                    isAddingParticle = false;
                else if ( event.button.button == SDL_BUTTON_RIGHT )
                    isErasingParticle= false;
            }
        }
    }


    public: bool GetIsQuiting()
    {
        return isQuiting;
    }


    public: bool GetIsAddingParticle()
    {
        return isAddingParticle;
    }


    public: bool GetIsErasingParticle()
    {
        return isErasingParticle;
    }


    public: SDL_FPoint GetMousePos()
    {
        return mousePos;
    }
};
