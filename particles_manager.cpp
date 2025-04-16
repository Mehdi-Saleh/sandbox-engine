#ifndef PARTICLES_MANAGER
#define PARTICLES_MANAGER

#include <iostream>
#include </home/mehdi/My Projects/sandbox-engine/particle_mover.cpp>

class ParticlesManager
{
    private: int** board = nullptr;
    private: bool** alreadyMoved = nullptr;
    private: int boardWidth = 10;
    private: int boardHeight = 10;

    ParticleMover particleMover;


    public: ParticlesManager( int boardWidth, int boardHeight )
    {
        this->boardWidth = boardWidth;
        this->boardHeight = boardHeight;
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
                if ( alreadyMoved[i][j] )
                    continue;
                if ( board[i][j] == 1 )
                    particleMover.ApplyPowderMovement( i, j );
                else if ( board[i][j] == 2 )
                    particleMover.ApplyLiquidMovement( i, j );
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
        if ( x >= boardWidth || y >= boardHeight )
            return;

        board[x][y] = element;
    }


    public: void EraseParticle( int x, int y )
    {
        if ( x >= boardWidth || y >= boardHeight )
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