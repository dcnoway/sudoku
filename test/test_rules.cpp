#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "classic_rule.hpp"
#include "dlx.hpp"
// #include "classic_solver.hpp"
#include "sample_sudoku.hpp"

using namespace wills::sudoku;
using namespace std;

TEST_CASE("classic rule 1 check", "[classic_rule]")
{
    auto p_board = std::make_shared<classic_board>();

    vector<wills::sudoku::cell_value_t> 
        v(sudoku1,sudoku1 + sizeof(sudoku1) /sizeof(unsigned));
    p_board->read(v);
    rules::every_cell_must_has_a_number rule1;
    REQUIRE_NOTHROW(rule1.attach(p_board));
    CHECK( rule1.dlx_cols() == 81);

}
