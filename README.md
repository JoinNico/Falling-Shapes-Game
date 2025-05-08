# Shape Catcher / 形状捕捉者

## Game Introduction / 游戏简介
"Shape Catcher" is a simple command-line game running in Windows terminal environment where players control a red triangle (represented by characters) to move left and right, catching shapes falling from the top of the screen at different speeds to earn points.

"形状捕捉者"是一个在Windows命令行环境下运行的简单小游戏，玩家控制一个红色三角形（用字符表示）左右移动，捕捉从屏幕顶部以不同速度下落的形状来获得分数。

## Special Thanks / 特别鸣谢
Special thanks to DeepSeek and Claude for their assistance in code construction. / 特别鸣谢DeepSeek和Claude对代码构建的帮助。

## Features / 游戏特点
- Character graphics for game elements / 使用字符图形表示游戏元素
- Double buffering technique to eliminate flickering / 实现双缓冲技术消除屏幕闪烁
- Left/Right arrow keys to control player character / 支持左右方向键控制玩家角色
- 5 different falling shapes with different scores / 5种不同下落形状，每种形状有不同分数
- 3 different falling speeds / 3种不同下落速度
- Real-time score display / 实时分数显示

## Technical Implementation / 技术实现
1. **Double Buffering** / 双缓冲技术: Uses two alternating buffers to effectively eliminate screen flickering / 通过创建两个缓冲区交替显示，有效消除了屏幕闪烁问题
2. **Console API** / 控制台API: Uses Windows Console API for precise screen output and input control / 使用Windows控制台API实现精确的屏幕输出和输入控制
3. **Multithreading** / 多线程: Uses multithreading to handle game logic and input response for smooth gameplay / 使用多线程处理游戏逻辑和输入响应，确保流畅的游戏体验

## Controls / 游戏控制
- **Left Arrow Key** / 左方向键: Move red triangle left / 将红色三角形向左移动
- **Right Arrow Key** / 右方向键: Move red triangle right / 将红色三角形向右移动

## Scoring Rules / 得分规则
Five different shapes with corresponding scores:
游戏中有5种不同形状，每种形状对应不同分数：
1. Square(■) - 10 points / 方块(■) - 10分
2. Circle(●) - 20 points / 圆形(●) - 20分
3. Star(★) - 30 points / 星形(★) - 30分
4. Diamond(◆) - 40 points / 菱形(◆) - 40分
5. Heart(♥) - 50 points / 心形(♥) - 50分

Three falling speeds: Slow, Medium, Fast / 下落速度分为慢速、中速和快速三种

## Compile & Run / 编译运行
1. Compile with C compiler (GCC or Visual Studio) / 使用支持C语言的编译器（如GCC或Visual Studio）编译代码
2. Run executable in Windows Command Prompt / 在Windows命令行中运行生成的可执行文件

## Code Structure / 代码结构
- `main()`: Game main loop handling initialization and flow / 游戏主循环，处理初始化和游戏流程
- `initGame()`: Initialize game state / 初始化游戏状态
- `drawGame()`: Render game screen with double buffering / 使用双缓冲技术绘制游戏画面
- `updateGame()`: Update game logic / 更新游戏逻辑
- `handleInput()`: Process player input / 处理玩家输入
- `spawnShape()`: Generate new falling shapes / 生成新的下落形状

## Notes / 注意事项
- Game must run in Windows command-line environment / 游戏需要在Windows命令行环境下运行
- Ensure console window is large enough to display full game screen / 确保控制台窗口足够大以显示完整游戏画面
- Final score will be displayed when exiting game / 游戏退出时会显示最终得分

Enjoy the game! / 祝您游戏愉快！