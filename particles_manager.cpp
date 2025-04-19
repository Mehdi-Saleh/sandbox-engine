#ifndef PARTICLES_MANAGER
#define PARTICLES_MANAGER

#include <iostream>
#include "particle_mover.cpp"
#include "elements_data.cpp"

class ParticlesManager
{
    private: ElementsData* elementsData;
    private: int** board = nullptr;
    private: bool** alreadyMoved = nullptr;
    private: int boardWidth = 10;
    private: int boardHeight = 10;

    ParticleMover particleMover;


    public: ParticlesManager( int boardWidth, int boardHeight, ElementsData* elementsData )
    {
        this->boardWidth = boardWidth;
        this->boardHeight = boardHeight;
        this->elementsData = elementsData;
        CreateBoard();
        CreateAlreadyMoved();
        particleMover = ParticleMover( board, alreadyMoved, boardWidth, boardHeight );
    }


    ~ParticlesManager()
    {
        DestroyBoard();
        DestroyAlreadyMoved();
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


    private: void DestroyAlreadyMoved()
    {
        for ( int i = 0; i < boardWidth; i++ )
        {
            delete [] alreadyMoved[i];
        }
        delete [] alreadyMoved;
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
        for ( int j = boardHeight - 1; j >= 0; j-- )
            for ( int i = 0; i < boardWidth; i++ )
            {
                if ( alreadyMoved[i][j] || board[i][j] == -1 )
                    continue;
                ElementParticleData* particleData = elementsData->GetParticleData( board[i][j] );
                if ( particleData->state == PARTICLE_STATE_POWDER )
                    particleMover.ApplyPowderMovement( i, j );
                else if (  particleData->state == PARTICLE_STATE_LIQUID )
                    particleMover.ApplyLiquidMovement( i, j );
                else if (  particleData->state == PARTICLE_STATE_GAS )
                {
                    particleMover.ApplyGasMovement( i, j );
                }
                else if (  particleData->state == PARTICLE_STATE_PLASMA )
                {
                    // TODO implement plasma movement
                    particleMover.ApplyGasMovement( i, j );
                }
            }
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
};

#endif