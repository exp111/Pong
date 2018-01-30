#pragma once

#include <Windows.h>
#include <vector>
#include <iostream>

#include "main.h"
#include "imgui/imgui.h"

class Vector
{
public:
	Vector() : x{ 0 }, y{ 0 } {};
	Vector(int setX, int setY) : x{ setX }, y{ setY } {};
	int x;
	int y;

	bool operator==(Vector& vec)
	{
		return vec.x == x && vec.y == y;
	}
};

class PongBall
{
public:
	PongBall() : position{ Vector(boardWidth / 2, boardHeight / 2) } 
	{ 
		int r = rand() % 4;
		switch (r)
		{
		case 0:
			velocity = Vector(-1, 1);
			break;
		case 1:
			velocity = Vector(1, 1);
			break;
		case 2:
			velocity = Vector(-1, -1);
			break;
		case 3:
			velocity = Vector(1, -1);
			break;
		}
	};

	Vector position;
	Vector velocity;
};
class Pong
{
public:
	void updatePositions();
	void checkControls(int& timer);

	void removeLive();
	void gameOver();

	bool isRunning()
	{
		return running;
	}

	//Draw and stuff
	void init();
	void run();
	void drawFilledRect(ImDrawList* drawlist, unsigned x, unsigned y, ImVec4 color);
	void draw();

private:
	unsigned lives;
	unsigned playerPosition;
	int playerVelocity; //Only one dimension cause we only move in x direction (left/right)
	PongBall* ball;
	bool running = false;
};