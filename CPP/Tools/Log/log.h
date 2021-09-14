#pragma once

#include "stdarg.h"
#define UNICODE
#include "windows.h"
#include <iostream>

#include <cassert>

// 核心打印函数
void PrintHelper( const wchar_t* format, ... )
{
	wchar_t buffer[1024];

	va_list alist;
	va_start( alist, format );
	::vswprintf( buffer, 1024, format, alist );
	va_end( alist );

	::OutputDebugString( buffer );
	::OutputDebugString( L"\r\n" );
};

// ==========================================TypeCheker
template <typename T>
struct TypeCheker;

// 不实现: 编译期报错
// 实现：运行期assert
//template <typename T>
//struct TypeCheker {
//	TypeCheker( ){
//		assert(false); // 运行期检查
//	};
//};

template <>
struct TypeCheker<int> { };

//template <>
//struct TypeCheker<void*> { };

// ==========================================StaticTypeCheker

template <typename T>
struct StaticTypeCheker;

template <typename T>
//struct StaticTypeCheker { enum { Support = 0 }; };
struct StaticTypeCheker { static constexpr bool Value = false; };

template <>
//struct StaticTypeCheker<int> { enum { Support = 1 }; };
struct StaticTypeCheker<int> { static constexpr bool Value = true; };

//template <>
//struct StaticTypeCheker<void*> { enum { Support = 1 }; };
//struct StaticTypeCheker<void*> { static constexpr bool Value = true; };

// ...

// ==========================================Cheker
// 解析可变参数，为了做可变参数的类型检查

// 终止
void Checker( ) { }
// 展开函数
template <typename T, typename ...Args>
void Checker( T head, Args... rest )
{
	// 1. 构造T类型对象，支持的类型特化，不支持则编译不通过
	// TypeCheker<T>( ); // 问题：1. 生成失败，报错的时候不知道是哪个参数格式检查不通过 2. 除了编译器做检查，运行期还会调用构造生成对象
	// TypeCheker<T>; // 检查实质发生在编译期，运行时的构造没有必要（不需要构造，只给个类型）。但这样可以编译通过（有模板声明）

	// 思路
	// 1. 只有debug情况下才需要通过构造TypeCheker来检查类型
	// 2. 只有编译期间需要检查类型，运行期间最好什么事情都不发生（如果编译器可以检查，没必要区分Debug）
	// 3. 能在编译器抛错且能说明原因

	// 2. 编译期间静态检查（利用enum也是编译器就可以识别的）
	//static_assert( StaticTypeCheker<T>::Support == 1, "Unsupport Type!" );
	static_assert( StaticTypeCheker<T>::Value, "Unsupport Type!" ); // 做到了只在编译期检查，而且有输出

	// 缺点：报错中没有出错的具体类型

	Checker( rest... );
}

// ==========================================MyPrintWithTypeCheck

template <typename ...Args>
void MyPrint( const wchar_t* format, Args... args )
{
	//#DEBUG 只在debug开，就不会定义一堆Checker函数了
	Checker( args... );

	PrintHelper( format, args... );
}

//void MyPrint( const wchar_t* format, ... )
//{
//	va_list alist;
//	va_start( alist, format );
//	Checker( alist ); // 只检查了va_list（char*），没有逐项检查
//	PrintHelper( format, alist );
//	va_end( alist );
//}

// ==========================================export macros

#define MYTEXT( x ) L ## x
#define LJJ_LOG( format, ... ) \
		{ \
			MyPrint( format, ##__VA_ARGS__ ); \
		}
#define LJJ_LOGT( tag, format, ... ) \
		{ \
			MyPrint( L"[" MYTEXT( #tag ) L"] " format, ##__VA_ARGS__ ); \
		}

