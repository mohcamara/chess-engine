//
//  Board.hpp
//  chessEngine
//
//  Created by Mohamed Lamine CAMARA on 19/10/2025.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>

#endif /* Board_hpp */

#include "types.h"

class Board {
public:
    Board();
    void print_board();
    
private:
    // Tableau des 12 bitboards (6 types de pièce, 2 couleurs)
    // ex: bitboards[Color::WHITE][PieceType::PAWN]
    Bitboard bitboards[2][6];
    
    // Bitboards d'occupation (toutes les pièces blanches, toutes les noires)
    Bitboard occupancy[2];
    
    // Etat du jeu
    Color side_to_move;
    int castling_rights;
    Square en_passant_square;
    int halfmove_clock;
};

