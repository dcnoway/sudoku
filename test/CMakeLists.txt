find_package(Catch2 CONFIG REQUIRED)
add_executable(Test test1.cpp)
target_link_libraries(Test PRIVATE Catch2::Catch2 sudoku_solver)

include(Catch)
catch_discover_tests(Test)
