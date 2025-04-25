#ifndef UI_LABEL
#define UI_LABEL

#include <iostream>
#include <string>
#include "ui_element.cpp"


class UILabel : public UIElement
{
    public: std::string text = "Label";
    public: SDL_Color color { 100, 100, 100, 255 };
    private: bool isHidden = false;


    public: UILabel( short anchorMode, SDL_FPoint relativePos, SDL_FPoint size, SDL_Color color ):
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
        if ( isHidden )
            return;
        if ( isRectDirty )
            UpdateSelfAndChildren();
        // TODO render text
    }
};

#endif