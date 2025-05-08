#ifndef CHARACTER_H
#define CHARACTER_H

// 玩家(三角形)结构体
typedef struct {
    int x;  // x坐标
    int y;  // y坐标
} Player;

// 下落物体结构体
typedef struct {
    int isActive;  // 是否活跃 即下落物体数组中是否存在元素 0-否 1-是
    int type;      // 形状类型 0-星形, 1-方形, 2-圆形, 3-菱形, 4-十字形
    int x;         // x坐标
    int y;         // y坐标
    int speed;     // 下落速度 1至3 1-最快 3-最慢
    int points;    // 碰撞得分
} FallingObject;

void movePlayer(Player* player, int direction); // direction: -1=左, 1=右

#endif