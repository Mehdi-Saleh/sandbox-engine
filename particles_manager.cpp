#ifndef PARTICLES_MANAGER
#define PARTICLES_MANAGER

#include <iostream>
#include "particle_mover.cpp"
#include "elements_data.cpp"

#define PARTICLE_DIR_NONE 0
#define PARTICLE_DIR_UP 1
#define PARTICLE_DIR_UP_RIGHT 2
#define PARTICLE_DIR_RIGHT 3
#define PARTICLE_DIR_DOWN_RIGHT 4
#define PARTICLE_DIR_DOWN 5
#define PARTICLE_DIR_DOWN_LEFT 6
#define PARTICLE_DIR_LEFT 7
#define PARTICLE_DIR_UP_LEFT 8



class ParticlesManager
{
    private: ElementsData* elementsData;
    private: int** board = nullptr;
    private: bool** alreadyMoved = nullptr;
    private: unsigned short** lastParticleDirs = nullptr;
    private: int boardWidth = 10;
    private: int boardHeight = 10;

    private: ParticleMover particleMover;

    private: unsigned long updateCount = 0;


    public: ParticlesManager( int boardWidth, int boardHeight, ElementsData* elementsData )
    {
        this->boardWidth = boardWidth;
        this->boardHeight = boardHeight;
        this->elementsData = elementsData;
        CreateBoard();
        CreateAlreadyMoved();
        CreateLastParticleDirs();
        particleMover = ParticleMover( board, alreadyMoved, lastParticleDirs, boardWidth, boardHeight, elementsData );
    }


    ~ParticlesManager()
    {
        DestroyBoard();
        DestroyAlreadyMoved();
        DestroyLastParticleDirs();
    }


    private: void CreateBoard()
    {
        board = new int*[boardWidth];
        for ( int i = 0; i < boardWidth; i++ )
        {
            board[i] = new int[boardHeight];
            for ( int j = 0; j < boardHeight; j++ )
            {
                board[i][j] = -1;
            }
        }
    }


    private: void DestroyBoard()
    {
        for ( int i = 0; i < boardWidth; i++ )
        {
            delete [] board[i];
        }
        delete [] board;
    }


    private: void CreateAlreadyMoved()
    {
        alreadyMoved = new bool*[boardWidth];
        for ( int i = 0; i < boardWidth; i++ )
        {
            alreadyMoved[i] = new bool[boardHeight];
            for ( int j = 0; j < boardHeight; j++ )
            {
                alreadyMoved[i][j] = false;
            }
        }
    }


    private: void CreateLastParticleDirs()
    {
        lastParticleDirs = new unsigned short*[boardWidth];
        for ( int i = 0; i < boardWidth; i++ )
        {
            lastParticleDirs[i] = new unsigned short[boardHeight];
            for ( int j = 0; j < boardHeight; j++ )
            {
                lastParticleDirs[i][j] = 0;
            }
        }
    }


    private: void DestroyAlreadyMoved()
    {
        for ( int i = 0; i < boardWidth; i++ )
        {
            delete [] alreadyMoved[i];
        }
        delete [] alreadyMoved;
    }


    private: void DestroyLastParticleDirs()
    {
        for ( int i = 0; i < boardWidth; i++ )
        {
            delete [] lastParticleDirs[i];
        }
        delete [] lastParticleDirs;
    }


    private: inline void ClearAlreadyMoved()
    {
        for ( int i = 0; i < boardWidth; i++ )
            for ( int j = 0; j < boardHeight; j++ )
                alreadyMoved[i][j] = false;
    }


    public: void Update()
    {
        ClearAlreadyMoved();
        if ( updateCount%6 < 3 )
            for ( int j = boardHeight - 1; j >= 0; j-- )
                for ( int i = boardWidth - 1; i >= 0; i-- )
                {
                    if ( alreadyMoved[i][j] || board[i][j] == -1 )
                        continue;
                    UpdateParticle( i, j );
                }
        else
            for ( int j = boardHeight - 1; j >= 0; j-- )
                for ( int i = 0; i < boardWidth; i++ )
                {
                    if ( alreadyMoved[i][j] || board[i][j] == -1 )
                        continue;
                    UpdateParticle( i, j );
                }
        
        updateCount++;
    }


    public: int** GetBoard()
    {
        return board;
    }


    public: void AddParticle( int element, int x, int y )
    {
        if ( GetIsOutOfBounds( x, y ) )
            return;

        if ( board[x][y] == -1 )
            board[x][y] = element;
    }


    public: void SwapParticle( int element, int x, int y )
    {
        if ( GetIsOutOfBounds( x, y ) )
            return;

        board[x][y] = element;
    }


    public: void EraseParticle( int x, int y )
    {
        if ( GetIsOutOfBounds( x, y ) )
            return;

        board[x][y] = -1;
    }


    private: inline bool GetIsOutOfBounds( int x, int y )
    {
        return ( 
            x >= boardWidth 
            || x < 0
            || y >= boardHeight 
            || y < 0
            );
    }


    private: inline void UpdateParticle( int x, int y )
    {
        ElementParticleData* particleData = elementsData->GetParticleData( board[x][y] );
        if ( particleData->state == PARTICLE_STATE_POWDER )
            particleMover.ApplyPowderMovement( x, y );
        else if (  particleData->state == PARTICLE_STATE_LIQUID )
            particleMover.ApplyLiquidMovement( x, y, true );
        else if (  particleData->state == PARTICLE_STATE_GAS )
        {
            particleMover.ApplyGasMovement( x, y );
        }
    }
};

#endif