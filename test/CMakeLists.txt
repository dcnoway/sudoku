find_package(Catch2 CONFIG REQUIRED)
add_executable(testdlx test1.cpp)
target_link_libraries(testdlx PRIVATE Catch2::Catch2 sudoku_solver)

add_executable(testdlxprot test_dlx_prot.cpp)
target_link_libraries(testdlxprot PRIVATE Catch2::Catch2 sudoku_solver)

include(Catch)
catch_discover_tests(testdlx)
catch_discover_tests(testdlxprot)
