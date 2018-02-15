//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  1858116
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XX   boardUtility.cpp
//XX   utility functions dealing with the board
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "boardUtility.h"
#include "utility.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	doAgain()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool boardUtilities::doAgain()
{
    ut::OutputLine("Enter 1 if you want to restart the game.");
    ut::OutputLine("Enter 2 if you want to quit.");
    long ans = ut::GetLongInRange("Your selection", 1, 2);
    
    if(ans == 1)
        return true;
    else
        return false;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	update()
//  update board, moves, turn number, change the turn and display the board
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void boardUtilities::update(const long move, std::vector<cell> & board, std::vector<long> & moves, long & turnNumber, cell & turn)
{
    board[move] = turn;        //update the board
    moves.push_back(move);     //update the vector of moves
    ++turnNumber;              //increase the turn number
    turn = bu::changeTurn(turn);   //change the turn
    bu::OutputBoard(board);    //display the board
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	OutputBoard()
//  prints the board with noughts/crosses
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void boardUtilities::OutputBoard(const std::vector<cell> & a)
{            
	std::cout << " " << char(a[0]) <<" | " << char(a[1]) <<" | " << char(a[2]) << std::endl;
    std::cout << "---|---|---" << std::endl;
    std::cout << " " << char(a[3]) <<" | " << char(a[4]) <<" | " << char(a[5]) << std::endl;
	std::cout << "---|---|---" << std::endl;
    std::cout << " " << char(a[6]) <<" | " << char(a[7]) <<" | " << char(a[8]) << std::endl;
    std::cout << std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	boardForSelection()
//  prints the board with numbers in empty squares and noughts/crosses
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void boardUtilities::boardForSelection(const std::vector<cell> & board)
{
    ut::OutputLine("** It's your turn **");
    long N = board.size();
    std::vector<long> a(N);       //create an empty long board (vector of long)
    
    for(long i = 0; i < N; ++i)
    {
        //if the cell is empty put a number in the "long copy" of the board
        if( board[i] == ' ' )  
            a[i] = 48 + i;     //knowing that char(48) = 0 (ASCII Character Set)
        else                   //otherwise copy the value of the existing cell
            a[i] = board[i];
    }
    
	std::cout << " " << char(a[0]) <<" | " << char(a[1]) <<" | " << char(a[2]) << std::endl;
    std::cout << "---|---|---" << std::endl;
    std::cout << " " << char(a[3]) <<" | " << char(a[4]) <<" | " << char(a[5]) << std::endl;
	std::cout << "---|---|---" << std::endl;
    std::cout << " " << char(a[6]) <<" | " << char(a[7]) <<" | " << char(a[8]) << std::endl;
    std::cout << std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	checkMoveValidity()
//  check if 'ans' is in the vector 'moves', if so return a false
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool boardUtilities::checkMoveValidity(const std::vector<long> & moves, const long ans)
{
    long N = moves.size();
    
    for(long i = 0; i != N; ++i)
        if(moves[i] == ans)
        {
           ut::OutputLine("cell already selected!");
           return false;
        }
        
    return true;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	checkLine()
//  check if there are two of the same kind in a line (row, column, diagonal)
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long boardUtilities::checkLine(const std::vector<long> & line, const std::vector<cell> & board)
{
    long first = line[0];            //first element
    long second = line[1];           //second element
    long third = line[2];            //third element
    
    if(board[first] == board[second])
        return third;
    else if(board[first] == board[third])
        return second;
    else if(board[second] == board[third])
        return first;
    else
        return -1;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	checkFork()
//  check in the 2D vector of possible tris how many tris opportunity there are
//  (check how many tris opportunity there are in a specific position)
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long boardUtilities::checkFork(const D2VectorLong & cellPossibleTris, const std::vector<cell> & board)
{
    long N = cellPossibleTris.size();
    long nonBlockedOfTwo = 0;      //counts how many not blocked pair there are
    
    for(long i = 0; i != N; ++i)
    {
        long possible = bu::checkLine(cellPossibleTris[i], board);
        
        //if there are two in a line and the third is empty increase the counter
        if(possible != -1 && board[possible] == empty)
            ++nonBlockedOfTwo;
    }
    
    return nonBlockedOfTwo;    
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	randCorner()
//  return a random position of a corner
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long boardUtilities::randCorner(const std::vector<long> & corners)
{
    //initialize random seed
    srand(time(NULL));
    
    const long N = corners.size();                   
    long randomCornerIndex = rand() % N;       //random index between 0 and N
    
    return corners[randomCornerIndex];    
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	emptyCorner()
//  check if there's an empty corner, if so return its position
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long boardUtilities::emptyCorner(const std::vector<cell> & board, const std::vector<long> & corners)
{
    const long Ncorners = corners.size();
    
    for(long i = 0; i != Ncorners; ++i)
    {
        long cornerIndex = corners[i];
        
        if(board[cornerIndex] == empty)
            return cornerIndex;
            
    }
    
    return -1;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	emptySide()
//  check if there's an empty side, if so return its position
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long boardUtilities::emptySide(const std::vector<cell> & board)
{
    const long N = board.size();
    
    long i = 1;
    while( i < N )
    {
        if(board[i] == empty)
            return i;
        i = i + 2;        
    }
            
    return -1;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	changeTurn()
//  it has been created passing the turn by value on purpose, 
//  in order to be able to manage different turns at the same time
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

cell boardUtilities::changeTurn(cell turn)
{
    if(turn == cross)
        return nought;
    else
        return cross;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	createPossibleTris()
//  create for each element of the board a vector containing a vector with 
//  possible tris positions for that specific element
//  e.g. for element 0 of the board it contains {0,1,2},{0,3,6},{0,4,8}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

D3VectorLong boardUtilities::createPossibleTris()
{ 
    //the listing initialization doesn't work on this version of the compiler
    //so I used the "array-initialized" version for 1D vectors
    long arrFirstR[] = {0,1,2};
    const std::vector<long> firstRow(arrFirstR, arrFirstR+3);
    long arrSecR[] = {3,4,5};
    const std::vector<long> secondRow(arrSecR, arrSecR+3);
    long arrThirdR[] = {6,7,8};
    const std::vector<long> thirdRow(arrThirdR, arrThirdR+3);
    long arrFirstC[] = {0,3,6};
    const std::vector<long> firstColumn(arrFirstC, arrFirstC+3);
    long arrSecC[] = {1,4,7};
    const std::vector<long> secondColumn(arrSecC, arrSecC+3);
    long arrThirdC[] = {2,5,8};
    const std::vector<long> thirdColumn(arrThirdC, arrThirdC+3);
    long arrFirstD[] = {0,4,8};
    const std::vector<long> firstDiagonal(arrFirstD, arrFirstD+3);
    long arrSecD[] = {2,4,6};
    const std::vector<long> secondDiagonal(arrSecD, arrSecD+3);
    
    //I haven't found any other ways to initialize a vector of dimension 2-3
    //so I assigned each element with puch_back
    D2VectorLong ZeroPossibleTris;
    ZeroPossibleTris.push_back(firstRow);
    ZeroPossibleTris.push_back(firstColumn);
    ZeroPossibleTris.push_back(firstDiagonal);
    
    D2VectorLong OnePossibleTris;
    OnePossibleTris.push_back(firstRow);
    OnePossibleTris.push_back(secondColumn);
    
    D2VectorLong TwoPossibleTris;
    TwoPossibleTris.push_back(firstRow);
    TwoPossibleTris.push_back(thirdColumn);
    TwoPossibleTris.push_back(secondDiagonal);
    
    D2VectorLong ThreePossibleTris;
    ThreePossibleTris.push_back(secondRow);
    ThreePossibleTris.push_back(firstColumn);
    
    D2VectorLong FourPossibleTris;
    FourPossibleTris.push_back(secondRow);
    FourPossibleTris.push_back(secondColumn);
    FourPossibleTris.push_back(firstDiagonal);
    FourPossibleTris.push_back(secondDiagonal);
    
    D2VectorLong FivePossibleTris;
    FivePossibleTris.push_back(secondRow);
    FivePossibleTris.push_back(thirdColumn);
    
    D2VectorLong SixPossibleTris;
    SixPossibleTris.push_back(thirdRow);
    SixPossibleTris.push_back(firstColumn);
    SixPossibleTris.push_back(secondDiagonal);
    
    D2VectorLong SevenPossibleTris;
    SevenPossibleTris.push_back(thirdRow);
    SevenPossibleTris.push_back(secondColumn);
    
    D2VectorLong EightPossibleTris;
    EightPossibleTris.push_back(thirdRow);
    EightPossibleTris.push_back(thirdColumn);
    EightPossibleTris.push_back(firstDiagonal);
    
    D3VectorLong PossibleTris;
    PossibleTris.push_back(ZeroPossibleTris);
    PossibleTris.push_back(OnePossibleTris);
    PossibleTris.push_back(TwoPossibleTris);
    PossibleTris.push_back(ThreePossibleTris);
    PossibleTris.push_back(FourPossibleTris);
    PossibleTris.push_back(FivePossibleTris);
    PossibleTris.push_back(SixPossibleTris);
    PossibleTris.push_back(SevenPossibleTris);
    PossibleTris.push_back(EightPossibleTris); 
    
    return PossibleTris;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XX     end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
