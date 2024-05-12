# Snake+

+ raylib 库版本的贪吃蛇
  + 需要在官网安装 raylib(开源游戏开发库)
+ 还需要安装 GLFW3(OpenGL框架) `sudo apt install libglfw3-dev`
  + 用于创建OpenGL窗口和处理用户输入
---
+ 默认 `<Esc>` 退出
+ 因为是新建的窗口，游戏结束可以点 `R` 重玩

#### 相关函数
+ `initWindow` 初始化游戏窗口
+ `CloseWindow` 关闭窗口

+ `ClearBackground` 设置背景色
+ `BeginDrawing`, `EndDrawing` 开始/结束 绘制

+ `LoadImage` 加载一张图片
+ `LoadTextureFromImage` 从图片加载 texture
+ `DrawTexture` 画这个 texture
#### 

`<raylib.h>, <raymath.h>`

+ struct color { R, G, B, A}
  + light-green: {173, 204, 96, 255}
  + dark-green: {43, 51, 24, 255}

创建网格grid，🍎和🐍都在网格上
苹果一格：{cell}
蛇多格：{cell, cell, cell}, deque

raylib 有 Vector2，是个存x,y的结构体

