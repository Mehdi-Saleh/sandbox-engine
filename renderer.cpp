#ifndef RENDERER
#define RENDERER

#include <SDL3/SDL.h>
#include <iostream>
#include <string>
using namespace std;


class Renderer
{
    private: SDL_Window* window = nullptr;
    private: SDL_Renderer* sdlRenderer = nullptr;

    private: string windowName = "Window";
    private: int windowWidth = 10;
    private: int windowHeight = 10;

    private: int** board = nullptr;
    private: int boardWidth = 10;
    private: int boardHeight = 10;

    private: float particleSize = 8;
    private: SDL_FRect particleRect { 0, 0, 10, 10 };

    private: SDL_Color* particleColors = nullptr;
    private: int particleColorsCount;


    public: Renderer( string windowName, int width, int height, float partileSize, int** board )
    {
        this->windowName = windowName;
        windowWidth = width;
        windowHeight = height;
        this->particleSize = partileSize;
        this->board = board;
    }


    ~Renderer()
    {
        delete [] particleColors;

        SDL_DestroyRenderer( sdlRenderer );
        SDL_DestroyWindow( window );
        SDL_Quit();
    }


    public: int Init()
    {
        int exitCode = 0;
        InitBoard();
        InitParticleColors();
        exitCode = InitSDL();
        return exitCode;
    }


    private: int InitSDL()
    {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow( windowName.c_str(),windowWidth, windowHeight, 0 );
        if (window == nullptr) 
        {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }
        sdlRenderer = SDL_CreateRenderer(window, NULL);
        if (sdlRenderer == nullptr) 
        {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow( window );
            SDL_Quit();
            return 1;
        }

        return 0;
    }


    private: void InitBoard()
    {
        boardWidth = windowWidth / particleSize;
        boardHeight = windowHeight / particleSize;
        particleRect.h = particleRect.w = particleSize;
    }


    private: void InitParticleColors()
    {
        // TODO needs to init from settings later
        particleColors = new SDL_Color[10];
        particleColorsCount = 10;

        particleColors[0].r = 0;
        particleColors[0].g = 0;
        particleColors[0].b = 0;
        particleColors[0].a = 255;
        
        particleColors[1].r = 252;
        particleColors[1].g = 219;
        particleColors[1].b = 3;
        particleColors[1].a = 255;
        
        particleColors[2].r = 6;
        particleColors[2].g = 3;
        particleColors[2].b = 219;
        particleColors[2].a = 255;
        
    }


    public: void RenderBoard()
    {
        SDL_SetRenderDrawColor( sdlRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( sdlRenderer );

        for ( int i = 0; i < boardWidth; i++ )
            for ( int j = 0; j < boardHeight; j++ )
            {
                // Ignore empty parts
                if ( board[i][j] == -1 )
                    continue;
                
                SDL_FPoint screenPoint = GetBoardToScreenSpace( i, j );
                particleRect.x = screenPoint.x;
                particleRect.y = screenPoint.y;
                SDL_Color particleColor = particleColors[ board[i][j] ];
                SDL_SetRenderDrawColor( sdlRenderer, particleColor.r, particleColor.g, particleColor.b, particleColor.a );
                SDL_RenderFillRect( sdlRenderer, &particleRect );
            }
        
        SDL_RenderPresent( sdlRenderer ); // Render the screen
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