collectSources(PROJECT_SRC src)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

set_target_properties(gtest PROPERTIES FOLDER "Dependencies")
set_target_properties(gtest_main PROPERTIES FOLDER "Dependencies")
set_target_properties(gmock PROPERTIES FOLDER "Dependencies")
set_target_properties(gmock_main PROPERTIES FOLDER "Dependencies")

add_executable(CherryTest
${PROJECT_SRC})

target_link_libraries(CherryTest PUBLIC 
CherryAPI 
GTest::gtest_main)

target_include_directories(CherryTest PUBLIC src)

source_group("" FILES ${PROJECT_SRC})

include(GoogleTest)
gtest_discover_tests(CherryTest)