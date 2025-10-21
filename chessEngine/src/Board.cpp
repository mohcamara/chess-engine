//
//  Board.cpp
//  chessEngine
//
//  Created by Mohamed Lamine CAMARA on 19/10/2025.
//

#include "Board.hpp"
#include <iostream>

using namespace std;

Board::Board() {
    for(int c = 0; c < 2; ++c) {
        for(int p = 0; p < 6; ++p) {
            bitboards[c][p] =  0ULL;
        }
        
        occupancy[c] = 0ULL;
    }
    
    // Les pions blancs sur la 2e rangée
    bitboards[(int) Color::WHITE][(int)PieceType::PAWN] = 0b11111111ULL << 8;
    
    // Les tours blanches
    bitboards[(int) Color::WHITE][(int)PieceType::ROOK] = (1ULL << A1) | (1ULL << H1);
    
    // Les cavaliers blancs
    bitboards[(int) Color::WHITE][(int)PieceType::KNIGHT] = (1ULL << B1) | (1ULL << G1);
    
    // Les fous blancs
    bitboards[(int) Color::WHITE][(int)PieceType::BISHOP] = (1ULL << C1) | (1ULL << F1);
    
    // La dame blanche
    bitboards[(int) Color::WHITE][(int)PieceType::QUEEN] = 1ULL << D1;
    
    // Le roi blanc
    bitboards[(int) Color::WHITE][(int)PieceType::KING] = (1ULL << E1);
    
    //Les pions noirs sur la 7e rangée
    bitboards[(int) Color::BLACK][(int)PieceType::PAWN] = 0b11111111ULL << 48;
    
    // Les tours noires
    bitboards[(int) Color::BLACK][(int)PieceType::ROOK] = (1ULL << A8) | (1ULL << H8);
    
    // Les cavaliers noirs
    bitboards[(int) Color::BLACK][(int)PieceType::KNIGHT] = (1ULL << B8) | (1ULL << G8);
    
    // Les fous noirs
    bitboards[(int) Color::BLACK][(int)PieceType::BISHOP] = (1ULL << C8) | (1ULL << F8);
    
    // La dame noire
    bitboards[(int) Color::BLACK][(int)PieceType::QUEEN] = 1ULL << D8;
    
    // Le roi noir
    bitboards[(int) Color::BLACK][(int)PieceType::KING] = (1ULL << E8);
    
    
    // Les bitboards d'occupation
    
    occupancy[(int)Color::WHITE] =  bitboards[(int) Color::WHITE][(int)PieceType::PAWN] |
                                    bitboards[(int) Color::WHITE][(int)PieceType::ROOK] |
                                    bitboards[(int) Color::WHITE][(int)PieceType::KNIGHT] |
                                    bitboards[(int) Color::WHITE][(int)PieceType::BISHOP] |
                                    bitboards[(int) Color::WHITE][(int)PieceType::QUEEN] |
                                    bitboards[(int) Color::WHITE][(int)PieceType::KING];
    
    occupancy[(int)Color::BLACK] =  bitboards[(int) Color::BLACK][(int)PieceType::PAWN] |
                                    bitboards[(int) Color::BLACK][(int)PieceType::ROOK] |
                                    bitboards[(int) Color::BLACK][(int)PieceType::KNIGHT] |
                                    bitboards[(int) Color::BLACK][(int)PieceType::BISHOP] |
                                    bitboards[(int) Color::BLACK][(int)PieceType::QUEEN] |
                                    bitboards[(int) Color::BLACK][(int)PieceType::KING];
    
    side_to_move = Color::WHITE;
    castling_rights = 0b1111;
    en_passant_square = Square::NO_SQUARE;
    halfmove_clock = 0;
}

void Board::print_board() {
    for(int rank = 7; rank >= 0; --rank) {
        for(int file = 0; file < 8; ++file) {
            
            Square square = (Square)(rank * 8 + file);
            
            char piece = '.';
            
            if(bitboards[(int)Color::WHITE][(int)PieceType::PAWN] & (1ULL << square)) piece = 'P';
            else if(bitboards[(int)Color::BLACK][(int)PieceType::PAWN] & (1ULL << square)) piece = 'p';
            else if(bitboards[(int)Color::WHITE][(int)PieceType::ROOK] & (1ULL << square)) piece = 'R';
            else if(bitboards[(int)Color::BLACK][(int)PieceType::ROOK] & (1ULL << square)) piece = 'r';
            else if(bitboards[(int)Color::WHITE][(int)PieceType::KNIGHT] & (1ULL << square)) piece = 'N';
            else if(bitboards[(int)Color::BLACK][(int)PieceType::KNIGHT] & (1ULL << square)) piece = 'n';
            else if(bitboards[(int)Color::WHITE][(int)PieceType::BISHOP] & (1ULL << square)) piece = 'B';
            else if(bitboards[(int)Color::BLACK][(int)PieceType::BISHOP] & (1ULL << square)) piece = 'b';
            else if(bitboards[(int)Color::WHITE][(int)PieceType::QUEEN] & (1ULL << square)) piece = 'Q';
            else if(bitboards[(int)Color::BLACK][(int)PieceType::QUEEN] & (1ULL << square)) piece = 'q';
            else if(bitboards[(int)Color::WHITE][(int)PieceType::KING] & (1ULL << square)) piece = 'K';
            else if(bitboards[(int)Color::BLACK][(int)PieceType::KING] & (1ULL << square)) piece = 'k';
            
            cout << piece;
        }
        cout << endl;
    }
}
