#!/bin/bash
PARSER_SRC_PATH="src/parsing"
flex --o $PARSER_SRC_PATH/lex.yy.c $PARSER_SRC_PATH/scanner.l 
bison --defines=$PARSER_SRC_PATH/parser.tab.h --output=$PARSER_SRC_PATH/parser.tab.c $PARSER_SRC_PATH/parser.y
mkdir -p build
cd build
cmake ..
cmake --build . 