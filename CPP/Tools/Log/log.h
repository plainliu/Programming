#pragma once

#include "stdarg.h"
#define UNICODE
#include "windows.h"
#include <iostream>

#include <cassert>

// ���Ĵ�ӡ����
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

// ��ʵ��: �����ڱ���
// ʵ�֣�������assert
//template <typename T>
//struct TypeCheker {
//	TypeCheker( ){
//		assert(false); // �����ڼ��
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
// �����ɱ������Ϊ�����ɱ���������ͼ��

// ��ֹ
void Checker( ) { }
// չ������
template <typename T, typename ...Args>
void Checker( T head, Args... rest )
{
	// 1. ����T���Ͷ���֧�ֵ������ػ�����֧������벻ͨ��
	// TypeCheker<T>( ); // ���⣺1. ����ʧ�ܣ������ʱ��֪�����ĸ�������ʽ��鲻ͨ�� 2. ���˱���������飬�����ڻ�����ù������ɶ���
	// TypeCheker<T>; // ���ʵ�ʷ����ڱ����ڣ�����ʱ�Ĺ���û�б�Ҫ������Ҫ���죬ֻ�������ͣ������������Ա���ͨ������ģ��������

	// ˼·
	// 1. ֻ��debug����²���Ҫͨ������TypeCheker���������
	// 2. ֻ�б����ڼ���Ҫ������ͣ������ڼ����ʲô���鶼��������������������Լ�飬û��Ҫ����Debug��
	// 3. ���ڱ������״�����˵��ԭ��

	// 2. �����ڼ侲̬��飨����enumҲ�Ǳ������Ϳ���ʶ��ģ�
	//static_assert( StaticTypeCheker<T>::Support == 1, "Unsupport Type!" );
	static_assert( StaticTypeCheker<T>::Value, "Unsupport Type!" ); // ������ֻ�ڱ����ڼ�飬���������

	// ȱ�㣺������û�г���ľ�������

	Checker( rest... );
}

// ==========================================MyPrintWithTypeCheck

template <typename ...Args>
void MyPrint( const wchar_t* format, Args... args )
{
	//#DEBUG ֻ��debug�����Ͳ��ᶨ��һ��Checker������
	Checker( args... );

	PrintHelper( format, args... );
}

//void MyPrint( const wchar_t* format, ... )
//{
//	va_list alist;
//	va_start( alist, format );
//	Checker( alist ); // ֻ�����va_list��char*����û��������
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

