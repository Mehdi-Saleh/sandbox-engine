#include "particles_manager.cpp"


class DrawingUtility
{
    private: ParticlesManager* particlesManager;

    public: int brushSize = 1;
    private: int selectedElement = 1;
    
    
    public: DrawingUtility( ParticlesManager* particlesManager )
    {
        this->particlesManager = particlesManager;
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


    private: inline bool GetIsInCircle( int x, int y, int r )
    {
        return x*x + y*y <= r*r;
    }
};
