//
//  main.cpp
//  chessEngine
//
//  Created by Mohamed Lamine CAMARA on 19/10/2025.
//

#include "src/Board.hpp"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[]) {
    Board board;

    cout << "Avant deplacement " << endl;
    board.print_board();
    
    Move move(E2, E4, PAWN);
    
    Move move2(E7, E5, PAWN);
    
    board.make_move(move);
    board.make_move(move2);
    
    cout << "Apres deplacement " << endl;
    board.print_board();
    
    board.unmake_move(move2);
    
    cout << "Annulation du dernier coup" << endl;
    board.print_board();
    
  return 0;
}
