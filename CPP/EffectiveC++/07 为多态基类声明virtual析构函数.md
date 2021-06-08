> 为多态基类声明virtual析构函数

# 背景

类似工厂模式的情景下，通过基类指针访问子类对象，子类对象存在于heap，需要正确地释放

- 如果通过基类指针释放，是未定义行为，可能导致泄露内存或其他资源（子类derived的成分没有被销毁）

# 方案

在基类的析构函数上加virtual，通过基类指针释放对象，会销毁整个对象



原因

- virtual的目的是允许子类的实现得以客制化，类推普通函数，通过基类指针访问函数，访问到子类的函数。
- 编译器对virtual函数的调用，**可以根据类对象中记录的vptr寻找适当的函数指针**

不适合加给析构函数virtual的情况

- class不含任何virtual函数，且通常不被当作基类（声明virtual，除多记录vptr增加内存、不能在多语言环境中传递对象外，没有任何益处）

规则

- 只有class内含只少一个virtual函数，才为它声明virtual析构函数

  - 已有virtual函数，说明能被继承，声明析构为virtual不会带来额外开销

- 拒绝继承带有non-virtual析构的class（防止通过基类指针释放子类对象的未定义行为发生）

- **pure virtual 析构函数**：希望拥有抽象class，但是没有任何virtual函数时

  （pure virtual析构必须提供定义，是编译器要求的，逐层调用析构会用）

- 析构函数加virtual的规则，只使用于带多态性质的base class身上

  不被设计为多态的base class、或者不被设计为base class的类，析构函数不适合加virtual

  根本原则是 **被设计经由base class接口处置derived class对象** 的析构函数加virtual

