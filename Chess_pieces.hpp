/*
 * Chess_pieces.hpp
 *
 *  Created on: Apr 13, 2018
 *      Author: filip
 */

#ifndef CHESS_PIECES_HPP_
#define CHESS_PIECES_HPP_

#include <memory>
#include <cstdlib>
#include <vector>

enum PieceName {KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN}; //enumeration type for better described operations on chess pieces

template <PieceName pnam> class PieceType;

//main class representing pieces on board
template <PieceName pnam>
class Piece
{
    int* x; //position on board
    int* y;
    std::shared_ptr< PieceType<pnam> > ptypeptr; //type of piece with specialized operations on it

public:
    Piece(): x(new int(-1)), y(new int(-1)), ptypeptr(std::make_shared < PieceType <pnam> >()) {}; //new piece of a type
    Piece(const Piece& pc): x(new int(-1)), y(new int(-1)), ptypeptr(pc.ptypeptr) {}; //new piece of an existing type added to the group with given piece
    Piece(Piece&& pc): x(pc.x), y(pc.y)
    {
        pc.x=nullptr;
        pc.y=nullptr;
        ptypeptr=nullptr;
        ptypeptr.swap(pc.ptypeptr);
    }
    ~Piece()
    {
        delete x;
        delete y;
        ptypeptr.reset();
    }

    //= operators change position and maybe the group the piece belongs to but can't change it's type nor update the board
    Piece& operator= (const Piece& pc)
    {
        if (this!=&pc)
        {
            *x=pc.rx();
            *y=pc.ry();
            ptypeptr.reset();
            ptypeptr=pc.rptypeptr();
        }
        return *this;
    }

    Piece& operator= (Piece&& pc)
    {
        if (this!=&pc)
        {
            x=pc.x;
            y=pc.y;
            pc.x=nullptr;
            pc.y=nullptr;
            ptypeptr.reset();
            ptypeptr=nullptr;
            ptypeptr.swap(pc.ptypeptr);
        }
        return *this;
    }

    bool Threatened (int bx, int by, int px, int py) //checking if the given board tile would be threatened if the piece were to stand on given coordinates
    {
        if (bx==-1) return false;
        return ptypeptr->Threatenedt (bx, by, px, py);
    }

    void Take( std::vector <std::vector <int> >& Board) //taking the piece off the board
    {
        if(*x!=-1)
        {
            ptypeptr->Taket(*x, *y, Board);
            *x=-1;
            *y=-1;
        }
    }

    void Place(int px, int py, std::vector <std::vector <int> >& Board) //placing the piece on the Board
    {
        if (px!=-1 && py!=-1)
        {
            if (*x!=-1) Take(Board);
            *x=px;
            *y=py;
            ptypeptr->Placet(px, py, Board);
        }
    }

    //returning constant values of stored data
    inline const int rx() const
    {
        return *x;
    }
    inline const int ry() const
    {
        return *y;
    }
    inline const std::shared_ptr< PieceType<pnam> >& rptypeptr() const
    {
        return ptypeptr;
    }
};

//assistant class representing different versions of operations that can be done on pieces for every piece type
template <PieceName pnam>
class PieceType
{
    PieceName type;

    template <PieceName NAM> friend class Piece; //making sure that operations can only be called via individual pieces
public:
    PieceType(): type(pnam) {};
    ~PieceType() {};
private:

    template <PieceName pname> bool Threatenedt (int bx, int by, int px, int py); //checking if given tile would be threatened if a piece of this type were to be placed on given position (with specialization with regard to each piece type's unique move pattern)
    void Taket (int px, int py, std::vector <std::vector <int> >& Board); //placing the piece of this type on given position and updating the board (with specialization with regard to each piece type's unique move pattern)
    void Placet (int px, int py, std::vector <std::vector <int> >& Board); //taking the piece of this type off the given tile and updating the board (with specialization with regard to each piece type's unique move pattern)
};

//all possible specializations of PieceType class
template <>
class PieceType <KING>
{
    PieceName type;

    template <PieceName NAM> friend class Piece;
public:
    PieceType(): type(KING) {};
    ~PieceType() {};
private:

    bool Threatenedt (int bx, int by, int px, int py)
    {
        if ((abs(bx-px)==1 && abs (by-py)<=1) || (abs(by-py)==1 && abs (bx-px)<=1)) return 1;
        return 0;
    }
    void Taket (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        for (int i=-1; i<=1; i++)
        {
            for (int j=-1; j<=1; j++)
            {
                Board[py+i][px+j]--;
            }
        }
        Board[py][px]++;
    }
    void Placet (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        for (int i=-1; i<=1; i++)
        {
            for (int j=-1; j<=1; j++)
            {
                Board[py+i][px+j]++;
            }
        }
        Board[py][px]--;
    }
};

template<>
class PieceType <QUEEN>
{
    PieceName type;

    template <PieceName NAM> friend class Piece;
public:
    PieceType(): type(QUEEN) {};
    ~PieceType() {};
private:

    bool Threatenedt (int bx, int by, int px, int py)
    {
        if (abs(bx-px)==abs(by-py) || bx==px || by==py) return 1;
        return 0;
    }
    void Taket (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        for (int i=0; i<static_cast<int>(Board.size()); i++)
        {
            if (px-abs(py-i)>=0) Board[i][px-abs(py-i)]--;
            if (px+abs(py-i)<static_cast<int>(Board[py].size())) Board[i][px+abs(py-i)]--;
            Board[i][px]--;
        }
        for (unsigned int i=0; i<Board[py].size(); i++)
        {
            Board[py][i]--;
        }
        Board[py][px]+=4;
    }
    void Placet (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        for (int i=0; i<static_cast<int>(Board.size()); i++)
        {
            if (px-abs(py-i)>=0) Board[i][px-abs(py-i)]++;
            if (px+abs(py-i)<static_cast<int>(Board[py].size())) Board[i][px+abs(py-i)]++;
            Board[i][px]++;
        }
        for (unsigned int i=0; i<Board[py].size(); i++)
        {
            Board[py][i]++;
        }
        Board[py][px]-=4;
    }
};

