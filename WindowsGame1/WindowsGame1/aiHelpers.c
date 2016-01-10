#include "checkers.h"
#include "aiHelpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include <assert.h>
#include <string.h>
void copyMove(struct Move *parentMove, struct Move *newMove) {
	int i;
	//Copy move into new move
	newMove->origin = parentMove->origin;
	for (i = 0; i < 12; i++) {
		newMove->stops[i] = parentMove->stops[i];
	}
	newMove->numStops = parentMove->numStops;
	newMove->isCapture = parentMove->isCapture;
}
//TODO: document generateJumpPaths()
int generateJumpPaths(
	struct CheckersGame *game, 
    struct GameInstance *gi, 
	struct Square *curSquare,
    int isWhiteTurn,
    int isKing,
	enum captureDirections capDirs,
	int depth
    ) {
	assert(gi->numMoves < 128);
	assert(gi->moves[gi->numMoves - 1].numStops <= 12);
	
	//Capture directions for destination Square
	enum captureDirections destCapDirs = 0;
	gi->moves[gi->numMoves - 1].numStops = depth;

	//Origin Square
	if (depth == 0) {
		gi->moves[gi->numMoves - 1].origin = curSquare;
	}

	//Not origin square
	//Save this new stop in moves[numMoves].stops[numStops - 1]
	else {
		gi->moves[gi->numMoves - 1].stops[depth - 1] = curSquare;
	}

	/*Base Case: curSquare has no captures available. */
	if (capDirs == 0) {
		return 1;
	}

	//Call canCapture on capture directions

	//This square can capture to the top left. 
	//This direction does not require duplicating the Move.
	//Catch infinite circuit condition
    if ((capDirs & TLEFT) == TLEFT && !(gi->moves[gi->numMoves - 1].origin == curSquare && curSquare->tl->tl == gi->moves[gi->numMoves - 1].stops[0])) {

        /*gi->numMoves++;*/
		//get the capture directions of the destination Square
		destCapDirs = canCapture(game, curSquare->tl->tl, isWhiteTurn, isKing, gi->moves[gi->numMoves - 1].origin);

		//Remove this square from destination capture directions to prevent inf loop
		destCapDirs = ((destCapDirs & BRIGHT) == BRIGHT)
			? (destCapDirs - BRIGHT)
			: destCapDirs;
		generateJumpPaths(
			game,
			gi,
			curSquare->tl->tl,
			isWhiteTurn,
			isKing,
			destCapDirs,
			(depth + 1));
    }
	//This square can capture to top right.
	//Catch infinite circuit condition
    if ((capDirs & TRIGHT) == TRIGHT && !(gi->moves[gi->numMoves - 1].origin == curSquare && curSquare->tr->tr == gi->moves[gi->numMoves - 1].stops[0])) {

        //If there is an alternate path to tl, duplicate move.Make sure that tl isn't the original move and we're on the origin, though.
        if (((capDirs & TLEFT) == TLEFT && (!(gi->moves[gi->numMoves - 1].origin == curSquare && curSquare->tl->tl == gi->moves[gi->numMoves - 1].stops[0]) || depth == 0))){
            copyMove(&gi->moves[gi->numMoves - 1], &gi->moves[gi->numMoves]);
			gi->moves[gi->numMoves].numStops = depth;
            gi->numMoves++;
        }
		//get the capture directions of the destination Square
		destCapDirs = canCapture(game, curSquare->tr->tr, isWhiteTurn, isKing, gi->moves[gi->numMoves - 1].origin);

		//Remove this square from destination capture directions to prevent inf loop
		destCapDirs = ((destCapDirs & BLEFT) == BLEFT)
			? (destCapDirs - BLEFT)
			: destCapDirs;
    	generateJumpPaths(
            game, 
            gi, 
            curSquare->tr->tr, 
            isWhiteTurn,
            isKing, 
    		destCapDirs,
			(depth + 1));
    }
	//This square can capture to bottom left
	//Catch infinite circuit condition
    if ((capDirs & BLEFT) == BLEFT && !(gi->moves[gi->numMoves - 1].origin == curSquare && curSquare->bl->bl == gi->moves[gi->numMoves - 1].stops[0])) {
        //If there is an alternate path to tl or tr, duplicate move.Make sure that tl isn't the original move and we're on the origin, though.
        if (((capDirs & TLEFT) == TLEFT && (!(gi->moves[gi->numMoves - 1].origin == curSquare && curSquare->tl->tl == gi->moves[gi->numMoves - 1].stops[0]) || depth == 0)) ||
			((capDirs & TRIGHT) == TRIGHT) && (!(gi->moves[gi->numMoves - 1].origin == curSquare && curSquare->tr->tr == gi->moves[gi->numMoves - 1].stops[0]) || depth == 0)) {
            copyMove(&gi->moves[gi->numMoves - 1], &gi->moves[gi->numMoves]);
			gi->moves[gi->numMoves].numStops = depth;
            gi->numMoves++;
        }
		//get the capture directions of the destination Square
		destCapDirs = canCapture(game, curSquare->bl->bl, isWhiteTurn, isKing, gi->moves[gi->numMoves - 1].origin);

		//Remove this square from destination capture directions to prevent inf loop
		destCapDirs = ((destCapDirs & TRIGHT) == TRIGHT)
			? (destCapDirs - TRIGHT)
			: destCapDirs;
		generateJumpPaths(
			game,
			gi,
			curSquare->bl->bl,
			isWhiteTurn,
			isKing,
			destCapDirs,
			(depth + 1));
    }
	//This square can capture to bottom right.
	//Catch infinite circuit condition
    if ((capDirs & BRIGHT) == BRIGHT && !(gi->moves[gi->numMoves - 1].origin == curSquare && curSquare->br->br == gi->moves[gi->numMoves - 1].stops[0])) {
		

        //If there is an alternate path to tl or tr, duplicate move. Make sure that tl isn't the original move and we're on the origin, though.
        if (((capDirs & TLEFT) == TLEFT && (!(gi->moves[gi->numMoves - 1].origin == curSquare && curSquare->tl->tl == gi->moves[gi->numMoves - 1].stops[0]) || depth == 0)) ||
			((capDirs & TRIGHT) == TRIGHT) && (!(gi->moves[gi->numMoves - 1].origin == curSquare && curSquare->tr->tr == gi->moves[gi->numMoves - 1].stops[0]) || depth == 0) ||
			((capDirs & BLEFT) == BLEFT) && (!(gi->moves[gi->numMoves - 1].origin == curSquare && curSquare->bl->bl == gi->moves[gi->numMoves - 1].stops[0]) || depth == 0)) {
            copyMove(&gi->moves[gi->numMoves - 1], &gi->moves[gi->numMoves]);
			gi->moves[gi->numMoves].numStops = depth;
            gi->numMoves++;
        }
		//get the capture directions of the destination Square
		destCapDirs = canCapture(game, curSquare->br->br, isWhiteTurn, isKing, gi->moves[gi->numMoves - 1].origin);

		//Remove this square from destination capture directions to prevent inf loop
		destCapDirs = ((destCapDirs & TLEFT) == TLEFT)
			? (destCapDirs - TLEFT)
			: destCapDirs;
    	generateJumpPaths(
            game, 
            gi, 
            curSquare->br->br, 
            isWhiteTurn, 
            isKing,
    		destCapDirs, 
			(depth + 1));
    }

    return 1;
}
/*
 * aiHelpers.c
 *
 *  Created on: Dec 8, 2015
 *      Author: Pink Desktop
 */
