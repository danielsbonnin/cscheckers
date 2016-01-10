#include <stdio.h>
#include <stdlib.h>
#include "checkers.h"
#include <assert.h>

void initCheckersBoard(struct CheckersGame *game) {
	int i;

	//Initialize board linked list.
	game->board[0].tl = NULL;
	game->board[0].tr = &game->board[4];
	game->board[0].bl = NULL;
	game->board[0].br = NULL;
	game->board[1].tl = &game->board[4];
	game->board[1].tr = &game->board[5];
	game->board[1].bl = NULL;
	game->board[1].br = NULL;
	game->board[2].tl = &game->board[5];
	game->board[2].tr = &game->board[6];
	game->board[2].bl = NULL;
	game->board[2].br = NULL;
	game->board[3].tl = &game->board[6];
	game->board[3].tr = &game->board[7];
	game->board[3].bl = NULL;
	game->board[3].br = NULL;
	game->board[4].tl = &game->board[8];
	game->board[4].tr = &game->board[9];
	game->board[4].bl = &game->board[0];
	game->board[4].br = &game->board[1];
	game->board[5].tl = &game->board[9];
	game->board[5].tr = &game->board[10];
	game->board[5].bl = &game->board[1];
	game->board[5].br = &game->board[2];
	game->board[6].tl = &game->board[10];
	game->board[6].tr = &game->board[11];
	game->board[6].bl = &game->board[2];
	game->board[6].br = &game->board[3];
	game->board[7].tl = &game->board[11];
	game->board[7].tr = NULL;
	game->board[7].bl = &game->board[3];
	game->board[7].br = NULL;
	game->board[8].tl = NULL;
	game->board[8].tr = &game->board[12];
	game->board[8].bl = NULL;
	game->board[8].br = &game->board[4];
	game->board[9].tl = &game->board[12];
	game->board[9].tr = &game->board[13];
	game->board[9].bl = &game->board[4];
	game->board[9].br = &game->board[5];
	game->board[10].tl = &game->board[13];
	game->board[10].tr = &game->board[14];
	game->board[10].bl = &game->board[5];
	game->board[10].br = &game->board[6];
	game->board[11].tl = &game->board[14];
	game->board[11].tr = &game->board[15];
	game->board[11].bl = &game->board[6];
	game->board[11].br = &game->board[7];
	game->board[12].tl = &game->board[16];
	game->board[12].tr = &game->board[17];
	game->board[12].bl = &game->board[8];
	game->board[12].br = &game->board[9];
	game->board[13].tl = &game->board[17];
	game->board[13].tr = &game->board[18];
	game->board[13].bl = &game->board[9];
	game->board[13].br = &game->board[10];
	game->board[14].tl = &game->board[18];
	game->board[14].tr = &game->board[19];
	game->board[14].bl = &game->board[10];
	game->board[14].br = &game->board[11];
	game->board[15].tl = &game->board[19];
	game->board[15].tr = NULL;
	game->board[15].bl = &game->board[11];
	game->board[15].br = NULL;
	game->board[16].tr = NULL;
	game->board[16].tl = &game->board[20];
	game->board[16].bl = NULL;
	game->board[16].br = &game->board[12];
	game->board[17].tl = &game->board[20];
	game->board[17].tr = &game->board[21];
	game->board[17].bl = &game->board[12];
	game->board[17].br = &game->board[13];
	game->board[18].tl = &game->board[21];
	game->board[18].tr = &game->board[22];
	game->board[18].bl = &game->board[13];
	game->board[18].br = &game->board[14];
	game->board[19].tl = &game->board[22];
	game->board[19].tr = &game->board[23];
	game->board[19].bl = &game->board[14];
	game->board[19].br = &game->board[15];
	game->board[20].tl = &game->board[24];
	game->board[20].tr = &game->board[25];
	game->board[20].bl = &game->board[16];
	game->board[20].br = &game->board[17];
	game->board[21].tl = &game->board[25];
	game->board[21].tr = &game->board[26];
	game->board[21].bl = &game->board[17];
	game->board[21].br = &game->board[18];
	game->board[22].tl = &game->board[26];
	game->board[22].tr = &game->board[27];
	game->board[22].bl = &game->board[18];
	game->board[22].br = &game->board[19];
	game->board[23].tl = &game->board[27];
	game->board[23].tr = NULL;
	game->board[23].bl = &game->board[19];
	game->board[23].br = NULL;
	game->board[24].tl = NULL;
	game->board[24].tr = &game->board[28];
	game->board[24].bl = NULL;
	game->board[24].br = &game->board[20];
	game->board[25].tl = &game->board[28];
	game->board[25].tr = &game->board[29];
	game->board[25].bl = &game->board[20];
	game->board[25].br = &game->board[21];
	game->board[26].tl = &game->board[29];
	game->board[26].tr = &game->board[30];
	game->board[26].bl = &game->board[21];
	game->board[26].br = &game->board[22];
	game->board[27].tl = &game->board[30];
	game->board[27].tr = &game->board[31];
	game->board[27].bl = &game->board[22];
	game->board[27].br = &game->board[23];
	game->board[28].tl = NULL;
	game->board[28].tr = NULL;
	game->board[28].bl = &game->board[24];
	game->board[28].br = &game->board[25];
	game->board[29].tl = NULL;
	game->board[29].tr = NULL;
	game->board[29].bl = &game->board[25];
	game->board[29].br = &game->board[26];
	game->board[30].tl = NULL;
	game->board[30].tr = NULL;
	game->board[30].bl = &game->board[26];
	game->board[30].br = &game->board[27];
	game->board[31].tl = NULL;
	game->board[31].tr = NULL;
	game->board[31].bl = &game->board[27];
	game->board[31].br = NULL;

	for (i = 0; i < 32; i++)
		game->board[i].tenant = NULL;
}

