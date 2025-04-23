#ifndef UI_RENDERER
#define UI_RENDERER

#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include "elements_data.cpp"


class BoardRenderer
{
    private: ElementsData* elementsData;

    private: int windowWidth = 10;
    private: int windowHeight = 10;

    private: float particleSize = 8;


    public: BoardRenderer( int width, int height, float partileSize, ElementsData* elementsData )
    {
        this->elementsData = elementsData;
        windowWidth = width;
        windowHeight = height;
        this->particleSize = partileSize;
    }


    ~BoardRenderer()
    {
        
    }


    public: void Init()
    {
        
    }


    public: void Render( SDL_Renderer* sdlRenderer )
    {

    }
};

#endif