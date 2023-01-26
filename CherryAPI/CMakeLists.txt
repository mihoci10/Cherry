set(PROJECT_INCLUDE )
set(PROJECT_SRC src/example.cpp)

file(GLOB PROJECT_INCLUDE_PLATFORM_OPENGL "src/Platform/OpenGL/*.h")
file(GLOB PROJECT_SRC_PLATFORM_OPENGL "src/Platform/OpenGL/*.cpp")

add_subdirectory(extern/glm EXCLUDE_FROM_ALL)

if(${CHERRY_ENABLE_OPENGL})
    find_package(OpenGL REQUIRED)
    set(OPENGL_LIB ${OPENGL_LIB} OpenGl)
endif()

if(${CHERRY_BUILD_SHARED})
    set(LIB_TYPE "SHARED")
else()
    set(LIB_TYPE "STATIC")
endif()

add_library(CherryAPI ${LIB_TYPE} 
${PROJECT_SRC} ${PROJECT_INCLUDE}
${PROJECT_SRC_PLATFORM_OPENGL} ${PROJECT_INCLUDE_PLATFORM_OPENGL})

target_include_directories(CherryAPI PRIVATE src)

target_precompile_headers(CherryAPI PUBLIC src/cherrypch.h)

target_link_libraries(CherryAPI PUBLIC ${OPENGL_LIB} glm::glm)

source_group("" FILES ${PROJECT_SRC} ${PROJECT_INCLUDE})
source_group("Platform/OpenGL" FILES ${PROJECT_SRC_PLATFORM_OPENGL} ${PROJECT_INCLUDE_PLATFORM_OPENGL})