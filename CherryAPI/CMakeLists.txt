collectSources(PROJECT_SRC src/Cherry)
collectSources(PROJECT_SRC_PLATFORM_OPENGL src/Cherry/Platform/OpenGL)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        efec5db081e3aad807d0731e172ac597f6a39447
)
set(BUILD_STATIC_LIBS ON)

FetchContent_MakeAvailable(glm)
set_target_properties(glm_static PROPERTIES FOLDER "Dependencies")

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        8f470597d625ae28758c16b4293dd42d63e8a83a
)
set(GLFW_LIBRARY_TYPE "STATIC")
set(GLFW_BUILD_DOCS OFF)

FetchContent_MakeAvailable(glfw)
set_target_properties(glfw PROPERTIES FOLDER "Dependencies")

if(${CHERRY_ENABLE_OPENGL})
    FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
        GIT_TAG        8260c05ee0121094a0dc9a53f610f514659763d6
    )
    set(ONLY_LIBS ON)
    set(glew-cmake_BUILD_SHARED OFF)
    set(glew-cmake_BUILD_STATIC ON)

    FetchContent_MakeAvailable(glew)
    set_target_properties(libglew_static PROPERTIES FOLDER "Dependencies")

    set(OPENGL_LIB libglew_static)
endif()

if(${CHERRY_BUILD_SHARED})
    set(LIB_TYPE "SHARED")
else()
    set(LIB_TYPE "STATIC")
endif()

add_library(CherryAPI ${LIB_TYPE} 
${PROJECT_SRC}
${PROJECT_SRC_PLATFORM_OPENGL})

target_include_directories(CherryAPI PUBLIC src)

target_precompile_headers(CherryAPI PUBLIC src/cherrypch.h)

target_link_libraries(CherryAPI PUBLIC glm glfw ${OPENGL_LIB})
message(STATUS "Compiling CHERRY API with: ${OPENGL_LIB}")

source_group("Cherry" FILES ${PROJECT_SRC})
source_group("Cherry/Platform/OpenGL" FILES ${PROJECT_SRC_PLATFORM_OPENGL})