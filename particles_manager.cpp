#include <iostream>

class ParticlesManager
{
    private: int** board = nullptr;
    private: int boardWidth = 10;
    private: int boardHeight = 10;


    public: ParticlesManager( int boardWidth, int boardHeight )
    {
        this->boardWidth = boardWidth;
        this->boardHeight = boardHeight;
        CreateBoard();
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

        // TEMP
        board[0][0] = 1;
        board[1][1] = 1;
        board[2][2] = 1;
        board[3][3] = 1;
        board[5][5] = 1;
        
    }


    private: void DestroyBoard()
    {
        for ( int i = 0; i < boardWidth; i++ )
        {
            delete [] board[i];
        }
        delete [] board;
    }


    public: int** GetBoard()
    {
        return board;
    }


    public: void AddParticle( int element, int x, int y )
    {
        if ( x >= boardWidth || y >= boardHeight )
        {
            std::cerr << "Out of bounds error: Tried to add particle at (" << x << ", " << y << ")!\n";
            return;
        }

        if ( board[x][y] == -1 )
            board[x][y] = element;
    }


    public: void SwapParticle( int element, int x, int y )
    {
        if ( x >= boardWidth || y >= boardHeight )
        {
            std::cerr << "Out of bounds error: Tried to swap particle at (" << x << ", " << y << ")!\n";
            return;
        }

        board[x][y] = element;
    }


    public: void EraseParticle( int x, int y )
    {
        if ( x >= boardWidth || y >= boardHeight )
        {
            std::cerr << "Out of bounds error: Tried to erase particle at (" << x << ", " << y << ")!\n";
            return;
        }

        board[x][y] = -1;
    }
};

