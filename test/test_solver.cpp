#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "classic_board.hpp"
#include "classic_solver.hpp"
#include "sample_sudoku.hpp"

using namespace wills::sudoku;

TEST_CASE("classic solver check", "[classic_solver]")
{
    auto p_board = std::make_shared<classic_board>();

    vector<wills::sudoku::cell_value_t> 
        v(sudoku1,sudoku1 + sizeof(sudoku1) /sizeof(unsigned));
    REQUIRE_NOTHROW(p_board->read(v));
    classic_solver solver;
    classic_board * p_answer;
    REQUIRE_NOTHROW(p_answer = dynamic_cast<classic_board *>(solver.solve(p_board).get()));
    REQUIRE(p_answer != nullptr);

}
