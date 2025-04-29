#ifndef UI_RECT
#define UI_RECT

#include <iostream>
#include "ui_element.cpp"


class UIRect : public UIElement
{
    public: SDL_Color color { 100, 100, 100, 255 };
    protected: bool isHidden = false;


    public: UIRect( short anchorMode, SDL_FPoint relativePos, SDL_FPoint size, SDL_Color color ):
        UIElement( anchorMode, relativePos, size )
    {
        this->color = color;
    }


    public: bool CheckWasHovered( SDL_FPoint& mousePos ) override
    {
        if ( GetIsPosInRect( mousePos ) )
            return true;

        if ( children.empty() )
            return false;
        
        for ( UIElement* child : children )
        {
            if ( child->CheckWasHovered( mousePos ) )
                return true;
        }
        return false;
    }


    public: bool CheckWasClicked( SDL_FPoint& clickPos ) override
    {
        if ( GetIsPosInRect( clickPos ) )
            return true;

        if ( children.empty() )
            return false;
        
        for ( UIElement* child : children )
        {
            if ( child->CheckWasClicked( clickPos ) )
                return true;
        }
        return false;
    }


    protected: void RenderSelf( SDL_Renderer* renderer ) override
    {
        if ( isHidden )
            return;
            
        if ( isRectDirty )
            UpdateSelfAndChildren();
        SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
        SDL_RenderFillRect( renderer, &rect );
    }
};

#endif