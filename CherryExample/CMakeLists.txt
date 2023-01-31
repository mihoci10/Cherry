collectSources(PROJECT_SRC src)

add_executable(CherryExample
${PROJECT_SRC})

target_link_libraries(CherryExample PUBLIC CherryAPI)
target_include_directories(CherryExample PRIVATE src)

source_group("" FILES ${PROJECT_SRC})