//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  1858116
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// lib_move.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef lib_moveH
#define lib_moveH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "boardUtility.h"
#include <vector>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  namespace MoveFunctions
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

namespace MoveFunctions
{
    long startDecision();    
    long playerMove(const std::vector<long> & moves, const std::vector<cell> & board);
    long computerMove(bool & noWin, 
                      const long move, 
                      const std::vector<cell> & board, 
                      const D3VectorLong & PossibleTris, 
                      const cell turn, 
                      const std::vector<long> & corners, 
                      const std::vector<long> & oppositeCorners, 
                      const std::vector<long> & moves, 
                      const long turnNumber);
    
    long winMove(const std::vector<long> & moves, const D3VectorLong & PossibleTris, const std::vector<cell> & board);
    long checkTwoInARow(const D2VectorLong & cellPossibleTris, const std::vector<cell> & board);
    long forkTurn3(const std::vector<cell> & board, const std::vector<long> & corners, const long move, const std::vector<long> & oppositeCorners, const cell turn);
    long fork(const D3VectorLong & PossibleTris, const std::vector<cell> & a, const cell turn);
    long blockForkThreat(const D3VectorLong & PossibleTris, const std::vector<cell> & a, const cell turn);
    long OppositeCornerMove(const std::vector<long> & corners, const std::vector<long> & oppositeCorners, const std::vector<cell> & board, const cell turn);
    long lastMove(const std::vector<cell> & board, const std::vector<long> & corners);
    
}

namespace mv = MoveFunctions;    //alias

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XX     end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
