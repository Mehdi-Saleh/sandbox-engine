#ifndef UI_SELECTION_BAR
#define UI_SELECTION_BAR

#include <vector>
#include <iostream>
#include <SDL3/SDL.h>
#include "ui_element.cpp"

class UIFloatingBar : public UIElement
{
    public: bool isFloatingX = false;
    public: bool isFloatingY = false;

    public: UIFloatingBar( short anchorMode, SDL_FPoint relativePos, SDL_FPoint size ):
        UIElement( anchorMode, relativePos, size ) 
    {
    }


    ~UIFloatingBar()
    {
    }


    public: bool CheckWasHovered( SDL_FPoint& mousePos ) override
    {
        bool wasHovered = GetIsPosInRect( mousePos );

        if ( wasHovered )
            UpdateChildPos( mousePos );

        if ( !children.empty() )
            for ( UIElement* child : children )
            {
                wasHovered |= child->CheckWasHovered( mousePos );
            }
        return wasHovered;
    }


    private: void UpdateChildPos( const SDL_FPoint& mousePos )
    {
        if ( children.empty() )
            return;
            
        if ( isFloatingX )
            UpdateChildPosX( mousePos );
        if ( isFloatingY )
            UpdateChildPosY( mousePos );

        children[0]->UpdateSelfAndChildren(true);
    }


    private: void UpdateChildPosX( const SDL_FPoint& mousePos )
    {
        float ratio = ( mousePos.x - rect.x ) / rect.w;
        SDL_FPoint childPos = children[0]->GetRelativePos();
        SDL_FPoint childSize = children[0]->GetSize();
        if ( childSize.x > rect.w )
            childPos.x = - ( childSize.x - rect.w ) * ratio;
        else
            childPos.x = 0;
        children[0]->SetRelativePos( childPos );
    }


    private: void UpdateChildPosY( const SDL_FPoint& mousePos )
    {
        float ratio = ( mousePos.y - rect.y ) / rect.h;
        SDL_FPoint childPos = children[0]->GetRelativePos();
        SDL_FPoint childSize = children[0]->GetSize();
        if ( childSize.y > rect.h )
            childPos.y = - ( childSize.y - rect.h ) * ratio;
        else
            childPos.y = 0;
        children[0]->SetRelativePos( childPos );
    }
};

#endif