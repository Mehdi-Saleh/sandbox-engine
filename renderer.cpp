#ifndef RENDERER
#define RENDERER

#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include "elements_data.cpp"
#include "board_renderer.cpp"


class Renderer
{
    private: BoardRenderer* boardRenderer;
    
    private: SDL_Window* window = nullptr;
    private: SDL_Renderer* sdlRenderer = nullptr;

    private: std::string windowName = "Window";
    private: int windowWidth = 10;
    private: int windowHeight = 10;

    private: float particleSize = 8;

    private: int** board = nullptr;
    private: ElementsData* elementsData = nullptr;


    public: Renderer( std::string windowName, int width, int height, float partileSize, int** board, ElementsData* elementsData )
    {
        this->windowName = windowName;
        this->elementsData = elementsData;
        windowWidth = width;
        windowHeight = height;
        this->particleSize = partileSize;
        this->board = board;
    }


    ~Renderer()
    {
        SDL_DestroyRenderer( sdlRenderer );
        SDL_DestroyWindow( window );
        SDL_Quit();
    }


    public: int Init()
    {
        int exitCode = 0;
        exitCode = InitSDL();
        InitBoard();
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
        boardRenderer = new BoardRenderer( windowWidth, windowHeight, particleSize, board, elementsData );
        boardRenderer->Init();
    }


    public: void Render()
    {
        SDL_SetRenderDrawColor( sdlRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( sdlRenderer );

        boardRenderer->Render( sdlRenderer );

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
        // point.x = 1;
        // point.y = 1;
        return point;
    }
};

#endif