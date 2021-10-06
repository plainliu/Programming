> 16 成对使用new和delete时要采取相同形式

# 情景

```c++
string* strArray = new string[100];
delete strArray;
```

其中delete的行为是**未定义**的，可能后面99个对象没有被释放。

# new和delete

new和delete

- new
  - 分配内存
  - 调用构造函数（1个或多个）
- delete
  - 调用析构函数（1个或多个）
  - 释放内存

delete的问题：即将被删除的内存之内究竟有多个对象？即将被删除的那个指针，所指的是单一对象或对象数组？

数组所用的内存通常还包括“**数组大小**”的记录。

对指针delete，唯一能够让delete直到内存是否存在数组大小的记录的办法：由程序员告诉它。

```c++
delete ptr1; // 删除一个对象（当ptr1指向的是一个对象时）
delete ptr2[]; // 删除一个数组
```

`delete ptr1[]`和`delete ptr2;`都是**未定义**的行为。

## 规则

如果你调用new时使用[]，你必须在对应调用delete时也使用[]。如果你调用new时没有使用[]，那么也不应该在对应调用delete时使用[]。

延申

1. 所有的构造中new的形式相同，保证析构函数能正确delete
2. 尽量不要对数组形式做typedefs行为

```c++
typedef string Addrs[4];

string* p = new Addrs; // new Addrs[4]
delete p[]; // 需要带[]，和new形式上不匹配
```

