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
#include "Chess_pieces.hpp"
#include "Queens_puzzle.hpp"

using namespace std;

vector < class Piece<KING>* >vki;
vector < class Piece<QUEEN>* >vq;
vector < class Piece<ROOK>* >vr;
vector < class Piece<BISHOP>* >vb;
vector < class Piece<KNIGHT>* >vkn;
vector < class Piece<PAWN>* >vp;

template <PieceName pnam>
bool ThreatenPlaced (int px, int py, class PieceType<pnam>& plp)
{
    for (unsigned int i=0; i<vki.size(); i++) if(vki[i]->rx()!=-1 && plp.Threatened(vki[i]->rx(), vki[i]->ry(), px, py)) return true;
    for (unsigned int i=0; i<vq.size(); i++) if(vq[i]->rx()!=-1 && plp.Threatened(vq[i]->rx(), vq[i]->ry(), px, py)) return true;
    for (unsigned int i=0; i<vr.size(); i++) if(vr[i]->rx()!=-1 && plp.Threatened(vr[i]->rx(), vr[i]->ry(), px, py)) return true;
    for (unsigned int i=0; i<vb.size(); i++) if(vb[i]->rx()!=-1 && plp.Threatened(vb[i]->rx(), vb[i]->ry(), px, py)) return true;
    for (unsigned int i=0; i<vkn.size(); i++) if(vkn[i]->rx()!=-1 && plp.Threatened(vkn[i]->rx(), vkn[i]->ry(), px, py)) return true;
    for (unsigned int i=0; i<vp.size(); i++) if(vp[i]->rx()!=-1 && plp.Threatened(vp[i]->rx(), vp[i]->ry(), px, py)) return true;
    return false;
}

