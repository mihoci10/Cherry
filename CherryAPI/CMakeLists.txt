collectSources(PROJECT_SRC src/Cherry)
collectSources(PROJECT_SRC_PLATFORM_OPENGL src/Cherry/Platform/OpenGL)
collectSources(PROJECT_SRC_UTILS src/Cherry/Utils)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        efec5db081e3aad807d0731e172ac597f6a39447
)
set(BUILD_STATIC_LIBS ON)

FetchContent_MakeAvailable(glm)
set_target_properties(glm_static PROPERTIES FOLDER "Dependencies")

FetchContent_Declare(
    sdl
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        d29e1f363239b45aedf5f81683fbb6cf52029bc2
)

FetchContent_MakeAvailable(sdl)
set_target_properties(SDL3 PROPERTIES FOLDER "Dependencies")

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

if(${CHERRY_ENABLE_IMGUI})
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        6b3435a2db4d28cb4b71de8ef06b097df2d840f7
    )
    FetchContent_MakeAvailable(imgui)

    collectSources(IMGUI_SRC src/Cherry/GUI)
    source_group("Cherry/GUI" FILES ${IMGUI_SRC})

    collectSources(IMGUI_SRC_INTERNAL ${imgui_SOURCE_DIR})
    source_group("Cherry/GUI/Internal" FILES ${IMGUI_SRC_INTERNAL})

    set(IMGUI_SRC_BACKENDS 
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h)
    source_group("Cherry/GUI/Backends" FILES ${IMGUI_SRC_BACKENDS})
    
    set(IMGUI_SRC ${IMGUI_SRC} ${IMGUI_SRC_BACKENDS} ${IMGUI_SRC_INTERNAL})
endif()

if(${CHERRY_BUILD_SHARED})
    set(LIB_TYPE "SHARED")
else()
    set(LIB_TYPE "STATIC")
endif()

add_library(CherryAPI ${LIB_TYPE} 
${PROJECT_SRC}
${PROJECT_SRC_PLATFORM_OPENGL}
${PROJECT_SRC_UTILS}
${IMGUI_SRC})

target_include_directories(CherryAPI PUBLIC src)
target_include_directories(CherryAPI PUBLIC ${imgui_SOURCE_DIR})

target_precompile_headers(CherryAPI PUBLIC src/cherrypch.h)

target_link_libraries(CherryAPI PUBLIC glm SDL3 ${OPENGL_LIB})
message(STATUS "Compiling CHERRY API with: ${OPENGL_LIB}")

source_group("Cherry" FILES ${PROJECT_SRC})
source_group("Cherry/Platform/OpenGL" FILES ${PROJECT_SRC_PLATFORM_OPENGL})
source_group("Cherry/Utils" FILES ${PROJECT_SRC_UTILS})