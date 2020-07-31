#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "classic_board.hpp"

using namespace wills::sudoku;

TEST_CASE( "rectangle_region check", "[classic_board]" ) {
    coordinate zero{0,0};
    coordinate one{1,1};
    coordinate two{2,2};
    auto cell0 = make_shared<square_cell>(zero);
    auto cell11 = make_shared<square_cell>(one);
    auto cell22 = make_shared<square_cell>(two);

    auto cell55 = make_shared<square_cell>(coordinate{5,5});
    auto cell66 = make_shared<square_cell>(coordinate{6,6});
    auto cell77 = make_shared<square_cell>(coordinate{7,7});

    auto cell99 = make_shared<square_cell>(coordinate{9,9});

    rectangle_region rect;
    REQUIRE(rect.contains(cell0));
    REQUIRE_FALSE(rect.contains(cell11));
    REQUIRE_FALSE(rect.contains(cell22));

    rect.set({1,1},{6,6});
    REQUIRE_FALSE(rect.contains(cell0));
    REQUIRE(rect.contains(cell11));
    REQUIRE(rect.contains(cell22));
    REQUIRE_FALSE(rect.contains(cell99));
    REQUIRE(rect.contains(cell55));
    REQUIRE(rect.contains(cell66));
    REQUIRE_FALSE(rect.contains(cell77));

    rect.set({6,1},{1,6});
    REQUIRE_FALSE(rect.contains(cell0));
    REQUIRE(rect.contains(cell11));
    REQUIRE(rect.contains(cell22));
    REQUIRE_FALSE(rect.contains(cell99));
    REQUIRE(rect.contains(cell55));
    REQUIRE(rect.contains(cell66));
    REQUIRE_FALSE(rect.contains(cell77));
}