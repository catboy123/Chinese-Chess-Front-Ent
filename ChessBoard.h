#ifndef ChessBoard_H
#define ChessBoard_H
#pragma once
#define NOMINMAX
#include<windows.h>
#include<stdio.h>
#include<iostream>
#include<limits>
#include<string.h>
#include<stack>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
using namespace std;
class MoveStruct {
public:
	int sChessPiece, sX, sY; // start
	int dX, dY, dChessPiece; // destination
	MoveStruct(int _sChessPiece, int _sX, int _sY, int _dX, int _dY, int _dChessPiece) {
		sChessPiece = _sChessPiece;
		sX = _sX;
		sY = _sY;
		dX = _dX;
		dY = _dY;
		dChessPiece = _dChessPiece;
	}/*
	moveStruct newStruct(int _sChessPiece, int _sX, int _sY, int _dX, int _dY, int _dChessPiece) {
		moveStruct tmp(_sChessPiece, _sX, _sY, _dX, _dY, _dChessPiece);
		return tmp;
	}*/
}; 
class ChessBoard {
private:
	int bCheckLoss = -1;
	int turn; // 0 - black or 1 - red
	sf::Texture boardTexture;
	sf::Texture iconTexture;
	sf::Texture gameStatusTexture;
	sf::Sprite sBoard, sChessPiece[20], sBlackChoosedChessPiece, sRedChoosedChessPiece, sLightCircle;
	sf::Sprite sBlackPreviousMove, sRedPreviousMove;
	sf::Sprite sWinStatus, sDrawStatus, sLossStatus;
	int chessPieces[15][15];//9x10
	int chessPieceX[15] = { 36 , 94 , 150, 205, 261, 319, 374, 429, 482 };
	int chessPieceY[15] = { 49 , 104 , 160, 212, 271, 326, 382, 435, 491, 549 };
	const int cBishopX[2] = { -2, 2 };
	const int cBishopY[2] = { -2 ,2 };
	const int cKnightX[8] = { -2,-2,-1,-1, 1, 1, 2, 2 };
	const int cKnightY[8] = { -1, 1,-2, 2,-2, 2,-1, 1 };
	const int cKingX[4] = { -1,1, 0,0 };
	const int cKingY[4] = { 0,0,-1,1 };
	const int cGuardX[2] = { -1,1 };
	const int cGuardY[2] = { 1,-1 };
	sf::Vector2i choosedChessPiece;
	stack<MoveStruct> history;
	bool checkKnightMove(int x, int y, int newX, int newY);
	/*
	Function: checkPointInSquare
	Param:	- x,y: coord of point
			- i,j: point (i,j) of chessPieces
			- width, height: size of square
	Return: - true: (x,y) in circle origin chessPiece[i][j] with raidus width/2
			- false: else
	*/
	bool checkPointInSquarev2(int x, int y, int i, int j, int width, int height);
	bool checkPointInSquare(int x, int y, int i, int j, int width, int height);
	/*
	Function cmpColor
	Purpose: Check if chessBoards[x1][y1] and chessBoards[x2][y2] is same color
	*/
	bool cmpColor(int x1, int y1, int x2, int y2);
	/*
	Function: sign
	Return: -1 if k<0
			1 if k>0
			0 if k=0
	*/
	int sign(int k);
	/*
	Function: isEmpty
	Purpose: Check if position of (x,y) in board is empty
	*/
	bool isEmpty(int x, int y);
public:
	ChessBoard(void);
	void init(void);
	int getTurn(void);
	void setTurn(int t);
	static string getNameChessPiece(int k);
	void draw(sf::RenderWindow& window, sf::Sprite& sprite, int i, int j);
	void draw(sf::RenderWindow& window);
	int checkHitChessPiece(int x, int y, int& res_i, int& res_j);
	void setChoosedChessPiece(int x, int y);
	void getChoosedChessPiece(int& x, int& y);
	void generateMove(int x, int y, int& n, int moveX[], int moveY[]);
	void generateMove(sf::RenderWindow& window, int x, int y, int& n, int moveX[], int moveY[]);
	void moveChessPiece(int originX, int originY, int desX, int desY);
	void undoMove(void);
	bool checkLoss(void);
	bool isHitedPoint(int x, int y, int posX, int posY);
	bool lossMove(int x, int y, int newX, int newY);
	void drawGameStatus(sf::RenderWindow& window);
};

#endif
