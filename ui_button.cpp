#ifndef UI_BUTTON
#define UI_BUTTON

#include <iostream>
#include "ui_element.cpp"
#include "ui_rect.cpp"


class UIButton : public UIRect
{
    private: SDL_Color currentColor;
    public: float onHoverColorMult = 1.1;
    public: float onClickColorMult = 0.6;

    public: UIButton( short anchorMode, SDL_FPoint relativePos, SDL_FPoint size, SDL_Color color ):
        UIRect( anchorMode, relativePos, size, color )
    {
        currentColor = color;
    }


    public: bool CheckWasHovered( SDL_FPoint& mousePos ) override
    {
        bool wasHovered = UIRect::CheckWasHovered( mousePos );
        if ( wasHovered )
        {
            currentColor.r = color.r * onHoverColorMult;
            currentColor.g = color.g * onHoverColorMult;
            currentColor.b = color.b * onHoverColorMult;
            currentColor.a = color.a;
            // TODO add on hover events
        }
        else
            currentColor = color;
        return wasHovered;
    }


    public: bool CheckWasClicked( SDL_FPoint& clickPos ) override
    {
        bool wasClicked = UIRect::CheckWasClicked( clickPos );
        if ( wasClicked )
        {
            currentColor.r = color.r * onClickColorMult;
            currentColor.g = color.g * onClickColorMult;
            currentColor.b = color.b * onClickColorMult;
            currentColor.a = color.a;
            // TODO add on click events
        }
        else
            currentColor = color;
        return wasClicked;
    }


    protected: void RenderSelf( SDL_Renderer* renderer ) override
    {
        if ( isHidden )
            return;
            
        if ( isRectDirty )
            UpdateSelfAndChildren();
        SDL_SetRenderDrawColor( renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a );
        SDL_RenderFillRect( renderer, &rect );
    }
};

#endif