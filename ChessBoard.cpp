#define SIZECHESSPIECEX 50
#define SIZECHESSPIECEY 48
#define SIZEGAMESTATUSX 188
#define SIZEGAMESTATUSY 200
#undef min
#undef max
#include"ChessBoard.h"

bool ChessBoard::checkKnightMove(int x, int y, int newX, int newY) {
	int delX = newX - x;
	int delY = newY - y;
	if (2 == abs(delX)) {
		return (chessPieces[x + sign(delX)][y] == 0);
	}
	if (2 == abs(delY)) {
		return (chessPieces[x][y + sign(delY)] == 0);
	}
}
/*
Function: checkPointInSquare
Param:	- x,y: coord of point
		- i,j: point (i,j) of chessPieces
		- width, height: size of square
Return: - true: (x,y) in circle origin chessPiece[i][j] with raidus width/2
		- false: else
*/
bool ChessBoard::checkPointInSquarev2(int x, int y, int i, int j, int width, int height) {
	int left = chessPieceX[j], top = chessPieceY[i];
	int distance = ((x - left) * (x - left)) + ((y - top) * (y - top));
	if (distance <= (width * height / 4)) {
		return true;
	}
	return false;
}
bool ChessBoard::checkPointInSquare(int x, int y, int i, int j, int width, int height) {
	if (i >= 10 || j >= 9) return false;
	if (i < 0 || j < 0) return false;
	if (chessPieces[i][j] == 0) return false;
	return checkPointInSquarev2(x, y, i, j, width, height);
}
/*
Function cmpColor
Purpose: Check if chessBoards[x1][y1] and chessBoards[x2][y2] is same color
*/
bool ChessBoard::cmpColor(int x1, int y1, int x2, int y2) {
	if (x2 < 0 || x2 >= 10 || y2 < 0 || y2 >= 9) {
		return true;
	}
	int color1;
	if (chessPieces[x1][y1] == 0) {
		color1 = -1;
	}
	else {
		color1 = (chessPieces[x1][y1] < 8) ? 0 : 1;
	}
	int color2;
	if (chessPieces[x2][y2] == 0) {
		color2 = -1;
	}
	else {
		color2 = (chessPieces[x2][y2] < 8) ? 0 : 1;
	}
	return (color1 == color2);
}
/*
Function: sign
Return: -1 if k<0
		1 if k>0
		0 if k=0
*/
int ChessBoard::sign(int k) {
	return (k > 0) - (k < 0);
}
/*
Function: isEmpty
Purpose: Check if position of (x,y) in board is empty
*/
bool ChessBoard::isEmpty(int x, int y) {
	return (chessPieces[x][y] == 0);
}
//Constructor
ChessBoard::ChessBoard(void) {
	if (!boardTexture.loadFromFile("board.png")) {
		printf("Cant open -board.png-\n");
		return;
	}
	if (!iconTexture.loadFromFile("icon.png")) {
		printf("Cant open -icon.png-\n");
		return;
	}
	if (!gameStatusTexture.loadFromFile("gameStatus.png")) {
		printf("Cant open -gameStatus.png-\n");
		return;
	}

	sBoard.setTexture(boardTexture);
	for (int i = 1; i <= 14; ++i) {
		sChessPiece[i].setTexture(iconTexture);
		int x;
		if (i <= 7) {
			x = (i - 1) * SIZECHESSPIECEX;
		}
		else {
			x = (i - 7 - 1) * SIZECHESSPIECEX;
		}
		int y = (i <= 7) ? 0 : SIZECHESSPIECEY;
		sChessPiece[i].setTextureRect(sf::IntRect(x, y, SIZECHESSPIECEX, SIZECHESSPIECEY));
	}
	sLightCircle.setTexture(iconTexture);
	sLightCircle.setTextureRect(sf::IntRect(0, 2 * SIZECHESSPIECEY, SIZECHESSPIECEX, SIZECHESSPIECEY));
	sRedChoosedChessPiece.setTexture(iconTexture);
	sRedChoosedChessPiece.setTextureRect(sf::IntRect(SIZECHESSPIECEX, 2 * SIZECHESSPIECEY, SIZECHESSPIECEX, SIZECHESSPIECEY));
	sRedPreviousMove.setTexture(iconTexture);
	sRedPreviousMove.setTextureRect(sf::IntRect(2 * SIZECHESSPIECEX, 2 * SIZECHESSPIECEY, SIZECHESSPIECEX, SIZECHESSPIECEY));
	sBlackChoosedChessPiece.setTexture(iconTexture);
	sBlackChoosedChessPiece.setTextureRect(sf::IntRect(3 * SIZECHESSPIECEX, 2 * SIZECHESSPIECEY, SIZECHESSPIECEX, SIZECHESSPIECEY));
	sBlackPreviousMove.setTexture(iconTexture);
	sBlackPreviousMove.setTextureRect(sf::IntRect(4 * SIZECHESSPIECEX, 2 * SIZECHESSPIECEY, SIZECHESSPIECEX, SIZECHESSPIECEY));
	choosedChessPiece.x = -1;
	choosedChessPiece.y = -1;
	sWinStatus.setTexture(gameStatusTexture);
	sWinStatus.setTextureRect(sf::IntRect(0 * SIZEGAMESTATUSX, 0, SIZEGAMESTATUSX, SIZEGAMESTATUSY));
	sWinStatus.setPosition(166, 200);
	sDrawStatus.setTexture(gameStatusTexture);
	sDrawStatus.setTextureRect(sf::IntRect(1 * SIZEGAMESTATUSX, 0, SIZEGAMESTATUSX, SIZEGAMESTATUSY));
	sDrawStatus.setPosition(166, 200);
	sLossStatus.setTexture(gameStatusTexture);
	sLossStatus.setTextureRect(sf::IntRect(2 * SIZEGAMESTATUSX, 0, SIZEGAMESTATUSX, SIZEGAMESTATUSY));
	sLossStatus.setPosition(166, 200);
}
/*
Function: init
Purpose: Generate start board
*/
void ChessBoard::init(void) {
	bCheckLoss = -1;
	int temp[][15] = {
		{ 2, 4, 7, 6, 5, 6, 7, 4, 2},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 3, 0, 0, 0, 0, 0, 3, 0},
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 8, 0, 8, 0, 8, 0, 8, 0, 8},
		{ 0,10, 0, 0, 0, 0, 0,10, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{ 9,11,14,13,12,13,14,11, 9}
	};
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 9; ++j) {
			chessPieces[i][j] = temp[i][j];
		}
	}
}
int ChessBoard::getTurn(void) {
	return turn;
}
void ChessBoard::setTurn(int t) {
	turn = t;
}
string ChessBoard::getNameChessPiece(int k) {
	string mau = "";
	if (k < 1 || k>14) {
		return string("Khong xac dinh");
	}
	if (k <= 7) {
		mau = "Den-Black";
	}
	else {
		k -= 7;
		mau = "Do-Red";
	}
	string chessPiece = "";
	switch (k) {
	case 1:
		chessPiece = "Chot-Pawn";
		break;
	case 2:
		chessPiece = "Xe-Pook";
		break;
	case 3:
		chessPiece = "Phao-Canon";
		break;
	case 4:
		chessPiece = "Ma-Knight";
		break;
	case 5:
		chessPiece = "Tuong-King";
		break;
	case 6:
		chessPiece = "Si-Guard";
		break;
	case 7:
		chessPiece = "Tuong-Bishop";
		break;
	}
	string ans = chessPiece + " " + mau;
	return ans;
}
/*
Function: draw
Purpose: draw image to window
*/
void ChessBoard::draw(sf::RenderWindow & window, sf::Sprite & sprite, int i, int j) {
	int x = chessPieceX[j] - (SIZECHESSPIECEX / 2);
	int y = chessPieceY[i] - (SIZECHESSPIECEY / 2);
	sprite.setPosition(sf::Vector2f(x, y));
	window.draw(sprite);
}
void ChessBoard::draw(sf::RenderWindow & window) {
	window.draw(sBoard);
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (0 == chessPieces[i][j]) {
				continue;
			}
			draw(window, sChessPiece[chessPieces[i][j]], i, j);
		}
	}
	if (choosedChessPiece.x >= 0 && choosedChessPiece.y >= 0) {
		if (chessPieces[choosedChessPiece.x][choosedChessPiece.y] < 8) {
			draw(window, sBlackChoosedChessPiece, choosedChessPiece.x, choosedChessPiece.y);
		}
		else {
			draw(window, sRedChoosedChessPiece, choosedChessPiece.x, choosedChessPiece.y);
		}
	}
	if (!history.empty()) {
		MoveStruct tmp = history.top();
		sf::Vector2i lastMove = sf::Vector2i(tmp.dX, tmp.dY);
		sf::Vector2i lastChoose = sf::Vector2i(tmp.sX, tmp.sY);
		if (chessPieces[lastMove.x][lastMove.y] < 8) {
			draw(window, sBlackChoosedChessPiece, lastMove.x, lastMove.y);
			draw(window, sBlackPreviousMove, lastChoose.x, lastChoose.y);
		}
		else {
			draw(window, sRedChoosedChessPiece, lastMove.x, lastMove.y);
			draw(window, sRedPreviousMove, lastChoose.x, lastChoose.y);
		}
	}
}
/*
Function: checkHitChessPiece
Purpose: return chess piece hited by mouse and get posion of it
Param:	-x,y: coord of mouse
		-res_i,resj: reference to position of chess piece
*/
int ChessBoard::checkHitChessPiece(int x, int y, int& res_i, int& res_j) {
	res_i = 10;
	res_j = 9;
	for (int j = 0; j < 9; ++j) {
		if (chessPieceX[j] >= x) {
			res_j = j;
			break;
		}
	}
	for (int i = 0; i < 10; ++i) {
		if (chessPieceY[i] >= y) {
			res_i = i;
			break;
		}
	}
	if (checkPointInSquare(x, y, res_i, res_j, SIZECHESSPIECEX, SIZECHESSPIECEY)) {
		return chessPieces[res_i][res_j];
	}
	if (checkPointInSquare(x, y, res_i - 1, res_j, SIZECHESSPIECEX, SIZECHESSPIECEY)) {
		res_i--;
		return chessPieces[res_i][res_j];
	}
	if (checkPointInSquare(x, y, res_i, res_j - 1, SIZECHESSPIECEX, SIZECHESSPIECEY)) {
		res_j--;
		return chessPieces[res_i][res_j];
	}
	if (checkPointInSquare(x, y, res_i - 1, res_j - 1, SIZECHESSPIECEX, SIZECHESSPIECEY)) {
		res_i--, res_j--;
		return chessPieces[res_i][res_j];
	}
	return 0;
}
//Chess Piece is choosing
void ChessBoard::setChoosedChessPiece(int x, int y) {
	choosedChessPiece.x = x;
	choosedChessPiece.y = y;
}
void ChessBoard::getChoosedChessPiece(int& x, int& y) {
	x = choosedChessPiece.x;
	y = choosedChessPiece.y;
}
/*
Function: generateMove
Param:	- window: window to draw
		- x,y: coord of chess piece to generate move
		- int n: number of move generated
		- moveX, moveY: array of generated move
*/
void ChessBoard::generateMove(int x, int y, int& n, int moveX[], int moveY[]) {
	n = 0;
	switch (chessPieces[x][y]) {
	case 1: // Black Pawn
		if (x < 9 && !cmpColor(x, y, x + 1, y) && !lossMove(x, y, x + 1, y)) {
			moveX[n] = x + 1;
			moveY[n] = y;
			n++;
		}
		if (x > 4) {
			if (y > 0 && !cmpColor(x, y, x, y - 1) && !lossMove(x, y, x, y - 1)) {
				moveX[n] = x;
				moveY[n] = y - 1;
				n++;
			}
			if (y < 8 && !cmpColor(x, y, x, y + 1) && !lossMove(x, y, x, y + 1)) {
				moveX[n] = x;
				moveY[n] = y + 1;
				n++;
			}
		}
		break;
	case 2: case 9: // Pook
		for (int i = x - 1; i >= 0; --i) {
			if (chessPieces[i][y] != 0) {
				if (!cmpColor(x, y, i, y) && !lossMove(x, y, i, y)) {
					moveX[n] = i;
					moveY[n] = y;
					n++;
				}
				break;
			}
			if (!lossMove(x, y, i, y)) {
				moveX[n] = i;
				moveY[n] = y;
				n++;
			}
		}
		for (int i = x + 1; i < 10; ++i) {
			if (chessPieces[i][y] != 0) {
				if (!cmpColor(x, y, i, y) && !lossMove(x, y, i, y)) {
					moveX[n] = i;
					moveY[n] = y;
					n++;
				}
				break;
			}
			if (!lossMove(x, y, i, y)) {
				moveX[n] = i;
				moveY[n] = y;
				n++;
			}
		}
		for (int j = y - 1; j >= 0; --j) {
			if (chessPieces[x][j] != 0) {
				if (!cmpColor(x, y, x, j) && !lossMove(x, y, x, j)) {
					moveX[n] = x;
					moveY[n] = j;
					n++;
				}
				break;
			}
			if (!lossMove(x, y, x, j)) {
				moveX[n] = x;
				moveY[n] = j;
				n++;
			}
		}
		for (int j = y + 1; j < 9; ++j) {
			if (chessPieces[x][j] != 0) {
				if (!cmpColor(x, y, x, j) && !lossMove(x, y, x, j)) {
					moveX[n] = x;
					moveY[n] = j;
					n++;
				}
				break;
			}
			if (!lossMove(x, y, x, j)) {
				moveX[n] = x;
				moveY[n] = j;
				n++;
			}
		}
		break;
	case 3: case 10: // canon
		for (int i = x - 1; i >= 0; --i) {
			if (chessPieces[i][y] != 0) {
				for (int ii = i - 1; ii >= 0; --ii) {
					if (chessPieces[ii][y] != 0) {
						if (!cmpColor(x, y, ii, y) && !lossMove(x, y, ii, y)) {
							moveX[n] = ii;
							moveY[n] = y;
							n++;
						}
						break;
					}
				}
				break;
			}
			if (!lossMove(x, y, i, y)) {
				moveX[n] = i;
				moveY[n] = y;
				n++;
			}
		}
		for (int i = x + 1; i < 10; ++i) {
			if (chessPieces[i][y] != 0) {
				for (int ii = i + 1; ii < 10; ++ii) {
					if (chessPieces[ii][y] != 0) {
						if (!cmpColor(x, y, ii, y) && !lossMove(x, y, ii, y)) {
							moveX[n] = ii;
							moveY[n] = y;
							n++;
						}
						break;
					}
				}
				break;
			}
			if (!lossMove(x, y, i, y)) {
				moveX[n] = i;
				moveY[n] = y;
				n++;
			}
		}
		for (int j = y - 1; j >= 0; --j) {
			if (chessPieces[x][j] != 0) {
				for (int jj = j - 1; jj >= 0; --jj) {
					if (chessPieces[x][jj] != 0) {
						if (!cmpColor(x, y, x, jj) && !lossMove(x, y, x, jj)) {
							moveX[n] = x;
							moveY[n] = jj;
							n++;
						}
						break;
					}
				}
				break;
			}
			if (!lossMove(x, y, x, j)) {
				moveX[n] = x;
				moveY[n] = j;
				n++;
			}
		}
		for (int j = y + 1; j < 9; ++j) {
			if (chessPieces[x][j] != 0) {
				for (int jj = j + 1; jj < 9; ++jj) {
					if (chessPieces[x][jj] != 0) {
						if (!cmpColor(x, y, x, jj) && !lossMove(x, y, x, jj)) {
							moveX[n] = x;
							moveY[n] = jj;
							n++;
						}
						break;
					}
				}
				break;
			}
			if (!lossMove(x, y, x, j)) {
				moveX[n] = x;
				moveY[n] = j;
				n++;
			}
		}
		break;
	case 4: case 11: // Knight
		for (int k = 0; k < 8; k++) {
			int xx = x + cKnightX[k];
			int yy = y + cKnightY[k];
			if (!checkKnightMove(x, y, xx, yy)) {
				continue;
			}
			if (!cmpColor(x, y, xx, yy) && !lossMove(x, y, xx, yy)) {
				moveX[n] = xx;
				moveY[n] = yy;
				n++;
			}
		}
		break;
	case 5: case 12: // King
		for (int k = 0; k < 4; k++) {
			int xx = x + cKingX[k];
			int yy = y + cKingY[k];
			if (!cmpColor(x, y, xx, yy) && !lossMove(x, y, xx, yy)) {
				moveX[n] = xx;
				moveY[n] = yy;
				n++;
			}
		}
		break;
	case 6: case 13://Guard
		for (int di = 0; di < 2; ++di) {
			for (int dj = 0; dj < 2; ++dj) {
				int xx = x + cGuardX[di];
				int yy = y + cGuardY[dj];
				if (yy < 3 || yy>5) {
					continue;
				}
				if (xx < 5) {
					if (xx > 2) {
						continue;
					}
				}
				else {
					if (xx < 7) {
						continue;
					}
				}
				if (!cmpColor(x, y, xx, yy) && !lossMove(x, y, xx, yy)) {
					moveX[n] = xx;
					moveY[n] = yy;
					n++;
				}
			}
		}
		break;
	case 7: case 14: // Elephant
		for (int di = 0; di < 2; ++di) {
			for (int dj = 0; dj < 2; ++dj) {
				int xx = x + cBishopX[di];
				int yy = y + cBishopY[dj];
				if (x <= 4 && xx > 4) {// river
					continue;
				}
				if (x > 4 && xx <= 4) {// river
					continue;
				}
				if (chessPieces[x + sign(cBishopX[di])][y + sign(cBishopX[dj])] != 0) {
					continue;
				}
				if (!cmpColor(x, y, xx, yy) && !lossMove(x, y, xx, yy)) {
					moveX[n] = x + cBishopX[di];
					moveY[n] = y + cBishopY[dj];
					n++;
				}
			}
		}
		break;
	case 8: // Red Pawn
		if (x > 0 && !cmpColor(x, y, x - 1, y) && !lossMove(x, y, x - 1, y)) {
			moveX[n] = x - 1;
			moveY[n] = y;
			n++;
		}
		if (x <= 4) {
			if (y > 0 && !cmpColor(x, y, x, y - 1) && !lossMove(x, y, x, y - 1)) {
				moveX[n] = x;
				moveY[n] = y - 1;
				n++;
			}
			if (y < 8 && !cmpColor(x, y, x, y + 1) && !lossMove(x, y, x, y + 1)) {
				moveX[n] = x;
				moveY[n] = y + 1;
				n++;
			}
		}
		break;
	}
}
void ChessBoard::generateMove(sf::RenderWindow & window, int x, int y, int& n, int moveX[], int moveY[]) {
	generateMove(x, y, n, moveX, moveY);
	for (int i = 0; i < n; ++i) {
		draw(window, sLightCircle, moveX[i], moveY[i]);
	}
}
/*
Function: moveChessPiece
Purpose: Move a chess piece to new postion. Save history and last move
*/
void ChessBoard::moveChessPiece(int originX, int originY, int desX, int desY) {
	bCheckLoss = -1;
	history.push(MoveStruct(chessPieces[originX][originY], originX, originY, desX, desY, chessPieces[desX][desY]));
	chessPieces[desX][desY] = chessPieces[originX][originY];
	chessPieces[originX][originY] = 0;
	setTurn(1 - getTurn());
}
/*
Function: UndoMove
Purpose: undo last move
*/
void ChessBoard::undoMove() {
	if (history.empty()) {
		printf("Cant undo move\n");
		return;
	}
	MoveStruct lastHistoryMove = history.top();
	history.pop();
	chessPieces[lastHistoryMove.sX][lastHistoryMove.sY] = lastHistoryMove.sChessPiece;
	chessPieces[lastHistoryMove.dX][lastHistoryMove.dY] = lastHistoryMove.dChessPiece;
	turn = 1 - turn;
}
bool ChessBoard::checkLoss() {
	if (bCheckLoss == 0) return false;
	if (bCheckLoss == 1) return true;
	int n;
	int moveX[50], moveY[50];
	int chess[15];
	for (int k = 1; k <= 14; ++k) {
		chess[k] = false;
	}
	int turn = getTurn();
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (chessPieces[i][j] == 0) continue;
			int color = (chessPieces[i][j] < 8) ? 0 : 1;
			if (chess[chessPieces[i][j]] == false && color == turn) {
				chess[chessPieces[i][j]] = true;
				generateMove(i, j, n, moveX, moveY);
				if (n > 0) {
					bCheckLoss = 0;
					return false;
				}
			}
		}
	}
	bCheckLoss = 1;
	return true;
}
/*
Function: isHitedPoint
Param:	- x,y : coord of mouse
		- posX, posY : position of board
*/
bool ChessBoard::isHitedPoint(int x, int y, int posX, int posY) {
	return checkPointInSquarev2(x, y, posX, posY, SIZECHESSPIECEX, SIZECHESSPIECEY);
}
bool ChessBoard::lossMove(int x, int y, int newX, int newY) {
	bool isBan = false;
	int originChessPiece = chessPieces[newX][newY];
	chessPieces[newX][newY] = chessPieces[x][y];
	chessPieces[x][y] = 0;
	int KingX = -1, KingY = -1;
	if (chessPieces[newX][newY] < 8) {
		//Find King
		for (int i = 0; i <= 2; ++i) {
			for (int j = 3; j <= 5; ++j) {
				if (chessPieces[i][j] == 5) {
					KingX = i;
					KingY = j;
					break;
				}
			}
			if (KingX >= 0 && KingY >= 0) {
				break;
			}
		}
		if (chessPieces[KingX + 1][KingY] == 8) {//Black Pawn
			isBan = true;
		}
	}
	else {
		// Find King
		for (int i = 7; i <= 9; ++i) {
			for (int j = 3; j <= 5; ++j) {
				if (chessPieces[i][j] == 12) {
					KingX = i;
					KingY = j;
					break;
				}
			}
			if (KingX >= 0 && KingY >= 0) {
				break;
			}
		}
		if (chessPieces[KingX - 1][KingY] == 1) {//Red Pawn
			isBan = true;
		}
	}
	if (chessPieces[KingX][KingY - 1] == 1 || chessPieces[KingX][KingY - 1] == 8) {//Pawn
		isBan = true;
	}
	if (chessPieces[KingX][KingY + 1] == 1 || chessPieces[KingX][KingY + 1] == 8) {//Pawn
		isBan = true;
	}
	for (int x = KingX - 1; x >= 0; --x) {
		if (chessPieces[x][KingY] != 0) {
			if (chessPieces[x][KingY] == 2 || chessPieces[x][KingY] == 9) {//pook
				if (!cmpColor(KingX, KingY, x, KingY)) {
					isBan = true;
				}
			}
			if (chessPieces[x][KingY] == 5 || chessPieces[x][KingY] == 12) {//king
				isBan = true;
			}
			for (int xx = x - 1; xx >= 0; --xx) {
				if (chessPieces[xx][KingY] != 0) {
					if (chessPieces[xx][KingY] == 3 || chessPieces[xx][KingY] == 10) {//canon
						if (!cmpColor(KingX, KingY, xx, KingY)) {
							isBan = true;
						}
					}
					break;
				}
			}
			break;
		}
	}
	for (int x = KingX + 1; x < 10; ++x) {
		if (chessPieces[x][KingY] != 0) {
			if (chessPieces[x][KingY] == 2 || chessPieces[x][KingY] == 9) {//pook
				if (!cmpColor(KingX, KingY, x, KingY)) {
					isBan = true;
				}
			}
			if (chessPieces[x][KingY] == 5 || chessPieces[x][KingY] == 12) {//king
				isBan = true;
			}
			for (int xx = x + 1; xx < 10; ++xx) {
				if (chessPieces[xx][KingY] != 0) {
					if (chessPieces[xx][KingY] == 3 || chessPieces[xx][KingY] == 10) {//canon
						if (!cmpColor(KingX, KingY, xx, KingY)) {
							isBan = true;
						}
					}
					break;
				}
			}
			break;
		}
	}
	for (int y = KingY - 1; y >= 0; --y) {
		if (chessPieces[KingX][y] != 0) {
			if (chessPieces[KingX][y] == 2 || chessPieces[KingX][y] == 9) {//pook
				if (!cmpColor(KingX, KingY, KingX, y)) {
					isBan = true;
				}
			}
			for (int yy = y - 1; yy >= 0; --yy) {
				if (chessPieces[KingX][yy] != 0) {
					if (chessPieces[KingX][yy] == 3 || chessPieces[KingX][yy] == 10) {//canon
						if (!cmpColor(KingX, KingY, KingX, yy)) {
							isBan = true;
						}
					}
					break;
				}
			}
			break;
		}
	}
	for (int y = KingY + 1; y < 9; ++y) {
		if (chessPieces[KingX][y] != 0) {
			if (chessPieces[KingX][y] == 2 || chessPieces[KingX][y] == 9) {//pook
				if (!cmpColor(KingX, KingY, KingX, y)) {
					isBan = true;
				}
			}
			for (int yy = y + 1; yy < 9; ++yy) {
				if (chessPieces[KingX][yy] != 0) {
					if (chessPieces[KingX][yy] == 3 || chessPieces[KingX][yy] == 10) {//canon
						if (!cmpColor(KingX, KingY, KingX, yy)) {
							isBan = true;
						}
					}
					break;
				}
			}
			break;
		}
	}
	for (int k = 0; k < 8; k++) {
		int xx = KingX + cKnightX[k];
		int yy = KingY + cKnightY[k];
		if (chessPieces[xx][yy] == 4 || chessPieces[xx][yy] == 11) {//knight
			if (!checkKnightMove(xx, yy, KingX, KingY)) {
				continue;
			}
			if (!cmpColor(KingX, KingY, xx, yy)) {
				isBan = true;
				break;
			}
		}
	}
	chessPieces[x][y] = chessPieces[newX][newY];
	chessPieces[newX][newY] = originChessPiece;
	return isBan;
}
void ChessBoard::drawGameStatus(sf::RenderWindow & window) {
	if (checkLoss()) {
		if (turn == 1) {
			window.draw(sLossStatus);
		}
		else {
			window.draw(sWinStatus);
		}
	}
}