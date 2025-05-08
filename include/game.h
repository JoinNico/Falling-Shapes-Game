/**
 * game.h - 游戏规则和状态定义
 */

#ifndef GAME_H
#define GAME_H

#include "character.h"

// 游戏区域大小
#define GAME_WIDTH 60
#define GAME_HEIGHT 20

// 最大同时下落物体数量
#define MAX_FALLING_OBJECTS 20

// 游戏状态结构体
typedef struct {
    Player player;                    // 玩家(三角形)
    FallingObject objects[MAX_FALLING_OBJECTS]; // 下落物体数组
    int activeObjects;               // 当前活跃的下落物体数量
    int score;                       // 游戏得分
    int frameCount;                  // 帧计数器，用于生成新物体的计时
    int isGameOver;                  // 游戏是否结束
} GameState;

// 游戏初始化
void initGame(GameState* gameState);

// 更新游戏状态
void updateGame(GameState* gameState);

// 检查碰撞并处理得分
void checkCollisions(GameState* gameState);

// 生成新的下落物体
void spawnNewObject(GameState* gameState);

// 游戏结束界面
void showGameOver(int score);

#endif // GAME_H