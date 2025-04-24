#ifndef UI_RECT
#define UI_RECT

#include <iostream>
#include "ui_element.cpp"


class UIRect : public UIElement
{
    public: SDL_Color color { 100, 100, 100, 255 };
    private: bool isHidden = false;


    public: UIRect( short anchorMode, SDL_FPoint relativePos, SDL_FPoint size, SDL_Color color ):
        UIElement( anchorMode, relativePos, size )
    {
        this->color = color;
    }


    public: bool GetWasClicked( const SDL_FPoint& clickPos ) const override
    {
        if ( GetIsPosInRect( clickPos ) )
            return true;

        if ( children.empty() )
            return false;
        
        for ( const UIElement* child : children )
        {
            if ( child->GetWasClicked( clickPos ) )
                return true;
        }
        return false;
    }


    protected: void RenderSelf( SDL_Renderer* renderer ) override
    {
        SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
        SDL_RenderFillRect( renderer, &rect );
        std::cout << "rendered rect " << rect.h << "," << rect.w << "\n";
    }
};

#endif