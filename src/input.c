#include <windows.h>
#include <conio.h>
#include "../include/input.h"
#include "../include/character.h"
#include "../include/game.h"

// 处理用户输入
void processInput(GameState* gameState) {
    // 检查是否有按键按下
    if (_kbhit()) {
        int key = _getch();
        
        // 检查是否为方向键
        if (key == 0 || key == 224) {  // 方向键的前缀
            key = _getch();  // 获取方向键的实际值
            
            switch (key) {
                case 75:  // 左箭头
                    movePlayer(&gameState->player, -1);
                    break;
                case 77:  // 右箭头
                    movePlayer(&gameState->player, 1);
                    break;
            }
        }
        // 检查ESC键 (退出游戏)
        else if (key == 27) {  // ESC键
            gameState->isGameOver = 1;
        }
    }
}