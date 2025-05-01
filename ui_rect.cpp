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
        bool wasHovered = GetIsPosInRect( mousePos );

        if ( !children.empty() )
            for ( UIElement* child : children )
            {
                wasHovered |= child->CheckWasHovered( mousePos );
            }
        return wasHovered;
    }


    public: bool CheckWasClicked( SDL_FPoint& clickPos ) override
    {
        bool wasClicked = GetIsPosInRect( clickPos );

        if ( !children.empty() )
            for ( UIElement* child : children )
            {
                wasClicked |= child->CheckWasClicked( clickPos );
            }
        return wasClicked;
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