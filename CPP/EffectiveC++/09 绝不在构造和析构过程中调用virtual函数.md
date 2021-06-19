> 绝不在构造和析构过程中调用virtual函数

# 描述

## 构造函数中调用virtual函数

base class 构造期间virtual函数绝不会下降到derived class阶层。（在base class构造期间，virtual函数不是virtual函数）

子类对象构造，基类部分先构造，子类的成员变量还没有被初始化。

基类构造期间，对象的类型是base class而不是derived class。

- 编译器解析为base class对象
- 运行期类型信息（dynamic_cast typeid）也会视为base class对象

## 析构函数

和构造函数一致，base class部分析构期间，视对象为base class，virtual函数和dynamic_cast 等也就这么看它。

## 编译器反馈

1. 在构造析构中直接调用virtual函数【09-test1】
   - 部分编译器可能会发出警告【VS2019没有警告】
   - pure virtual，连接器找不到定义，无法链接（除非被定义）
2. 构造析构中调用init函数，init中调用virtual函数，隐蔽【09-test2】
   - 通常不会有警告
   - pure virtual函数，链接器也不会报错。执行中止程序（不论有无定义都中止）。

pure virtual 被定义没有语法错误，但一般没有意义的，会下降到子类的virtual方法，除非在base class 的构造和析构期间调用，才会调用到pure virtual方法的定义，但违反这条规则。

# 解决方案

需求：基类构造析构中调用函数，执行和子类相关的版本

方案：

- 声明为non-virtual方法
- 通过子类构造函数传递必要信息给non-virtual方法