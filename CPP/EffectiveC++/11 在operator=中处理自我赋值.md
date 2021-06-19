> 在operator=中处理自我赋值

# 问题

自我赋值可能会导致的问题，比如指针指向一个已经被删除的对象

```c++
Widget& operator=(const Widget& rhs)
{
    delete pb;
    pb = new Bitmap(*rhs.pb); // rhs.pb已经被删除

    return *this;
}
```

# 方案

## 证同测试

自我检验

```c++
Widget& operator=(const Widget& rhs)
{
    if (this == &rhs) reutrn *this;

    delete pb;
    pb = new Bitmap(*rhs.pb); // 可能存在异常

    return *this;
}
```

但上面代码不具备异常安全性。

分配内存失败，则会导致pb野指针存在。

## 调整语句顺序

“异常安全性”同时保证“自我赋值安全”

【疑】

> 令人高兴的是，让operator=具备“异常安全性”往往自动获得“自我赋值安全”的回报

上面这句没有理解逻辑是什么

看书中例子吧

```c++
Widget& operator=(const Widget& rhs)
{
    Bitmap* pOrig = pb;
    pb = new Bitmap(*rhs.pb);
    delete pOrig;

    return *this;
}
```

保证了异常安全性（为啥异常安全了？new失败，delete执行还是野指针呀）

问题是自我赋值会创造副本，但这里是否有必要加证同测试

- 自我赋值的频率有多高，是否需要加
- 添加自我赋值，另一方面会使代码变大（原始代码和目标码都是）、新增了控制流、降低了流水指令的效率。

## copy and swap技术

条款29

```c++
Widget& operator=(const Widget& rhs)
{
    Widget temp(rhs);
    swap(temp);

    return *this;
}
```

变体：

```c++
Widget& operator=(Widget rhs) // pass by value 创建了副本
{
    swap(temp);

    return *this;
}
```

变体

- 牺牲了清晰性
- 但可以令编译器生成更高效的代码

