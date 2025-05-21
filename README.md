# Battleship

**Author:** Andrea Alfano (alfanowski)  
**Language:** C++  
**Platform:** Windows Console  

---

## Overview

**Battleship** is a single-player console game inspired by the classic naval strategy game. The player must locate and destroy enemy ships placed randomly on a 20×20 grid using coordinate-based attacks.

---

## Gameplay

- Grid size: 20×20 (rows `0–19`, columns `A–T`)
- Ships:
  - 3 large ships (size selected by the player, max 5)
  - 3 small ships (1 cell)
- Input format: e.g., `13F`
- Goal: destroy all ship cells in the fewest possible moves

---

## Features

- ANSI-colored grid display (compatible terminals only)
- Intro animation and progress indicators
- Randomized ship placement with adjacency constraints
- Replay support with best score tracking

---

## Controls

- Input coordinate (row number + column letter)
- Case-insensitive
- Example: `7C`, `14T`

---

## Notes

- Windows-only (uses `system("cls")`)
- Debug view available by enabling `bool debug = 1`
- No external libraries required
