> 20 宁以pass-by-reference-to-const替换pass-by-value

# 背景

C++默认以pass-by-value传对象到函数

- 以参数的副本为初值
- 调用返回的是函数返回值的副本

每次复制，调用copy构造，函数返回时，函数内的对象调用析构。

# pass-by-reference-to-const

```c++
bool process(const Student& s);
```

const防止修改对象

好处：

1. 高效，去掉了拷贝和析构
2. 避免slicing（对象切割）问题：以base class类型传递，值传递会只剩下基类部分，引用传递可以避免。

例外（内置类型、STL迭代器、函数对象）：

- 内置类型pass-by-value往往比pass-by-reference-to-const效率高（reference往往以指针实现）

自定义的小types，建议也使用pass-by-reference-to-const

- 效率依赖编译器，值传递不一定比引用传递效率高
- 自定义类型的大小容易有变化，甚至大小依赖编译器