//TODO: test availableMoves()
void availableMoves(struct CheckersGame *game, struct GameInstance *gi, int isWhiteTurn) {
	int i, captureDest = 0;
	
	//Loop through all board squares
	for (i = 0; i < 32; i++) {

		//Friendly piece exists on current Square
		if (game->board[i].tenant != NULL && game->board[i].tenant->isWhite == isWhiteTurn) {
			//printSquare(game, &game->board[i]);
			//captureDest = capture directions or 0
			captureDest = canCapture(
				game, 
				&game->board[i], 
				isWhiteTurn, 
				game->board[i].tenant->isKing, 
				gi->moves[gi->numMoves - 1].origin);

			//printf("captureDest in availMoves function: %d\n", (int)captureDest);
			//Capture move identified
			if (captureDest > 0) {

				//If this is the first capture found, reset moves
				if (!gi->mustCapture) {
					gi->mustCapture = 1;    //Do not consider regular moves
					gi->numMoves = 1;       //Remove any moves already saved
					gi->moves[0].isCapture = 1;
					gi->moves[0].numStops = 0;
					gi->moves[0].origin = &game->board[i];
				}
				//New capture move found (after first capture move was found)
				else {
					gi->numMoves++;
					gi->moves[gi->numMoves - 1].origin = &game->board[i];
					gi->moves[gi->numMoves - 1].numStops = 0;
				}
				//printf("gi->numMoves  before generateJumpPaths(): %d\n", gi->numMoves);
				//Record a new move for each unique jump path
				generateJumpPaths(
					game, 
					gi, 
					&game->board[i], 
					isWhiteTurn, 
					game->board[i].tenant->isKing,
					captureDest,
					0);
				//printf("gi->numMoves after generateJumpPaths(): %d\n", gi->numMoves);
			}
			
			//Friendly piece exists at this square so check for move
			else if (
				!gi->mustCapture				&&
				game->board[i].tenant != NULL	&&
				game->board[i].tenant->isWhite == isWhiteTurn
				) {
				//Check each direction for legal move.
				if (canMove(game, &game->board[i])) {
					if (isLegalMove(game, &game->board[i], game->board[i].tl)) {
						gi->moves[gi->numMoves].origin = &game->board[i];
						gi->moves[gi->numMoves].stops[0] = game->board[i].tl;
						gi->moves[gi->numMoves].numStops++;
						gi->numMoves++;

					}
					if (isLegalMove(game, &game->board[i], game->board[i].tr)) {
						gi->moves[gi->numMoves].origin = &game->board[i];
						gi->moves[gi->numMoves].stops[0] = game->board[i].tr;
						gi->moves[gi->numMoves].numStops++;
						gi->numMoves++;
					}
					if (isLegalMove(game, &game->board[i], game->board[i].bl)) {
						gi->moves[gi->numMoves].origin = &game->board[i];
						gi->moves[gi->numMoves].stops[0] = game->board[i].bl;
						gi->moves[gi->numMoves].numStops++;
						gi->numMoves++;
					}
					if (isLegalMove(game, &game->board[i], game->board[i].br)) {
						gi->moves[gi->numMoves].origin = &game->board[i];
						gi->moves[gi->numMoves].stops[0] = game->board[i].br;
						gi->moves[gi->numMoves].numStops++;
						gi->numMoves++;
					}
				}
			}
			else {}//Either empty square or opponent-occupied
		}
	}
	return;
}

