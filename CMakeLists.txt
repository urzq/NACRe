cmake_minimum_required(VERSION 3.8)
project(NACRe)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(externals/glfw)

# We often see in CMakeLists.txt thing like "file(GLOB SOME_HEADERS Some/Folder/*.hpp)", but apparently this prevent cmake from detecting changes to the source.
# Conclusion: Let's be explicit, and list all the sources.
set(MAIN
	"src/main.cpp")

set(GLAD_SOURCES 
	"externals/glad/src/glad.c")

set(IMGUI_SOURCES 
	"externals/imgui/imgui.cpp"
	"externals/imgui/imgui_draw.cpp")

set(CORE_SOURCES 
	"src/Core/Clock.cpp"
	"src/Core/Clock.h"
	"src/Core/Color.cpp"
	"src/Core/Color.h"
	"src/Core/Memory.h"
	"src/Core/ServiceLocator.cpp"
	"src/Core/ServiceLocator.h")

set(GRAPHICS_SOURCES
	"src/Graphics/Camera.cpp"
	"src/Graphics/Camera.h"
	"src/Graphics/Light.cpp"
	"src/Graphics/Light.h"
	"src/Graphics/Renderable.cpp"
	"src/Graphics/Renderable.h"
	"src/Graphics/Renderer.cpp"
	"src/Graphics/Renderer.h"
	"src/Graphics/Transform.cpp"
	"src/Graphics/Transform.h")

set(IMGUI_IMPL_SOURCES
	"src/ImGuiImpl/imgui_impl_glfw_gl3.cpp"
	"src/ImGuiImpl/imgui_impl_glfw_gl3.h")

set(INPUT_SOURCES
	"src/Input/InputManager.cpp"
	"src/Input/InputManager.h")

set(SCENE_SOURCES
	"src/Scene/MinecraftCube.cpp"
	"src/Scene/MinecraftCube.h"
	"src/Scene/Scene.cpp"
	"src/Scene/Scene.h"
	"src/Scene/SceneNode.cpp"
	"src/Scene/SceneNode.h"
	"src/Scene/WhiteCube.cpp"
	"src/Scene/WhiteCube.h")

set(SHADER_SOURCES
	"src/Shader/Shader.cpp"
	"src/Shader/Shader.h"
	"src/Shader/ShaderProgram.cpp"
	"src/Shader/ShaderProgram.h"
	"src/Shader/ShaderProgramManager.cpp"
	"src/Shader/ShaderProgramManager.h")

set(TEXTURE_SOURCES
	"src/Texture/GLTexture.cpp"
	"src/Texture/GLTexture.h"
	"src/Texture/TextureManager.cpp"
	"src/Texture/TextureManager.h")

set(VERTEX_BUFFER_SOURCES
	"src/VertexBuffer/VertexBuffer.cpp"
	"src/VertexBuffer/VertexBuffer.h"
	"src/VertexBuffer/VertexBufferData.h"
	"src/VertexBuffer/VertexBufferManager.cpp"
	"src/VertexBuffer/VertexBufferManager.h")

source_group("externals" FILES ${GLAD_SOURCES} ${IMGUI_SOURCES})
source_group("" FILES ${MAIN})
source_group("Core" FILES ${CORE_SOURCES})
source_group("Graphics" FILES ${GRAPHICS_SOURCES})
source_group("ImGuiImpl" FILES ${IMGUI_IMPL_SOURCES})
source_group("Input" FILES ${INPUT_SOURCES})
source_group("Scene" FILES ${SCENE_SOURCES})
source_group("Shader" FILES ${SHADER_SOURCES})
source_group("Texture" FILES ${TEXTURE_SOURCES})
source_group("VertexBuffer" FILES ${VERTEX_BUFFER_SOURCES})

include_directories(
    src/
    externals/glfw/include/
	externals/glad/include/
	externals/glm/
    externals/stb/
    externals/ # So we can write #include <imgui/...> and #include <par/...>
)

add_executable(${PROJECT_NAME}	
	${MAIN}
	${CORE_SOURCES}
	${GRAPHICS_SOURCES}
	${IMGUI_IMPL_SOURCES}
	${GLAD_SOURCES}
	${IMGUI_SOURCES}
	${INPUT_SOURCES}
	${SCENE_SOURCES}
	${SHADER_SOURCES}
	${TEXTURE_SOURCES}
	${VERTEX_BUFFER_SOURCES})

target_link_libraries(${PROJECT_NAME} 
	${GLAD_LIBRARIES}
	glfw
    ${GLFW_LIBRARIES})

#I assume to be working with visual studio (which kinda defeats the purpose of cmake, I know)
#and I want my generated project to have access to the /data folder.
#Setting VS_DEBUGGER_WORKING_DIRECTORY let me do that without copying the /data folder to the "out of source" dir (which can be very expensive)
#and without doing black magic (eg: environment variables or generated c++ string with the absolute path of the data folder).
#Note: we need to handle distribution, because people will also launch the .exe without visual studio, and the exe expect the /data folder to be "below him".
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
	