#pragma once

#include "stdarg.h"
#define UNICODE
#include "windows.h"
#include <iostream>


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

// 类型检查
template <typename T>
struct TypeCheker;

template <>
struct TypeCheker<int> {};

template <>
struct TypeCheker<void*> {};

// ...

/// <summary>
/// 目的是让可变参数列表一个一个解析，最后达到所有参数被访问的情况
/// 主要是为了做可变参数的类型检查
/// 通过统一接口传入可变参数列表，逐项检查，检查的过程实质是特化的过程
/// 特化对应不上的，输出asset？不写出来，编译不通过？
/// </summary>
// 终止
void Checker( ) { }
//展开函数
template <typename T, typename ...Args>
void Checker( T head, Args... rest )
{
	// 只有debug情况下才需要通过构造TypeCheker来检查类型
	// TypeCheker<T>; // 检查实质发生在编译期，运行时的构造没有必要（不需要构造，只给个类型）。但这样可以编译通过？
	TypeCheker<T>( ); // 问题：生成失败，报错的时候不知道是哪个参数格式检查不通过
	Checker( rest... );
}

template <typename ...Args>
void MyPrint( const wchar_t* format, Args... args )
{
	Checker( args... );
	PrintHelper( format, args... );
}

#define MYTEXT( x ) L ## x
#define LJJ_LOG( format, ... ) \
		{ \
			MyPrint( format, ##__VA_ARGS__ ); \
		}
#define LJJ_LOGT( tag, format, ... ) \
		{ \
			MyPrint( L"[" MYTEXT( #tag ) L"] " format, ##__VA_ARGS__ ); \
		}