bool Solve(int iki, int iq, int ir, int ib, int ikn, int ip, unsigned int bx, unsigned int by, std::vector <std::vector <int> >& Board)
{
    if (iki==0 && iq==0 && ir==0 && ib==0 && ikn==0 && ip==0) return true;

    for (; bx<Board[by].size()-2; bx++)
    {
        if (Board[by][bx]==0)
        {
            if (iq>0 && !ThreatenPlaced<QUEEN>(bx, by, *(vq[vq.size()-iq])->rptypeptr()))
            {
                vq[vq.size()-iq]->Place(bx, by, Board[by].size(), Board.size(), Board);
                if (bx<Board[by].size()-3)
                {
                    if (Solve (iki, iq-1, ir, ib, ikn, ip, bx+1, by, Board)) return true;
                }
                else
                {
                    if (Solve (iki, iq-1, ir, ib, ikn, ip, 2, by+1, Board)) return true;
                }
                vq[vq.size()-iq]->Take(Board[by].size(), Board.size(), Board);
            }
            if (ir>0 && !ThreatenPlaced<ROOK>(bx, by, *(vr[vr.size()-ir])->rptypeptr()))
            {
                vr[vr.size()-ir]->Place(bx, by, Board[by].size(), Board.size(), Board);
                if (bx<Board[by].size()-3)
                {
                    if (Solve (iki, iq, ir-1, ib, ikn, ip, bx+1, by, Board)) return true;
                }
                else
                {
                    if (Solve (iki, iq, ir-1, ib, ikn, ip, 2, by+1, Board)) return true;
                }
                vr[vr.size()-ir]->Take(Board[by].size(), Board.size(), Board);
            }
            if (ib>0 && !ThreatenPlaced<BISHOP>(bx, by, *(vb[vb.size()-ib])->rptypeptr()))
            {
                vb[vb.size()-ib]->Place(bx, by, Board[by].size(), Board.size(), Board);
                if (bx<Board[by].size()-3)
                {
                    if (Solve (iki, iq, ir, ib-1, ikn, ip, bx+1, by, Board)) return true;
                }
                else
                {
                    if (Solve (iki, iq, ir, ib-1, ikn, ip, 2, by+1, Board)) return true;
                }
                vb[vb.size()-ib]->Take(Board[by].size(), Board.size(), Board);
            }
            if (ikn>0 && !ThreatenPlaced<KNIGHT>(bx, by, *(vkn[vkn.size()-ikn])->rptypeptr()))
            {
                vkn[vkn.size()-ikn]->Place(bx, by, Board[by].size(), Board.size(), Board);
                if (bx<Board[by].size()-3)
                {
                    if (Solve (iki, iq, ir, ib, ikn-1, ip, bx+1, by, Board)) return true;
                }
                else
                {
                    if (Solve (iki, iq, ir, ib, ikn-1, ip, 2, by+1, Board)) return true;
                }
                vkn[vkn.size()-ikn]->Take(Board[by].size(), Board.size(), Board);
            }
            if (iki>0 && !ThreatenPlaced<KING>(bx, by, *(vki[vki.size()-iki])->rptypeptr()))
            {
                vki[vki.size()-iki]->Place(bx, by, Board[by].size(), Board.size(), Board);
                if (bx<Board[by].size()-3)
                {
                    if (Solve (iki-1, iq, ir, ib, ikn, ip, bx+1, by, Board)) return true;
                }
                else
                {
                    if (Solve (iki-1, iq, ir, ib, ikn, ip, 2, by+1, Board)) return true;
                }
                vki[vki.size()-iki]->Take(Board[by].size(), Board.size(), Board);
            }
            if (ip>0 && !ThreatenPlaced<PAWN>(bx, by, *(vp[vp.size()-ip])->rptypeptr()))
            {
                vp[vp.size()-ip]->Place(bx, by, Board[by].size(), Board.size(), Board);
                if (bx<Board[by].size()-3)
                {
                    if (Solve (iki, iq, ir, ib, ikn, ip-1, bx+1, by, Board)) return true;
                }
                else
                {
                    if (Solve (iki, iq, ir, ib, ikn, ip-1, 2, by+1, Board)) return true;
                }
                vp[vp.size()-ip]->Take(Board[by].size(), Board.size(), Board);
            }
        }
    }

    for (by++; by<Board.size()-2; by++)
    {
        for (bx=2; bx<Board[by].size()-2; bx++)
        {
            if (Board[by][bx]==0)
            {
                if (iq>0 && !ThreatenPlaced<QUEEN>(bx, by, *(vq[vq.size()-iq])->rptypeptr()))
                {
                    vq[vq.size()-iq]->Place(bx, by, Board[by].size(), Board.size(), Board);
                    if (bx<Board[by].size()-3)
                    {
                        if (Solve (iki, iq-1, ir, ib, ikn, ip, bx+1, by, Board)) return true;
                    }
                    else
                    {
                        if (Solve (iki, iq-1, ir, ib, ikn, ip, 2, by+1, Board)) return true;
                    }
                    vq[vq.size()-iq]->Take(Board[by].size(), Board.size(), Board);
                }
                if (ir>0 && !ThreatenPlaced<ROOK>(bx, by, *(vr[vr.size()-ir])->rptypeptr()))
                {
                    vr[vr.size()-ir]->Place(bx, by, Board[by].size(), Board.size(), Board);
                    if (bx<Board[by].size()-3)
                    {
                        if (Solve (iki, iq, ir-1, ib, ikn, ip, bx+1, by, Board)) return true;
                    }
                    else
                    {
                        if (Solve (iki, iq, ir-1, ib, ikn, ip, 2, by+1, Board)) return true;
                    }
                    vr[vr.size()-ir]->Take(Board[by].size(), Board.size(), Board);
                }
                if (ib>0 && !ThreatenPlaced<BISHOP>(bx, by, *(vb[vb.size()-ib])->rptypeptr()))
                {
                    vb[vb.size()-ib]->Place(bx, by, Board[by].size(), Board.size(), Board);
                    if (bx<Board[by].size()-3)
                    {
                        if (Solve (iki, iq, ir, ib-1, ikn, ip, bx+1, by, Board)) return true;
                    }
                    else
                    {
                        if (Solve (iki, iq, ir, ib-1, ikn, ip, 2, by+1, Board)) return true;
                    }
                    vb[vb.size()-ib]->Take(Board[by].size(), Board.size(), Board);
                }
                if (ikn>0 && !ThreatenPlaced<KNIGHT>(bx, by, *(vkn[vkn.size()-ikn])->rptypeptr()))
                {
                    vkn[vkn.size()-ikn]->Place(bx, by, Board[by].size(), Board.size(), Board);
                    if (bx<Board[by].size()-3)
                    {
                        if (Solve (iki, iq, ir, ib, ikn-1, ip, bx+1, by, Board)) return true;
                    }
                    else
                    {
                        if (Solve (iki, iq, ir, ib, ikn-1, ip, 2, by+1, Board)) return true;
                    }
                    vkn[vkn.size()-ikn]->Take(Board[by].size(), Board.size(), Board);
                }
                if (iki>0 && !ThreatenPlaced<KING>(bx, by, *(vki[vki.size()-iki])->rptypeptr()))
                {
                    vki[vki.size()-iki]->Place(bx, by, Board[by].size(), Board.size(), Board);
                    if (bx<Board[by].size()-3)
                    {
                        if (Solve (iki-1, iq, ir, ib, ikn, ip, bx+1, by, Board)) return true;
                    }
                    else
                    {
                        if (Solve (iki-1, iq, ir, ib, ikn, ip, 2, by+1, Board)) return true;
                    }
                    vki[vki.size()-iki]->Take(Board[by].size(), Board.size(), Board);
                }
                if (ip>0 && !ThreatenPlaced<PAWN>(bx, by, *(vp[vp.size()-ip])->rptypeptr()))
                {
                    vp[vp.size()-ip]->Place(bx, by, Board[by].size(), Board.size(), Board);
                    if (bx<Board[by].size()-3)
                    {
                        if (Solve (iki, iq, ir, ib, ikn, ip-1, bx+1, by, Board)) return true;
                    }
                    else
                    {
                        if (Solve (iki, iq, ir, ib, ikn, ip-1, 2, by+1, Board)) return true;
                    }
                    vp[vp.size()-ip]->Take(Board[by].size(), Board.size(), Board);
                }
            }
        }
    }

    return false;
}

