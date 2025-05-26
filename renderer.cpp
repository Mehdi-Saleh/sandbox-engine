#ifndef RENDERER
#define RENDERER

#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <functional>
#include "elements_data.cpp"
#include "board_renderer.cpp"
#include "ui_renderer.cpp"


class Renderer
{
    private: BoardRenderer* boardRenderer;
    private: UIRenderer* uiRenderer;

    
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
        delete boardRenderer;
        delete uiRenderer;
        SDL_DestroyRenderer( sdlRenderer );
        SDL_DestroyWindow( window );
        SDL_Quit();
    }


    public: int Init()
    {
        int exitCode = 0;
        exitCode = InitSDL();
        InitBoard();
        InitUI();
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


    private: void InitUI()
    {
        uiRenderer = new UIRenderer( windowWidth, windowHeight, particleSize, elementsData );
        uiRenderer->Init();
    }


    public: void Render()
    {
        SDL_SetRenderDrawColor( sdlRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( sdlRenderer );

        boardRenderer->Render( sdlRenderer );
        uiRenderer->Render( sdlRenderer );

        SDL_RenderPresent( sdlRenderer ); // Render the screen
    }


    public: bool HandleMouseInputForUI( SDL_FPoint& mousePos, bool isClicking )
    {
        return uiRenderer->HandleMouseInput( mousePos, isClicking );
    }


    public: void SetMousePos( SDL_FPoint mouseScreenPos )
    {
        uiRenderer->mousePos = mouseScreenPos;
    }


    public: void SetMouseMarkerRadius( int radiusOnBoard )
    {
        uiRenderer->SetMouseMarkerRadius( radiusOnBoard );
    }


    public: void SetFPSText( int fps )
    {
        uiRenderer->SetFPSText( fps );
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


    public: void CreateSelectElementButtons( std::function<void(int)> selectElement )
    {
        uiRenderer->CreateSelectElementButtons( selectElement );
    }


    public: void UpdateSelectedElement( int element )
    {
        uiRenderer->UpdateSelectedElement( element );
    }
};

#endif