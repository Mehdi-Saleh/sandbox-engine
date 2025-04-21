#ifndef PARTICLE_MOVER
#define PARTICLE_MOVER

#include "elements_data.cpp"
#include "particle_dirs.cpp"

class ParticleMover
{
    private: int** board = nullptr;
    private: bool** alreadyMoved = nullptr;
    private: unsigned short** lastParticleDirs = nullptr;
    private: int boardWidth = 10;
    private: int boardHeight = 10;
    private: ElementsData* elementsData = nullptr;

    public: ParticleMover(){}


    public: ParticleMover( int** board, bool** alreadyMoved, unsigned short** lastParticleDirs, int boardWidth, int boardHeight, ElementsData* elementsData )
    {
        this->board = board;
        this->alreadyMoved = alreadyMoved;
        this->lastParticleDirs = lastParticleDirs;
        this->boardWidth = boardWidth;
        this->boardHeight = boardHeight;
        this->elementsData = elementsData;
    }


    public: bool ApplyPowderMovement( int x, int y )
    {
        int otherX, otherY;
        GetDown( x, y, otherX, otherY );
        if ( GetCanAPassThroughB( x, y, otherX, otherY ) && !GetHasAlreadyMoved( otherX, otherY ) ) // TODO should move through water as well
        {
            Swap( x, y, otherX, otherY );
            lastParticleDirs[x][y] = PARTICLE_DIR_UP;
            lastParticleDirs[otherX][otherY] = PARTICLE_DIR_DOWN;
            return true;
        }

        GetDownRight( x, y, otherX, otherY );
        if ( GetCanAPassThroughB( x, y, otherX, otherY ) && !GetHasAlreadyMoved( otherX, otherY ) )
        {
            Swap( x, y, otherX, otherY );
            lastParticleDirs[x][y] = PARTICLE_DIR_UP_LEFT;
            lastParticleDirs[otherX][otherY] = PARTICLE_DIR_DOWN_RIGHT;
            return true;
        }

        GetDownLeft( x, y, otherX, otherY );
        if ( GetCanAPassThroughB( x, y, otherX, otherY ) && !GetHasAlreadyMoved( otherX, otherY ) )
        {
            Swap( x, y, otherX, otherY );
            lastParticleDirs[x][y] = PARTICLE_DIR_UP_RIGHT;
            lastParticleDirs[otherX][otherY] = PARTICLE_DIR_DOWN_LEFT;
            return true;
        }
        
        return false;
    }


    public: bool ApplyLiquidMovement( int x, int y )
    {
        bool moved = ApplyLiquidMovementNoLeftAndRight( x, y );
        if ( moved )
            return true;

        return ApplyLiquidMovementOnlyLeftAndRight( x, y );
    }


    public: bool ApplyLiquidMovementNoLeftAndRight( int x, int y )
    {
        return ApplyPowderMovement( x, y );
    }


    public: bool ApplyLiquidMovementOnlyLeftAndRight( int x, int y )
    {
        bool isRightFirst = lastParticleDirs[x][y] < PARTICLE_DIR_DOWN;

        int rightX, rightY;
        int leftX, leftY;
        GetRight( x, y, rightX, rightY );
        GetLeft( x, y, leftX, leftY );

        if ( isRightFirst )
        {
            if ( GetIsEmpty( rightX, rightY ) && !GetHasAlreadyMoved( rightX, rightY ) )
            {
                Swap( x, y, rightX, rightY );
                lastParticleDirs[x][y] = PARTICLE_DIR_LEFT;
                lastParticleDirs[rightX][rightY] = PARTICLE_DIR_RIGHT;
                return true;
            }
        }

        if ( GetIsEmpty( leftX, leftY ) && !GetHasAlreadyMoved( leftX, leftY ) )
        {
            Swap( x, y, leftX, leftY );
            lastParticleDirs[x][y] = PARTICLE_DIR_RIGHT;
            lastParticleDirs[leftX][leftY] = PARTICLE_DIR_LEFT;
            return true;
        }

        if ( !isRightFirst )
        {
            if ( GetIsEmpty( rightX, rightY ) && !GetHasAlreadyMoved( rightX, rightY ) )
            {
                Swap( x, y, rightX, rightY );
                lastParticleDirs[x][y] = PARTICLE_DIR_LEFT;
                lastParticleDirs[rightX][rightY] = PARTICLE_DIR_RIGHT;
                return true;
            }
        }

        if ( isRightFirst )
        {
            if ( GetCanAPassThroughB( x, y, rightX, rightY ) && !GetHasAlreadyMoved( rightX, rightY ) && GetIsTheSameElement( x, y, leftX, leftY ) )
            {
                Swap( x, y, rightX, rightY );
                lastParticleDirs[x][y] = PARTICLE_DIR_LEFT;
                lastParticleDirs[rightX][rightY] = PARTICLE_DIR_RIGHT;
                return true;
            }
        }

        if ( GetCanAPassThroughB( x, y, leftX, leftY ) && !GetHasAlreadyMoved( leftX, leftY ) && GetIsTheSameElement( x, y, rightX, rightY ) )
        {
            Swap( x, y, leftX, leftY );
            lastParticleDirs[x][y] = PARTICLE_DIR_RIGHT;
            lastParticleDirs[leftX][leftY] = PARTICLE_DIR_LEFT;
            return true;
        }

        if ( !isRightFirst )
        {
            if ( GetCanAPassThroughB( x, y, rightX, rightY ) && !GetHasAlreadyMoved( rightX, rightY ) && GetIsTheSameElement( x, y, leftX, leftY ) )
            {
                Swap( x, y, rightX, rightY );
                lastParticleDirs[x][y] = PARTICLE_DIR_LEFT;
                lastParticleDirs[rightX][rightY] = PARTICLE_DIR_RIGHT;
                return true;
            }
        }
        
        return false;
    }


