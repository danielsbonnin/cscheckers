/*checkers.h*/
/**
 * Dumb Checkers is an implementation of the game of checkers with an
 * adjustable AI. TODO
 * 
 * The checkers board is represented by a linked list of struct Square
 * objects that identify their respective neighbors via pointers.
 *
 * The checkers on the board are represented by struct Checker objects
 * which exist as the tenant member of struct Square. 
 *
 * The Dumb Checkers API is used thusly for each move: 1)call
 * availableMoves() to get an array of all available moves.
 * (note: if any piece can capture, then all non-capture moves are 
 * ignored)
 * (note 2: if any capture move contains multiple capture paths, each
 * path is recorded as a unique move, however, for human interaction, 
 * jump path decisions are requested in a while loop [more on this later]).
 * 2)The appropriate move is selected from the list of available moves.
 *
 **/

#ifndef CHECKERS_H
#define CHECKERS_H

enum captureDirections {TLEFT = 1, TRIGHT = 2, BLEFT = 4, BRIGHT = 8};

struct Checker{
	int isWhite;
	int isKing;
};

struct Square {
	struct Square *tl; //adjacent square to the top left
	struct Square *tr; //adjacent square to the top right
	struct Square *bl; //adjacent square to the bottom left
	struct Square *br; //adjacent square to the bottom right
	struct Checker *tenant; //Checker occupying square or NULL
};

struct CheckersGame {
	struct Square board[32];
	int dead;
	int white;
	int black;
	int whiteTurn;
	struct Checker set[24];
};



/**
 * Set up board squares as a linked list
 */
void initCheckersBoard(struct CheckersGame *game);

/**
 * Initialize 24 checkers and assign checkers to squares on
 * initialized board.
 * Set up checkers on board squares
 *
 * @post 	game.board first 12 elements.tenant.isWhite == 1
 * 			and last 12 elements.tenant.iswhite == 0.
 * 			game.board[12] : game.board[23].tenant == NULL;
 *
 * 	@post	game.dead == 0
 * 	@post	game.white == 12
 * 	@post	game.black == 12
 * 	@post 	game.set first 12 elements.isWhite == 1;
 * 			game.set last 12 elements.isWhite == 0;
 * 	@post 	game.set all elements.isKing == 0;
 */
void initCheckersGame(struct CheckersGame *game);

/**
 * @return 1 if proposed move is legal, 0 otherwise.
 */
int isLegalMove(struct CheckersGame *game, struct Square *curSquare, struct Square *destination);

/**
 * @return enum captureDirections bitwise OR of all capture directions available.
 */
int canCapture(struct CheckersGame *game, struct Square *curSquare, int isWhite, int isKing, struct Square *origin);

/**
 * @return 1 if curSquare contains a tenant that can move. Otherwise return 0.
 * @pre curSquare.tenant is not NULL.
 */
int canMove(struct CheckersGame *game, struct Square *curSquare);

/**
 *
 * @pre: curSquare->tenant->isKing == 0
 * @post: curSquare->tenant->isKing == 1
 */
void kingMe(struct CheckersGame *game, struct Square *curSquare);

/**
 * Move checker to adjacent square.
 *
 * @pre curSquare not NULL, correct color or king for move direction.
 * @pre destination is NULL
 *
 * @post destination not NULL, curSquare is NULL
 */
void move(struct CheckersGame *game, struct Square *curSquare, struct Square *destination);

/**
 * Capture adjacent opponent and take multiple jumps
 *
 * @pre curSquare is not NULL, correct color or king for move direction
 * @pre destination is NULL
 * @pre There is an adjacent piece of opposite color in the same direction
 * 		as destination.
 * @post captured opponent square is NULL
 * @post white/black is decremented. dead is incremented.
 * @post if multiple jumps are possible, they are taken.
 */
//void capture(struct CheckersGame *game, struct Square *curSquare, struct Square *toCapture);

/**
 * A single capture with no checking for subsequent moves.
 *
 * @return the Square the capturing piece lands on after jumping opponent piece.
 */
struct Square * singleCapture(struct CheckersGame *game, struct Square *curSquare, struct Square *toCapture);


#endif
