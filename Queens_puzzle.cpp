/*
 * Queens_puzzle.cpp
 *
 *  Created on: Apr 13, 2018
 *      Author: filip
 */

#include <iostream>
#include <memory>
#include <vector>
#include <climits>
#include <limits>
#include "Chess_pieces.hpp"
#include "Queens_puzzle.hpp"

using namespace std;

//checking weather the given piece threatens any pieces from given type
template <PieceName pnam, PieceName PNAM>
inline bool CheckThreaten (int px, int py, class Piece<pnam>& plp, class PieceVector& Vec)
{
    for (unsigned int i=0; i<(*(static_cast<vector<class Piece<PNAM>*>*>(Vec[PNAM]))).size(); i++) if(plp.Threatened((*(static_cast<vector<class Piece<PNAM>*>*>(Vec[PNAM])))[i]->rx(), (*(static_cast<vector<class Piece<PNAM>*>*>(Vec[PNAM])))[i]->ry(), px, py)) return true;
    return false;
}

//checking weather the given piece threatens any others
template <PieceName pnam>
bool ThreatenPlaced (int px, int py, class Piece<pnam>& plp, class PieceVector& Vec)
{
    if (CheckThreaten<pnam, KING>(px, py, plp, Vec)) return true; //checking possible threat to every type of piece
    if (CheckThreaten<pnam, QUEEN>(px, py, plp, Vec)) return true;
    if (CheckThreaten<pnam, ROOK>(px, py, plp, Vec)) return true;
    if (CheckThreaten<pnam, BISHOP>(px, py, plp, Vec)) return true;
    if (CheckThreaten<pnam, KNIGHT>(px, py, plp, Vec)) return true;
    if (CheckThreaten<pnam, PAWN>(px, py, plp, Vec)) return true;
    return false;
}

//tries to put a piece of given type on the given tile and takes it off if it is not a proper solution
template <PieceName PNAM>
bool Try(int iki, int iq, int ir, int ib, int ikn, int ip, int itr, int idx, LinearVector<int>& lBoard, class PieceVector& Vec)
{
    (*(static_cast<vector<class Piece<PNAM>*>*>(Vec[PNAM])))[(*(static_cast<vector<class Piece<PNAM>*>*>(Vec[PNAM]))).size()-itr]->Place(lBoard.posx(idx), lBoard.posy(idx), lBoard.lvector); //placing the piece on the board
    if (Solve (iki, iq, ir, ib, ikn, ip, idx+1, lBoard, Vec)) return true; //continuing going through the board until it decides weather it's a proper solution
    (*(static_cast<vector<class Piece<PNAM>*>*>(Vec[PNAM])))[(*(static_cast<vector<class Piece<PNAM>*>*>(Vec[PNAM]))).size()-itr]->Take(lBoard.lvector); //taking the piece off
    return false;
}

//goes through entire board trying to put different pieces on unthreatened tiles until it arrives at a solution or concludes that there isn't any
bool Solve(int iki, int iq, int ir, int ib, int ikn, int ip, int idx, LinearVector<int>& lBoard, class PieceVector& Vec)
{
    if (iki==0 && iq==0 && ir==0 && ib==0 && ikn==0 && ip==0) return true; //if all the pieces have been placed - it's a viable solution

    for (; idx<=lBoard.lidx(lBoard.lvector[0].size()-3,lBoard.lvector.size()-3); idx++) //going through the playable part of the board with an uplayable "frame"
    {
        if (lBoard[idx]==0) //if the tile isn't already threatened - trying to put different pieces on it
        {
            if (iq>0 && !ThreatenPlaced<QUEEN>(lBoard.posx(idx), lBoard.posy(idx), *((*(static_cast<vector<class Piece<QUEEN>*>*>(Vec[QUEEN])))[(*(static_cast<vector<class Piece<QUEEN>*>*>(Vec[QUEEN]))).size()-iq]),Vec))
            {
                if(Try<QUEEN>(iki, iq-1, ir, ib, ikn, ip, iq, idx, lBoard, Vec)) return true;
            }
            if (ir>0 && !ThreatenPlaced<ROOK>(lBoard.posx(idx), lBoard.posy(idx), *((*(static_cast<vector<class Piece<ROOK>*>*>(Vec[ROOK])))[(*(static_cast<vector<class Piece<ROOK>*>*>(Vec[ROOK]))).size()-ir]),Vec))
            {
                if(Try<ROOK>(iki, iq, ir-1, ib, ikn, ip, ir, idx, lBoard, Vec)) return true;
            }
            if (ib>0 && !ThreatenPlaced<BISHOP>(lBoard.posx(idx), lBoard.posy(idx), *((*(static_cast<vector<class Piece<BISHOP>*>*>(Vec[BISHOP])))[(*(static_cast<vector<class Piece<BISHOP>*>*>(Vec[BISHOP]))).size()-ib]),Vec))
            {
                if(Try<BISHOP>(iki, iq, ir, ib-1, ikn, ip, ib, idx, lBoard, Vec)) return true;
            }
            if (ikn>0 && !ThreatenPlaced<KNIGHT>(lBoard.posx(idx), lBoard.posy(idx), *((*(static_cast<vector<class Piece<KNIGHT>*>*>(Vec[KNIGHT])))[(*(static_cast<vector<class Piece<QUEEN>*>*>(Vec[KNIGHT]))).size()-ikn]),Vec))
            {
                if(Try<KNIGHT>(iki, iq, ir, ib, ikn-1, ip, ikn, idx, lBoard, Vec)) return true;
            }
            if (iki>0 && !ThreatenPlaced<KING>(lBoard.posx(idx), lBoard.posy(idx), *((*(static_cast<vector<class Piece<KING>*>*>(Vec[KING])))[(*(static_cast<vector<class Piece<KING>*>*>(Vec[KING]))).size()-iki]),Vec))
            {
                if(Try<KING>(iki-1, iq, ir, ib, ikn, ip, iki, idx, lBoard, Vec)) return true;
            }
            if (ip>0 && !ThreatenPlaced<PAWN>(lBoard.posx(idx), lBoard.posy(idx), *((*(static_cast<vector<class Piece<PAWN>*>*>(Vec[PAWN])))[(*(static_cast<vector<class Piece<PAWN>*>*>(Vec[PAWN]))).size()-ip]),Vec))
            {
                if(Try<PAWN>(iki, iq, ir, ib, ikn, ip-1, ip, idx, lBoard, Vec)) return true;
            }
        }
    }
    return false;
}

