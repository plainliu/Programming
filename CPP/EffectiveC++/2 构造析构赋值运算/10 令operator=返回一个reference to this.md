> 令operator=返回一个reference to *this

# 目的

为了实现连锁赋值，右结合

```c++
int x, y, z;
x = y = z = 0;
```

# 实现

返回左侧对象

```c++
Widget& operator=(const Widget& rhs)
{
    //...
    return *this;
}
```

+=，-=等也适用同样的规则

