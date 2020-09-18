project(jloxScanner)

SET(LIBRARY_OUTPUT_PATH ../lib)

SET(LIBSCANNER_SRC Scanner.cpp Token.cpp)
SET(LIBSCANNER_Header Scanner.h Token.h)
ADD_LIBRARY(Scanner STATIC ${LIBSCANNER_SRC} ${LIBSCANNER_Header} ../Common/Enum.h)