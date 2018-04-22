/*
 * Queens_puzzle.hpp
 *
 *  Created on: Apr 13, 2018
 *      Author: filip
 */

#ifndef QUEENS_PUZZLE_HPP_
#define QUEENS_PUZZLE_HPP_

#include <vector>
#include "Chess_pieces.hpp"

//two-dimensional vector with extended means of access
template <typename type>
class LinearVector
{
public:
    std::vector <std::vector <type> > lvector; //leaving the vector public to allow for standard access

    LinearVector () {};
    ~LinearVector()
    {
        for (unsigned int i=0; i<lvector.size(); i++) lvector[i].clear();
        lvector.clear();
    }

    //"linear" access counting from first element of first vector
    type& operator[](int ix)
    {
        unsigned int jx=0;
        while (ix>=static_cast<int>(lvector[jx].size()))
        {
            ix-=lvector[jx].size();
            jx++;
        }
        return lvector[jx][ix];
    }

    //returning the combined size of all vectors
    unsigned int size() const
    {
        int S=0;
        for (unsigned int i=0; i<lvector.size(); i++) S+=lvector[i].size();
        return S;
    }

    //calculating the second argument of standard access that corresponds with given index of "linear" access
    int posx(int ix) const
    {
        if (ix<0 || lvector.size()==0 || ix>static_cast<int>(size())) return -1;
        unsigned int jx=0;
        while (ix>=static_cast<int>(lvector[jx].size()))
        {
            ix-=lvector[jx].size();
            jx++;
        }
        return ix;
    }

    //calculating the first argument of standard access that corresponds with given index of "linear" access
    int posy(int ix) const
    {
        if (ix<0 || lvector.size()==0 || ix>static_cast<int>(size())) return -1;
        unsigned int jx=0;
        while (ix>=static_cast<int>(lvector[jx].size()))
        {
            ix-=lvector[jx].size();
            jx++;
        }
        return jx;
    }

    //calculating the index of "linear" access that corresponds with given arguments of standard access
    int lidx (int x, int y) const
    {
        if (x<0 || y<0 || lvector.size()==0 || y>=static_cast<int>(lvector.size()) || x>static_cast<int>(lvector[y].size())) return -1;
        int l=0;
        for (int i=0; i<y; i++) l+=lvector[i].size();
        l+=x;
        return l;
    }

};

void Puzzle();
template <PieceName pnam> bool ThreatenPlaced (int px, int py, class PieceType<pnam>& plp, class PieceVector& Vec);
bool Solve(int iki, int iq, int ir, int ib, int ikn, int ip, int idx, LinearVector<int>& Board, class PieceVector& Vec);
template <PieceName pnam, PieceName PNAM> bool CheckThreaten (int px, int py, class Piece<pnam>& plp, class PieceVector& Vec);
template <PieceName PNAM> bool Try(int iki, int iq, int ir, int ib, int ikn, int ip, int itr, int idx, LinearVector<int>& lBoard, class PieceVector& Vec);
void ProperInput (int& col, int& row, int& iki, int& iq, int& ir, int& ib, int& ikn, int& ip);
void intBoardPrep (int col, int row, LinearVector<int>& lBoard);
void PieceVecFill(int iki, int iq, int ir, int ib, int ikn, int ip, PieceVector& Vec);

#endif /* QUEENS_PUZZLE_HPP_ */
