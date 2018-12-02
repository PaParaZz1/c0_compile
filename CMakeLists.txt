CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(c0_compile)

SET(ALL_INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
	)
INCLUDE_DIRECTORIES(${ALL_INCLUDE})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

SET(ALL_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/c0_compile_symbol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/c0_compile_lexical_analysis.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/c0_compile_gramma_analysis.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/c0_compile_semantic_analysis.cpp
)

ADD_EXECUTABLE(compile_test
    ${ALL_SRC}
)

