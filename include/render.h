#ifndef RENDER_H
#define RENDER_H

#include "game.h"
#include <windows.h>

// 控制台缓冲区信息
typedef struct {
    CHAR_INFO* buffer;        // 缓冲区数据
    COORD bufferSize;         // 缓冲区大小
    COORD bufferCoord;        // 缓冲区坐标
    SMALL_RECT writeRegion;   // 写入区域
} ScreenBuffer;

void initConsole();
void restoreConsole();
void clearBuffer();
void flushBuffer();
void renderGame(GameState* gameState);
void drawBorder();
void drawPlayer(Player* player);
void drawFallingObject(FallingObject* object);
void drawScore(int score);
void drawTime(int timeRemaining);
void showGameOver(int score);
void writeToBuffer(int x, int y, char ch, WORD attributes);
void writeWCharToBuffer(int x, int y, WCHAR ch, WORD attributes);  // 新增宽字符函数
void writeStringToBuffer(int x, int y, const char* str, WORD attributes);

#endif