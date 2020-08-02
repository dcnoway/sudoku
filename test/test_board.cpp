#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "classic_board.hpp"
#include "sample_sudoku.hpp"

using namespace wills::sudoku;

TEST_CASE("rectangle_region check", "[classic_board]")
{
    //All boundary of left top, 9 cells
    auto cell00 = make_shared<square_cell>(coordinate{0, 0});
    auto cell01 = make_shared<square_cell>(coordinate{0, 1});
    auto cell02 = make_shared<square_cell>(coordinate{0, 2});
    auto cell10 = make_shared<square_cell>(coordinate{1, 0});
    auto cell11 = make_shared<square_cell>(coordinate{1, 1});
    auto cell12 = make_shared<square_cell>(coordinate{1, 2});
    auto cell20 = make_shared<square_cell>(coordinate{2, 0});
    auto cell21 = make_shared<square_cell>(coordinate{2, 1});
    auto cell22 = make_shared<square_cell>(coordinate{2, 2});

    //All boundary of right down, 9 cells
    auto cell55 = make_shared<square_cell>(coordinate{5, 5});
    auto cell56 = make_shared<square_cell>(coordinate{5, 6});
    auto cell57 = make_shared<square_cell>(coordinate{5, 7});
    auto cell65 = make_shared<square_cell>(coordinate{6, 5});
    auto cell66 = make_shared<square_cell>(coordinate{6, 6});
    auto cell67 = make_shared<square_cell>(coordinate{6, 7});
    auto cell75 = make_shared<square_cell>(coordinate{7, 5});
    auto cell76 = make_shared<square_cell>(coordinate{7, 6});
    auto cell77 = make_shared<square_cell>(coordinate{7, 7});

    //All boundary of left down, 9 cells
    auto cell05 = make_shared<square_cell>(coordinate{0, 5});
    auto cell06 = make_shared<square_cell>(coordinate{0, 6});
    auto cell07 = make_shared<square_cell>(coordinate{0, 7});
    auto cell15 = make_shared<square_cell>(coordinate{1, 5});
    auto cell16 = make_shared<square_cell>(coordinate{1, 6});
    auto cell17 = make_shared<square_cell>(coordinate{1, 7});
    auto cell25 = make_shared<square_cell>(coordinate{2, 5});
    auto cell26 = make_shared<square_cell>(coordinate{2, 6});
    auto cell27 = make_shared<square_cell>(coordinate{2, 7});

    //All boundary of right top, 9 cells
    auto cell50 = make_shared<square_cell>(coordinate{5, 0});
    auto cell51 = make_shared<square_cell>(coordinate{5, 1});
    auto cell52 = make_shared<square_cell>(coordinate{5, 2});
    auto cell60 = make_shared<square_cell>(coordinate{6, 0});
    auto cell61 = make_shared<square_cell>(coordinate{6, 1});
    auto cell62 = make_shared<square_cell>(coordinate{6, 2});
    auto cell70 = make_shared<square_cell>(coordinate{7, 0});
    auto cell71 = make_shared<square_cell>(coordinate{7, 1});
    auto cell72 = make_shared<square_cell>(coordinate{7, 2});

    auto cell99 = make_shared<square_cell>(coordinate{9, 9});
    rectangle_region rect;

    SECTION("Uninitlized rectangle_region only contains 0,0")
    {
        REQUIRE(rect.contains(cell00));
        REQUIRE_FALSE(rect.contains(cell11));
        REQUIRE_FALSE(rect.contains(cell22));
    }

    SECTION("Init rect region with lefttop and right down")
    {
        rect.set({1, 1}, {6, 6});
        SECTION("Check left top corner")
        {
            CHECK_FALSE(rect.contains(cell00));
            CHECK_FALSE(rect.contains(cell01));
            CHECK_FALSE(rect.contains(cell02));
            CHECK_FALSE(rect.contains(cell10));
            CHECK(rect.contains(cell11));
            CHECK(rect.contains(cell12));
            CHECK_FALSE(rect.contains(cell20));
            CHECK(rect.contains(cell21));
            CHECK(rect.contains(cell22));
        }
        SECTION("Check left down corner")
        {
            CHECK_FALSE(rect.contains(cell05));
            CHECK_FALSE(rect.contains(cell06));
            CHECK_FALSE(rect.contains(cell07));
            CHECK(rect.contains(cell15));
            CHECK(rect.contains(cell16));
            CHECK_FALSE(rect.contains(cell17));
            CHECK(rect.contains(cell25));
            CHECK(rect.contains(cell26));
            CHECK_FALSE(rect.contains(cell27));
        }
        SECTION("Check right down corner")
        {
            CHECK(rect.contains(cell55));
            CHECK(rect.contains(cell56));
            CHECK_FALSE(rect.contains(cell57));
            CHECK(rect.contains(cell65));
            CHECK(rect.contains(cell66));
            CHECK_FALSE(rect.contains(cell67));
            CHECK_FALSE(rect.contains(cell75));
            CHECK_FALSE(rect.contains(cell76));
            CHECK_FALSE(rect.contains(cell77));
        }
        SECTION("Check right top corner")
        {
            CHECK_FALSE(rect.contains(cell50));
            CHECK(rect.contains(cell51));
            CHECK(rect.contains(cell52));
            CHECK_FALSE(rect.contains(cell60));
            CHECK(rect.contains(cell61));
            CHECK(rect.contains(cell62));
            CHECK_FALSE(rect.contains(cell70));
            CHECK_FALSE(rect.contains(cell71));
            CHECK_FALSE(rect.contains(cell72));
        }
        SECTION("Check a cell far from region")
        {
            REQUIRE_FALSE(rect.contains(cell99));
        }
    }

    SECTION("Init rect region with right top and left down")
    {
        rect.set({6, 1}, {1, 6});
        SECTION("Check left top corner")
        {
            CHECK_FALSE(rect.contains(cell00));
            CHECK_FALSE(rect.contains(cell01));
            CHECK_FALSE(rect.contains(cell02));
            CHECK_FALSE(rect.contains(cell10));
            CHECK(rect.contains(cell11));
            CHECK(rect.contains(cell12));
            CHECK_FALSE(rect.contains(cell20));
            CHECK(rect.contains(cell21));
            CHECK(rect.contains(cell22));
        }
        SECTION("Check left down corner")
        {
            CHECK_FALSE(rect.contains(cell05));
            CHECK_FALSE(rect.contains(cell06));
            CHECK_FALSE(rect.contains(cell07));
            CHECK(rect.contains(cell15));
            CHECK(rect.contains(cell16));
            CHECK_FALSE(rect.contains(cell17));
            CHECK(rect.contains(cell25));
            CHECK(rect.contains(cell26));
            CHECK_FALSE(rect.contains(cell27));
        }
        SECTION("Check right down corner")
        {
            CHECK(rect.contains(cell55));
            CHECK(rect.contains(cell56));
            CHECK_FALSE(rect.contains(cell57));
            CHECK(rect.contains(cell65));
            CHECK(rect.contains(cell66));
            CHECK_FALSE(rect.contains(cell67));
            CHECK_FALSE(rect.contains(cell75));
            CHECK_FALSE(rect.contains(cell76));
            CHECK_FALSE(rect.contains(cell77));
        }
        SECTION("Check right top corner")
        {
            CHECK_FALSE(rect.contains(cell50));
            CHECK(rect.contains(cell51));
            CHECK(rect.contains(cell52));
            CHECK_FALSE(rect.contains(cell60));
            CHECK(rect.contains(cell61));
            CHECK(rect.contains(cell62));
            CHECK_FALSE(rect.contains(cell70));
            CHECK_FALSE(rect.contains(cell71));
            CHECK_FALSE(rect.contains(cell72));
        }
        SECTION("Check a cell far from region")
        {
            REQUIRE_FALSE(rect.contains(cell99));
        }
    }
}