double scoreGame(struct CheckersGame *game, int curPlayerIsWhite) {
	int i, whiteRowNum, blackRowNum;
	double whiteScore;
	double blackScore;
	double scoreSum;
	double score;
	//assert((game->dead + game->white + game->black) == 24);

	whiteScore = 0;
	blackScore = 0;
	for (i = 0; i < 32; i++) {
		whiteRowNum = i / 4;
		blackRowNum = 7 - whiteRowNum;
		//Calculate white portion of score
		if (game->board[i].tenant && game->board[i].tenant->isWhite) {

			//kings are worth 5 points
			if (game->board[i].tenant->isKing) {
				whiteScore += 5;
			}
			//Checkers are worth 1 point for every 2 rows advanced.
			else
				whiteScore += (1 + (whiteRowNum / 2));
		}
		//Calculate black portion of score
		else if (game->board[i].tenant && !game->board[i].tenant->isWhite) {
			if (game->board[i].tenant->isKing) {
				blackScore += 5;
			}
			else
				blackScore += (1 + (blackRowNum / 2));
		}
	}
	scoreSum = whiteScore + blackScore;
	//printf("white: %f, black: %f\n", whiteScore, blackScore);
	if (whiteScore == 0)
		return curPlayerIsWhite ? -1.0 : 1.0;
	else if (blackScore == 0)
		return !curPlayerIsWhite ? 1.0 : -1.0;
	else if (whiteScore > blackScore) {
		score = whiteScore / scoreSum;
		if (curPlayerIsWhite)
			return score;
		else
			return -score;
	}
	else if (blackScore > whiteScore) {
		score = blackScore / scoreSum;
		if (curPlayerIsWhite)
			return -score;
		else
			return score;
	}
	//Scores are equal and non-zero
	else
		return 0.0;

}

void initGameInstance(struct GameInstance *gi) {
     int i, j;
	 initCheckersGame(&gi->game);
	 gi->mustCapture = 0;
	 gi->numMoves = 0;
	 gi->whiteProb = 0.0;
     for (i = 0; i < 128; i++) {
		gi->moves[i].origin = NULL;
		gi->moves[i].numStops = 0;
		for (j = 0; j < 12; j++) {
            gi->moves[i].stops[j] = NULL;
			gi->moves[i].numStops = 0;
        }
	 }
     
     return;
}

