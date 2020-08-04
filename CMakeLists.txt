CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)
PROJECT(sudoku VERSION 0.1.0 DESCRIPTION "A modern C++ app to solve sudoku problems. by willswu@outlook.com")

#################################################
# CXX Compile and link segement
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_STANDARD 20)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(sudoku_board STATIC  src/classic_board.cpp)

SET(LIB_SRC_LIST src/sudoku.cpp src/classic_rule.cpp src/classic_board.cpp src/classic_enumerator.cpp)
ADD_LIBRARY(sudoku_solver STATIC ${LIB_SRC_LIST})


ADD_EXECUTABLE(sudoku src/main.cpp)
TARGET_LINK_LIBRARIES(sudoku sudoku_solver)

#################################################
# CXX unit test segement
INCLUDE(CTest)
ENABLE_TESTING()
ADD_SUBDIRECTORY(test)

#################################################
# Comment documentation segement
# Require dot, treat the other components as optional
FIND_PACKAGE(Doxygen
             REQUIRED dot
             OPTIONAL_COMPONENTS mscgen dia)
IF(DOXYGEN_FOUND)
    SET(DOXYGEN_GENERATE_HTML YES)
    SET(DOXYGEN_GENERATE_MAN YES)
    SET(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/docs)
    SET(DOXYGEN_BUILTIN_STL_SUPPORT YES)
    SET(DOXYGEN_EXTRACT_STATIC YES)
    SET(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    SET(DOXYGEN_VERBATIM_HEADERS NO)
    SET(DOXYGEN_SOURCE_BROWSER NO)
    DOXYGEN_ADD_DOCS(
        docs
        README.md
        include/
        src/
        COMMENT "Generate html doc and man pages")
ENDIF()
#################################################
# CPACK segement
SET(CPACK_PROJECT_NAME ${PROJECT_NAME})
SET(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
INCLUDE(CPack)
#################################################
