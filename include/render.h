#ifndef RENDER_H
#define RENDER_H

#include "game.h"

void initConsole();
void restoreConsole();
void clearScreen();
void renderGame(GameState* gameState);

void drawBorder();
void drawPlayer(Player* player);
void drawFallingObject(FallingObject* object);
void drawScore(int score);

#endif