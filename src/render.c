#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <wchar.h>  // 添加宽字符支持
#include "render.h"
#include "game.h"
#include "utils.h"

// 控制台句柄和原始设置
HANDLE hConsole;
HANDLE hConsoleOutput;
CONSOLE_CURSOR_INFO originalCursorInfo;
CONSOLE_SCREEN_BUFFER_INFO originalScreenInfo;

// 双缓冲相关变量
ScreenBuffer screenBuffer;

// 初始化控制台和双缓冲
void initConsole() {
    // 获取控制台句柄
    hConsole = GetStdHandle(STD_INPUT_HANDLE);
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // 设置控制台代码页为UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // 设置控制台字体
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 16;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"新宋体"); // 使用支持中文的字体
    SetCurrentConsoleFontEx(hConsoleOutput, FALSE, &cfi);

    // 隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsoleOutput, &originalCursorInfo);
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsoleOutput, &cursorInfo);

    // 保存原始屏幕信息
    GetConsoleScreenBufferInfo(hConsoleOutput, &originalScreenInfo);

    // 设置控制台窗口大小和缓冲区大小
    COORD bufferSize = {GAME_WIDTH + 30, GAME_HEIGHT + 5};
    SMALL_RECT windowSize = {0, 0, GAME_WIDTH + 29, GAME_HEIGHT + 4};

    SetConsoleScreenBufferSize(hConsoleOutput, bufferSize);
    SetConsoleWindowInfo(hConsoleOutput, TRUE, &windowSize);

    // 初始化双缓冲区
    screenBuffer.bufferSize.X = GAME_WIDTH + 30;
    screenBuffer.bufferSize.Y = GAME_HEIGHT + 5;
    screenBuffer.buffer = (CHAR_INFO*)malloc(
            sizeof(CHAR_INFO) * screenBuffer.bufferSize.X * screenBuffer.bufferSize.Y
    );
    screenBuffer.bufferCoord.X = 0;
    screenBuffer.bufferCoord.Y = 0;
    screenBuffer.writeRegion.Left = 0;
    screenBuffer.writeRegion.Top = 0;
    screenBuffer.writeRegion.Right = screenBuffer.bufferSize.X - 1;
    screenBuffer.writeRegion.Bottom = screenBuffer.bufferSize.Y - 1;

    // 清除缓冲区
    clearBuffer();
    flushBuffer();
}

// 恢复控制台设置
void restoreConsole() {
    // 恢复光标可见性
    SetConsoleCursorInfo(hConsoleOutput, &originalCursorInfo);

    // 恢复颜色
    SetConsoleTextAttribute(hConsoleOutput, originalScreenInfo.wAttributes);

    // 释放缓冲区内存
    free(screenBuffer.buffer);
}

// 清除缓冲区
void clearBuffer() {
    CHAR_INFO clearChar;
    clearChar.Char.UnicodeChar = L' ';  // 使用UnicodeChar而不是AsciiChar
    clearChar.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    // 填充整个缓冲区为空格字符
    for (int i = 0; i < screenBuffer.bufferSize.X * screenBuffer.bufferSize.Y; i++) {
        screenBuffer.buffer[i] = clearChar;
    }
}

// 将缓冲区内容刷新到屏幕
void flushBuffer() {
    WriteConsoleOutputW(  // 使用WriteConsoleOutputW而不是WriteConsoleOutput
            hConsoleOutput,
            screenBuffer.buffer,
            screenBuffer.bufferSize,
            screenBuffer.bufferCoord,
            &screenBuffer.writeRegion
    );
}

// 在缓冲区指定位置写入字符
void writeToBuffer(int x, int y, char ch, WORD attributes) {
    // 检查坐标是否在有效范围内
    if (x < 0 || x >= screenBuffer.bufferSize.X || y < 0 || y >= screenBuffer.bufferSize.Y) {
        return;
    }

    // 计算缓冲区索引
    int index = y * screenBuffer.bufferSize.X + x;

    // 将字符和属性写入缓冲区
    screenBuffer.buffer[index].Char.UnicodeChar = (WCHAR)ch;  // 转换为宽字符
    screenBuffer.buffer[index].Attributes = attributes;
}

// 在缓冲区指定位置写入宽字符
void writeWCharToBuffer(int x, int y, WCHAR ch, WORD attributes) {
    // 检查坐标是否在有效范围内
    if (x < 0 || x >= screenBuffer.bufferSize.X || y < 0 || y >= screenBuffer.bufferSize.Y) {
        return;
    }

    // 计算缓冲区索引
    int index = y * screenBuffer.bufferSize.X + x;

    // 将字符和属性写入缓冲区
    screenBuffer.buffer[index].Char.UnicodeChar = ch;
    screenBuffer.buffer[index].Attributes = attributes;
}

// 在缓冲区指定位置写入字符串
void writeStringToBuffer(int x, int y, const char* str, WORD attributes) {
    // 转换为宽字符串
    int length = strlen(str);
    wchar_t* wstr = (wchar_t*)malloc(sizeof(wchar_t) * (length + 1));

    // 转换UTF-8字符串为宽字符串
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, length + 1);

    // 写入宽字符串
    for (int i = 0; wstr[i] != L'\0'; i++) {
        writeWCharToBuffer(x + i, y, wstr[i], attributes);
    }

    free(wstr);
}

