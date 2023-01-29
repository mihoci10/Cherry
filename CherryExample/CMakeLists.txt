collectSources(PROJECT_SRC src)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        8f470597d625ae28758c16b4293dd42d63e8a83a
)
set(GLFW_LIBRARY_TYPE "STATIC")
set(GLFW_BUILD_DOCS OFF)

FetchContent_MakeAvailable(glfw)

add_executable(CherryExample
${PROJECT_SRC})

target_link_libraries(CherryExample PUBLIC CherryAPI glfw)
target_include_directories(CherryExample PRIVATE src)

source_group("" FILES ${PROJECT_SRC})