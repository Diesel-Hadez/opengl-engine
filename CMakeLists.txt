cmake_minimum_required(VERSION 3.6)
include(FetchContent)

project(tutorial VERSION 1.0 DESCRIPTION "Tutorial"
		LANGUAGES CXX C)

add_executable(tutorial 
	src/main.cpp
	src/Shader.cpp
	src/stb_image.cpp
	src/Game.cpp
	
	src/Scene/Scene.cpp
	src/Scene/CubeScene.cpp
	src/Scene/ColoursScene.cpp
	src/Scene/PlaneScene.cpp
	src/Scene/DiffuseScene.cpp
	src/Scene/PhysicsScene.cpp
	src/Scene/ImguiScene.cpp
	src/Scene/MenuScene.cpp
	src/Scene/BetterLightingScene.cpp
	src/Scene/LightMapScene.cpp
	
	src/GPUData/GPUData.cpp
	src/GPUData/PositionTexture.cpp
	src/GPUData/Position.cpp
	src/GPUData/PositionNormals.cpp
	src/GPUData/PositionNormalsTexture.cpp
	
	src/Texture.cpp
	
	src/GameObject/GameObject.cpp
	src/GameObject/Plane.cpp
	src/GameObject/Cuboid.cpp
	
	src/GameObject/Interfaces/Collidable.cpp
	
	src/Command/Command.cpp
	src/Command/CameraMovement.cpp
	
	src/Camera/CameraInputHandler.cpp
	src/Camera/Camera.cpp
	src/Camera/FPCamera.cpp
	
	src/Pausable.cpp
	
	include/Shader.h
	include/Game.h
	
	include/Scene/Scene.h
	include/Scene/CubeScene.h
	include/Scene/ColoursScene.h
	include/Scene/PlaneScene.h
	include/Scene/DiffuseScene.h
	include/Scene/PhysicsScene.h
	include/Scene/ImguiScene.h
	include/Scene/MenuScene.h
	include/Scene/BetterLightingScene.h
	include/Scene/LightMapScene.h
	
	include/GPUData/GPUData.h
	include/GPUData/PositionTexture.h
	include/GPUData/Position.h
	include/GPUData/PositionNormals.h
	include/GPUData/PositionNormalsTexture.h
	
	include/SampleVertices.h
	include/Texture.h
	
	include/GameObject/GameObject.h
	include/GameObject/Plane.h
	include/GameObject/Cuboid.h
	
	include/GameObject/Interfaces/Collidable.h
	
	include/Command/Command.h
	include/Command/CameraMovement.h
	
	include/Camera/CameraInputHandler.h
	include/Camera/Camera.h
	include/Camera/FPCamera.h
	
	include/Pausable.h
	)

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)

FetchContent_Declare(
	ReactPhysics3D
	GIT_REPOSITORY https://github.com/DanielChappuis/reactphysics3d.git
	GIT_TAG		v0.9.0
	GIT_PROGRESS TRUE
	)
FetchContent_MakeAvailable(ReactPhysics3D)

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

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.88
)
FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    set(IMGUI_INCLUDE_DIR ${imgui_SOURCE_DIR}/)
    file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)
    file(GLOB IMGUI_HEADERS ${imgui_SOURCE_DIR}/*.h)
    
    # Will probably need to modify this for emscripten or other backends.
    set(IMGUI_GLFW_SOURCE 
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )
    set(IMGUI_GLFW_HEADER ${imgui_SOURCE_DIR}/backends/)
    add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_GLFW_SOURCE})
    add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
    target_include_directories(imgui PUBLIC ${IMGUI_INCLUDE_DIR} ${IMGUI_GLFW_HEADER} ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDE_DIR})
    target_link_libraries(imgui ${OPENGL_LIBRARIES} glfw glad)
endif ()

target_include_directories(tutorial PRIVATE 
	"${glm_SOURCE_DIR}"
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/external/stb_image"
	"${OPENGL_INCLUDE_DIR}")

target_link_libraries(tutorial PRIVATE glad OpenGL::GL glfw
	reactphysics3d imgui)
