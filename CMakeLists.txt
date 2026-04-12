cmake_minimum_required(VERSION 3.10)

project(JogoTeste)

include_directories(extern/SDL2/include)

link_directories(extern/SDL2/lib)

add_executable(meujogo_teste src/main.c++ src/player.c++ src/barreira.c++ src/timer.c++ src/magia_negra.c++)

target_link_libraries(meujogo_teste mingw32 SDL2main SDL2 SDL2_mixer)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")