#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "character.h"
#include "render.h"
#include "utils.h"

// 游戏初始化
void initGame(GameState* gameState) {
    // 初始化玩家
    gameState->player.x = GAME_WIDTH / 2;
    gameState->player.y = GAME_HEIGHT - 1;

    // 初始化下落物体
    gameState->activeObjects = 0;
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        gameState->objects[i].isActive = 0;
    }

    // 初始化游戏状态
    gameState->score = 0;
    gameState->frameCount = 0;
    gameState->isGameOver = 0;

    // 初始化游戏时间
    gameState->startTime = clock();
    gameState->timeRemaining = GAME_TIME_LIMIT;

    // 生成初始下落物体
    for (int i = 0; i < 5; i++) {
        spawnNewObject(gameState);
    }
}

// 更新游戏状态
void updateGame(GameState* gameState) {
    gameState->frameCount++;

    // 计算剩余时间
    clock_t currentTime = clock();
    int elapsedSeconds = (currentTime - gameState->startTime) / CLOCKS_PER_SEC;
    gameState->timeRemaining = GAME_TIME_LIMIT - elapsedSeconds;

    // 检查时间是否用完
    if (gameState->timeRemaining <= 0) {
        gameState->timeRemaining = 0;
        gameState->isGameOver = 1;
        return;
    }

    // 每隔一定帧数生成新的下落物体
    if (gameState->frameCount % 20 == 0) {
        spawnNewObject(gameState);
    }

    // 更新所有下落物体的位置
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (gameState->objects[i].isActive) {
            // 根据速度更新位置
            if (gameState->frameCount % gameState->objects[i].speed == 0) {
                gameState->objects[i].y++;

                // 如果物体到达底部，移除它
                if (gameState->objects[i].y >= GAME_HEIGHT) {
                    gameState->objects[i].isActive = 0;
                    gameState->activeObjects--;
                }
            }
        }
    }

    // 检查碰撞
    checkCollisions(gameState);
}

// 检查碰撞并处理得分
void checkCollisions(GameState* gameState) {
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (gameState->objects[i].isActive) {
            // 检查是否与玩家发生碰撞
            if (gameState->objects[i].y == gameState->player.y &&
                gameState->objects[i].x >= gameState->player.x - 1 &&
                gameState->objects[i].x <= gameState->player.x + 1) {

                // 增加分数
                gameState->score += gameState->objects[i].points;

                // 移除下落物体
                gameState->objects[i].isActive = 0;
                gameState->activeObjects--;
            }
        }
    }
}

// 生成新的下落物体
void spawnNewObject(GameState* gameState) {
    // 如果已达到最大下落物体数量，则不生成
    if (gameState->activeObjects >= MAX_FALLING_OBJECTS) {
        return;
    }

    // 寻找空闲的下落物体槽位
    int index = -1;
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (!gameState->objects[i].isActive) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // 随机选择形状类型 (0-4)
        int shapeType = rand() % 5;

        // 随机选择速度 (1-3)，数字越小速度越快
        int speed = rand() % 3 + 1;

        // 根据形状类型设置点数
        int points;
        switch (shapeType) {
            case 0: points = 10; break;  // 星形
            case 1: points = 20; break;  // 方形
            case 2: points = 30; break;  // 圆形
            case 3: points = 40; break;  // 菱形
            case 4: points = 50; break;  // 十字形
            default: points = 10;
        }

        // 随机x位置，确保在游戏区域内
        int x = rand() % (GAME_WIDTH - 2) + 1;

        // 设置下落物体属性
        gameState->objects[index].isActive = 1;
        gameState->objects[index].type = shapeType;
        gameState->objects[index].x = x;
        gameState->objects[index].y = 0;
        gameState->objects[index].speed = speed;
        gameState->objects[index].points = points;

        gameState->activeObjects++;
    }
}