TEST_CASE("classic_board read raw data check", "[classic_board]")
{
    classic_board board;
    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    CHECK(board.shape().col_count() == 9);
    CHECK(board.shape().row_count() == 9);
    CHECK(board.shape().size() == 81);
    REQUIRE(board.get(1, 1) == 5);
    REQUIRE(board.get(2, 1) == 7);
    REQUIRE(board.get(2, 5) == 2);
    REQUIRE(board.get(9, 9) == 3);
    REQUIRE(board.get(9, 1) == 0);
    REQUIRE(board.get(1, 9) == 0);
    REQUIRE(board.get(8, 9) == 6);

    vector<wills::sudoku::cell_value_t>
        v2(sudoku2, sudoku2 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v2);
    REQUIRE(board.get(1, 1) == 1);
    REQUIRE(board.get(9, 9) == 9);
    REQUIRE(board.get(9, 1) == 0);
    REQUIRE(board.get(1, 9) == 0);
}

TEST_CASE("classic_board get() boundary check", "[classic_board]")
{
    classic_board board;
    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    cell_value_t value = 100;
    REQUIRE_NOTHROW(value = board.get(0, 0));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(1, 0));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(0, 1));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE(board.get(1, 1) == 5);

    REQUIRE_NOTHROW(value = board.get(10, 10));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(9, 10));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(10, 9));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE(board.get(9, 9) == 3);

    REQUIRE_NOTHROW(value = board.get(10, 1));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(10, 0));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(9, 0));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE(board.get(9, 1) == 0);

    REQUIRE_NOTHROW(value = board.get(1, 10));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(0, 10));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE_NOTHROW(value = board.get(0, 9));
    REQUIRE(value == CELL_COORDS_ERROR);
    REQUIRE(board.get(1, 9) == 0);
}

TEST_CASE("classic_board coords2index check", "[classic_board]")
{
    classic_board board;
    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    CHECK(board.shape().coords2index(1,1) == 0);
    CHECK(board.shape().coords2index(9,1) == 8);
    CHECK(board.shape().coords2index(1,9) == 72);
    CHECK(board.shape().coords2index(9,9) == 80);
}


