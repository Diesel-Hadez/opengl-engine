cmake_minimum_required(VERSION 3.6)
include(FetchContent)

project(tutorial VERSION 1.0 DESCRIPTION "Tutorial"
		LANGUAGES CXX C)

add_executable(tutorial 
	src/main.cpp
	src/Shader.cpp
	src/FPCamera.cpp
	src/stb_image.cpp
	include/Shader.h
	include/FPCamera.h
	)

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)


FetchContent_Declare(
	glad
	GIT_REPOSITORY https://github.com/Dav1dde/glad.git
	GIT_PROGRESS TRUE
	)
FetchContent_MakeAvailable(glad)

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG		   3.3-stable
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(glm)

target_include_directories(tutorial PRIVATE 
	"${glm_SOURCE_DIR}"
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/external/stb_image"
	"${OPENGL_INCLUDE_DIR}")

target_link_libraries(tutorial PRIVATE glad OpenGL::GL glfw)
