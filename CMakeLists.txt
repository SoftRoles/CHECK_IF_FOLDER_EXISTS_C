cmake_minimum_required(VERSION 2.8.9)

project (main)

# compile
add_executable(main main.c)

# link
target_link_libraries(main ${PROJECT_LINK_LIBS})