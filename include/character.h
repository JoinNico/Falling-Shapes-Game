/**
 * character.h - 角色和物体定义
 */

#ifndef CHARACTER_H
#define CHARACTER_H

// 玩家(三角形)结构体
typedef struct {
    int x;  // x坐标
    int y;  // y坐标
} Player;

// 下落物体结构体
typedef struct {
    int isActive;  // 是否活跃
    int type;      // 形状类型：0=星形, 1=方形, 2=圆形, 3=菱形, 4=十字形
    int x;         // x坐标
    int y;         // y坐标
    int speed;     // 下落速度（1-3，1最快，3最慢）
    int points;    // 碰撞得分
} FallingObject;

// 移动玩家
void movePlayer(Player* player, int direction); // direction: -1=左, 1=右

#endif // CHARACTER_H