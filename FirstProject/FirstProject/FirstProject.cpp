// FirstProject.cpp : Defines the entry point for the console application.
//------------------------------------------------------------------
// File name:   FirstProject.cpp
// Program ID:  PONG in C++
// Complete Date:    09/11/2017
//
// Purpose:     Based off a tutorial, it helps me become more comfortable with the C++
//				standards of coding! Also, creatinga game using a different form of logic.
//				Being exposed to new solving factors.
//
// Author:      jmckinley Jonathan McKinley
//
//------------------------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

//Determines the direction for the Ball
enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

//Manages the Ball
class cBall
{
private:
	int x, y;
	int originalX = 0, originalY = 0;
	eDir direction;
public:
	cBall(int posX, int posY) {
		originalX = posX;
		originalY = posY;
		x = posX; y = posY;
		direction = STOP;
	}
	//Reset position of ball
	void Reset() {
		x = originalX; y = originalY;
		direction = STOP;
	}
	//Change direction of ball
	void changeDirection(eDir d) {
		direction = d;
	}
	//Puts ball in a random direction
	void randomDirection() {
		direction = (eDir)((rand() % 6) + 1);
	}

	//Get current X of ball
	int getX() { return x; }

	//Get current Y of ball
	int getY() { return y; }

	//Gets the direction of the ball
	inline eDir getDirection() { return direction; }

	//Moves the ball based on current direction
	void Move() {
		switch (direction) {
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--; y--;
			break;
		case DOWNLEFT:
			x--; y++;
			break;
		case UPRIGHT:
			x++; y--;
			break;
		case DOWNRIGHT:
			x++; y++;
			break;
		default:
			break;
		}
	}

	//Handles the cout operation for Ball
	friend ostream & operator<<(ostream & o, cBall c) {
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
		return o;
	}
};

//Manages the Paddle for player1 and player2
class cPaddle {
private:
	int x, y;
	int originalX, originalY;
public:
	cPaddle() {
		x = y = 0;
	}
	cPaddle(int posX, int posY) : cPaddle() {
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}

	//Reset the position of paddle
	inline void Reset() {
		x = originalX; y = originalY;
	}

	//Get current X value of paddle
	inline int getX() { return x; }

	//Get current Y value of paddle
	inline int getY() { return y; }

	//Move PaddleUp
	inline void moveUp() { y = y - 2; }

	//Move PaddleDown
	inline void moveDown() { y = y + 2; }

	//Handles the cout operation for Paddle
	friend ostream & operator<<(ostream & o, cPaddle c) {
		o << "Paddle [" << c.x << "," << c.y << "]";
			return o;
	}
};

//Manages general operations and settings of game
class cGameManager {
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	cBall *ball;
	cPaddle *player1;
	cPaddle *player2;
public:
	cGameManager(int w, int h) {
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w; height = h;
		ball = new cBall(w/2, h/2);
		player1 = new cPaddle(1, h/2 - 3);
		player2 = new cPaddle(w-2, h/2 - 3);
	}
	~cGameManager() {
		delete ball, player1, player2;
	}
	void ScoreUp(cPaddle *player) {
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;

		ball->Reset();
		player1->Reset();
		player2->Reset();
	}
	void Draw() {
		system("cls");

		//Wall
		for (int i = 0; i < width + 2; i++) {
			cout << "\xB2";
		}


		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player2x = player2->getX();
				int player1y = player1->getY();
				int player2y = player2->getY();

				//Creates the edge wall
				if (j == 0) 
					cout << "\xB2";

				if (ballx == j && bally == i)
					cout << "O"; //ball
				else if (player1x == j && player1y == i)
					cout << "\xDB"; // player1
				else if (player2x == j && player2y == i)
					cout << "\xDB"; //player2
				else if (player1x == j && player1y + 1 == i)
					cout << "\xDB"; // player1
				else if (player1x == j && player1y + 2 == i)
					cout << "\xDB"; // player1
				else if (player1x == j && player1y + 3 == i)
					cout << "\xDB"; // player1
				else if (player2x == j && player2y + 1 == i)
					cout << "\xDB"; // player1
				else if (player2x == j && player2y + 2 == i)
					cout << "\xDB"; // player1
				else if (player2x == j && player2y + 3 == i)
					cout << "\xDB"; // player1
				else
					cout << " ";

				//Creates the edge wall
				if (j == width - 1)
					cout << "\xB2";

			}

			cout << endl;
		}

		cout << endl;

		//Wall
		for (int i = 0; i < width + 2; i++) {
			cout << "\xB2";
		}

		cout << endl;

		cout << endl << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
	}
	void Input() {
		ball->Move();

		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();


		//Keyboard input
		if (_kbhit()) {
			char current = _getch();

			if (current == up1)
				if (player1y > 0)
					player1->moveUp();
			if (current == up2)
				if (player2y > 0)
					player2->moveUp();
			if (current == down1)
				if (player1y + 4 < height)
					player1->moveDown();
			if (current == down2)
				if (player2y + 4 < height)
					player2->moveDown();

			if (ball->getDirection() == STOP)
				ball->randomDirection();

			if (current == 'q')
				quit = true;
		}
	}

	void logic() {
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

		//left paddle
		for (int i = 0; i < 4; i++) {
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->changeDirection((eDir)((rand() % 3) + 4));
		}

		//right paddle
		for (int i = 0; i < 4; i++) 
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->changeDirection((eDir)((rand() % 3) + 1));
		
		//bottom wall
		if (bally == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		//top wall
		if (bally == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		//right wall
		if (ballx == width - 1)
			ScoreUp(player1);
		//left wall
		if (ballx == 0)
			ScoreUp(player2);
	}
	void Run() {
		while (!quit) {
			Draw();
			Input();
			logic();
		}
	}
};

int main()
{
	cGameManager c(40, 30); //Manages the settings for game
	c.Run(); 

	
	return 0;
}