    public: bool ApplyGasMovement( int x, int y )
    {
        bool moved = ApplyGasMovementNoLeftAndRight( x, y );
        if ( moved )
            return true;

        return ApplyGasMovementOnlyLeftAndRight( x, y );
    }


    public: bool ApplyGasMovementNoLeftAndRight( int x, int y )
    {
        int otherX, otherY;
        GetUp( x, y, otherX, otherY );
        if ( GetCanAPassThroughB( x, y, otherX, otherY, false ) && !GetHasAlreadyMoved( otherX, otherY ) )
        {
            Swap( x, y, otherX, otherY );
            lastParticleDirs[x][y] = PARTICLE_DIR_DOWN;
            lastParticleDirs[otherX][otherY] = PARTICLE_DIR_UP;
            return true;
        }

        GetUpRight( x, y, otherX, otherY );
        if ( GetCanAPassThroughB( x, y, otherX, otherY, false ) && !GetHasAlreadyMoved( otherX, otherY ) )
        {
            Swap( x, y, otherX, otherY );
            lastParticleDirs[x][y] = PARTICLE_DIR_DOWN_LEFT;
            lastParticleDirs[otherX][otherY] = PARTICLE_DIR_UP_RIGHT;
            return true;
        }

        GetUpLeft( x, y, otherX, otherY );
        if ( GetCanAPassThroughB( x, y, otherX, otherY, false ) && !GetHasAlreadyMoved( otherX, otherY ) )
        {
            Swap( x, y, otherX, otherY );
            lastParticleDirs[x][y] = PARTICLE_DIR_DOWN_RIGHT;
            lastParticleDirs[otherX][otherY] = PARTICLE_DIR_UP_LEFT;
            return true;
        }

        return false;
    }


    public: bool ApplyGasMovementOnlyLeftAndRight( int x, int y )
    {
        bool isRightFirst = lastParticleDirs[x][y] < PARTICLE_DIR_DOWN;

        int otherX, otherY;
        if ( isRightFirst )
        {
            GetRight( x, y, otherX, otherY );
            if ( GetCanAPassThroughB( x, y, otherX, otherY, false ) && !GetHasAlreadyMoved( otherX, otherY ) )
            {
                Swap( x, y, otherX, otherY );
                lastParticleDirs[x][y] = PARTICLE_DIR_LEFT;
                lastParticleDirs[otherX][otherY] = PARTICLE_DIR_RIGHT;
                return true;
            }
        }

        GetLeft( x, y, otherX, otherY );
        if ( GetCanAPassThroughB( x, y, otherX, otherY, false ) && !GetHasAlreadyMoved( otherX, otherY ) )
        {
            Swap( x, y, otherX, otherY );
            lastParticleDirs[x][y] = PARTICLE_DIR_RIGHT;
            lastParticleDirs[otherX][otherY] = PARTICLE_DIR_LEFT;
            return true;
        }

        if ( !isRightFirst )
        {
            GetRight( x, y, otherX, otherY );
            if ( GetCanAPassThroughB( x, y, otherX, otherY, false ) && !GetHasAlreadyMoved( otherX, otherY ) )
            {
                Swap( x, y, otherX, otherY );
                lastParticleDirs[x][y] = PARTICLE_DIR_LEFT;
                lastParticleDirs[otherX][otherY] = PARTICLE_DIR_RIGHT;
                return true;
            }
        }
        
        return false;
    }


    private: inline void GetUp( int x, int y, int &newX, int &newY )
    {
        newX = x;
        newY = y - 1;
    }


    private: inline void GetDown( int x, int y, int &newX, int &newY )
    {
        newX = x;
        newY = y + 1;
    }


    private: inline void GetLeft( int x, int y, int &newX, int &newY )
    {
        newX = x - 1;
        newY = y;
    }


    private: inline void GetRight( int x, int y, int &newX, int &newY )
    {
        newX = x + 1;
        newY = y;
    }


