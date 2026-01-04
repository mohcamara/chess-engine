# ♟️ High-Performance Chess Engine in C++

A custom-built Chess Engine developed from scratch in C++, focusing on performance and low-level optimizations.

## 🚀 Key Features

*   **Bitboard Architecture**: Uses 64-bit integers (`unsigned long long`) to represent the board, allowing for extremely fast bitwise operations.
*   **Memory Efficiency**: Optimized data structures to minimize cache misses.
*   **Move Validation**: Robust `make_move` and `unmake_move` implementation with full state restoration (history stack).
*   **Clean Codebase**: Organized modular structure separating board representation, move logic, and types.

## 🛠️ Technical Stack

*   **Language**: C++ 17+
*   **Representations**: Bitboards (Little-Endian Rank-File Mapping)
*   **Tools**: Git, Xcode/GCC

## 🏗️ Architecture Overview

### Board Representation
The engine uses **Bitboards** for board representation, which is the industry standard for top-tier engines (like Stockfish). 
- **12 Bitboards**: One for each piece type and color.
- **Occupancy Bitboards**: Accelerated lookout for white, black, and all pieces.
- **State Management**: Tracks Castling rights, En Passant, and Half-move clock using a history stack.

### Move Making
*   **XOR Operations**: Moves are executed using XOR operations for maximum speed.
*   **Zobrist Hashing** (Planned): For fast position comparison.

## 📦 Getting Started

### Prerequisites
*   A C++ Compiler (GCC, Clang, or MSVC)

### Build and Run

```bash
# Clone the repository
git clone https://github.com/your-username/chess-engine.git

# Navigate to source
cd chessEngine

# Compile
g++ main.cpp src/Board.cpp src/Move.cpp -o engine

# Run
./engine
```

## 🗺️ Roadmap

- [x] **Sprint 0**: Architecture Design & Bitboard Implementation
- [x] **Sprint 1**: Board State, Make/Unmake Move Logic
- [ ] **Sprint 2**: Move Generator (Pseudo-legal & Legal moves)
- [ ] **Sprint 3**: Search Algorithm (Minimax & Alpha-Beta Pruning)
- [ ] **Sprint 4**: UCI (Universal Chess Interface) Protocol Support

## 👤 Author

**Mohamed Lamine CAMARA**
*   Project for learning advanced C++ and Game Theory algorithms.
