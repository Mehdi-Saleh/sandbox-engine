#ifndef DRAWING_UTILITY
#define DRAWING_UTILITY

#include <functional>
#include "particles_manager.cpp"


class DrawingUtility
{
    private: ParticlesManager* particlesManager;

    public: int brushSize = 6;
    private: int selectedElement = 1;
    private: bool justSelectedElement = false;

    public: std::function<void(int)> onElementSelected;
    
    
    public: DrawingUtility( ParticlesManager* particlesManager )
    {
        this->particlesManager = particlesManager;
    }


    public: void SelectElement( int element )
    {
        selectedElement = element;
        justSelectedElement = true;
        if ( onElementSelected )
            onElementSelected( element );
    }


    public: void SetBrushSize( int size )
    {
        brushSize = size;
        if ( brushSize < 0 )
            brushSize = 0;
    }


    public: void IncreaseBrushSize( int sizeIncrease )
    {
        brushSize += sizeIncrease;
    }


    public: void DecreaseBrushSize( int sizeDecrease )
    {
        brushSize -= sizeDecrease;
        if ( brushSize < 0 )
            brushSize = 0;
    }


    public: void AddParticles( int x, int y )
    {
        for ( int i = -brushSize; i <= brushSize; i++ )
            for ( int j = -brushSize; j <= brushSize; j++ )
            {
                if ( !GetIsInCircle( i, j, brushSize ) )
                    continue;
                int newX = x + i;
                int newY = y + j;
                particlesManager->AddParticle( selectedElement, newX, newY );
            }
    }


    public: void EraseParticles( int x, int y )
    {
        for ( int i = -brushSize; i <= brushSize; i++ )
            for ( int j = -brushSize; j <= brushSize; j++ )
            {
                if ( !GetIsInCircle( i, j, brushSize ) )
                    continue;
                int newX = x + i;
                int newY = y + j;
                particlesManager->EraseParticle( newX, newY );
            }
    }


    public: void SelectElementFromBoard( int x, int y )
    {
        int element = particlesManager->GetParticle( x, y );
        if ( element != -1 )
            SelectElement( element );
    }


    private: inline bool GetIsInCircle( int x, int y, int r )
    {
        return x*x + y*y <= r*r;
    }


    public: bool GetJustSelectedElement()
    {
        if ( justSelectedElement )
        {
            justSelectedElement = false;
            return true;
        }
        else
            return false;
    }
};

#endif