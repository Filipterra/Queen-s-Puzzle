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

void Puzzle();
template <PieceName pnam> bool ThreatenPlaced (int px, int py, class PieceType<pnam>& plp);
bool Solve(int iki, int iq, int ir, int ib, int ikn, int ip, unsigned int bx, unsigned int by, std::vector <std::vector <int> >& Board);



#endif /* QUEENS_PUZZLE_HPP_ */
