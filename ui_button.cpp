#ifndef UI_BUTTON
#define UI_BUTTON

#include <iostream>
#include <functional>
#include "ui_element.cpp"
#include "ui_rect.cpp"


class UIButton : public UIRect
{
    private: SDL_Color currentColor;
    public: float onHoverColorMult = 1.1;
    public: float onClickColorMult = 0.6;

    public: std::function<void()> onHover;
    public: std::function<void()> onClick;
    private: bool wasHoveredLastFrame = false;
    private: bool wasClickedLastFrame = false;

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
            SetColorToHoverColor();
            if ( !wasHoveredLastFrame && onHover )
                onHover();
        }
        else
            currentColor = color;
        wasHoveredLastFrame = wasHovered;
        wasClickedLastFrame = false;
        return wasHovered;
    }


    public: bool CheckWasClicked( SDL_FPoint& clickPos ) override
    {
        bool wasClicked = UIRect::CheckWasClicked( clickPos );
        if ( wasClicked )
        {
            SetColorToClickColor();
            if ( !wasClickedLastFrame && onClick )
                onClick();
        }
        else
            currentColor = color;
        wasClickedLastFrame = wasClicked;
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


    private: inline void SetColorToHoverColor()
    {
        currentColor.r = color.r * onHoverColorMult;
        if ( currentColor.r < color.r )
            currentColor.r = 255;
        currentColor.g = color.g * onHoverColorMult;
        if ( currentColor.g < color.g )
            currentColor.g = 255;
        currentColor.b = color.b * onHoverColorMult;
        if ( currentColor.b < color.b )
            currentColor.b = 255;
        currentColor.a = color.a;
    }


    private: inline void SetColorToClickColor()
    {
        currentColor.r = color.r * onClickColorMult;
        currentColor.g = color.g * onClickColorMult;
        currentColor.b = color.b * onClickColorMult;
        currentColor.a = color.a;
    }
};

#endif