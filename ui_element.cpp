#ifndef UI_ELEMENT
#define UI_ELEMENT

#include <vector>
#include <SDL3/SDL.h>
#include "ui_anchor_modes.cpp"

class UIElement
{
    private: short anchorMode = 0;
    private: SDL_FPoint pivot;
    private: SDL_Point relativePos { 0, 0 };
    private: SDL_Point size { 10, 10 };
    protected: SDL_Rect rect;
    protected: bool isRectDirty = true;

    protected: UIElement* parent = nullptr;
    protected: std::vector<UIElement> children;


    public: UIElement( short anchorMode, SDL_Point relativePos, SDL_Point size )
    {
        this->anchorMode = anchorMode;
        this->relativePos = relativePos;
        this->size = size;
    }


    public: void UpdateSelfAndChildren()
    {
        UpdateRect();
        if ( !children.empty() )
            for ( UIElement& child : children )
                child.UpdateSelfAndChildren();
    }


    public: void RenderSelfAndChildren( SDL_Renderer* renderer )
    {
        RenderSelf( renderer );
        if ( !children.empty() )
            for ( UIElement& child : children )
                child.RenderSelfAndChildren( renderer );
    }


    public: virtual bool GetWasClicked( const SDL_Point& clickPos ) const
    {
        // Override in children classes
        if ( children.empty() )
            return false;
        
        for ( const UIElement& child : children )
        {
            if ( child.GetWasClicked( clickPos ) )
                return true;
        }
        return false;
    }


    private: void UpdateRect()
    {
        SDL_Point realPos = GetRealPos();
        rect.x = realPos.x;
        rect.y = realPos.y;
        SDL_Point realSize = GetRealSize();
        rect.w = realSize.x;
        rect.h = realSize.y;
        isRectDirty = false;
    }


    protected: virtual void RenderSelf( SDL_Renderer* renderer )
    {
        // Override in children classes
    }


    private: SDL_Point GetRealPos() const
    {
        SDL_Point realPos = relativePos;
        if ( !isRectDirty || parent == nullptr )
        {
            realPos.x = rect.x;
            realPos.y = rect.y;
            return realPos;
        }

        realPos.x -= size.x * pivot.x;
        realPos.y -= size.y * pivot.y;

        switch ( anchorMode )
        {
            case UI_ANCHOR_MODE_TOP_LEFT:
                break;
            case UI_ANCHOR_MODE_FILL:
                break;
            case UI_ANCHOR_MODE_TOP:
                realPos.x -= parent->rect.w * 0.5;
                break;
            case UI_ANCHOR_MODE_TOP_FILL:
                realPos.x -= parent->rect.w * 0.5;
                break;
            case UI_ANCHOR_MODE_TOP_RIGHT:
                realPos.x -= parent->rect.w;
                break;
            case UI_ANCHOR_MODE_RIGHT:
                realPos.x -= parent->rect.w;
                realPos.y -= parent->rect.h * 0.5;
                break;
            case UI_ANCHOR_MODE_RIGHT_FILL:
                realPos.x -= parent->rect.w;
                realPos.y -= parent->rect.h * 0.5;
                break;
            case UI_ANCHOR_MODE_BUTTOM_RIGHT:
                realPos.x -= parent->rect.w;
                realPos.y -= parent->rect.h;
                break;
            case UI_ANCHOR_MODE_BUTTOM:
                realPos.x -= parent->rect.w * 0.5;
                realPos.y -= parent->rect.h;
                break;
            case UI_ANCHOR_MODE_BUTTOM_FILL:
                realPos.x -= parent->rect.w * 0.5;
                realPos.y -= parent->rect.h;
                break;
            case UI_ANCHOR_MODE_BUTTOM_LEFT:
                realPos.y -= parent->rect.w;
                break;
            case UI_ANCHOR_MODE_LEFT:
                realPos.y -= parent->rect.w * 0.5;
                break;
            case UI_ANCHOR_MODE_LEFT_FILL:
                realPos.y -= parent->rect.w * 0.5;
                break;
            case UI_ANCHOR_MODE_CENTER:
                realPos.x -= parent->rect.w * 0.5;
                realPos.y -= parent->rect.h * 0.5;
                break;
        }
    }


    private: SDL_Point GetRealSize() const
    {
        SDL_Point realSize = size;
        if ( !isRectDirty || parent == nullptr )
        {
            realSize.x = rect.w;
            realSize.y = rect.h;
            return realSize;
        }

        if ( 
            anchorMode == UI_ANCHOR_MODE_FILL 
            || anchorMode == UI_ANCHOR_MODE_TOP_FILL 
            || anchorMode == UI_ANCHOR_MODE_BUTTOM_FILL 
            )
            realSize.x = parent->rect.w;
        if ( 
            anchorMode == UI_ANCHOR_MODE_FILL 
            || anchorMode == UI_ANCHOR_MODE_LEFT_FILL 
            || anchorMode == UI_ANCHOR_MODE_RIGHT_FILL 
            )
            realSize.y = parent->rect.h;
        
        return realSize;
    }
};

#endif