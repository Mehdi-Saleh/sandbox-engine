// class ParticleMover
// {
//     private: int** board;
//     private: int boardWidth;
//     private: int boardHeight;

//     public: ParticleMover();
//     public: ParticleMover( int** board, int boardWidth, int boardHeight );

//     public: void ApplySandMovement( int x, int y );
//     private: bool GetIsDownEmpty( int x, int y );
//     private: bool GetIsUpEmpty( int x, int y );
//     private: bool GetIsLeftEmpty( int x, int y );
//     private: bool GetIsRightEmpty( int x, int y );
//     private: bool GetIsLeftDownEmpty( int x, int y );
//     private: bool GetIsRightDownEmpty( int x, int y );
//     private: bool GetIsLeftUpEmpty( int x, int y );
//     private: bool GetIsRightUpEmpty( int x, int y );
//     private: bool GetIsEmpty( int x, int y );
//     private: void SwapWithDown( int x, int y );
//     private: void SwapWithUp( int x, int y );
//     private: void SwapWithLeft( int x, int y );
//     private: void SwapWithRight( int x, int y );
//     private: void SwapWithLeftDown( int x, int y );
//     private: void SwapWithRightDown( int x, int y );
//     private: void SwapWithLeftUp( int x, int y );
//     private: void SwapWithRightUp( int x, int y );
//     private: inline void Swap( int xA, int yA, int xB, int yB );
//     private: inline bool GetIsInBoardBounds( int x, int y );
// };