//
//  Move.hpp
//  chessEngine
//
//  Created by Mohamed Lamine CAMARA on 04/01/2026.
//

#ifndef Move_hpp
#define Move_hpp

#include <stdio.h>

#endif /* Move_hpp */
#include "types.h"

class Move {
public:
    
    Move(Square from, Square to, PieceType pieceType);
    
    Move(Square from, Square to, PieceType pieceType, PieceType prom, bool double_push, bool en_passant, bool castling);
    
    Square from;
    Square to;
    PieceType typePiece;
    PieceType promotion;
    bool doublePush;
    bool enPassant;
    bool castling;
};
