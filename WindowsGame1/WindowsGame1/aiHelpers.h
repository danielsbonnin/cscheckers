/*
 * aiHelpers.h
 *
 *  Created on: Dec 8, 2015
 *      Author: Pink Desktop
 */

#ifndef AIHELPERS_H_
#define AIHELPERS_H_

#include "checkers.h"
#include <stdio.h>
#include "minunit.h"

struct Move {
    struct Square *origin;
	struct Square *stops[12];
	int numStops;
	int isCapture;
};

struct GameInstance {
	struct CheckersGame game;
	struct Move moves[128];
	int mustCapture;
	int numMoves;
	double whiteProb;
};

/**
 * Make a deep copy of a Move
 */
void copyMove(struct Move *parentMove, struct Move *newMove);
/**
 * 
 */
int generateJumpPaths(
	struct CheckersGame *game, 
    struct GameInstance *gi, 
	struct Square *curSquare,
    int isWhiteTurn,
    int isKing,
	enum captureDirections capDirs,
	int depth);

void initGameInstance(struct GameInstance *gi);
/**
 * @Return heuristic value for current player odds as a continuous value 0 < x < 1.
 * Kings: 5 points
 * checkers: 1 + rows-from-the-bottom / 2 (eg. white checker 1 row away from king
 * would be worth 4 points)
 *
 * @return 1 - lowScore/highScore (* -1 if curPlayer is lowScore)
 */
double scoreGame(struct CheckersGame *game, int curPlayerIsWhite);

/**
 * Call minimax algorithm and execute the optimal move.
 */
void makeBestMove(struct GameInstance *gi, int isWhiteTurn);

/**
 * Recursive algorithm to find optimal move.
 * 
 * @return likelihook of winning
 * @param isMaxTurn maximizing level
 * @param isWhite maximizing player is white
 *
 * @pre gi->moves is populated with all possible moves. Origin is the 
 * originating square of the move; stops[0] is destination of regular
 * move or single capture; stops[i] are used for multiple jump captures.
 */
double minimax(struct GameInstance *gi, int isMaxTurn, int isWhite, int depth);

/**
 * Execute the move at moves[moveNumber]
 */
void runMove(struct GameInstance *gi, int moveNumber);
/**
 * gi.moves[] contains list of available moves
 * @param gi struct GameInstance* with Move array[128]
 * @param isWhiteTurn matches with all occupied Square.tenant.isWhite
 *
 * @pre: gi.moves[] origin and destination are initialized to NULL
 * @return  populates gi.moves[128] with Move objects of all legal moves with
 * 			matching color.
 */
void availableMoves(struct CheckersGame *game, struct GameInstance *gi, int isWhiteTurn);

/**
* Call singleCapture on saved capture move. (converts new location of capturer to toCapture location)
*/
void captureMove(struct GameInstance *gi, struct Square *origin, struct Square *destination);

/**
 * Make a deep copy of a GameInstance
 **/
void copyGI(struct GameInstance *gi, struct GameInstance *giCopy);
#endif /* AIHELPERS_H_ */