void Puzzle()
{
    int n,m,iki,iq,ir,ib,ikn,ip;
    cout<<"Please enter the Board's measurements and amounts of individual chess pieces in a following order:\ncolumns: rows: Kings: Qeens: Rooks: Bishops: Knights: Pawns:"<<endl;
    cin>>n>>m>>iki>>iq>>ir>>ib>>ikn>>ip;

    n+=4;
    m+=4;
    vector <vector <int> > Board;
    Board.resize(m);
    for (int i=0; i<m; i++) Board[i].resize(n);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++) Board[i][j]=0;
    }
    for (int i=0; i<=1; i++)
    {
        for (int j=0; j<m; j++) Board[i][j]=INT_MAX/2;
        for (int j=0; j<n; j++) Board[j][i]=INT_MAX/2;
    }
    for (int i=n-1; i>=n-2; i--)
    {
        for (int j=0; j<m; j++) Board[i][j]=INT_MAX/2;
        for (int j=0; j<n; j++) Board[j][i]=INT_MAX/2;
    }

    if (iki>0)
    {
        vki.push_back(new Piece<KING>);
        for (int i=1; i<iki; i++) vki.push_back(new Piece<KING>(vki[0]->rptypeptr()));
    }
    if (iq>0)
    {
        vq.push_back(new Piece<QUEEN>);
        for (int i=1; i<iq; i++) vq.push_back(new Piece<QUEEN>(vq[0]->rptypeptr()));
    }
    if (ir>0)
    {
        vr.push_back(new Piece<ROOK>);
        for (int i=1; i<ir; i++) vr.push_back(new Piece<ROOK>(vr[0]->rptypeptr()));
    }
    if (ib>0)
    {
        vb.push_back(new Piece<BISHOP>);
        for (int i=1; i<ib; i++) vb.push_back(new Piece<BISHOP>(vb[0]->rptypeptr()));
    }
    if (ikn>0)
    {
        vkn.push_back(new Piece<KNIGHT>);
        for (int i=1; i<ikn; i++) vkn.push_back(new Piece<KNIGHT>(vkn[0]->rptypeptr()));
    }
    if (ip>0)
    {
        vp.push_back(new Piece<PAWN>);
        for (int i=1; i<ip; i++) vp.push_back(new Piece<PAWN>(vp[0]->rptypeptr()));
    }

    /*
    for (int i=2; i<m-2; i++)
    {
    	for (int j=2; j<n-2; j++) cout<<Board[i][j];
    	cout<<endl;
    }
	*/
    //cout<<vki[0]->rptypeptr().use_count()<<" "<<vq[0]->rptypeptr().use_count()<<" "<<vr[0]->rptypeptr().use_count()<<" "<<vb[0]->rptypeptr().use_count()<<" "<<vkn[0]->rptypeptr().use_count()<<" "<<vp[0]->rptypeptr().use_count()<<" ";


    if (!Solve (iki, iq, ir, ib, ikn, ip, 2, 2, Board)) cout<<"Lack of solution"<<endl;
    else
    {
    	/*
    	cout<<endl;
        for (int i=2; i<m-2; i++)
        {
        	for (int j=2; j<n-2; j++) cout<<Board[i][j];
        	cout<<endl;
        }
        cout<<endl;
		*/

    	char S[m-4][n-4];
    	for (int i=0; i<m-4; i++)
        {
     		for (int j=0; j<n-4; j++) S[i][j]='X';
       	}
    	for (int i=0; i<iki; i++) S[vki[i]->ry()-2][vki[i]->rx()-2]='K';
    	for (int i=0; i<iq; i++) S[vq[i]->ry()-2][vq[i]->rx()-2]='Q';
    	for (int i=0; i<ir; i++) S[vr[i]->ry()-2][vr[i]->rx()-2]='R';
    	for (int i=0; i<ib; i++) S[vb[i]->ry()-2][vb[i]->rx()-2]='B';
    	for (int i=0; i<ikn; i++) S[vkn[i]->ry()-2][vkn[i]->rx()-2]='k';
    	for (int i=0; i<ip; i++) S[vp[i]->ry()-2][vp[i]->rx()-2]='p';

    	cout<<"Solution:"<<endl;
    	for (int i=0; i<m-4; i++)
    	{
    		for (int j=0; j<n-4; j++) cout<<S[i][j];
    		cout<<endl;
    	}
    }

    for (int i=0; i<iki; i++) delete vki[i];
    for (int i=0; i<iq; i++) delete vq[i];
    for (int i=0; i<ir; i++) delete vr[i];
    for (int i=0; i<ib; i++) delete vb[i];
    for (int i=0; i<ikn; i++) delete vkn[i];
    for (int i=0; i<ip; i++) delete vp[i];
    vki.clear();
    vq.clear();
    vr.clear();
    vb.clear();
    vkn.clear();
    vp.clear();
}
