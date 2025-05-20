#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdbool.h>

/**
 * \file board.h
 *
 * \brief This SAE game engine functions.
 *
 * In this file, all the functions for having a game run are defined
 * and documented.
 *
 * \author Dorbec
 *
 */

/**
 * \mainpage SAE 1.1 and 1.2 for IUT Grand Ouest Normandie, computer science department
 * \section description Description of the SAE
 * This SAE is aimed to implement a two player game.
 * The rules of the games are described below.
 *
 * The project is divided into various files. Mostly, the engine of the game,
 * implementing the detailed rules, is provided in the files board.c and board.h
 *
 * \section rules Detailed rules of the game.
 *
 * \subsection general Simple set of rules
 *
 * The game is played by two players that we call here _north_ and _south_.
 * It is played on a board made of _cells_, 
 * initially cells are organized according to a seven columns by eight lines square grid, 
 * but variants will be proposed.
 *
 * Each player has a single piece, his _king_, that is initially placed on the middle cell
 * of the row closest to his side of the board.
 * 
 * Players alternate turns first moving their king to an adjacent cell, 
 * then killing an unoccupied cell from the board.
 * 
 * If the player's king is unable to move (no living cells remain next to his king's cell),
 * the player looses the game.
 *
 * \subsection variations Variations
 *  
 *  Two alternate versions of the game are proposed:
 *    * the first one, the hex variation, is simply played on a board of hexagonal cells
 *      organized along a diamond whose side is made of five cells.
 *    * the second one, the ranged variation, is a version where each king is 
 *    allowed to kill a cell only if he could have reached it within at most 3 moves.
 *  Of course, both variations can be combined into a hex and ranged game.
 *
 * In hexagonal grids, here are the scheme that the column coordinates are defined :
 *
 * @verbatim
     / \ / \ / \
    | 0 | 1 | 2 | 
   / \ / \ / \ / \
  | 0 | 1 | 2 | 3 | 
 / \ / \ / \ / \ / \
| 0 | 1 | 2 | 3 | 4 |   
 \ / \ / \ / \ / \ /
  | 1 | 2 | 3 | 4 |   
   \ / \ / \ / \ /
    | 2 | 3 | 4 |   
     \ / \ / \ / @endverbatim
 *
 */

/**
 * @brief Pointer to the structure that holds the game.
 *
 * Details of the content are not necessary for its use, so the structure is not
 * included here.
 */
typedef struct board_s * board;

/**
 * @brief Game board number of columns.
 *
 * Column indices are given from 0 to NB_COLS - 1.
 */
#define NB_COLS 7

/**
 * @brief Game board number of lines.
 *
 * Line indices are given from 0 to NB_LINES - 1.
 */
#define NB_LINES 8

/**
 * @brief Game board sides for hexagonal boards.
 */
#define HEX_SIDE 5

/**
 * @brief Maximum dimension for all grids.
 *
 * All indices used in any rule set are ensured to be less than ::MAX_DIMENSION - 1
 * Therefore, ::MAX_DIMENSION must be no less than ::NB_COLS, ::NB_LINES and
 * 2 * ::HEX_SIDE - 1
 */
#define MAX_DIMENSION 9

/**
 * @brief number of players in the game.
 */
#define NB_PLAYERS 2

/**
 * @brief number of steps within which the king should be able 
 * to reach the target when using the ranged rule.
 */
#define KING_RANGE 3


/**
 * @brief the different types of cells.
 *
 * This set includes references to a 'none' type, which may be used on empty cells.
 */
enum cell_e {
  EMPTY, /**< no pieces */
  NORTH_KING, /**< _north_'s king*/
  SOUTH_KING, /**< _south_'s king*/
  KILLED, /**< once the cell has been killed */
};

/** simplified name */
typedef enum cell_e cell;

/**
 * @brief return codes for functions when they fail.
 *
 * * OK means the function ran smoothly
 * * ::OUT means coordinates where not on the grid
 * * ::BUSY means some cell that needed to be empty is actually occupied
 * * ::RULES means the move does not respect the rules.
 */
enum return_code {
  OK, /**< things went smoothly */
  OUT, /**< coordinates where not on the board or point to a killed cell */
  BUSY, /**< some cell that needed to be empty is actually occupied */
  RULES, /**< an action that does not respect the rules*/
};

/**
 * @brief the different players for further reference.
 * ::NO_PLAYER is used when informing that a cell is empty.
 */
enum players_e {
  NO_PLAYER, /**< None of the two players*/
  NORTH, /**< the first player, north*/
  SOUTH /**< the second player, south*/
};

/** simplified type name for the player */
typedef enum players_e player;

