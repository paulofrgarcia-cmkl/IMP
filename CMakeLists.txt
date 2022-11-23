cmake_minimum_required(VERSION 3.10)
project(ASLC LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)
# find_package(FLEX REQUIRED)
# find_package(BISON REQUIRED)

# bison_target(parser src/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
#             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)
# flex_target(lexer src/scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)

# add_flex_bison_dependency(lexer parser)

# include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB MyCSources src/parsing/*.c src/execution/*.c)

add_executable(ASLC ${MyCSources}
    # ${BISON_PARSER_OUTPUTS}
    # ${FLEX_LEXER_OUTPUTS}
)

# target_link_libraries(ASLC ${FLEX_LIBRARIES})

target_include_directories(ASLC PUBLIC include)
target_include_directories(ASLC PUBLIC include/parsing)
target_include_directories(ASLC PUBLIC include/execution)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(ASLC PUBLIC ${MATH_LIBRARY})
endif()