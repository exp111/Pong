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
	if (ball->position.y - ball->velocity.y == playerLine) //so we bounce of before the player not in him
	{
		if (ball->position.x + ball->velocity.x >= playerPosition && ball->position.x + ball->velocity.x < playerPosition + playerWidth)
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
	if (isKeyDown(VK_LEFT))
	{
		if (playerPosition > 0) //Check if the border is next to the player
			playerVelocity = -1; //Not directly changing cause of timer delay
	}
	else if (isKeyDown(VK_RIGHT))
	{
		if (playerPosition + playerWidth < boardWidth - 1) //Check if the border is next to the player
			playerVelocity = 1;
	}
#ifdef _DEBUG
	if (isKeyDown(VK_CONTROL))
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
	if (isRunning())
	{
		if (timer > 10)
		{
			updatePositions();
			timer = 0;
		}
		timer++;
		draw();
		checkControls(timer);
	}
}

void Pong::drawFilledRect(ImDrawList* drawlist, unsigned x, unsigned y, ImVec4 color)
{
	ImVec2 winpos = ImGui::GetWindowPos();
	const static float titleBarHeight = ImGui::GetTextLineHeight() + ImGui::GetStyle().FramePadding.y * 2.0f;
	drawlist->AddRectFilled(ImVec2(winpos.x + x * tileWidth, winpos.y + titleBarHeight + y * tileHeight), ImVec2(winpos.x + (x + 1)*tileWidth, winpos.y + titleBarHeight + (y + 1)*tileHeight), ImGui::GetColorU32(color));
}

void Pong::draw()
{
	ImGui::Begin("Pong");
	const static float titleBarHeight = ImGui::GetTextLineHeight() + ImGui::GetStyle().FramePadding.y * 2.0f;
	ImGui::SetWindowSize(ImVec2(boardWidth * tileWidth, boardHeight * tileHeight + titleBarHeight));

	ImDrawList* drawList = ImGui::GetWindowDrawList();

	for (unsigned y = 0; y < boardHeight; y++)
	{
		for (unsigned x = 0; x < boardWidth; x++)
		{
			if (y == playerLine) //Player
			{
				if (x >= playerPosition && x < playerPosition + playerWidth)
				{
					drawFilledRect(drawList, x, y, ImVec4(255, 255, 255, 255));
				}
				else
					drawFilledRect(drawList, x, y, ImVec4(0, 0, 0, 255));
			}
			else if (Vector(x, y) == ball->position) //Ball
				drawFilledRect(drawList, x, y, ImVec4(255, 255, 255, 255));
			else
				drawFilledRect(drawList, x, y, ImVec4(0, 0, 0, 255));
		}
	}

	ImGui::End();
}
