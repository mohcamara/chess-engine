//
//  Move.cpp
//  chessEngine
//
//  Created by Mohamed Lamine CAMARA on 04/01/2026.
//

#include "Move.hpp"
#include <iostream>

using namespace std;

Move::Move(Square source, Square destination, PieceType piece) {
    from = source;
    to = destination;
    typePiece = piece;
    promotion = PieceType::NONE;
    doublePush = false;
    enPassant = false;
    castling = false;
}

Move::Move(Square source, Square destination, PieceType piece, PieceType prom, bool double_push, bool en_passant, bool is_castling) {
    from = source;
    to = destination;
    typePiece = piece;
    promotion = prom;
    doublePush = double_push;
    enPassant = en_passant;
    castling = is_castling;
}