void initCheckersGame(struct CheckersGame *game) {

	int i;

	initCheckersBoard(game);

	for (i = 0; i < 12; i++) {
		game->set[i].isWhite = 1;
		game->set[i].isKing = 0;
	}

	for (i = 12; i < 24; i++) {
		game->set[i].isWhite = 0;
		game->set[i].isKing = 0;
	}

	//Put checkers out on the board
	for (i = 0; i < 12; i++) {
		game->board[i].tenant = &game->set[i];
	}

	for (i = 12; i < 20; i++) {
		game->board[i].tenant = NULL;
	}

	for (i = 20; i < 32; i++) {
		game->board[i].tenant = &game->set[i - 8];
	}
	game->dead = 0;
	game->white = 12;
	game->black = 12;
	game->whiteTurn = 1;
}

int isLegalMove(struct CheckersGame *game, struct Square *curSquare, struct Square *destination) {
	//Detect edge of board
	if (destination == NULL)
		return 0;
	//Check that destination is empty
	if (destination->tenant != NULL) {
		return 0;
	}
	//king can move any direction. Check for edge and occupied
	if (curSquare->tenant->isKing){
		//Check for adjacent square
		if ((destination != curSquare->tl &&
			destination != curSquare->tr &&
			destination != curSquare->bl &&
			destination != curSquare->br) ||
			//destination is occupied
			destination->tenant != NULL){
			return 0;
		}
	}
	else if (curSquare->tenant->isWhite) {
		//white, non-king: can only move to tr or tl
		if (destination != curSquare->tl &&
			destination != curSquare->tr)
			return 0;
	}
	else if (!curSquare->tenant->isWhite) {
		//black, non-king: can only move to br or bl
		if (destination != curSquare->br &&
			destination != curSquare->bl)
			return 0;
	}
	return 1;
}

int canMove(struct CheckersGame *game, struct Square *curSquare) {
	assert(curSquare->tenant != NULL);
	//Not a king
	if (!curSquare->tenant->isKing) {
		//White player
		if (curSquare->tenant->isWhite) {
			//Both top neighbors are blocked
			if ((curSquare->tl == NULL || curSquare->tl->tenant != NULL) &&
				(curSquare->tr == NULL || curSquare->tr->tenant != NULL))
					return 0;
		}
		//Black player
		else {
			//Both bottom neighbors are blocked
			if ((curSquare->bl == NULL || curSquare->bl->tenant != NULL) &&
				(curSquare->br == NULL || curSquare->br->tenant != NULL))
				return 0;
		}
	}
	//A king
	else {
		//All neighbors are blocked
		if ((curSquare->bl == NULL || curSquare->bl->tenant != NULL) &&
			(curSquare->br == NULL || curSquare->tr->tenant != NULL) &&
			(curSquare->tl == NULL || curSquare->tl->tenant != NULL) &&
			(curSquare->tr == NULL || curSquare->tr->tenant != NULL)
			)
			return 0;

	}
	return 1;
}

