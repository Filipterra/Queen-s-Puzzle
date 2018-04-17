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

enum PieceName {KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN};


template <PieceName pnam>
class PieceType
{
	PieceName type;

public:
	PieceType(): type(pnam) {};
	~PieceType(){};

	bool Threatened (int bx, int by, int px, int py);
	void Taket (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board);
	void Placet (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board);
};

template <>
class PieceType <KING>
{
	PieceName type;

public:
	PieceType(): type(KING) {};
	~PieceType(){};

	bool Threatened (int bx, int by, int px, int py)
	{
	if ((abs(bx-px)==1 && abs (by-py)<=1) || (abs(by-py)==1 && abs (bx-px)<=1)) return 1;
	return 0;
	}
	void Taket (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
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
	void Placet (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
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

public:
	PieceType(): type(QUEEN) {};
	~PieceType(){};

	bool Threatened (int bx, int by, int px, int py)
	{
	if (abs(bx-px)==abs(by-py) || bx==px || by==py) return 1;
	return 0;
	}
	void Taket (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
	{
	for (int i=0; i<bm; i++)
	{
		if (px-abs(py-i)>=0) Board[i][px-abs(py-i)]--;
		if (px+abs(py-i)<bn) Board[i][px+abs(py-i)]--;
		Board[i][px]--;
	}
	for (int i=0; i<bn; i++)
	{
		Board[py][i]--;
	}
	Board[py][px]+=4;
	}
	void Placet (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
	{
	for (int i=0; i<bm; i++)
	{
		if (px-abs(py-i)>=0) Board[i][px-abs(py-i)]++;
		if (px+abs(py-i)<bn) Board[i][px+abs(py-i)]++;
		Board[i][px]++;
	}
	for (int i=0; i<bn; i++)
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

public:
	PieceType(): type(ROOK) {};
	~PieceType(){};

	bool Threatened (int bx, int by, int px, int py)
	{
	if (bx==px || by==py) return 1;
	return 0;
	}
	void Taket (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
	{
	for (int i=0; i<bm; i++)
	{
		Board[i][px]--;
	}
	for (int i=0; i<bn; i++)
	{
		Board[py][i]--;
	}
	Board[py][px]+=2;
	}
	void Placet (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
	{
	for (int i=0; i<bm; i++)
	{
		Board[i][px]++;
	}
	for (int i=0; i<bn; i++)
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

public:
	PieceType(): type(BISHOP) {};
	~PieceType(){};

	bool Threatened (int bx, int by, int px, int py)
	{
	if (abs(bx-px)==abs(by-py)) return 1;
	return 0;
	}
	void Taket (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
	{
	for (int i=0; i<bm; i++)
	{
		if (px-abs(py-i)>=0) Board[i][px-abs(py-i)]--;
		if (px+abs(py-i)<bn) Board[i][px+abs(py-i)]--;
	}
	Board[py][px]+=2;
	}
	void Placet (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
	{
	for (int i=0; i<bm; i++)
	{
		if (px-abs(py-i)>=0) Board[i][px-abs(py-i)]++;
		if (px+abs(py-i)<bn) Board[i][px+abs(py-i)]++;
	}
	Board[py][px]-=2;
	}
};

template <>
class PieceType <KNIGHT>
{
	PieceName type;

public:
	PieceType(): type(KNIGHT) {};
	~PieceType(){};

	bool Threatened (int bx, int by, int px, int py)
	{
	if ((abs(bx-px)==2 && abs (by-py)==1) || (abs(by-py)==2 && abs (bx-px)==1)) return 1;
	return 0;
	}
	void Taket (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
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
	void Placet (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
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

public:
	PieceType(): type(PAWN) {};
	~PieceType(){};

	bool Threatened (int bx, int by, int px, int py)
	{
	return 0;
	}
	void Taket (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
	{

	}
	void Placet (int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
	{

	}
};

template <PieceName pnam>
class Piece
{
	int x;
	int y;
	std::shared_ptr< PieceType<pnam> > ptypeptr;

public:
	Piece(): x(-1), y(-1), ptypeptr(std::make_shared < PieceType <pnam> >()) {};
	Piece(std::shared_ptr< PieceType<pnam> > tptr): x(-1), y(-1) {ptypeptr=tptr;};
	~Piece() {ptypeptr.reset();}

	void Take(int bn, int bm, std::vector <std::vector <int> >& Board)
	{
		this->ptypeptr->Taket(this->x, this->y, bn, bm, Board);
		this->x=-1;
		this->y=-1;
	}

	void Place(int px, int py, int bn, int bm, std::vector <std::vector <int> >& Board)
	{
		if (this->x!=-1) this->Take(bn, bm, Board);
		this->x=px;
		this->y=py;
		this->ptypeptr->Placet(px, py, bn, bm, Board);
	}

	const int rx() const {return x;}
	const int ry() const {return y;}
	const std::shared_ptr< PieceType<pnam> >& rptypeptr() const {return ptypeptr;}
};


#endif /* CHESS_PIECES_HPP_ */
