#ifndef UI_RENDERER
#define UI_RENDERER

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>
#include "elements_data.cpp"
#include "ui_element.cpp"
#include "ui_rect.cpp"
#include "ui_label.cpp"
#include "ui_button.cpp"


#define SMALL_FONT_SIZE 12
#define MEDIUM_FONT_SIZE 16
#define BIG_FONT_SIZE 20


class UIRenderer
{
    private: ElementsData* elementsData;

    private: int windowWidth = 10;
    private: int windowHeight = 10;
    private: float particleSize = 8;

    public: SDL_FPoint mousePos;
    private: int mouseMarkerRadius = 10;
    private: SDL_Color mouseMarkerColor { 255, 255, 255, 255 };

    private: UIElement* uiRoot = nullptr;
    private: UILabel* fpsIndicator = nullptr;

    private: TTF_Font* fontSmall = nullptr;
    private: TTF_Font* fontMedium = nullptr;
    private: TTF_Font* fontBig = nullptr;


    public: UIRenderer( int width, int height, float partileSize, ElementsData* elementsData )
    {
        this->elementsData = elementsData;
        windowWidth = width;
        windowHeight = height;
        this->particleSize = partileSize;
    }


    ~UIRenderer()
    {
        delete uiRoot;
        DestroySDL_TTF();
    }


    public: void Init()
    {
        InitSDL_TTF();
        CreateUI();
        uiRoot->UpdateSelfAndChildren();
    }


    private: void InitSDL_TTF()
    {
        TTF_Init();

        fontSmall = TTF_OpenFont( "PixelEmulator-xq08.ttf", SMALL_FONT_SIZE );
        fontMedium = TTF_OpenFont( "PixelEmulator-xq08.ttf", MEDIUM_FONT_SIZE );
        fontBig = TTF_OpenFont( "PixelEmulator-xq08.ttf", BIG_FONT_SIZE );
        if ( !( fontSmall && fontMedium && fontBig ) ) 
        {
            std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
        }
    }


    private: void DestroySDL_TTF()
    {
        TTF_CloseFont( fontSmall );
        TTF_CloseFont( fontMedium );
        TTF_CloseFont( fontBig );
        TTF_Quit();
    }


    public: void Render( SDL_Renderer* sdlRenderer )
    {
        uiRoot->RenderSelfAndChildren( sdlRenderer );
        SDL_SetRenderDrawColor( sdlRenderer, mouseMarkerColor.r, mouseMarkerColor.g, mouseMarkerColor.b , mouseMarkerColor.a );
        DrawCircle( sdlRenderer, mousePos.x, mousePos.y, mouseMarkerRadius );
    }


    public: bool HandleMouseInput( SDL_FPoint& mousePos, bool isClicking )
    {
        if ( isClicking )
            return uiRoot->CheckWasClicked( mousePos );
        else
            return uiRoot->CheckWasHovered( mousePos );
    }


    public: void SetMouseMarkerRadius( int radiusOnBoard )
    {
        mouseMarkerRadius = radiusOnBoard * particleSize;
    }


    int DrawCircle( SDL_Renderer* renderer, int x, int y, int radius )
    {
        int offsetX = 0;
        int offsetY = radius;
        int d = radius - 1;
        int status = 0;

        // TODO render all points at once!
        while ( offsetY >= offsetX ) 
        {
            status += SDL_RenderPoint( renderer, x + offsetX, y + offsetY );
            status += SDL_RenderPoint( renderer, x + offsetY, y + offsetX );
            status += SDL_RenderPoint( renderer, x - offsetX, y + offsetY );
            status += SDL_RenderPoint( renderer, x - offsetY, y + offsetX );
            status += SDL_RenderPoint( renderer, x + offsetX, y - offsetY );
            status += SDL_RenderPoint( renderer, x + offsetY, y - offsetX );
            status += SDL_RenderPoint( renderer, x - offsetX, y - offsetY );
            status += SDL_RenderPoint( renderer, x - offsetY, y - offsetX );

            if ( status < 0 ) 
            {
                status = -1;
                break;
            }

            if ( d >= 2*offsetX ) 
            {
                d -= 2*offsetX + 1;
                offsetX +=1;
            }
            else if ( d < 2 * ( radius - offsetY ) ) 
            {
                d += 2 * offsetY - 1;
                offsetY -= 1;
            }
            else 
            {
                d += 2 * ( offsetY - offsetX - 1 );
                offsetY -= 1;
                offsetX += 1;
            }
        }

        return status;
    }


    public: void SetFPSText( int fps )
    {
        std::string newText = "fps ";
        newText.append( std::to_string( fps ) );
        fpsIndicator->SetText( newText );
    }


    private: void CreateUI()
    {
        uiRoot = new UIElement( 
            UI_ANCHOR_MODE_DEFAULT,
            SDL_FPoint{ 0, 0 }, 
            SDL_FPoint{ float( windowWidth ), float( windowHeight ) } 
            );

        UIElement* fpsIndicatorFrame = new UIElement( 
            UI_ANCHOR_MODE_TOP_RIGHT,
            SDL_FPoint{ 0, 0 }, 
            SDL_FPoint{ 80, 20 }
            );
        fpsIndicatorFrame->SetPivot( 1.0, 0.0 );
        uiRoot->AddChild( fpsIndicatorFrame );

        fpsIndicator = new UILabel( 
            UI_ANCHOR_MODE_CENTER,
            SDL_FPoint{ 0, 0 }, 
            SDL_FPoint{ 60, 20 },
            SDL_Color{ 100, 100, 20, 255 },
            fontSmall
            );
        SDL_Color fpsColor = SDL_Color { 200, 200, 200, 255 };
        fpsIndicator->SetColor( fpsColor );
        fpsIndicator->SetText( "fps 999" );
        fpsIndicatorFrame->AddChild( fpsIndicator );
    }
};

#endif