/**
 * @brief the directions that can be used for moving pieces.
 *
 * On a square grid, the relative positions are :
 * @verbatim
 *  ---------------
 *  | NW | N | NE |
 *  ---------------
 *  |  W | * |  E |
 *  ---------------
 *  | SW | S | SE |
 *  --------------- @endverbatim 

 *  On an hexagonal grid, they are:
 * @verbatim
 *     / \ / \
 *    | NW| NE|
 *   / \ / \ / \
 *  | w | * | E |  
 *   \ / \ / \ /
 *    | SW| SE|
 *     \ / \ / @endverbatim
 *
 **/

enum direction_e {
  SW, /**< towards increasing line numbers and decreasing column number**/
  S, /**< towards increasing line numbers **/
  SE, /**< towards increasing line numbers and increasing column number**/
  W, /**< towards decreasing column numbers **/
  E, /**< towards increasing column numbers **/
  NW, /**< towards decreasing line numbers and decreasing column number**/
  N, /**< towards decreasing line numbers **/
  NE, /**< towards decreasing line numbers and increasing column number**/
};

/** simplified type name for the direction **/
typedef enum direction_e direction;

/**@{
 * @name Game creation/deletion functionalities.
 */

/**
 * @brief Defines a new empty board for starting a game.
 *
 * The first player is always ::NORTH
 * This makes a regular game, that is a game on a square grid with no range rule.
 * @return the newly created board
 */
board new_game();

/**
 * @brief Defines a new empty board for starting a game with special rules.
 *
 * The first player is always ::NORTH
 * This makes a regular game, that is a game on a square grid with no range rule.
 * @param is_hex specifies whether the game should be played on an hexagonal grid
 * @param use_range specifies whether the rule should use the range special rule for killing
 * @return the newly created board
 */
board new_special_game(bool is_hex, bool use_range);

/**
 * @brief Makes a deep copy of the game.
 * @param original_game the game to copy.
 * @return a new copy fully independent of the original game.
 */
board copy_game(board original_game);

/**
 * @brief Delete the game and frees all associated memory.
 * @param game the game to destroy.
 */
void destroy_game(board game);

/**@}*/

/**@{
 * \name Accessing game data functionalities.
 */

/**
 * @brief states whether the game uses a hexagonal board
 *
 * @param game the game to consider
 * @return whether the game uses a hexagonal board.
 */
bool is_hex(board game);

/**
 * @brief states whether the game uses the ranged killing rule.
 *
 * @param game the game to consider
 * @return whether the game uses the ranged killing rule.
 */
bool uses_range(board game);

/**
 * @brief return the player whose turn it is to play.
 *
 * Current player is ::NORTH at the beginning of the game.
 * This function allows to check whose turn it is to play,
 * including during the setting up of the game.
 *
 * @param game the game to consider
 * @return the current player in the game
 */
player current_player(board game);

/**
 * @brief returns the content of the indicated place.
 *
 * If the request is misplaced, this function returns ::KILLED
 *
 * @param game the game from which to collect information
 * @param line the line number
 * @param column the column number
 * @return the player who has a piece on that place
 */
cell get_content(board game, int line, int column);

/**
 * @brief Checks whether the game has a winner already
 *
 * A player wins when his opponent must move but has no neighboring cell available.
 *
 * @param game the game to test.
 * @return the winning player or ::NO_PLAYER if no player is winning.
 */
player get_winner(board game);

/**@}*/

/**@{
 * \name Playing functionalities
 *
 */

/**
 * @brief moves the current player's king one step in the given direction
 *
 * The following ::return_code are used, in this priority order:
 * * ::RULES if the direction required is not a valid direction 
 *    or if the current player has moved already and is supposed to kill a cell
 * * ::OUT if the move would bring the piece out of the board or to a killed cell
 * * ::BUSY if the target cell is occupied by the opponent's king.
 * * ::OK if the move is successful. 
 * 
 * If the move is successful, then the second part of the player's turn starts, 
 * namely he should kill a cell from the board.
 * 
 * @param game the game where to move the piece
 * @param direction the direction where to move the piece
 * @return a return code, ::OK if everything went smoothly
 */
enum return_code move_toward(board game, direction direction); 

/**
 * @brief kills a cell from the board, at the given line and column.
 *
 * The following ::return_code are used, in this priority order:
 * * ::RULES if the current player has to move before removing a cell 
 * * ::OUT if the cell is out of the board or killed already
 * * ::BUSY if the target cell is occupied by some player's king.
 * * ::RULES if the range rule is used and the player's king could no go to the target within three extra moves
 * * ::OK if the removal is successful. 
 *
 * Note that when the range rule is used, there are two different reasons for returning ::RULES, 
 * with different priority order.
 *
 * If the removal is successful, then the turn of the other player starts.
 * 
 * @param game the game where to move the piece
 * @param line the line number of the cell to kill
 * @param column the column number of the cell to kill
 * @return a return code, ::OK if everything went smoothly
 */
enum return_code kill_cell(board game, int line, int column);

/**@}*/
#endif /*_BOARD_H_*/
