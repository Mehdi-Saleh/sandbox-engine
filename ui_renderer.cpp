#ifndef UI_RENDERER
#define UI_RENDERER

#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include "elements_data.cpp"
#include "ui_element.cpp"
#include "ui_rect.cpp"


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
    }


    public: void Init()
    {
        uiRoot = new UIElement( 
            UI_ANCHOR_MODE_DEFAULT,
            SDL_FPoint{ 0, 0 }, 
            SDL_FPoint{ float( windowWidth ), float( windowHeight ) } 
            );

        UIRect* testRect = new UIRect( 
            UI_ANCHOR_MODE_TOP_RIGHT,
            SDL_FPoint{ 0, 0 }, 
            SDL_FPoint{ 100, 40 },
            SDL_Color{ 255, 255, 100, 255 }
            );
        testRect->SetPivot( 1.0, 0.0 );
        uiRoot->AddChild( testRect );

        UIRect* testRect2 = new UIRect( 
            UI_ANCHOR_MODE_CENTER,
            SDL_FPoint{ 0, 0 }, 
            SDL_FPoint{ 20, 20 },
            SDL_Color{ 100, 100, 20, 255 }
            );
        testRect->AddChild( testRect2 );
        
        uiRoot->UpdateSelfAndChildren();
    }


    public: void Render( SDL_Renderer* sdlRenderer )
    {
        uiRoot->RenderSelfAndChildren( sdlRenderer );
        SDL_SetRenderDrawColor( sdlRenderer, mouseMarkerColor.r, mouseMarkerColor.g, mouseMarkerColor.b , mouseMarkerColor.a );
        DrawCircle( sdlRenderer, mousePos.x, mousePos.y, mouseMarkerRadius );
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
};

#endif