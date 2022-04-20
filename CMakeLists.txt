cmake_minimum_required(VERSION 3.17)
project(DefinskiDaniel-etap3)

set(CMAKE_CXX_STANDARD 14)

add_executable(DefinskiDaniel-etap3 main.cpp Produkt.cpp Produkt.h Lista.cpp Lista.h Produkt_szt.cpp Produkt_szt.h Produkt_kilo.cpp Produkt_kilo.h Produkt_litr.cpp Produkt_litr.h Tcontainer.cpp Tcontainer.h)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/stdin1.txt stdin2.txt stdin3.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

