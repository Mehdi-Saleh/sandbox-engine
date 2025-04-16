#ifndef PARTICLE_MOVER
#define PARTICLE_MOVER

class ParticleMover
{
    private: int** board = nullptr;
    private: bool** alreadyMoved = nullptr;
    private: int boardWidth = 10;
    private: int boardHeight = 10;


    public: ParticleMover(){}


    public: ParticleMover( int** board, bool** alreadyMoved, int boardWidth, int boardHeight )
    {
        this->board = board;
        this->alreadyMoved = alreadyMoved;
        this->boardWidth = boardWidth;
        this->boardHeight = boardHeight;
    }


    public: void ApplyPowderMovement( int x, int y )
    {
        if ( GetIsDownEmpty( x, y ) ) // TODO should move through water as well
            SwapWithDown( x, y );
        else if ( GetIsRightDownEmpty( x, y ) )
            SwapWithRightDown( x, y );
        else if ( GetIsLeftDownEmpty( x, y ) )
            SwapWithLeftDown( x, y );
    }


    public: void ApplyLiquidMovement( int x, int y )
    {
        if ( GetIsDownEmpty( x, y ) )
            SwapWithDown( x, y );
        else if ( GetIsRightDownEmpty( x, y ) )
            SwapWithRightDown( x, y );
        else if ( GetIsLeftDownEmpty( x, y ) )
            SwapWithLeftDown( x, y );
        else if ( GetIsRightEmpty( x, y ) )
            SwapWithRight( x, y );
        else if ( GetIsLeftEmpty( x, y ) )
            SwapWithLeft( x, y );
    }


    private: bool GetIsDownEmpty( int x, int y )
    {
        int newX = x;
        int newY = y + 1;
        return GetIsEmpty( newX, newY );
    }


    private: bool GetIsUpEmpty( int x, int y )
    {
        int newX = x;
        int newY = y - 1;
        return GetIsEmpty( newX, newY );
    }


    private: bool GetIsLeftEmpty( int x, int y )
    {
        int newX = x - 1;
        int newY = y;
        return GetIsEmpty( newX, newY );
    }


    private: bool GetIsRightEmpty( int x, int y )
    {
        int newX = x + 1;
        int newY = y;
        return GetIsEmpty( newX, newY );
    }


    private: bool GetIsLeftDownEmpty( int x, int y )
    {
        int newX = x - 1;
        int newY = y + 1;
        return GetIsEmpty( newX, newY );
    }


    private: bool GetIsRightDownEmpty( int x, int y )
    {
        int newX = x + 1;
        int newY = y + 1;
        return GetIsEmpty( newX, newY );
    }


    private: bool GetIsLeftUpEmpty( int x, int y )
    {
        int newX = x - 1;
        int newY = y - 1;
        return GetIsEmpty( newX, newY );
    }


    private: bool GetIsRightUpEmpty( int x, int y )
    {
        int newX = x + 1;
        int newY = y - 1;
        return GetIsEmpty( newX, newY );
    }


    private: bool GetIsEmpty( int x, int y )
    {
        if ( !GetIsInBoardBounds( x, y ) )
            return false;
        else
            return board[x][y] == -1;
    }


    private: void SwapWithDown( int x, int y )
    {
        int newX = x;
        int newY = y + 1;
        Swap( x, y, newX, newY );
    }


    private: void SwapWithUp( int x, int y )
    {
        int newX = x;
        int newY = y - 1;
        Swap( x, y, newX, newY );
    }


    private: void SwapWithLeft( int x, int y )
    {
        int newX = x - 1;
        int newY = y;
        Swap( x, y, newX, newY );
    }


    private: void SwapWithRight( int x, int y )
    {
        int newX = x + 1;
        int newY = y;
        Swap( x, y, newX, newY );
    }


    private: void SwapWithLeftDown( int x, int y )
    {
        int newX = x - 1;
        int newY = y + 1;
        Swap( x, y, newX, newY );
    }


    private: void SwapWithRightDown( int x, int y )
    {
        int newX = x + 1;
        int newY = y + 1;
        Swap( x, y, newX, newY );
    }



    private: void SwapWithLeftUp( int x, int y )
    {
        int newX = x - 1;
        int newY = y - 1;
        Swap( x, y, newX, newY );
    }


    private: void SwapWithRightUp( int x, int y )
    {
        int newX = x + 1;
        int newY = y - 1;
        Swap( x, y, newX, newY );
    }


    private: inline void Swap( int xA, int yA, int xB, int yB )
    {
        int temp = board[xA][yA];
        board[xA][yA] = board[xB][yB];
        board[xB][yB] = temp;
        alreadyMoved[xA][yA] = true;
        alreadyMoved[xB][yB] = true;
    }


    private: inline bool GetIsInBoardBounds( int x, int y )
    {
        return (
            x >= 0
            && x < boardWidth
            && y >= 0
            && y < boardHeight
        );
    }
};

#endif