//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  1858116
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// boardUtility.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef boardUtilitiesH
#define boardUtilitiesH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <vector>

//create the enum cell type represeting a possible situation for each cell
enum cell { nought='O', cross='X', empty=' ' };
//alias for 3D vector of long
typedef std::vector< std::vector<std::vector<long> > > D3VectorLong;
//alias for 2D vector of long
typedef std::vector<std::vector<long> > D2VectorLong;

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  namespace boardUtility
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

namespace boardUtilities
{
    bool doAgain();
    void update(const long move, std::vector<cell> & board, std::vector<long> & moves, long & turnNumber, cell & turn);
    
    void OutputBoard(const std::vector<cell> & a);
    void boardForSelection(const std::vector<cell> & board);
    
    bool checkMoveValidity(const std::vector<long> & moves, const long ans);
    long checkLine(const std::vector<long> & line, const std::vector<cell> & board);
    long checkFork(const D2VectorLong & cellPossibleTris, const std::vector<cell> & board);
    long randCorner(const std::vector<long> & corners);
    long emptyCorner(const std::vector<cell> & board, const std::vector<long> & corners);
    long emptySide(const std::vector<cell> & board);
    
    cell changeTurn(cell turn);
    
    D3VectorLong createPossibleTris();
    
}

namespace bu = boardUtilities;    //alias

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XX     end of file
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
