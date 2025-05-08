#include <stdio.h>
#include <windows.h>
#include "../include/render.h"
#include "../include/game.h"
#include "../include/utils.h"

// 原始控制台属性，用于游戏结束后的终端恢复
HANDLE hConsole;
CONSOLE_CURSOR_INFO originalCursorInfo;
CONSOLE_SCREEN_BUFFER_INFO originalScreenInfo;

// 初始化控制台
void initConsole() {
    // 获取控制台句柄
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // 隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &originalCursorInfo);
    cursorInfo.dwSize = 1;//光标的大小 1%
    cursorInfo.bVisible = FALSE;//光标是否可见 false-否 true-是
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    
    // 保存原始屏幕信息
    GetConsoleScreenBufferInfo(hConsole, &originalScreenInfo);
    
    // 设置控制台窗口大小
    COORD bufferSize = {GAME_WIDTH + 10, GAME_HEIGHT + 5};
    SMALL_RECT windowSize = {0, 0, GAME_WIDTH + 9, GAME_HEIGHT + 4};
    
    SetConsoleScreenBufferSize(hConsole, bufferSize);
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    clearScreen();
}

// 恢复控制台设置
void restoreConsole() {
    // 恢复光标可见性
    SetConsoleCursorInfo(hConsole, &originalCursorInfo);
    // 恢复颜色
    SetConsoleTextAttribute(hConsole, originalScreenInfo.wAttributes);
}

// 清除屏幕
void clearScreen() {
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;//控制台屏幕缓冲区信息 结构体类型的变量名缩写
    DWORD dwConSize;
    
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y; //计算需要清除的字符总数
    
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    
    SetConsoleCursorPosition(hConsole, coordScreen);
}

// 渲染游戏画面
void renderGame(GameState* gameState) {
    drawBorder();
    // 绘制所有活跃的下落物体
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (gameState->objects[i].isActive) {
            drawFallingObject(&gameState->objects[i]);
        }
    }
    drawPlayer(&gameState->player);
    drawScore(gameState->score);
}

// 绘制游戏边界
void drawBorder() {
    // 设置边界颜色
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    
    // 绘制上边界
    for (int x = 0; x < GAME_WIDTH; x++) {
        gotoxy(x, 0);
        printf("=");
    }
    
    // 绘制下边界
    for (int x = 0; x < GAME_WIDTH; x++) {
        gotoxy(x, GAME_HEIGHT);
        printf("=");
    }
    
    // 绘制左边界
    for (int y = 0; y <= GAME_HEIGHT; y++) {
        gotoxy(0, y);
        printf("|");
    }
    
    // 绘制右边界
    for (int y = 0; y <= GAME_HEIGHT; y++) {
        gotoxy(GAME_WIDTH - 1, y);
        printf("|");
    }
    
    // 恢复默认颜色
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// 绘制玩家(三角形)
void drawPlayer(Player* player) {
    // 设置红色
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    
    // 绘制三角形
    gotoxy(player->x, player->y);
    printf("^");
    gotoxy(player->x - 1, player->y);
    printf("/");
    gotoxy(player->x + 1, player->y);
    printf("\\");
    
    // 恢复默认颜色
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// 绘制下落物体
void drawFallingObject(FallingObject* object) {
    switch (object->type) {
        case 0: // 星形 - 黄色
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case 1: // 方形 - 绿色
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case 2: // 圆形 - 青色
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case 3: // 菱形 - 紫色
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case 4: // 十字形 - 白色
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
    }
    
    // 绘制不同下落形状
    gotoxy(object->x, object->y);
    switch (object->type) {
        case 0: printf("*"); break;  // 星形
        case 1: printf("#"); break;  // 方形
        case 2: printf("O"); break;  // 圆形
        case 3: printf("<>"); break; // 菱形
        case 4: printf("+"); break;  // 十字形
    }
    
    // 恢复默认颜色
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// 绘制分数和游戏提示
void drawScore(int score) {
    gotoxy(GAME_WIDTH + 2, 2);
    printf("分数: %d", score);
    
    gotoxy(GAME_WIDTH + 2, 4);
    printf("控制说明:");
    
    gotoxy(GAME_WIDTH + 2, 5);
    printf("左箭头 - 向左移动");
    
    gotoxy(GAME_WIDTH + 2, 6);
    printf("右箭头 - 向右移动");
    
    gotoxy(GAME_WIDTH + 2, 7);
    printf("ESC - 退出游戏");
    
    gotoxy(GAME_WIDTH + 2, 9);
    printf("形状得分:");
    
    gotoxy(GAME_WIDTH + 2, 10);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("* - 10分");
    
    gotoxy(GAME_WIDTH + 2, 11);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("# - 20分");
    
    gotoxy(GAME_WIDTH + 2, 12);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("O - 30分");
    
    gotoxy(GAME_WIDTH + 2, 13);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("<> - 40分");
    
    gotoxy(GAME_WIDTH + 2, 14);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("+ - 50分");
    
    // 恢复默认颜色
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}