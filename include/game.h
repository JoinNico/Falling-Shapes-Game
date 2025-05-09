#ifndef GAME_H
#define GAME_H

#include "character.h"
#include <time.h>

// 游戏区域大小
#define GAME_WIDTH 60
#define GAME_HEIGHT 20

// 最大同时下落物体数量
#define MAX_FALLING_OBJECTS 20

// 游戏时间限制(秒)
#define GAME_TIME_LIMIT 120

// 游戏状态结构体
typedef struct {
    Player player;                    // 玩家(三角形)
    FallingObject objects[MAX_FALLING_OBJECTS]; // 下落物体数组
    int activeObjects;               // 当前活跃的下落物体数量
    int score;                       // 游戏得分
    int frameCount;                  // 帧计数器，用于生成新物体的计时
    int isGameOver;                  // 游戏是否结束
    clock_t startTime;               // 游戏开始时间
    int timeRemaining;               // 剩余时间(秒)
} GameState;

void initGame(GameState* gameState);
void updateGame(GameState* gameState);
void checkCollisions(GameState* gameState);
void spawnNewObject(GameState* gameState);

#endif