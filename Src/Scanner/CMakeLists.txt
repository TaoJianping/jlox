
SET(LIBSCANNER_SRC Scanner.cpp Token.cpp)
SET(LIBSCANNER_Header Scanner.h Token.h)
ADD_LIBRARY(Scanner STATIC ${LIBSCANNER_SRC} ${LIBSCANNER_Header})