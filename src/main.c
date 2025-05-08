#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "../include/game.h"
#include "../include/character.h"
#include "../include/render.h"
#include "../include/input.h"
#include "../include/utils.h"

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
        
        // 渲染游戏
        clearScreen();
        renderGame(&gameState);
        
        // 帧率控制
        Sleep(50);  // 约20帧每秒
    }
    
    // 游戏结束
    clearScreen();
    showGameOver(gameState.score);
    
    // 恢复控制台设置
    restoreConsole();
    
    return 0;
}
