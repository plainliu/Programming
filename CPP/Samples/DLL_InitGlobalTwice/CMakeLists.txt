cmake_minimum_required(VERSION 3.10)
project(DLL_InitGlobalTwice)

set(CMAKE_CXX_STANDARD 17)

add_library(dll_initGlobal SHARED dll_initGlobal.cpp)
INSTALL(TARGETS dll_initGlobal)

add_executable(TestInitGlobal
	dll.h
	# dll_initGlobal.cpp 被编译进exe，main前构造一次全局对象
	dll_initGlobal.cpp
	main.cpp
)
