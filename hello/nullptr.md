# Differences among NULL, 0 and nullptr
- Filename: nullptr.md
- Author: Phil Lee
- Date: 02/11/2018
- Reference: http://www.cppblog.com/airtrack/archive/2012/09/16/190828.html

## 1 NULL in C
在C语言中，我们常使用NULL表示空指针，例如：

```c++
int *i = NULL;
foo_t *f = NULL;
```
实际上在C中，NULL定义如下：
```c++
#define NULL ((void *)0)	// NULL实际上是一个void *类型的指针，然后赋值给int *和foo_t *时，隐式转换成相应的类型
```
因为C++是强类型的，void * 在C++编译器中是不能隐式转换成其他指针类型的，通常情况下编译器提供的头文件这样定义NULL：
```c++
#ifdef __cplusplus
	#define NULL 0
#else
	#define NULL ((void *)0)
#endif
```

## 2 0 in C++
为了解决空指针的问题，C++引入0表示空指针。实际上C++中更习惯使用0而不是NULL表示空指针，尽管NULL在C++编译器中就是0。
为什么推荐使用0而不是NULL呢？我们看一个例子：
foo.h头文件中声明函数：
```c++
// filename: foo.h
void bar(type1 a, type2 *b);
```
另外有两个文件a.cpp、b.cpp中调用了这个函数。
```c++
// filename: a.cpp
#include "foo.h"
...
bar(a, b);
...```

```c++
// filename: b.cpp
#include "foo.h"
...
bar(a, 0);
...```
现在这些代码能够正常完美的编译运行，但是如果我们要进行功能扩展，在函数定义时使用了函数重载：
```c++
// filename: foo.h
void bar(type1 a, type2 *b);
void bar(type1 a, int b);
```
这时我们发现，a.cpp和b.cpp中对bar的调用可能就不会按预期进行了。但是我们知道在overload resolution时，b.cpp中的bar调用的是void bar(type1 a, int b)这个重载函数，这时我们可以修改一下代码：
```c++
// filename: b.cpp
...
bar(a, static_cast<type2 *>(0));
...```
假设我们b.cpp中的代码是这样的：
```c++
// filename: b.cpp
...
bar(a, NULL);	// 因为NULL实际上就是0, 其实跟前面的用法是一样的，同样调用的也是void bar(type1 a, int b)这个重载函数
...```
但是我们很容易误以为我们使用的就是NULL，应该调用void bar(type1 a, type2 *b)才对。
**因此我们说，NULL不够明显，如果用0表示则非常明显，因为0是空指针，也是整形变量。用0做为空指针比使用NULL更让人警觉。**

## 3 nullptr in C++11
上面我们说0比NULL更让人警觉，但并没有就此解决这个问题。
而c++11中的nullptr则是一个很好的解决方案。
```c++
// filename: b.cpp
...
bar(a, nullptr);	// 这时函数调用的才是我们预想的void bar(type1 a, type2 *b)
...```
而在没有c++11的nullptr时，参考《Imperfect C++》我们可以自己实现一个：
```c++
const class nullptr_t
{
public:
	template<class T>
	inline operator T*() const {
		return 0;
	}

	template<class C, class T>
	inline operator T C::*() const {
		return 0;
	}

private:
	void operator&() const;
} nullptr = {};

Reference
**airtrack** [NULL、0、nullptr](http://www.cppblog.com/airtrack/archive/2012/09/16/190828.html)

> /* END OF NULLPTR_MD */
