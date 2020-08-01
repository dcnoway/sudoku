find_package(Catch2 CONFIG REQUIRED)
include(Catch)

add_executable(testdlx test1.cpp)
target_link_libraries(testdlx PRIVATE Catch2::Catch2)
catch_discover_tests(testdlx)

# add_executable(testdlxprot test_dlx_prot.cpp)
# target_link_libraries(testdlxprot PRIVATE Catch2::Catch2 sudoku_solver)
# catch_discover_tests(testdlxprot)

add_executable(testboard test_board.cpp)
target_link_libraries(testboard PRIVATE Catch2::Catch2 sudoku_board)
catch_discover_tests(testboard)

add_executable(testsolver test_solver.cpp)
target_link_libraries(testsolver PRIVATE Catch2::Catch2 sudoku_board sudoku_solver)
catch_discover_tests(testsolver)