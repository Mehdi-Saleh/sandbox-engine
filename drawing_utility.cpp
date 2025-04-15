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
        for ( int i = x - brushSize; i <= x + brushSize; i++ )
            for ( int j = y - brushSize; j <= y + brushSize; j++ )
                particlesManager->AddParticle( selectedElement, i, j );
    }


    public: void EraseParticles( int x, int y )
    {
        for ( int i = x - brushSize; i <= x + brushSize; i++ )
            for ( int j = y - brushSize; j <= y + brushSize; j++ )
                particlesManager->EraseParticle( i, j );
    }
};
