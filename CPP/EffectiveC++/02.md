> 尽量以const，enum，inline替换#define
> 
> 宁可以编译器替换预处理器

# const

```c++
#define XXX 123.45
const double XXX = 123.45;
```
原因：

## 编译错误和调试困惑

#define定义的符号没有进入符号表。

## 常量可能会编译较小量的码

#define 盲目替换，目标码中可能有多份123.45

常量不会有替换拷贝的情况

## 注意

### 指针

声明指针为const时
1. 定义常量指针
2. 指针所指为const

```c++
const char* const name = "";
const std::string name(""); //对于字符串 string比char*更合宜？
```

### class专属常量

class的static成员，声明成const

相对宏，具有作用域，而且可以声明为私有。

两部分

1. 声明式，在类中声明
2. 定义

使用

1. 声明式（+定义式），in-class初值设定【神奇】

    ```c++
    // .h
    class A{
        static const int Num = 5;
        int a[Num];
    }
    
    // .cpp
    // static 整数型 class 常量，只要不取地址，可以不写定义式（编译器错误地要求写除外）
    // (int char bool)
    // 声明时设置了初始值，定义时不可以再写
    const int A::Num;
    ```
    
2. 旧编译器不支持声明中赋初值，在定义式中赋初值

    ```c++
    // .h
    class A{
        static const int Num;
        // int a[Num]; 不支持
    }
    
    // .cpp
    const int A::Num = 5;
    ```

    

3. 如果编译器属于2的情况，又需要在编译期间声明数组a的大小，用enum hack

    ```c++
    // .h
    class A{
        enum {Num = 5};
        int a[Num];
    }
    ```

    

**注：**in-class初值设定只支持**static 整数型 class 常量**

# enum

enum hack认识的原因

1. 某方面比较像#define而不是const
   - 不能取地址（可以用enum hack来约束别人用指针或引用访问某个整形常量）
   - 不会导致非必要的内存分配（不好的编译器可能会给整型const[虽然没有指针或引用指向它]创建空间）
2. 实用
   - 看代码能认识
   - 模板元编程的基础技术

# template

#define定义函数

- 减少function call
- 但因为只替换文本，需要注意加括号来保证运算顺序，如果有++操作可能有数据操作结果不符合预期

## template inline 函数

真正的函数，不需要操心括号的问题

产出一堆函数

可以控制作用域，写class的private inline 函数