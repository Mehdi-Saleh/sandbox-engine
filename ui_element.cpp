#ifndef UI_ELEMENT
#define UI_ELEMENT

#include <vector>
#include <iostream>
#include <SDL3/SDL.h>
#include "ui_anchor_modes.cpp"

class UIElement
{
    private: short anchorMode = 0;
    private: SDL_FPoint pivot { 0.5, 0.5 };
    private: SDL_FPoint relativePos { 0, 0 };
    private: SDL_FPoint size { 10, 10 };
    protected: SDL_FRect rect;
    protected: bool isRectDirty = true;

    protected: UIElement* parent = nullptr;
    protected: std::vector<UIElement*> children;


    public: UIElement( short anchorMode, SDL_FPoint relativePos, SDL_FPoint size )
    {
        this->anchorMode = anchorMode;
        this->relativePos = relativePos;
        this->size = size;
    }


    ~UIElement()
    {
        if ( !children.empty() )
            for ( UIElement* child : children )
                delete child;
    }


    public: void AddChild( UIElement* newChild )
    {
        newChild->parent = this;
        newChild->isRectDirty = true;
        children.push_back( newChild );
    }


    public: void RemoveAndDeleteChild( int childNumber )
    {
        if ( childNumber >= children.size() )
        {
            std::cerr << "Tried to remove a UI child that doesn't exist! child id: " << childNumber << "\n";
            return;
        }
        delete children[childNumber];
        children.erase( children.begin() + childNumber );
    }


    public: void UpdateSelfAndChildren()
    {
        UpdateRect();
        if ( !children.empty() )
            for ( UIElement* child : children )
                child->UpdateSelfAndChildren();
    }


    public: void RenderSelfAndChildren( SDL_Renderer* renderer )
    {
        RenderSelf( renderer );
        if ( !children.empty() )
            for ( UIElement* child : children )
                child->RenderSelfAndChildren( renderer );
    }


    public: virtual bool GetWasClicked( const SDL_FPoint& clickPos ) const
    {
        // Override in children classes
        if ( children.empty() )
            return false;
        
        for ( const UIElement* child : children )
        {
            if ( child->GetWasClicked( clickPos ) )
                return true;
        }
        return false;
    }


    private: void UpdateRect()
    {
        SDL_FPoint realPos = GetRealPos();
        rect.x = realPos.x;
        rect.y = realPos.y;
        SDL_FPoint realSize = GetRealSize();
        rect.w = realSize.x;
        rect.h = realSize.y;
        isRectDirty = false;
    }


    protected: virtual void RenderSelf( SDL_Renderer* renderer )
    {
        // Override in children classes
        if ( isRectDirty )
            UpdateSelfAndChildren();
    }


    public: inline bool GetIsPosInRect( SDL_FPoint pos ) const
    {
        return (
            pos.x >= rect.x
            && pos.y >= rect.y
            && pos.x < rect.x + rect.w
            && pos.y < rect.y + rect.h
        );
    }


    public: void SetPivot( float pivotX, float pivotY )
    {
        pivot.x = pivotX;
        pivot.y = pivotY;
        isRectDirty = true;
    }


    private: SDL_FPoint GetRealPos() const
    {
        SDL_FPoint realPos = relativePos;
        if ( !isRectDirty )
        {
            realPos.x = rect.x;
            realPos.y = rect.y;
            return realPos;
        }

        else if ( parent == nullptr )
        {
            realPos.x = relativePos.x;
            realPos.y = relativePos.y;
            return realPos;
        }

        if ( !(
            anchorMode == UI_ANCHOR_MODE_FILL
            || anchorMode == UI_ANCHOR_MODE_TOP_FILL
            || anchorMode == UI_ANCHOR_MODE_LEFT_FILL
            || anchorMode == UI_ANCHOR_MODE_RIGHT_FILL
            || anchorMode == UI_ANCHOR_MODE_BUTTOM_FILL
        )
        )
        {
            realPos.x -= size.x * pivot.x;
            realPos.y -= size.y * pivot.y;
        }

        SDL_FRect parentRect = parent->rect;
        realPos.x += parentRect.x;
        realPos.y += parentRect.y;
        switch ( anchorMode )
        {
            case UI_ANCHOR_MODE_TOP_LEFT:
                break;
            case UI_ANCHOR_MODE_FILL:
                break;
            case UI_ANCHOR_MODE_TOP:
                realPos.x += parentRect.w * 0.5;
                break;
            case UI_ANCHOR_MODE_TOP_FILL:
                break;
            case UI_ANCHOR_MODE_TOP_RIGHT:
                realPos.x += parentRect.w;
                break;
            case UI_ANCHOR_MODE_RIGHT:
                realPos.x += parentRect.w;
                realPos.y += parentRect.h * 0.5;
                break;
            case UI_ANCHOR_MODE_RIGHT_FILL:
                realPos.x += parentRect.w - size.x;
                break;
            case UI_ANCHOR_MODE_BUTTOM_RIGHT:
                realPos.x += parentRect.w;
                realPos.y += parentRect.h;
                break;
            case UI_ANCHOR_MODE_BUTTOM:
                realPos.x += parentRect.w * 0.5;
                realPos.y += parentRect.h;
                break;
            case UI_ANCHOR_MODE_BUTTOM_FILL:
                realPos.y += parentRect.h - size.y;
                break;
            case UI_ANCHOR_MODE_BUTTOM_LEFT:
                realPos.y += parentRect.h;
                break;
            case UI_ANCHOR_MODE_LEFT:
                realPos.y += parentRect.h * 0.5;
                break;
            case UI_ANCHOR_MODE_LEFT_FILL:
                break;
            case UI_ANCHOR_MODE_CENTER:
                realPos.x += parentRect.w * 0.5;
                realPos.y += parentRect.h * 0.5;
                break;
        }
        return realPos;
    }


    private: SDL_FPoint GetRealSize() const
    {
        SDL_FPoint realSize = size;
        if ( !isRectDirty )
        {
            realSize.x = rect.w;
            realSize.y = rect.h;
            return realSize;
        }
        else if ( parent == nullptr )
        {
            realSize.x = size.x;
            realSize.y = size.y;
            return realSize;
        }

        SDL_FRect parentRect = parent->rect;
        if ( 
            anchorMode == UI_ANCHOR_MODE_FILL 
            || anchorMode == UI_ANCHOR_MODE_TOP_FILL 
            || anchorMode == UI_ANCHOR_MODE_BUTTOM_FILL 
            )
            realSize.x = parentRect.w;
        if ( 
            anchorMode == UI_ANCHOR_MODE_FILL 
            || anchorMode == UI_ANCHOR_MODE_LEFT_FILL 
            || anchorMode == UI_ANCHOR_MODE_RIGHT_FILL 
            )
            realSize.y = parentRect.h;
        
        return realSize;
    }
};

#endif