//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  1858116
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// main.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "utility.h"
#include "boardUtility.h"
#include "lib_move.h"
#include <vector>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	main
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int main (int argc, char *argv[])
{  
    //create the board constant
    
    const long N_cells = 9;      //number of cell in the board
    
    //3D vector with the positions of possible tris for each cell in the board
    const D3VectorLong PossibleTris = bu::createPossibleTris();
    //create vector containing corner position
    long arrCorn[] = {0,2,6,8};
    const std::vector<long> corners(arrCorn, arrCorn+4);
    //create vector containing opposite corner position for each corner
    long arrOppCorn[] = {8,6,2,0};
    const std::vector<long> oppositeCorners(arrOppCorn, arrOppCorn+4);  
    
    //start the loop of the complete game
    //if the player wants to play again it will be run again   
    do
    {        
        //create the basic variables
        long turnNumber = 1;     //number of the turn that is going to be played
        std::vector<cell> board(N_cells, empty); //empty board
        std::vector<long> moves;         //vector to store all moves done
        long move = 0;                   //move position in the board
        cell turn = cross;               //who is writing on the board
        
        ut::OutputLine("*** NOUGHTS & CROSSES ***");
        ut::OutputLine();
        ut::OutputLine("*** New game ***");
        bu::OutputBoard(board);          //print the board (empty at this point)
        
        //decide who starts
        long start = mv::startDecision();
        
        if(start != 1)               //if the player wants the computer tu start
        {
            ut::OutputLine("** Computer move **");
            
            //random move in a corner
            move = bu::randCorner(corners);
            bu::update(move, board, moves, turnNumber, turn);
        }   
        
        bool noWin = true;  //initialize variable to check if there's a win move
        
        //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        //  start of the moves loop
        //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        do
        {
            //player move
            move = mv::playerMove(moves, board);
            bu::update(move, board, moves, turnNumber, turn); 
            
            //computer move
            move = mv::computerMove(noWin, move, board, PossibleTris, turn, corners, oppositeCorners, moves, turnNumber);
            
            //if the board is full computerMove returns -1
            if(move != -1)
            {
                ut::OutputLine("** Computer move **");
                bu::update(move, board, moves, turnNumber, turn);
            }
            
        }
        while(turnNumber <= N_cells && noWin);
        //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        //  end of the moves loop
        //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        
        //check if there has been a win ora a draw
        if(noWin)
        {
            ut::OutputLine("************");
            ut::OutputLine("*** DRAW ***");
            ut::OutputLine("************");
        }
        else
        {
            ut::OutputLine("********************");
            ut::OutputLine("*** COMPUTER WIN ***");
            ut::OutputLine("********************");
        }
        
    }
    while(bu::doAgain());  //the player has the opportunity to play again
    
    return 0;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end main
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XX     end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
