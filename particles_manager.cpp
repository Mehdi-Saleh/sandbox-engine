#ifndef PARTICLES_MANAGER
#define PARTICLES_MANAGER

#include <iostream>
#include </home/mehdi/My Projects/sandbox-engine/particle_mover.cpp>

class ParticlesManager
{
    private: int** board = nullptr;
    private: int boardWidth = 10;
    private: int boardHeight = 10;

    ParticleMover particleMover;


    public: ParticlesManager( int boardWidth, int boardHeight )
    {
        this->boardWidth = boardWidth;
        this->boardHeight = boardHeight;
        CreateBoard();
        particleMover = ParticleMover( board, boardWidth, boardHeight );
    }


    ~ParticlesManager()
    {
        DestroyBoard();
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


    public: void Update()
    {
        for ( int j = boardHeight - 1; j >= 0; j-- )
            for ( int i = 0; i < boardWidth; i++ )
            {
                if ( board[i][j] == 1 )
                    particleMover.ApplySandMovement( i, j );
            }
    }


    public: int** GetBoard()
    {
        return board;
    }


    public: void AddParticle( int element, int x, int y )
    {
        if ( x >= boardWidth || y >= boardHeight )
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
};

#endif