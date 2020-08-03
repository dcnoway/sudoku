#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "classic_board.hpp"
// #include "classic_solver.hpp"
#include "sample_sudoku.hpp"
#include "sudoku.hpp"
#include "classic_rule.hpp"

using namespace wills::sudoku;

TEST_CASE("sudoku solver check", "[sudoku]")
{
    vector<wills::sudoku::cell_value_t> 
        v(sudoku1,sudoku1 + sizeof(sudoku1) /sizeof(unsigned));
    wills::sudoku::sudoku solver;
    bool loaded;
    REQUIRE_NOTHROW(loaded = solver.load_cells(v));
    REQUIRE(loaded);

    REQUIRE_NOTHROW(solver.add_rule(make_shared<rules::every_cell_must_has_a_number>()));
    REQUIRE_NOTHROW(solver.add_rule(make_shared<rules::no_duplicated_number_in_col>()));
    REQUIRE_NOTHROW(solver.add_rule(make_shared<rules::no_duplicated_number_in_row>()));
    REQUIRE_NOTHROW(solver.add_rule(make_shared<rules::no_duplicated_number_in_region>()));
    
    vector<classic_board> ans;
    REQUIRE_NOTHROW(ans = solver.solve());
    CHECK(ans.size() > 0);
}