template <>
class PieceType <ROOK>
{
    PieceName type;

    template <PieceName NAM> friend class Piece;
public:
    PieceType(): type(ROOK) {};
    ~PieceType() {};
private:

    bool Threatenedt (int bx, int by, int px, int py)
    {
        if (bx==px || by==py) return 1;
        return 0;
    }
    void Taket (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        for (unsigned int i=0; i<Board.size(); i++)
        {
            Board[i][px]--;
        }
        for (unsigned int i=0; i<Board[py].size(); i++)
        {
            Board[py][i]--;
        }
        Board[py][px]+=2;
    }
    void Placet (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        for (unsigned int i=0; i<Board.size(); i++)
        {
            Board[i][px]++;
        }
        for (unsigned int i=0; i<Board[py].size(); i++)
        {
            Board[py][i]++;
        }
        Board[py][px]-=2;
    }
};

template <>
class PieceType <BISHOP>
{
    PieceName type;

    template <PieceName NAM> friend class Piece;
public:
    PieceType(): type(BISHOP) {};
    ~PieceType() {};
private:

    bool Threatenedt (int bx, int by, int px, int py)
    {
        if (abs(bx-px)==abs(by-py)) return 1;
        return 0;
    }
    void Taket (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        for (int i=0; i<static_cast<int>(Board.size()); i++)
        {
            if (px-abs(py-i)>=0) Board[i][px-abs(py-i)]--;
            if (px+abs(py-i)<static_cast<int>(Board[py].size())) Board[i][px+abs(py-i)]--;
        }
        Board[py][px]+=2;
    }
    void Placet (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        for (int i=0; i<static_cast<int>(Board.size()); i++)
        {
            if (px-abs(py-i)>=0) Board[i][px-abs(py-i)]++;
            if (px+abs(py-i)<static_cast<int>(Board[py].size())) Board[i][px+abs(py-i)]++;
        }
        Board[py][px]-=2;
    }
};

template <>
class PieceType <KNIGHT>
{
    PieceName type;

    template <PieceName NAM> friend class Piece;
public:
    PieceType(): type(KNIGHT) {};
    ~PieceType() {};
private:

    bool Threatenedt (int bx, int by, int px, int py)
    {
        if ((abs(bx-px)==2 && abs (by-py)==1) || (abs(by-py)==2 && abs (bx-px)==1)) return 1;
        return 0;
    }
    void Taket (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        for (int i=-2; i<=2; i+=4)
        {
            for (int j=-1; j<=1; j+=2)
            {
                Board[py+i][px+j]--;
                Board[py+j][px+i]--;
            }
        }
    }
    void Placet (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        for (int i=-2; i<=2; i+=4)
        {
            for (int j=-1; j<=1; j+=2)
            {
                Board[py+i][px+j]++;
                Board[py+j][px+i]++;
            }
        }
    }
};

template <>
class PieceType <PAWN>
{
    PieceName type;

    template <PieceName NAM> friend class Piece;
public:
    PieceType(): type(PAWN) {};
    ~PieceType() {};
private:

    bool Threatenedt (int bx, int by, int px, int py)
    {
        if (bx-px==1 && abs(by-py)==1) return 1;
        return 0;
    }
    void Taket (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        Board[py-1][px+1]--;
        Board[py+1][px+1]--;
    }
    void Placet (int px, int py,  std::vector <std::vector <int> >& Board)
    {
        Board[py-1][px+1]++;
        Board[py+1][px+1]++;
    }
};

//assistant class for storing vectors of each piece type in one place
class PieceVector
{
    std::vector < class Piece<KING>* >vki;
    std::vector < class Piece<QUEEN>* >vq;
    std::vector < class Piece<ROOK>* >vr;
    std::vector < class Piece<BISHOP>* >vb;
    std::vector < class Piece<KNIGHT>* >vkn;
    std::vector < class Piece<PAWN>* >vp;
public:
    PieceVector() {};
    ~PieceVector()
    {
        for (unsigned int i=0; i<vki.size(); i++) delete vki[i];
        for (unsigned int i=0; i<vq.size(); i++) delete vq[i];
        for (unsigned int i=0; i<vr.size(); i++) delete vr[i];
        for (unsigned int i=0; i<vb.size(); i++) delete vb[i];
        for (unsigned int i=0; i<vkn.size(); i++) delete vkn[i];
        for (unsigned int i=0; i<vp.size(); i++) delete vp[i];
        vki.clear();
        vq.clear();
        vr.clear();
        vb.clear();
        vkn.clear();
        vp.clear();
    }

    void* operator [](int i) //access to vectors of given type (accepts using PieceName names)(sadly, requires casting to expected type)
    {
        switch (i%6)
        {
        case 0:
        {
            return &vki;
            break;
        }
        case 1:
        {
            return &vq;
            break;
        }
        case 2:
        {
            return &vr;
            break;
        }
        case 3:
        {
            return &vb;
            break;
        }
        case 4:
        {
            return &vkn;
            break;
        }
        case 5:
        {
            return &vp;
            break;
        }
        }
        return nullptr;
    }
};

#endif /* CHESS_PIECES_HPP_ */
