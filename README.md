# Shape Catcher / 形状捕捉者

## Game Introduction / 游戏简介
"Shape Catcher" is a simple command-line game running in Windows terminal where players control a red triangle (represented by ASCII characters) to move left and right, catching various shapes falling from the top of the screen at different speeds to earn points.

"形状捕捉者"是一个在Windows命令行环境下运行的简单小游戏，玩家控制一个红色三角形（用ASCII字符表示）左右移动，捕捉从屏幕顶部以不同速度下落的各种形状来获得分数。

## Special Thanks / 特别鸣谢
Special thanks to DeepSeek and Claude for their assistance in code construction. / 特别鸣谢DeepSeek和Claude对代码构建的帮助。

## Features / 游戏特点
- ASCII character graphics for game elements / 使用ASCII字符图形表示游戏元素
- Double buffering technique to eliminate flickering / 实现双缓冲技术消除屏幕闪烁
- Left/Right arrow keys to control player character / 支持左右方向键控制玩家角色
- 5 different falling shapes with different point values / 5种不同下落形状，每种形状有不同分数
- 3 different falling speeds for varied gameplay / 3种不同下落速度增加游戏变化
- Real-time score display / 实时分数显示
- Game information sidebar / 游戏信息侧边栏

## Technical Implementation / 技术实现
1. **Double Buffering** / 双缓冲技术: Uses two alternating buffers to effectively eliminate screen flickering / 通过创建两个缓冲区交替显示，有效消除了屏幕闪烁问题
2. **Console API** / 控制台API: Uses Windows Console API for precise screen output and input control / 使用Windows控制台API实现精确的屏幕输出和输入控制
3. **UTF-8 Support** / UTF-8支持: Configures console for proper display of non-ASCII characters / 配置控制台以正确显示非ASCII字符
4. **Input Handling** / 输入处理: Non-blocking keyboard input detection using _kbhit() and _getch() / 使用_kbhit()和_getch()实现非阻塞键盘输入检测

## Controls / 游戏控制
- **Left Arrow Key** / 左方向键: Move red triangle left / 将红色三角形向左移动
- **Right Arrow Key** / 右方向键: Move red triangle right / 将红色三角形向右移动
- **ESC Key** / ESC键: Exit game / 退出游戏

## Scoring Rules / 得分规则
The game features five different shapes with corresponding scores:
游戏中有5种不同形状，每种形状对应不同分数：
1. Star(\*) - 10 points / 星形(\*) - 10分
2. Square(#) - 20 points / 方形(#) - 20分
3. Circle(O) - 30 points / 圆形(O) - 30分
4. Diamond(<>) - 40 points / 菱形(<>) - 40分
5. Cross(+) - 50 points / 十字形(+) - 50分

Three falling speeds affect gameplay difficulty: Slow(3), Medium(2), Fast(1) / 下落速度分为慢速(3)、中速(2)和快速(1)三种

## Compile & Run / 编译运行
1. Compile with C compiler (GCC or Visual Studio) / 使用C语言编译器（如GCC或Visual Studio）编译代码
   ```
   gcc -o shape_catcher src/*.c -I./include -luser32
   ```
2. Run executable in Windows Command Prompt / 在Windows命令行中运行生成的可执行文件
   ```
   shape_catcher.exe
   ```

## Code Structure / 代码结构
- `main.c`: Game main loop handling initialization, input processing, game updating, and rendering / 游戏主循环，处理初始化、输入处理、游戏更新和渲染
- `game.c`: Core game logic implementation including collision detection and shape generation / 核心游戏逻辑实现，包括碰撞检测和形状生成
- `character.c`: Player character movement and related functions / 玩家角色移动及相关功能
- `input.c`: Keyboard input processing / 键盘输入处理
- `render.c`: Drawing functions and double buffer implementation / 绘图功能和双缓冲实现
- `utils.c`: Utility functions / 工具函数

### Header Files / 头文件
- `game.h`: Game state and core structure definitions / 游戏状态和核心结构定义
- `character.h`: Player and falling object definitions / 玩家和下落物体定义
- `input.h`: Input handling definitions / 输入处理定义
- `render.h`: Rendering and buffer management definitions / 渲染和缓冲区管理定义
- `utils.h`: Utility function declarations / 工具函数声明

## Game Logic Details / 游戏逻辑细节
- The game creates a maximum of 20 falling objects / 游戏最多同时创建20个下落物体
- New shapes spawn approximately every 20 frames / 大约每20帧生成一个新形状
- The player's triangle spans 3 character positions for catching shapes / 玩家的三角形跨越3个字符位置用于捕捉形状
- Shapes are removed when they reach the bottom of the screen / 形状到达屏幕底部时会被移除
- Points are awarded when shapes collide with the player's triangle / 当形状与玩家的三角形碰撞时会获得相应分数
- Game loop runs at approximately 20 frames per second / 游戏循环以约20帧每秒的速度运行

## Notes / 注意事项
- Game must run in Windows command-line environment / 游戏需要在Windows命令行环境下运行
- Console window size is automatically set to accommodate game area and information panel / 控制台窗口大小会自动设置为适应游戏区域和信息面板
- Game uses UTF-8 encoding for proper text display / 游戏使用UTF-8编码以正确显示文本
- Final score will be displayed when exiting game / 游戏退出时会显示最终得分

Enjoy the game! / 祝您游戏愉快！