#ifndef INPUT_HANDLER
#define INPUT_HANDLER

#include <SDL3/SDL.h>
#include <iostream>
#include <functional>


class InputHandler
{
    private: bool isQuiting = false;
    private: bool isTogglingUI = false;
    private: bool isTogglingSimulationPause = false;
    private: bool isHoldingShift = false;
    private: bool isLeftClicking = false;
    private: bool isRightClicking = false;
    private: bool isMiddleClicking = false;
    private: bool isIncreasingBrushSize = false;
    private: bool isDecreasingBrushSize = false;
    private: int isSelectingElement = -1;
    private: SDL_FPoint mousePos = SDL_FPoint();


    public: void HandleInput()
    {
        SDL_GetMouseState( &mousePos.x, &mousePos.y );

        isTogglingUI = false;
        isTogglingSimulationPause = false;
        isIncreasingBrushSize = false;
        isDecreasingBrushSize = false;
        isSelectingElement = -1;

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
                    isLeftClicking = true;
                else if ( event.button.button == SDL_BUTTON_RIGHT )
                    isRightClicking = true;
                else if ( event.button.button == SDL_BUTTON_MIDDLE )
                    isMiddleClicking = true;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) 
            {
                if ( event.button.button == SDL_BUTTON_LEFT )
                    isLeftClicking = false;
                else if ( event.button.button == SDL_BUTTON_RIGHT )
                    isRightClicking= false;
                else if ( event.button.button == SDL_BUTTON_MIDDLE )
                    isMiddleClicking = false;
            }
            else if ( event.type == SDL_EVENT_MOUSE_WHEEL ) 
            {
                if ( event.wheel.y < 0 )
                    isDecreasingBrushSize = true;
                else if ( event.wheel.y > 0 )
                    isIncreasingBrushSize = true;
            }
            else if ( event.type == SDL_EVENT_KEY_DOWN ) 
            {
                if ( event.key.scancode == SDL_SCANCODE_LSHIFT )
                    isHoldingShift = true;
                isTogglingUI |= event.key.scancode == SDL_SCANCODE_ESCAPE;
                isTogglingSimulationPause |= event.key.scancode == SDL_SCANCODE_SPACE;
                isIncreasingBrushSize |= event.key.scancode == SDL_SCANCODE_W;
                isDecreasingBrushSize |= event.key.scancode == SDL_SCANCODE_S;

                if ( event.key.key == SDLK_1 )
                    isSelectingElement = 1;
                else if ( event.key.key == SDLK_2 )
                    isSelectingElement = 2;
                else if ( event.key.key == SDLK_3 )
                    isSelectingElement = 3;
                else if ( event.key.key == SDLK_4 )
                    isSelectingElement = 4;
                else if ( event.key.key == SDLK_5 )
                    isSelectingElement = 5;
                else if ( event.key.key == SDLK_6 )
                    isSelectingElement = 6;
                else if ( event.key.key == SDLK_7 )
                    isSelectingElement = 7;
                else if ( event.key.key == SDLK_8 )
                    isSelectingElement = 8;
                else if ( event.key.key == SDLK_9 )
                    isSelectingElement = 9;
                else if ( event.key.key == SDLK_0 )
                    isSelectingElement = 0;
                if ( isHoldingShift && isSelectingElement != -1 )
                    isSelectingElement += 10;
            }
            else if ( event.type == SDL_EVENT_KEY_UP )
            {
                if ( event.key.scancode == SDL_SCANCODE_LSHIFT )
                    isHoldingShift = false;
            } 
        }
    }


    public: bool GetIsQuiting()
    {
        return isQuiting;
    }


    public: bool GetIsTogglingUI()
    {
        return isTogglingUI;
    }


    public: bool GetIsTogglingSimulationPause()
    {
        return isTogglingSimulationPause;
    }


    public: bool GetIsLeftClicking()
    {
        return isLeftClicking;
    }


    public: bool GetIsRightClicking()
    {
        return isRightClicking;
    }


    public: bool GetIsMiddleClicking()
    {
        return isMiddleClicking;
    }


    public: bool GetIsIncreasingBrushSize()
    {
        return isIncreasingBrushSize;
    }


    public: bool GetIsDecreasingBrushSize()
    {
        return isDecreasingBrushSize;
    }


    public: int GetIsSelectingElement()
    {
        return isSelectingElement;
    }


    public: SDL_FPoint GetMousePos()
    {
        return mousePos;
    }
};

#endif