int canCapture(struct CheckersGame *game, struct Square *curSquare, int isWhite, int isKing, struct Square *origin) {
       int dirs = 0;
	
	//White player or king
	if (isWhite || isKing) {
		
		//Test for top left direction
		if (
			curSquare->tl != NULL 				&&  //neighbor square exists
			curSquare->tl->tenant != NULL		&&  //neighbor square has tenant
			curSquare->tl->tenant->isWhite != isWhite	 	&&  //neighbor square tenant is opposite color
			curSquare->tl->tl != NULL			&&  //far neighbor of neighbor exists
			(curSquare->tl->tl->tenant == NULL  ||      	//far neighbor of neighbor is empty or origin
			 curSquare->tl->tl == origin)) 
			dirs = (dirs | TLEFT);
		
		//Test for top right direction
	
		if (
			curSquare->tr != NULL 				&&  //neighbor square exists
			curSquare->tr->tenant != NULL		&&  //neighbor square has tenant
			curSquare->tr->tenant->isWhite != isWhite		&&  //neighbor square is not friend
			curSquare->tr->tr != NULL			&&  //far neighbor of neighbor exists
			(curSquare->tr->tr->tenant == NULL ||      	//far neighbor of neighbor is empty or origin
				curSquare->tr->tr == origin)
			) 
			dirs = (dirs | TRIGHT);
	}

	//Black player
	if (!isWhite || isKing){
		
		//Test for bottom left direction
		if (
			curSquare->bl != NULL 				&&  //neighbor square exists
			curSquare->bl->tenant != NULL		&&  //neighbor square has tenant
			curSquare->bl->tenant->isWhite != isWhite 		&&  //neighbor square is not friend
			curSquare->bl->bl != NULL			&&  //far neighbor of neighbor exists
			(curSquare->bl->bl->tenant == NULL ||      	//far neighbor of neighbor is empty or origin
				curSquare->bl->bl == origin)
			) 
			dirs = (dirs | BLEFT);
		
		//Test for bottom right direction
		if (
			curSquare->br != NULL 				&&  //neighbor square exists
			curSquare->br->tenant != NULL		&&  //neighbor square has tenant
			curSquare->br->tenant->isWhite != isWhite 		&&  //neighbor square is not friend
			curSquare->br->br != NULL			&&  //far neighbor of neighbor exists
			(curSquare->br->br->tenant == NULL ||      	//far neighbor of neighbor is empty or origin
				curSquare->br->br == origin)
			)
			dirs = (dirs | BRIGHT);
	}
	return dirs;
}

struct Square * singleCapture(struct CheckersGame *game, struct Square *curSquare, struct Square *toCapture) {
    struct Square *newLoc;
	
	assert(toCapture->tenant != NULL);
    if (toCapture == curSquare->tl)
		newLoc = toCapture->tl;
	else if (toCapture == curSquare->tr)
		newLoc = toCapture->tr;
	else if (toCapture == curSquare->bl)
		newLoc = toCapture->bl;
	else if (toCapture == curSquare->br)
		newLoc = toCapture->br;
	else
		return NULL;
	move(game, curSquare, newLoc);
	//printSquare(game, newLoc);
	

	game->dead++;
	if (toCapture->tenant->isWhite)
		game->white--;
	else
		game->black--;
	toCapture->tenant = NULL;
	kingMe(game, newLoc);
	return newLoc;
 }
 
//void capture(struct CheckersGame *game, struct Square *curSquare, struct Square *toCapture) {
//	struct Square *newLoc;
//	newLoc = singleCapture(game, curSquare, toCapture);
//	toCapture = canCapture(game, newLoc);
//	while (toCapture) {
//		newLoc = singleCapture(game, newLoc, toCapture);
//		toCapture = canCapture(game, newLoc);
//	}
//	return;
//}

void move(struct CheckersGame *game, struct Square *curSquare, struct Square *destination) {
	destination->tenant = curSquare->tenant;
	curSquare->tenant = NULL;
	kingMe(game, destination);
	return;
}

void kingMe(struct CheckersGame *game, struct Square *destination) {
	//King the moved piece if conditions are met.
	if ((destination == &game->board[0] || destination == &game->board[1] ||
		destination == &game->board[2] || destination == &game->board[3]) &&
		(destination->tenant != NULL && !destination->tenant->isKing && !destination->tenant->isWhite))
		destination->tenant->isKing = 1;

	else if ((destination == &game->board[28] || destination == &game->board[29] ||
		destination == &game->board[30] || destination == &game->board[31]) &&
		(destination->tenant != NULL && !destination->tenant->isKing && destination->tenant->isWhite))
		destination->tenant->isKing = 1;
	else {}
}

