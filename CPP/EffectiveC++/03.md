> 尽可能使用const

# const

让编译器帮忙检查不该被修改的对象是否被修改了



const使用

1. 修饰global或namespace作用域中的常量

2. 修饰文件、函数、或区块作用域中被声明为static的对象

3. 修饰classes中static或者non-static成员变量

4. 指针

   const在*左边，被指物是常量

   const在*右边，指针自身是常量

   ```c++
   char greeting[] = "Hello";
   
   char* p = greeting;					// non
   const char* p = greeting;			// const data (const *)
   char const * p = greeting;			// const data (const *)
   char* const p = greeting;			// const pointer (* const)
   const char* const p = greeting;		// const data, const pointer
   ```

   > STL 迭代器
   >
   > iterator --- T* const（迭代器本身，指针本身，不可以被修改）
   >
   > const_iterator --- const T*（迭代器本身可以修改，所指对象不可以被修改）

5. 函数声明

   - 函数返回值

     函数返回值在后续使用中不可以被修改

   - 参数

     pass by reference-to-const

     pass by pointer-to-const

   - 函数自身（成员函数）

     **只有函数常量性不同，可以被重载**

     - 重载后，const对象调用const方法，non-const调用non-const方法

     const成员函数不可以更改对象内任何non-static成员变量（bitwise constness）

     - 注意：对象有指针成员，const成员函数中不可以修改指针本身，但是可以修改指针所指对象！（需要注意接口设计及内部实现，可能在const函数中修改指针指向对象的值，也可能返回非const指针或引用修改原指针指向的对象）
     - const对象内部能修改的成员变量可以声明为**mutable**（logical constness）
     - 常量函数和非常量函数如果有相同的实现：非常量函数中调用常量函数（cast this为const再调用）



non-const成员函数调用const成员函数

```c++
class Tex {
public:
    const char& operator[](std::size_t position) const
    {
        // ...
        return text [position];
    }
    char& operator[](std::size_t position)
    {
        return const_cast<char&>(
        	static_cast<const Tex&>(*this)[position] // this转const调用const函数
        );
    }
}
```



优点

- 编译器发现如把==错写成=的问题

