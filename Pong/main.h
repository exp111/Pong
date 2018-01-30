#pragma once

#define isKeyDown(x) GetKeyState(x) & 0x8000

const unsigned boardWidth = 30, boardHeight = 25;
const unsigned playerWidth = 4;
const unsigned playerLine = boardHeight - 3;
const unsigned tileWidth = 10, tileHeight = 10;