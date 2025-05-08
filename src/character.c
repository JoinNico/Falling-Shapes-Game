/**
 * character.c - 角色和物体实现
 */

#include "../include/character.h"
#include "../include/game.h"

// 移动玩家
void movePlayer(Player* player, int direction) {
    // 确保玩家不会移动出游戏区域边界
    int newX = player->x + direction;
    
    if (newX >= 1 && newX < GAME_WIDTH - 1) {
        player->x = newX;
    }
}