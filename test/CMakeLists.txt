FIND_PACKAGE(Catch2 CONFIG REQUIRED)
INCLUDE(Catch)

ADD_EXECUTABLE(testdlx test1.cpp)
TARGET_LINK_LIBRARIES(testdlx PRIVATE Catch2::Catch2)
CATCH_DISCOVER_TESTS(testdlx)

ADD_EXECUTABLE(testboard test_board.cpp)
TARGET_LINK_LIBRARIES(testboard PRIVATE Catch2::Catch2 sudoku_board)
CATCH_DISCOVER_TESTS(testboard)

ADD_EXECUTABLE(testsolver test_solver.cpp)
TARGET_LINK_LIBRARIES(testsolver PRIVATE Catch2::Catch2 sudoku_board sudoku_solver)
CATCH_DISCOVER_TESTS(testsolver)

ADD_EXECUTABLE(testrules test_rules.cpp)
TARGET_LINK_LIBRARIES(testrules PRIVATE Catch2::Catch2 sudoku_board sudoku_solver)
CATCH_DISCOVER_TESTS(testrules)