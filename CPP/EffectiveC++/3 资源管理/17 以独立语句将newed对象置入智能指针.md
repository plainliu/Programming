> 17 以独立语句将newed对象置入智能指针

# 情景

```c++
process(shared_ptr<Widget>(new Widget), priority());
```

上述调用可能泄露资源。

调用process前需要执行的内容

1. new Widget
2. shared_ptr构造
3. priority调用

其中12的顺序固定，3可能在1前，2前，或2后

当3卡在12中间，且3调用导致异常，1new的指针会遗失，造成泄露

```
1. new Widget
2. priority调用 (异常，new指针丢失)
3. shared_ptr构造
```

# 方案

以独立语句将newed对象置入智能指针。

```c++
shared_ptr<Widget> pw(new Widget); // 单独语句存储到指针指针
process(pw, priority());
```

原因：编译器对于“跨越语句的各项操作”没有重新排列的自由（只有在语句内它才有那个自由度）。