//making sure that data provided by the user makes any sort of sense
void ProperInput (int& col, int& row, int& iki, int& iq, int& ir, int& ib, int& ikn, int& ip)
{
    while(col<=0)
    {
        cout<<"Please enter a correct number of columns."<<endl;
        cin>>col;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    while(row<=0)
    {
        cout<<"Please enter a correct number of rows."<<endl;
        cin>>row;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    while(iki<0)
    {
        cout<<"Please enter a correct number of king pieces."<<endl;
        cin>>iki;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    while(iq<0)
    {
        cout<<"Please enter a correct number of queen pieces."<<endl;
        cin>>iq;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    while(ir<0)
    {
        cout<<"Please enter a correct number of rook pieces."<<endl;
        cin>>ir;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    while(ib<0)
    {
        cout<<"Please enter a correct number of bishop pieces."<<endl;
        cin>>ib;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    while(ikn<0)
    {
        cout<<"Please enter a correct number of knight pieces."<<endl;
        cin>>ikn;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    while(ip<0)
    {
        cout<<"Please enter a correct number of pawn pieces."<<endl;
        cin>>ip;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}

//preparing the board of threatened tiles with an "impenetrable frame"
void intBoardPrep (int col, int row, LinearVector<int>& lBoard)
{
    lBoard.lvector.resize(row);
    for (int i=0; i<row; i++) lBoard.lvector[i].resize(col); //setting the size of the rectangular board

    for (int i=2; i<row-2; i++)
    {
        for (int j=2; j<col-2; j++) lBoard.lvector[i][j]=0; //setting an unthreatened playable area
    }
    for (int i=0; i<=1; i++) //setting an always threatened frame
    {
        for (int j=0; j<col; j++)
        {
            lBoard.lvector[i][j]=INT_MAX/2;
            lBoard.lvector[row-i-1][j]=INT_MAX/2;
        }
        for (int j=0; j<row; j++)
        {
            lBoard.lvector[j][i]=INT_MAX/2;
            lBoard.lvector[j][col-i-1]=INT_MAX/2;
        }
    }
}

//filling the piece vectors with proper amounts of each of them
void PieceVecFill(int iki, int iq, int ir, int ib, int ikn, int ip, PieceVector& Vec)
{
    if (iki>0)
    {
        (*(static_cast<vector<class Piece<KING>*>*>(Vec[KING]))).push_back(new Piece<KING>);
        for (int i=1; i<iki; i++) (*(static_cast<vector<class Piece<KING>*>*>(Vec[KING]))).push_back(new Piece<KING>(*(*(static_cast<vector<class Piece<KING>*>*>(Vec[KING])))[0]));
    }
    if (iq>0)
    {
        (*(static_cast<vector<class Piece<QUEEN>*>*>(Vec[QUEEN]))).push_back(new Piece<QUEEN>);
        for (int i=1; i<iq; i++) (*(static_cast<vector<class Piece<QUEEN>*>*>(Vec[QUEEN]))).push_back(new Piece<QUEEN>(*(*(static_cast<vector<class Piece<QUEEN>*>*>(Vec[QUEEN])))[0]));
    }
    if (ir>0)
    {
        (*(static_cast<vector<class Piece<ROOK>*>*>(Vec[ROOK]))).push_back(new Piece<ROOK>);
        for (int i=1; i<ir; i++) (*(static_cast<vector<class Piece<ROOK>*>*>(Vec[ROOK]))).push_back(new Piece<ROOK>(*(*(static_cast<vector<class Piece<ROOK>*>*>(Vec[ROOK])))[0]));
    }
    if (ib>0)
    {
        (*(static_cast<vector<class Piece<BISHOP>*>*>(Vec[BISHOP]))).push_back(new Piece<BISHOP>);
        for (int i=1; i<ib; i++) (*(static_cast<vector<class Piece<BISHOP>*>*>(Vec[BISHOP]))).push_back(new Piece<BISHOP>(*(*(static_cast<vector<class Piece<BISHOP>*>*>(Vec[BISHOP])))[0]));
    }
    if (ikn>0)
    {
        (*(static_cast<vector<class Piece<KNIGHT>*>*>(Vec[KNIGHT]))).push_back(new Piece<KNIGHT>);
        for (int i=1; i<ikn; i++) (*(static_cast<vector<class Piece<KNIGHT>*>*>(Vec[KNIGHT]))).push_back(new Piece<KNIGHT>(*(*(static_cast<vector<class Piece<KNIGHT>*>*>(Vec[KNIGHT])))[0]));
    }
    if (ip>0)
    {
        (*(static_cast<vector<class Piece<PAWN>*>*>(Vec[PAWN]))).push_back(new Piece<PAWN>);
        for (int i=1; i<ip; i++) (*(static_cast<vector<class Piece<PAWN>*>*>(Vec[PAWN]))).push_back(new Piece<PAWN>(*(*(static_cast<vector<class Piece<PAWN>*>*>(Vec[PAWN])))[0]));
    }
}

//solving the queens puzzle
void Puzzle()
{
    LinearVector<int> lBoard; //board
    PieceVector Vec; //piece vectors
    int col,row,iki,iq,ir,ib,ikn,ip; //board measurments and amount of pieces

    //data input
    cout<<"Welcome to the extended Queens' Puzzle solver.\nPlease note that the pieces face right-ways.\nPlease enter the board's measurements and amounts of individual chess pieces in a following order:\ncolumns: rows: Kings: Qeens: Rooks: Bishops: Knights: Pawns:"<<endl;
    cin>>col>>row>>iki>>iq>>ir>>ib>>ikn>>ip;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    ProperInput (col, row, iki, iq, ir, ib, ikn, ip);

    //preparing board
    col+=4;
    row+=4;
    intBoardPrep(col, row, lBoard);

    PieceVecFill(iki, iq, ir, ib, ikn, ip, Vec); //preparing piece vectors

    //solving the puzzle using recursion with backtracking
    if (!Solve (iki, iq, ir, ib, ikn, ip, lBoard.lidx(2,2), lBoard, Vec)) cout<<"Lack of solution"<<endl; //no solution has been found for given data
    else
    {

    	//preparing a char table for displaying the solution
        char S[row-4][col-4];

        for (int i=0; i<row-4; i++)
        {
            for (int j=0; j<col-4; j++) S[i][j]='.';
        }
        //placing pieces on char table
        for (int i=0; i<iki; i++) S[(*(static_cast<vector<class Piece<KING>*>*>(Vec[KING])))[i]->ry()-2][(*(static_cast<vector<class Piece<KING>*>*>(Vec[KING])))[i]->rx()-2]='K';
        for (int i=0; i<iq; i++) S[(*(static_cast<vector<class Piece<QUEEN>*>*>(Vec[QUEEN])))[i]->ry()-2][(*(static_cast<vector<class Piece<QUEEN>*>*>(Vec[QUEEN])))[i]->rx()-2]='Q';
        for (int i=0; i<ir; i++) S[(*(static_cast<vector<class Piece<ROOK>*>*>(Vec[ROOK])))[i]->ry()-2][(*(static_cast<vector<class Piece<ROOK>*>*>(Vec[ROOK])))[i]->rx()-2]='R';
        for (int i=0; i<ib; i++) S[(*(static_cast<vector<class Piece<BISHOP>*>*>(Vec[BISHOP])))[i]->ry()-2][(*(static_cast<vector<class Piece<BISHOP>*>*>(Vec[BISHOP])))[i]->rx()-2]='B';
        for (int i=0; i<ikn; i++) S[(*(static_cast<vector<class Piece<KNIGHT>*>*>(Vec[KNIGHT])))[i]->ry()-2][(*(static_cast<vector<class Piece<KNIGHT>*>*>(Vec[KNIGHT])))[i]->rx()-2]='k';
        for (int i=0; i<ip; i++) S[(*(static_cast<vector<class Piece<PAWN>*>*>(Vec[PAWN])))[i]->ry()-2][(*(static_cast<vector<class Piece<PAWN>*>*>(Vec[PAWN])))[i]->rx()-2]='p';
        //displaying the char table
        cout<<"Solution:"<<endl;
        for (int i=0; i<row-4; i++)
        {
            for (int j=0; j<col-4; j++) cout<<S[i][j];
            cout<<endl;
        }
    }
}
