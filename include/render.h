/**
 * render.h - 图形输出函数
 */

#ifndef RENDER_H
#define RENDER_H

#include "game.h"

// 初始化控制台
void initConsole();

// 恢复控制台设置
void restoreConsole();

// 清除屏幕
void clearScreen();

// 渲染游戏
void renderGame(GameState* gameState);

// 绘制游戏边界
void drawBorder();

// 绘制玩家(三角形)
void drawPlayer(Player* player);

// 绘制下落物体
void drawFallingObject(FallingObject* object);

// 绘制分数
void drawScore(int score);

#endif // RENDER_H