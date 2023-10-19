cmake_minimum_required(VERSION 3.12)
project(FP)

set(CMAKE_CXX_STANDARD 14)

include_directories("C:/mingw/include")
include_directories("C:/mingw64/include")
include_directories("C:/mingw64/mingw64/include")
include_directories("C:/mingw64/x86_64-w64-mingw32/include")

add_executable(FP main.cpp card.cpp card.h deck.cpp deck.h player.cpp player.h gameplay.cpp gameplay.h gamewindow.cpp gamewindow.h ellipse.cpp ellipse.h)

target_link_directories(FP PUBLIC "C:/mingw/lib")
target_link_directories(FP PUBLIC "C:/mingw64/lib")
target_link_directories(FP PUBLIC "C:/mingw64/mingw64/lib")
target_link_directories(FP PUBLIC "C:/mingw64/x86_64-w64-mingw32/lib")

target_link_libraries(FP sfml-graphics sfml-system sfml-window sfml-main)
