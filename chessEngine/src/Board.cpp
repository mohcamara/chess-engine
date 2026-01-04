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
  for (int c = 0; c < 2; ++c) {
    for (int p = 0; p < 6; ++p) {
      bitboards[c][p] = 0ULL;
    }

    occupancy[c] = 0ULL;
  }

  // Les pions blancs sur la 2e rangée
  bitboards[(int)Color::WHITE][(int)PieceType::PAWN] = 0b11111111ULL << 8;

  // Les tours blanches
  bitboards[(int)Color::WHITE][(int)PieceType::ROOK] =
      (1ULL << A1) | (1ULL << H1);

  // Les cavaliers blancs
  bitboards[(int)Color::WHITE][(int)PieceType::KNIGHT] =
      (1ULL << B1) | (1ULL << G1);

  // Les fous blancs
  bitboards[(int)Color::WHITE][(int)PieceType::BISHOP] =
      (1ULL << C1) | (1ULL << F1);

  // La dame blanche
  bitboards[(int)Color::WHITE][(int)PieceType::QUEEN] = 1ULL << D1;

  // Le roi blanc
  bitboards[(int)Color::WHITE][(int)PieceType::KING] = (1ULL << E1);

  // Les pions noirs sur la 7e rangée
  bitboards[(int)Color::BLACK][(int)PieceType::PAWN] = 0b11111111ULL << 48;

  // Les tours noires
  bitboards[(int)Color::BLACK][(int)PieceType::ROOK] =
      (1ULL << A8) | (1ULL << H8);

  // Les cavaliers noirs
  bitboards[(int)Color::BLACK][(int)PieceType::KNIGHT] =
      (1ULL << B8) | (1ULL << G8);

  // Les fous noirs
  bitboards[(int)Color::BLACK][(int)PieceType::BISHOP] =
      (1ULL << C8) | (1ULL << F8);

  // La dame noire
  bitboards[(int)Color::BLACK][(int)PieceType::QUEEN] = 1ULL << D8;

  // Le roi noir
  bitboards[(int)Color::BLACK][(int)PieceType::KING] = (1ULL << E8);

  // Les bitboards d'occupation

  occupancy[(int)Color::WHITE] =
      bitboards[(int)Color::WHITE][(int)PieceType::PAWN] |
      bitboards[(int)Color::WHITE][(int)PieceType::ROOK] |
      bitboards[(int)Color::WHITE][(int)PieceType::KNIGHT] |
      bitboards[(int)Color::WHITE][(int)PieceType::BISHOP] |
      bitboards[(int)Color::WHITE][(int)PieceType::QUEEN] |
      bitboards[(int)Color::WHITE][(int)PieceType::KING];

  occupancy[(int)Color::BLACK] =
      bitboards[(int)Color::BLACK][(int)PieceType::PAWN] |
      bitboards[(int)Color::BLACK][(int)PieceType::ROOK] |
      bitboards[(int)Color::BLACK][(int)PieceType::KNIGHT] |
      bitboards[(int)Color::BLACK][(int)PieceType::BISHOP] |
      bitboards[(int)Color::BLACK][(int)PieceType::QUEEN] |
      bitboards[(int)Color::BLACK][(int)PieceType::KING];

  side_to_move = Color::WHITE;
  castling_rights = 0b1111;
  en_passant_square = Square::NO_SQUARE;
  halfmove_clock = 0;
}

void Board::print_board() {
  for (int rank = 7; rank >= 0; --rank) {
    for (int file = 0; file < 8; ++file) {

      Square square = (Square)(rank * 8 + file);

      char piece = '.';

      if (bitboards[(int)Color::WHITE][(int)PieceType::PAWN] & (1ULL << square))
        piece = 'P';
      else if (bitboards[(int)Color::BLACK][(int)PieceType::PAWN] &
               (1ULL << square))
        piece = 'p';
      else if (bitboards[(int)Color::WHITE][(int)PieceType::ROOK] &
               (1ULL << square))
        piece = 'R';
      else if (bitboards[(int)Color::BLACK][(int)PieceType::ROOK] &
               (1ULL << square))
        piece = 'r';
      else if (bitboards[(int)Color::WHITE][(int)PieceType::KNIGHT] &
               (1ULL << square))
        piece = 'N';
      else if (bitboards[(int)Color::BLACK][(int)PieceType::KNIGHT] &
               (1ULL << square))
        piece = 'n';
      else if (bitboards[(int)Color::WHITE][(int)PieceType::BISHOP] &
               (1ULL << square))
        piece = 'B';
      else if (bitboards[(int)Color::BLACK][(int)PieceType::BISHOP] &
               (1ULL << square))
        piece = 'b';
      else if (bitboards[(int)Color::WHITE][(int)PieceType::QUEEN] &
               (1ULL << square))
        piece = 'Q';
      else if (bitboards[(int)Color::BLACK][(int)PieceType::QUEEN] &
               (1ULL << square))
        piece = 'q';
      else if (bitboards[(int)Color::WHITE][(int)PieceType::KING] &
               (1ULL << square))
        piece = 'K';
      else if (bitboards[(int)Color::BLACK][(int)PieceType::KING] &
               (1ULL << square))
        piece = 'k';

      cout << piece;
    }
    cout << endl;
  }
}

