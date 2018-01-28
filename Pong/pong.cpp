#include "pong.h"
using namespace std;

void Pong::updatePositions()
{
	//Apply controls to playerPosition
	playerPosition += playerVelocity;
	playerVelocity = 0;

	//Check for border/player -> change ball's velocity
	//Border
	if (ball->position.x == 0 || ball->position.x == boardWidth - 1)
		ball->velocity.x = -ball->velocity.x;

	if (ball->position.y == 0) //Only check y for upper
		ball->velocity.y = -ball->velocity.y;

	//Player
	if (ball->position.y == playerLine - 1) //so we bounce of before the player not in him
	{
		if (ball->position.x >= playerPosition && ball->position.x < playerPosition + playerWidth)
			ball->velocity.y = -ball->velocity.y;
	}

	if (ball->position.y >= boardHeight - 1) //Rip
		removeLive();

	//Apply velocity to ball
	ball->position.x += ball->velocity.x;
	ball->position.y -= ball->velocity.y; //Subtract cause of drawing method
}

void Pong::checkControls(int& timer)
{
	if (IsKeyDown(VK_LEFT))
	{
		if (playerPosition > 0) //Check if the border is next to the player
			playerVelocity = -1; //Not directly changing cause of timer delay
	}
	else if (IsKeyDown(VK_RIGHT))
	{
		if (playerPosition + playerWidth < boardWidth - 1) //Check if the border is next to the player
			playerVelocity = 1;
	}
#ifdef _DEBUG
	if (IsKeyDown(VK_CONTROL))
		timer = 1337;
#endif // _DEBUG
}

void Pong::removeLive()
{

	//Remove Live
	lives--;

	//Reset Ball
	ball = new PongBall;

	if (lives == 0)
		gameOver();
}

void Pong::gameOver()
{
	system("cls");
	cout << R"(#####################################################
#                                                   #
#       .::::                                       #
#     .:    .::                                     #
#    .::           .::    .::: .:: .::    .::       #
#    .::         .::  .::  .::  .:  .:: .:   .::    #
#    .::   .::::.::   .::  .::  .:  .::.::::: .::   #
#     .::    .: .::   .::  .::  .:  .::.:           #
#      .:::::     .:: .:::.:::  .:  .::  .::::      #
#                                                   #
#        .::::                                      #
#      .::    .::                                   #
#    .::        .::.::     .:: .::   .: .:::        #
#    .::        .:: .::   .::.:   .:: .::           #
#    .::        .::  .:: .::.::::: .::.::           #
#      .::     .::    .:.:: .:        .::           #
#        .::::         .::    .::::  .:::           #
#                                                   #
#####################################################
        )";

	running = false;
}

void Pong::init()
{
	playerPosition = boardWidth / 2 - playerWidth / 2;
	playerVelocity = 0;

	lives = 3;
	ball = new PongBall;
	running = true;
}

void Pong::run()
{
	static int timer = 0;
	if (timer > 10)
	{
		updatePositions();
		timer = 0;
	}
	timer++;
	draw();
	checkControls(timer);
}

void Pong::draw()
{
	if (!isRunning())
		return;

	system("cls");
	for (unsigned x = 0; x < boardWidth + 2; x++) //+2 to include the border
		cout << "-";
	cout << endl;

	for (unsigned y = 0; y < boardHeight; y++)
	{
		cout << "|";
		for (unsigned x = 0; x < boardWidth; x++)
		{
			if (y == playerLine) //Player
			{
				if (x >= playerPosition && x < playerPosition + playerWidth)
				{
					cout << "#";
				}
				else
					cout << " ";
			}
			else if (Vector(x, y) == ball->position) //Ball
				cout << "*";
			else
				cout << " ";
		}
		cout << "|";
		cout << endl;
	}

	for (unsigned x = 0; x < boardWidth + 2; x++)
		cout << "-";
	cout << endl;
}
