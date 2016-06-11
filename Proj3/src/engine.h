/** @file
    Interface of game engine.
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>

#define null NULL
#define OK 0
#define INIT_ERROR 1
#define MOVE_ERROR 2
#define PRODUCE_ERROR 3
#define PLAYER_1_WINS 10
#define PLAYER_2_WINS 11
#define TURN_LIMIT 12
#define DRAW 13
#define END_BEFORE_INIT 20

/*---------------------------------------------------------------------------*/
//DATA STRUCTURES
/*---------------------------------------------------------------------------*/

/** Enum for unit types.
 */
typedef enum {PEASANT, KING, KNIGHT} unit_type;

/** Enum for players.
 */
typedef enum {PLAYER_1, PLAYER_2} player_type;

/** Structure of a unit.
 Returns unit with unit type, owner and last move information
 */
typedef struct def_unit {
    unit_type type; /**< Type of unit. */
    player_type owner; /**< Owner of unit. */
    int last_move; /**< When was the last move (int turns). */
    int x; /**< Column number. */
    int y; /**< Row number. */
} unit;

/** Typedef for a unit pointer.
 */
typedef unit* unit_ptr;

/** Typedef for a unit pointer.
 */
typedef struct def_unit_list_elem unit_list_elem;

/** Typedef for a unit list element pointer.
 */
typedef unit_list_elem* unit_list_elem_ptr;

/** Structure of a unit list element.
 Returns a unit list element that holds a unit and a pointer to the next element.
 */
struct def_unit_list_elem {
    unit_ptr unit; /**< A pointer to a unit. */
    unit_list_elem_ptr next; /**< A pointer to the next element of the list. */
};

/** Structure of a board.
 Returns board with size, info if initialised and two lists of units
 */
typedef struct def_board {
    int size; /**< Size of the board. */
    unit_list_elem_ptr player_1_list; /**< A list of units for player 1. */
    unit_list_elem_ptr player_2_list; /**< A list of units for player 2. */
    bool init; /**< Boolean informing if the board has been initialised. */
} game_board;

/** Structure of a player.
 Returns player holding turn limit information, a pointer to the king and if initialised
 */
typedef struct def_player {
    bool init; /**< Boolean informing whether the player has been initialised. */
    int turn_limit; /**< Integer corresponding to the turn limit. */
    unit_ptr king; /**< Pointer to the player's king unit. */
} player;

/*---------------------------------------------------------------------------*/
//HEADER GLOBAL VARIABLES
/*---------------------------------------------------------------------------*/
/**
 * Global variables for player 1, player 2 and for the ai (us)
 */
player player_1, player_2, us;
/**
 * Global variable for the one and only game board
 */
game_board board;
/**
 * Integer holding the current turn number
 */
int cur_turn;
/**
 * Boolean saying if its player 1's turn or not
 */
bool player_1_turn;

/*---------------------------------------------------------------------------*/
//FUNCTIONS AND METHODS
/*---------------------------------------------------------------------------*/
/**
 Initializes a game. Needed before first INIT.
 */
void start_game();

/**
 Frees memory. Needed after finishing game.
 */
void end_game();

/**
 Checks if initialisation arguments are correct.
 * @param[in] n Size of board.
 * @param[in] k number of turns per player.
 * @param[in] x1 Column number of p1's king.
 * @param[in] y1 Row number of p1's king.
 * @param[in] x2 Column number of p2's king.
 * @param[in] y2 Row number of p2's king.
 * @return bool.
 */
bool check_init(int n, int k, int x1, int y1, int x2, int y2);

/**
 Prints (to stdout) the given unit.
 * @param[in] u_ptr Pointer to unit.
 * @return void.
 */
void print_unit(unit_ptr u_ptr);

/**
 Checks if cell[x1, y1] on board is empty.
 * @param[in] x1 Column number to check.
 * @param[in] y1 Row number to check.
 * @return bool True if is empty, false otherwise.
 */
bool is_empty(int x1, int y1);

/**
 Erases unit from given cell.
 * @param[in] u_ptr Pointer to unit to be erased.
 * @return void.
 */
void erase_unit(unit_ptr u_ptr);

/**
 Gives unit that occupies given coordinates.
 * @param[in] x1 Column number of unit.
 * @param[in] y1 Row number of unit.
 * @return unit_ptr Pointer to unit.
 */
unit_ptr get_unit(int x1, int y1);

/**
 Initializes a game with size of a board, number of rounds and positions of kings.
 * @param[in] n Size of board.
 * @param[in] k number of turns per player.
 * @param[in] p player.
 * @param[in] x1 Column number of p1's king.
 * @param[in] x2 Row number of p1's king.
 * @param[in] y1 Column number of p2's king.
 * @param[in] y2 Row number of p2's king.
 * @return 0.
 */
int init(int n, int k, int p, int x1, int y1, int x2, int y2);

/**
 Creates a game board.
 * @param[in] n Size of board.
 * @param[in] x1 Column number of p1's king.
 * @param[in] y1 Row number of p1's king.
 * @param[in] x2 Column number of p2's king.
 * @param[in] y2 Row number of p2's king.
 * @return void.
 */
void allocate_board(int n, int x1, int y1, int x2, int y2);

/**
 Checks if move destination is adjacent to move beginning.
 * @param[in] x1 Column number before a move.
 * @param[in] y1 Row number before a move.
 * @param[in] x2 Column number after a move.
 * @param[in] y2 Row number before a move.
 * @return bool.
 */
bool not_adjacent(int x1, int y1, int x2, int y2);

/**
 Checks if player can move.
 * @param[in] x1 Column number of unit to be moved.
 * @param[in] y1 Row number of unit to be moved.
 * @param[in] x2 Column number of destination.
 * @param[in] y2 Row number of destination.
 * @return bool.
 */
bool can_move(int x1, int y1, int x2, int y2);

/**
 Makes a move.
 * @param[in] x1 Column number before a move.
 * @param[in] y1 Row number before a move.
 * @param[in] x2 Column number after a move.
 * @param[in] y2 Row number before a move.
 * @return 0.
 */
int move(int x1, int y1, int x2, int y2);

/**
 Checks if player can produce.
 * @param[in] x1 Column number of unit to produce.
 * @param[in] y1 Row number of unit to produce.
 * @param[in] x2 Column number of production output.
 * @param[in] y2 Row number of production output.
 * @return bool.
 */
bool can_produce(int x1, int y1, int x2, int y2);

/**
 Produces a unit.
 * @param[in] x1 Column number for unit.
 * @param[in] y1 Row number for unit.
 * @param[in] p_type Player ownership of unit.
 * @param[in] u_type Unit type.
 * @return void.
 */
void produce_unit(int x1, int y1, player_type p_type, unit_type u_type);

/**
 Produces a knight.
 * @param[in] x1 Column number of peasant.
 * @param[in] y1 Row number of peasant.
 * @param[in] x2 Column number for production output.
 * @param[in] y2 Row number for production output.
 * @return 0.
 */
int produce_knight(int x1, int y1, int x2, int y2);

/**
 Produces a peasant.
 * @param[in] x1 Column number of peasant.
 * @param[in] y1 Row number of peasant.
 * @param[in] x2 Column number for production output.
 * @param[in] y2 Row number for production output.
 * @return 0.
 */
int produce_peasant(int x1, int y1, int x2, int y2);

/**
 Ends a turn
 */
int end_turn();

/**
 Prints (into stdout) top-left corner of the board of size m x m where m = min(n,10).
 */
void print_topleft();

/**
 Checks if victory conditions for any player have been met.
 */
int check_if_end();

#endif /* ENGINE_H */
