#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "classic_rule.hpp"
#include "dlx.hpp"
// #include "classic_solver.hpp"
// #include "sample_sudoku.hpp"

using namespace wills::sudoku;
using namespace std;

TEST_CASE("classic rule 1 check", "[classic_rule]")
{
    //size_t every_cell_must_has_a_number::dlx_cols(const rectangle_region &board_shape)
    rectangle_region bshape{{1,1},{9,9}};
    rules::every_cell_must_has_a_number rule1;
    CHECK( rule1.dlx_cols(bshape) == 81);

    value_t<cell_value_t> v1;
    
    //value_t<cell_value_t> every_cell_must_has_a_number::generate(pair<coordinate, cell_value_t> cellp)

    CHECK_NOTHROW( v1 = rule1.generate(bshape,{1,1},7));

}