void makeBestMove(struct GameInstance *gi, int isWhite) {
#include "unitTests.h"
	int i, bestMove;
	double curScore, bestScore;
	curScore = bestScore = 0.0;
	bestMove = 0;
	availableMoves(&gi->game, gi, isWhite);
	//printMoves(&gi->game, gi);
	for (i = 0; i < gi->numMoves; i++) {
		curScore = minimax(gi, 1, isWhite, 2);
		if (curScore > bestScore) {
			bestScore = curScore;
			bestMove = i;
		}
	}
	printf("bestScore %f bestMove %d\n", bestScore, bestMove);
	/*runMove(gi, bestMove);*/
	printState(&gi->game);
}

//TODO: implement alpha beta pruning
//TODO: test runMove/copyGI/availableMoves in the context of minimax(). 

//Minimax should make a copy of the game state, run a move on the copy, and recurse on that copy. 
//Then, minimax should do this again on the next move. 
double minimax(struct GameInstance *gi, int isMaxTurn, int isWhite, int depth) {
	printState(&gi->game);
	int i;
	struct GameInstance curGI;
	initGameInstance(&curGI);
	double bestScore, curScore;
	if (depth == 0)
		return scoreGame(&gi->game, isWhite);
	if (isMaxTurn)
		bestScore = -1.0;
	else
		bestScore = 1.0;
	availableMoves(&gi->game, gi, isWhite);
	//for each possible move, call minimax()
	for (i = 0; i < gi->numMoves; i++) {
		copyGI(gi, &curGI);
		runMove(&curGI, i);
		curScore = minimax(&curGI, !isMaxTurn, !isWhite, depth - 1);
		if (isMaxTurn)
			bestScore = (bestScore > curScore) ? bestScore : curScore;
		else
			bestScore = (bestScore > curScore) ? curScore : bestScore;
	}
	return bestScore;
}

//TODO: properly unit test runMove
void runMove(struct GameInstance *gi, int moveNumber) {
	int i = 1;
	if (gi->mustCapture) {
		captureMove(gi, gi->moves[moveNumber].origin, gi->moves[moveNumber].stops[0]);
		while (i <= gi->moves[moveNumber].numStops) {
			captureMove(gi, gi->moves[moveNumber].stops[i - 1], gi->moves[moveNumber].stops[i]);
			i++;
		}
	}
	else
		move(&gi->game, gi->moves[moveNumber].origin, gi->moves[moveNumber].stops[0]);
	return;
}


void captureMove(struct GameInstance *gi, struct Square *origin, struct Square *destination) {
	if (destination == origin->tl->tl)
		singleCapture(&gi->game, origin, origin->tl);
	else if (destination == origin->tr->tr)
		singleCapture(&gi->game, origin, origin->tr);
	else if (destination == origin->bl->bl)
		singleCapture(&gi->game, origin, origin->bl);
	else /*(destination == origin->br->br)*/
		singleCapture(&gi->game, origin, origin->br);
	return;
}

void copyGI(struct GameInstance *gi, struct GameInstance *giCopy) {
	int i, whiteSetIndex, blackSetIndex;
	whiteSetIndex = 0;
	blackSetIndex = 12;
	for (i = 0; i < 128; i++) 
		copyMove(&gi->moves[i], &giCopy->moves[i]);
	giCopy->mustCapture = gi->mustCapture;
	giCopy->numMoves = gi->numMoves;
	giCopy->whiteProb = gi->whiteProb;
	for (i = 0; i < 32; i++) {
		if (gi->game.board[i].tenant != NULL) {
			if (gi->game.board[i].tenant->isWhite) {
				giCopy->game.board[i].tenant = &giCopy->game.set[whiteSetIndex];
				whiteSetIndex++;
			}
			else {
				giCopy->game.board[i].tenant = &giCopy->game.set[blackSetIndex];
				blackSetIndex++;
			}
			giCopy->game.board[i].tenant->isKing = gi->game.board[i].tenant->isKing;
		}
		else
			giCopy->game.board[i].tenant = NULL;
	}
	giCopy->game.black = gi->game.black;
	giCopy->game.white = gi->game.white;
	giCopy->game.dead = gi->game.dead;
	giCopy->game.whiteTurn = gi->game.whiteTurn;
	for (i = 0; i < 24; i++) {
		giCopy->game.set[i].isKing = gi->game.set[i].isKing;
		giCopy->game.set[i].isWhite = gi->game.set[i].isWhite;
	}
	
	return;
}