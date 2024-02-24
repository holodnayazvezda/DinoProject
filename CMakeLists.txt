cmake_minimum_required(VERSION 3.21.3)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/holod/vcpkg/scripts/buildsystems/vcpkg.cmake")


project(DinoProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(DinoProject main.cpp)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(DinoProject PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

# Output file name settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/$<0:>)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .exe)