    private: inline void GetUpLeft( int x, int y, int &newX, int &newY )
    {
        newX = x - 1;
        newY = y - 1;
    }


    private: inline void GetUpRight( int x, int y, int &newX, int &newY )
    {
        newX = x + 1;
        newY = y - 1;
    }


    private: inline void GetDownLeft( int x, int y, int &newX, int &newY )
    {
        newX = x - 1;
        newY = y + 1;
    }


    private: inline void GetDownRight( int x, int y, int &newX, int &newY )
    {
        newX = x + 1;
        newY = y + 1;
    }


    private: inline bool GetCanAPassThroughB( int aX, int aY, int bX, int bY, bool reverseDensity = false )
    {
        if ( !( GetIsInBoardBounds( aX, aY ) && GetIsInBoardBounds( bX, bY ) ) )
            return false;

        if ( GetIsEmpty( bX, bY ) )
            return true;
        else{
                int aState = GetParticleState( aX, aY );
                int bState = GetParticleState( bX, bY );
                return (
                        GetCanStateAPassThrougStateB( aState, bState )
                        && ( GetIsADenserThanB( aX, aY, bX, bY ) xor reverseDensity )
                );
            }
    }


    private: bool GetIsEmpty( int x, int y )
    {
        if ( !GetIsInBoardBounds( x, y ) )
            return false;
        else
            return board[x][y] == -1;
    }


    private: bool GetIsSolid( int x, int y )
    {
        if ( !GetIsInBoardBounds( x, y ) )
            return true;
        else
            return GetParticleState( x, y ) == PARTICLE_STATE_SOLID;
    }


    private: bool GetIsPowder( int x, int y )
    {
        if ( !GetIsInBoardBounds( x, y ) )
            return false;
        else
            return GetParticleState( x, y ) == PARTICLE_STATE_POWDER;
    }


    private: bool GetIsLiquid( int x, int y )
    {
        if ( !GetIsInBoardBounds( x, y ) )
            return false;
        else
            return GetParticleState( x, y ) == PARTICLE_STATE_LIQUID;
    }


    private: bool GetIsGas( int x, int y )
    {
        if ( !GetIsInBoardBounds( x, y ) )
            return false;
        else
            return GetParticleState( x, y ) == PARTICLE_STATE_GAS;
    }


    private: bool GetIsADenserThanB( int aX, int aY, int bX, int bY )
    {
        if ( !( GetIsInBoardBounds( aX, aY ) && GetIsInBoardBounds( bX, bY ) ) )
            return true;
        else
            return GetParticleDensity( aX, aY ) > GetParticleDensity( bX, bY );
    }


    private: inline bool GetCanStateAPassThrougStateB( int aState, int bState )
    {
        return aState < bState || ( aState == bState && aState != PARTICLE_STATE_POWDER );
        // return aState != PARTICLE_STATE_SOLID && bState != PARTICLE_STATE_SOLID && !( aState == bState && aState == PARTICLE_STATE_POWDER );
    }


    private: inline bool GetIsTheSameElement( int x, int y, int otherX, int otherY )
    {
        if ( !( GetIsInBoardBounds( x, y ) && GetIsInBoardBounds( otherX, otherY ) ) )
            return false;
        return board[x][y] == board[otherX][otherY];
    }


    private: inline int GetParticleState( int x, int y )
    {
        return elementsData->GetParticleData( board[x][y] )->state;
    }


    private: inline int GetParticleDensity( int x, int y )
    {
        return elementsData->GetParticleData( board[x][y] )->density;
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


    private: void SwapWithDownLeft( int x, int y )
    {
        int newX = x - 1;
        int newY = y + 1;
        Swap( x, y, newX, newY );
    }


    private: void SwapWithDownRight( int x, int y )
    {
        int newX = x + 1;
        int newY = y + 1;
        Swap( x, y, newX, newY );
    }



    private: void SwapWithUpLeft( int x, int y )
    {
        int newX = x - 1;
        int newY = y - 1;
        Swap( x, y, newX, newY );
    }


    private: void SwapWithUpRight( int x, int y )
    {
        int newX = x + 1;
        int newY = y - 1;
        Swap( x, y, newX, newY );
    }


    private: inline void Swap( int xA, int yA, int xB, int yB )
    {
        if ( !( GetIsInBoardBounds( xA, yA ) && GetIsInBoardBounds( xB, yB ) ) )
            return;
        int temp = board[xA][yA];
        board[xA][yA] = board[xB][yB];
        board[xB][yB] = temp;
        alreadyMoved[xA][yA] = board[xA][yA] != -1;
        alreadyMoved[xB][yB] = board[xB][yB] != -1;
    }


    private: inline bool GetHasAlreadyMoved( int x, int y )
    {
        // return false;
        if ( !GetIsInBoardBounds( x, y ) )
            return true;
        return alreadyMoved[x][y];
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