TEST_CASE("classic_board set() boundary check", "[classic_board]")
{
    classic_board board;
    REQUIRE_FALSE(board.shape().check_coords(0,0));
    CHECK_THROWS(board.set({0,0},1));
    REQUIRE_FALSE(board.shape().check_coords(1,0));
    CHECK_THROWS(board.set({1, 0},1));
    REQUIRE_FALSE(board.shape().check_coords(0,1));
    CHECK_THROWS(board.set({0, 1},1));
    REQUIRE_FALSE(board.shape().check_coords(1,1));
    CHECK_THROWS(board.set({1, 1},1));

    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    cell_value_t value = 100;
    CHECK_THROWS(board.set({0,0},value));
    CHECK_THROWS(board.set({1, 0},value));
    CHECK_THROWS(board.set({0, 1},value));
    CHECK_NOTHROW(board.set({1, 1},value));
    REQUIRE(board.get({1, 1}) == value);

    CHECK_THROWS(board.set({10,0},value));
    CHECK_THROWS(board.set({10, 1},value));
    CHECK_THROWS(board.set({9, 0},value));
    CHECK_NOTHROW(board.set({9, 1},value));
    REQUIRE(board.get({9, 1}) == value);

    CHECK_THROWS(board.set({0,9},value));
    CHECK_THROWS(board.set({1, 10},value));
    CHECK_THROWS(board.set({0, 10},value));
    CHECK_NOTHROW(board.set({1, 9},value));
    REQUIRE(board.get({1, 9}) == value);


    CHECK_THROWS(board.set({10,10},value));
    CHECK_THROWS(board.set({10, 9},value));
    CHECK_THROWS(board.set({9, 10},value));
    CHECK_NOTHROW(board.set({9, 9},value));
    REQUIRE(board.get({9, 1}) == value);
}

TEST_CASE("classic_board regions() check", "[classic_board]")
{
    classic_board board;

    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    auto regions = board.regions();
    REQUIRE(regions.size() == 9);

    shared_ptr<cell> pcell11 = std::make_shared<square_cell>(coordinate{1,1});
    REQUIRE(regions[0]->contains(pcell11));
    for(int i = 1;i<regions.size();++i){
        REQUIRE_FALSE(regions[i]->contains(pcell11));
    }

    shared_ptr<cell> pcell99 = std::make_shared<square_cell>(coordinate{9,9});
    REQUIRE(regions[8]->contains(pcell99));
    for(int i = 0;i<regions.size() - 1;++i){
        REQUIRE_FALSE(regions[i]->contains(pcell99));
    }
}

TEST_CASE("classic_board regions() boundary check", "[classic_board]")
{
    classic_board board;

    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    auto regions = board.regions();
    REQUIRE(regions.size() == 9);

    shared_ptr<cell> pcell00 = std::make_shared<square_cell>(coordinate{0,0});
    for(int i = 0;i<regions.size();++i){
        REQUIRE_FALSE(regions[i]->contains(pcell00));
    }

    shared_ptr<cell> pcellxx = std::make_shared<square_cell>(coordinate{10,10});
    for(int i = 0;i<regions.size();++i){
        REQUIRE_FALSE(regions[i]->contains(pcellxx));
    }
}

TEST_CASE("classic_board region() check", "[classic_board]")
{
    classic_board board;

    vector<wills::sudoku::cell_value_t>
        v(sudoku1, sudoku1 + sizeof(sudoku1) / sizeof(unsigned));
    board.read(v);
    auto regions = board.regions();
    REQUIRE(regions.size() == 9);

    shared_ptr<cell> pcell00 = std::make_shared<square_cell>(coordinate{0,0});
    std::shared_ptr<region_t> preg;
    REQUIRE_NOTHROW(preg = board.region(pcell00));
    REQUIRE(preg == nullptr);

    shared_ptr<cell> pcellxx = std::make_shared<square_cell>(coordinate{10,10});
    REQUIRE_NOTHROW(preg = board.region(pcellxx));
    REQUIRE(preg == nullptr);

    std::shared_ptr<region_t> preg11,preg33,preg44,preg99;
    shared_ptr<cell> pcell11 = std::make_shared<square_cell>(coordinate{1,1});
    shared_ptr<cell> pcell33 = std::make_shared<square_cell>(coordinate{3,3});
    shared_ptr<cell> pcell44 = std::make_shared<square_cell>(coordinate{4,4});
    shared_ptr<cell> pcell99 = std::make_shared<square_cell>(coordinate{9,9});
    REQUIRE_NOTHROW(preg11 = board.region(pcell11));
    REQUIRE_NOTHROW(preg33 = board.region(pcell33));
    REQUIRE_NOTHROW(preg44 = board.region(pcell44));
    REQUIRE_NOTHROW(preg99 = board.region(pcell99));
    REQUIRE(preg11 != nullptr);
    REQUIRE(preg33 != nullptr);
    REQUIRE(preg44 != nullptr);
    REQUIRE(preg99 != nullptr);
    REQUIRE(((preg11 != preg44)&&(preg44 != preg99)));
    REQUIRE(preg11->contains(pcell11));
    REQUIRE(preg11->contains(pcell33));
    REQUIRE(preg44->contains(pcell44));
    REQUIRE(preg99->contains(pcell99));
    REQUIRE(preg11 == preg33);
}