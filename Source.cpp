/*
Author: Quan Luong
Project: Chinese Chess
*/
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<stdio.h>
#include<iostream>
#include"ChessBoard.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Co tuong");
	ChessBoard board;

	//initial
	board.setTurn(0);
	board.init();
	window.clear();
	board.draw(window);
	window.display();
	sf::Vector2u lastMove;
	int n;
	int moveX[100], moveY[100];
	bool continueGame = true;

	while (window.isOpen() && continueGame) {
		if (board.checkLoss()) {
			window.clear();
			board.draw(window);
			board.drawGameStatus(window);
			window.display();
			for (;;);
			break;
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed: {
					window.close();
				}
				case sf::Event::MouseMoved: {
					lastMove.x = event.mouseMove.x;
					lastMove.y = event.mouseMove.y;
				}
				case sf::Event::MouseButtonPressed: {
					if (event.mouseButton.button == sf::Mouse::Button::Left) {
						if (event.mouseButton.x < 0 || event.mouseButton.y < 0) {
							break;
						}
						int posI, posJ;
						board.getChoosedChessPiece(posI, posJ);
						if (posI >= 0 && posJ >= 0) {
							board.generateMove(posI, posJ, n, moveX, moveY);
							int hitedX = -1;
							int hitedY = -1;
							for (int i = 0; i < n; ++i) {
								if (board.isHitedPoint(event.mouseButton.x, event.mouseButton.y, moveX[i], moveY[i])) {
									hitedX = moveX[i];
									hitedY = moveY[i];
									break;
								}
							}
							if (hitedX >= 0 && hitedY >= 0) {
								board.moveChessPiece(posI, posJ, hitedX, hitedY);
								board.setChoosedChessPiece(-1, -1);
								window.clear();
								board.draw(window);
								window.display();
								break;
							}
						}
						int hitedChessPiece = board.checkHitChessPiece(event.mouseButton.x, event.mouseButton.y,posI,posJ);
						if (hitedChessPiece > 0 && ((hitedChessPiece>=8)==board.getTurn())) {
							board.setChoosedChessPiece(posI, posJ);

							window.clear();
							board.draw(window);
							board.generateMove(window, posI, posJ,n,moveX,moveY);
							window.display();
						}
						else {
							board.setChoosedChessPiece(-1, -1);
							window.clear();
							board.draw(window);
							window.display();
						}
						break;
					}
					if (event.mouseButton.button == sf::Mouse::Button::Right) {
						if (event.mouseButton.x < 0 || event.mouseButton.y < 0) {
							break;
						}
						board.undoMove();
						board.setChoosedChessPiece(-1,-1);
						window.clear();
						board.draw(window);
						window.display();
					}
				}
			}
		}
	}
	return 0;
}