void Board::make_move(Move move) {
  // Sauvegarde de l'état
  GameState state;
  state.castling_rights = castling_rights;
  state.en_passant_square = en_passant_square;
  state.halfmove_clock = halfmove_clock;
  state.captured_piece = PieceType::NONE;

  Color enemy = (side_to_move == Color::WHITE) ? Color::BLACK : Color::WHITE;
  for (int piece = PAWN; piece <= KING; ++piece) {
    if (bitboards[(int)enemy][piece] & (1ULL << move.to)) {
      state.captured_piece = (PieceType)piece;
      // On supprime l'ennemi tout de suite
      bitboards[(int)enemy][piece] &= ~(1ULL << move.to);
      break;
    }
  }
  history.push_back(state);

  // 1. On récupère notre bitboard
  Bitboard &my_pieces = bitboards[(int)side_to_move][move.typePiece];

  // 2. On éteint le départ et on allume l'arrivée
  my_pieces ^= (1ULL << move.from) | (1ULL << move.to);

  // On parcourt les 6 types de pièces ennemis
  for (int piece = PAWN; piece <= KING; ++piece) {
    if (bitboards[(int)enemy][piece] & (1ULL << move.to)) {
      // Ennemi trouvé ! On le supprime (XOR ou décalage inverse)
      bitboards[(int)enemy][piece] ^= (1ULL << move.to);
      break; // Une seule pièce par case, on peut arrêter
    }
  }

  occupancy[(int)Color::WHITE] =
      bitboards[(int)Color::WHITE][(int)PieceType::PAWN] |
      bitboards[(int)Color::WHITE][(int)PieceType::ROOK] |
      bitboards[(int)Color::WHITE][(int)PieceType::KNIGHT] |
      bitboards[(int)Color::WHITE][(int)PieceType::BISHOP] |
      bitboards[(int)Color::WHITE][(int)PieceType::QUEEN] |
      bitboards[(int)Color::WHITE][(int)PieceType::KING];

  occupancy[(int)Color::BLACK] =
      bitboards[(int)Color::BLACK][(int)PieceType::PAWN] |
      bitboards[(int)Color::BLACK][(int)PieceType::ROOK] |
      bitboards[(int)Color::BLACK][(int)PieceType::KNIGHT] |
      bitboards[(int)Color::BLACK][(int)PieceType::BISHOP] |
      bitboards[(int)Color::BLACK][(int)PieceType::QUEEN] |
      bitboards[(int)Color::BLACK][(int)PieceType::KING];

  side_to_move = (side_to_move == Color::WHITE) ? Color::BLACK : Color::WHITE;
}

void Board::unmake_move(Move move){
    side_to_move = (side_to_move == Color::WHITE) ? Color::BLACK : Color::WHITE;
    
    Bitboard& my_pieces = bitboards[(int)side_to_move][move.typePiece];
    my_pieces &= ~(1ULL << move.to);   // Enlever de l'arrivée
    my_pieces |= (1ULL << move.from);  // Remettre au départ
    
    GameState state = history.back();
    history.pop_back();
    
    castling_rights = state.castling_rights;
    en_passant_square = state.en_passant_square;
    halfmove_clock = state.halfmove_clock;
    
    if(state.captured_piece != NONE) {
        Color enemy = (side_to_move == Color::WHITE) ? Color::BLACK : Color::WHITE;
        bitboards[(int) enemy][state.captured_piece] |= (1ULL << move.to);
    }
    
    occupancy[(int)Color::WHITE] =
        bitboards[(int)Color::WHITE][(int)PieceType::PAWN] |
        bitboards[(int)Color::WHITE][(int)PieceType::ROOK] |
        bitboards[(int)Color::WHITE][(int)PieceType::KNIGHT] |
        bitboards[(int)Color::WHITE][(int)PieceType::BISHOP] |
        bitboards[(int)Color::WHITE][(int)PieceType::QUEEN] |
        bitboards[(int)Color::WHITE][(int)PieceType::KING];

    occupancy[(int)Color::BLACK] =
        bitboards[(int)Color::BLACK][(int)PieceType::PAWN] |
        bitboards[(int)Color::BLACK][(int)PieceType::ROOK] |
        bitboards[(int)Color::BLACK][(int)PieceType::KNIGHT] |
        bitboards[(int)Color::BLACK][(int)PieceType::BISHOP] |
        bitboards[(int)Color::BLACK][(int)PieceType::QUEEN] |
        bitboards[(int)Color::BLACK][(int)PieceType::KING];
}
