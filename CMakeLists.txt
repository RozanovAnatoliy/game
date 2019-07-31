cmake_minimum_required(VERSION 3.12)
project(game)

set(CMAKE_CXX_STANDARD 17)

include_directories(utils/SFML-2.5.1/include include src/objects/include src/interface/include)
file(GLOB SRC_FILES src/*.cpp include/*.h src/objects/include/*.h src/objects/src/*.cpp src/interface/include/*.h src/interface/src/*.cpp)

add_executable(game ${SRC_FILES})

set(SFML_DIR "utils/SFML-2.5.1_32/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS window graphics audio REQUIRED)

target_link_libraries(game sfml-graphics sfml-audio)