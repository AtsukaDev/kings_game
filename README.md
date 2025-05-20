Here is a project made during my first year in IT studies, enjoy.

# 👑 Kings Game

**Kings Game** is a 2-player strategy game written in C, where the goal is to outmaneuver your opponent and trap their king. The game is played in turns and involves strategic movement and destruction of tiles on the board.

## 🎮 How to Play

### 🛠️ 1. Download & Compile

Download the `game.c` file and compile it using `gcc`. Open your terminal and run:

```bash
gcc -Wall game.c
```

Then, start the game by typing:

```bash
./a.out
```

> Make sure you have GCC installed on your system.

---

### 👤 2. Game Start

- The game is played by **two players**, taking turns.
- Each player enters their **nickname** at the beginning, which will be displayed during gameplay.

---

### 🎯 3. Goal of the Game

Trap your opponent’s king by strategically **breaking boxes**.  
The first player to **block the opponent's king completely** wins the game!

---

### 🎲 4. Gameplay Mechanics

- Players alternate turns.
- On your turn:
  1. Move your king to one of the **8 adjacent tiles** (visible movement options are shown).
  2. Break a box anywhere on the board to **trap** your opponent.

- The game continues until one player's king **can no longer move**.

---

### 🔁 5. Moves and Breakages

- Kings can move to any of the **8 surrounding tiles**, as long as:
  - The tile is within the board.
  - The tile is not broken.
  - The other king is not on that tile.

- When breaking a box (in standard mode):
  - You can break **any tile** that:
    - Is not already broken.
    - Does not contain a king.

---

### 🎮 6. Game Modes

You can play in **3 different modes**:

1. **Standard Mode**  
   - Move your king.
   - Break any tile not occupied or already broken.

2. **Range Mode**  
   - Adds challenge by **restricting you from breaking boxes within 3 tiles** of your king.

3. **Hexagonal Board Mode**  
   - Changes the board layout to a **hexagonal grid** for a new level of strategic depth.

You can even **combine both special modes** for the ultimate challenge!

---

Enjoy the game and may the best strategist win!
