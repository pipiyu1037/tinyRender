# Little Renderer

一个小的游戏引擎。但是因为专业实训时间限制，它目前还只是个渲染器。

## 食用方式

用vs2022打开sln，先编译，然后将ThirdParty\assimp-5.2.4\lib文件夹下的assimp-vc143-mtd.dll文件复制进x64\Debug文件夹即可运行。

WASD移动，空格跳跃。（移动控制的代码在CharacterController.cpp的Update()中）

Esc键暂停并显示控制面板。

目前要向场景添加物体只能用硬编码的方式，需要将代码加入GameManager.cpp的Update()中。