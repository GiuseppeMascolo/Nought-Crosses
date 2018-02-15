//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  1858116
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XX   lib_move.cpp
//XX   move related functions
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "lib_move.h"
#include "boardUtility.h"
#include "utility.h"
#include <iostream>
#include <vector>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	startDecision()
//  ask the player who is going to start
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long MoveFunctions::startDecision()
{
    ut::OutputLine("Enter 1 if you want to start.");
    ut::OutputLine("Enter 2 if you want the computer to start.");
    long ans = ut::GetLongInRange("Your selection", 1, 2);
    ut::OutputLine();
    
    return ans;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	playerMove()
//  ask the player where to move and checks until it is correct
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long MoveFunctions::playerMove(const std::vector<long> & moves, const std::vector<cell> & board)
{
    bool moveValidity = false;       //initialize the validity as false
    long ans = -1;                   //initialize the answer as an invalid one
    bu::boardForSelection(board);    //display the board with numbers
    
    do
    {
        ans = ut::GetLongInRange("Enter the number where you want to play", 0, 8);
        //check if the number entered correspond to an empty square
        moveValidity = bu::checkMoveValidity(moves, ans);
    }
    while(moveValidity == false);  //keep asking untill the number is valid
    
    return ans;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	computerMove()
//  return the optimal move or -1 (when the board is full)
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long MoveFunctions::computerMove(bool & noWin, 
                                 const long move, 
                                 const std::vector<cell> & board, 
                                 const D3VectorLong & PossibleTris, 
                                 const cell turn, 
                                 const std::vector<long> & corners, 
                                 const std::vector<long> & oppositeCorners, 
                                 const std::vector<long> & moves, 
                                 const long turnNumber)
{
    const long centrePos = 4;       //position of the centre
    
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    // WIN
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    long winPosition = winMove(moves, PossibleTris, board); 
    
    //winPosition is the position where computer can win or -1 
    
    if(winPosition != -1)  //if there's a win position
    {
        noWin = false;
        return winPosition;
    }
    
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    // BLOCK
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    long block = mv::checkTwoInARow(PossibleTris[move], board);
    
    //block is the position where to move for a block
    //or -1 if there's nothing to block
    
    if(block != -1)
        return block;
    
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    // FORK
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    long tryFork = -1;        //initialization
    
    //3rd turn separately in order to increase chance to win
    if(turnNumber == 3)
        tryFork = mv::forkTurn3(board, corners, move, oppositeCorners, turn);
    else
        tryFork = mv::fork(PossibleTris, board, turn);
        
    //tryFork is the position where to move for a fork
    //or -1 if there's no possible fork
    
    if(tryFork != -1)
        return tryFork;
     
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    // BLOCK FORK - THREATEN
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    long tryThreatBlockFork = mv::blockForkThreat(PossibleTris, board, turn);
    
    //tryThreatBlockFork is the position where to move to 
    //threaten without creating a fork, it is -1 if there's no
    //threaten or all threaten creates forks
    
    if(tryThreatBlockFork != -1)
        return tryThreatBlockFork;
    
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    // CENTRE
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    if(board[centrePos] == empty)
        return centrePos;
    
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    // OPPOSITE CORNER
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    cell playerTurn = bu::changeTurn(turn);
    long oppCornMove = mv::OppositeCornerMove(corners, oppositeCorners, board, playerTurn);
    
    //oppCornMove is the position where there is an empty
    //corner opposite to a player move or -1 if there is not
    
    if(oppCornMove != -1)
        return oppCornMove;
    
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    // EMPTY CORNER - SIDE (last possible move)
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    return mv::lastMove(board, corners);
    
    //lastmove is the position where there is an empty
    //corner or side (if no corner empty)
      
}

long MoveFunctions::winMove(const std::vector<long> & moves, const D3VectorLong & PossibleTris, const std::vector<cell> & board) 
{
    long computerMoveIndex = moves.size() - 2;
    if(computerMoveIndex >= 0)
    {
        long computerMove = moves[computerMoveIndex];
        //computerMove is the last move of the computer
        
        return mv::checkTwoInARow(PossibleTris[computerMove], board);
    }
    else
    {
        return -1;
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	checkTwoInARow()
//  check if in the 2D vector of possible tris there is any tris opportunity 
//  (check if there is a tris opportunity and return the position)
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long MoveFunctions::checkTwoInARow(const D2VectorLong & cellPossibleTris, const std::vector<cell> & board)
{
    long N = cellPossibleTris.size();
    
    for(long i = 0; i != N; ++i)       //for each vector in cellPossibleTris
    {                                //controll the position of a possible tris      
        long possible = bu::checkLine(cellPossibleTris[i], board);
        
        if(possible != -1 && board[possible] == empty)
            return possible;
    }
    
    return -1;    
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	forkTurn3()
//  specific fork for turn n.3 (to increase possibilities to win)
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long MoveFunctions::forkTurn3(const std::vector<cell> & board, const std::vector<long> & corners, const long move, const std::vector<long> & oppositeCorners, const cell turn)
{
    const long Ncorners = corners.size();
    const long centre = 4;
    
    if(move == centre)
        //if the player moves in the centre the computer moves in its opposite corner
        return mv::OppositeCornerMove(corners, oppositeCorners, board, turn);
    else       
        for(long i = 0; i != Ncorners; ++i)
            if(move == corners[i])   //if player in the corner
                return bu::emptyCorner(board, corners); //PC in an empty corner

    return centre;     //otherwise computer in the centre
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	fork()
//  fork move, returns the position of the possible fork otherwise -1
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long MoveFunctions::fork(const D3VectorLong & PossibleTris, const std::vector<cell> & a, const cell turn)
{
    const long N = a.size();
    
    for(long i = 0; i != N; ++i)              
    {
        if(a[i] == empty) //for each empty element of the board
        {
            std::vector<cell> fakeBoard(N);   //create a copy of the board
            fakeBoard = a;                    //initialized at every loop  
             
            long move = i;
            fakeBoard[move] = turn;           //fake the move in the empty space
            
            //check now if it creates a fork     
            long nBlockTwo = bu::checkFork(PossibleTris[i], fakeBoard);
            
            //if the number of possible tris is 2 return the position
            if(nBlockTwo == 2)
                return i;
            //otherwise search for another empty element for a fake move
        }
    }
    return -1;    //if no positions create a fork return -1
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	blockForkThreat()
//  search for a threaten move which will not result in an opponent fork
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long MoveFunctions::blockForkThreat(const D3VectorLong & PossibleTris, const std::vector<cell> & a, const cell turn)
{
    const long N = a.size();
    
    for(long i = 0; i != N; ++i)
    {
        if(a[i] == empty)  //for each empty element of the real board
        {
            std::vector<cell> fakeBoard(N);   //create a copy of the board
            fakeBoard = a;                    //initialized at every loop  
            
            long move = i;
            fakeBoard[move] = turn;     //fake the move in the empty space
            
            //check if this move is a threaten
            long possibleTwo = mv::checkTwoInARow(PossibleTris[i], fakeBoard); 
            
            //possibleTwo is the position to conclude the tris
            if(possibleTwo != -1)
            {
                cell playerTurn = bu::changeTurn(turn);  
                                
                move = possibleTwo;
                fakeBoard[move] = playerTurn;
                
                //check now if an hypothetical block from the player will lead
                //to a fork for him 
                
                long nBlockTwo = bu::checkFork(PossibleTris[possibleTwo], fakeBoard);
                
                //if the player blocking doesn't have forks, it's a good move
                if(nBlockTwo != 2)
                    return i;
                //otherwise look a the next empty element of the board
            }
            
        }
        
    }
    
    return -1;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	OppositeCornerMove()
//  checks if there's a corner with a specific value (nought/cross) which has
//  opposite corner free, if so return its position
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long MoveFunctions::OppositeCornerMove(const std::vector<long> & corners, const std::vector<long> & oppositeCorners, const std::vector<cell> & board, const cell turn)
{
    const long Ncorners = corners.size();
    
    for(long i = 0; i != Ncorners; ++i)
    {
        long corner = corners[i];  //index to access a corner each loop
        long oppositeCorner = oppositeCorners[i];    //corresponding opposite
        if(board[corner] == turn && board[oppositeCorner] == empty)
            return oppositeCorner;
    }
    
    return -1;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	lastMove()
//  check if there's an empty corner, if not check an empty side and 
//  return the position
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long MoveFunctions::lastMove(const std::vector<cell> & board, const std::vector<long> & corners)
{    
    //check corner empty
    long corn = bu::emptyCorner(board, corners);
    
    if(corn != -1)
        return corn;
    else
    {
        //check sides empty
        long side = bu::emptySide(board);
        return side;
    }
    
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XX     end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
