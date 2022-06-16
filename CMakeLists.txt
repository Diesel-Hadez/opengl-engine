cmake_minimum_required(VERSION 3.6)
include(FetchContent)

project(tutorial VERSION 1.0 DESCRIPTION "Tutorial"
		LANGUAGES CXX C)

add_executable(tutorial 
	src/main.cpp)