// 渲染游戏
void renderGame(GameState* gameState) {
    // 清除缓冲区
    clearBuffer();

    // 绘制边界
    drawBorder();

    // 绘制所有活跃的下落物体
    for (int i = 0; i < MAX_FALLING_OBJECTS; i++) {
        if (gameState->objects[i].isActive) {
            drawFallingObject(&gameState->objects[i]);
        }
    }

    // 绘制玩家(三角形)
    drawPlayer(&gameState->player);

    // 绘制分数
    drawScore(gameState->score);

    // 将缓冲区内容刷新到屏幕
    flushBuffer();
}

// 绘制游戏边界
void drawBorder() {
    // 设置边界颜色
    WORD borderColor = FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    // 绘制上边界
    for (int x = 0; x < GAME_WIDTH; x++) {
        writeToBuffer(x, 0, '=', borderColor);
    }

    // 绘制下边界
    for (int x = 0; x < GAME_WIDTH; x++) {
        writeToBuffer(x, GAME_HEIGHT, '=', borderColor);
    }

    // 绘制左边界
    for (int y = 0; y <= GAME_HEIGHT; y++) {
        writeToBuffer(0, y, '|', borderColor);
    }

    // 绘制右边界
    for (int y = 0; y <= GAME_HEIGHT; y++) {
        writeToBuffer(GAME_WIDTH - 1, y, '|', borderColor);
    }
}

// 绘制玩家(三角形)
void drawPlayer(Player* player) {
    // 设置红色
    WORD playerColor = FOREGROUND_RED | FOREGROUND_INTENSITY;

    // 绘制三角形
    writeToBuffer(player->x, player->y, '^', playerColor);
    writeToBuffer(player->x - 1, player->y, '/', playerColor);
    writeToBuffer(player->x + 1, player->y, '\\', playerColor);
}

// 绘制下落物体
void drawFallingObject(FallingObject* object) {
    // 为不同类型的形状设置不同颜色
    WORD objectColor;
    char objectChar[3] = " ";  // 预留3个字符位置，包括结束符

    switch (object->type) {
        case 0: // 星形 - 黄色
            objectColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            objectChar[0] = '*';
            break;
        case 1: // 方形 - 绿色
            objectColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            objectChar[0] = '#';
            break;
        case 2: // 圆形 - 青色
            objectColor = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            objectChar[0] = 'O';
            break;
        case 3: // 菱形 - 紫色
            objectColor = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            objectChar[0] = '<';
            objectChar[1] = '>';
            break;
        case 4: // 十字形 - 白色
            objectColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            objectChar[0] = '+';
            break;
    }

    // 绘制形状
    if (object->type == 3) {  // 菱形特殊处理，因为占两个字符
        writeToBuffer(object->x, object->y, '<', objectColor);
        writeToBuffer(object->x + 1, object->y, '>', objectColor);
    } else {
        writeToBuffer(object->x, object->y, objectChar[0], objectColor);
    }
}

// 绘制分数和游戏说明
void drawScore(int score) {
    // 设置默认文本颜色
    WORD textColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    // 分数信息
    char scoreText[32];
    sprintf(scoreText, "分数: %d", score);
    writeStringToBuffer(GAME_WIDTH + 2, 2, scoreText, textColor);

    // 控制说明
    writeStringToBuffer(GAME_WIDTH + 2, 4, "控制说明:", textColor);
    writeStringToBuffer(GAME_WIDTH + 2, 5, "左箭头 - 向左移动", textColor);
    writeStringToBuffer(GAME_WIDTH + 2, 6, "右箭头 - 向右移动", textColor);
    writeStringToBuffer(GAME_WIDTH + 2, 7, "ESC - 退出游戏", textColor);

    // 形状得分说明
    writeStringToBuffer(GAME_WIDTH + 2, 9, "形状得分:", textColor);

    // 每种形状带颜色的得分说明
    writeStringToBuffer(GAME_WIDTH + 2, 10, "* - 10分",
                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    writeStringToBuffer(GAME_WIDTH + 2, 11, "# - 20分",
                        FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    writeStringToBuffer(GAME_WIDTH + 2, 12, "O - 30分",
                        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    writeStringToBuffer(GAME_WIDTH + 2, 13, "<> - 40分",
                        FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    writeStringToBuffer(GAME_WIDTH + 2, 14, "+ - 50分",
                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

// 游戏结束界面 (使用双缓冲)
void showGameOver(int score) {
    // 清除缓冲区
    clearBuffer();

    // 游戏结束文本
    WORD gameOverColor = FOREGROUND_RED | FOREGROUND_INTENSITY;
    writeStringToBuffer(GAME_WIDTH / 2 - 5, GAME_HEIGHT / 2 - 2, "游戏结束!", gameOverColor);

    // 显示最终得分
    char finalScore[32];
    sprintf(finalScore, "你的最终得分: %d", score);
    writeStringToBuffer(GAME_WIDTH / 2 - 12, GAME_HEIGHT / 2, finalScore,
                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    // 退出提示
    writeStringToBuffer(GAME_WIDTH / 2 - 12, GAME_HEIGHT / 2 + 2, "按任意键退出...",
                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    // 刷新缓冲区到屏幕
    flushBuffer();

    // 等待用户按键
    FlushConsoleInputBuffer(hConsole);  // 清空输入缓冲
    getchar();
}