/**
 * main.c - 程序入口和主循环
 * 下落形状捕捉游戏
 */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "game.h"
#include "character.h"
#include "render.h"
#include "input.h"
#include "utils.h"

int main() {
    //设置控制台输出为 UTF-8 编码
    SetConsoleOutputCP(65001);

    // 初始化随机数种子
    srand((unsigned int)time(NULL));

    // 初始化控制台
    initConsole();

    // 初始化游戏
    GameState gameState;
    initGame(&gameState);

    // 主游戏循环
    while (!gameState.isGameOver) {
        // 处理输入
        processInput(&gameState);

        // 更新游戏状态
        updateGame(&gameState);

        // 使用双缓冲渲染游戏（无需额外清屏，clearBuffer已集成在renderGame中）
        renderGame(&gameState);

        // 帧率控制
        Sleep(50);  // 约20帧每秒
    }

    // 游戏结束
    showGameOver(gameState.score);

    // 恢复控制台设置
    restoreConsole();

    return 0;
}