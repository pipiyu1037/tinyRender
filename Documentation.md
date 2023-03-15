## Components

### Camera

摄像机。

背景色：rgb`(0.1914f, 0.3008f, 0.4727f)`（抄了Unity的数据）

#### 方法

`glm::mat4 GetViewMatrix()`

得到相机的View矩阵，由渲染相关代码调用。

`void DisableReceive()`

鼠标不再控制视角旋转，鼠标箭头从屏幕出现。

`void EnableReceive()`

和以上相反，鼠标箭头消失，鼠标重新控制视角旋转。

### CharacterController

移动脚本，所有挂载这个组件的物体将会能够用WASD移动，用空格起跳。将它绑定在主摄像机上，即可得到自由移动的第一人称视角。

#### 构造方式

依附于一个`GameObject`构造。

直接调用`someGameObject.AddComponent<CharacterController>()`即可。

### GameManager

引擎开始运行时创建的最初组件，用于创建其他物体。

### MeshRenderer

网格渲染器，用于渲染一个3D模型。其默认渲染队列为1000。

#### 构造方式

依附于一个`GameObject`构造。

`someGameObject.AddComponent<MeshRenderer>(std::string path)`

其中`path`是某个`.obj`文件的相对路径。若文件不存在，构造函数会输出错误信息。

#### 属性

`std::unique_ptr<Material> material`

指向这个模型所拥有的材质。

## EngineFrame

### IMouseReceiver

接口，所有接受鼠标操作的物体都应该实现此接口。然而它现在已经弃用。

### IRenderable

接口，表示一个可渲染物。

#### 方法

`void Draw()`

绘制一次。它每帧都会被调用一次。

`int GetRenderQueue()`

获取渲染队列。渲染队列数字越小，越会先被绘制。渲染队列相同的物体，会根据深度缓冲来绘制；渲染队列不同的物体之间不使用同一个深度缓冲。

### Component

组件。

像这样可以“实现”一个组件：

```cpp
class SomeScript : public Component {
public:
	SomeScript(std::weak_ptr<GameObject> gameObject, int i) :
		Component(gameObject, "SomeScript") , i(i) {}

	void Update() override {
		MessageOut::Console << ++i << std::endl;
	}

private:
	int i;
};
```

构造函数第一项必须是`std::weak_ptr<GameObject> gameObject`，基类初始化也必须使用`Component(gameObject, "SomeScript")`，第二个参数字符串是类名（因为我们目前还不知道怎么自动获取类名，所以需要手动传给基类）。

#### 方法

`void Update()`

重写此方法，实现组件每帧的动作。

### Engine

静态类。游戏引擎，负责各个类的初始化和`Update()`等方法的调用。



### GameObject

一个游戏对象，由组件组成。

#### 属性

`int id`

独一无二的id，按照`GameObject`的生成顺序

`std::string name`

名字

`Transform transform`

变换（坐标、旋转、缩放等）。所有`GameObject`必有`transform`。

#### 方法

`template<class TComponent, class... Args>
	bool AddComponent(Args&&... args);`

添加一个组件。使用形式是：`xxx.AddComponent<SomeComponent>(args)`，其中`args`是`SomeComponent`构造函数的除了第一个参数`gameObject`以外的所有参数。

不能添加两个同类的组件。

`template<class TComponent>
	std::shared_ptr<TComponent> GetComponent();`

获得一个组件（指向它的`shared_ptr`）。使用形式是：`xxx.GetComponent<SomeComponent>()`。如果获取失败，会返回无效的指针。

`void Update()`

更新所有`Component`，由`GOManager`调用。

### GOManager

静态类，用于管理所有的`GameObject`。

#### 静态方法

`std::shared_ptr<GameObject> GOManager::MakeGameObject(const std::string& name)`

用一个字符串创建一个新的空白对象。

`void GOManager::Update()`

由引擎调用的函数，更新所有`GameObject`。

`template<class TComponent>
std::vector<TComponent*> GOManager::GetAllComponents() `

获取当前场景中所有`GameObject`的某种`Component`。这个操作非常费时，应该尽可能减少调用，不要每帧都调用，而应该把结果缓存起来。

### Input

静态类，用于获取输入信息。

#### 静态属性

`Input::key_*`

`Input::Key`类型的对象，代表键盘上的键。

#### 静态方法

`void Input::Init(GLFWwindow* _window)`

初始化，由引擎调用。需要在`RenderBase`初始化之后调用。

`void Input::Update()`

每帧更新输入状态，由引擎调用。

`bool Input::GetKeyUp(Input::Key& key)`

查询某个键是否在某帧被松开（瞬时）。

`bool Input::GetKey(Input::Key& key)`

查询某个键是否在某帧被按住（持续）。

`bool Input::GetKeyDown(Input::Key& key)`

查询某个键是否在某帧被按下（瞬时）。

**其余众多函数不一一列出，请直接查看.h文件，意思都十分明了。**

### MessageOut

用于输出调试信息。

#### 方法

`operator<<`

就像cout那样用就行。

#### 静态属性

`MessageOut MessageOut::Console`

向控制台打印消息。

`MessageOut MessageOut::Log`

向日志文件打印消息。

#### 静态方法

`void MessageOut::OpenLog(string fileName);`

初始化函数，将Log指向指定文件（追加至末尾）。由引擎调用。

### Time

静态类。用于获取引擎运行时间，或是一帧经过的时间。

#### 静态属性

`float Time::unscaledDeltaTime`

`double Time::dbDeltaTime`

一帧经过的时间，`float`与`double`版本。不会受到`timeScale`影响。

`float Time::unscaledTime`

`double Time::dbTime`

引擎开始运行直到现在经过的时间，`float`与`double`版本。不会受到`timeScale`影响。

`float Time::timeScale`

时间缩放尺度。会影响接下来两个属性：

`float Time::deltaTime` 
`float Time::time`

分别是一帧经过的时间与引擎运行的总时间，但是会受到`timeScale`影响。当`timeScale`被设为0时，所有运用这两个属性计时的脚本将会暂停。

#### 静态方法

`Time::Init()`

`Time::Update()`

由引擎调用的函数，更新`Time`的状态。

### Transform

“变换”，用来表示物体的坐标和缩放（未来可能支持旋转）。概念上，它也是依附于`GameObject`的组件之一，但是所有`GameObject`都有`transform`，所以我将其直接内嵌进`GameObject`。

#### 属性

`glm::vec3 position`

一个三维向量表示的空间位置。

`glm::vec3 scale`

一个三维向量表示的缩放。

## Render

### Meterial

材质。同一类的材质会有一个共享的Shader，会有同样类型的属性，但是属性的取值可以不同。

#### Property

```cpp
struct Property {
    float value;
    const float minVal;
    const float maxVal;
};
```

代表属性的结构体。`minVal`和`maxVal`是属性取值的合理范围。

#### 属性

`MeshRenderer& meshRenderer`

这个材质被该`MeshRenderer`所有。

#### 方法

`void Set()`

每帧调用的方法，设置渲染状态。

`Shader& GetShader()`

获取Shader。

`void SetProperty(std::string name, float value)`

根据属性的名字，设置它的值。

`std::vector<std::pair<std::string, Property>> GetProperties() `

获取所有的渲染属性和它们的名字。

### RenderBase

静态类，它负责直接和OpenGL交互。

### RenderObject

一个可渲染物体。

### ROManager

静态类，用于管理所有的`RenderObject`。

目前我感觉它是个设计上的冗余，可能在将来会与`RenderBase`合并。