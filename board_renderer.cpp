#ifndef BOARD_RENDERER
#define BOARD_RENDERER

#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include "elements_data.cpp"


class BoardRenderer
{
    private: ElementsData* elementsData;

    private: int windowWidth = 10;
    private: int windowHeight = 10;

    private: int** board = nullptr;
    private: int boardWidth = 10;
    private: int boardHeight = 10;

    private: float particleSize = 8;
    private: SDL_FRect particleRect { 0, 0, 10, 10 };


    public: BoardRenderer( int width, int height, float partileSize, int** board, ElementsData* elementsData )
    {
        this->elementsData = elementsData;
        windowWidth = width;
        windowHeight = height;
        this->particleSize = partileSize;
        this->board = board;
    }


    ~BoardRenderer()
    {
        
    }


    public: void Init()
    {
        boardWidth = windowWidth / particleSize;
        boardHeight = windowHeight / particleSize;
        particleRect.h = particleRect.w = particleSize;
    }


    public: void Render( SDL_Renderer* sdlRenderer )
    {
        for ( int i = 0; i < boardWidth; i++ )
            for ( int j = 0; j < boardHeight; j++ )
            {
                // Ignore empty parts
                if ( board[i][j] == -1 )
                    continue;
                
                SDL_FPoint screenPoint = GetBoardToScreenSpace( i, j );
                particleRect.x = screenPoint.x;
                particleRect.y = screenPoint.y;
                ElementRenderingData* particleData = elementsData->GetRenderingData( board[i][j] );
                SDL_Color color = particleData->color;
                SDL_SetRenderDrawColor( sdlRenderer, color.r, color.g, color.b, color.a );
                SDL_RenderFillRect( sdlRenderer, &particleRect );
            }
    }


    public: SDL_FPoint GetBoardToScreenSpace( int boardX, int boardY )
    {
        SDL_FPoint point = SDL_FPoint();
        point.x = boardX * particleSize;
        point.y = boardY * particleSize;
        return point;
    }


    public: SDL_FPoint GetScreenToBoardSpace( int screenX, int screenY )
    {
        SDL_FPoint point = SDL_FPoint();
        point.x = screenX / particleSize;
        point.y = screenY / particleSize;
        return point;
    }


    // TODO
    // public: void UpdateBoard( particles ) {}
};

#endif