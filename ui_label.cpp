#ifndef UI_LABEL
#define UI_LABEL

#include <iostream>
#include <string>
#include <SDL3_ttf/SDL_ttf.h>
#include "ui_element.cpp"


class UILabel : public UIElement
{
    private: std::string text = "Label";
    private: SDL_Color color { 100, 100, 100, 255 };
    private: TTF_Font* font;
    private: bool isHidden = false;

    private: SDL_Texture* texture = nullptr;
    private: bool isTextureDirty = true;


    public: UILabel( short anchorMode, SDL_FPoint relativePos, SDL_FPoint size, SDL_Color color, TTF_Font* font ):
        UIElement( anchorMode, relativePos, size )
    {
        this->color = color;
        this->font = font;
    }


    ~UILabel()
    {
        SDL_DestroyTexture( texture );
    }


    public: void SetText( std::string newText )
    {
        text = newText;
        isTextureDirty = true;
    }


    public: void SetColor( SDL_Color& newColor )
    {
        color = newColor;
        isTextureDirty = true;
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
            
        if ( isTextureDirty )
        {
            UpdateTexture( renderer );
            isRectDirty = true;
        }
        SDL_RenderTexture( renderer, texture, NULL, &rect );
    }


    private: void UpdateTexture( SDL_Renderer* renderer )
    {
        SDL_Surface* surface = TTF_RenderText_Blended( font, text.c_str(), 0, color );
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_GetTextureSize( texture, &rect.w, &rect.h );
        SDL_DestroySurface( surface );
    }
};

#endif